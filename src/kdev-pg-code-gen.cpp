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
#include "kdev-pg-code-gen.h"

#include <list>
#include <stack>
#include <iostream>
#include <cassert>

namespace
{
  void gen_condition(world::node_set const &s, std::ostream &out)
  {
    bool initial = true;

    world::node_set::iterator it = s.begin();
    while (it != s.end())
      {
        model::node *item = *it++;

        if (model::terminal_item *t = node_cast<model::terminal_item*>(item))
          {
            if (!initial)
              out << std::endl << "|| ";

            out << "yytoken == Token_" << t->_M_name;
            initial = false;
          }
      }

    if (initial && s.find(_G_system.zero()) != s.end())
      out << "true /*epsilon*/";
  }

  void gen_test_condition(model::node *node, std::ostream &out)
  {
    world::node_set s = _G_system.FIRST(node);
    if (reduce_to_epsilon(node))
      s.insert(_G_system.FOLLOW(node).begin(), _G_system.FOLLOW(node).end());

    gen_condition(s, out);
  }

  std::string gen_parser_call(model::symbol_item *node, char const *parser, std::ostream &out)
  {
    static int __id = 0;
    static char __var[1024];

    if (_G_system.generate_ast)
      {
        sprintf(__var, "__node_%d", __id++);

        out << node->_M_name << "_ast *" << __var << " = 0;" << std::endl
            << "if (!parse_" << node->_M_name << "(&" << __var << "))"
            << "{ return yy_expected_symbol(" << parser << "_ast_node::Kind_" << node->_M_name << ", \"" << node->_M_name << "\"" << "); }"
            << std::endl;
      }
    else
      {
        out << "if (!parse_" << node->_M_name << "())"
            << "{ return yy_expected_symbol(" << parser << "_ast_node::Kind_" << node->_M_name << ", \"" << node->_M_name << "\"" << "); }"
            << std::endl;
      }

    return __var;
  }


} // namespace

void code_generator::operator()(model::node *node)
{
  visit_node(node);
}

void code_generator::visit_zero(model::zero_item *node)
{
  // out << " /* nothing to do */" << std::endl;
}

void code_generator::visit_symbol(model::symbol_item *node)
{
  gen_parser_call(node, parser, out);
}

void code_generator::visit_terminal(model::terminal_item *node)
{
  out << "if (yytoken != Token_" << node->_M_name << ")"
      << "return yy_expected_token(yytoken, Token_" << node->_M_name << ", \"" << node->_M_name << "\");"
      << std::endl
      << "yylex();" << std::endl;
}

void code_generator::visit_bang(model::bang_item *node)
{
  out << "while (";
  gen_test_condition(node, out);
  out << ") {" << std::endl;
  visit_node(node->_M_item);
  out << "}" << std::endl;
}

void code_generator::visit_action(model::action_item *node)
{
  default_visitor::visit_action(node);
  out << node->_M_code;
}

void code_generator::visit_condition(model::condition_item *node)
{
  default_visitor::visit_condition(node);
}

void code_generator::visit_alternative(model::alternative_item *node)
{
  std::list<model::node*> top_level_nodes;

  std::stack<model::node*> working_list;
  working_list.push(node->_M_right);
  working_list.push(node->_M_left);

  while (!working_list.empty())
    {
      model::node *n = working_list.top();
      working_list.pop();

      if (model::alternative_item *a = node_cast<model::alternative_item*>(n))
        {
          working_list.push(a->_M_right);
          working_list.push(a->_M_left);
        }
      else
        {
          top_level_nodes.push_back(n);
        }
    }

  std::list<model::node*>::iterator it = top_level_nodes.begin();
  while (it != top_level_nodes.end())
    {
      model::node *n = *it++;
      model::condition_item *cond = node_cast<model::condition_item*>(n);

      out << "if (";

      if (cond)
        out << "(" << cond->_M_code << ") && (";

      gen_test_condition(n, out);

      if (cond)
        out << ")";

      out << ") {" << std::endl;
      visit_node(n);
      out << "}";

      if (it != top_level_nodes.end())
        out << "else ";
      else
        {
          out << "else {" << std::endl
              << "  return false;" << std::endl
              << "}" << std::endl;
        }
    }
}

