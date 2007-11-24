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

    char const *mName;
  };

  class ActionItem: public Node
  {
  public:
    PG_NODE(Action)

    Node *mItem;
    char const *mCode;
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

    char const *mCode;
    SymbolItem *mSymbol;
  };

  class TerminalItem: public Node
  {
  public:
    PG_NODE(Terminal)

    char const *mName;
    char const *mDescription;
  };

  class NonTerminalItem: public Node
  {
  public:
    PG_NODE(NonTerminal)

    SymbolItem *mSymbol;
    char const *mArguments;
  };

  class VariableDeclarationItem: public Node
  {
  public:
    PG_NODE(VariableDeclaration)

    enum DeclarationType {
      DeclarationArgument,
      DeclarationLocal,
    };

    enum StorateType {
      StorageAstMember,
      StorageTemporary,
    };

    enum VariableType {
      TypeNode,
      TypeToken,
      TypeVariable,
    };

    char const *mType;
    char const *mName;

    DeclarationType mDeclarationType;
    StorateType     mStorageType;
    VariableType    mVariableType;
    bool                  mIsSequence;

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

    char const *mCode;
    Node *mItem;
  };

  class EvolveItem: public Node
  {
  public:
    PG_NODE(Evolve)

    Node *mItem;
    SymbolItem *mSymbol;
    VariableDeclarationItem *mDeclarations;
    char const *mCode;
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
      DestructorCode       = 16,
    };

    MemberKind mMemberKind;
    char const *mCode;
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
  _Tp *node = reinterpret_cast<_Tp*>(globalMemoryPool.allocate(sizeof(_Tp)));
  node->kind = _Tp::NodeKind;
  return node;
}


}


#endif // KDEV_PG_AST_H
