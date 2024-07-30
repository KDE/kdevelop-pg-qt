/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEV_PG_CLONE_TREE_H
#define KDEV_PG_CLONE_TREE_H

#include "kdev-pg-default-visitor.h"
#include <QStack>

namespace KDevPG
{

class CloneTree: public DefaultVisitor
{
public:
  QStack<Model::Node*> mTemps;

public:
  Model::Node *clone(Model::Node *node);

protected:
  void visitZero(Model::ZeroItem *node) override;
  void visitSymbol(Model::SymbolItem *node) override;
  void visitTerminal(Model::TerminalItem *node) override;
  void visitNonTerminal(Model::NonTerminalItem *node) override;
  void visitInlinedNonTerminal(Model::InlinedNonTerminalItem *node) override;
  void visitPlus(Model::PlusItem *node) override;
  void visitStar(Model::StarItem *node) override;
  void visitAction(Model::ActionItem *node) override;
  void visitAlternative(Model::AlternativeItem *node) override;
  void visitCons(Model::ConsItem *node) override;
  void visitEvolve(Model::EvolveItem *node) override;
  void visitTryCatch(Model::TryCatchItem *node) override;
  void visitAlias(Model::AliasItem *node) override;
  void visitAnnotation(Model::AnnotationItem *node) override;
  void visitOperator(Model::OperatorItem *node) override;
};

}

#endif // KDEV_PG_CLONE_TREE_H
