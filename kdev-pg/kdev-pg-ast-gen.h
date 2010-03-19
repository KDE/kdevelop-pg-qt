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

#ifndef KDEV_PG_AST_GEN_H
#define KDEV_PG_AST_GEN_H

#include "kdev-pg-default-visitor.h"

#include <QtCore/QTextStream>
#include <QtCore/QSet>
#include <QtCore/QPair>
#include <QtCore/QList>
#include <QtCore/QString>

namespace KDevPG
{

class GenerateAst
{
public:
  QTextStream& out;

public:
  GenerateAst(QTextStream& o): out(o)
  {}

  void operator()();
};

class GenerateAstRule: protected DefaultVisitor
{
public:
  QTextStream& out;
  QSet<QString> mNames;
  bool mInAlternative;
  bool mInCons;

public:
  GenerateAstRule(QTextStream& o): out(o) {}

  void operator()(QPair<QString, Model::SymbolItem*> const &__it);

protected:
  virtual void visitAlternative(Model::AlternativeItem *node);
  virtual void visitVariableDeclaration(Model::VariableDeclarationItem *node);
  virtual void visitCons(Model::ConsItem *node);
  virtual void visitEvolve(Model::EvolveItem *node);

  bool switchAlternative(bool alt);
  bool switchCons(bool c);
};

}

#endif // KDEV_PG_AST_GEN_H
