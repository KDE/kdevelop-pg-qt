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

#include "kdev-pg-follow.h"
#include "kdev-pg-utils.h"

#include <cassert>
#include <iostream>

void initialize_FOLLOW::operator()(model::node *node)
{
  visit_node(node);
}

void initialize_FOLLOW::visit_symbol(model::symbol_item *node)
{
  if (_G_system.find_in_FOLLOW(node) != _G_system.FOLLOW_end())
    return ;

  default_visitor::visit_symbol(node);
}

next_FOLLOW::next_FOLLOW(bool &changed)
  : _M_changed(changed)
{}

void next_FOLLOW::operator()(model::node *node)
{
  model::evolve_item *e = node_cast<model::evolve_item*>(node);
  assert(e != 0);
  _M_symbol = e->_M_symbol;
  visit_node(node);
}

void next_FOLLOW::merge(model::node*__dest, world::node_set const &source)
{
  world::node_set &dest = _G_system.FOLLOW(__dest);

  for (world::node_set::const_iterator it = source.begin(); it != source.end(); ++it)
    {
      if (model::terminal_item *t = node_cast<model::terminal_item*>(*it))
        {
          _M_changed |= dest.insert(t).second;
        }
    }
}

void next_FOLLOW::visit_condition(model::condition_item *node)
{
  default_visitor::visit_condition(node);

  merge(node, _G_system.FOLLOW(node->_M_item));
}

void next_FOLLOW::visit_annotation(model::annotation_item *node)
{
  default_visitor::visit_annotation(node);

  merge(node, _G_system.FOLLOW(node->_M_item));
}

void next_FOLLOW::visit_alternative(model::alternative_item *node)
{
  default_visitor::visit_alternative(node);

  merge(node, _G_system.FOLLOW(node->_M_left));
  merge(node, _G_system.FOLLOW(node->_M_right));
}

void next_FOLLOW::visit_cons(model::cons_item *node)
{
  default_visitor::visit_cons(node);

  right_most_symbols rm;

  std::set <model::symbol_item*>
    symbols = rm(node->_M_left);

  for (std::set <model::symbol_item*>::iterator it = symbols.begin(); it != symbols.end(); ++it)
    {
      model::symbol_item *sym = *it;
      merge(sym, _G_system.FIRST(node->_M_right));
      merge(node, _G_system.FOLLOW(sym));
    }
}

void next_FOLLOW::visit_evolve(model::evolve_item *node)
{
  default_visitor::visit_evolve(node);

  model::terminal_item *teof = _G_system.push_terminal("EOF", "end of file");
  if (node == _G_system.start && _G_system.FOLLOW(node->_M_symbol).insert(teof).second)
    _M_changed = true;

  check_right_tail(node->_M_item);
}

void next_FOLLOW::check_right_tail(model::node *node)
{
  if (model::cons_item *c = node_cast<model::cons_item*>(node))
    {
      if (reduce_to_epsilon(c->_M_right))
        check_right_tail(c->_M_left);

      check_right_tail(c->_M_right);
    }
  else if (model::alternative_item *a = node_cast<model::alternative_item*>(node))
    {
      check_right_tail(a->_M_left);
      check_right_tail(a->_M_right);
      merge(a, _G_system.FOLLOW(_M_symbol));
    }
  else if (model::symbol_item *s = node_cast<model::symbol_item*>(node))
    {
      merge(s, _G_system.FOLLOW(_M_symbol));
    }
  else if (model::annotation_item *a = node_cast<model::annotation_item*>(node))
    {
      check_right_tail(a->_M_item);
      merge(a, _G_system.FOLLOW(a->_M_item));
    }
  else if (model::condition_item *c = node_cast<model::condition_item*>(node))
    {
      check_right_tail(c->_M_item);
      merge(c, _G_system.FOLLOW(c->_M_item));
    }
}

void compute_FOLLOW()
{
  std::for_each(_G_system.rules.begin(), _G_system.rules.end(), initialize_FOLLOW());

  bool changed = true;
  while (changed)
    {
      changed = false;
      std::for_each(_G_system.rules.begin(), _G_system.rules.end(), next_FOLLOW(changed));
    }
}
