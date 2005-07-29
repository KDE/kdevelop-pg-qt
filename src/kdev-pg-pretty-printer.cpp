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

#include "kdev-pg-pretty-printer.h"
#include <iostream>
#include <cassert>

void pretty_printer::visit_zero(model::zero_item *node)
{
  out << "0";
}

void pretty_printer::visit_bang(model::bang_item *node)
{
  out << "!";
  visit_node(node->_M_item);
}

void pretty_printer::visit_symbol(model::symbol_item *node)
{
  out << node->_M_name;
}

void pretty_printer::visit_action(model::action_item *node)
{
  visit_node(node->_M_item);
}

void pretty_printer::visit_alternative(model::alternative_item *node)
{
  out << "(";
  visit_node(node->_M_left);
  out << " | ";
  visit_node(node->_M_right);
  out << ")";
}

void pretty_printer::visit_cons(model::cons_item *node)
{
  out << "(";
  visit_node(node->_M_left);
  out << " ";
  visit_node(node->_M_right);
  out << ")";
}

void pretty_printer::visit_evolve(model::evolve_item *node)
{
  visit_node(node->_M_item);
  out << " -> ";
  visit_node(node->_M_symbol);
}

void pretty_printer::visit_alias(model::alias_item *node)
{
  assert(0); // ### not implemented yet
}

void pretty_printer::visit_terminal(model::terminal_item *node)
{
  out << node->_M_name;
}

void pretty_printer::visit_annotation(model::annotation_item *node)
{
  out << (node->_M_sequence ? "#" : "") << node->_M_name << (node->_M_local ? ":" : "=");
  visit_node(node->_M_item);
}
