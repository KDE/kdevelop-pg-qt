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

#include "kdev-pg.h"
#include "kdev-pg-ast.h"
#include "kdev-pg-visitor.h"
#include "kdev-pg-default-visitor.h"
#include "kdev-pg-pretty-printer.h"
#include "kdev-pg-environment.h"
#include "kdev-pg-first.h"
#include "kdev-pg-follow.h"
#include "kdev-pg-code-gen.h"
#include "kdev-pg-ast-gen.h"
#include "kdev-pg-visitor-gen.h"
#include "kdev-pg-visitor-bits-gen.h"
#include "kdev-pg-default-visitor-gen.h"
#include "kdev-pg-serialize-visitor-gen.h"
#include "kdev-pg-beautifier.h"
#include "kdev-pg-checker.h"

#include <iterator>
#include <algorithm>
#include <memory>

#include <iostream>
#include <sstream>
#include <fstream>

#include <cassert>
#include <cstdio>
#include <cstdlib>

int yyparse();

void usage()
{
  std::cerr << "usage: kdev-pg --output=<name> file.g" << std::endl;
  exit(EXIT_SUCCESS);
}

struct debug_rule
{
  std::ostream &out;

  debug_rule(std::ostream &o): out(o)
  {}

  void operator()(model::node *node)
  {
    model::evolve_item *e = node_cast<model::evolve_item*>(node);

    out << std::endl;
    pretty_printer p(out);
    p(e);

    bool initial = true;
    world::node_set::iterator it;

    out << std::endl;
    out << " FIRST:[";
    for (it = _G_system.FIRST(e).begin(); it != _G_system.FIRST(e).end(); it++)
      {
        if (!initial)
          out << ",";

        p(*it);
        initial = false;
      }
    out << "]";

    initial = true;

    out << std::endl;
    out << " FOLLOW:[";
    for (it = _G_system.FOLLOW(e->_M_symbol).begin();
         it != _G_system.FOLLOW(e->_M_symbol).end(); it++)
      {
        if (!initial)
          out << ",";

        p(*it);
        initial = false;
      }
    out << "]";
    out << std::endl;
  }
};

