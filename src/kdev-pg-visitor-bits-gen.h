/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEV_PG_VISITOR_BITS_GEN_H
#define KDEV_PG_VISITOR_BITS_GEN_H

#include "kdev-pg-default-visitor.h"

#include <QSet>
#include <QList>
#include <QString>
#include <QTextStream>

namespace KDevPG
{

class GenerateVisitorBits
{
public:
  QTextStream& out;

public:
  explicit GenerateVisitorBits(QTextStream& o): out(o)
  {}

  void operator()();
};

}

#endif // KDEV_PG_VISITORGEN_H

