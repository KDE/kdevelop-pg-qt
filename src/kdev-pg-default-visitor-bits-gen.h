/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEV_PG_DEFAULT_VISITOR_BITS_GEN_H
#define KDEV_PG_DEFAULT_VISITOR_BITS_GEN_H

#include "kdev-pg-default-visitor.h"

#include <QSet>
#include <QList>
#include <QTextStream>

namespace KDevPG
{

class GenerateDefaultVisitorBitsRule: protected DefaultVisitor
{
public:
  QTextStream& out;
  QString name;
  QSet<QString> mNames;
  QList<Model::VariableDeclarationItem*> mVariableDeclarations;

public:
  explicit GenerateDefaultVisitorBitsRule(QTextStream& o, const QString& n = QStringLiteral("DefaultVisitor")): out(o), name(n)
  {}

  void operator()(QPair<QString, Model::SymbolItem*> const &__it);

protected:
  void visitVariableDeclaration(Model::VariableDeclarationItem *node) override;
};

class HasMemberNodes: protected DefaultVisitor
{
public:
  bool &has_members;

public:
  HasMemberNodes(bool &result): has_members(result)
  {}

  void operator()(Model::SymbolItem *sym);

protected:
  void visitVariableDeclaration(Model::VariableDeclarationItem *node) override;
};

}

#endif // KDEV_PG_DEFAULT_VISITOR_BITS_GEN_H
