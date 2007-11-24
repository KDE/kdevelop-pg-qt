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

#include "kdev-pg.h"
#include "kdev-pg-ast.h"


#include <QtCore/QDebug>

namespace KDevPG
{

Model::ZeroItem *zero()
{
  Model::ZeroItem *node = createNode<Model::ZeroItem>();
  return node;
}

Model::PlusItem *plus(Model::Node *item)
{
  Model::PlusItem *node = createNode<Model::PlusItem>();
  node->mItem = item;
  return node;
}

Model::StarItem *star(Model::Node *item)
{
  Model::StarItem *node = createNode<Model::StarItem>();
  node->mItem = item;
  return node;
}

Model::SymbolItem *symbol(const QString& name)
{
  Model::SymbolItem *node = createNode<Model::SymbolItem>();
  node->mName = name;
  node->mCapitalizedName = name;
  node->mCapitalizedName.replace( 0, 1, name.at(0).toUpper() );
  return node;
}

Model::ActionItem *action(Model::Node *item, const QString& code)
{
  Model::ActionItem *node = createNode<Model::ActionItem>();
  node->mItem = item;
  node->mCode = code;
  return node;
}

Model::AlternativeItem *alternative(Model::Node *left, Model::Node *right)
{
  Model::AlternativeItem *node = createNode<Model::AlternativeItem>();
  node->mLeft = left;
  node->mRight = right;
  return node;
}

Model::ConsItem *cons(Model::Node *left, Model::Node *right)
{
  Model::ConsItem *node = createNode<Model::ConsItem>();
  node->mLeft = left;
  node->mRight = right;
  return node;
}

Model::EvolveItem *evolve(
    Model::Node *item, Model::SymbolItem *symbol,
    Model::VariableDeclarationItem *declarations, const QString& code)
{
  Model::EvolveItem *node = createNode<Model::EvolveItem>();
  node->mItem = item;
  node->mSymbol = symbol;
  node->mDeclarations = declarations;
  node->mCode = code;
  return node;
}

Model::TryCatchItem *tryCatch(Model::Node *try_item, Model::Node *catch_item)
{
  Model::TryCatchItem *node = createNode<Model::TryCatchItem>();
  node->mTryItem = try_item;
  node->mCatchItem = catch_item;
  node->mUnsafe = false;
  return node;
}

Model::AliasItem *alias(const QString& code, Model::SymbolItem *symbol)
{
  Model::AliasItem *node = createNode<Model::AliasItem>();
  node->mCode = code;
  node->mSymbol = symbol;
  return node;
}

Model::TerminalItem *terminal(const QString& name, const QString& description)
{
  Model::TerminalItem *node = createNode<Model::TerminalItem>();
  node->mName = name;
  node->mDescription = description;
  return node;
}

Model::NonTerminalItem *nonTerminal(Model::SymbolItem *symbol, const QString& arguments)
{
  Model::NonTerminalItem *node = createNode<Model::NonTerminalItem>();
  node->mSymbol = symbol;
  node->mArguments = arguments;
  return node;
}

Model::AnnotationItem *annotation(
    const QString& name, Model::Node *item, bool isSequence,
    Model::VariableDeclarationItem::StorateType storageType)
{
  Model::AnnotationItem *node = createNode<Model::AnnotationItem>();
  node->mItem = item;

  Model::VariableDeclarationItem::VariableType variableType;
  QString type;

  if (Model::TerminalItem *t = nodeCast<Model::TerminalItem*>(item))
    {
      variableType = Model::VariableDeclarationItem::TypeToken;
      type = t->mName;
    }
  else if (Model::NonTerminalItem *nt = nodeCast<Model::NonTerminalItem*>(item))
    {
      variableType = Model::VariableDeclarationItem::TypeNode;
      type = nt->mSymbol->mName;
    }
  else
    {
      Q_ASSERT(0); // ### item must either be a terminal or a nonTerminal
    }

  node->mDeclaration =
     variableDeclaration(Model::VariableDeclarationItem::DeclarationLocal,
                              storageType, variableType, isSequence, name, type);
  return node;
}

Model::ConditionItem *condition(const QString& code, Model::Node *item)
{
  Model::ConditionItem *node = createNode<Model::ConditionItem>();
  node->mCode = code;
  node->mItem = item;
  return node;
}

Model::VariableDeclarationItem *variableDeclaration(
      Model::VariableDeclarationItem::DeclarationType declarationType,
      Model::VariableDeclarationItem::StorateType     storageType,
      Model::VariableDeclarationItem::VariableType    variableType,
      bool isSequence, const QString& name, const QString& type)
{
  Model::VariableDeclarationItem *node = createNode<Model::VariableDeclarationItem>();
  node->mName = name;
  node->mType = type;
  node->mDeclarationType = declarationType;
  node->mStorageType     = storageType;
  node->mVariableType    = variableType;
  node->mIsSequence      = isSequence;
  node->mNext = 0;
  return node;
}

Settings::MemberItem *member(Settings::MemberItem::MemberKind kind, const QString& code)
{
  Settings::MemberItem *node = createNode<Settings::MemberItem>();
  node->mMemberKind = kind;
  node->mCode = code;
  return node;
}


bool reducesToEpsilon(Model::Node *node)
{
  if (Model::ConsItem *c = nodeCast<Model::ConsItem*>(node))
    {
      return reducesToEpsilon(c->mLeft) && reducesToEpsilon(c->mRight);
    }
  else if (Model::AlternativeItem *a = nodeCast<Model::AlternativeItem*>(node))
    {
      return reducesToEpsilon(a->mLeft) || reducesToEpsilon(a->mRight);
    }
  else if (Model::ActionItem *a = nodeCast<Model::ActionItem*>(node))
    {
      return reducesToEpsilon(a->mItem);
    }
  else if (Model::ConditionItem *c = nodeCast<Model::ConditionItem*>(node))
    {
      return reducesToEpsilon(c->mItem);
    }
  else if (Model::TryCatchItem *t = nodeCast<Model::TryCatchItem*>(node))
    {
      return reducesToEpsilon(t->mTryItem)
             || (t->mCatchItem && reducesToEpsilon(t->mCatchItem));
    }
  else if (Model::AnnotationItem *a = nodeCast<Model::AnnotationItem*>(node))
    {
      return reducesToEpsilon(a->mItem);
    }
  else if (Model::NonTerminalItem *n = nodeCast<Model::NonTerminalItem*>(node))
    {
      return reducesToEpsilon(n->mSymbol);
    }
  else if (Model::SymbolItem *s = nodeCast<Model::SymbolItem*>(node))
    {
      return globalSystem.first(s).find(globalSystem.zero()) != globalSystem.first(s).end(); // hmm
    }
  else if (Model::PlusItem *p = nodeCast<Model::PlusItem*>(node))
    {
      return reducesToEpsilon(p->mItem);
    }
  else if (nodeCast<Model::StarItem*>(node))
    {
      return true;
    }
  else if (nodeCast<Model::ZeroItem*>(node))
    {
      return true;
    }

  return false;
}

bool isZero(Model::Node *node)
{
  if (Model::ActionItem *a = nodeCast<Model::ActionItem*>(node))
    {
      return isZero(a->mItem);
    }
  else if (Model::ConditionItem *c = nodeCast<Model::ConditionItem*>(node))
    {
      return isZero(c->mItem);
    }
  else if (Model::AnnotationItem *a = nodeCast<Model::AnnotationItem*>(node))
    {
      return isZero(a->mItem);
    }
  else if (Model::PlusItem *p = nodeCast<Model::PlusItem*>(node))
    {
      return isZero(p->mItem);
    }
  else if (Model::StarItem *s = nodeCast<Model::StarItem*>(node))
    {
      return isZero(s->mItem);
    }
  else if (nodeCast<Model::ZeroItem*>(node))
    {
      return true;
    }

  return false;
}

}

