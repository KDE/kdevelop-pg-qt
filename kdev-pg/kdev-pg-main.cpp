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

#include <QtCore/QFile>
#include <QtCore/QStringList>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>



int yyparse();

void usage()
{
  qDebug() << "usage: kdev-pg --output=<name> file.g" << endl;
  exit(EXIT_SUCCESS);
}

class DebugRule
{
public:
  QTextStream& out;

  DebugRule(QTextStream& o): out(o)
  {}

  void operator()(KDevPG::Model::Node *node)
  {
    KDevPG::Model::EvolveItem *e = KDevPG::nodeCast<KDevPG::Model::EvolveItem*>(node);

    out << endl;
    KDevPG::PrettyPrinter p(out);
    p(e);

    bool initial = true;
    KDevPG::World::NodeSet::iterator it;

    out << endl;
    out << " FIRST:[";
    for (it = KDevPG::globalSystem.first(e).begin(); it != KDevPG::globalSystem.first(e).end(); it++)
      {
        if (!initial)
          out << ",";

        p(*it);
        initial = false;
      }
    out << "]";

    initial = true;

    out << endl;
    out << " FOLLOW:[";
    for (it = KDevPG::globalSystem.follow(e->mSymbol).begin();
         it != KDevPG::globalSystem.follow(e->mSymbol).end(); it++)
      {
        if (!initial)
          out << ",";

        p(*it);
        initial = false;
      }
    out << "]";
    out << endl;
  }
};

int main(int argc, char **argv)
{
  bool dump_terminals = false;
  bool dump_symbols = false;
  bool DebugRules = false;

  QCoreApplication app(argc, argv);

  QStringList args = QCoreApplication::arguments();
  args.pop_front();
  foreach(QString arg, args)
  {
    if (arg.startsWith("--output="))
    {
      KDevPG::globalSystem.language = arg.mid( 9 );
    }
    else if (arg.startsWith("--namespace="))
    {
      KDevPG::globalSystem.ns = arg.mid( 12 );
    }
    else if (arg == "--no-ast")
    {
      KDevPG::globalSystem.GenerateAst = false;
    }
    else if (arg == "--serialize-visitor")
    {
      KDevPG::globalSystem.generateSerializeVisitor = true;
    }
    else if (arg == "--debug-visitor")
    {
      KDevPG::globalSystem.generateDebugVisitor = true;
    }
    else if (arg == "--token-text")
    {
      KDevPG::globalSystem.generateTokenText = true;
    }
    else if (arg == "--help")
    {
      usage();
    }
    else if (arg == "--terminals")
    {
      dump_terminals = true;
    }
    else if (arg == "--symbols")
    {
      dump_symbols = true;
    }
    else if (arg == "--rules")
    {
      DebugRules = true;
    }
    else if (KDevPG::file.fileName().isEmpty())
    {
      KDevPG::file.setFileName(arg);

      if (!KDevPG::file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
          qDebug() << "kdev-pg-qt: file ``" << arg
                    << "'' not found!" << endl;
          KDevPG::file.setFileName("");
        }
    }
    else
    {
      qDebug() << "kdev-pg: unknown option ``" << arg << "''"
                << endl;
    }
    }

  if( KDevPG::globalSystem.ns.isEmpty() )
    KDevPG::globalSystem.ns = KDevPG::globalSystem.language;

  if( !KDevPG::file.isOpen() )
  {
    exit(1);
  }

  yyparse();

  KDevPG::file.close();

  for(QList<KDevPG::Model::Node*>::iterator it = KDevPG::globalSystem.rules.begin(); it != KDevPG::globalSystem.rules.end(); it++)
  {
    KDevPG::InitializeEnvironment initenv;
    initenv(*it);
  }

  KDevPG::computeFirst();
  KDevPG::computeFollow();

  for(QList<KDevPG::Model::Node*>::iterator it = KDevPG::globalSystem.rules.begin(); it != KDevPG::globalSystem.rules.end(); it++)
  {
    KDevPG::FirstFollowConflictChecker check;
    check(*it);
  }

  for(QList<KDevPG::Model::Node*>::iterator it = KDevPG::globalSystem.rules.begin(); it != KDevPG::globalSystem.rules.end(); it++)
  {
    KDevPG::FirstFirstConflictChecker check;
    check(*it);
  }

  for(QList<KDevPG::Model::Node*>::iterator it = KDevPG::globalSystem.rules.begin(); it != KDevPG::globalSystem.rules.end(); it++)
  {
    KDevPG::EmptyFirstChecker check;
    check(*it);
  }

  for(QList<KDevPG::Model::Node*>::iterator it = KDevPG::globalSystem.rules.begin(); it != KDevPG::globalSystem.rules.end(); it++)
  {
    KDevPG::UndefinedSymbolChecker check;
    check(*it);
  }

  for(QList<KDevPG::Model::Node*>::iterator it = KDevPG::globalSystem.rules.begin(); it != KDevPG::globalSystem.rules.end(); it++)
  {
    KDevPG::UndefinedTokenChecker check;
    check(*it);
  }

  KDevPG::ProblemSummaryPrinter()();

  if (dump_terminals || dump_symbols || DebugRules)
    {
      if(dump_terminals)
        {
          QFile ft("kdev-pg-terminals");
          ft.open( QIODevice::WriteOnly | QIODevice::Truncate );
          QTextStream strm(&ft);
          for (KDevPG::World::TerminalSet::iterator it = KDevPG::globalSystem.terminals.begin();
               it != KDevPG::globalSystem.terminals.end(); ++it)
            {
              strm << it.key() << endl;
            }
        }
      if (dump_symbols)
        {
          QFile ft("kdev-pg-symbols");
          ft.open( QIODevice::WriteOnly | QIODevice::Truncate );
          QTextStream strm(&ft);
          for (KDevPG::World::SymbolSet::iterator it = KDevPG::globalSystem.symbols.begin();
               it != KDevPG::globalSystem.symbols.end(); ++it)
            {
              strm << it.key() << endl;
            }
        }
      if (DebugRules)
        {
          QFile ft("kdev-pg-rules");
          ft.open( QIODevice::WriteOnly | QIODevice::Truncate );
          QTextStream strm(&ft);
          for(QList<KDevPG::Model::Node*>::iterator it = KDevPG::globalSystem.rules.begin(); it != KDevPG::globalSystem.rules.end(); it++)
          {
            DebugRule dr(strm);
            dr(*it);
          }
        }
    }
  else if (KDevPG::globalSystem.language.isEmpty())
    {
      usage();
    }

  KDevPG::generateOutput();

  return EXIT_SUCCESS;
}

