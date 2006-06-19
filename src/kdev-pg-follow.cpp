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

#include "kdev-pg-follow.h"

#include <cassert>
#include <iostream>

//
// Calculating the FOLLOW set depends on the FIRST set being already available
// and is in principle quite easy. There are only a few simple rules:
//
// 1. Put EOF at the end of the start rule
// 2. For every rule "items -> rulename", put FOLLOW(rulename) into FOLLOW(items)
// 3. For every item sequence "item1 item2", put FIRST(item2) into FOLLOW(item1)
// 4. For every rule "item1 item2 -> rulename", put FOLLOW(rulename)
//    into FOLLOW(item1) if item2 can derive to epsilon ("0").
// 5. Propagate the FOLLOW sets down to the symbols where appropriate.
// 6. Loop for all rules until there are no changes in any FOLLOW set anymore.
//

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
  if (node_cast<model::zero_item*>(__dest) != 0
      || node_cast<model::terminal_item*>(__dest) != 0)
    {
      return;
    }

  world::node_set &dest = _G_system.FOLLOW(__dest);

  for (world::node_set::const_iterator it = source.begin(); it != source.end(); ++it)
    {
      if (model::terminal_item *t = node_cast<model::terminal_item*>(*it))
        {
          _M_changed |= dest.insert(t).second;
        }
    }
}

void next_FOLLOW::visit_evolve(model::evolve_item *node)
{
  model::terminal_item *teof = _G_system.push_terminal("EOF", "end of file");
  if (node == _G_system.start && _G_system.FOLLOW(node->_M_symbol).insert(teof).second)
    {
      _M_changed = true;
    }

  merge(node->_M_item, _G_system.FOLLOW(node->_M_symbol));

  default_visitor::visit_evolve(node);
}

void next_FOLLOW::visit_cons(model::cons_item *node)
{
  merge(node->_M_right, _G_system.FOLLOW(node));
  merge(node->_M_left, _G_system.FIRST(node->_M_right));

  if (reduces_to_epsilon(node->_M_right))
    merge(node->_M_left, _G_system.FOLLOW(node));

  default_visitor::visit_cons(node);
}

void next_FOLLOW::visit_alternative(model::alternative_item *node)
{
  merge(node->_M_left, _G_system.FOLLOW(node));
  merge(node->_M_right, _G_system.FOLLOW(node));

  default_visitor::visit_alternative(node);
}

void next_FOLLOW::visit_action(model::action_item *node)
{
  merge(node->_M_item, _G_system.FOLLOW(node));

  default_visitor::visit_action(node);
}

void next_FOLLOW::visit_annotation(model::annotation_item *node)
{
  merge(node->_M_item, _G_system.FOLLOW(node));

  default_visitor::visit_annotation(node);
}

void next_FOLLOW::visit_condition(model::condition_item *node)
{
  merge(node->_M_item, _G_system.FOLLOW(node));

  default_visitor::visit_condition(node);
}

void next_FOLLOW::visit_plus(model::plus_item *node)
{
  merge(node->_M_item, _G_system.FOLLOW(node));

  default_visitor::visit_plus(node);
}

void next_FOLLOW::visit_star(model::star_item *node)
{
  merge(node->_M_item, _G_system.FOLLOW(node));

  default_visitor::visit_star(node);
}

void compute_FOLLOW()
{
  bool changed = true;
  while (changed)
    {
      changed = false;
      std::for_each(_G_system.rules.begin(), _G_system.rules.end(), next_FOLLOW(changed));
    }
}
