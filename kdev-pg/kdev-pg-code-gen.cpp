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

#include "kdev-pg-code-gen.h"

#include <QtCore/QList>
#include <QtCore/QDebug>
#include <QtCore/QStack>
#include <QtCore/QStringList>

namespace KDevPG
{
  void generateCondition(World::NodeSet const &s, QTextStream& out)
  {
    bool initial = true;
    Model::Node *item = globalSystem.zero();

    QStringList tokens;
    World::NodeSet::const_iterator it = s.begin();
    while (it != s.end())
      {
        item = *it;
        ++it;

        if (Model::TerminalItem *t = nodeCast<Model::TerminalItem*>(item))
          tokens << t->mName;
      }
    tokens.sort();
    foreach (const QString &token, tokens)
      {
        if (!initial)
          out << endl << "|| ";

        out << "yytoken == Token_" << token;
        initial = false;
      }


    if (initial && isZero(item))
      out << "true /*epsilon*/";
  }

  void generateTestCondition(Model::Node *node, QTextStream& out)
  {
    World::NodeSet s = globalSystem.first(node);
    generateCondition(s, out);
  }

  QString generateParserCall(Model::NonTerminalItem *node, int catch_id, QTextStream& out)
  {
    static int __id = 0;
    static char __var[1024];
    QString symbol_name = node->mSymbol->mName;

    QString capSymbolName = node->mSymbol->mCapitalizedName;

    if (globalSystem.generateAst)
      {
        sprintf(__var, "__node_%d", __id);
        ++__id;

        out << capSymbolName << "Ast *" << __var << " = 0;" << endl
            << "if (!parse" << capSymbolName << "(&" << __var;

        if (node->mArguments[0] != '\0') // read: if (mArguments != "")
            out << ", " << node->mArguments;

        out << "))" << endl;
      }
    else
      {
        out << "if (!parse" << capSymbolName << "(" << node->mArguments << "))"
            << endl;
      }

    if (!catch_id)
      {
        out << "{" << endl;

        if (globalSystem.needStateManagement)
          out <<   "if (!mBlockErrors) {" << endl;

        out << "expectedSymbol(AstNode::" << capSymbolName << "Kind"
            << ", \"" << symbol_name << "\"" << ");" << endl;

        if (globalSystem.needStateManagement)
          out << "}" << endl;

        out << "return false;" << endl
            << "}" << endl;
      }
    else
      {
        out << "{ goto __catch_" << catch_id << "; }" << endl;
      }

    return __var;
  }

  void generateTokenTest(Model::TerminalItem *node, int catch_id, QTextStream& out)
  {
    out << "if (yytoken != Token_" << node->mName << ")" << endl;
    if (!catch_id)
      {
        out << "{" << endl;

        if (globalSystem.needStateManagement)
          out << "if (!mBlockErrors) {" << endl;

        out << "expectedToken(yytoken, Token_" << node->mName
            << ", \"" << node->mDescription << "\");" << endl;

        if (globalSystem.needStateManagement)
          out << "}" << endl;

        out << "return false;" << endl
            << "}" << endl;
      }
    else
      {
        out << "goto __catch_" << catch_id << ";" << endl;
      }
  }