int main(int, char *argv[])
{
  bool gen_serialize_visitor = false;
  bool dump_terminals = false;
  bool dump_symbols = false;
  bool debug_rules = false;
  char const *parser = 0;

  file = stdin;

  while (char const *arg = *++argv)
    {
      if (!strncmp(arg, "--output=", 9))
        {
          parser = arg + 9;
        }
      else if (!strcmp("--no-ast", arg))
        {
          _G_system.generate_ast = false;
        }
      else if (!strcmp("--serialize-visitor", arg))
        {
          gen_serialize_visitor = true;
        }
      else if (!strcmp("--help", arg))
        {
          usage();
        }
      else if (!strcmp("--terminals", arg))
        {
          dump_terminals = true;
        }
      else if (!strcmp("--symbols", arg))
        {
          dump_symbols = true;
        }
      else if (!strcmp("--rules", arg))
        {
          debug_rules = true;
        }
      else if (!strncmp(arg, "--adapt-to=", 11))
        {
          char const *adapt_to = arg + 11;
          _G_system.adapt_to_kdevelop = (strcmp("kdevelop", adapt_to) == 0);
        }
      else if (file == stdin)
        {
          file = fopen(arg, "r");

          if (!file)
            {
              std::cerr << "kdev-pg: file ``" << arg
                        << "'' not found!" << std::endl;
              file = stdin;
            }
        }
      else
        {
          std::cerr << "kdev-pg: unknown option ``" << arg << "''"
                    << std::endl;
        }
    }

  yyparse();

  fclose(file);

  std::for_each(_G_system.rules.begin(), _G_system.rules.end(),
                initialize_environment());

  compute_FIRST();
  compute_FOLLOW();

  std::for_each(_G_system.rules.begin(), _G_system.rules.end(),
                FIRST_FOLLOW_conflict_checker());

  std::for_each(_G_system.rules.begin(), _G_system.rules.end(),
                FIRST_FIRST_conflict_checker());

  std::for_each(_G_system.rules.begin(), _G_system.rules.end(),
                empty_FIRST_checker());

  std::for_each(_G_system.rules.begin(), _G_system.rules.end(),
                undefined_symbol_checker());

  std::for_each(_G_system.rules.begin(), _G_system.rules.end(),
                undefined_token_checker());

  problem_summary_printer()();

  if (dump_terminals)
    {
      for (world::terminal_set::iterator it = _G_system.terminals.begin();
           it != _G_system.terminals.end(); ++it)
        {
          std::cout << (*it).first << std::endl;
        }
      return EXIT_SUCCESS;
    }
  else if (dump_symbols)
    {
      for (world::symbol_set::iterator it = _G_system.symbols.begin();
           it != _G_system.symbols.end(); ++it)
        {
          std::cout << (*it).first << std::endl;
        }
      return EXIT_SUCCESS;
    }
  else if (debug_rules)
    {
      std::for_each(_G_system.rules.begin(), _G_system.rules.end(),
                    debug_rule(std::cout));
      return EXIT_SUCCESS;
    }
  else if (!parser)
    {
      usage();
    }

  { // generate the decls
    std::stringstream s;

    generate_ast __ast(s);
    generate_parser_decls __decls(s);
    generate_visitor __visitor(s);
    generate_default_visitor __default_visitor(s);

    s << "// THIS FILE IS GENERATED" << std::endl
      << "// WARNING! All changes made in this file will be lost!" << std::endl
      << std::endl;

    s << "#ifndef " << parser << "_H_INCLUDED" << std::endl
      << "#define " << parser << "_H_INCLUDED" << std::endl
      << std::endl;

    if (_G_system.generate_ast)
      {
        s << "#include \"kdev-pg-memory-pool.h\"" << std::endl
          << "#include \"kdev-pg-allocator.h\"" << std::endl
          << "#include \"kdev-pg-list.h\"" << std::endl;
      }

    if (!strcmp(_G_system.token_stream, "kdev_pg_token_stream"))
      s << "#include \"kdev-pg-token-stream.h\"" << std::endl;

    if (_G_system.adapt_to_kdevelop)
      {
        s << std::endl
          << "#include <kdevast.h>" << std::endl
          << std::endl;
      }

    s << "#include <cassert>" << std::endl
      << std::endl;

    if (_G_system.decl)
      s << _G_system.decl << std::endl;

    if (_G_system.generate_ast)
      {
        s << "namespace " << parser << "{" << std::endl
          << std::endl;

        __ast();

        s << std::endl << "} // end of namespace " << parser << std::endl
          << std::endl;
      }

    s << "namespace " << parser << "{" << std::endl
      << std::endl;

    __decls();

    if (_G_system.generate_ast)
      {
        __visitor();
        __default_visitor();
      }

    s << std::endl << "} // end of namespace " << parser << std::endl
      << std::endl;

    s << "#endif" << std::endl << std::endl;

    std::string oname = parser;
    oname += ".h";

    std::ofstream ofile;
    ofile.open(oname.c_str(), std::ios::out);
    format(s, ofile);
  }

  if (gen_serialize_visitor)
  { // generate the serialization visitor
    std::stringstream s;

    generate_serialize_visitor __serialize_visitor(s);

    s << "// THIS FILE IS GENERATED" << std::endl
      << "// WARNING! All changes made in this file will be lost!" << std::endl
      << std::endl;

    s << "#ifndef " << parser << "_SERIALIZATION_H_INCLUDED" << std::endl
      << "#define " << parser << "_SERIALIZATION_H_INCLUDED" << std::endl
      << std::endl;

    s << "#include \"" << parser << ".h\"" << std::endl
      << std::endl;

    s << "#include <iostream>" << std::endl
      << "#include <fstream>" << std::endl
      << std::endl;

    s << "namespace " << parser << "{" << std::endl
      << std::endl;

    __serialize_visitor();

    s << std::endl << "} // end of namespace " << parser << std::endl
      << std::endl;

    s << "#endif" << std::endl << std::endl;

    std::string oname = parser;
    oname += "_serialize_visitor.h";

    std::ofstream ofile;
    ofile.open(oname.c_str(), std::ios::out);
    format(s, ofile);
  }

  { // generate the bits
    std::stringstream s;

    s << "// THIS FILE IS GENERATED" << std::endl
      << "// WARNING! All changes made in this file will be lost!" << std::endl
      << std::endl;

    s << "#include \"" << parser << ".h\"" << std::endl
      << std::endl;

    if (_G_system.bits)
      s << _G_system.bits << std::endl;

    s << "namespace " << parser << "{" << std::endl
      << std::endl;

    generate_parser_bits __bits(s);
    generate_visitor_bits __visitor_bits(s);

    __bits();

    if (_G_system.generate_ast)
      {
        __visitor_bits();
      }

    s << std::endl << "} // end of namespace " << parser << std::endl
      << std::endl;

    std::string oname = parser;
    oname += ".cpp";

    std::ofstream ofile;
    ofile.open(oname.c_str(), std::ios::out);
    format(s, ofile);
  }

  return EXIT_SUCCESS;
}

