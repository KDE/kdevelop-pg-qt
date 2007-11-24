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

#include "kdev-pg-checker.h"
#include "kdev-pg-pretty-printer.h"

#include <iostream>
#include <iterator>
#include <algorithm>

//uncomment this to see debug output for follow checker
// #define FOLLOW_CHECKER_DEBUG

namespace KDevPG
{

int ProblemSummaryPrinter::mFirstFirstConflictCount = 0;
int ProblemSummaryPrinter::mFirstFollowConflictCount = 0;
int ProblemSummaryPrinter::mErrorCount = 0;

void FirstFirstConflictChecker::operator()(Model::Node *node)
{
  Model::EvolveItem *e = nodeCast<Model::EvolveItem*>(node);
  assert(e != 0);
  mSymbol = e->mSymbol;
  visitNode(node);
}

void FirstFirstConflictChecker::visitAlternative(Model::AlternativeItem *node)
{
  DefaultVisitor::visitAlternative(node);

  mCheckedNode = node;
  check(node->mLeft, node->mRight);
}

void FirstFirstConflictChecker::check(Model::Node *left, Model::Node *right)
{
  World::NodeSet const &left_first = globalSystem.first(left);
  World::NodeSet const &right_first = globalSystem.first(right);

  std::deque<Model::Node*> U;
  std::set_intersection(left_first.begin(), left_first.end(),
                        right_first.begin(), right_first.end(), std::back_inserter(U));

  if (!U.empty())
    {
      PrettyPrinter p(std::cerr);
      std::cerr << "** WARNING found FIRST/FIRST conflict in "
                << mSymbol->mName << ":" << std::endl << "\tRule ``";
      p(mCheckedNode);
      //      p(left);
      std::cerr << "''" << std::endl << "\tTerminals [";

      std::deque<Model::Node*>::iterator it = U.begin();
      while (it != U.end())
        {
          Model::Node *n = *it++;

          std::cerr << n;
          if (it != U.end())
            std::cerr << ", ";
        }
      std::cerr << "]" << std::endl << std::endl;
      ProblemSummaryPrinter::reportFirstFirstConflict();
    }
}

void FirstFirstConflictChecker::visitEvolve(Model::EvolveItem *node)
{
  DefaultVisitor::visitEvolve(node);

  World::Environment::iterator it = globalSystem.env.find(node->mSymbol);
  while (it != globalSystem.env.end())
    {
      Model::SymbolItem *sym = (*it).first;
      Model::EvolveItem *e = (*it).second;
      ++it;

      if (sym != node->mSymbol || node == e)
        continue;

      mCheckedNode = node;
      check(e, node);
    }
}

void FirstFollowConflictChecker::operator()(Model::Node *node)
{
  Model::EvolveItem *e = nodeCast<Model::EvolveItem*>(node);
  assert(e != 0);
  mSymbol = e->mSymbol;
  visitNode(node);
}

void FirstFollowConflictChecker::check(Model::Node *node, Model::Node *sym)
{
  if (!sym)
    sym = node;

  World::NodeSet const &first = globalSystem.first(node);
  World::NodeSet const &follow = globalSystem.follow(sym);

  std::deque<Model::Node*> U;

  std::set_intersection(first.begin(), first.end(),
                        follow.begin(), follow.end(),
                        std::back_inserter(U));

  if (!U.empty())
    {
      PrettyPrinter p(std::cerr);
      std::cerr << "** WARNING found FIRST/FOLLOW conflict in "
                << mSymbol->mName;
#ifdef FOLLOW_CHECKER_DEBUG
      std::cerr << "(" << (uint*)mSymbol << ")";
#endif
      std::cerr << ":" << std::endl << "\tRule ``";
      p(node);
#ifdef FOLLOW_CHECKER_DEBUG
      std::cerr << " [[" << (uint*)node << "]]";
#endif
      std::cerr << "''" << std::endl << "\tTerminals [" << std::endl;

      std::deque<Model::Node*>::iterator it = U.begin();
      while (it != U.end())
        {
          Model::Node *n = *it++;
          if (isZero(n))
            continue;

          std::cerr << "\t" << n << ": conflicts with the FIRST set of: ";
          FollowDepChecker(n).check(node);
          if (it != U.end())
            std::cerr << ", ";
          std::cerr << std::endl;
        }
      std::cerr << "\t" << "]" << std::endl << std::endl;
      ProblemSummaryPrinter::reportFirstFollowConflict();
    }
}

void FollowDepChecker::check(Model::Node *node)
{
  //avoid cyclical follow dependency check
  if (mVisited.find(node) != mVisited.end())
    return;
  mVisited.insert(node);

  World::FollowDep &D = globalSystem.followDep(node);
  World::NodeSet FD = D.first;
  World::NodeSet FLD = D.second;
  PrettyPrinter p(std::cerr);
#ifdef FOLLOW_CHECKER_DEBUG
  std::cerr << "[["; p(node); std::cerr << " | " << (uint*)node << "]] ";
  std::cerr << "{" << node->kind << "}";
#endif
  for (World::NodeSet::const_iterator it = FD.begin(); it != FD.end(); ++it)
    {
      World::NodeSet first = globalSystem.first(*it);
#ifdef FOLLOW_CHECKER_DEBUG
      std::cerr << " <iterating first ";
      for (World::NodeSet::const_iterator fit = first.begin(); fit != first.end(); ++fit)
      {
        p(*fit);
        std::cerr << " ";
      }
      std::cerr << " >";
#endif
      if (first.find(mTerminal) != first.end())
      {
        std::cerr << std::endl << "            ";
        p(*it);
#ifdef FOLLOW_CHECKER_DEBUG
        std::cerr << " ( in \"";
        p(node);
        std::cerr << " \" )";
#endif
        std::cerr << ", ";
      }
    }
 for (World::NodeSet::const_iterator it = FLD.begin(); it != FLD.end(); ++it)
  {
      World::NodeSet first = globalSystem.first(*it);
#ifdef FOLLOW_CHECKER_DEBUG
      std::cerr << std::endl << "\t\t" << "in ";
      p(*it);
      std::cerr << std::endl;
#endif
      check(*it);
  }
}

void FirstFollowConflictChecker::visitAlternative(Model::AlternativeItem *node)
{
  DefaultVisitor::visitAlternative(node);

  if (isZero(node->mRight))
    return;

  if (reducesToEpsilon(node))
    check(node);
}

void FirstFollowConflictChecker::visitCons(Model::ConsItem *node)
{
  DefaultVisitor::visitCons(node);

  if (reducesToEpsilon(node))
    check(node);
}

void FirstFollowConflictChecker::visitPlus(Model::PlusItem *node)
{
  DefaultVisitor::visitPlus(node);

  if (reducesToEpsilon(node))
    check(node);
}

void FirstFollowConflictChecker::visitStar(Model::StarItem *node)
{
  DefaultVisitor::visitStar(node);

  check(node);
}

void UndefinedSymbolChecker::operator()(Model::Node *node)
{
  Model::EvolveItem *e = nodeCast<Model::EvolveItem*>(node);
  assert(e != 0);
  mSymbol = e->mSymbol;
  visitNode(node);
}

void UndefinedSymbolChecker::visitSymbol(Model::SymbolItem *node)
{
  if (globalSystem.env.count(node) == 0)
    {
      std::cerr << "** ERROR Undefined symbol ``" << node->mName << "'' in "
                << mSymbol->mName << std::endl;
      ProblemSummaryPrinter::reportError();
    }
}

void UndefinedSymbolChecker::visitVariableDeclaration(Model::VariableDeclarationItem *node)
{
  if (node->mVariableType != Model::VariableDeclarationItem::TypeNode)
    return;

  Model::SymbolItem *sym;

  std::string name = node->mType;
  World::SymbolSet::iterator it = globalSystem.symbols.find(name);
  if (it == globalSystem.symbols.end())
    {
      std::cerr << "** ERROR Undefined symbol ``" << name
                << "'' (rule parameter declaration) in "
                << mSymbol->mName << std::endl;
      ProblemSummaryPrinter::reportError();
      return;
    }
  else
    sym = (*it).second;

  if (globalSystem.env.count(sym) == 0)
    {
      std::cerr << "** ERROR Undefined symbol ``" << node->mName
                << "'' (rule parameter declaration) in "
                << mSymbol->mName << std::endl;
      ProblemSummaryPrinter::reportError();
    }
}

void UndefinedTokenChecker::operator()(Model::Node *node)
{
  Model::EvolveItem *e = nodeCast<Model::EvolveItem*>(node);
  assert(e != 0);
  mSymbol = e->mSymbol;
  visitNode(node);
}

void UndefinedTokenChecker::visitTerminal(Model::TerminalItem *node)
{
  std::string name = node->mName;
  if (globalSystem.terminals.find(name) == globalSystem.terminals.end())
    {
      std::cerr << "** ERROR Undefined token ``" << node->mName << "'' in "
                << mSymbol->mName << std::endl;
      ProblemSummaryPrinter::reportError();
    }
}

void EmptyFirstChecker::operator()(Model::Node *node)
{
  visitNode(node);
}

void EmptyFirstChecker::visitSymbol(Model::SymbolItem *node)
{
  if (globalSystem.first(node).empty())
    {
      std::cerr << "** ERROR Empty FIRST set for ``" << node->mName
                << "''" << std::endl;
      ProblemSummaryPrinter::reportError();
    }
}

void ProblemSummaryPrinter::operator()()
{
  std::cerr << (mFirstFirstConflictCount + mFirstFollowConflictCount)
            << " conflicts total: " << mFirstFollowConflictCount
            << " FIRST/FOLLOW conflicts, " << mFirstFirstConflictCount
            << " FIRST/FIRST conflicts." << std::endl;

  if (mErrorCount > 0)
    {
      std::cerr << mErrorCount << " fatal errors found, exiting."
                << std::endl;
      exit(EXIT_FAILURE);
    }
}

void ProblemSummaryPrinter::reportFirstFirstConflict()
{
  mFirstFirstConflictCount++;
}

void ProblemSummaryPrinter::reportFirstFollowConflict()
{
  mFirstFollowConflictCount++;
}

void ProblemSummaryPrinter::reportError()
{
  mErrorCount++;
}

}

// kate: space-indent on; indent-width 2; tab-width 2; show-tabs on;
