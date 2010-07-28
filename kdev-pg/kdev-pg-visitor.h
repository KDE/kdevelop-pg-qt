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

#ifndef KDEV_PG_VISITOR_H
#define KDEV_PG_VISITOR_H

#include "kdev-pg-ast.h"

namespace KDevPG
{

class Visitor
{
public:
  virtual ~Visitor()
  {}

  virtual void visitNode(Model::Node *node)
  {
    if (node)
      (this->*sTable[node->kind])(node);
  }

protected:
  virtual void visitZero(Model::ZeroItem *) {}
  virtual void visitPlus(Model::PlusItem *) {}
  virtual void visitStar(Model::StarItem *) {}
  virtual void visitSymbol(Model::SymbolItem *) {}
  virtual void visitAction(Model::ActionItem *) {}
  virtual void visitAlternative(Model::AlternativeItem *) {}
  virtual void visitCons(Model::ConsItem *) {}
  virtual void visitEvolve(Model::EvolveItem *) {}
  virtual void visitTryCatch(Model::TryCatchItem *) {}
  virtual void visitAlias(Model::AliasItem *) {}
  virtual void visitTerminal(Model::TerminalItem *) {}
  virtual void visitNonTerminal(Model::NonTerminalItem *) {}
  virtual void visitInlinedNonTerminal(Model::InlinedNonTerminalItem *) {}
  virtual void visitAnnotation(Model::AnnotationItem *) {}
  virtual void visitCondition(Model::ConditionItem *) {}
  virtual void visitVariableDeclaration(Model::VariableDeclarationItem *) {}
  virtual void visitOperator(Model::OperatorItem *) {}

private:
  typedef void (Visitor::*VisitorFuncPointer)(Model::Node *item);
  static Visitor::VisitorFuncPointer sTable[];
};

}

#endif // KDEV_PG_VISITOR_H

