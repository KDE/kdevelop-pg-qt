/* This file is part of kdev-pg-qt
   Copyright (C) 2005 Roberto Raggi <roberto@kdevelop.org>
   Copyright (C) 2006 Jakob Petsovits <jpetso@gmx.at>
   Copyright (C) 2010 Jonathan Schmidt-Dominé <devel@the-user.org>

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

void initializeFirst()
{
  globalSystem.first(globalSystem.zero()).insert(globalSystem.zero());
  for(__typeof__(globalSystem.terminals.begin()) i = globalSystem.terminals.begin();
      i != globalSystem.terminals.end();
      ++i)
  {
      globalSystem.first(*i).insert(*i);
  }
}

NextFirst::NextFirst(bool &changed): mChanged(changed)
{
}

void NextFirst::operator ()(Model::Node *node)
{
  assert(nodeCast<Model::EvolveItem*>(node));
  mMergeZeroBlocked = false;
  visitNode(node);
}

bool NextFirst::blockZeroMerge(bool block)
{
  bool old = mMergeZeroBlocked;
  mMergeZeroBlocked = block;
  return old;
}

void NextFirst::merge(Model::Node *__dest, Model::Node *__source, int K)
{
  if(__source == 0 || __dest == 0)
    return;
  
  World::NodeSet &dest = globalSystem.first(__dest, K);
  World::NodeSet &source = globalSystem.first(__source, K);

  for (World::NodeSet::iterator it = source.begin(); it != source.end(); ++it)
    {
      if (mMergeZeroBlocked && nodeCast<Model::ZeroItem*>(*it))
        {
          continue;
        }
      if( !dest.contains(*it) )
      {
        dest.insert(*it);
        mChanged = true;
      }
    }
}

void NextFirst::visitNode(Model::Node *node)
{
  if(node == 0)
    return;
  
  if(mVisited.contains(node))
    return;
  
  mVisited.insert(node);
  
  DefaultVisitor::visitNode(node);

  mVisited.remove(node);
}

void NextFirst::visitAlternative(Model::AlternativeItem *node)
{
  DefaultVisitor::visitAlternative(node);

  merge(node, node->mLeft);
  merge(node, node->mRight);
}

void NextFirst::visitCons(Model::ConsItem *node)
{
  visitNode(node->mRight);

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

void computeFirst() // the closure of the FIRST sets
{
  initializeFirst();

  bool changed = true;
  NextFirst next(changed);
  while (changed)
    {
      changed = false;
      for(QList<Model::EvolveItem*>::iterator it = globalSystem.rules.begin(); it != globalSystem.rules.end(); ++it)
      {
        next(*it);
      }
    }
}

}
