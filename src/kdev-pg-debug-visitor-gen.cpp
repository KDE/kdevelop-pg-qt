/*
    SPDX-FileCopyrightText: 2006 Alexander Dymo <adymo@kdevelop.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg-debug-visitor-gen.h"
#include "kdev-pg.h"
#include <iostream>

namespace KDevPG
{

void GenerateDebugVisitor::operator()()
{
  // the debug visitor class is header-only, thus we don't need an export macro here
  out << "class DebugVisitor: public DefaultVisitor {" << Qt::endl
      << "public:" << Qt::endl;

  out << "DebugVisitor("<< globalSystem.tokenStream << " *str, const QString& content = QString())" << Qt::endl;
  out << "    : m_str(str), m_indent(0), m_content(content) {}" << Qt::endl;
  GenerateDebugVisitorRule gen(out);
  for( World::SymbolSet::iterator it = globalSystem.symbols.begin();
       it != globalSystem.symbols.end(); ++it )
  {
    gen(qMakePair(it.key(), *it));
  }

  out << "private:" << Qt::endl;
  out << "void printToken(const AstNode *node, const QString &mType, const QString &mName = QString())" << Qt::endl;
  out << "{" << Qt::endl;
  out << "        KDevPG::TokenStream::Token startToken;" << Qt::endl;
  out << "        KDevPG::TokenStream::Token endToken;" << Qt::endl;
  out << "        qint64 line, column;" << Qt::endl;
  out << "        const bool isValidStartToken = (0 <= node->startToken && node->startToken < m_str->size());" << Qt::endl;
  out << "        QString startTokenString;" << Qt::endl;
  out << "        if (isValidStartToken) {" << Qt::endl;
  out << "            startToken = m_str->at(node->startToken);" << Qt::endl;
  out << "            m_str->startPosition(node->startToken, &line, &column);" << Qt::endl;
  out << "            startTokenString = QString::number(startToken.begin) + QLatin1String(\", \") + QString::number(line) + QLatin1String(\", \") + QString::number(column);" << Qt::endl;
  out << "        } else {" << Qt::endl;
  out << "            startTokenString = QLatin1String(\"invalid token index: \") + QString::number(node->startToken);" << Qt::endl;
  out << "        }" << Qt::endl;
  out << "        const bool isValidEndToken = (0 <= node->endToken && node->endToken < m_str->size());" << Qt::endl;
  out << "        QString endTokenString;" << Qt::endl;
  out << "        if (isValidEndToken) {" << Qt::endl;
  out << "            endToken = m_str->at(node->endToken);" << Qt::endl;
  out << "            m_str->startPosition(node->endToken, &line, &column);" << Qt::endl;
  out << "            endTokenString = QString::number(endToken.begin) + QLatin1String(\", \") + QString::number(line) + QLatin1String(\", \") + QString::number(column);" << Qt::endl;
  out << "        } else {" << Qt::endl;
  out << "            endTokenString = QLatin1String(\"invalid token index: \") + QString::number(node->endToken);" << Qt::endl;
  out << "        }" << Qt::endl;
  out << "        QString tokenString;" << Qt::endl;
  out << "        if (!m_content.isEmpty() && isValidStartToken && isValidEndToken) {" << Qt::endl;
  out << "            const int begin = startToken.begin;" << Qt::endl;
  out << "            const int end = endToken.end;" << Qt::endl;
  out << "            if (end-begin > 30) {" << Qt::endl;
  out << "                tokenString = m_content.mid(begin, 10);" << Qt::endl;
  out << "                tokenString += QStringLiteral(\" ...\");" << Qt::endl;
  out << "                tokenString += QStringLiteral(\"%1 more\").arg(end-begin-20);" << Qt::endl;
  out << "                tokenString += QStringLiteral(\"... \");" << Qt::endl;
  out << "                tokenString += QStringView(m_content).mid(end-10, 10);" << Qt::endl;
  out << "            }" << Qt::endl;
  out << "            else {" << Qt::endl;
  out << "                tokenString = m_content.mid(begin, end-begin+1);" << Qt::endl;
  out << "            }" << Qt::endl;
  out << "            tokenString.replace(QLatin1Char('\\n'), QLatin1String(\"\\\\n\"));" << Qt::endl;
  out << "            tokenString.replace(QLatin1Char('\\r'), QLatin1String(\"\\\\r\"));" << Qt::endl;
  out << "        }" << Qt::endl;
  out << "        qDebug() <<"
      << " QString(QString().fill(QLatin1Char(' '), m_indent) +"
      << " mName + QLatin1String(!mName.isEmpty() ? \"->\" : \"\") + mType +"
      << " QLatin1Char('[') + startTokenString + QLatin1String(\"] --- [\") + endTokenString + QLatin1String(\"] \")).toUtf8().constData()"
      << " << tokenString;" << Qt::endl;
  out << "}" << Qt::endl;
  out << globalSystem.tokenStream << " *m_str;" << Qt::endl;
  out << "int m_indent;" << Qt::endl;
  out << "QString m_content;" << Qt::endl;
  out << "};" << Qt::endl;
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
          << ") override {" << Qt::endl;
  #define O2(name) \
  out << "printToken(node, QStringLiteral(\"" << name << "\"));" << Qt::endl;
  #define O3(name) \
    out << "++m_indent;"; \
        \
    out << "DefaultVisitor::visit" << name \
        << "(" << "node" \
        << ");" << Qt::endl; \
        \
    out << "m_indent--;"; \
        \
    out << "}" << Qt::endl << Qt::endl;
  
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
            << ", *__end = __it;" << Qt::endl
            << "do {" << Qt::endl
            << "printToken(__it->element, QStringLiteral(\"" << node->mType << "\"), QStringLiteral(\"" << node->mName << "[]\"));" << Qt::endl
            << "__it = __it->next;" << Qt::endl
            << "} while (__it != __end);" << Qt::endl
            << "}" << Qt::endl;
      }
    else
      {
        out << "if (node->" << node->mName << ") printToken(node->" << node->mName << ", QStringLiteral(\"" << node->mType << "\"), QStringLiteral(\"" << node->mName << "\"));" << Qt::endl;
      }

    mNames.insert(node->mName);

  } while(false);

  DefaultVisitor::visitVariableDeclaration(node);
}
}
