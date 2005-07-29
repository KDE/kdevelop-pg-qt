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

#include "kdev-pg-default-visitor-gen.h"
#include "kdev-pg.h"
#include <iostream>

void generate_default_visitor::operator()()
{
  out << "class " << parser << "_default_visitor: public "
      << parser << "_visitor {" << std::endl
      << "public:" << std::endl;

  std::for_each(_G_system.symbols.begin(), _G_system.symbols.end(),
		gen_default_visitor_rule(out));

  out << "};" << std::endl;
}

void gen_default_visitor_rule::operator()(std::pair<std::string,
					  model::symbol_item*> const &__it)
{
  _M_names.clear();
  _M_annotations.clear();

  model::symbol_item *sym = __it.second;

  out << "virtual void visit_" << sym->_M_name
      << "(" << sym->_M_name << "_ast *node) {" << std::endl;

  world::environment::iterator it = _G_system.env.find(sym);
  while (it != _G_system.env.end())
    {
      model::evolve_item *e = (*it).second;
      if ((*it).first != sym)
        break;

      ++it;

      visit_node(e);
    }

  out << "}" << std::endl << std::endl;
}

void gen_default_visitor_rule::visit_annotation(model::annotation_item *node)
{
  default_visitor::visit_annotation(node);

  if (node->_M_local)
    return;

  if (_M_names.find(node->_M_name) != _M_names.end())
    return;

  model::symbol_item *sym = node_cast<model::symbol_item*>(node->_M_item);

  if (!sym)
    return; // nothing to do

  std::string base_type = std::string(sym->_M_name) + "_ast*";

  if (node->_M_sequence)
    {
      out << "if (" << "node->" << node->_M_name << "_sequence" << ") {"
          << "const list_node<" << base_type << "> *__it = " << "node->" << node->_M_name << "_sequence" << "->to_front()"
          << ", *__end = __it;" << std::endl
          << "do {" << std::endl
          << "visit_node(__it->element);" << std::endl
          << "__it = __it->next;" << std::endl
          << "} while (__it != __end);" << std::endl
          << "}" << std::endl;
    }
  else
    {
      out << "visit_node(" << "node->" << node->_M_name << ")" << ";" << std::endl;
    }

  _M_names.insert(node->_M_name);
  _M_annotations.push_back(node);
}

