/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
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

