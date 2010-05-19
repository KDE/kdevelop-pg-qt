/* This file is part of kdev-pg
   Copyright (C) 2005 Roberto Raggi <roberto@kdevelop.org>

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

#ifndef KDEV_PG_FIRST_H
#define KDEV_PG_FIRST_H

#include "kdev-pg.h"
#include "kdev-pg-default-visitor.h"

namespace KDevPG
{

/**
 * Adds first-sets for terminals, zeros and operators.
 */
class InitializeFirst: protected DefaultVisitor
{
public:
  void operator ()(Model::Node *node);

protected:
  /**
   * Stops endless recursion.
   */
  virtual void visitNode(Model::Node *node);
  /**
   * Add node to the first-set of node.
   */
  virtual void visitZero(Model::ZeroItem *node);
  /**
   * The same as visitZero.
   */
  virtual void visitTerminal(Model::TerminalItem *node);
  /**
   * Initialize the required terminals.
   */
  virtual void visitOperator(Model::OperatorItem *node);
};

/**
 * Recursively merge first-sets.
 */
class NextFirst: protected DefaultVisitor
{
public:
  NextFirst(bool &changed);

  void operator ()(Model::Node *node);

protected:
  bool blockMerge(bool block);
  bool blockZeroMerge(bool block);
  void merge(Model::Node *__dest, Model::Node *__source, int K = 1);

  virtual void visitNode(Model::Node *node);
  virtual void visitZero(Model::ZeroItem *node);
  virtual void visitTerminal(Model::TerminalItem *node);
  virtual void visitNonTerminal(Model::NonTerminalItem *node);
  virtual void visitSymbol(Model::SymbolItem *node);
  virtual void visitPlus(Model::PlusItem *node);
  virtual void visitStar(Model::StarItem *node);
  virtual void visitAction(Model::ActionItem *node);
  virtual void visitAlternative(Model::AlternativeItem *node);
  virtual void visitCons(Model::ConsItem *node);
  virtual void visitEvolve(Model::EvolveItem *node);
  virtual void visitTryCatch(Model::TryCatchItem *node);
  virtual void visitAlias(Model::AliasItem *node);
  virtual void visitAnnotation(Model::AnnotationItem *node);
  virtual void visitCondition(Model::ConditionItem *node);
  virtual void visitOperator(Model::OperatorItem *node);

private:
  Model::Node *mItem;
  bool mMergeBlocked;
  bool mMergeZeroBlocked;
  bool &mChanged;
};

/**
 * This method computes the first-set for all symbols.
 * The algorithm: The function starts with InitializeFirst. As long as possible NextFirst will merge first-sets.
 */
void computeFirst();

}

#endif // KDEV_PG_FIRST_H
