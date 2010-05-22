/* This file is part of kdev-pg
   Copyright (C) 2005 Roberto Raggi <roberto@kdevelop.org>
   Copyright (C) 2006 Jakob Petsovits <jpetso@gmx.at>
   Copyright (C) 2006 Alexander Dymo <adymo@kdevelop.org>

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

#include "kdev-pg-follow.h"
#include "kdev-pg-pretty-printer.h"

#include <QtCore/QDebug>

//uncomment this to see debug output for follow dependency calculation
// #define followDepsEP_DEBUG


namespace KDevPG
{

#ifdef FOLLOWDEP_DEBUG
void DebugFollowDep(Model::Node *dest, Model::Node *dep, const QString &message)
{
  qDebug() << "=============================" << endl;
  PrettyPrinter p(QTextStream( stderr ));
  qDebug() << "adding " << message << " ";
  p(dep);
  qDebug() << " (" << (uint*)dep << ")";
  qDebug() << " to follow ";
  p(dest);
  qDebug() << " (" << (uint*)dest << ")";
  qDebug() << "{" << dest->kind << "}";
  if (dest->kind == Model::Node_kind_nonTerminal)
  {
    Model::SymbolItem *s = ((Model::NonTerminalItem*)dest)->mSymbol;
    if (s)
      qDebug() << "__"; p(s); qDebug() << "__";
  }
  qDebug() << endl;
}

void debugFirstToFollowDep(Model::Node *dest, Model::Node *dep)
{
  DebugFollowDep(dest, dep, "first");
}

void debugFollowToFollowDep(Model::Node *dest, Model::Node *dep)
{
  DebugFollowDep(dest, dep, "follow");
}
#endif

//
// Calculating the FOLLOW set depends on the first set being already available
// and is in principle quite easy. There are only a few simple rules:
//
// 1. Put EOF at the end of the start rule
// 2. For every rule "items -> rulename", put FOLLOW(rulename) into FOLLOW(items)
// 3. For every item sequence "item1 item2", put first(item2) into FOLLOW(item1)
// 4. For every rule "item1 item2 -> rulename", put FOLLOW(rulename)
//    into FOLLOW(item1) if item2 can derive to epsilon ("0").
// 5. Propagate the FOLLOW sets down to the symbols where appropriate.
// 6. Loop for all rules until there are no changes in any FOLLOW set anymore.
//

NextFollow::NextFollow(bool &changed)
  : mChanged(changed)
{}

void NextFollow::operator()(Model::Node *node)
{
  Model::EvolveItem *e = nodeCast<Model::EvolveItem*>(node);
  Q_ASSERT(e != 0);
  mSymbol = e->mSymbol;
  visitNode(node);
}

void NextFollow::merge(Model::Node*__dest, World::NodeSet const &source)
{
  if (nodeCast<Model::ZeroItem*>(__dest) != 0
      || nodeCast<Model::TerminalItem*>(__dest) != 0)
    {
      return;
    }

  PrettyPrinter p(QTextStream( stdout ));

  World::NodeSet &dest = globalSystem.follow(__dest);

  for (World::NodeSet::const_iterator it = source.begin(); it != source.end(); ++it)
    {
      if (Model::TerminalItem *t = nodeCast<Model::TerminalItem*>(*it))
      {
          if( dest.contains(t) )
            /*mChanged |= false*/;
          else
            mChanged |= true;
          dest.insert(t) != dest.end();
      }
    }
}

void NextFollow::visitEvolve(Model::EvolveItem *node)
{
  Model::TerminalItem *teof = globalSystem.pushTerminal("EOF", "end of file");
  if (node == globalSystem.start && !globalSystem.follow(node->mSymbol).contains(teof) )
  {
    mChanged = true;
  }
  globalSystem.follow(node->mSymbol).insert(teof);

  merge(node->mItem, globalSystem.follow(node->mSymbol));
  addFollowToFollowDep(node->mItem, node->mSymbol);
  
  DefaultVisitor::visitEvolve(node);
}

void NextFollow::visitCons(Model::ConsItem *node)
{
  merge(node->mRight, globalSystem.follow(node));
  addFollowToFollowDep(node->mRight, node);

  merge(node->mLeft, globalSystem.first(node->mRight));
  addFirstToFollowDep(node->mLeft, node->mRight);

  if (reducesToEpsilon(node->mRight))
  {
    merge(node->mLeft, globalSystem.follow(node));
    addFollowToFollowDep(node->mLeft, node);
  }

  DefaultVisitor::visitCons(node);
}

