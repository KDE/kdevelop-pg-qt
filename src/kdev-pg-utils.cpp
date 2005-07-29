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

#include "kdev-pg-utils.h"
#include "kdev-pg.h"

std::list<model::node*> left_most_items::operator()(model::node *node)
{
  _M_symbols.clear();
  visit_node(node);
  return _M_symbols;
}

void left_most_items::visit_condition(model::condition_item *node)
{
  visit_node(node->_M_item);
}

void left_most_items::visit_annotation(model::annotation_item *node)
{
  visit_node(node->_M_item);
}

void left_most_items::visit_cons(model::cons_item *node)
{
  visit_node(node->_M_left);
}

void left_most_items::visit_alternative(model::alternative_item *node)
{
  default_visitor::visit_alternative(node);
}

void left_most_items::visit_symbol(model::symbol_item *node)
{
  _M_symbols.push_back(node);
}

void left_most_items::visit_terminal(model::terminal_item *node)
{
  _M_symbols.push_back(node);
}

void left_most_items::visit_evolve(model::evolve_item *node)
{
  visit_node(node->_M_item);
}

std::set <model::symbol_item*>
right_most_symbols::operator()(model::node *node)
{
  _M_symbols.clear();
  visit_node(node);
  return _M_symbols;
}

void right_most_symbols::visit_cons(model::cons_item *node)
{
  visit_node(node->_M_right);

  if (reduce_to_epsilon(node->_M_right))
    visit_node(node->_M_left);
}

void right_most_symbols::visit_annotation(model::annotation_item *node)
{
  default_visitor::visit_annotation(node);
}

void right_most_symbols::visit_condition(model::condition_item *node)
{
  default_visitor::visit_condition(node);
}

void right_most_symbols::visit_alternative(model::alternative_item *node)
{
  default_visitor::visit_alternative(node);
}

void right_most_symbols::visit_symbol(model::symbol_item *node)
{
  _M_symbols.insert(node);
}

void right_most_symbols::visit_evolve(model::evolve_item *node)
{
  visit_node(node->_M_item);
}

std::list<model::node*> right_tails::operator()(model::node *node)
{
  _M_tails.clear();
  visit_node(node);
  return _M_tails;
}

void right_tails::visit_cons(model::cons_item *node)
{
  if (reduce_to_epsilon(node))
    _M_tails.push_back(node);

  default_visitor::visit_cons(node);
}

