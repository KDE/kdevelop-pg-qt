/* This file is part of kdev-pg
   Copyright (C) 2005 Roberto Raggi <roberto@kdevelop.org>
   Copyright (C) 2006 Jakob Petsovits <jpetso@gmx.at>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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

#include <QtCore/QString>

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
    QString mTok, mCond, mCode;
  };
  
  class OperatorItem : public Node
  {
  public:
    PG_NODE(Operator)
    
    struct TernDescription
    {
      Operator first, second;
      bool left: 1;
      QString priority;
    };
    struct BinDescription
    {
      Operator op;
      bool left: 1;
      QString priority;
    };
    struct UnaryDescription
    {
      Operator op;
      QString priority;
    };
    QString mBase;
    vector< pair<Operator, Operator> > mParen;
    vector< TernDescription > mTern;
    vector< BinDescription > mBin, mPost;
    vector< UnaryDescription > mPre;
    
    inline void pushParen(const Operator& op1, const Operator& op2)
    {
      mParen.push_back(make_pair(op1, op2));
    }
    inline void pushPre(const Operator& op, const QString& priority)
    {
      UnaryDescription d;
      d.op = op;
      d.priority = priority;
      mPre.push_back(d);
    }
    inline void pushPost(const Operator& op, const QString& priority)
    {
      BinDescription d;
      d.op = op;
      d.priority = priority;
      d.left = false;
      mPost.push_back(d);
    }
    inline void pushBin(const Operator& op, bool left, const QString& priority)
    {
      BinDescription d;
      d.op = op;
      d.left = left;
      d.priority = priority;
      mBin.push_back(d);
    }
    inline void pushTern(const Operator& op1, const Operator& op2, bool left, const QString& priority)
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

    enum StorateType {
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
    StorateType     mStorageType;
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

template <class _Tp>
_Tp nodeCast(Model::Node *item)
{
  if (static_cast<_Tp>(0)->NodeKind == item->kind)
    return static_cast<_Tp>(item);

  return 0;
}

extern KDevPG::Allocator<char> globalMemoryPool;

template <class _Tp>
_Tp *createNode()
{
  _Tp *node = new (globalMemoryPool.allocate(sizeof(_Tp)))_Tp();
  //reinterpret_cast<_Tp*>);
  node->kind = _Tp::NodeKind;
  return node;
}


}


#endif // KDEV_PG_AST_H
