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

#ifndef KDEV_PG_AST_H
#define KDEV_PG_AST_H

#include "kdev-pg-allocator.h"

#define PG_NODE(k) \
    enum { node_kind = node_kind_##k };

// the kdev-pg calculus
namespace model
{

  enum node_kind_enum {
    node_kind_item = 0,
    node_kind_zero = 1,
    node_kind_plus = 2,
    node_kind_star = 3,
    node_kind_symbol = 4,
    node_kind_action = 5,
    node_kind_alternative = 6,
    node_kind_cons = 7,
    node_kind_evolve = 8,
    node_kind_alias = 9,
    node_kind_terminal = 10,
    node_kind_annotation = 11,
    node_kind_condition = 12,

    node_kind_LAST
  };

  struct node
  {
    PG_NODE(item)

    int kind;
  };

  struct zero_item: public node
  {
    PG_NODE(zero)
  };

  struct plus_item: public node
  {
    PG_NODE(plus)

    node *_M_item;
  };

  struct star_item: public node
  {
    PG_NODE(star)

    node *_M_item;
  };

  struct symbol_item: public node
  {
    PG_NODE(symbol)

    char const *_M_name;
  };

  struct action_item: public node
  {
    PG_NODE(action)

    node *_M_item;
    char const *_M_code;
  };

  struct alternative_item: public node
  {
    PG_NODE(alternative)

    node *_M_left;
    node *_M_right;
  };

  struct cons_item: public node
  {
    PG_NODE(cons)

    node *_M_left;
    node *_M_right;
  };

  struct evolve_item: public node
  {
    PG_NODE(evolve)

    node *_M_item;
    symbol_item *_M_symbol;
    char const *_M_code;
  };

  struct alias_item: public node
  {
    PG_NODE(alias)

    char const *_M_code;
    symbol_item *_M_symbol;
  };

  struct terminal_item: public node
  {
    PG_NODE(terminal)

    char const *_M_name;
    char const *_M_description;
  };

  struct annotation_item: public node
  {
    PG_NODE(annotation)

    char const *_M_name;
    node *_M_item;
    bool _M_sequence;
    bool _M_local;
  };

  struct condition_item: public node
  {
    PG_NODE(condition)

    char const *_M_code;
    node *_M_item;
  };

} // namespace model

template <class _Tp>
_Tp node_cast(model::node *item)
{
  if (static_cast<_Tp>(0)->node_kind == item->kind)
    return static_cast<_Tp>(item);

  return 0;
}

extern kdev_pg_allocator<char> _G_memory_pool;

template <class _Tp>
_Tp *create_node()
{
  _Tp *node = reinterpret_cast<_Tp*>(_G_memory_pool.allocate(sizeof(_Tp)));
  node->kind = _Tp::node_kind;
  return node;
}

#endif // KDEV_PG_AST_H
