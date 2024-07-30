/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEV_PG_DEFAULT_VISITOR_GEN_H
#define KDEV_PG_DEFAULT_VISITOR_GEN_H

#include "kdev-pg-default-visitor.h"

#include <QSet>
#include <QList>
#include <QString>
#include <QTextStream>


namespace KDevPG
{

class GenerateDefaultVisitor
{
public:
  QTextStream& out;
  QString name;

public:
  explicit GenerateDefaultVisitor(QTextStream& o, const QString& n = "DefaultVisitor"): out(o), name(n)
  {}

  void operator()();
};

class GenerateDefaultVisitorRule: protected DefaultVisitor
{
public:
  QTextStream& out;

public:
  GenerateDefaultVisitorRule(QTextStream& o): out(o)
  {}

  void operator()(QPair<QString, Model::SymbolItem*> const &__it);
};

}

#endif // KDEV_PG_DEFAULT_VISITOR_GEN_H
