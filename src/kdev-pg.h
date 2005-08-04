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
  typedef std::set<model::node*> node_set;
  typedef std::map<std::string, model::symbol_item*> symbol_set;
  typedef std::map<std::string, model::terminal_item*> terminal_set;
  typedef std::multimap<model::symbol_item*, model::evolve_item *> environment;

  typedef std::map<std::pair<model::node*, int>, node_set> first_set;
  typedef std::map<std::pair<model::node*, int>, node_set> follow_set;

  world()
    : token_stream("kdev_pg_token_stream"), decl(0), bits(0), generate_ast(true),
      start(0), _M_zero(0)
  {}

  // options
  char const *token_stream;
  char const *decl;
  char const *bits;
  bool generate_ast;

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

  first_set::iterator FIRST_begin() { return FIRST_K.begin(); }
  first_set::iterator FIRST_end() { return FIRST_K.end(); }

  follow_set::iterator FOLLOW_begin() { return FOLLOW_K.begin(); }
  follow_set::iterator FOLLOW_end() { return FOLLOW_K.end(); }

  node_set &FIRST(model::node *node, int K = 1)
  { return FIRST_K[std::make_pair(node, K)]; }

  node_set &FOLLOW(model::node *node, int K = 1)
  { return FOLLOW_K[std::make_pair(node, K)]; }

  first_set::iterator find_in_FIRST(model::node *node, int K = 1)
  { return FIRST_K.find(std::make_pair(node, K)); }

  follow_set::iterator find_in_FOLLOW(model::node *node, int K = 1)
  { return FOLLOW_K.find(std::make_pair(node, K)); }

  model::evolve_item *start;
  model::zero_item *_M_zero;

  symbol_set symbols;
  terminal_set terminals;
  std::deque<model::node*> rules;

  environment env;

private:
  first_set FIRST_K;
  follow_set FOLLOW_K;
};

bool reduce_to_epsilon(model::node *node);
std::ostream &operator << (std::ostream &out, model::node const *__node);

extern world _G_system;
extern FILE *file;

#endif // KDEV_PG_H
