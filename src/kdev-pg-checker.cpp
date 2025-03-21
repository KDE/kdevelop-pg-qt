/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>
    SPDX-FileCopyrightText: 2006 Alexander Dymo <adymo@kdevelop.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg-checker.h"
#include "kdev-pg-pretty-printer.h"
#include "kdev-pg-bnf-visitor.h"

#include <QDebug>

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
  Q_ASSERT(e != nullptr);
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
                << mSymbol->mName << ":" << Qt::endl << "\tRule ``";
      printer(mCheckedNode);
      //      p(left);
      str << "''" << Qt::endl << "\tTerminals [" << Qt::endl;

      QSet<Model::Node*>::iterator it = U.begin();
      while (it != U.end())
        {
          Model::Node *n = *it++;

          str << "\t\t" << n;
          if (it != U.end())
            str << ", ";
          str << Qt::endl;
        }
      str << "\t]" << Qt::endl << Qt::endl;
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
  Q_ASSERT(e != nullptr);
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
      str << ":" << Qt::endl << "\tRule ``";
      p(node);
#ifdef FOLLOW_CHECKER_DEBUG
      str << " [[" << (uint*)node << "]]";
#endif
      str << "''" << Qt::endl << "\tTerminals [" << Qt::endl;

      QSet<Model::Node*>::iterator it = U.begin();
      while (it != U.end())
        {
          Model::Node *n = *it++;
          if (isZero(n))
            continue;

          str << "\t\t" << ((Model::TerminalItem*)n)->mName << ": conflicts with the FIRST set of: " << Qt::endl;
          FollowDepChecker(n).check(node);
          if (it != U.end())
            str << "," << Qt::endl;
        }
      str << "\t]" << Qt::endl << Qt::endl;
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
  QList<Model::Node*> FD = D.first.values();
  QList<Model::Node*> FLD = D.second.values();
  QTextStream& str( checkOut );
  PrettyPrinter p(str);
#ifdef FOLLOW_CHECKER_DEBUG
  str << "[["; p(node); str << " | " << (uint*)node << "]] ";
  str << "{" << node->kind << "}" << Qt::endl;
#endif
  for (int i = 0; i != FD.size(); ++i) // no iterator → modifiable
    {
      if(BnfVisitor::isInternal(FD[i]))
      {
        World::NodeSet set = globalSystem.followDep(FD[i]).second;
        World::NodeSet set2 = globalSystem.followDep(FD[i]).first; // :-S has to be verified…
        for(auto jt = FD.begin(); jt != FD.end(); ++jt)
        {
          set.remove(*jt);
          set2.remove(*jt);
        }
        for(auto jt = set2.begin(); jt != set2.end(); ++jt)
          if(!BnfVisitor::isInternal(*jt))
            FD.append(*jt);
        FD.append(set.values());
      }
      else
      {
        World::NodeSet first = globalSystem.first(FD[i]);
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
          p(FD[i]);
  #ifdef FOLLOW_CHECKER_DEBUG
          str << " ( in \"";
          p(node);
          str << " \" )";
  #endif
          str << ", " << Qt::endl;
        }
      }
    }
 for (int i = 0; i != FLD.size(); ++i)
  {
    if(BnfVisitor::isInternal(FLD[i]))
    {
      World::NodeSet set = globalSystem.followDep(FLD[i]).second;
      for(auto jt = FLD.begin(); jt != FLD.end(); ++jt)
        set.remove(*jt);
      FLD.append(set.values());
    }
    else
    {
      World::NodeSet first = globalSystem.first(FLD[i]);
#ifdef FOLLOW_CHECKER_DEBUG
      str << Qt::endl << "\t\t" << "in ";
      p(FLD[i]);
      str << Qt::endl;
#endif
      check(FLD[i]);
    }
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
  Q_ASSERT(e != nullptr);
  mSymbol = e->mSymbol;
  visitNode(node);
}

void UndefinedSymbolChecker::visitSymbol(Model::SymbolItem *node)
{
  if (globalSystem.env.count(node) == 0)
    {
      checkOut << "** ERROR Undefined symbol ``" << node->mName << "'' in "
                << mSymbol->mName << Qt::endl;
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
                << mSymbol->mName << Qt::endl;
      ProblemSummaryPrinter::reportError();
      return;
    }
  else
    sym = (*it);

  if (globalSystem.env.count(sym) == 0)
    {
      checkOut << "** ERROR Undefined symbol ``" << node->mName
                << "'' (rule parameter declaration) in "
                << mSymbol->mName << Qt::endl;
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
  Q_ASSERT(e != nullptr);
  mSymbol = e->mSymbol;
  visitNode(node);
}

void UndefinedTokenChecker::visitTerminal(Model::TerminalItem *node)
{
  QString name = node->mName;
  if (globalSystem.terminals.find(name) == globalSystem.terminals.end())
    {
      checkOut << "** ERROR Undefined token ``" << node->mName << "'' in "
                << mSymbol->mName << Qt::endl;
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
              << "''" << Qt::endl;
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
    checkOut << "** ERROR Base symbol ``" << node->mBase->mSymbol->mName << "'' for operator ``" << node->mName << "'' reduces to zero" << Qt::endl;
    ProblemSummaryPrinter::reportError();
  }
}

void ProblemSummaryPrinter::operator()()
{
  if (KDevPG::globalSystem.conflictHandling != KDevPG::World::Ignore)
    checkOut << (mFirstFirstConflictCount + mFirstFollowConflictCount)
              << " conflicts total: " << mFirstFollowConflictCount
              << " FIRST/FOLLOW conflicts, " << mFirstFirstConflictCount
              << " FIRST/FIRST conflicts." << Qt::endl;

  if (mErrorCount > 0)
    {
      checkOut << mErrorCount << " fatal errors found, exiting."
                << Qt::endl;
      exit(EXIT_FAILURE);
    }
    
  if (KDevPG::globalSystem.conflictHandling == KDevPG::World::Strict && mFirstFirstConflictCount + mFirstFollowConflictCount > 0)
    {
      checkOut << "Conflicts found, exiting."
                << Qt::endl;
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
