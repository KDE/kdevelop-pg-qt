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

#include "kdev-pg-clone-tree.h"
#include "kdev-pg.h"

namespace KDevPG
{

void CloneTree::visitZero(Model::ZeroItem *node)
{
  mTemps.push(node);
}

void CloneTree::visitSymbol(Model::SymbolItem *node)
{
  mTemps.push(node);
}

void CloneTree::visitTerminal(Model::TerminalItem *node)
{
  mTemps.push(node);
}

void CloneTree::visitNonTerminal(Model::NonTerminalItem *node)
{
  mTemps.push(KDevPG::nonTerminal(node->mSymbol, node->mArguments));
}

void CloneTree::visitPlus(Model::PlusItem *node)
{
  visitNode(node->mItem);

  Model::Node *item = mTemps.top();
  mTemps.pop();

  mTemps.push(KDevPG::plus(item));
}

void CloneTree::visitStar(Model::StarItem *node)
{
  visitNode(node->mItem);

  Model::Node *item = mTemps.top();
  mTemps.pop();

  mTemps.push(KDevPG::star(item));
}

void CloneTree::visitAction(Model::ActionItem *node)
{
  visitNode(node->mItem);

  Model::Node *item = mTemps.top();
  mTemps.pop();

  mTemps.push(KDevPG::action(item, node->mCode));
}

void CloneTree::visitAlternative(Model::AlternativeItem *node)
{
  visitNode(node->mLeft);

  Model::Node *left = mTemps.top();
  mTemps.pop();

  visitNode(node->mRight);

  Model::Node *right = mTemps.top();
  mTemps.pop();

  mTemps.push(KDevPG::alternative(left, right));
}

void CloneTree::visitCons(Model::ConsItem *node)
{
  visitNode(node->mLeft);

  Model::Node *left = mTemps.top();
  mTemps.pop();

  visitNode(node->mRight);

  Model::Node *right = mTemps.top();
  mTemps.pop();

  mTemps.push(KDevPG::cons(left, right));
}

void CloneTree::visitEvolve(Model::EvolveItem *node)
{
  visitNode(node->mItem);

  Model::Node *item = mTemps.top();
  mTemps.pop();

  mTemps.push(KDevPG::evolve("", item, node->mSymbol, node->mDeclarations, node->mCode));
}

void CloneTree::visitTryCatch(Model::TryCatchItem *node)
{
  visitNode(node->mTryItem);

  Model::Node *try_item = mTemps.top();
  mTemps.pop();

  Model::Node *catch_item = 0;

  if (node->mCatchItem)
    {
      visitNode(node->mCatchItem);

      catch_item = mTemps.top();
      mTemps.pop();
    }

  mTemps.push(KDevPG::tryCatch(try_item, catch_item));
}

void CloneTree::visitAlias(Model::AliasItem *node)
{
  Q_ASSERT(0); // ### not implemented yet
}

void CloneTree::visitAnnotation(Model::AnnotationItem *node)
{
  visitNode(node->mItem);

  Model::Node *item = mTemps.top();
  mTemps.pop();

  mTemps.push(KDevPG::annotation(node->mDeclaration->mName, item,
                               node->mDeclaration->mIsSequence,
                               node->mDeclaration->mStorageType));
}

Model::Node *CloneTree::clone(Model::Node *node)
{
  mTemps = QStack<Model::Node*>();
  visitNode(node);
  Model::Node *n = mTemps.top();
  mTemps.pop();
  Q_ASSERT(mTemps.empty());
  return n;
}

}
