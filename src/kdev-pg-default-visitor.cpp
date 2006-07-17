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

#include "kdev-pg-default-visitor.h"

void default_visitor::visit_zero(model::zero_item *node)
{}

void default_visitor::visit_symbol(model::symbol_item *node)
{}

void default_visitor::visit_terminal(model::terminal_item *node)
{}

void default_visitor::visit_nonterminal(model::nonterminal_item *node)
{
  visit_node(node->_M_symbol);
}

void default_visitor::visit_plus(model::plus_item *node)
{
  visit_node(node->_M_item);
}

void default_visitor::visit_star(model::star_item *node)
{
  visit_node(node->_M_item);
}

void default_visitor::visit_action(model::action_item *node)
{
  visit_node(node->_M_item);
}

void default_visitor::visit_alternative(model::alternative_item *node)
{
  visit_node(node->_M_left);
  visit_node(node->_M_right);
}

void default_visitor::visit_cons(model::cons_item *node)
{
  visit_node(node->_M_left);
  visit_node(node->_M_right);
}

void default_visitor::visit_evolve(model::evolve_item *node)
{
  visit_node(node->_M_item);
  visit_node(node->_M_symbol);
}

void default_visitor::visit_alias(model::alias_item *node)
{
  visit_node(node->_M_symbol);
}

void default_visitor::visit_annotation(model::annotation_item *node)
{
  visit_node(node->_M_item);
}

void default_visitor::visit_condition(model::condition_item *node)
{
  visit_node(node->_M_item);
}
