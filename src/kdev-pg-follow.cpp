/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>
    SPDX-FileCopyrightText: 2006 Alexander Dymo <adymo@kdevelop.org>
    SPDX-FileCopyrightText: 2010 Jonathan Schmidt-Dominé <devel@the-user.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg-follow.h"
#include "kdev-pg-pretty-printer.h"

#include <QTextStream>

//uncomment this to see debug output for follow dependency calculation
// #define followDepsEP_DEBUG

/*
 * Computing LL(k)-follow-sets
 */

namespace KDevPG
{

extern QTextStream checkOut;

#ifdef FOLLOWDEP_DEBUG
void DebugFollowDep(Model::Node *dest, Model::Node *dep, const QString &message)
{
  checkOut << "=============================" << Qt::endl;
  PrettyPrinter p(QTextStream( stderr ));
  checkOut << "adding " << message << " ";
  p(dep);
  checkOut << " (" << (uint*)dep << ")";
  checkOut << " to follow ";
  p(dest);
  checkOut << " (" << (uint*)dest << ")";
  checkOut << "{" << dest->kind << "}";
  if (dest->kind == Model::Node_kind_nonTerminal)
  {
    Model::SymbolItem *s = ((Model::NonTerminalItem*)dest)->mSymbol;
    if (s)
      checkOut << "__"; p(s); checkOut << "__";
  }
  checkOut << Qt::endl;
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
{
  Model::TerminalItem *teof = globalSystem.pushTerminal(QStringLiteral("EOF"), QStringLiteral("end of file"));
  for(auto i = globalSystem.rules.begin(); i != globalSystem.rules.end(); ++i)
  {
    if(globalSystem.start.contains((*i)->mSymbol))
    {
      globalSystem.follow(*i).insert(teof);
      globalSystem.follow((*i)->mSymbol).insert(teof);
      globalSystem.follow((*i)->mItem).insert(teof);
    }
  }
}

void NextFollow::operator()(Model::Node *node)
{
  Model::EvolveItem *e = nodeCast<Model::EvolveItem*>(node);
  Q_ASSERT(e != nullptr);
  mSymbol = e->mSymbol;
  visitNode(node);
}

void NextFollow::merge(Model::Node*__dest, World::NodeSet const &source)
{
  if (nodeCast<Model::ZeroItem*>(__dest) != nullptr
      || nodeCast<Model::TerminalItem*>(__dest) != nullptr)
    {
      return;
    }

  World::NodeSet &dest = globalSystem.follow(__dest);

  for (World::NodeSet::const_iterator it = source.begin(); it != source.end(); ++it)
    {
      if (Model::TerminalItem *t = nodeCast<Model::TerminalItem*>(*it))
      {
          if( !dest.contains(t) )
          {
            mChanged = true;
            dest.insert(t);
          }
      }
    }
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

void NextFollow::visitNode(Model::Node* node)
{
    if(node == nullptr)
      return;
  
    if(mVisited.contains(node))
      return;
    
    mVisited.insert(node);
    
    KDevPG::Visitor::visitNode(node);
    
    mVisited.remove(node);
}

void NextFollow::preCopy(Model::Node* from, Model::Node* to)
{
  if(from != nullptr && to != nullptr)
  {
    merge(from, globalSystem.follow(to));
    addFollowToFollowDep(from, to);
  }
}

void NextFollow::copy(Model::Node* from, Model::Node* to)
{
    Q_UNUSED(from);
    Q_UNUSED(to);
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
  NextFollow next(changed);
  while (true)
    {
      for(QList<Model::EvolveItem*>::iterator it = globalSystem.rules.begin(); it != globalSystem.rules.end(); ++it)
      {
        next(*it);
      }
      if(!changed) // for the eof in the first iteration
        break;
      changed = false;
    }
}

}

// kate: space-indent on; indent-width 2; tab-width 2; show-tabs on;
