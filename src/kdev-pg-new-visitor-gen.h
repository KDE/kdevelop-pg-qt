/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEV_PG_NEW_VISITOR_GEN_H
#define KDEV_PG_NEW_VISITOR_GEN_H

#include "kdev-pg-default-visitor.h"

#include <QSet>
#include <QList>
#include <QString>
#include <QTextStream>


namespace KDevPG
{

class GenerateNewVisitor
{
public:
  QTextStream& out;
  QString name;

public:
  GenerateNewVisitor(QTextStream& o, const QString& n): out(o), name(n)
  {}

  void operator()();
};

}

#endif // KDEV_PG_NEW_VISITOR_GEN_H
