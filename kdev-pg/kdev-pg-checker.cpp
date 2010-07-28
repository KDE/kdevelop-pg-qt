/* This file is part of kdev-pg-qt
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

#include <QtCore/QDebug>

//uncomment this to see debug output for follow checker
// #define FOLLOW_CHECKER_DEBUG

namespace KDevPG
{
  
QTextStream checkOut(stderr);

int ProblemSummaryPrinter::mFirstFirstConflictCount = 0;
int ProblemSummaryPrinter::mFirstFollowConflictCount = 0;
int ProblemSummaryPrinter::mErrorCount = 0;

void FirstFirstConflictChecker::operator()(Model::Node *node)
{
  Model::EvolveItem *e = nodeCast<Model::EvolveItem*>(node);
  Q_ASSERT(e != 0);
  mSymbol = e->mSymbol;
  visitNode(node);
}

void FirstFirstConflictChecker::visitAlternative(Model::AlternativeItem *node)
{
  DefaultVisitor::visitAlternative(node);

  mCheckedNode = node;
  check(node->mLeft, node->mRight);
}

void FirstFirstConflictChecker::visitInlinedNonTerminal(Model::InlinedNonTerminalItem* node)
{
    Q_UNUSED(node);
}

void FirstFirstConflictChecker::check(Model::Node *left, Model::Node *right)
{
  World::NodeSet const &left_first = globalSystem.first(left);
  World::NodeSet const &right_first = globalSystem.first(right);

  QSet<Model::Node*> U = left_first;
  U.intersect( right_first );

  if (!U.empty())
    {
      QTextStream& str( checkOut );
      PrettyPrinter printer(str);
      str << "** WARNING found FIRST/FIRST conflict in "
                << mSymbol->mName << ":" << endl << "\tRule ``";
      printer(mCheckedNode);
      //      p(left);
      str << "''" << endl << "\tTerminals [" << endl;

      QSet<Model::Node*>::iterator it = U.begin();
      while (it != U.end())
        {
          Model::Node *n = *it++;

          str << "\t\t" << n;
          if (it != U.end())
            str << ", ";
          str << endl;
        }
      str << "\t]" << endl << endl;
      ProblemSummaryPrinter::reportFirstFirstConflict();
    }
}

void FirstFirstConflictChecker::visitEvolve(Model::EvolveItem *node)
{
  DefaultVisitor::visitEvolve(node);

  World::Environment::iterator it = globalSystem.env.find(node->mSymbol);
  while (it != globalSystem.env.end())
    {
      Model::SymbolItem *sym = it.key();
      Model::EvolveItem *e = (*it);
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
  Q_ASSERT(e != 0);
  mSymbol = e->mSymbol;
  visitNode(node);
}

void FirstFollowConflictChecker::check(Model::Node *node, Model::Node *sym)
{
  if (!sym)
    sym = node;

  World::NodeSet const &first = globalSystem.first(node);
  World::NodeSet const &follow = globalSystem.follow(sym);

  QSet<Model::Node*> U = first;

  U.intersect(follow);

  if (!U.empty())
    {
      QTextStream& str( checkOut );
      PrettyPrinter p(str);
      str << "** WARNING found FIRST/FOLLOW conflict in "
                << mSymbol->mName;
#ifdef FOLLOW_CHECKER_DEBUG
      str << "(" << (uint*)mSymbol << ")";
#endif
      str << ":" << endl << "\tRule ``";
      p(node);
#ifdef FOLLOW_CHECKER_DEBUG
      str << " [[" << (uint*)node << "]]";
#endif
      str << "''" << endl << "\tTerminals [" << endl;

      QSet<Model::Node*>::iterator it = U.begin();
      while (it != U.end())
        {
          Model::Node *n = *it++;
          if (isZero(n))
            continue;

          str << "\t\t" << ((Model::TerminalItem*)n)->mName << ": conflicts with the FIRST set of: " << endl;
          FollowDepChecker(n).check(node);
          if (it != U.end())
            str << ",";
          str << endl;
        }
      str << "\t]" << endl << endl;
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
  QTextStream& str( checkOut );
  PrettyPrinter p(str);
#ifdef FOLLOW_CHECKER_DEBUG
  str << "[["; p(node); str << " | " << (uint*)node << "]] ";
  str << "{" << node->kind << "}" << endl;
#endif
  for (World::NodeSet::const_iterator it = FD.begin(); it != FD.end(); ++it)
    {
      World::NodeSet first = globalSystem.first(*it);
#ifdef FOLLOW_CHECKER_DEBUG
      str << " <iterating first ";
      for (World::NodeSet::const_iterator fit = first.begin(); fit != first.end(); ++fit)
      {
        p(*fit);
        str << " ";
      }
      str << ">";
#endif
      if (first.find(mTerminal) != first.end())
      {
        str << "\t\t";
        p(*it);
#ifdef FOLLOW_CHECKER_DEBUG
        str << " ( in \"";
        p(node);
        str << " \" )";
#endif
        str << ", " << endl;
      }
    }
 for (World::NodeSet::const_iterator it = FLD.begin(); it != FLD.end(); ++it)
  {
      World::NodeSet first = globalSystem.first(*it);
#ifdef FOLLOW_CHECKER_DEBUG
      str << endl << "\t\t" << "in ";
      p(*it);
      str << endl;
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

void FirstFollowConflictChecker::visitInlinedNonTerminal(Model::InlinedNonTerminalItem* node)
{
    Q_UNUSED(node);
}

void UndefinedSymbolChecker::visitInlinedNonTerminal(Model::InlinedNonTerminalItem* node)
{
    if(node->mSymbol)
        visitSymbol(node->mSymbol);
}

void UndefinedSymbolChecker::operator()(Model::Node *node)
{
  Model::EvolveItem *e = nodeCast<Model::EvolveItem*>(node);
  Q_ASSERT(e != 0);
  mSymbol = e->mSymbol;
  visitNode(node);
}

void UndefinedSymbolChecker::visitSymbol(Model::SymbolItem *node)
{
  if (globalSystem.env.count(node) == 0)
    {
      checkOut << "** ERROR Undefined symbol ``" << node->mName << "'' in "
                << mSymbol->mName << endl;
      ProblemSummaryPrinter::reportError();
    }
}

void UndefinedSymbolChecker::visitVariableDeclaration(Model::VariableDeclarationItem *node)
{
  if (node->mVariableType != Model::VariableDeclarationItem::TypeNode)
    return;

  Model::SymbolItem *sym;

  QString name = node->mType;
  World::SymbolSet::iterator it = globalSystem.symbols.find(name);
  if (it == globalSystem.symbols.end())
    {
      checkOut << "** ERROR Undefined symbol ``" << name
                << "'' (rule parameter declaration) in "
                << mSymbol->mName << endl;
      ProblemSummaryPrinter::reportError();
      return;
    }
  else
    sym = (*it);

  if (globalSystem.env.count(sym) == 0)
    {
      checkOut << "** ERROR Undefined symbol ``" << node->mName
                << "'' (rule parameter declaration) in "
                << mSymbol->mName << endl;
      ProblemSummaryPrinter::reportError();
    }
}

void UndefinedTokenChecker::visitInlinedNonTerminal(Model::InlinedNonTerminalItem* node)
{
    Q_UNUSED(node);
}

void UndefinedTokenChecker::operator()(Model::Node *node)
{
  Model::EvolveItem *e = nodeCast<Model::EvolveItem*>(node);
  Q_ASSERT(e != 0);
  mSymbol = e->mSymbol;
  visitNode(node);
}

void UndefinedTokenChecker::visitTerminal(Model::TerminalItem *node)
{
  QString name = node->mName;
  if (globalSystem.terminals.find(name) == globalSystem.terminals.end())
    {
      checkOut << "** ERROR Undefined token ``" << node->mName << "'' in "
                << mSymbol->mName << endl;
      ProblemSummaryPrinter::reportError();
    }
}

void EmptyFirstChecker::operator()(Model::Node *node)
{
  visitNode(node);
}

void EmptyFirstChecker::visitNonTerminal(Model::NonTerminalItem *node)
{
  Q_UNUSED(node);
}

void EmptyFirstChecker::visitInlinedNonTerminal(Model::InlinedNonTerminalItem *node)
{
  Q_UNUSED(node);
}

void EmptyFirstChecker::visitSymbol(Model::SymbolItem *node)
{
  if (globalSystem.first(node).empty())
  {
    checkOut << "** ERROR Empty FIRST set for ``" << node->mName
              << "''" << endl;
    ProblemSummaryPrinter::reportError();
  }
}

void EmptyOperatorChecker::operator()(Model::Node *node)
{
  visitNode(node);
}

void EmptyOperatorChecker::visitOperator(Model::OperatorItem *node)
{
  if (reducesToEpsilon((node->mBase->mSymbol)))
  {
    checkOut << "** ERROR Base symbol ``" << node->mBase->mSymbol->mName << "'' for operator ``" << node->mName << "'' reduces to zero" << endl;
    ProblemSummaryPrinter::reportError();
  }
}

void ProblemSummaryPrinter::operator()()
{
  if (KDevPG::globalSystem.conflictHandling != KDevPG::World::Ignore)
    checkOut << (mFirstFirstConflictCount + mFirstFollowConflictCount)
              << " conflicts total: " << mFirstFollowConflictCount
              << " FIRST/FOLLOW conflicts, " << mFirstFirstConflictCount
              << " FIRST/FIRST conflicts." << endl;

  if (mErrorCount > 0)
    {
      checkOut << mErrorCount << " fatal errors found, exiting."
                << endl;
      exit(EXIT_FAILURE);
    }
    
  if (KDevPG::globalSystem.conflictHandling == KDevPG::World::Strict && mFirstFirstConflictCount + mFirstFollowConflictCount > 0)
    {
      checkOut << "Conflicts found, exiting."
                << endl;
      exit(EXIT_FAILURE);
    }
}

void ProblemSummaryPrinter::reportFirstFirstConflict()
{
  ++mFirstFirstConflictCount;
}

void ProblemSummaryPrinter::reportFirstFollowConflict()
{
  ++mFirstFollowConflictCount;
}

void ProblemSummaryPrinter::reportError()
{
  ++mErrorCount;
}

}

// kate: space-indent on; indent-width 2; tab-width 2; show-tabs on;
