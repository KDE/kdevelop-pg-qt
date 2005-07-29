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

#ifndef KDEV_PG_H
#define KDEV_PG_H

#include "kdev-pg-ast.h"

#include <set>
#include <map>
#include <deque>
#include <string>
#include <cassert>

namespace pg
{
  model::zero_item *zero();
  model::bang_item *bang(model::node *item);
  model::symbol_item *symbol(char const *name);
  model::action_item *action(model::node *item, char const *code);
  model::alternative_item *alternative(model::node *left, model::node *right);
  model::cons_item *cons(model::node *left, model::node *right);
  model::evolve_item *evolve(model::node *item, model::symbol_item *symbol, char const *code);
  model::alias_item *alias(char const *code, model::symbol_item *symbol);
  model::terminal_item *terminal(char const *name);
  model::annotation_item *annotation(char const *name, model::node *item, bool sequence, bool local);
  model::condition_item *condition(char const *code, model::node *item);
} // namespace pg

struct world
{
  world()
    : token_stream("kdev_pg_token_stream"), decl(0), bits(0),
      start(0), _M_zero(0)
  {}

  char const *token_stream;
  char const *decl;
  char const *bits;

  model::zero_item *zero()
  {
    if (!_M_zero)
      _M_zero = pg::zero();
    return _M_zero;
  }

  void push_rule(model::node *rule)
  {
    model::evolve_item *e = node_cast<model::evolve_item*>(rule);
    assert(e != 0);

    if (rules.empty())
      start = e;
    rules.push_back(e);
  }

  model::terminal_item *push_terminal(char const *__name)
  {
    std::string name = __name;
    terminal_set::iterator it = terminals.find(name);
    if (it == terminals.end())
      it = terminals.insert(std::make_pair(name, pg::terminal(__name))).first;

    return (*it).second;
  }

  model::symbol_item *push_symbol(char const *__name)
  {
    std::string name = __name;
    symbol_set::iterator it = symbols.find(name);
    if (it == symbols.end())
      it = symbols.insert(std::make_pair(name, pg::symbol(__name))).first;

    return (*it).second;
  }

  typedef std::set <model::node*> node_set;
  typedef std::map<std::string, model::symbol_item*> symbol_set;
  typedef std::map<std::string, model::terminal_item*> terminal_set;
  typedef std::multimap<model::symbol_item*, model::evolve_item *> environment;

  model::evolve_item *start;
  model::zero_item *_M_zero;

  symbol_set symbols;
  terminal_set terminals;
  std::deque<model::node*> rules;

  environment env;

  std::map<model::node*, node_set> FIRST;
  std::map<model::node*, node_set> FOLLOW;
};

bool reduce_to_epsilon(model::node *node);
std::ostream &operator << (std::ostream &out, model::node const *__node);


extern world _G_system;
extern FILE *file;

#endif // KDEV_PG_H
