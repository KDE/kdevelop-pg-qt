/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg-visitor.h"

namespace KDevPG
{

Visitor::VisitorFuncPointer Visitor::sTable[Model::NodeKindLast] = {
  nullptr,
  reinterpret_cast<Visitor::VisitorFuncPointer>(&Visitor::visitZero),
  reinterpret_cast<Visitor::VisitorFuncPointer>(&Visitor::visitPlus),
  reinterpret_cast<Visitor::VisitorFuncPointer>(&Visitor::visitStar),
  reinterpret_cast<Visitor::VisitorFuncPointer>(&Visitor::visitSymbol),
  reinterpret_cast<Visitor::VisitorFuncPointer>(&Visitor::visitAction),
  reinterpret_cast<Visitor::VisitorFuncPointer>(&Visitor::visitAlternative),
  reinterpret_cast<Visitor::VisitorFuncPointer>(&Visitor::visitCons),
  reinterpret_cast<Visitor::VisitorFuncPointer>(&Visitor::visitEvolve),
  reinterpret_cast<Visitor::VisitorFuncPointer>(&Visitor::visitTryCatch),
  reinterpret_cast<Visitor::VisitorFuncPointer>(&Visitor::visitAlias),
  reinterpret_cast<Visitor::VisitorFuncPointer>(&Visitor::visitTerminal),
  reinterpret_cast<Visitor::VisitorFuncPointer>(&Visitor::visitNonTerminal),
  reinterpret_cast<Visitor::VisitorFuncPointer>(&Visitor::visitAnnotation),
  reinterpret_cast<Visitor::VisitorFuncPointer>(&Visitor::visitCondition),
  reinterpret_cast<Visitor::VisitorFuncPointer>(&Visitor::visitVariableDeclaration),
  reinterpret_cast<Visitor::VisitorFuncPointer>(&Visitor::visitOperator),
  reinterpret_cast<Visitor::VisitorFuncPointer>(&Visitor::visitInlinedNonTerminal),
};

}
