/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
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
#include <../kdevelop-pg-qt_version.h>

#include <QFile>
#include <QStringList>
#include <QCoreApplication>
#include <QRegularExpression>
#include <QFileInfo>

namespace KDevPG
{
  extern QTextStream checkOut;
}

int yyparse();

void usage()
{
  KDevPG::checkOut << "Usage: kdev-pg-qt [further-options] --output=<name> [further-options] <file.g>" << Qt::endl;
}

void help()
{
  usage();
  KDevPG::checkOut
           << "Options:" << Qt::endl
           << "\t--output=<name> - Specify a prefix for all generated files" << Qt::endl
           << "\t--namespace=<NameSpaceName> - Specify the namespace for all generated classes (default: the prefix)" << Qt::endl
           << "\t--no-output - Do not actually generate files" << Qt::endl
           << "Components:" << Qt::endl
           << "\t--debug-visitor - Generate a visitor to dump the parse-tree" << Qt::endl
           << "\t--serialize-visitor - Generate a visitor to store the parse-tree in a QTextStream" << Qt::endl
           << "\t--no-ast - Do not generate any AST-files" << Qt::endl
           << "\t--with-ast - Generate AST (default)" << Qt::endl
           << "\t--no-parser - Do not create the parser, built-in-visitors etc." << Qt::endl
           << "\t--with-parser - The default, a parser will be generated" << Qt::endl
           << "\t--no-lexer - Do not generate the lexer" << Qt::endl
           << "\t--with-lexer - Ensure lexer generation" << Qt::endl
           << "\t--token-text - Generate a function converting the number of a token into its name" << Qt::endl
           << "Informative output:" << Qt::endl
           << "\t--terminals - Save a list of all terminals in a file named \"kdev-pg-terminals\"" << Qt::endl
           << "\t--symbols - Save a list of all non-terminals in a file named \"kdev-pg-symbols\"" << Qt::endl
           << "\t--rules - Save debugging-information for all rules in a file named \"kdev-pg-rules\"" << Qt::endl
           << "\t--automata - Save DFAs for all used named regexps in \"kdev-pg-lexer-name-<name>.dot\" and for all states in \"kdev-pg-lexer-state-<name>.dot\"" << Qt::endl
           << "Error-handling:" << Qt::endl
           << "\t--permissive-conflicts - The default, conflicts are shown, but kdev-pg-qt will continue (default)" << Qt::endl
           << "\t--strict-conflicts - Quit after having detected conflicts" << Qt::endl
           << "\t--ignore-conflicts - Do not perform conflict-checking" << Qt::endl
           << "Visitor generation:" << Qt::endl
           << "\t--new-visitor=VisitorName - Create a new empty visitor" << Qt::endl
           << "\t--inherit-default-visitor - Use the DefaultVisitor to visit sub-nodes" << Qt::endl
           << "\t--inherit-abstract-visitor - Reimplement the functionality of the DefaultVisitor" << Qt::endl
           << "Output format:" << Qt::endl
           << "\t--error-aware-code - Line-numbers in parser.cpp related compiler-messages will correspond to line-numbers in the grammar-file (default)" << Qt::endl
           << "\t--beautiful-code - Line-numbers in compiler-messages will be arbitrary, but the code will look more beautiful and it is probably more compiler-independent" << Qt::endl
           << "\t--compatible-error-aware-code - Like --error-aware-code, but using #line instead of GCC-specific directives, thus not providing included-from-info to display the line number in the generated file" << Qt::endl
           << "\t--visitor-table - Visit::visitNode will be implemented by using a lookup-array (default)" << Qt::endl
           << "\t--visitor-switch - Visitor::visitNode will use a switch-statement" << Qt::endl
           << "About:" << Qt::endl
           << "\t--help - Show this messages" << Qt::endl
           << "\t--usage - Show usage" << Qt::endl
           << "\t--version - Show version" << Qt::endl
           << "\t--author - Show authors" << Qt::endl << Qt::endl
           << "See http://techbase.kde.org/Development/KDevelop-PG-Qt_Introduction for further aid." << Qt::endl;

  exit(EXIT_SUCCESS);
}