void code_generator::visit_cons(model::cons_item *node)
{
  default_visitor::visit_cons(node);
}

void code_generator::visit_evolve(model::evolve_item *node)
{
  out << "if (";

  model::condition_item *cond = node_cast<model::condition_item*>(node->_M_item);

  if (cond)
    out << "(" << cond->_M_code << " && ";

  gen_test_condition(node, out);

  if (reduce_to_epsilon(node->_M_item))
    {
      out << " || ";
      gen_condition(_G_system.FOLLOW(node->_M_symbol), out);
    }

  if (cond)
    out << ")";

  out << ") {" << std::endl;

  out << node->_M_code;

  visit_node(node->_M_item);

  if (node == _G_system.start)
    out << "if (Token_EOF != yytoken) { return false; }" << std::endl;

  out << "}" << std::endl;
}

void code_generator::visit_alias(model::alias_item *node)
{
  assert(0); // ### not implemented yet
}

void code_generator::visit_annotation(model::annotation_item *node)
{
  if (!_G_system.generate_ast)
    {
      // std::cerr << "** WARNING annotation ignored" << std::endl;
      visit_node(node->_M_item);
      return;
    }

  if (model::terminal_item *t = node_cast<model::terminal_item*>(node->_M_item))
    {
      out << "if (yytoken != Token_" << t->_M_name << ") "
          << "return yy_expected_token(yytoken, Token_" << t->_M_name << ", \"" << t->_M_name << "\");"
          << std::endl;

      if (node->_M_sequence)
        {
          std::string target;

          if (!node->_M_local)
            target += "(*yynode)->";

          target += node->_M_name;
          target += "_sequence";

          out << target << " = snoc(" << target << ", " << "token_stream->index() - 1, memory_pool);" << std::endl
              << "yylex();" << std::endl;
        }
      else
        {
          out << "(*yynode)->" << node->_M_name << " = token_stream->index() - 1;" << std::endl
              << "yylex();" << std::endl;
        }
    }
  else if (model::symbol_item *s = node_cast<model::symbol_item*>(node->_M_item))
    {
      if (node->_M_sequence)
        {
          std::string __var = gen_parser_call(s, parser, out);

          std::string target;
          if (!node->_M_local)
            target += "(*yynode)->";

          target += node->_M_name;
          target += "_sequence";

          out << target << " = " << "snoc(" << target << ", " << __var << ", memory_pool);" << std::endl;
        }
      else
        {
          std::string __var = gen_parser_call(s, parser, out);

          std::string target;
          if (!node->_M_local)
            target += "(*yynode)->";

          target += node->_M_name;

          out << target << " = " << __var << ";" << std::endl;
        }
    }
  else
    assert(0); // ### not supported
}


void gen_forward_parser_rule::operator()(std::pair<std::string, model::symbol_item*> const &__it)
{
  model::symbol_item *sym = __it.second;
  out << "bool" << " " << "parse_" << sym->_M_name << "(";
  if (_G_system.generate_ast)
    {
      out << sym->_M_name << "_ast **yynode";
    }
  out << ");" << std::endl;
}

