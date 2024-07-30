/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEV_PG_DEFAULT_VISITOR_H
#define KDEV_PG_DEFAULT_VISITOR_H

#include "kdev-pg-visitor.h"

namespace KDevPG
{

#define visitNonTerminalIndirectly \
  visitNode(node->mSymbol);

#define visitNonTerminalDirectly \
  Model::EvolveItem *rule = globalSystem.searchRule(node->mSymbol); \
  visitNode(rule);

class DefaultVisitor: public Visitor
{
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
  void visitCondition(Model::ConditionItem *node) override;
  void visitVariableDeclaration(Model::VariableDeclarationItem *node) override;
  void visitOperator(Model::OperatorItem *node) override;
};

}

#endif // KDEV_PG_DEFAULT_VISITOR_H
