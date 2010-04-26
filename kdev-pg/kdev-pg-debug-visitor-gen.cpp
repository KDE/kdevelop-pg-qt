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
       it != globalSystem.symbols.end(); ++it )
  {
    gen(qMakePair(it.key(), *it));
  }

  out << "private:" << endl;
  out << "void printToken(AstNode *node, const QString &mType, const QString &mName = QString())" << endl;
  out << "{" << endl;
  out << "    QString tokenString;" << endl;
  out << "    if (!m_content.isEmpty()) {" << endl;
  out << "        " << globalSystem.tokenStream << "::Token startToken = m_str->token(node->startToken);" << endl;
  out << "        " << globalSystem.tokenStream << "::Token endToken = m_str->token(node->endToken);" << endl;
  out << "        int begin = startToken.begin;" << endl;
  out << "        int end = endToken.end;" << endl;
  out << "        if (end-begin > 30) {" << endl;
  out << "            tokenString = m_content.mid(begin, 10);" << endl;
  out << "            tokenString += \" ...\";" << endl;
  out << "            tokenString += QString(\"%1 more\").arg(end-begin-20);" << endl;
  out << "            tokenString += \"... \";" << endl;
  out << "            tokenString += m_content.mid(end-10, 10);" << endl;
  out << "        } else {" << endl;
  out << "            tokenString = m_content.mid(begin, end-begin+1);" << endl;
  out << "        }" << endl;
  out << "        tokenString = tokenString.replace('\\n', \"\\\\n\");" << endl;
  out << "        tokenString = tokenString.replace('\\r', \"\\\\r\");" << endl;
  out << "    }" << endl;
  out << "    qint64 beginLine,endLine,beginCol,endCol;" << endl;
  out << "    m_str->startPosition(node->startToken, &beginLine, &beginCol);" << endl;
  out << "m_str->endPosition(node->endToken, &endLine, &endCol);" << endl;
  out << "qDebug() << QString().fill(' ', m_indent) + mName + (!mName.isEmpty() ? \"->\" : \"\") + mType + \"[\" << m_str->token( node->startToken ).begin"
      << " << \",\" << beginLine << \",\" << beginCol << "
      << "\"] --- [\" << m_str->token( node->endToken ).end <<"
      << " \",\" << endLine << \",\" << endCol "
      << "<< \"] \""
      << " << tokenString"
      << ";";
  out << "}" << endl;
  out << globalSystem.tokenStream << " *m_str;" << endl;
  out << "int m_indent;" << endl;
  out << "QString m_content;" << endl;
  out << "};" << endl;
}

void GenerateDebugVisitorRule::operator()(QPair<QString,
                                          Model::SymbolItem*> const &__it)
{
  Model::SymbolItem *sym = __it.second;
  mNames.clear();

  bool has_members = false;
  HasMemberNodes hms(has_members);
  hms(sym);

  #define O1(name) \
      out << "virtual void visit" << name \
          << "(" << name << "Ast *" << "node" \
          << ") {" << endl;
  #define O2(name) \
  out << "printToken(node, \"" << name << "\");" << endl;
  #define O3(name) \
    out << "++m_indent;"; \
        \
    out << "DefaultVisitor::visit" << name \
        << "(" << "node" \
        << ");" << endl; \
        \
    out << "m_indent--;"; \
        \
    out << "}" << endl << endl;
  
  if(isOperatorSymbol(sym))
  {
    O1("Prefix" + sym->mCapitalizedName)
    O2("prefix-" + sym->mName)
    O3("Prefix" + sym->mCapitalizedName)
    O1("Postfix" + sym->mCapitalizedName)
    O2("postfix-" + sym->mName)
    O3("Postfix" + sym->mCapitalizedName)
    O1("Binary" + sym->mCapitalizedName)
    O2("binary-" + sym->mName)
    O3("Binary" + sym->mCapitalizedName)
    O1("Ternary" + sym->mCapitalizedName)
    O2("ternary-" + sym->mName)
    O3("Ternary" + sym->mCapitalizedName)
  }
  else
  {
    O1(sym->mCapitalizedName)
    O2(sym->mName)

    World::Environment::iterator it = globalSystem.env.find(sym);
    while (it != globalSystem.env.end())
      {
        Model::EvolveItem *e = (*it);
        if (it.key() != sym)
          break;

        ++it;

        visitNode(e);
      }
    O3(sym->mCapitalizedName)
  }
  
  #undef O3
  #undef O2
  #undef O1
  
}

void GenerateDebugVisitorRule::visitVariableDeclaration(Model::VariableDeclarationItem *node)
{
  do
  {
    if (node->mStorageType != Model::VariableDeclarationItem::StorageAstMember)
      break;

    if (node->mVariableType != Model::VariableDeclarationItem::TypeNode)
      break; // nothing to do

    if (mNames.find(node->mName) != mNames.end())
      break;

    QString base_type = node->mCapitalizedType + "Ast*";

    if (node->mIsSequence)
      {
        out << "if (" << "node->" << node->mName << "Sequence" << ") {"
            << "const KDevPG::ListNode<" << base_type << "> *__it = "
            << "node->" << node->mName << "Sequence" << "->front()"
            << ", *__end = __it;" << endl
            << "do {" << endl
            << "printToken(__it->element, \"" << node->mType << "\", \"" << node->mName << "[]\");" << endl
            << "__it = __it->next;" << endl
            << "} while (__it != __end);" << endl
            << "}" << endl;
      }
    else
      {
        out << "if (node->" << node->mName << ") printToken(node->" << node->mName << ", \"" << node->mType << "\", \"" << node->mName << "\");" << endl;
      }

    mNames.insert(node->mName);

  } while(false);

  DefaultVisitor::visitVariableDeclaration(node);
}
}