void version()
{
  KDevPG::checkOut << "KDevelop-PG-Qt: " << KDEVELOP_PG_QT_VERSION_STRING << Qt::endl;
  
  exit(EXIT_SUCCESS);
}

void author()
{
  KDevPG::checkOut << QString::fromUtf8("KDevelop-PG-Qt: SPDX-FileCopyrightText: 2005-2012 the KDevelop-PG-Qt developers :") << Qt::endl
    << QString::fromUtf8("\tRoberto Raggi\n"
       "\tJakob Petsovits\n"
       "\tAndreas Pakulat\n"
       "\tJonathan Schmidt-Dominé\n"
       "\t...and others") << Qt::endl;

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

    out << Qt::endl;
    KDevPG::PrettyPrinter p(out);
    p(e);

    bool initial = true;
    KDevPG::World::NodeSet::iterator it;

    out << Qt::endl;
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

    out << Qt::endl;
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
    out << Qt::endl;
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
  bool generate_lexer = true;
  bool ensure_generate_lexer_or_not = false;
  bool ensure_generate_parser_or_not = false;
  bool debug_rules = false;
  bool debug_automata = false;
  bool inherit_default = false;
  bool output = true;
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
      output = true;
    }
    else if (SW(--namespace=))
    {
      KDevPG::globalSystem.ns = arg.mid( 12 );
    }
    else if (arg == "--no-output")
    {
      output = false;
    }
    else if (arg == "--no-ast")
    {
      KDevPG::globalSystem.generateAst = false;
    }
    else if (arg == "--with-ast")
    {
      KDevPG::globalSystem.generateAst = true;
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
      ensure_generate_parser_or_not = true;
    }
    else if (arg == "--with-parser")
    {
      generate_parser = true;
      ensure_generate_parser_or_not = true;
    }
    else if (arg == "--no-lexer")
    {
      generate_lexer = false;
      ensure_generate_lexer_or_not = true;
    }
    else if (arg == "--with-lexer")
    {
      generate_lexer = true;
      ensure_generate_lexer_or_not = true;
    }
    else if (arg == "--beautiful-code")
    {
      KDevPG::globalSystem.lineNumberPolicy = KDevPG::World::BeautifulCode;
    }
    else if (arg == "--error-aware-code")
    {
      KDevPG::globalSystem.lineNumberPolicy = KDevPG::World::FullLineNumbers;
    }
    else if (arg == "--compatible-error-aware-code")
    {
      KDevPG::globalSystem.lineNumberPolicy = KDevPG::World::CompatibilityLineNumbers;
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
      output = false;
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
      debug_rules = true;
    }
    else if (arg == "--automata")
    {
      debug_automata = true;
    }
    else if (KDevPG::file.fileName().isEmpty())
    {
      KDevPG::file.setFileName(arg);

      if (!KDevPG::file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
          KDevPG::checkOut << "kdev-pg-qt: file ``" << arg
                    << "'' not found!" << Qt::endl;
          KDevPG::file.setFileName("");
        }
      else
          KDevPG::fileInfo.setFile(KDevPG::file);
    }
    else
    {
      KDevPG::checkOut << "kdev-pg-qt: unknown option ``" << arg << "''"
                << Qt::endl;
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
  
  if(!ensure_generate_parser_or_not)
    generate_parser = !KDevPG::globalSystem.rules.empty();
  
  if(generate_parser)
  {
    if(KDevPG::globalSystem.rules.empty())
    {
      KDevPG::checkOut << "** ERROR no parser rules" << Qt::endl;
      KDevPG::ProblemSummaryPrinter::reportError();
    }
    else
    {
      
      if(KDevPG::globalSystem.start.empty())
        KDevPG::checkOut << "** WARNING could not detect a start-symbol, every symbol gets reused, you have to care about EOFs yourself!" << Qt::endl;
      
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
    }
  }
  
  if (ensure_generate_lexer_or_not && generate_lexer && !KDevPG::globalSystem.hasLexer)
  {
    KDevPG::checkOut << "** ERROR no lexer definiton" << Qt::endl;
    KDevPG::ProblemSummaryPrinter::reportError();
    generate_lexer = false;
  }
  
  if (!ensure_generate_lexer_or_not)
    generate_lexer = KDevPG::globalSystem.hasLexer;
    
  if (generate_lexer)
  {
    if(!KDevPG::globalSystem.lexerEnvs.contains("start"))
    {
      KDevPG::checkOut << "** ERROR missing start-state in the lexer" << Qt::endl;
      KDevPG::ProblemSummaryPrinter::reportError();
    }
    if(!QRegularExpression(QStringLiteral("\\A[a-zA-Z_][a-zA-Z_0-9]*\\z")).match(KDevPG::globalSystem.tokenStream).hasMatch())
    { // primarily to exclude KDevPG::TokenStream (the default value)
      KDevPG::checkOut << "** ERROR You have to specify a valid name for your lexer (%token_stream)" << Qt::endl;
      KDevPG::ProblemSummaryPrinter::reportError();
    }
    foreach(QString state, KDevPG::globalSystem.lexerEnvs.keys())
    {
      KDevPG::GNFA &alltogether = **KDevPG::globalSystem.lexerEnvResults.insert(state, new KDevPG::GNFA(KDevPG::globalSystem.lexerEnvs[state]));
      KDevPG::GDFA &deterministic = **KDevPG::globalSystem.dfaForNfa.insert(&alltogether, new KDevPG::GDFA(alltogether.dfa()));
      deterministic.minimize();
      deterministic.setActions(KDevPG::globalSystem.lexerActions[state]);
    }
  }

  if(dump_terminals)
    {
      QFile ft("kdev-pg-terminals");
      ft.open( QIODevice::WriteOnly | QIODevice::Truncate );
      QTextStream strm(&ft);
      for (KDevPG::World::TerminalSet::iterator it = KDevPG::globalSystem.terminals.begin();
            it != KDevPG::globalSystem.terminals.end(); ++it)
        {
          strm << it.key() << Qt::endl;
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
          strm << it.key() << Qt::endl;
        }
    }
  if (debug_rules)
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
  if (debug_automata)
  {
    foreach(QString state, KDevPG::globalSystem.lexerEnvs.keys())
    {
      QFile ft(QString("kdev-pg-lexer-state-") + state + ".dot");
      ft.open(QIODevice::WriteOnly);
      QTextStream str(&ft);
      KDevPG::globalSystem.dfaForNfa[KDevPG::globalSystem.lexerEnvResults[state]]->dotOutput(str, state);
      ft.close();
    }
    foreach(QString name, KDevPG::globalSystem.regexpById.keys())
    {
      if(KDevPG::globalSystem.dfaForNfa.contains(KDevPG::globalSystem.regexpById[name]))
      {
        QFile ft(QString("kdev-pg-lexer-name-") + name + ".dot");
        ft.open(QIODevice::WriteOnly);
        QTextStream str(&ft);
        KDevPG::globalSystem.dfaForNfa[KDevPG::globalSystem.regexpById[name]]->dotOutput(str, name);
        ft.close();
      }
    }
  }
  
  KDevPG::ProblemSummaryPrinter()();
  
  if (!(dump_terminals || dump_symbols || debug_rules) && output && KDevPG::globalSystem.language.isEmpty())
  {
    usage();
    exit(EXIT_FAILURE);
  }

  if (output && generate_parser)
    KDevPG::generateOutput();
  
  if (output && generate_lexer)
    KDevPG::generateLexer();
  
  if (!new_visitor.isEmpty())
    KDevPG::generateVisitor(new_visitor, inherit_default);

  return EXIT_SUCCESS;
}

