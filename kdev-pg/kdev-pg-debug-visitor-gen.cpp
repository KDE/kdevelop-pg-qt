/* This file is part of kdev-pg-qt
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
  // the debug visitor class is header-only, thus we don't need an export macro here
  out << "class DebugVisitor: public DefaultVisitor {" << endl
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
  out << "void printToken(const AstNode *node, const QString &mType, const QString &mName = QString())" << endl;
  out << "{" << endl;
  out << "        KDevPG::TokenStream::Token startToken;" << endl;
  out << "        KDevPG::TokenStream::Token endToken;" << endl;
  out << "        qint64 line, column;" << endl;
  out << "        const bool isValidStartToken = (0 <= node->startToken && node->startToken < m_str->size());" << endl;
  out << "        QString startTokenString;" << endl;
  out << "        if (isValidStartToken) {" << endl;
  out << "            startToken = m_str->at(node->startToken);" << endl;
  out << "            m_str->startPosition(node->startToken, &line, &column);" << endl;
  out << "            startTokenString = QString::number(startToken.begin) + QLatin1String(\", \") + QString::number(line) + QLatin1String(\", \") + QString::number(column);" << endl;
  out << "        } else {" << endl;
  out << "            startTokenString = QLatin1String(\"invalid token index: \") + QString::number(node->startToken);" << endl;
  out << "        }" << endl;
  out << "        const bool isValidEndToken = (0 <= node->endToken && node->endToken < m_str->size());" << endl;
  out << "        QString endTokenString;" << endl;
  out << "        if (isValidEndToken) {" << endl;
  out << "            endToken = m_str->at(node->endToken);" << endl;
  out << "            m_str->startPosition(node->endToken, &line, &column);" << endl;
  out << "            endTokenString = QString::number(endToken.begin) + QLatin1String(\", \") + QString::number(line) + QLatin1String(\", \") + QString::number(column);" << endl;
  out << "        } else {" << endl;
  out << "            endTokenString = QLatin1String(\"invalid token index: \") + QString::number(node->endToken);" << endl;
  out << "        }" << endl;
  out << "        QString tokenString;" << endl;
  out << "        if (!m_content.isEmpty() && isValidStartToken && isValidEndToken) {" << endl;
  out << "            const int begin = startToken.begin;" << endl;
  out << "            const int end = endToken.end;" << endl;
  out << "            if (end-begin > 30) {" << endl;
  out << "                tokenString = m_content.mid(begin, 10);" << endl;
  out << "                tokenString += QStringLiteral(\" ...\");" << endl;
  out << "                tokenString += QStringLiteral(\"%1 more\").arg(end-begin-20);" << endl;
  out << "                tokenString += QStringLiteral(\"... \");" << endl;
  out << "                tokenString += m_content.midRef(end-10, 10);" << endl;
  out << "            }" << endl;
  out << "            else {" << endl;
  out << "                tokenString = m_content.mid(begin, end-begin+1);" << endl;
  out << "            }" << endl;
  out << "            tokenString.replace('\\n', QStringLiteral(\"\\\\n\"));" << endl;
  out << "            tokenString.replace('\\r', QStringLiteral(\"\\\\r\"));" << endl;
  out << "        }" << endl;
  out << "        qDebug() <<"
      << " QString(QString().fill(QLatin1Char(' '), m_indent) +"
      << " mName + QLatin1String(!mName.isEmpty() ? \"->\" : \"\") + mType +"
      << " QLatin1Char('[') + startTokenString + QLatin1String(\"] --- [\") + endTokenString + QLatin1String(\"] \")).toUtf8().constData()"
      << " << tokenString;" << endl;
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
      out << "void visit" << name \
          << "(" << name << "Ast *" << "node" \
          << ") override {" << endl;
  #define O2(name) \
  out << "printToken(node, QStringLiteral(\"" << name << "\"));" << endl;
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
            << "printToken(__it->element, QStringLiteral(\"" << node->mType << "\"), QStringLiteral(\"" << node->mName << "[]\"));" << endl
            << "__it = __it->next;" << endl
            << "} while (__it != __end);" << endl
            << "}" << endl;
      }
    else
      {
        out << "if (node->" << node->mName << ") printToken(node->" << node->mName << ", QStringLiteral(\"" << node->mType << "\"), QStringLiteral(\"" << node->mName << "\"));" << endl;
      }

    mNames.insert(node->mName);

  } while(false);

  DefaultVisitor::visitVariableDeclaration(node);
}
}
