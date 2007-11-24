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

#include "kdev-pg-first.h"

#include <cassert>


namespace KDevPG
{

void InitializeFirst::operator ()(Model::Node *node)
{
  return visitNode(node);
}

void InitializeFirst::visitNode(Model::Node *node)
{
  if (globalSystem.findInFirst(node) != globalSystem.firstEnd())
    return ; // nothing to do

  DefaultVisitor::visitNode(node);
}

void InitializeFirst::visitZero(Model::ZeroItem *node)
{
  globalSystem.first(node).insert(node);
}

void InitializeFirst::visitTerminal(Model::TerminalItem *node)
{
  globalSystem.first(node).insert(node);
}


NextFirst::NextFirst(bool &changed): mChanged(changed)
{
}

void NextFirst::operator ()(Model::Node *node)
{
  assert(nodeCast<Model::EvolveItem*>(node));
  mMergeBlocked = false;
  mMergeZeroBlocked = false;
  mItem = node;
  visitNode(node);
}

bool NextFirst::blockMerge(bool block)
{
  bool old = mMergeBlocked;
  mMergeBlocked = block;
  return old;
}

bool NextFirst::blockZeroMerge(bool block)
{
  bool old = mMergeZeroBlocked;
  mMergeZeroBlocked = block;
  return old;
}

void NextFirst::merge(Model::Node *__dest, Model::Node *__source, int K)
{
  World::NodeSet &dest = globalSystem.first(__dest, K);
  World::NodeSet &source = globalSystem.first(__source, K);

  for (World::NodeSet::iterator it = source.begin(); it != source.end(); ++it)
    {
      if (mMergeZeroBlocked == true && nodeCast<Model::ZeroItem*>(*it))
        {
          continue;
        }

      if( dest.contains(*it) )
        mChanged |= false;
      else
      {
        mChanged |= true;
      }
      dest.insert(*it);
    }
}

void NextFirst::visitNode(Model::Node *node)
{
  DefaultVisitor::visitNode(node);

  if (!mMergeBlocked)
    {
      merge(mItem, node);
    }
}

void NextFirst::visitZero(Model::ZeroItem *)
{
}

void NextFirst::visitTerminal(Model::TerminalItem *)
{
}

void NextFirst::visitNonTerminal(Model::NonTerminalItem *node)
{
  DefaultVisitor::visitNonTerminal(node);

  merge(node, node->mSymbol);
}

void NextFirst::visitSymbol(Model::SymbolItem *)
{
}

void NextFirst::visitPlus(Model::PlusItem *node)
{
  DefaultVisitor::visitPlus(node);

  merge(node, node->mItem);
}

void NextFirst::visitStar(Model::StarItem *node)
{
  DefaultVisitor::visitStar(node);

  if ( !globalSystem.first(node).contains(globalSystem.zero()) )
    mChanged = true;
  globalSystem.first(node).insert(globalSystem.zero());

  merge(node, node->mItem);
}

void NextFirst::visitAction(Model::ActionItem *node)
{
  DefaultVisitor::visitAction(node);

  merge(node, node->mItem);
}

void NextFirst::visitAlternative(Model::AlternativeItem *node)
{
  DefaultVisitor::visitAlternative(node);

  merge(node, node->mLeft);
  merge(node, node->mRight);
}

void NextFirst::visitCons(Model::ConsItem *node)
{
  bool blocked = blockMerge(true);
  visitNode(node->mRight);
  blockMerge(blocked);

  bool zero_blocked = mMergeZeroBlocked;
  if (!reducesToEpsilon(node->mRight))
    zero_blocked = blockZeroMerge(true);

  visitNode(node->mLeft);
  merge(node, node->mLeft);

  if (reducesToEpsilon(node->mLeft))
    {
      visitNode(node->mRight);
      merge(node, node->mRight);
    }

  blockZeroMerge(zero_blocked);
}

void NextFirst::visitEvolve(Model::EvolveItem *node)
{
  visitNode(node->mItem);
  merge(node, node->mItem);

  merge(node->mSymbol, node);
}

void NextFirst::visitTryCatch(Model::TryCatchItem *node)
{
  DefaultVisitor::visitTryCatch(node);

  merge(node, node->mTryItem);

  if (node->mCatchItem)
    merge(node, node->mCatchItem);
}

void NextFirst::visitAlias(Model::AliasItem *node)
{
  DefaultVisitor::visitAlias(node);
  assert(0); // ### not implemented yet
}

void NextFirst::visitAnnotation(Model::AnnotationItem *node)
{
  DefaultVisitor::visitAnnotation(node);

  merge(node, node->mItem);
}

void NextFirst::visitCondition(Model::ConditionItem* node)
{
  DefaultVisitor::visitCondition(node);

  merge(node, node->mItem);
}

void computeFirst() // the closure of the FIRST sets
{
  for(QList<Model::Node*>::iterator it = globalSystem.rules.begin(); it != globalSystem.rules.end(); it++)
  {
    InitializeFirst initfirst;
    initfirst(*it);
  }

  bool changed = true;
  while (changed)
    {
      changed = false;
      for(QList<Model::Node*>::iterator it = globalSystem.rules.begin(); it != globalSystem.rules.end(); it++)
      {
        NextFirst next(changed);
        next(*it);
      }
    }
}

}
