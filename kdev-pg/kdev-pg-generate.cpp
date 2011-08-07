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
#include "kdev-pg-regexp.h"

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

  if (globalSystem.generateAst)
  {
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
        
        << "#include \"" << globalSystem.language << "ast-fwd.h\"" << endl
        << endl

        << "#include <QtCore/QList>" << endl
        << "#include <kdev-pg-list.h>" << endl
        << endl;
      if (!globalSystem.exportMacroHeader.isEmpty())
        s << "#include \"" << globalSystem.exportMacroHeader << "\""
          << endl;

      foreach (const QString& header, globalSystem.astHeaders)
        s << "#include \"" << header << "\"\n";

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

      format(s, oname);
    }
    { // generate ast forward declarations
    
      QString str;
      QTextStream s(&str, QIODevice::WriteOnly);
      
      GenerateAstFwd _AstFwd(s);
      
      s << ""// THIS FILE IS GENERATED" << endl
        << "// WARNING! All changes made in this file will be lost!" << endl
        << endl

        << "#ifndef " << language << "_AST_FWD_INCLUDED" << endl
        << "#define " << language << "_AST_FWD_INCLUDED" << endl
        << endl;
      if (!globalSystem.exportMacroHeader.isEmpty())
        s << "#include \"" << globalSystem.exportMacroHeader << "\""
          << endl;
      
      s << "namespace " << globalSystem.ns << "{" << endl
        << endl;
      
      _AstFwd();
      
      s << endl << "} // end of namespace " << globalSystem.ns << endl
        << endl
      
        << "#endif" << endl
        << endl;
      
      QString oname = globalSystem.language;
      oname += "ast-fwd.h";
      
      format(s, oname);
    }
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
    
    if(globalSystem.hasLexer)
      s << "#include \"" << globalSystem.language << "lexer.h\"" << endl;

    if (globalSystem.generateAst)
      {
        s << "#include \"" << globalSystem.language << "ast-fwd.h\"" << endl
          << "#include <kdev-pg-memory-pool.h>" << endl
          << "#include <kdev-pg-allocator.h>" << endl;
      }

    if (globalSystem.tokenStream == "KDevPG::TokenStream")
      s << "#include <kdev-pg-token-stream.h>" << endl;
    
    if (globalSystem.needOperatorStack)
      s << "#include <QtCore/QVector>" << endl;
    
    foreach (const QString& header, globalSystem.parserDeclarationHeaders)
      s << "#include \"" << header << "\"\n";

    s << endl;
    if (!globalSystem.exportMacroHeader.isEmpty())
      s << "#include \"" << globalSystem.exportMacroHeader << "\""
        << endl;

    if (!globalSystem.decl.isEmpty() && !globalSystem.generateAst)
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

    format(s, oname);
  }

  if (globalSystem.generateAst)
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
      s << "#include \"" << globalSystem.exportMacroHeader << "\""
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

    format(s, oname);
  }

  if (globalSystem.generateAst)
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
      s << "#include \"" << globalSystem.exportMacroHeader << "\""
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

    format(s, oname);
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
      s << "#include \"" << globalSystem.exportMacroHeader << "\""
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

    format(s, oname);
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
      s << "#include \"" << globalSystem.exportMacroHeader << "\""
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

    format(s, oname);
  }
  if (globalSystem.generateTokenText || globalSystem.generateDebugVisitor)
  { // generate the token text function
    QString str;
    QTextStream s(&str, QIODevice::WriteOnly);

    s << "// THIS FILE IS GENERATED" << endl
      << "// WARNING! All changes made in this file will be lost!" << endl
      << endl

      << "#ifndef " << language << "_TOKEN_TEXT_H_INCLUDED" << endl
      << "#define " << language << "_TOKEN_TEXT_H_INCLUDED" << endl
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

    format(s, oname);
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
    
    if (globalSystem.generateAst)
    {
      s << "#include \"" << globalSystem.language << "ast.h\"" << endl;
    }

    foreach (const QString& header, globalSystem.parserBitsHeaders)
      s << "#include \"" << header << "\"\n";

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

    format(s, oname);
  }

  if (globalSystem.generateAst)
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

    format(s, oname);
  }

  if (globalSystem.generateAst)
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
        it != globalSystem.symbols.end(); ++it )
    {
      gen(qMakePair(it.key(), *it));
    }

    s << endl << "} // end of namespace " << globalSystem.ns << endl
      << endl;

    QString oname = globalSystem.language;
    oname += "defaultvisitor.cpp";

    format(s, oname);
  }
}

