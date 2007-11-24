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
#include "kdev-pg-checker.h"
#include "kdev-pg-generate.h"

#include <iterator>
#include <algorithm>
#include <memory>

#include <iostream>
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

class DebugRule
{
public:
  std::ostream &out;

  DebugRule(std::ostream &o): out(o)
  {}

  void operator()(KDevPG::Model::Node *node)
  {
    KDevPG::Model::EvolveItem *e = KDevPG::nodeCast<KDevPG::Model::EvolveItem*>(node);

    out << std::endl;
    KDevPG::PrettyPrinter p(out);
    p(e);

    bool initial = true;
    KDevPG::World::NodeSet::iterator it;

    out << std::endl;
    out << " FIRST:[";
    for (it = globalSystem.first(e).begin(); it != globalSystem.first(e).end(); it++)
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
    for (it = globalSystem.follow(e->mSymbol).begin();
         it != globalSystem.follow(e->mSymbol).end(); it++)
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
  bool dump_terminals = false;
  bool dump_symbols = false;
  bool DebugRules = false;

  file = stdin;

  while (char const *arg = *++argv)
    {
      if (!strncmp(arg, "--output=", 9))
        {
          globalSystem.language = arg + 9;
        }
      else if (!strncmp(arg,"--namespace=",12))
        {
          globalSystem.ns = arg + 12;
    }
      else if (!strcmp("--no-ast", arg))
        {
          globalSystem.GenerateAst = false;
        }
      else if (!strcmp("--serialize-visitor", arg))
        {
          globalSystem.generateSerializeVisitor = true;
        }
      else if (!strcmp("--debug-visitor", arg))
        {
          globalSystem.generateDebugVisitor = true;
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
          DebugRules = true;
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

  if( !globalSystem.ns )
    globalSystem.ns = globalSystem.language;

  yyparse();

  fclose(file);

  std::for_each(globalSystem.rules.begin(), globalSystem.rules.end(),
                KDevPG::InitializeEnvironment());

  KDevPG::computeFirst();
  KDevPG::computeFollow();

  std::for_each(globalSystem.rules.begin(), globalSystem.rules.end(),
                KDevPG::FirstFollowConflictChecker());

  std::for_each(globalSystem.rules.begin(), globalSystem.rules.end(),
                KDevPG::FirstFirstConflictChecker());

  std::for_each(globalSystem.rules.begin(), globalSystem.rules.end(),
                KDevPG::EmptyFirstChecker());

  std::for_each(globalSystem.rules.begin(), globalSystem.rules.end(),
                KDevPG::UndefinedSymbolChecker());

  std::for_each(globalSystem.rules.begin(), globalSystem.rules.end(),
                KDevPG::UndefinedTokenChecker());

  KDevPG::ProblemSummaryPrinter()();

  if (dump_terminals || dump_symbols || DebugRules)
    {
      if(dump_terminals)
        {
          std::ofstream ft("kdev-pg-terminals", std::ios_base::out | std::ios_base::trunc );
          for (KDevPG::World::TerminalSet::iterator it = globalSystem.terminals.begin();
               it != globalSystem.terminals.end(); ++it)
            {
              ft << (*it).first << std::endl;
            }
        }
      if (dump_symbols)
        {
          std::ofstream st("kdev-pg-symbols", std::ios_base::out | std::ios_base::trunc );
          for (KDevPG::World::SymbolSet::iterator it = globalSystem.symbols.begin();
               it != globalSystem.symbols.end(); ++it)
            {
              st << (*it).first << std::endl;
            }
        }
      if (DebugRules)
        {
          std::ofstream rt("kdev-pg-rules", std::ios_base::out | std::ios_base::trunc );
          std::for_each(globalSystem.rules.begin(), globalSystem.rules.end(),
                        DebugRule(rt));
        }
    }
  else if (!globalSystem.language)
    {
      usage();
    }

  KDevPG::generateOutput();

  return EXIT_SUCCESS;
}

