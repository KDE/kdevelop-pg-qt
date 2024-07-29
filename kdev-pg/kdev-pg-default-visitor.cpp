/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg-default-visitor.h"

#include "kdev-pg.h"

namespace KDevPG
{

void DefaultVisitor::visitZero(Model::ZeroItem *node)
{
  Q_UNUSED(node);
}

void DefaultVisitor::visitSymbol(Model::SymbolItem *node)
{
  Q_UNUSED(node);
}

void DefaultVisitor::visitTerminal(Model::TerminalItem *node)
{
  Q_UNUSED(node);
}

void DefaultVisitor::visitNonTerminal(Model::NonTerminalItem *node)
{
  visitNonTerminalIndirectly
}

void DefaultVisitor::visitInlinedNonTerminal(Model::InlinedNonTerminalItem* node)
{
  visitNonTerminalDirectly
}

void DefaultVisitor::visitPlus(Model::PlusItem *node)
{
  visitNode(node->mItem);
}

void DefaultVisitor::visitStar(Model::StarItem *node)
{
  visitNode(node->mItem);
}

void DefaultVisitor::visitAction(Model::ActionItem *node)
{
  visitNode(node->mItem);
}

void DefaultVisitor::visitAlternative(Model::AlternativeItem *node)
{
  visitNode(node->mLeft);
  visitNode(node->mRight);
}

void DefaultVisitor::visitCons(Model::ConsItem *node)
{
  visitNode(node->mLeft);
  visitNode(node->mRight);
}

void DefaultVisitor::visitEvolve(Model::EvolveItem *node)
{
  visitNode(node->mDeclarations);
  visitNode(node->mItem);
  visitNode(node->mSymbol);
}

void DefaultVisitor::visitTryCatch(Model::TryCatchItem *node)
{
  visitNode(node->mTryItem);
  visitNode(node->mCatchItem);
}

void DefaultVisitor::visitAlias(Model::AliasItem *node)
{
  visitNode(node->mSymbol);
}

void DefaultVisitor::visitAnnotation(Model::AnnotationItem *node)
{
  visitNode(node->mDeclaration);
  visitNode(node->mItem);
}

void DefaultVisitor::visitCondition(Model::ConditionItem *node)
{
  visitNode(node->mItem);
}

void DefaultVisitor::visitVariableDeclaration(Model::VariableDeclarationItem *node)
{
  visitNode(node->mNext);
}

void DefaultVisitor::visitOperator(Model::OperatorItem *node)
{
  Q_UNUSED(node);
}

}