  void generateRecovery(Model::Node *node, int catch_id, QTextStream& out)
  {
    World::NodeSet s = globalSystem.follow(node);
    Model::Node *item = globalSystem.zero();

    out << "if (try_startToken_" << catch_id
        << " == tokenStream->index() - 1)" << endl
        << "yylex();" << endl
        << endl;

    out << "while (yytoken != Token_EOF";

    World::NodeSet::iterator it = s.begin();
    while (it != s.end())
      {
        item = *it;
        ++it;

        if (Model::TerminalItem *t = nodeCast<Model::TerminalItem*>(item))
          out << endl << "&& yytoken != Token_" << t->mName;
      }

    out << ")" << endl
        << "{ yylex(); }" << endl;
  }


void CodeGenerator::operator()(Model::Node *node)
{
  mEvolve = nodeCast<Model::EvolveItem*>(node);
  Q_ASSERT(mEvolve != 0);
  visitNode(node);
}

void CodeGenerator::visitZero(Model::ZeroItem *node)
{
  Q_UNUSED(node);
  // out << " /* nothing to do */" << endl;
}

void CodeGenerator::visitSymbol(Model::SymbolItem *node)
{
  Q_UNUSED(node);
  // out << " /* nothing to do */" << endl;
}

void CodeGenerator::visitNonTerminal(Model::NonTerminalItem *node)
{
  generateParserCall(node, mCurrentCatchId, out);
}

void CodeGenerator::visitTerminal(Model::TerminalItem *node)
{
  generateTokenTest(node, mCurrentCatchId, out);

  out << "yylex();" << endl
      << endl;
}

void CodeGenerator::visitPlus(Model::PlusItem *node)
{
  out << "do {" << endl;
  visitNode(node->mItem);
  out << "} while (";
  generateTestCondition(node, out);
  out << ");" << endl;
}

void CodeGenerator::visitStar(Model::StarItem *node)
{
  out << "while (";
  generateTestCondition(node, out);
  out << ") {" << endl;
  visitNode(node->mItem);
  out << "}" << endl;
}

void CodeGenerator::visitAction(Model::ActionItem *node)
{
  DefaultVisitor::visitAction(node);
  out << node->mCode;
}

void CodeGenerator::visitCondition(Model::ConditionItem *node)
{
  DefaultVisitor::visitCondition(node);
}

void CodeGenerator::visitAlternative(Model::AlternativeItem *node)
{
  QList<Model::Node*> top_level_nodes;

  QStack<Model::Node*> working_list;
  working_list.push(node->mRight);
  working_list.push(node->mLeft);

  while (!working_list.empty())
    {
      Model::Node *n = working_list.top();
      working_list.pop();

      if (Model::AlternativeItem *a = nodeCast<Model::AlternativeItem*>(n))
        {
          working_list.push(a->mRight);
          working_list.push(a->mLeft);
        }
      else
        {
          top_level_nodes.push_back(n);
        }
    }

  QList<Model::Node*>::iterator it = top_level_nodes.begin();
  while (it != top_level_nodes.end())
    {
      Model::Node *n = *it;
      ++it;
      Model::ConditionItem *cond = nodeCast<Model::ConditionItem*>(n);

      out << "if (";

      if (cond)
        out << "(";

      generateTestCondition(n, out);

      if (cond)
        out << ") && (" << cond->mCode << ")";

      out << ") {" << endl;
      visitNode(n);
      out << "}";

      if (it != top_level_nodes.end())
        out << "else ";
      else
        {
          out << "else {" << endl;

          if (!mCurrentCatchId)
              out << "return false;" << endl;
          else
              out << "goto __catch_" << mCurrentCatchId << ";";

          out << "}" << endl;
        }
    }
}

void CodeGenerator::visitCons(Model::ConsItem *node)
{
  DefaultVisitor::visitCons(node);
}

void CodeGenerator::visitEvolve(Model::EvolveItem *node)
{
  out << "if (";

  Model::ConditionItem *cond = nodeCast<Model::ConditionItem*>(node->mItem);

  if (cond)
    out << "(";

  generateTestCondition(node, out);

  if (reducesToEpsilon(node->mItem))
    {
      out << " || ";
      generateCondition(globalSystem.follow(node->mSymbol), out);
    }

  if (cond)
    out << ") && (" << cond->mCode << ")";

  out << ") {" << endl;

  GenerateLocalDeclarations gen_locals(out, mNames);
  gen_locals(node->mItem);

  out << node->mCode;

  visitNode(node->mItem);

  if (node == globalSystem.start)
    out << "if (Token_EOF != yytoken) { return false; }" << endl;

  out << "}" << endl;
}

void CodeGenerator::visitTryCatch(Model::TryCatchItem *node)
{
  static int tryCatch_counter = 0;
  int previous_catch_id = setCatchId(++tryCatch_counter);

  if (node->mCatchItem) // node is a try/rollback block
    {
      out << "bool blockErrors_" << mCurrentCatchId
          << " = blockErrors(true);" << endl;
    }

  out << "qint64 try_startToken_" << mCurrentCatchId
      << " = tokenStream->index() - 1;" << endl;

  if (!node->mUnsafe)
    {
      out << "ParserState *try_startState_" << mCurrentCatchId
          << " = copyCurrentState();" << endl;
    }

  out << "{" << endl;
  visitNode(node->mTryItem);
  out << "}" << endl;

  if (node->mCatchItem)
    {
      out << "blockErrors(blockErrors_" << mCurrentCatchId << ");" << endl;
    }

  if (!node->mUnsafe)
    {
      out << "if (try_startState_" << mCurrentCatchId << ")" << endl
          << "delete try_startState_" <<  mCurrentCatchId << ";" << endl
          << endl;
    }

  out << "if (false) // the only way to enter here is using goto" << endl
      << "{" << endl
      << "__catch_" << mCurrentCatchId << ":" << endl;

  if (!node->mUnsafe)
    {
      out << "if (try_startState_" << mCurrentCatchId << ")" << endl
          << "{" << endl
          << "restoreState(try_startState_" <<  mCurrentCatchId << ");" << endl
          << "delete try_startState_" <<  mCurrentCatchId << ";" << endl
          << "}" << endl;
    }

  if (!node->mCatchItem)
    {
      generateRecovery(node, mCurrentCatchId, out);
      setCatchId(previous_catch_id);
    }
  else
    {
      out << "blockErrors(blockErrors_" << mCurrentCatchId << ");" << endl
          << "rewind(try_startToken_" << mCurrentCatchId << ");" << endl
          << endl;

      setCatchId(previous_catch_id);
      visitNode(node->mCatchItem);
    }

  out << "}" << endl
      << endl;
}

int CodeGenerator::setCatchId(int catch_id)
{
  int previous = mCurrentCatchId;
  mCurrentCatchId = catch_id;
  return previous;
}

void CodeGenerator::visitAlias(Model::AliasItem *node)
{
  Q_UNUSED(node);
  Q_ASSERT(0); // ### not implemented yet
}

void CodeGenerator::visitAnnotation(Model::AnnotationItem *node)
{
  if (!globalSystem.generateAst)
    {
      // qDebug() << "** WARNING annotation ignored" << endl;
      visitNode(node->mItem);
      return;
    }

  if (Model::TerminalItem *t = nodeCast<Model::TerminalItem*>(node->mItem))
    {
      generateTokenTest(t, mCurrentCatchId, out);

      if (node->mDeclaration->mIsSequence)
        {
          QString target;

          if (node->mDeclaration->mStorageType == Model::VariableDeclarationItem::StorageAstMember)
            target += "(*yynode)->";

          target += node->mDeclaration->mName;
          target += "Sequence";

          out << target << " = snoc(" << target << ", "
              << "tokenStream->index() - 1, memoryPool);" << endl
              << "yylex();" << endl
              << endl;
        }
      else
        {
          if (node->mDeclaration->mStorageType == Model::VariableDeclarationItem::StorageAstMember)
            out << "(*yynode)->";

          out << node->mDeclaration->mName
              << " = tokenStream->index() - 1;" << endl
              << "yylex();" << endl
              << endl;
        }
    }
  else if (Model::NonTerminalItem *nt = nodeCast<Model::NonTerminalItem*>(node->mItem))
    {
      QString __var = generateParserCall(nt, mCurrentCatchId, out);

      bool check_startToken = false;
      World::Environment::iterator it = globalSystem.env.find(nt->mSymbol);
      while (it != globalSystem.env.end())
        {
          Model::EvolveItem *e = (*it);
          if (it.key() != nt->mSymbol)
            break;

          ++it;

          Model::VariableDeclarationItem *current_decl = e->mDeclarations;
          while (current_decl)
            {
              if ((current_decl->mDeclarationType
                   == Model::VariableDeclarationItem::DeclarationArgument)
                  &&
                  (current_decl->mVariableType
                   != Model::VariableDeclarationItem::TypeVariable))
                {
                  check_startToken = true;
                  break;
                }

              current_decl = current_decl->mNext;
            }
        }

      if (check_startToken == true)
        {
          check_startToken = false;
          Model::VariableDeclarationItem *current_decl = mEvolve->mDeclarations;
          while (current_decl)
            {
              if ((current_decl->mStorageType
                   == Model::VariableDeclarationItem::StorageTemporary)
                  &&
                  (current_decl->mVariableType
                   != Model::VariableDeclarationItem::TypeVariable)
                  &&
                  (current_decl->mDeclarationType
                   == Model::VariableDeclarationItem::DeclarationArgument))
                {
                  check_startToken = true;
                  break;
                }

              current_decl = current_decl->mNext;
            }
        }

      if (check_startToken == true)
        {
          out << "if (" << __var << "->startToken < (*yynode)->startToken)" << endl
              << "(*yynode)->startToken = " << __var << "->startToken;" << endl;
        }

      QString target;
      if (node->mDeclaration->mStorageType == Model::VariableDeclarationItem::StorageAstMember)
        target += "(*yynode)->";

      target += node->mDeclaration->mName;

      if (node->mDeclaration->mIsSequence)
        {
          target += "Sequence";

          out << target << " = " << "snoc(" << target << ", "
              << __var << ", memoryPool);" << endl
              << endl;
        }
      else
        {
          out << target << " = " << __var << ";" << endl
              << endl;
        }
    }
  else
    Q_ASSERT(0); // ### not supported
}

void CodeGenerator::visitOperator(Model::OperatorItem *node)
{
  // generateTestCondition(node, out)
//   out << "if(";
//   generateTestCondition(node, out);
//   out << ")";
  out << "bool expectOperator = false;"
      << "while(true) {"
      << "if(expectOperator) {"
      << " ";
  const QString capNode = capitalized(node->mName);
  const QString nodeType = capNode + "Ast";    /// @TODO Add a unique name
  const QString baseNameC = node->mBase->mSymbol->mCapitalizedName;
  const QString baseType = baseNameC + "Ast";
  Model::NonTerminalItem ntItem;
  ntItem.mSymbol = mSym;
  ntItem.kind = Model::NodeKindNonTerminal;
  {
    QTextStream argStr(&ntItem.mArguments);
    GenerateRecursiveDelegation del(argStr);
  }
  bool printElse = false;
  for(__typeof__(node->mPost.begin()) i = node->mPost.begin(); i != node->mPost.end(); ++i)
  {
    if(printElse)
      out << "else ";
    printElse = true;
    out << "if(yytoken == Token_" << i->op.mTok;
    if(i->op.mCond.size() != 0)
      out << " && " << i->op.mCond;
    out << ") { const unsigned int priority = " << i->priority << ";";
    out << i->op.mCode;
    out << "AstNode *last = 0; bool br = false;";
    out << "while(priority " << (i->left ? "<=" : "<") << " opStack.last().p) {";
    out << "if(opStack.size() == 1) {"
           "if(last)\n"
           "opStack.last().n->endToken = last->endToken;"
           "last = opStack.last().n;"
           "opStack.pop_back();"
           "opStack.push_front(OperatorStackItem((*yynode) = create<Postfix"<< nodeType << ">(last), -1));"
           "(*yynode)->endToken = last->endToken + 1;"
           "(*yynode)->startToken = last->startToken;"
           "br = true; break; } else {"
           "AstNode *olast = last;"
           "last = opStack.last().n;\n"
           "if(olast)\nlast->endToken = olast->endToken;"
           "opStack.pop_back(); }}";
    out << "if(!br) { "
           "opStack.last().n->endToken = last->endToken;"
        << "AstNode*& ref = opStack.last().n->kind == AstNode::Binary" << capNode << "Kind && ((Binary" << nodeType << "*)opStack.last().n)->second ? ((Binary" << nodeType << "*)opStack.last().n)->second : ((Binary" << nodeType << "*)opStack.last().n)->first;\n"
        << "opStack.push_back(OperatorStackItem(ref = create<Postfix" << nodeType << ">(last), -1));"
          "ref->endToken = last->endToken + 1;"
          "ref->startToken = last->startToken;"
          "} yylex(); }";
  }
  for(__typeof__(node->mBin.begin()) i = node->mBin.begin(); i != node->mBin.end(); ++i)
  {
    if(printElse)
      out << "else ";
    printElse = true;
    out << "if(yytoken == Token_" << i->op.mTok;
    if(i->op.mCond.size() != 0)
      out << " && " << i->op.mCond;
    out << ") { const unsigned int priority = " << i->priority << ";";
    out << i->op.mCode;
    out << "AstNode *last = 0; bool br = false;";
    out << "while(priority " << (i->left ? "<=" : "<") << " opStack.last().p) {";
    out << "if(opStack.size() == 1) {"
           "if(last)\n"
           "opStack.last().n->endToken = last->endToken;"
           "last = opStack.last().n;\n"
           "opStack.pop_back();"
           "opStack.push_front(OperatorStackItem((*yynode) = create<Binary" << nodeType << ">(last), priority));"
           "(*yynode)->startToken = last->startToken;"
           "br = true; break; } else {"
           "AstNode *olast = last;"
           "last = opStack.last().n;\n"
           "if(olast)\nlast->endToken = olast->endToken;"
           "opStack.pop_back(); }}";
    out << "if(!br) { "
           "opStack.last().n->endToken = last->endToken;"
        << "AstNode*& ref = "
           "opStack.last().n->kind == AstNode::Ternary" << capNode << "Kind"
           "  ? (((Ternary" << nodeType << "*)opStack.last().n)->third"
           "   ? ((Ternary" << nodeType << "*)opStack.last().n)->third"
           "   : (((Ternary" << nodeType << "*)opStack.last().n)->second"
           "    ? ((Ternary" << nodeType << "*)opStack.last().n)->second"
           "    : ((Ternary" << nodeType << "*)opStack.last().n)->first ))"
           "  : opStack.last().n->kind == AstNode::Binary" << capNode << "Kind"
           " && ((Binary" << nodeType << "*)opStack.last().n)->second"
           "  ? ((Binary" << nodeType << "*)opStack.last().n)->second"
           "  : ((Binary" << nodeType << "*)opStack.last().n)->first;\n"
        << "opStack.push_back(OperatorStackItem(ref = create<Binary" << nodeType << ">(last), priority)); ref->startToken = last->startToken; } expectOperator = false; yylex(); }";
  }
  for(__typeof__(node->mTern.begin()) i = node->mTern.begin(); i != node->mTern.end(); ++i)
  {
    if(printElse)
      out << "else ";
    printElse = true;
    out << "if(yytoken == Token_" << i->first.mTok;
    if(i->first.mCond.size() != 0)
      out << " && " << i->first.mCond;
        out << ") { const unsigned int priority = " << i->priority << ";";
    out << i->first.mCode;
    out << "AstNode *last = 0; bool br = false;";
    out << "while(priority " << (i->left ? "<=" : "<") << " opStack.last().p) {";
    out << "if(opStack.size() == 1) {"
           "if(last)\n"
           "opStack.last().n->endToken = last->endToken;"
           "last = opStack.last().n;\n"
           "opStack.pop_back();"
           "opStack.push_front(OperatorStackItem((*yynode) = create<Ternary" << nodeType << ">(last), priority));"
           "(*yynode)->startToken = last->startToken;"
           "yylex();";
    QString __var = generateParserCall(&ntItem, mCurrentCatchId, out);
    out << "if(!(yytoken == Token_" << i->second.mTok;
    if(i->second.mCond.size() != 0)
      out << " && " << i->second.mCond;
    out << ")) return false;"
           "((Ternary" << nodeType << "*)*yynode)->second = "
        << __var
        << ";br = true; break; } else {"
           "AstNode *olast = last;"
           "last = opStack.last().n;\n"
           "if(olast)\nlast->endToken = olast->endToken;"
           "opStack.pop_back(); }}";
    out << "if(!br) { "
           "opStack.last().n->endToken = last->endToken;"
        << "AstNode*& ref = "
           "opStack.last().n->kind == AstNode::Ternary" << capNode << "Kind"
           "  ? (((Ternary" << nodeType << "*)opStack.last().n)->third"
           "   ? ((Ternary" << nodeType << "*)opStack.last().n)->third"
           "   : (((Ternary" << nodeType << "*)opStack.last().n)->second"
           "    ? ((Ternary" << nodeType << "*)opStack.last().n)->second"
           "    : ((Ternary" << nodeType << "*)opStack.last().n)->first ))"
           "  : opStack.last().n->kind == AstNode::Binary" << capNode << "Kind"
           " && ((Binary" << nodeType << "*)opStack.last().n)->second"
           "  ? ((Binary" << nodeType << "*)opStack.last().n)->second"
           "  : ((Binary" << nodeType << "*)opStack.last().n)->first;\n"
        << "opStack.push_back(OperatorStackItem(ref = create<Ternary" << nodeType << ">(last), priority)); ref->startToken = last->startToken; } expectOperator = false; yylex(); }";
  }
  out << "else ";
  out << "break;";
  out << "} else {";
  printElse = false;
  for(__typeof__(node->mPre.begin()) i = node->mPre.begin(); i != node->mPre.end(); ++i)
  {
    if(printElse)
      out << "else ";
    printElse = true;
    out << "if(yytoken == Token_" << i->op.mTok;
    if(i->op.mCond.size() != 0)
      out << " && " << i->op.mCond;
    out << ") { const unsigned int priority = " << i->priority << ";";
    out << i->op.mCode
        << "Prefix" << nodeType << " *node = create<Prefix" << nodeType << ">();"
           "if(opStack.empty())\n"
           "(*yynode) = node;"
           "void *last = opStack.last().n;"
           "if(last)\n"
           "{\n"
           "if(reinterpret_cast<Prefix" << nodeType << "*>(last)->first == 0)\n"
           "reinterpret_cast<Prefix" << nodeType << "*>(last)->first = node;"
           "else if(reinterpret_cast<Binary" << nodeType << "*>(last)->second == 0)\n"
           "reinterpret_cast<Binary" << nodeType << "*>(last)->second = node;"
           "else\n"
           "reinterpret_cast<Ternary" << nodeType << "*>(last)->third = node;"
           "}"
           "opStack.push_back(OperatorStackItem(node, priority));"
           "node->startToken = tokenStream->index() - 1;"
           "yylex();"
           "}" << endl;
  }
  for(__typeof__(node->mParen.begin()) i = node->mParen.begin(); i != node->mParen.end(); ++i)
  {
    if(printElse)
      out << "else ";
    printElse = true;
    out << "if(yytoken == Token_" << i->first.mTok;
    if(i->first.mCond.size() != 0)
      out << " && " << i->first.mCond;
    out << ") { yylex();"
           "if(";
    generateTestCondition(mSym, out);
    out << ") {";
    QString __var = generateParserCall(&ntItem, mCurrentCatchId, out);
    out << "if(!(yytoken == Token_" << i->second.mTok;
    if(i->second.mCond.size() != 0)
      out << " && " << i->second.mCond;
    out << ")) {"
           "return false;"
           "}"
           "--" << __var << "->startToken;"
           "++" << __var << "->endToken;"
           "yylex();";
    #define PUSH_UNARY \
        out << "\
if(!opStack.isEmpty())\
{\
  void *last = opStack.last().n;\
  if(reinterpret_cast<Prefix" << nodeType << "*>(last)->first == 0)\n\
    reinterpret_cast<Prefix" << nodeType << "*>(last)->first = " << __var << ";" << endl; \
  out << "else if(reinterpret_cast<Binary" << nodeType << "*>(last)->second == 0)\n\
  reinterpret_cast<Binary" << nodeType << "*>(last)->second = " << __var << ";\
  else\nreinterpret_cast<Ternary" << nodeType << "*>(last)->third = " << __var << ";}\
else\n\
(*yynode) = " << __var << ";\
opStack.push_back(OperatorStackItem(" << __var << ", -1));";
    PUSH_UNARY
    out << "expectOperator = true; } else\nreturn false; }";
  }
  if(printElse)
    out << "else ";
  out << "if(";
  generateTestCondition(node->mBase->mSymbol, out);
  out << ") { ";
  QString __var = generateParserCall(node->mBase, mCurrentCatchId, out);
  PUSH_UNARY
  #undef PUSH_UNARY
  out << "expectOperator = true; }";
  /*for(__typeof__(node->mParen.begin()) i = node->mParen.begin(); i != node->mParen.end(); ++i)
  {
    if(printElse)
      out << "else ";
    printElse = true;
    out << "if(yytoken == Token_" << i->first.mTok;
    if(i->first.mCond.size() != 0)
      out << " && " << i->first.mCond;
    out << ") { " << i->first.mCode << " }";
  }*/
  /*for(__typeof__(node->mPre.begin()) i = node->mPre.begin(); i != node->mPre.end(); ++i)
  {
    if(printElse)
      out << "else ";
    printElse = true;
    out << "if(yytoken == Token_" << i->op.mTok;
    if(i->op.mCond.size() != 0)
      out << " && " << i->op.mCond;
    out << ") { const unsigned int priority = " << i->priority << ";";
    out << i->op.mCode;
    out << "... }";
  }*/
  out << "else ";
  out << "break;";
  out << "} }";
  /// @TODO Further: empty binary operator
}


void GenerateForwardParserRule::operator()(QPair<QString, Model::SymbolItem*> const &__it)
{
  Model::SymbolItem *sym = __it.second;
  out << "bool" << " " << "parse" << sym->mCapitalizedName << "(";

  GenerateParseMethodSignature gen_signature(out, 0);
  gen_signature(sym);

  out << ");" << endl;
}

void GenerateParserRule::operator()(QPair<QString, Model::SymbolItem*> const &__it)
{
  mNames.clear();
  Model::SymbolItem *sym = __it.second;
  CodeGenerator cg(out, &mNames, sym);

  out << "bool Parser::parse" << sym->mCapitalizedName << "(";

  GenerateParseMethodSignature gen_signature(out, &mNames);
  gen_signature(sym);

  out << ")" << endl
      << "{" << endl;

  if (globalSystem.generateAst)
    {
      if(isOperatorSymbol(sym))
        out << "QVector<OperatorStackItem> opStack;" << endl;
      else
      {
        out << "*yynode = create<" << sym->mCapitalizedName << "Ast" << ">();" << endl << endl
            << "(*yynode)->startToken = tokenStream->index() - 1;" << endl;
        //Generate initialization for this ast nodes token-members using -1 as invalid value
        GenerateTokenVariableInitialization gentokenvar( out );
        gentokenvar(sym);
        out << endl;
      }
    }

  World::Environment::iterator it = globalSystem.env.find(sym);
  GenerateLocalDeclarations gen_locals(out, &mNames);
  while (it != globalSystem.env.end())
    {
      Model::EvolveItem *e = (*it);
      if (it.key() != sym)
        break;

      ++it;
      gen_locals(e->mDeclarations);
    }

  it = globalSystem.env.find(sym);
  bool initial = true;
  while (it != globalSystem.env.end())
    {
      Model::EvolveItem *e = (*it);
      if (it.key() != sym)
        break;

      ++it;

      if (!initial)
        out << "else ";

      cg(e);
      initial = false;
    }

  out << "else" << endl << "{ return false; }" << endl
      << endl;


  if (globalSystem.generateAst)
    {
      if(isOperatorSymbol(sym))
      {
        out << "AstNode *olast, *last = 0;"
               "while(!opStack.empty())\n"
               "{"
               "olast = last;"
               "last = opStack.last().n;"
               "bool fail = false;"
               "if(last->kind == AstNode::Ternary" << sym->mCapitalizedName << "Kind)\n"
               "fail = ((Ternary" << sym->mCapitalizedName << "Ast*)last)->third == 0;"
               "else if(last->kind == AstNode::Binary" << sym->mCapitalizedName << "Kind)\n"
               "fail = ((Binary" << sym->mCapitalizedName << "Ast*)last)->second == 0;"
               "else\n"
               "fail = ((Prefix" << sym->mCapitalizedName << "Ast*)last)->first == 0;"
               "if(fail){"
               "expectedSymbol(AstNode::" << sym->mCapitalizedName << "Kind"
            << ", \"" << sym->mName << "\"" << ");return false;}"
               "if(olast)\n"
               "last->endToken = olast->endToken;"
               "opStack.pop_back();"
               "}" << endl;
      }
      else
      {
        out << "(*yynode)->endToken = tokenStream->index() - 2;" << endl
            << endl;
      }
    }

  out << "return true;" << endl
      << "}" << endl
      << endl;
}

void GenerateLocalDeclarations::operator()(Model::Node *node)
{
  visitNode(node);
}

void GenerateLocalDeclarations::visitVariableDeclaration(Model::VariableDeclarationItem *node)
{
  // normal declarations for local variables
  if (node->mStorageType == Model::VariableDeclarationItem::StorageTemporary
      && node->mDeclarationType == Model::VariableDeclarationItem::DeclarationLocal)
    {
      if ((mNames == 0) || mNames->find(node->mName) == mNames->end())
        {
          GenerateVariableDeclaration<true, true> gen_var_decl(out);
          gen_var_decl(node);

          if (node->mVariableType == Model::VariableDeclarationItem::TypeToken
              || node->mVariableType == Model::VariableDeclarationItem::TypeNode
              || node->mIsSequence)
            {
              out << " = 0";
            }

          out << ";" << endl << endl;

          if (mNames != 0)
            mNames->insert(node->mName);
        }
    }

  // for argument member nodes and tokens, check if their index precedes the current one
  else if (node->mStorageType == Model::VariableDeclarationItem::StorageAstMember
           && node->mDeclarationType == Model::VariableDeclarationItem::DeclarationArgument
           && globalSystem.generateAst)
    {
      QString sequence_suffix = (node->mIsSequence) ? "Sequence" : "";

      out << "(*yynode)->" << node->mName << sequence_suffix << " = "
          << node->mName << sequence_suffix << ";" << endl;

      if (node->mVariableType != Model::VariableDeclarationItem::TypeVariable)
        {
          QString argument_startToken = node->mName;
          if (node->mIsSequence)
            argument_startToken += "Sequence->front()->element";

          if (node->mVariableType == Model::VariableDeclarationItem::TypeNode)
            argument_startToken += "->startToken";

          out << "if (";

          // check that the variable is not null
          if (node->mVariableType == Model::VariableDeclarationItem::TypeNode
              || node->mIsSequence)
            {
              out << node->mName << sequence_suffix << " && ";
            }

          out << argument_startToken << " < (*yynode)->startToken)" << endl
              << "(*yynode)->startToken = " << argument_startToken << ";"
            << endl << endl;
        }
    }

  DefaultVisitor::visitVariableDeclaration(node);
}

void GenerateParseMethodSignature::operator()(Model::SymbolItem* sym)
{
  if (globalSystem.generateAst)
    {
      out << sym->mCapitalizedName << "Ast **yynode";
      firstParameter = false;
    }

  World::Environment::iterator it = globalSystem.env.find(sym);
  if (it != globalSystem.env.end())
    {
      // this creates the method signature using just the first of
      // possibly multiple rules with the same name.
      Model::EvolveItem *e = (*it);
      if (e->mDeclarations)
        visitNode(e->mDeclarations);
    }
}

void GenerateRecursiveDelegation::operator()(Model::SymbolItem* node)
{
  World::Environment::iterator it = globalSystem.env.find(node);
  if (it != globalSystem.env.end())
  {
    // this creates the method signature using just the first of
    // possibly multiple rules with the same name.
    Model::EvolveItem *e = (*it);
    Model::VariableDeclarationItem *decl = e->mDeclarations;
    GenerateVariableDeclaration<false, true> vd(out);
    while(decl)
    {
      vd(decl);
      decl = decl->mNext;
    }
  }
}

void GenerateParseMethodSignature::visitVariableDeclaration(Model::VariableDeclarationItem *node)
{
  if (node->mDeclarationType == Model::VariableDeclarationItem::DeclarationArgument)
    {
      if (globalSystem.generateAst || (node->mStorageType != Model::VariableDeclarationItem::StorageAstMember))
        {
          if (firstParameter)
            firstParameter = false;
          else
            out << ", ";

          GenerateVariableDeclaration<true, true> gen_var_decl(out);
          gen_var_decl(node);

          if (mNames != 0)
            mNames->insert(node->mName);
        }
    }

  DefaultVisitor::visitVariableDeclaration(node);
}

template<bool printType, bool printName>
void GenerateVariableDeclaration<printType, printName>::operator()(Model::VariableDeclarationItem *node)
{
  if(printType)
  {
    if (node->mIsSequence)
      out << "const KDevPG::ListNode<";

    if (node->mVariableType == Model::VariableDeclarationItem::TypeToken)
      out << "qint64 ";
    else if (node->mVariableType == Model::VariableDeclarationItem::TypeNode)
    {
      out << node->mCapitalizedType << "Ast *";
    }else if (node->mVariableType == Model::VariableDeclarationItem::TypeVariable)
      out << node->mType << " ";
    else
      Q_ASSERT(0); // ### not supported

    if (node->mIsSequence)
      out << "> *";
  }

  if(printName)
  {
    out << node->mName;

    if (node->mIsSequence)
      out << "Sequence";
  }
}

void GenerateToken::operator()(QPair<QString, Model::TerminalItem*> const &__it)
{
  Model::TerminalItem *t = __it.second;
  out << "Token_" << t->mName << " = " << mTokenValue << "," << endl;
  ++mTokenValue;
}

void GenerateMemberCode::operator()(Settings::MemberItem* m)
{
  if ((mKindMask & m->mMemberKind) != 0)
    {
      if (m->mMemberKind == Settings::MemberItem::PublicDeclaration)
        out << "public:" << endl;
      else if (m->mMemberKind == Settings::MemberItem::ProtectedDeclaration)
        out << "protected:" << endl;
      else if (m->mMemberKind == Settings::MemberItem::PrivateDeclaration)
        out << "private:" << endl;

      out << m->mCode << endl;
    }
}

void GenerateParserDeclarations::operator()()
{
  out << "class " << globalSystem.exportMacro << " Parser ";
  if(!globalSystem.parserBaseClass.isEmpty())
    out << ": public " << globalSystem.parserBaseClass << " ";
  out << "{"
      << "public:" << endl
//       << "typedef " << globalSystem.tokenStream << " tokenStreamType;" << endl
      << "typedef " << globalSystem.tokenStream << "::Token Token;" << endl
      << globalSystem.tokenStream << " *tokenStream;" << endl
      << "int yytoken;" << endl;
  if(globalSystem.needOperatorStack)
    out << "struct OperatorStackItem{AstNode *n; int unsigned p;"
           "inline OperatorStackItem(AstNode *n, int unsigned p)\n"
           ": n(n), p(p)\n{}\n"
           "inline OperatorStackItem()\n{}\n"
           "inline OperatorStackItem(const OperatorStackItem& o)\n"
           ": n(o.n), p(o.p)\n"
           "{}\n};" << endl;
  out << endl
      << "inline Token LA(qint64 k = 1) const" << endl
      << "{ return tokenStream->token(tokenStream->index() - 1 + k - 1); }"
      << endl
      << "inline int yylex() {" << endl
      << "return (yytoken = tokenStream->nextToken());" << endl
      << "}" << endl
      << "inline void rewind(qint64 index) {" << endl
      << "tokenStream->rewind(index);" << endl
      << "yylex();" << endl
      << "}" << endl
      << endl;

  out << "// token stream" << endl
      << "void setTokenStream(" << globalSystem.tokenStream << " *s)" << endl
      << "{ tokenStream = s; }" << endl
      << endl;

  out << "// error handling" << endl
      << "void expectedSymbol(int kind, const QString& name);" << endl
      << "void expectedToken(int kind, qint64 token, const QString& name);" << endl
      << endl
      << "bool mBlockErrors;" << endl
      << "inline bool blockErrors(bool block) {" << endl
      << "bool previous = mBlockErrors;" << endl
      << "mBlockErrors = block;" << endl
      << "return previous;" << endl
      << "}" << endl;

  out << endl;

    if (globalSystem.generateAst)
      {
        out << "// memory pool" << endl
            << "typedef KDevPG::MemoryPool memoryPoolType;" << endl
            << endl
            << "KDevPG::MemoryPool *memoryPool;" << endl
            << "void setMemoryPool(KDevPG::MemoryPool *p)" << endl
            << "{ memoryPool = p; }" << endl
            << "template <class T>" << endl
            << "inline T *create()" << endl
            << "{" << endl
            << "T *node = new (memoryPool->allocate(sizeof(T))) T();" << endl
            << "node->kind = T::KIND;" << endl
            << "return node;" << endl
            << "}" << endl
            << "template <class T>" << endl
            << "inline T *create(AstNode *u)" << endl
            << "{" << endl
            << "T *node = new (memoryPool->allocate(sizeof(T))) T(u);" << endl
            << "node->kind = T::KIND;" << endl
            << "return node;" << endl
            << "}" << endl
            << endl;
      }


  out << "enum TokenType" << endl << "{" << endl;
  GenerateToken gen(out);
  for(World::TerminalSet::iterator it = globalSystem.terminals.begin(); it != globalSystem.terminals.end(); ++it )
  {
    gen(qMakePair(it.key(), *it));
  }
  out << "TokenTypeSize" << endl
      << "}; // TokenType" << endl
      << endl;


  if (globalSystem.parserclassMembers.declarations.empty() == false)
    {
      out << "// user defined declarations:" << endl;
      GenerateMemberCode gen(out, Settings::MemberItem::PublicDeclaration
                            | Settings::MemberItem::ProtectedDeclaration
                            | Settings::MemberItem::PrivateDeclaration);
      for( QList<Settings::MemberItem*>::iterator it = globalSystem.parserclassMembers.declarations.begin();
                    it != globalSystem.parserclassMembers.declarations.end(); ++it )
      {
                    gen(*it);
      }
      out << endl << "public:" << endl;
    }

  if (globalSystem.needStateManagement)
    {
      out << "// The copyCurrentState() and restoreState() methods are only declared" << endl
          << "// if you are using try blocks in your grammar, and have to be" << endl
          << "// implemented by yourself, and you also have to define a" << endl
          << "// \"struct ParserState\" inside a %parserclass directive." << endl
          << endl
          << "// This method should create a new ParserState object and return it," << endl
          << "// or return 0 if no state variables need to be saved." << endl
          << "ParserState *copyCurrentState();" << endl
          << endl
          << "// This method is only called for ParserState objects != 0" << endl
          << "// and should restore the parser state given as argument." << endl
          << "void restoreState(ParserState *state);" << endl;
    }

  out << "Parser() {" << endl;
  if (globalSystem.generateAst)
    {
      out << "memoryPool = 0;" << endl;
    }

  out << "tokenStream = 0;" << endl
      << "yytoken = Token_EOF;" << endl
      << "mBlockErrors = false;" << endl;

  if (globalSystem.parserclassMembers.constructorCode.empty() == false)
    {
      out << endl << "// user defined constructor code:" << endl;
      GenerateMemberCode gen(out, Settings::MemberItem::ConstructorCode);
      for(QList<Settings::MemberItem*>::iterator it =
            globalSystem.parserclassMembers.constructorCode.begin();
            it != globalSystem.parserclassMembers.constructorCode.end(); ++it )
      {
        gen(*it);
      }
    }

  out << "}" << endl << endl;

  out << "virtual ~Parser() {";

  if (globalSystem.parserclassMembers.destructorCode.empty() == false)
    {
      out << endl
          << "// user defined destructor code:" << endl;

      GenerateMemberCode gen(out, Settings::MemberItem::DestructorCode);
      for(QList<Settings::MemberItem*>::iterator it = globalSystem.parserclassMembers.destructorCode.begin();
                    it != globalSystem.parserclassMembers.destructorCode.end(); ++it )
      {
        gen(*it);
      }
    }

  out << "}" << endl << endl;

  GenerateForwardParserRule genfwdparserrule(out);
  for( World::SymbolSet::iterator it = globalSystem.symbols.begin();
       it != globalSystem.symbols.end(); ++it )
  {
    genfwdparserrule(qMakePair(it.key(), *it));
  }

  out << "};" << endl;
}

void GenerateParserBits::operator()()
{
  GenerateParserRule gen(out);
  for( World::SymbolSet::iterator it = globalSystem.symbols.begin();
       it != globalSystem.symbols.end(); ++it )
  {
    gen(qMakePair(it.key(), *it));
  }
}

void GenerateTokenVariableInitialization::operator()(Model::SymbolItem* sym)
{

  World::Environment::iterator it = globalSystem.env.find(sym);
  if (it != globalSystem.env.end())
    {
      // this creates the method signature using just the first of
      // possibly multiple rules with the same name.
      Model::EvolveItem *e = (*it);
      if (e->mItem)
        visitNode(e->mItem);
    }
}

void GenerateTokenVariableInitialization::visitVariableDeclaration(Model::VariableDeclarationItem *node)
{
  if( node->mVariableType == Model::VariableDeclarationItem::TypeToken )
  {
    if( !node->mIsSequence )
      out << "(*yynode)->" << node->mName << " = -1;" << endl;
  }
}


void GenerateTokenTexts::operator()()
{
  out << "switch (token) {" << endl;
  GenerateToken gen(out);
  for(World::TerminalSet::iterator it = globalSystem.terminals.begin(); it != globalSystem.terminals.end(); ++it )
  {
    Model::TerminalItem* t = *it;
    out << "    case Parser::Token_" << t->mName << ":" << endl;
    QString text = t->mDescription;
    text.replace('\\', "\\\\").replace('"', "\\\"");
    out << "        return \"" <<  text << "\";" << endl;
  }
  out << "    default:" << endl;
  out << "        return \"unknown token\";" << endl;
  out << "}" << endl;
}


} // namespace KDevPG
