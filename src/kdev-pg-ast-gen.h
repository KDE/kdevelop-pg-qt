/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEV_PG_AST_GEN_H
#define KDEV_PG_AST_GEN_H

#include "kdev-pg-default-visitor.h"

#include <QTextStream>
#include <QSet>
#include <QPair>
#include <QList>
#include <QString>

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
  QSet<QString> mGenerated;
  QSet<Model::SymbolItem*> mToGenerate;
  bool mInAlternative;
  bool mInCons;
  bool mForce;
  bool mFirstTime;

public:
  GenerateAstRule(QTextStream& o): out(o), mForce(false), mFirstTime(true) {}

  void operator()(Model::SymbolItem *sym);

protected:
  void visitAlternative(Model::AlternativeItem *node) override;
  void visitVariableDeclaration(Model::VariableDeclarationItem *node) override;
  void visitCons(Model::ConsItem *node) override;
  void visitEvolve(Model::EvolveItem *node) override;
  void visitInlinedNonTerminal(Model::InlinedNonTerminalItem *node) override;

  bool switchAlternative(bool alt);
  bool switchCons(bool c);
};

class GenerateAstFwd
{
public:
  QTextStream& out;
  
public:
  GenerateAstFwd(QTextStream& o): out(o)
  {}
  
  void operator()();
};
}

#endif // KDEV_PG_AST_GEN_H
