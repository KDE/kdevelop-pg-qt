/* This file is part of kdev-pg-qt
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

#ifndef KDEV_PG_PRETTY_PRINTER_H
#define KDEV_PG_PRETTY_PRINTER_H

#include "kdev-pg-default-visitor.h"

#include <QTextStream>

namespace KDevPG
{

class PrettyPrinter: protected DefaultVisitor
{
public:
  QTextStream& out;

  PrettyPrinter(QTextStream& o): out(o)
  {}

  void operator()(Model::Node *node)
  {
    visitNode(node);
    out.flush();
  }

protected:
  void visitZero(Model::ZeroItem *node) override;
  void visitPlus(Model::PlusItem *node) override;
  void visitStar(Model::StarItem *node) override;
  void visitSymbol(Model::SymbolItem *node) override;
  void visitAction(Model::ActionItem *node) override;
  void visitAlternative(Model::AlternativeItem *node) override;
  void visitCons(Model::ConsItem *node) override;
  void visitEvolve(Model::EvolveItem *node) override;
  void visitTryCatch(Model::TryCatchItem *node) override;
  void visitAlias(Model::AliasItem *node) override;
  void visitTerminal(Model::TerminalItem *node) override;
  void visitInlinedNonTerminal(Model::InlinedNonTerminalItem *node) override;
  void visitNonTerminal(Model::NonTerminalItem *node) override;
  void visitAnnotation(Model::AnnotationItem *node) override;
};

}

#endif // KDEV_PG_PRETTY_PRINTER_H
