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

#ifndef KDEV_PG_CHECKER_H
#define KDEV_PG_CHECKER_H

#include "kdev-pg.h"
#include "kdev-pg-default-visitor.h"

namespace KDevPG
{

class EmptyFirstChecker: protected DefaultVisitor
{
public:
  void operator()(Model::Node *node);

protected:
  virtual void visitNonTerminal(Model::NonTerminalItem *node);
  virtual void visitInlinedNonTerminal(Model::InlinedNonTerminalItem *node);
  virtual void visitSymbol(Model::SymbolItem *node);
};

class EmptyOperatorChecker: protected DefaultVisitor
{
public:
  void operator()(Model::Node *node);

protected:
  virtual void visitOperator(Model::OperatorItem *node);
};

class FirstFirstConflictChecker: protected DefaultVisitor
{
public:
  void operator()(Model::Node *node);

protected:
  void check(Model::Node *left, Model::Node *right);

  virtual void visitEvolve(Model::EvolveItem *node);
  virtual void visitAlternative(Model::AlternativeItem *node);
  virtual void visitInlinedNonTerminal(Model::InlinedNonTerminalItem *node);

private:
  Model::SymbolItem *mSymbol;
  Model::Node *mCheckedNode;
};

class FirstFollowConflictChecker: protected DefaultVisitor
{
public:
  void operator()(Model::Node *node);

protected:
  void check(Model::Node *node, Model::Node *sym = 0);

  virtual void visitAlternative(Model::AlternativeItem *node);
  virtual void visitCons(Model::ConsItem *node);
  virtual void visitPlus(Model::PlusItem *node);
  virtual void visitStar(Model::StarItem *node);
  virtual void visitInlinedNonTerminal(Model::InlinedNonTerminalItem *node);

private:
  Model::SymbolItem *mSymbol;
};

class FollowDepChecker
{
public:
  FollowDepChecker(Model::Node *terminal): mTerminal(terminal) {}
  void check(Model::Node *n);

private:
  Model::Node *mTerminal;
  World::NodeSet mVisited;
};

class UndefinedSymbolChecker: protected DefaultVisitor
{
public:
  void operator()(Model::Node *node);

protected:
  virtual void visitSymbol(Model::SymbolItem *node);
  virtual void visitVariableDeclaration(Model::VariableDeclarationItem *node);
  virtual void visitInlinedNonTerminal(Model::InlinedNonTerminalItem *node);

private:
  Model::SymbolItem *mSymbol;
};

class UndefinedTokenChecker: protected DefaultVisitor
{
public:
  void operator()(Model::Node *node);

protected:
  virtual void visitTerminal(Model::TerminalItem *node);
  virtual void visitInlinedNonTerminal(Model::InlinedNonTerminalItem *node);

private:
  Model::SymbolItem *mSymbol;
};

class ProblemSummaryPrinter
{
public:
  void operator()();

  static void reportFirstFirstConflict();
  static void reportFirstFollowConflict();
  static void reportError();

private:
  static int mFirstFirstConflictCount;
  static int mFirstFollowConflictCount;
  static int mErrorCount;
};

}

#endif // KDEV_PG_CHECKER_H

// kate: space-indent on; indent-width 2; tab-width 2; show-tabs on;
