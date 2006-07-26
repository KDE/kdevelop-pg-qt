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
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
  model::plus_item *plus(model::node *item);
  model::star_item *star(model::node *item);
  model::symbol_item *symbol(char const *name);
  model::action_item *action(model::node *item, char const *code);
  model::alternative_item *alternative(model::node *left, model::node *right);
  model::cons_item *cons(model::node *left, model::node *right);
  model::evolve_item *evolve(
      model::node *item, model::symbol_item *symbol,
      model::variable_declaration_item *declarations, char const *code
  );
  model::recovery_item *recovery(model::node *item);
  model::alias_item *alias(char const *code, model::symbol_item *symbol);
  model::terminal_item *terminal(char const *name, char const *description);
  model::nonterminal_item *nonterminal(model::symbol_item *symbol, char const *arguments);
  model::condition_item *condition(char const *code, model::node *item);
  model::annotation_item *annotation(
      char const *name, model::node *item, bool is_sequence,
      model::variable_declaration_item::storage_type_enum storage_type
  );
  model::variable_declaration_item *variable_declaration(
      model::variable_declaration_item::declaration_type_enum declaration_type,
      model::variable_declaration_item::storage_type_enum     storage_type,
      model::variable_declaration_item::variable_type_enum    variable_type,
      bool is_sequence, char const* name, char const *type
  );
  settings::member_item *member(settings::member_item::member_kind_enum kind, char const *code);
} // namespace pg

struct world
{
  typedef struct member_code {
    std::deque<settings::member_item*> declarations;
    std::deque<settings::member_item*> constructor_code;
    std::deque<settings::member_item*> destructor_code;
  };
  typedef std::set<model::node*> node_set;
  typedef std::map<std::string, model::symbol_item*> symbol_set;
  typedef std::map<std::string, model::terminal_item*> terminal_set;
  typedef std::multimap<model::symbol_item*, model::evolve_item*> environment;
  typedef std::multimap<std::string, std::string> namespace_set;

  typedef std::map<std::pair<model::node*, int>, node_set> first_set;
  typedef std::map<std::pair<model::node*, int>, node_set> follow_set;

  world()
    : token_stream("kdev_pg_token_stream"), decl(0), bits(0), generate_ast(true),
      start(0), _M_zero(0), adapt_to_kdevelop(false)
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

  model::terminal_item *terminal(char const *__name)
  {
    std::string name = __name;
    terminal_set::iterator it = terminals.find(name);
    if (it == terminals.end())
      return pg::terminal(__name, __name);

    return (*it).second;
  }

  void push_rule(model::node *rule)
  {
    model::evolve_item *e = node_cast<model::evolve_item*>(rule);
    assert(e != 0);

    if (rules.empty())
      start = e;
    rules.push_back(e);
  }

  void push_namespace(char const *name, char const *code)
  {
    namespaces.insert(std::make_pair(name, code));
  }

  void *push_parserclass_member(model::node *member)
  {
    settings::member_item *m = node_cast<settings::member_item*>(member);
    assert(m != 0);

    if (m->_M_member_kind == settings::member_item::constructor_code)
      parserclass_members.constructor_code.push_back(m);
    else if (m->_M_member_kind == settings::member_item::destructor_code)
      parserclass_members.destructor_code.push_back(m);
    else // public, protected or private declaration
      parserclass_members.declarations.push_back(m);
  }

  model::terminal_item *push_terminal(char const *__name, char const *__description)
  {
    std::string name = __name;
    terminal_set::iterator it = terminals.find(name);
    if (it == terminals.end())
      it = terminals.insert(std::make_pair(name, pg::terminal(__name, __description))).first;

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
  namespace_set namespaces;
  member_code parserclass_members;

  environment env;

  bool adapt_to_kdevelop;

private:
  first_set FIRST_K;
  follow_set FOLLOW_K;
};

bool reduces_to_epsilon(model::node *node);
bool is_zero(model::node *node);
std::ostream &operator << (std::ostream &out, model::node const *__node);

extern world _G_system;
extern FILE *file;

#endif // KDEV_PG_H
