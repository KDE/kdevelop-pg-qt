/* This file is part of kdev-pg-qt
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
#include "kdev-pg-inline-checker.h"
#include "kdev-pg-generate.h"
#include "kdev-pg-regexp.h"

#include <QtCore/QFile>
#include <QtCore/QStringList>
#include <QtCore/QCoreApplication>
#include <QtCore/QFileInfo>

namespace KDevPG
{
  extern QTextStream checkOut;
}

int yyparse();

void usage()
{
  KDevPG::checkOut << "Usage: kdev-pg-qt [further-options] --output=<name> [further-options] file.g" << endl;
}

void help()
{
  usage();
  KDevPG::checkOut
           << "Options:" << endl
           << "\t--output=<name> - Specify a prefix for all generated files" << endl
           << "\t--namespace=<NameSpaceName> - Specify the namespace for all generated classes (default: the prefix)" << endl
           << "\t--debug-visitor - Generate a visitor to dump the parse-tree" << endl
           << "\t--serialize-visitor - Generate a visitor to store the parse-tree in a QTextStream" << endl
           << "\t--no-ast - Do not generate any AST-files" << endl
           << "\t--terminals - Save a list of all terminals in a file named \"kdev-pg-terminals\"" << endl
           << "\t--symbols - Save a list of all non-terminals in a file named \"kdev-pg-symbols\"" << endl
           << "\t--rules - Save debugging-information for all rules in a file named \"kdev-pg-rules\"" << endl
           << "\t--token-text - Generate a function converting the number of a token into its name" << endl
           << "\t--permissive-conflicts - The default, conflicts are shown, but kdev-pg-qt will continue" << endl
           << "\t--strict-conflicts - Quit after having detected conflicts" << endl
           << "\t--ignore-conflicts - Do not perform conflict-checking" << endl
           << "\t--new-visitor=VisitorName - Create a new empty visitor" << endl
           << "\t--inherit-default-visitor - Use the DefaultVisitor to visit sub-nodes" << endl
           << "\t--inherit-abstract-visitor - Reimplement the functionality of the DefaultVisitor" << endl
           << "\t--with-parser - The default, a parser will be generated" << endl
           << "\t--no-parser - Do not create the parser, asts, built-in-visitors etc." << endl
           << "\t--error-aware-code - Line-numbers in parser.cpp related compiler-messages will correspond to line-numbers in the grammar-file (default)" << endl
           << "\t--beautiful-code - Line-numbers in compiler-messages will be arbitrary, but the code will look more beautiful and it is probably more compiler-independent" << endl
           << "\t--visitor-table - Visit::visitNode will be implemented by using a lookup-array" << endl
           << "\t--visitor-switch - Visitor::visitNode will use a switch-statement" << endl
           << "\t--help - Show this messages" << endl
           << "\t--usage - Show usage" << endl
           << "\t--version - Show version" << endl
           << "\t--author - Show authors" << endl << endl
           << "See http://techbase.kde.org/Development/KDevelop-PG-Qt_Introduction for further aid." << endl;

  exit(EXIT_SUCCESS);
}

void version()
{
  KDevPG::checkOut << "KDevelop-PG-Qt: pre1.0" << endl;
  
  exit(EXIT_SUCCESS);
}

void author()
{
  KDevPG::checkOut << QString::fromUtf8("KDevelop-PG-Qt: Copyright © 2005-2010 by the KDevelop-PG-Qt developers:") << endl
    << QString::fromUtf8("\tRoberto Raggi\n"
       "\tJakob Petsovits\n"
       "\tAndreas Pakulat\n"
       "\tJonathan Schmidt-Dominé\n"
       "\t...and others") << endl;

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
    for (it = KDevPG::globalSystem.first(e).begin(); it != KDevPG::globalSystem.first(e).end(); ++it)
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
         it != KDevPG::globalSystem.follow(e->mSymbol).end(); ++it)
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

namespace KDevPG
{
    QFileInfo fileInfo;
}

int main(int argc, char **argv)
{
  bool dump_terminals = false;
  bool dump_symbols = false;
  bool generate_parser = true;
  bool DebugRules = false;
  bool inherit_default = false;
  QString new_visitor;

  QCoreApplication app(argc, argv);

  QStringList args = QCoreApplication::arguments();
  args.pop_front();
  foreach(const QString& arg, args)
  {
    #define SW(str) arg.startsWith(QLatin1String(#str))
    if (SW(--output=))
    {
      KDevPG::globalSystem.language = arg.mid( 9 );
    }
    else if (SW(--namespace=))
    {
      KDevPG::globalSystem.ns = arg.mid( 12 );
    }
    else if (arg == "--no-ast")
    {
      KDevPG::globalSystem.generateAst = false;
    }
    else if (arg == "--serialize-visitor")
    {
      KDevPG::globalSystem.generateSerializeVisitor = true;
    }
    else if (arg == "--ignore-conflicts")
    {
      KDevPG::globalSystem.conflictHandling = KDevPG::World::Ignore;
    }
    else if (arg == "--strict-conflicts")
    {
      KDevPG::globalSystem.conflictHandling = KDevPG::World::Strict;
    }
    else if (arg == "--permissive-conflicts")
    {
      KDevPG::globalSystem.conflictHandling = KDevPG::World::Permissive;
    }
    else if (arg == "--debug-visitor")
    {
      KDevPG::globalSystem.generateDebugVisitor = true;
    }
    else if (arg == "--token-text")
    {
      KDevPG::globalSystem.generateTokenText = true;
    }
    else if (arg == "--no-parser")
    {
      generate_parser = false;
    }
    else if (arg == "--with-parser")
    {
      generate_parser = true;
    }
    else if (arg == "--beautiful-code")
    {
      KDevPG::globalSystem.beautifulCode = true;
    }
    else if (arg == "--error-aware-code")
    {
      KDevPG::globalSystem.beautifulCode = false;
    }
    else if (arg == "--visitor-table")
    {
      KDevPG::globalSystem.visitorTable = true;
    }
    else if (arg == "--visitor-switch")
    {
      KDevPG::globalSystem.visitorTable = false;
    }
    else if (SW(--new-visitor=))
    {
      new_visitor = arg.mid( 14 );
      KDevPG::globalSystem.conflictHandling = KDevPG::World::Ignore;
      generate_parser = false;
    }
    else if (arg == "--inherit-default-visitor")
    {
      inherit_default = true;
    }
    else if (arg == "--inherit-abstract-visitor")
    {
      inherit_default = false;
    }
    else if (arg == "--help")
    {
      help();
    }
    else if (arg == "--version")
    {
      version();
    }
    else if (arg == "--author")
    {
      author();
    }
    else if (arg == "--usage")
    {
      usage();
      exit(EXIT_SUCCESS);
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
          KDevPG::checkOut << "kdev-pg-qt: file ``" << arg
                    << "'' not found!" << endl;
          KDevPG::file.setFileName("");
        }
      else
          KDevPG::fileInfo.setFile(KDevPG::file);
    }
    else
    {
      KDevPG::checkOut << "kdev-pg-qt: unknown option ``" << arg << "''"
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

  KDevPG::globalSystem.finishedParsing();
  
  if(KDevPG::globalSystem.start.empty())
    KDevPG::checkOut << "** WARNING could not detect a start-symbol, every symbol gets reused, you have to care about EOFs yourself!" << endl;
  
  for(QList<KDevPG::Model::EvolveItem*>::iterator it = KDevPG::globalSystem.rules.begin(); it != KDevPG::globalSystem.rules.end(); ++it)
  {
    KDevPG::InlineChecker check;
    check(*it);
  }
  
  for(QList<KDevPG::Model::EvolveItem*>::iterator it = KDevPG::globalSystem.rules.begin(); it != KDevPG::globalSystem.rules.end(); ++it)
  {
    KDevPG::InitializeEnvironment initenv;
    initenv(*it);
  }

  for(QList<KDevPG::Model::EvolveItem*>::iterator it = KDevPG::globalSystem.rules.begin(); it != KDevPG::globalSystem.rules.end(); ++it)
  {
    KDevPG::EmptyOperatorChecker check;
    check(*it);
  }

  KDevPG::computeFirst();
  KDevPG::computeFollow();

  if(KDevPG::globalSystem.conflictHandling != KDevPG::World::Ignore)
  {
    for(QList<KDevPG::Model::EvolveItem*>::iterator it = KDevPG::globalSystem.rules.begin(); it != KDevPG::globalSystem.rules.end(); ++it)
    {
      KDevPG::FirstFollowConflictChecker check;
      check(*it);
    }

    for(QList<KDevPG::Model::EvolveItem*>::iterator it = KDevPG::globalSystem.rules.begin(); it != KDevPG::globalSystem.rules.end(); ++it)
    {
      KDevPG::FirstFirstConflictChecker check;
      check(*it);
    }
  }
    
  for(QList<KDevPG::Model::EvolveItem*>::iterator it = KDevPG::globalSystem.rules.begin(); it != KDevPG::globalSystem.rules.end(); ++it)
  {
    KDevPG::EmptyFirstChecker check;
    check(*it);
  }
  
  for(QList<KDevPG::Model::EvolveItem*>::iterator it = KDevPG::globalSystem.rules.begin(); it != KDevPG::globalSystem.rules.end(); ++it)
  {
    KDevPG::EmptyOperatorChecker check;
    check(*it);
  }

  for(QList<KDevPG::Model::EvolveItem*>::iterator it = KDevPG::globalSystem.rules.begin(); it != KDevPG::globalSystem.rules.end(); ++it)
  {
    KDevPG::UndefinedSymbolChecker check;
    check(*it);
  }

  for(QList<KDevPG::Model::EvolveItem*>::iterator it = KDevPG::globalSystem.rules.begin(); it != KDevPG::globalSystem.rules.end(); ++it)
  {
    KDevPG::UndefinedTokenChecker check;
    check(*it);
  }

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
      for(QList<KDevPG::Model::EvolveItem*>::iterator it = KDevPG::globalSystem.rules.begin(); it != KDevPG::globalSystem.rules.end(); ++it)
      {
        DebugRule dr(strm);
        dr(*it);
      }
    }
    
  QFile flex("lexer.cpp");
  flex.open( QIODevice::WriteOnly | QIODevice::Truncate );
  QTextStream strm(&flex);
  KDevPG::GNFA gnfa(KDevPG::globalSystem.lexerEnvs[""]);
  KDevPG::GDFA gdfa = gnfa.dfa();
  gdfa.codegen(strm);
  
  KDevPG::ProblemSummaryPrinter()();
  
  if (!(dump_terminals || dump_symbols || DebugRules) && KDevPG::globalSystem.language.isEmpty())
  {
    usage();
    exit(EXIT_FAILURE);
  }

  if (generate_parser)
    KDevPG::generateOutput();
  
  if (!new_visitor.isEmpty())
    KDevPG::generateVisitor(new_visitor, inherit_default);

  return EXIT_SUCCESS;
}

