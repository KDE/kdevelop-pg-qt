/* This file is part of kdev-pg
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
   the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
*/

#ifndef KDEV_PG_VISITOR_BITS_GEN_H
#define KDEV_PG_VISITOR_BITS_GEN_H

#include "kdev-pg-default-visitor.h"

#include <set>
#include <list>
#include <string>

class generate_visitor_bits
{
  std::ostream &out;
  char const *parser;

public:
  generate_visitor_bits(std::ostream &o, char const *p): out(o), parser(p)
  {}

  void operator()();
};


#endif // KDEV_PG_VISITORGEN_H

