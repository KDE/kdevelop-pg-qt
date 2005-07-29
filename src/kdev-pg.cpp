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

#include "kdev-pg.h"
#include "kdev-pg-ast.h"

#include <cassert>
#include <iostream>

model::zero_item *pg::zero()
{
  model::zero_item *node = create_node<model::zero_item>();
  return node;
}

model::bang_item *pg::bang(model::node *item)
{
  model::bang_item *node = create_node<model::bang_item>();
  node->_M_item = item;
  return node;
}

model::symbol_item *pg::symbol(char const *name)
{
  model::symbol_item *node = create_node<model::symbol_item>();
  node->_M_name = name;
  return node;
}

model::action_item *pg::action(model::node *item, char const *code)
{
  model::action_item *node = create_node<model::action_item>();
  node->_M_item = item;
  node->_M_code = code;
  return node;
}

model::alternative_item *pg::alternative(model::node *left, model::node *right)
{
  model::alternative_item *node = create_node<model::alternative_item>();
  node->_M_left = left;
  node->_M_right = right;
  return node;
}

model::cons_item *pg::cons(model::node *left, model::node *right)
{
  model::cons_item *node = create_node<model::cons_item>();
  node->_M_left = left;
  node->_M_right = right;
  return node;
}

model::evolve_item *pg::evolve(model::node *item, model::symbol_item *symbol, char const *code)
{
  model::evolve_item *node = create_node<model::evolve_item>();
  node->_M_item = item;
  node->_M_symbol = symbol;
  node->_M_code = code;
  return node;
}

model::alias_item *pg::alias(char const *code, model::symbol_item *symbol)
{
  model::alias_item *node = create_node<model::alias_item>();
  node->_M_code = code;
  node->_M_symbol = symbol;
  return node;
}

model::terminal_item *pg::terminal(char const *name)
{
  model::terminal_item *node = create_node<model::terminal_item>();
  node->_M_name = name;
  return node;
}

model::annotation_item *pg::annotation(char const *name, model::node *item, bool sequence, bool local)
{
  model::annotation_item *node = create_node<model::annotation_item>();
  node->_M_name = name;
  node->_M_item = item;
  node->_M_sequence = sequence;
  node->_M_local = local;
  return node;
}

model::condition_item *pg::condition(char const *code, model::node *item)
{
  model::condition_item *node = create_node<model::condition_item>();
  node->_M_code = code;
  node->_M_item = item;
  return node;
}

std::ostream &operator << (std::ostream &out, model::node const *__node)
{
  model::node *node = const_cast<model::node*>(__node);

  if (model::zero_item *z = node_cast<model::zero_item*>(node))
    return (out << "0");
  else if (model::symbol_item *s = node_cast<model::symbol_item *>(node))
    return (out << s->_M_name);
  else if (model::terminal_item *t = node_cast<model::terminal_item *>(node))
    return (out << t->_M_name);
  else if (model::annotation_item *a = node_cast<model::annotation_item *>(node))
    return (out << (a->_M_sequence ? "#" : "") << a->_M_name << (a->_M_local ? ":" : "=") << a->_M_item);
#if 0

  else
    if (model::evolve_item *e = node_cast<model::evolve_item *>(node))
      return (out << "evolve:" << e->_M_symbol->_M_name);
#endif

  assert(0);
  return out;
}

bool reduce_to_epsilon(model::node *node)
{
  if (model::cons_item *c = node_cast<model::cons_item*>(node))
    {
      return reduce_to_epsilon(c->_M_left) && reduce_to_epsilon(c->_M_right);
    }
  else if (model::alternative_item *a = node_cast<model::alternative_item*>(node))
    {
      return reduce_to_epsilon(a->_M_left) || reduce_to_epsilon(a->_M_right);
    }
  else if (model::action_item *a = node_cast<model::action_item*>(node))
    {
      return reduce_to_epsilon(a->_M_item);
    }
  else if (model::condition_item *c = node_cast<model::condition_item*>(node))
    {
      return reduce_to_epsilon(c->_M_item);
    }
  else if (model::annotation_item *a = node_cast<model::annotation_item*>(node))
    {
      return reduce_to_epsilon(a->_M_item);
    }
  else if (model::symbol_item *s = node_cast<model::symbol_item*>(node))
    {
      return _G_system.FIRST[s].find(_G_system.zero()) != _G_system.FIRST[s].end(); // hmm
    }
  else if (model::bang_item *b = node_cast<model::bang_item*>(node))
    {
      return true;
    }
  else if (model::zero_item *z = node_cast<model::zero_item*>(node))
    {
      return true;
    }

  return false;
}

