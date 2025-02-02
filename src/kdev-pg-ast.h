/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>
    SPDX-FileCopyrightText: 2010 Jonathan Schmidt-Dominé <devel@the-user.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEV_PG_AST_H
#define KDEV_PG_AST_H

#include "kdev-pg-allocator.h"
#include "kdev-pg-memory-pool.h"

#include <vector>
#include <utility>
using std::vector;
using std::pair;
using std::make_pair;

#include <QString>

#include <QDebug>

#define PG_NODE(k) \
    enum { NodeKind = NodeKind##k };

namespace KDevPG
{

// the kdev-pg calculus
namespace Model
{

  enum NodeKind {
    NodeKindItem = 0,
    NodeKindZero = 1,
    NodeKindPlus = 2,
    NodeKindStar = 3,
    NodeKindSymbol = 4,
    NodeKindAction = 5,
    NodeKindAlternative = 6,
    NodeKindCons = 7,
    NodeKindEvolve = 8,
    NodeKindTryCatch = 9,
    NodeKindAlias = 10,
    NodeKindTerminal = 11,
    NodeKindNonTerminal = 12,
    NodeKindAnnotation = 13,
    NodeKindCondition = 14,
    NodeKindVariableDeclaration = 15,
    NodeKindOperator = 16,
    NodeKindInlinedNonTerminal = 17,

    NodeKindLast
  };

  class Node
  {
  public:
    PG_NODE(Item)

    int kind;
  };

  class ZeroItem: public Node
  {
  public:
    PG_NODE(Zero)
  };

  class PlusItem: public Node
  {
  public:
    PG_NODE(Plus)

    Node *mItem;
  };

  class StarItem: public Node
  {
  public:
    PG_NODE(Star)

    Node *mItem;
  };

  class SymbolItem: public Node
  {
  public:
    PG_NODE(Symbol)

    QString mName;
    QString mCapitalizedName;
  };

  class ActionItem: public Node
  {
  public:
    PG_NODE(Action)

    Node *mItem;
    QString mCode;
  };

  class AlternativeItem: public Node
  {
  public:
    PG_NODE(Alternative)

    Node *mLeft;
    Node *mRight;
  };

  class ConsItem: public Node
  {
  public:
    PG_NODE(Cons)

    Node *mLeft;
    Node *mRight;
  };

  class TryCatchItem: public Node
  {
  public:
    PG_NODE(TryCatch)

    Node *mTryItem;
    Node *mCatchItem; // contains 0 for "catch(recover)"
    bool mUnsafe;
  };

  class AliasItem: public Node
  {
  public:
    PG_NODE(Alias)

    QString mCode;
    SymbolItem *mSymbol;
  };
  
  class InlinedNonTerminalItem: public Node
  {
  public:
    PG_NODE(InlinedNonTerminal)
    
    SymbolItem *mSymbol;
  };

  class TerminalItem: public Node
  {
  public:
    PG_NODE(Terminal)

    QString mName;
    QString mDescription;
  };

  class NonTerminalItem: public Node
  {
  public:
    PG_NODE(NonTerminal)

    SymbolItem *mSymbol;
    QString mArguments;
  };
  
  class Operator
  {
  public:
    Node *mTok;
    QString mCond, mCode;
  };
  
  class OperatorItem : public Node
  {
  public:
    PG_NODE(Operator)
    
    struct TernDescription
    {
      Operator first, second;
      QString left;
      QString priority;
    };
    struct BinDescription
    {
      Operator op;
      QString left;
      QString priority;
    };
    struct UnaryDescription
    {
      Operator op;
      QString priority;
    };
    struct ParenDescription
    {
      Operator first, second;
    };
    QString mName;
    NonTerminalItem *mBase;
    std::vector< ParenDescription > mParen;
    std::vector< TernDescription > mTern;
    std::vector< BinDescription > mBin, mPost;
    std::vector< UnaryDescription > mPre;
    
    inline void pushParen(const Operator& op1, const Operator& op2)
    {
      ParenDescription d;
      d.first = op1;
      d.second = op2;
      mParen.push_back(d);
    }
    inline void pushPre(const Operator& op, const QString& priority)
    {
      UnaryDescription d;
      d.op = op;
      d.priority = priority;
      mPre.push_back(d);
    }
    inline void pushPost(const Operator& op, const QString& left, const QString& priority)
    {
      BinDescription d;
      d.op = op;
      d.priority = priority;
      d.left = left;
      mPost.push_back(d);
    }
    inline void pushBin(const Operator& op, const QString& left, const QString& priority)
    {
      BinDescription d;
      d.op = op;
      d.left = left;
      d.priority = priority;
      mBin.push_back(d);
    }
    inline void pushTern(const Operator& op1, const Operator& op2, const QString& left, const QString& priority)
    {
      TernDescription d;
      d.first = op1;
      d.second = op2;
      d.left = left;
      d.priority = priority;
      mTern.push_back(d);
    }
  };

  class VariableDeclarationItem: public Node
  {
  public:
    PG_NODE(VariableDeclaration)

    enum DeclarationType {
      DeclarationArgument,
      DeclarationLocal
    };

    enum StorageType {
      StorageAstMember,
      StorageTemporary
    };

    enum VariableType {
      TypeNode,
      TypeToken,
      TypeVariable
    };

    QString mType;
    QString mCapitalizedType;
    QString mName;

    DeclarationType mDeclarationType;
    StorageType     mStorageType;
    VariableType    mVariableType;
    bool            mIsSequence;

    VariableDeclarationItem *mNext;
  };

  class AnnotationItem: public Node
  {
  public:
    PG_NODE(Annotation)

    Node *mItem;
    VariableDeclarationItem *mDeclaration;
  };

  class ConditionItem: public Node
  {
  public:
    PG_NODE(Condition)

    QString mCode;
    Node *mItem;
  };

  class EvolveItem: public Node
  {
  public:
    PG_NODE(Evolve)

    Node *mItem;
    SymbolItem *mSymbol;
    VariableDeclarationItem *mDeclarations;
    QString mCode;
  };

} // namespace model


// configuration stuff outside the model
namespace Settings
{

  enum NodeKind {
    NodeKindMember = 30,

    NodeKindLast
  };

  class MemberItem: public Model::Node
  {
  public:
    PG_NODE(Member)

    enum MemberKind {
      PublicDeclaration    = 1,
      ProtectedDeclaration = 2,
      PrivateDeclaration   = 4,
      ConstructorCode      = 8,
      DestructorCode       = 16
    };

    MemberKind mMemberKind;
    QString mCode;
  };

} // namespace settings

template<class T>
struct StripPtr { typedef T Result; };
template<class T>
struct StripPtr<T*> { typedef T Result; };

template <class _Tp>
_Tp nodeCast(Model::Node *item)
{
  if (StripPtr<_Tp>::Result::NodeKind == item->kind)
    return static_cast<_Tp>(item);

  return nullptr;
}

extern KDevPG::Allocator<char> globalMemoryPool;

template <class _Tp>
_Tp *createNode()
{
  _Tp *node = new (globalMemoryPool.allocate(sizeof(_Tp)))_Tp();
  node->kind = _Tp::NodeKind;
  return node;
}


}


#endif // KDEV_PG_AST_H
