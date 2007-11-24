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

#ifndef KDEV_PG_DEFAULT_VISITOR_H
#define KDEV_PG_DEFAULT_VISITOR_H

#include "kdev-pg-visitor.h"

namespace KDevPG
{

class DefaultVisitor: public Visitor
{
protected:
  virtual void visitZero(Model::ZeroItem *node);
  virtual void visitSymbol(Model::SymbolItem *node);
  virtual void visitTerminal(Model::TerminalItem *node);
  virtual void visitNonTerminal(Model::NonTerminalItem *node);
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
  virtual void visitVariableDeclaration(Model::VariableDeclarationItem *node);
};

}

#endif // KDEV_PG_DEFAULT_VISITOR_H
