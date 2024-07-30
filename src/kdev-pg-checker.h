/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>
    SPDX-FileCopyrightText: 2006 Alexander Dymo <adymo@kdevelop.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEV_PG_CHECKER_H
#define KDEV_PG_CHECKER_H

#include "kdev-pg.h"
#include "kdev-pg-default-visitor.h"

/**
 * @file
 * Checks for conflicts and some errors.
 * TODO: split conflict-computation and conflict-message-printing
 */

namespace KDevPG
{

class EmptyFirstChecker: protected DefaultVisitor
{
public:
  void operator()(Model::Node *node);

protected:
  void visitNonTerminal(Model::NonTerminalItem *node) override;
  void visitInlinedNonTerminal(Model::InlinedNonTerminalItem *node) override;
  void visitSymbol(Model::SymbolItem *node) override;
};

class EmptyOperatorChecker: protected DefaultVisitor
{
public:
  void operator()(Model::Node *node);

protected:
  void visitOperator(Model::OperatorItem *node) override;
};

class FirstFirstConflictChecker: protected DefaultVisitor
{
public:
  void operator()(Model::Node *node);

protected:
  void check(Model::Node *left, Model::Node *right);

  void visitEvolve(Model::EvolveItem *node) override;
  void visitAlternative(Model::AlternativeItem *node) override;
  void visitInlinedNonTerminal(Model::InlinedNonTerminalItem *node) override;

private:
  Model::SymbolItem *mSymbol;
  Model::Node *mCheckedNode;
};

class FirstFollowConflictChecker: protected DefaultVisitor
{
public:
  void operator()(Model::Node *node);

protected:
  void check(Model::Node *node, Model::Node *sym = nullptr);

  void visitAlternative(Model::AlternativeItem *node) override;
  void visitCons(Model::ConsItem *node) override;
  void visitPlus(Model::PlusItem *node) override;
  void visitStar(Model::StarItem *node) override;
  void visitInlinedNonTerminal(Model::InlinedNonTerminalItem *node) override;

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
  void visitSymbol(Model::SymbolItem *node) override;
  void visitVariableDeclaration(Model::VariableDeclarationItem *node) override;
  void visitInlinedNonTerminal(Model::InlinedNonTerminalItem *node) override;

private:
  Model::SymbolItem *mSymbol;
};

class UndefinedTokenChecker: protected DefaultVisitor
{
public:
  void operator()(Model::Node *node);

protected:
  void visitTerminal(Model::TerminalItem *node) override;
  void visitInlinedNonTerminal(Model::InlinedNonTerminalItem *node) override;

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
