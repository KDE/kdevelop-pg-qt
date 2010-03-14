/* This file is part of kdev-pg
   Copyright (C) 2005 Roberto Raggi <roberto@kdevelop.org>
   Copyright (C) 2006 Jakob Petsovits <jpetso@gmx.at>

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

#include "kdev-pg-default-visitor.h"

namespace KDevPG
{

void DefaultVisitor::visitZero(Model::ZeroItem *node)
{}

void DefaultVisitor::visitSymbol(Model::SymbolItem *node)
{}

void DefaultVisitor::visitTerminal(Model::TerminalItem *node)
{}

void DefaultVisitor::visitNonTerminal(Model::NonTerminalItem *node)
{
  visitNode(node->mSymbol);
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
  
}

}