void generateLexer()
{
  QByteArray language = globalSystem.language.toUpper().toLatin1();
  bool hasStates = globalSystem.lexerEnvs.size() > 1;
  
  { // generate the lexer header
    QString str;
    QTextStream s(&str, QIODevice::WriteOnly);
    
    s << "// THIS FILE IS GENERATED" << endl
      << "// WARNING! All changes made in this file will be lost!" << endl
      << endl
    
      << "#ifndef " << language << "_LEXER_H_INCLUDED" << endl
      << "#define " << language << "_LEXER_H_INCLUDED" << endl
      << endl
    
      << endl
      
      << "#include <kdev-pg-char-sets.h>" << endl
      << "#include <kdev-pg-token-stream.h>" << endl
      << endl;
      
    foreach (const QString& header, globalSystem.lexerDeclarationHeaders)
      s << "#include \"" << header << "\"\n";
    
    s << endl << "namespace " << globalSystem.ns << "{" << endl
      << endl
      
      << "class " << globalSystem.exportMacro << " " << globalSystem.tokenStream << " : " 
      << (globalSystem.lexerBaseClass.isEmpty() ? "" : " public " + globalSystem.lexerBaseClass)
      << ", public " << globalSystem.inputStream << endl
      << "{" << endl
      << "public:" << endl
      << "typedef " << (globalSystem.lexerBaseClass.isEmpty() ? globalSystem.tokenStream : globalSystem.lexerBaseClass) << " Base;" << endl
      << "typedef " << globalSystem.inputStream << " Iterator;" << endl << endl << "private:" << endl;
      
    
    if(hasStates)
    {
      foreach(QString state, globalSystem.lexerEnvs.keys())
        s << "Base::Token& lex" << KDevPG::capitalized(state) << "();" << endl;
      s << "public:\nenum RuleSet {\n";
      foreach(QString state, globalSystem.lexerEnvs.keys())
        s << "State_" << state << ", /*" << globalSystem.lexerEnvs[state].size() << "*/" << endl;
      s << "State_COUNT\n};\n"
           "private:\n"
           "RuleSet m_ruleSet;\n"
           "public:\n"
           "inline RuleSet ruleSet()\n{\nreturn m_ruleSet;\n}\n"
           "void setRuleSet(RuleSet rs);\n";
      foreach(QString state, globalSystem.lexerEnvs.keys())
      {
        s << "inline void enteringRuleSet" << state << "();" << endl;
        s << "inline void leavingRuleSet" << state << "();" << endl;
      }
    }
      
    s << "Iterator::PlainIterator spos;" << endl
      << "bool continueLexeme;" << endl << endl
      
      << "public:" << endl << globalSystem.tokenStream << "(const Iterator& iter);" << endl
      // non-virtual, virtuality will be inherited
      << "~" << globalSystem.tokenStream << "();"
      <<  endl << "Base::Token& advance();" << endl;
    
      /// TODO: not good that it happens in a separate file for the parser but in this file for the lexer
#define LEXER_EXTRA_CODE_GEN(name) \
    if (globalSystem.lexerclassMembers.name.empty() == false) \
    { \
      s << "\n// user defined code:" << endl; \
      GenerateMemberCode gen(s, Settings::MemberItem::PublicDeclaration \
                                | Settings::MemberItem::ProtectedDeclaration \
                                | Settings::MemberItem::PrivateDeclaration); \
      for( auto it = globalSystem.lexerclassMembers.name.begin(); \
      it != globalSystem.lexerclassMembers.name.end(); ++it ) \
      { \
        gen(*it); \
      } \
    }
    
    // for (optional) lazyness add nextToken implementation here
    
    LEXER_EXTRA_CODE_GEN(declarations)
    
    s << "};" << endl << endl << "} // end of namespace " << globalSystem.ns << endl
      << endl
      
      << "#endif" << endl
      << endl;
      
    QString oname = globalSystem.language;
    oname += "lexer.h";
        
    format(s, oname);
    
  }
  { // generate the lexer bits
    QString str;
    QTextStream s(&str, QIODevice::WriteOnly);
    
    s << "// THIS FILE IS GENERATED" << endl
      << "// WARNING! All changes made in this file will be lost!" << endl
      << endl
    
      << "#include \"" << globalSystem.language << "lexer.h\"" << endl
      << "#include \"" << globalSystem.language << "parser.h\"" << endl
      << endl;
    
    foreach (const QString& header, globalSystem.lexerBitsHeaders)
      s << "#include \"" << header << "\"\n";
    
    s << "\n#include <cassert>\n";
    
    s << endl << "namespace " << globalSystem.ns << "{" << endl
      << endl << globalSystem.tokenStream << "::" << globalSystem.tokenStream
      << "(const " << globalSystem.tokenStream << "::Iterator& iter) : Base(), Iterator(iter), " << (hasStates ? "m_ruleSet(State_start), " : "") << "continueLexeme(false)" << endl
      << "{";
    LEXER_EXTRA_CODE_GEN(constructorCode)
    s << "}" << endl << endl
      << globalSystem.tokenStream << "::~" << globalSystem.tokenStream
      << "()\n{";
    LEXER_EXTRA_CODE_GEN(destructorCode)
    s << "}" << endl << endl
            
      << "#define PP_CONCAT_IMPL(x, y) x ## y\n" // necesarry, otherwise CURRENT_RULE_SET would not get resolved
         "#define PP_CONCAT(x, y) PP_CONCAT_IMPL(x, y)\n\n"
         
         "#define lxCURR_POS (Iterator::plain())\n"
         "#define lxCURR_IDX (Iterator::plain() - Iterator::begin())\n"
         "#define lxCONTINUE {continueLexeme = true; return advance();}\n"
         "#define lxLENGTH (Iterator::plain() - Iterator::begin())\n"
         "#define lxBEGIN_POS (spos)\n"
         "#define lxBEGIN_IDX (spos - Iterator::begin())\n"
         "#define lxNAMED_TOKEN(token, X) KDevPG::Token& token(Base::next()); token.kind = ::" + KDevPG::globalSystem.ns + "::Parser::Token_##X; token.begin = lxBEGIN_IDX; token.end = lxCURR_IDX - 1;\n"
         "#define lxTOKEN(X) {lxNAMED_TOKEN(token, X);}\n"
         "#define lxDONE {return Base::advance();}\n"
         "#define lxRETURN(X) {lxTOKEN(X); lxDONE}\n"
         "#define yytoken (Base::back())\n"
         "#define lxFAIL {goto _fail;}\n"
         "#define lxSKIP {return advance();}\n"
         "#define lxNEXT_CHR(chr) { if(!Iterator::hasNext()) goto _end; chr = Iterator::next(); }\n" << endl;
    
    if(hasStates)
    {
      s << "#define lxSET_RULE_SET(r) {PP_CONCAT(leavingRuleSet, CURRENT_RULE_SET) (); m_ruleSet = State_##r; enteringRuleSet##r ();}\n" << endl << endl;
      
      foreach(QString state, globalSystem.lexerEnvs.keys())
      {
        s << "inline void " << globalSystem.tokenStream << "::enteringRuleSet" << state << "() { " << globalSystem.enteringCode[state] << "}" << endl;
        s << "inline void " << globalSystem.tokenStream << "::leavingRuleSet" << state << "() { " << globalSystem.leavingCode[state] << "}" << endl;
      }
      s << "\n"
           "void " << globalSystem.tokenStream << "::setRuleSet(RuleSet rs)\n"
           "{\n"
           "switch(m_ruleSet)\n"
           "{\n";
      foreach(QString state, globalSystem.lexerEnvs.keys())
      {
        s << "case State_" << state << ":\n"
             "leavingRuleSet" << state << "();\n"
             "break;\n";
      }
      s << "\ndefault:\n"
           "assert(0 == \"Invalid rule set\");\n"
           "}\n\n"
           "m_ruleSet = rs;\n\n"
           "switch(m_ruleSet)\n"
           "{\n";
      foreach(QString state, globalSystem.lexerEnvs.keys())
      {
        s << "case State_" << state << ":\n"
             "enteringRuleSet" << state << "();\n"
             "break;\n";
      }
      s << "\ndefault:\n"
           "assert(0 == \"Invalid rule set\");\n"
           "}\n"
           "}\n\n";
    }
    
#define LEXER_CORE_IMPL(name, state, extra) \
      s << globalSystem.tokenStream << "::Base::Token& " << globalSystem.tokenStream << "::" \
        << name << "()" << endl << "{" \
        << extra << "if(!Iterator::hasNext())\n{\nBase::Token& _t(Base::advance());\n_t.kind = Parser::Token_EOF;\n_t.begin = _t.end = Iterator::plain() - Iterator::begin();\nreturn _t;\n}" << endl \
        << "if(continueLexeme) continueLexeme = false;\nelse spos = plain();\nIterator::PlainIterator lpos = Iterator::plain();\nIterator::Int chr = 0;\nint lstate = 0;\n"; \
      globalSystem.dfaForNfa[globalSystem.lexerEnvResults[state]]->codegen(s); \
      s << "/* assert(false);*/\nreturn Base::advance();}" << endl << endl;
    
    if(hasStates)
    {
      foreach(QString state, globalSystem.lexerEnvs.keys())
      {
        s << "#define CURRENT_RULE_SET " << state << endl;
        LEXER_CORE_IMPL("lex" + KDevPG::capitalized(state), state, "")
        s << "#undef CURRENT_RULE_SET" << endl;
      }
      s << globalSystem.tokenStream << "::Base::Token& " << globalSystem.tokenStream
        << "::advance()" << endl << "{" << endl << "if(Base::index() < Base::size())\nreturn Base::advance();\nswitch(m_ruleSet)\n{" << endl;
      foreach(QString state, globalSystem.lexerEnvs.keys())
        s << "case State_" << state << ": return lex" << capitalized(state) << "();" << endl;
      s << "default:\nexit(-1);\n}\n}" << endl;
    }
    else
    {
      LEXER_CORE_IMPL("advance", "start", "if(Base::index() < Base::size())\nreturn Base::advance();\n")
    }
    
    if(hasStates)
    {
      s << "#undef lxSET_RULE_SET\n" << endl;
    }
    
    s << "#undef lxNEXT_CHR\n"
         "#undef lxFAIl\n"
         "#undef lxRETURN\n"
         "#undef lxTOKEN\n"
         "#undef lxBEGIN_IDX\n"
         "#undef lxBEGIN_POS\n"
         "#undef lxLENGTH\n"
         "#undef lxCONTINUE\n"
         "#undef lxCURR_IDX\n"
         "#undef lxCURR_POS\n\n"
         
         "#undef PP_CONCAT\n"
         "#undef PP_CONCAT_IMPL\n" << endl;
    
    s << globalSystem.lexerBits << endl
      << "} // end of namespace " << globalSystem.ns << endl << endl;
    
    QString oname = globalSystem.language;
    oname += "lexer.cpp";
        
    format(s, oname);
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
      s << "#include \"" << globalSystem.exportMacroHeader << "\""
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
    
    format(s, oname);
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
              it != globalSystem.symbols.end(); ++it )
      {
        gen(qMakePair(it.key(), *it));
      }
    }
    else
    {
      GenerateDefaultVisitorBitsRule gen(s, name);
      for( World::SymbolSet::iterator it = globalSystem.symbols.begin();
              it != globalSystem.symbols.end(); ++it )
      {
        gen(qMakePair(it.key(), *it));
      }
    }
    
    s << endl << "} // end of namespace " << globalSystem.ns << endl
      << endl;
    
    QString oname = globalSystem.language;
    oname += name.toLower() + ".cpp";

    format(s, oname);
  }
  
}

}


