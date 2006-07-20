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
   the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
*/

#ifndef KDEV_PG_DEFAULT_VISITORGEN_H
#define KDEV_PG_DEFAULT_VISITORGEN_H

#include "kdev-pg-default-visitor.h"

#include <set>
#include <list>
#include <string>

class generate_default_visitor
{
  std::ostream &out;

public:
  generate_default_visitor(std::ostream &o): out(o)
  {}

  void operator()();
};

class gen_default_visitor_rule: protected default_visitor
{
  std::ostream &out;
  std::set<std::string> _M_names;
  std::list<model::variable_declaration_item*> _M_variable_declarations;

public:
  gen_default_visitor_rule(std::ostream &o): out(o)
  {}

  void operator()(std::pair<std::string, model::symbol_item*> const &__it);

protected:
  virtual void visit_variable_declaration(model::variable_declaration_item *node);
};


#endif // KDEV_PG_DEFAULT_VISITORGEN_H
