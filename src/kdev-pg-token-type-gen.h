/*
    SPDX-FileCopyrightText: 2011 Jonathan Schmidt-Dominé <devel@the-user.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEVPG_KDEV_PG_TOKEN_TYPE_GEN_H
#define KDEVPG_KDEV_PG_TOKEN_TYPE_GEN_H

#include <QTextStream>

namespace KDevPG
{

class GenerateTokenType
{
public:
  QTextStream& out;

public:
  GenerateTokenType(QTextStream& o): out(o)
  {}
  
  void operator()();
};

}

#endif // KDEVPG_KDEV_PG_TOKEN_TYPE_GEN_H