void NextFollow::visitAlternative(Model::AlternativeItem *node)
{
  merge(node->mLeft, globalSystem.follow(node));
  addFollowToFollowDep(node->mLeft, node);
  merge(node->mRight, globalSystem.follow(node));
  addFollowToFollowDep(node->mRight, node);

  DefaultVisitor::visitAlternative(node);
}

void NextFollow::visitAction(Model::ActionItem *node)
{
  if(node->mItem)
  {
    merge(node->mItem, globalSystem.follow(node));
    addFollowToFollowDep(node->mItem, node);

    DefaultVisitor::visitAction(node);
  }
}

void NextFollow::visitTryCatch(Model::TryCatchItem *node)
{
  merge(node->mTryItem, globalSystem.follow(node));
  addFollowToFollowDep(node->mTryItem, node);

  if (node->mCatchItem)
  {
    merge(node->mCatchItem, globalSystem.follow(node));
    addFollowToFollowDep(node->mCatchItem, node);
  }

  DefaultVisitor::visitTryCatch(node);
}

void NextFollow::visitAnnotation(Model::AnnotationItem *node)
{
  merge(node->mItem, globalSystem.follow(node));
  addFollowToFollowDep(node->mItem, node);

  DefaultVisitor::visitAnnotation(node);
}

void NextFollow::visitCondition(Model::ConditionItem *node)
{
  merge(node->mItem, globalSystem.follow(node));
  addFollowToFollowDep(node->mItem, node);

  DefaultVisitor::visitCondition(node);
}

void NextFollow::visitPlus(Model::PlusItem *node)
{
  merge(node->mItem, globalSystem.first(node->mItem));
  addFirstToFollowDep(node->mItem, node->mItem);
  merge(node->mItem, globalSystem.follow(node));
  addFollowToFollowDep(node->mItem, node);

  DefaultVisitor::visitPlus(node);
}

void NextFollow::visitStar(Model::StarItem *node)
{
  merge(node->mItem, globalSystem.first(node->mItem));
  addFirstToFollowDep(node->mItem, node->mItem);
  merge(node->mItem, globalSystem.follow(node));
  addFollowToFollowDep(node->mItem, node);

  DefaultVisitor::visitStar(node);
}

void NextFollow::visitNonTerminal(Model::NonTerminalItem *node)
{
  merge(node->mSymbol, globalSystem.follow(node));

  DefaultVisitor::visitNonTerminal(node);
}

void NextFollow::visitInlinedNonTerminal(Model::InlinedNonTerminalItem* node)
{
    merge(node->mSymbol, globalSystem.follow(node));
    
    DefaultVisitor::visitNode(node->mSymbol);
}

void NextFollow::visitOperator(Model::OperatorItem *node)
{
  Q_UNUSED(node);
  /// @TODO Do we have to do anything here? I think not, because an operator-expression expects mBase not to reduce to zero, because prefix and postfix expression would not make any sense in this case. All necessary FOLLOW-stuff should be added from outside. But I am not 100% sure. (The User, 6.3.2010)
}

void NextFollow::addFirstToFollowDep(Model::Node *dest, Model::Node *dep)
{
  if (dest->kind == Model::NodeKindNonTerminal)
  {
    Model::SymbolItem *s = nodeCast<Model::NonTerminalItem*>(dest)->mSymbol;
    if (s)
      globalSystem.followDep(s).first.insert(dep);
  }
  else
    globalSystem.followDep(dest).first.insert(dep);
#ifdef FOLLOWDEP_DEBUG
  debugFirstToFollowDep(dest, dep);
#endif
}

void NextFollow::addFollowToFollowDep(Model::Node *dest, Model::Node *dep)
{
  if (dest->kind == Model::NodeKindNonTerminal)
  {
    Model::SymbolItem *s = nodeCast<Model::NonTerminalItem*>(dest)->mSymbol;
    if (s)
      globalSystem.followDep(s).second.insert(dep);
  }
  else
    globalSystem.followDep(dest).second.insert(dep);
#ifdef FOLLOWDEP_DEBUG
  debugFollowToFollowDep(dest, dep);
#endif
}

void computeFollow()
{
  bool changed = true;
  while (changed)
    {
      changed = false;
      for(QList<Model::EvolveItem*>::iterator it = globalSystem.rules.begin(); it != globalSystem.rules.end(); ++it)
      {
        NextFollow next(changed);
        next(*it);
      }
    }
}

}

// kate: space-indent on; indent-width 2; tab-width 2; show-tabs on;
