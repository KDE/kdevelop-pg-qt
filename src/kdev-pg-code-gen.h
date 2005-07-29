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

#ifndef KDEV_PG_CODEGEN_H
#define KDEV_PG_CODEGEN_H

#include "kdev-pg-default-visitor.h"

class code_generator: protected default_visitor
{
  std::ostream &out;
  char const *parser;

public:
  code_generator(std::ostream &o, char const *p): out(o), parser(p)
  {}

  void operator()(model::node *node);

protected:
  virtual void visit_zero(model::zero_item *node);
  virtual void visit_symbol(model::symbol_item *node);
  virtual void visit_terminal(model::terminal_item *node);
  virtual void visit_bang(model::bang_item *node);
  virtual void visit_action(model::action_item *node);
  virtual void visit_alternative(model::alternative_item *node);
  virtual void visit_cons(model::cons_item *node);
  virtual void visit_evolve(model::evolve_item *node);
  virtual void visit_alias(model::alias_item *node);
  virtual void visit_annotation(model::annotation_item *node);
  virtual void visit_condition(model::condition_item *node);
};

class gen_forward_parser_rule
{
  std::ostream &out;

public:
  gen_forward_parser_rule(std::ostream &o): out(o)
  {}

  void operator()(std::pair<std::string, model::symbol_item*> const &__it);
};

class gen_parser_rule
{
  std::ostream &out;
  char const *parser;

public:
  gen_parser_rule(std::ostream &o, char const *p): out(o), parser(p)
  {}

  void operator()(std::pair<std::string, model::symbol_item*> const &__it);
};

class gen_token
{
  std::ostream &out;
  int _M_token_value;

public:
  gen_token(std::ostream &o): out(o), _M_token_value(1000)
  {}

  void operator()(std::pair<std::string, model::terminal_item*> const &__it);
};

class generate_parser_decls
{
  std::ostream &out;
  char const *parser;

public:
  generate_parser_decls(std::ostream &o, char const *p): out(o), parser(p)
  {}

  void operator()();
};

class generate_parser_bits
{
  std::ostream &out;
  char const *parser;

public:
  generate_parser_bits(std::ostream &o, char const *p): out(o), parser(p)
  {}

  void operator()();
};

#endif // KDEV_PG_CODEGEN_H
