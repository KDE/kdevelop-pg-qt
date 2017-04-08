
/* This file is part of kdev-pg-qt
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
