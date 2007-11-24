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

#include <iostream>
#include <sstream>
#include <fstream>

namespace KDevPG
{
void generateOutput()
{
  if (globalSystem.GenerateAst)
  { // generate the ast
    std::stringstream s;

    GenerateAst _Ast(s);

    s << "// THIS FILE IS GENERATED" << std::endl
      << "// WARNING! All changes made in this file will be lost!" << std::endl
      << std::endl

      << "#ifndef " << globalSystem.language << "_AST_H_INCLUDED" << std::endl
      << "#define " << globalSystem.language << "_AST_H_INCLUDED" << std::endl
      << std::endl

      << "#include <kdev-pg-list.h>" << std::endl
      << std::endl;
    if (globalSystem.exportMacroHeader)
      s << "#include <" << globalSystem.exportMacroHeader << ">"
        << std::endl;

    if (globalSystem.decl)
      s << globalSystem.decl << std::endl;

    s << "namespace " << globalSystem.ns << "{" << std::endl
      << std::endl;

    _Ast();

    s << std::endl << "} // end of namespace " << globalSystem.ns << std::endl
      << std::endl

      << "#endif" << std::endl
      << std::endl;

    std::string oname = globalSystem.language;
    oname += "ast.h";

    std::ofstream ofile;
    ofile.open(oname.c_str(), std::ios::out);
    format(s, ofile);
  }

  { // generate the parser decls
    std::stringstream s;

    GenerateParserDeclarations __decls(s);

    s << "// THIS FILE IS GENERATED" << std::endl
      << "// WARNING! All changes made in this file will be lost!" << std::endl
      << std::endl

      << "#ifndef " << globalSystem.language << "_H_INCLUDED" << std::endl
      << "#define " << globalSystem.language << "_H_INCLUDED" << std::endl
      << std::endl;

    if (globalSystem.GenerateAst)
      {
        s << "#include \"" << globalSystem.language << "Ast.h\"" << std::endl
          << "#include <kdev-pg-memory-pool.h>" << std::endl
          << "#include <kdev-pg-allocator.h>" << std::endl;
      }

    if (!strcmp(globalSystem.tokenStream, "KDevPG::tokenStream"))
      s << "#include <kdev-pg-token-stream.h>" << std::endl;

    s << std::endl;
    if (globalSystem.exportMacroHeader)
      s << "#include <" << globalSystem.exportMacroHeader << ">"
        << std::endl;

    if (globalSystem.decl && !globalSystem.GenerateAst)
      s << globalSystem.decl << std::endl;

    s << "namespace " << globalSystem.ns << "{" << std::endl
      << std::endl;

    __decls();

    s << std::endl << "} // end of namespace " << globalSystem.ns << std::endl
      << std::endl

      << "#endif" << std::endl
      << std::endl;

    std::string oname = globalSystem.language;
    oname += "parser.h";

    std::ofstream ofile;
    ofile.open(oname.c_str(), std::ios::out);
    format(s, ofile);
  }

  if (globalSystem.GenerateAst)
  { // generate the visitor decls
    std::stringstream s;

    GenerateVisitor __visitor(s);

    s << "// THIS FILE IS GENERATED" << std::endl
      << "// WARNING! All changes made in this file will be lost!" << std::endl
      << std::endl

      << "#ifndef " << globalSystem.language << "_VISITOR_H_INCLUDED" << std::endl
      << "#define " << globalSystem.language << "_VISITOR_H_INCLUDED" << std::endl
      << std::endl

      << "#include \"" << globalSystem.language << "Ast.h\"" << std::endl
      << std::endl;
    if (globalSystem.exportMacroHeader)
      s << "#include <" << globalSystem.exportMacroHeader << ">"
        << std::endl;

    s << "namespace " << globalSystem.ns << "{" << std::endl
      << std::endl;

    __visitor();

    s << std::endl << "} // end of namespace " << globalSystem.ns << std::endl
      << std::endl

      << "#endif" << std::endl
      << std::endl;

    std::string oname = globalSystem.language;
    oname += "visitor.h";

    std::ofstream ofile;
    ofile.open(oname.c_str(), std::ios::out);
    format(s, ofile);
  }

  if (globalSystem.GenerateAst)
  { // generate the default visitor
    std::stringstream s;

    GenerateDefaultVisitor __DefaultVisitor(s);

    s << "// THIS FILE IS GENERATED" << std::endl
      << "// WARNING! All changes made in this file will be lost!" << std::endl
      << std::endl

      << "#ifndef " << globalSystem.language << "_DEFAULT_VISITOR_H_INCLUDED" << std::endl
      << "#define " << globalSystem.language << "_DEFAULT_VISITOR_H_INCLUDED" << std::endl
      << std::endl

      << "#include \"" << globalSystem.language << "visitor.h\"" << std::endl
      << std::endl;
    if (globalSystem.exportMacroHeader)
      s << "#include <" << globalSystem.exportMacroHeader << ">"
        << std::endl;

    s << "namespace " << globalSystem.ns << "{" << std::endl
      << std::endl;

    __DefaultVisitor();

    s << std::endl << "} // end of namespace " << globalSystem.ns << std::endl
      << std::endl

      << "#endif" << std::endl
      << std::endl;

    std::string oname = globalSystem.language;
    oname += "defaultvisitor.h";

    std::ofstream ofile;
    ofile.open(oname.c_str(), std::ios::out);
    format(s, ofile);
  }

  if (globalSystem.generateSerializeVisitor)
  { // generate the serialization visitor
    std::stringstream s;

    GenerateSerializeVisitor __serialize_visitor(s);

    s << "// THIS FILE IS GENERATED" << std::endl
      << "// WARNING! All changes made in this file will be lost!" << std::endl
      << std::endl

      << "#ifndef " << globalSystem.language << "_SERIALIZATION_H_INCLUDED" << std::endl
      << "#define " << globalSystem.language << "_SERIALIZATION_H_INCLUDED" << std::endl
      << std::endl

      << "#include \"" << globalSystem.language << "defaultvisitor.h\"" << std::endl
      << std::endl;
    if (globalSystem.exportMacroHeader)
      s << "#include <" << globalSystem.exportMacroHeader << ">"
        << std::endl;

    s << "#include <iostream>" << std::endl
      << "#include <fstream>" << std::endl
      << std::endl

      << "namespace " << globalSystem.ns << "{" << std::endl
      << std::endl;

    __serialize_visitor();

    s << std::endl << "} // end of namespace " << globalSystem.ns << std::endl
      << std::endl;

    s << "#endif" << std::endl
      << std::endl;

    std::string oname = globalSystem.language;
    oname += "serializevisitor.h";

    std::ofstream ofile;
    ofile.open(oname.c_str(), std::ios::out);
    format(s, ofile);
  }

  if (globalSystem.generateDebugVisitor)
  { // generate the debug visitor
    std::stringstream s;

    GenerateDebugVisitor __debug_visitor(s);

    s << "// THIS FILE IS GENERATED" << std::endl
      << "// WARNING! All changes made in this file will be lost!" << std::endl
      << std::endl

      << "#ifndef " << globalSystem.language << "_DEBUG_VISITOR_H_INCLUDED" << std::endl
      << "#define " << globalSystem.language << "_DEBUG_VISITOR_H_INCLUDED" << std::endl
      << std::endl

      << "#include \"" << globalSystem.language << "defaultvisitor.h\"" << std::endl
      << std::endl;
    if (globalSystem.exportMacroHeader)
      s << "#include <" << globalSystem.exportMacroHeader << ">"
        << std::endl;

    s << "#include <iostream>" << std::endl
      << "#include <fstream>" << std::endl
      << std::endl

      << "namespace " << globalSystem.ns << "{" << std::endl
      << std::endl;

    __debug_visitor();

    s << std::endl << "} // end of namespace " << globalSystem.ns << std::endl
      << std::endl;

    s << "#endif" << std::endl
      << std::endl;

    std::string oname = globalSystem.language;
    oname += "debugvisitor.h";

    std::ofstream ofile;
    ofile.open(oname.c_str(), std::ios::out);
    format(s, ofile);
  }

  { // generate the parser bits
    std::stringstream s;

    GenerateParserBits __bits(s);

    s << "// THIS FILE IS GENERATED" << std::endl
      << "// WARNING! All changes made in this file will be lost!" << std::endl
      << std::endl;

    s << "#include \"" << globalSystem.language << "parser.h\""
      << std::endl
      << std::endl;

    if (globalSystem.bits)
      s << globalSystem.bits << std::endl;

    s << "namespace " << globalSystem.ns << "{" << std::endl
      << std::endl;

    __bits();

    s << std::endl << "} // end of namespace " << globalSystem.ns << std::endl
      << std::endl;

    std::string oname = globalSystem.language;
    oname += "parser.cpp";

    std::ofstream ofile;
    ofile.open(oname.c_str(), std::ios::out);
    format(s, ofile);
  }

  if (globalSystem.GenerateAst)
  { // generate the visitor bits
    std::stringstream s;

    GenerateVisitorBits __visitor_bits(s);

    s << "// THIS FILE IS GENERATED" << std::endl
      << "// WARNING! All changes made in this file will be lost!" << std::endl
      << std::endl

      << "#include \"" << globalSystem.language << "visitor.h\"" << std::endl
      << std::endl

      << "namespace " << globalSystem.ns << "{" << std::endl
      << std::endl;

    __visitor_bits();

    s << std::endl << "} // end of namespace " << globalSystem.ns << std::endl
      << std::endl;

    std::string oname = globalSystem.language;
    oname += "visitor.cpp";

    std::ofstream ofile;
    ofile.open(oname.c_str(), std::ios::out);
    format(s, ofile);
  }

  if (globalSystem.GenerateAst)
  { // generate the default visitor bits
    std::stringstream s;

    s << "// THIS FILE IS GENERATED" << std::endl
      << "// WARNING! All changes made in this file will be lost!" << std::endl
      << std::endl

      << "#include \"" << globalSystem.language << "defaultvisitor.h\"" << std::endl
      << std::endl

      << "namespace " << globalSystem.ns << "{" << std::endl
      << std::endl;

    std::for_each(globalSystem.symbols.begin(), globalSystem.symbols.end(),
                  GenerateDefaultVisitorBitsRule(s));

    s << std::endl << "} // end of namespace " << globalSystem.ns << std::endl
      << std::endl;

    std::string oname = globalSystem.language;
    oname += "defaultvisitor.cpp";

    std::ofstream ofile;
    ofile.open(oname.c_str(), std::ios::out);
    format(s, ofile);
  }
}

}

