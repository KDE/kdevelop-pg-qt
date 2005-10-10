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

#include "kdev-pg-ast-gen.h"
#include "kdev-pg.h"
#include <iostream>

void generate_ast::operator()()
{
  for (std::map<std::string, model::symbol_item*>::iterator it = _G_system.symbols.begin();
       it != _G_system.symbols.end(); ++it)
    {
      model::symbol_item *sym = (*it).second;
      out << "struct " << sym->_M_name << "_ast;" << std::endl;
    }

  out << std::endl;

  out << "struct " << parser << "_ast_node {" << std::endl
      << "enum ast_node_kind_enum {" << std::endl;

  int node_id = 1000;
  for (std::map<std::string, model::symbol_item*>::iterator it = _G_system.symbols.begin();
       it != _G_system.symbols.end(); ++it)
    {
      model::symbol_item *sym = (*it).second;
      out << "Kind_" << sym->_M_name << " = " << node_id++ << "," << std::endl;
    }

  out << "AST_NODE_KIND_COUNT" << std::endl
      << "};" << std::endl << std::endl
      << "int kind;" << std::endl
      << "std::size_t start_token;" << std::endl
      << "std::size_t end_token;" << std::endl
      << "};" << std::endl
      << std::endl;

  std::for_each(_G_system.symbols.begin(), _G_system.symbols.end(), gen_ast_rule(out, parser));
  out << std::endl;
}

void gen_ast_rule::operator()(std::pair<std::string, model::symbol_item*> const &__it)
{
  _M_names.clear();
  _M_in_alternative = false;
  _M_in_cons = false;

  model::symbol_item *sym = __it.second;
  out << "struct " << sym->_M_name << "_ast: public " << parser << "_ast_node"
      << "{" << std::endl
      << "enum { KIND = Kind_" << sym->_M_name << "};" << std::endl << std::endl;

  world::environment::iterator it = _G_system.env.find(sym);
  while (it != _G_system.env.end())
    {
      model::evolve_item *e = (*it).second;
      if ((*it).first != sym)
        break;

      ++it;

      visit_node(e);
    }

  out << std::endl
      << "};" << std::endl << std::endl;
}

void gen_ast_rule::visit_annotation(model::annotation_item *node)
{
  default_visitor::visit_annotation(node);

  if (node->_M_local)
    return;

  if (_M_names.find(node->_M_name) != _M_names.end())
    return;

  if (node->_M_sequence)
    {
      out << "const list_node<";

      if (node_cast<model::terminal_item*>(node->_M_item))
        out << "std::size_t";
      else if (model::symbol_item *sym = node_cast<model::symbol_item*>(node->_M_item))
        out << sym->_M_name << "_ast *";
      else
        assert(0); // ### not supported

      out << "> *";
    }
  else
    {
      if (node_cast<model::terminal_item*>(node->_M_item))
        out << "std::size_t ";
      else if (model::symbol_item *sym = node_cast<model::symbol_item*>(node->_M_item))
        out << sym->_M_name << "_ast *";
      else
        assert(0); // ### not supported
    }

  out << node->_M_name;

  if (node->_M_sequence)
    out << "_sequence";

  out << ";" << std::endl;

  _M_names.insert(node->_M_name);
}

void gen_ast_rule::visit_alternative(model::alternative_item *node)
{
  bool in_alternative = switch_alternative(true);

#if defined(AST_OPT_BRANCH)
  if (!in_alternative)
    {
      out << "union" << std::endl
          << "{" << std::endl
          << parser << "_ast_node *__node_cast;" << std::endl
          << "std::size_t __token_cast;" << std::endl
          << std::endl;
    }
#endif

  default_visitor::visit_alternative(node);

#if defined(AST_OPT_BRANCH)
  if (!in_alternative)
    out << "}; // union" << std::endl;
#endif

  switch_alternative(in_alternative);
}

void gen_ast_rule::visit_cons(model::cons_item *node)
{
  bool in_cons = switch_cons(true);

#if defined(AST_OPT_BRANCH)
  if (!in_cons)
    {
      out << "struct" << std::endl
          << "{" << std::endl;
    }
#endif

  default_visitor::visit_cons(node);

#if defined(AST_OPT_BRANCH)
  if (!in_cons)
    {
      out << "}; // struct" << std::endl;
      _M_names.clear();
    }
#endif

  switch_cons(in_cons);
}

bool gen_ast_rule::switch_alternative(bool alt)
{
  bool old = _M_in_alternative;
  _M_in_alternative = alt;
  return old;
}

bool gen_ast_rule::switch_cons(bool c)
{
  bool old = _M_in_cons;
  _M_in_cons = c;
  return old;
}
