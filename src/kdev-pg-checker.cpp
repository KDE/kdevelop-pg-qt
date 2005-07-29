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

#include "kdev-pg-checker.h"
#include "kdev-pg-utils.h"
#include "kdev-pg-pretty-printer.h"

#include <iostream>
#include <iterator>
#include <algorithm>

void FIRST_FIRST_conflict_checker::operator()(model::node *node)
{
  visit_node(node);
}

void FIRST_FIRST_conflict_checker::visit_alternative(model::alternative_item *node)
{
  default_visitor::visit_alternative(node);

  check(node->_M_left, node->_M_right);
}

void FIRST_FIRST_conflict_checker::check(model::node *left, model::node *right)
{
  world::node_set const &left_first = _G_system.FIRST[left];
  world::node_set const &right_first = _G_system.FIRST[right];

  std::deque<model::node*> U;
  std::set_intersection(left_first.begin(), left_first.end(),
                        right_first.begin(), right_first.end(), std::back_inserter(U));

  if (!U.empty())
    {
      pretty_printer p(std::cerr);
      std::cerr << "** WARNING found FIRST/FIRST conflict in" << std::endl << "\tRule ``";
      p(left);
      std::cerr << "''" << std::endl << "\tTerminals [";

      std::deque<model::node*>::iterator it = U.begin();
      while (it != U.end())
        {
          model::node *n = *it++;

          std::cerr << n;
          if (it != U.end())
            std::cerr << ", ";
        }
      std::cerr << "]" << std::endl << std::endl;
      // ### exit(EXIT_FAILURE);
    }
}

void FIRST_FIRST_conflict_checker::visit_evolve(model::evolve_item *node)
{
  default_visitor::visit_evolve(node);

  world::environment::iterator it = _G_system.env.find(node->_M_symbol);
  while (it != _G_system.env.end())
    {
      model::symbol_item *sym = (*it).first;
      model::evolve_item *e = (*it).second;
      ++it;

      if (sym != node->_M_symbol || node == e)
        continue;

      check(e, node);
    }
}

void FIRST_FOLLOW_conflict_checker::operator()(model::node *node)
{
  visit_node(node);
}

void FIRST_FOLLOW_conflict_checker::check(model::node *node, model::node *sym)
{
  if (!sym)
    sym = node;

  world::node_set const &first = _G_system.FIRST[node];
  world::node_set const &follow = _G_system.FOLLOW[sym];

  std::deque<model::node*> U;

  std::set_intersection(first.begin(), first.end(),
                        follow.begin(), follow.end(),
                        std::back_inserter(U));

  if (!U.empty())
    {
      pretty_printer p(std::cerr);
      std::cerr << "** WARNING found FIRST/FOLLOW conflict in" << std::endl << "\tRule ``";
      p(node);
      std::cerr << "''" << std::endl << "\tTerminals [";

      std::deque<model::node*>::iterator it = U.begin();
      while (it != U.end())
        {
          model::node *n = *it++;
          if (node_cast<model::zero_item*>(n))
            continue;

          std::cerr << n;
          if (it != U.end())
            std::cerr << ", ";
        }
      std::cerr << "]" << std::endl << std::endl;
      // ### exit(EXIT_FAILURE);
    }
}

void FIRST_FOLLOW_conflict_checker::visit_alternative(model::alternative_item *node)
{
  default_visitor::visit_alternative(node);

  if (reduce_to_epsilon(node))
    check(node);
}

void FIRST_FOLLOW_conflict_checker::visit_cons(model::cons_item *node)
{
  default_visitor::visit_cons(node);

  if (reduce_to_epsilon(node))
    check(node);
}

void FIRST_FOLLOW_conflict_checker::visit_evolve(model::evolve_item *node)
{
  default_visitor::visit_evolve(node);

  if (reduce_to_epsilon(node->_M_item))
    check(node->_M_item, node->_M_symbol);
}

void undefined_symbol_checker::operator()(model::node *node)
{
  visit_node(node);
}

void undefined_symbol_checker::visit_symbol(model::symbol_item *node)
{
  if (_G_system.env.count(node) == 0)
    {
      std::cerr << "** WARNING Undefined symbol ``" << node->_M_name << "''" << std::endl;
      exit(EXIT_FAILURE);
    }
}

void empty_FIRST_checker::operator()(model::node *node)
{
  visit_node(node);
}

void empty_FIRST_checker::visit_symbol(model::symbol_item *node)
{
  if (_G_system.FIRST[node].empty())
    {
      std::cerr << "** WARNING Empty FIRST set for ``" << node->_M_name << "''" << std::endl;
      exit(EXIT_FAILURE);
    }
}