void gen_parser_rule::operator()(std::pair<std::string, model::symbol_item*> const &__it)
{
  model::symbol_item *sym = __it.second;
  code_generator cg(out, parser);

  out << "bool" << " " << parser << "::parse_" << sym->_M_name << "(";
  if (_G_system.generate_ast)
    {
      out << sym->_M_name << "_ast **yynode";
    }
  out << ")" << std::endl
      << "{" << std::endl;

  if (_G_system.generate_ast)
    {
      out << "*yynode = create<" << sym->_M_name << "_ast" << ">();" << std::endl << std::endl
          << "(*yynode)->start_token = token_stream->index() - 1;" << std::endl
          << std::endl;
    }

  world::environment::iterator it = _G_system.env.find(sym);
  bool initial = true;
  while (it != _G_system.env.end())
    {
      model::evolve_item *e = (*it).second;
      if ((*it).first != sym)
        break;

      ++it;

      if (!initial)
        out << "else ";

      cg(e);
      initial = false;
    }

  out << "else" << std::endl << "{ return false; }" << std::endl
      << std::endl;


  if (_G_system.generate_ast)
    {
      out << "(*yynode)->end_token = token_stream->index() - 1;" << std::endl
          << std::endl;
    }

  out << "return true;" << std::endl
      << "}" << std::endl
      << std::endl;
}

void gen_token::operator()(std::pair<std::string, model::terminal_item*> const &__it)
{
  model::terminal_item *t = __it.second;
  out << "Token_" << t->_M_name << " = " << _M_token_value++ << "," << std::endl;
}

void generate_parser_decls::operator()()
{
  if (_G_system.decl)
    out << _G_system.decl << std::endl;

  out << "class " << parser << "{"
      << "public:" << std::endl
      << "typedef " << _G_system.token_stream << " token_stream_type;" << std::endl
      << "typedef " << _G_system.token_stream << "::token_type token_type;" << std::endl
      << _G_system.token_stream << " *token_stream;" << std::endl
      << "int yytoken;" << std::endl
      << std::endl
      << "inline token_type LA(std::size_t k = 1) const" << std::endl
      << "{ return token_stream->token(token_stream->index() - 1 + k - 1); }"
      << std::endl
      << "inline int yylex() {"
      << "return (yytoken = token_stream->next_token());" << std::endl
      << "}" << std::endl
      << std::endl;

  out << "// token stream" << std::endl
      << "void set_token_stream(" << _G_system.token_stream << " *s)" << std::endl
      << "{ token_stream = s; }" << std::endl
      << std::endl;

  out << "// error recovery" << std::endl
      << "bool yy_expected_symbol(int kind, char const *name);" << std::endl
      << "bool yy_expected_token(int kind, std::size_t token, char const *name);" << std::endl
      << std::endl;

    if (_G_system.generate_ast)
      {
        out << "// memory pool" << std::endl
            << "typedef kdev_pg_memory_pool memory_pool_type;" << std::endl
            << std::endl
            << "kdev_pg_memory_pool *memory_pool;" << std::endl
            << "void set_memory_pool(kdev_pg_memory_pool *p)" << std::endl
            << "{ memory_pool = p; }" << std::endl
            << "template <class T>" << std::endl
            << "inline T *create()" << std::endl
            << "{" << std::endl
            << "T *node = new (memory_pool->allocate(sizeof(T))) T();" << std::endl
            << "node->kind = T::KIND;" << std::endl
            << "return node;" << std::endl
            << "}" << std::endl << std::endl;
      }


  out << "enum token_type_enum" << std::endl << "{" << std::endl;
  std::for_each(_G_system.terminals.begin(), _G_system.terminals.end(), gen_token(out));
  out << "token_type_size" << std::endl
      << "}; // token_type_enum" << std::endl
      << std::endl;

  out << parser << "()" << "{" << std::endl;
  if (_G_system.generate_ast)
    {
      out << "memory_pool = 0;" << std::endl;
    }

  out << "token_stream = 0;" << std::endl
      << "yytoken = Token_EOF;" << std::endl
      << "}" << std::endl << std::endl;

  std::for_each(_G_system.symbols.begin(), _G_system.symbols.end(), gen_forward_parser_rule(out));
  out << "};" << std::endl;
}

void generate_parser_bits::operator()()
{
  if (_G_system.bits)
    out << _G_system.bits << std::endl;

  std::for_each(_G_system.symbols.begin(), _G_system.symbols.end(), gen_parser_rule(out, parser));
}

