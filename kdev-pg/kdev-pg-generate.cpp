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

#include "kdev-pg-generate.h"

#include "kdev-pg.h"
#include "kdev-pg-code-gen.h"
#include "kdev-pg-ast-gen.h"
#include "kdev-pg-visitor-gen.h"
#include "kdev-pg-visitor-bits-gen.h"
#include "kdev-pg-default-visitor-gen.h"
#include "kdev-pg-default-visitor-bits-gen.h"
#include "kdev-pg-serialize-visitor-gen.h"
#include "kdev-pg-debug-visitor-gen.h"
#include "kdev-pg-new-visitor-gen.h"
#include "kdev-pg-new-visitor-bits-gen.h"
#include "kdev-pg-beautifier.h"

#include <QtCore/QTextStream>
#include <QtCore/QFile>

namespace KDevPG
{
void generateOutput()
{
  QByteArray language = globalSystem.language.toUpper().toLatin1();
  for(int i = 0; i != language.size(); ++i)
  {
    if(language[i] < '0' || (language[i] > '9' && language[i] < 'A') || language[i] > 'Z')
      language[i] = '_';
  }

  if (globalSystem.GenerateAst)
  { // generate the ast
    QString str;
    QTextStream s(&str, QIODevice::WriteOnly);

    GenerateAst _Ast(s);

    s << "// THIS FILE IS GENERATED" << endl
      << "// WARNING! All changes made in this file will be lost!" << endl
      << endl

      << "#ifndef " << language << "_AST_H_INCLUDED" << endl
      << "#define " << language << "_AST_H_INCLUDED" << endl
      << endl

      << "#include <QtCore/QList>" << endl
      << "#include <kdev-pg-list.h>" << endl
      << endl;
    if (!globalSystem.exportMacroHeader.isEmpty())
      s << "#include <" << globalSystem.exportMacroHeader << ">"
        << endl;

    foreach (const QString& header, globalSystem.astHeaders)
      s << "#include <" << header << ">\n";

    if (!globalSystem.decl.isEmpty())
      s << globalSystem.decl << endl;

    s << "namespace " << globalSystem.ns << "{" << endl
      << endl;

    _Ast();

    s << endl << "} // end of namespace " << globalSystem.ns << endl
      << endl

      << "#endif" << endl
      << endl;

    QString oname = globalSystem.language;
    oname += "ast.h";

    QFile ofile(oname);
    ofile.open(QIODevice::WriteOnly);
    QTextStream outstr(&ofile);
    format(s, outstr);
  }

  { // generate the parser decls
    QString str;
    QTextStream s(&str, QIODevice::WriteOnly);

    GenerateParserDeclarations __decls(s);

    s << "// THIS FILE IS GENERATED" << endl
      << "// WARNING! All changes made in this file will be lost!" << endl
      << endl

      << "#ifndef " << language << "_H_INCLUDED" << endl
      << "#define " << language << "_H_INCLUDED" << endl
      << endl;

    if (globalSystem.GenerateAst)
      {
        s << "#include \"" << globalSystem.language << "ast.h\"" << endl
          << "#include <kdev-pg-memory-pool.h>" << endl
          << "#include <kdev-pg-allocator.h>" << endl;
      }

    if (globalSystem.tokenStream == "KDevPG::TokenStream")
      s << "#include <kdev-pg-token-stream.h>" << endl;

    foreach (const QString& header, globalSystem.parserDeclarationHeaders)
      s << "#include <" << header << ">\n";

    s << endl;
    if (!globalSystem.exportMacroHeader.isEmpty())
      s << "#include <" << globalSystem.exportMacroHeader << ">"
        << endl;

    if (!globalSystem.decl.isEmpty() && !globalSystem.GenerateAst)
      s << globalSystem.decl << endl;

    s << "namespace " << globalSystem.ns << "{" << endl
      << endl;

    __decls();

    s << endl << "} // end of namespace " << globalSystem.ns << endl
      << endl

      << "#endif" << endl
      << endl;

    QString oname = globalSystem.language;
    oname += "parser.h";

    QFile ofile(oname);
    ofile.open(QIODevice::WriteOnly);
    QTextStream outstr(&ofile);
    format(s, outstr);
  }

  if (globalSystem.GenerateAst)
  { // generate the visitor decls
    QString str;
    QTextStream s(&str, QIODevice::WriteOnly);

    GenerateVisitor __visitor(s);

    s << "// THIS FILE IS GENERATED" << endl
      << "// WARNING! All changes made in this file will be lost!" << endl
      << endl

      << "#ifndef " << language << "_VISITOR_H_INCLUDED" << endl
      << "#define " << language << "_VISITOR_H_INCLUDED" << endl
      << endl

      << "#include \"" << globalSystem.language << "ast.h\"" << endl
      << endl;
    if (!globalSystem.exportMacroHeader.isEmpty())
      s << "#include <" << globalSystem.exportMacroHeader << ">"
        << endl;

    s << "namespace " << globalSystem.ns << "{" << endl
      << endl;

    __visitor();

    s << endl << "} // end of namespace " << globalSystem.ns << endl
      << endl

      << "#endif" << endl
      << endl;

    QString oname = globalSystem.language;
    oname += "visitor.h";

    QFile ofile(oname);
    ofile.open(QIODevice::WriteOnly);
    QTextStream outstr(&ofile);
    format(s, outstr);
  }

  if (globalSystem.GenerateAst)
  { // generate the default visitor
    QString str;
    QTextStream s(&str, QIODevice::WriteOnly);

    GenerateDefaultVisitor __DefaultVisitor(s);

    s << "// THIS FILE IS GENERATED" << endl
      << "// WARNING! All changes made in this file will be lost!" << endl
      << endl

      << "#ifndef " << language << "_DEFAULT_VISITOR_H_INCLUDED" << endl
      << "#define " << language << "_DEFAULT_VISITOR_H_INCLUDED" << endl
      << endl

      << "#include \"" << globalSystem.language << "visitor.h\"" << endl
      << endl;
    if (!globalSystem.exportMacroHeader.isEmpty())
      s << "#include <" << globalSystem.exportMacroHeader << ">"
        << endl;

    s << "namespace " << globalSystem.ns << "{" << endl
      << endl;

    __DefaultVisitor();

    s << endl << "} // end of namespace " << globalSystem.ns << endl
      << endl

      << "#endif" << endl
      << endl;

    QString oname = globalSystem.language;
    oname += "defaultvisitor.h";

    QFile ofile(oname);
    ofile.open(QIODevice::WriteOnly);
    QTextStream outstr(&ofile);
    format(s, outstr);
  }

  if (globalSystem.generateSerializeVisitor)
  { // generate the serialization visitor
    QString str;
    QTextStream s(&str, QIODevice::WriteOnly);

    GenerateSerializeVisitor __serialize_visitor(s);

    s << "// THIS FILE IS GENERATED" << endl
      << "// WARNING! All changes made in this file will be lost!" << endl
      << endl

      << "#ifndef " << language << "_SERIALIZATION_H_INCLUDED" << endl
      << "#define " << language << "_SERIALIZATION_H_INCLUDED" << endl
      << endl

      << "#include \"" << globalSystem.language << "defaultvisitor.h\"" << endl
      << endl;
    if (!globalSystem.exportMacroHeader.isEmpty())
      s << "#include <" << globalSystem.exportMacroHeader << ">"
        << endl;

    s << "#include <QtCore/QTextStream>" << endl
      << "#include <QtCore/QFile>" << endl
      << endl

      << "namespace " << globalSystem.ns << "{" << endl
      << endl;

    __serialize_visitor();

    s << endl << "} // end of namespace " << globalSystem.ns << endl
      << endl;

    s << "#endif" << endl
      << endl;

    QString oname = globalSystem.language;
    oname += "serializevisitor.h";

    QFile ofile(oname);
    ofile.open(QIODevice::WriteOnly);
    QTextStream outstr(&ofile);
    format(s, outstr);
  }

  if (globalSystem.generateDebugVisitor)
  { // generate the debug visitor
    QString str;
    QTextStream s(&str, QIODevice::WriteOnly);

    GenerateDebugVisitor __debug_visitor(s);

    s << "// THIS FILE IS GENERATED" << endl
      << "// WARNING! All changes made in this file will be lost!" << endl
      << endl

      << "#ifndef " << language << "_DEBUG_VISITOR_H_INCLUDED" << endl
      << "#define " << language << "_DEBUG_VISITOR_H_INCLUDED" << endl
      << endl

      << "#include \"" << globalSystem.language << "defaultvisitor.h\"" << endl
      << endl;
    if (!globalSystem.exportMacroHeader.isEmpty())
      s << "#include <" << globalSystem.exportMacroHeader << ">"
        << endl;

    s << "#include <kdev-pg-token-stream.h>" << endl;
    
    s << "#include <QtCore/QTextStream>" << endl
      << "#include <QtCore/QDebug>" << endl
      << endl

      << "namespace " << globalSystem.ns << "{" << endl
      << endl;

    __debug_visitor();

    s << endl << "} // end of namespace " << globalSystem.ns << endl
      << endl;

    s << "#endif" << endl
      << endl;

    QString oname = globalSystem.language;
    oname += "debugvisitor.h";

    QFile ofile(oname);
    ofile.open(QIODevice::WriteOnly);
    QTextStream outstr(&ofile);
    format(s, outstr);
  }
  if (globalSystem.generateDebugVisitor)
  { // generate the token text function
    QString str;
    QTextStream s(&str, QIODevice::WriteOnly);

    s << "// THIS FILE IS GENERATED" << endl
      << "// WARNING! All changes made in this file will be lost!" << endl
      << endl

      << "#ifndef " << language << "_TOKEN_TEXT_H_INCLUDED" << endl
      << "#define " << language << "_TOKEN_TEXT_H_INCLUDED" << endl
      << endl

      << "#include \"" << globalSystem.language << "parser.h\"" << endl
      << endl

      << "namespace " << globalSystem.ns << "{" << endl
      << endl

      << "QString tokenText(int token)" << endl << "{" << endl;

    GenerateTokenTexts gen(s);
    gen();

    s << "}"
      << endl << "} // end of namespace " << globalSystem.ns << endl
      << endl;

    s << "#endif" << endl
      << endl;

    QString oname = globalSystem.language;
    oname += "tokentext.h";

    QFile ofile(oname);
    ofile.open(QIODevice::WriteOnly);
    QTextStream outstr(&ofile);
    format(s, outstr);
  }
  { // generate the parser bits
    QString str;
    QTextStream s(&str, QIODevice::WriteOnly);

    GenerateParserBits __bits(s);

    s << "// THIS FILE IS GENERATED" << endl
      << "// WARNING! All changes made in this file will be lost!" << endl
      << endl;

    s << "#include \"" << globalSystem.language << "parser.h\""
      << endl;

    foreach (const QString& header, globalSystem.parserBitsHeaders)
      s << "#include <" << header << ">\n";

    s << endl;

    if (!globalSystem.bits.isEmpty())
      s << globalSystem.bits << endl;

    s << "namespace " << globalSystem.ns << "{" << endl
      << endl;

    __bits();

    s << endl << "} // end of namespace " << globalSystem.ns << endl
      << endl;

    QString oname = globalSystem.language;
    oname += "parser.cpp";

    QFile ofile(oname);
    ofile.open(QIODevice::WriteOnly);
    QTextStream outstr(&ofile);
    format(s, outstr);
  }

  if (globalSystem.GenerateAst)
  { // generate the visitor bits
    QString str;
    QTextStream s(&str, QIODevice::WriteOnly);

    GenerateVisitorBits __visitor_bits(s);

    s << "// THIS FILE IS GENERATED" << endl
      << "// WARNING! All changes made in this file will be lost!" << endl
      << endl

      << "#include \"" << globalSystem.language << "visitor.h\"" << endl

      << endl

      << "namespace " << globalSystem.ns << "{" << endl
      << endl;

    __visitor_bits();

    s << endl << "} // end of namespace " << globalSystem.ns << endl
      << endl;

    QString oname = globalSystem.language;
    oname += "visitor.cpp";

    QFile ofile(oname);
    ofile.open(QIODevice::WriteOnly);
    QTextStream outstr(&ofile);
    format(s, outstr);
  }

  if (globalSystem.GenerateAst)
  { // generate the default visitor bits
    QString str;
    QTextStream s(&str, QIODevice::WriteOnly);

    s << "// THIS FILE IS GENERATED" << endl
      << "// WARNING! All changes made in this file will be lost!" << endl
      << endl

      << "#include \"" << globalSystem.language << "defaultvisitor.h\"" << endl
      << endl

      << "namespace " << globalSystem.ns << "{" << endl

      << endl;

    GenerateDefaultVisitorBitsRule gen(s);
    for( World::SymbolSet::iterator it = globalSystem.symbols.begin();
        it != globalSystem.symbols.end(); it++ )
    {
      gen(qMakePair(it.key(), *it));
    }

    s << endl << "} // end of namespace " << globalSystem.ns << endl
      << endl;

    QString oname = globalSystem.language;
    oname += "defaultvisitor.cpp";

    QFile ofile(oname);
    ofile.open(QIODevice::WriteOnly);
    QTextStream outstr(&ofile);
    format(s, outstr);
  }
}

void generateVisitor(const QString& name, bool inherit_default)
{
  QByteArray language = globalSystem.language.toUpper().toLatin1();
  for(int i = 0; i != language.size(); ++i)
  {
    if(language[i] < '0' || (language[i] > '9' && language[i] < 'A') || language[i] > 'Z')
      language[i] = '_';
  }
  QByteArray upper_name = name.toUpper().toLatin1();
  
  {
    QString str;
    QTextStream s(&str, QIODevice::WriteOnly);
    
    s << "#ifndef " << language << "_" << upper_name << "_H" << endl
      << "#define " << language << "_" << upper_name << "_H" << endl
      << endl
    
      << "#include \"" << globalSystem.language << (inherit_default ? "default" : "") << "visitor.h\"" << endl
      << endl;
    
    if (!globalSystem.exportMacroHeader.isEmpty())
      s << "#include <" << globalSystem.exportMacroHeader << ">"
        << endl;
    
    s << "namespace " << globalSystem.ns << "{" << endl << endl;
                                                            
    if (inherit_default)
    { // generate an empty visitor using the default-visitor
      
      GenerateNewVisitor visitor(s, name);
      
      visitor();
    }
    else
    { // generate a visitor like the default visitor
      
      GenerateDefaultVisitor visitor(s, name);
          
      visitor();
    }
        
    s << endl << "} // end of namespace " << globalSystem.ns << endl
      << endl
        
      << "#endif" << endl
      << endl;
        
    QString oname = globalSystem.language;
    oname += name.toLower() + ".h";
    
    QFile ofile(oname);
    ofile.open(QIODevice::WriteOnly);
    QTextStream outstr(&ofile);
    format(s, outstr);
  }
  
  {
    QString str;
    QTextStream s(&str, QIODevice::WriteOnly);
    
    s << "#include \"" << globalSystem.language << "defaultvisitor.h\"" << endl
      << endl
    
      << "namespace " << globalSystem.ns << "{" << endl
    
      << endl;
    
    if(inherit_default)
    {
      GenerateNewVisitorBitsRule gen(s, name);
      for( World::SymbolSet::iterator it = globalSystem.symbols.begin();
              it != globalSystem.symbols.end(); it++ )
      {
        gen(qMakePair(it.key(), *it));
      }
    }
    else
    {
      GenerateDefaultVisitorBitsRule gen(s, name);
      for( World::SymbolSet::iterator it = globalSystem.symbols.begin();
              it != globalSystem.symbols.end(); it++ )
      {
        gen(qMakePair(it.key(), *it));
      }
    }
    
    s << endl << "} // end of namespace " << globalSystem.ns << endl
      << endl;
    
    QString oname = globalSystem.language;
    oname += name.toLower() + ".cpp";
    
    QFile ofile(oname);
    ofile.open(QIODevice::WriteOnly);
    QTextStream outstr(&ofile);
    format(s, outstr);
  }
  
}

}
