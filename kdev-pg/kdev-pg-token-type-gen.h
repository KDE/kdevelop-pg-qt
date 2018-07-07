/* This file is part of kdev-pg-qt
   Copyright (C) 2011 Jonathan Schmidt-Dominé <devel@the-user.org>

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
