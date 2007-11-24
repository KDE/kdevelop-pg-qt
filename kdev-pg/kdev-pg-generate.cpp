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
#include "kdev-pg-beautifier.h"

#include <QtCore/QTextStream>
#include <QtCore/QFile>

namespace KDevPG
{
void generateOutput()
{
  if (globalSystem.GenerateAst)
  { // generate the ast
    QString str;
    QTextStream s(&str, QIODevice::WriteOnly);

    GenerateAst _Ast(s);

    s << "// THIS FILE IS GENERATED" << endl
      << "// WARNING! All changes made in this file will be lost!" << endl
      << endl

      << "#ifndef " << globalSystem.language << "_AST_H_INCLUDED" << endl
      << "#define " << globalSystem.language << "_AST_H_INCLUDED" << endl
      << endl

      << "#include <QtCore/QList>" << endl
      << endl;
    if (!globalSystem.exportMacroHeader.isEmpty())
      s << "#include <" << globalSystem.exportMacroHeader << ">"
        << endl;

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

      << "#ifndef " << globalSystem.language << "_H_INCLUDED" << endl
      << "#define " << globalSystem.language << "_H_INCLUDED" << endl
      << endl;

    if (globalSystem.GenerateAst)
      {
        s << "#include \"" << globalSystem.language << "Ast.h\"" << endl
          << "#include <kdev-pg-memory-pool.h>" << endl
          << "#include <kdev-pg-allocator.h>" << endl;
      }

    if (globalSystem.tokenStream == "KDevPG::TokenStream")
      s << "#include <kdev-pg-token-stream.h>" << endl;

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

      << "#ifndef " << globalSystem.language << "_VISITOR_H_INCLUDED" << endl
      << "#define " << globalSystem.language << "_VISITOR_H_INCLUDED" << endl
      << endl

      << "#include \"" << globalSystem.language << "Ast.h\"" << endl
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

      << "#ifndef " << globalSystem.language << "_DEFAULT_VISITOR_H_INCLUDED" << endl
      << "#define " << globalSystem.language << "_DEFAULT_VISITOR_H_INCLUDED" << endl
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

      << "#ifndef " << globalSystem.language << "_SERIALIZATION_H_INCLUDED" << endl
      << "#define " << globalSystem.language << "_SERIALIZATION_H_INCLUDED" << endl
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

      << "#ifndef " << globalSystem.language << "_DEBUG_VISITOR_H_INCLUDED" << endl
      << "#define " << globalSystem.language << "_DEBUG_VISITOR_H_INCLUDED" << endl
      << endl

      << "#include \"" << globalSystem.language << "defaultvisitor.h\"" << endl
      << endl;
    if (!globalSystem.exportMacroHeader.isEmpty())
      s << "#include <" << globalSystem.exportMacroHeader << ">"
        << endl;

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

  { // generate the parser bits
    QString str;
    QTextStream s(&str, QIODevice::WriteOnly);

    GenerateParserBits __bits(s);

    s << "// THIS FILE IS GENERATED" << endl
      << "// WARNING! All changes made in this file will be lost!" << endl
      << endl;

    s << "#include \"" << globalSystem.language << "parser.h\""
      << endl
      << endl;

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


    for( World::SymbolSet::iterator it = globalSystem.symbols.begin();
        it != globalSystem.symbols.end(); it++ )
    {
      GenerateDefaultVisitorBitsRule gen(s);
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

}

