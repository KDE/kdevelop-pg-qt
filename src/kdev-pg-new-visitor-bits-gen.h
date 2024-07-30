/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEV_PG_NEW_VISITOR_BITS_GEN_H
#define KDEV_PG_NEW_VISITOR_BITS_GEN_H

#include "kdev-pg-default-visitor.h"

#include <QPair>
#include <QTextStream>

namespace KDevPG
{

class GenerateNewVisitorBitsRule: protected DefaultVisitor
{
public:
  QTextStream& out;
  QString name;
  
public:
  GenerateNewVisitorBitsRule(QTextStream& o, const QString& n): out(o), name(n)
  {}

  void operator()(QPair<QString, Model::SymbolItem*> const &__it);
};

}

#endif // KDEV_PG_NEW_VISITOR_BITS_GEN_H