QTextStream& operator << (QTextStream& out, KDevPG::Model::Node const *__node)
{
  KDevPG::Model::Node *node = const_cast<KDevPG::Model::Node*>(__node);

  if (KDevPG::nodeCast<KDevPG::Model::ZeroItem*>(node))
    return (out << "0");
  else if (KDevPG::Model::SymbolItem *s = KDevPG::nodeCast<KDevPG::Model::SymbolItem *>(node))
    return (out << s->mName);
  else if (KDevPG::Model::TerminalItem *t = KDevPG::nodeCast<KDevPG::Model::TerminalItem *>(node))
    return (out << t->mName);
  else if (KDevPG::Model::AnnotationItem *a = KDevPG::nodeCast<KDevPG::Model::AnnotationItem *>(node))
    return (out << ((a->mDeclaration->mIsSequence) ? "#" : "")
                << a->mDeclaration->mName
                << ((a->mDeclaration->mStorageType
                     == KDevPG::Model::VariableDeclarationItem::StorageTemporary) ? ":" : "=")
                << a->mItem);
#if 0

  else
    if (Model::EvolveItem *e = nodeCast<Model::EvolveItem *>(node))
      return (out << "evolve:" << e->mSymbol->mName);
#endif

  Q_ASSERT(0);
  return out;
}

