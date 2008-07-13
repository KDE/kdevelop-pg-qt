/* This file is part of kdev-pg
   Copyright (C) 2006 Alexander Dymo <adymo@kdevelop.org>

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

#include "kdev-pg-debug-visitor-gen.h"
#include "kdev-pg.h"
#include <iostream>

namespace KDevPG
{

void GenerateDebugVisitor::operator()()
{
  out << "class " << globalSystem.exportMacro << " DebugVisitor: public DefaultVisitor {" << endl
      << "public:" << endl;

  out << "DebugVisitor("<< globalSystem.tokenStream << " *str, const QString& content = QString())" << endl;
  out << "    : m_str(str), m_indent(0), m_content(content) {}" << endl;
  GenerateDebugVisitorRule gen(out);
  for( World::SymbolSet::iterator it = globalSystem.symbols.begin();
       it != globalSystem.symbols.end(); it++ )
  {
    gen(qMakePair(it.key(), *it));
  }

  out << "private:" << endl << globalSystem.tokenStream << " *m_str;" << endl;
  out << "int m_indent;" << endl;
  out << "QString m_content;" << endl;
  out << "};" << endl;
}

void GenerateDebugVisitorRule::operator()(QPair<QString,
                                          Model::SymbolItem*> const &__it)
{
  Model::SymbolItem *sym = __it.second;

  bool has_members = false;
  HasMemberNodes hms(has_members);
  hms(sym);

  out << "virtual void visit" << sym->mCapitalizedName
      << "(" << sym->mCapitalizedName << "Ast *" << "node"
      << ") {" << endl;

  out << "qint64 beginLine,endLine,beginCol,endCol;" << endl;
  out << "m_str->startPosition(node->startToken, &beginLine, &beginCol);" << endl;
  out << "m_str->endPosition(node->endToken, &endLine, &endCol);" << endl;
  out << "QString tokenString;" << endl;
  out << "if (!m_content.isEmpty()) {" << endl;
  out << "    " << globalSystem.tokenStream << "::Token startToken = m_str->token(node->startToken);" << endl;
  out << "    " << globalSystem.tokenStream << "::Token endToken = m_str->token(node->endToken);" << endl;
  out << "    int begin = startToken.begin;" << endl;
  out << "    int end = endToken.end;" << endl;
  out << "    if (end-begin > 30) {" << endl;
  out << "        tokenString = m_content.mid(begin, 10);" << endl;
  out << "        tokenString += \" ...\";" << endl;
  out << "        tokenString += QString(\"%1 more\").arg(end-begin-20);" << endl;
  out << "        tokenString += \"... \";" << endl;
  out << "        tokenString += m_content.mid(end-10, 10);" << endl;
  out << "    } else {" << endl;
  out << "        tokenString = m_content.mid(begin, end-begin+1);" << endl;
  out << "    }" << endl;
  out << "    tokenString = tokenString.replace('\\n', \"\\\\n\");" << endl;
  out << "    tokenString = tokenString.replace('\\r', \"\\\\r\");" << endl;
  out << "}" << endl;
  out << "qDebug() << QString().fill(' ', m_indent) << \"" << sym->mName << "[\" << m_str->token( node->startToken ).begin"
      << " << \",\" << beginLine << \",\" << beginCol << "
      << "\"] --- [\" << m_str->token( node->endToken ).end <<"
      << " \",\" << endLine << \",\" << endCol "
      << "<< \"] \""
      << " << tokenString"
      << ";"
      << endl;
  
  out << "m_indent++;";
  
  out << "DefaultVisitor::visit" << sym->mCapitalizedName
      << "(" << "node"
      << ");" << endl;
  
  out << "m_indent--;";
  
  out << "}" << endl << endl;
}

}
