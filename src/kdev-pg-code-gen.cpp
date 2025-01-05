/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>
    SPDX-FileCopyrightText: 2010 Jonathan Schmidt-Dominé <devel@the-user.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg-code-gen.h"

#include <QList>
#include <QDebug>
#include <QStack>
#include <QStringList>
#include "kdev-pg-pretty-printer.h"

namespace KDevPG
{
  extern QTextStream checkOut;
  
  void generateConditionFromStrings(QStringList &tokens, bool zerop, QTextStream& out)
  {
    tokens.sort();
    bool initial = true;
    for (const QString &token : std::as_const(tokens))
      {
        if (!initial)
          out << Qt::endl << "|| ";

        out << "yytoken == Token_" << token;
        initial = false;
      }


    if (initial && zerop)
      out << "true /*epsilon*/";
  }

  void generateCondition(const World::NodeSet& s, QTextStream& out)
  {
    if(s.size() == 0 || (s.size() == 1 && nodeCast<Model::ZeroItem*>(*s.begin()) != nullptr))
    {
      out << "true /*epsilon*/";
      return;
    }
    
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
    generateConditionFromStrings(tokens, false, out);
  }

  void generateTestCondition(Model::Node *node, QTextStream& out)
  {
    if(node->kind == Model::NodeKindTerminal)
    {
      QStringList tokens;
      tokens << ((Model::TerminalItem*)node)->mName;
      generateConditionFromStrings(tokens, false, out);
    }
    else
    {
      World::NodeSet& s = globalSystem.first(node);
      
      generateCondition(s, out);
    }
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

        out << capSymbolName << "Ast *" << __var << " = nullptr;" << Qt::endl
            << "if (!parse" << capSymbolName << "(&" << __var;

        if (!node->mArguments.isEmpty())
            out << ", " << node->mArguments;

        out << "))" << Qt::endl;
      }
    else
      {
        out << "if (!parse" << capSymbolName << "(" << node->mArguments << "))"
            << Qt::endl;
      }

    if (!catch_id)
      {
        out << "{" << Qt::endl;

        if (globalSystem.needStateManagement)
          out <<   "if (!mBlockErrors) {" << Qt::endl;

        out << "expectedSymbol(AstNode::" << capSymbolName << "Kind"
            << ", QStringLiteral(\"" << symbol_name << "\")" << ");" << Qt::endl;

        if (globalSystem.needStateManagement)
          out << "}" << Qt::endl;

        out << "return false;" << Qt::endl
            << "}" << Qt::endl;
      }
    else
      {
        out << "{ goto __catch_" << catch_id << "; }" << Qt::endl;
      }

    return __var;
  }

  void generateTokenTest(Model::TerminalItem *node, int catch_id, QTextStream& out)
  {
    out << "if (yytoken != Token_" << node->mName << ")" << Qt::endl;
    if (!catch_id)
      {
        out << "{" << Qt::endl;

        if (globalSystem.needStateManagement)
          out << "if (!mBlockErrors) {" << Qt::endl;

        out << "expectedToken(yytoken, Token_" << node->mName
            << ", QStringLiteral(\"" << node->mDescription << "\"));" << Qt::endl;

        if (globalSystem.needStateManagement)
          out << "}" << Qt::endl;

        out << "return false;" << Qt::endl
            << "}" << Qt::endl;
      }
    else
      {
        out << "goto __catch_" << catch_id << ";" << Qt::endl;
      }
  }

  void generateRecovery(Model::Node *node, int catch_id, QTextStream& out)
  {
    World::NodeSet s = globalSystem.follow(node);
    Model::Node *item = globalSystem.zero();

    out << "if (try_startToken_" << catch_id
        << " == tokenStream->index() - 1  && yytoken != Token_EOF)" << Qt::endl
        << "yylex();" << Qt::endl
        << Qt::endl;

    out << "while (yytoken != Token_EOF";

    World::NodeSet::iterator it = s.begin();
    while (it != s.end())
      {
        item = *it;
        ++it;

        if (Model::TerminalItem *t = nodeCast<Model::TerminalItem*>(item))
          out << Qt::endl << "&& yytoken != Token_" << t->mName;
      }

    out << ")" << Qt::endl
        << "{ yylex(); }" << Qt::endl;
  }


void CodeGenerator::operator()(Model::Node *node)
{
  mEvolve = nodeCast<Model::EvolveItem*>(node);
  Q_ASSERT(mEvolve != nullptr);
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

  out << "yylex();" << Qt::endl
      << Qt::endl;
}

void CodeGenerator::visitPlus(Model::PlusItem *node)
{
  out << "do {" << Qt::endl;
  visitNode(node->mItem);
  out << "} while (";
  generateTestCondition(node, out);
  out << ");" << Qt::endl;
}

void CodeGenerator::visitStar(Model::StarItem *node)
{
  out << "while (";
  generateTestCondition(node, out);
  out << ") {" << Qt::endl;
  visitNode(node->mItem);
  out << "}" << Qt::endl;
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

      out << ") {" << Qt::endl;
      visitNode(n);
      out << "}";

      if (it != top_level_nodes.end())
        out << "else ";
      else
        {
          out << "else {" << Qt::endl;

          if (!mCurrentCatchId)
              out << "return false;" << Qt::endl;
          else
              out << "goto __catch_" << mCurrentCatchId << ";";

          out << "}" << Qt::endl;
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

  out << ") {" << Qt::endl;

  GenerateLocalDeclarations gen_locals(out, mNames);
  gen_locals(node->mItem);

  out << node->mCode;

  visitNode(node->mItem);

  if (globalSystem.start.contains(node->mSymbol))
    out << "if (Token_EOF != yytoken) { return false; }" << Qt::endl;

  out << "}" << Qt::endl;
}

void CodeGenerator::visitTryCatch(Model::TryCatchItem *node)
{
  static int tryCatch_counter = 0;
  int previous_catch_id = setCatchId(++tryCatch_counter);

  if (node->mCatchItem) // node is a try/rollback block
    {
      out << "bool blockErrors_" << mCurrentCatchId
          << " = blockErrors(true);" << Qt::endl;
    }

  out << "qint64 try_startToken_" << mCurrentCatchId
      << " = tokenStream->index() - 1;" << Qt::endl;

  if (!node->mUnsafe)
    {
      out << "ParserState *try_startState_" << mCurrentCatchId
          << " = copyCurrentState();" << Qt::endl;
    }

  out << "{" << Qt::endl;
  visitNode(node->mTryItem);
  out << "}" << Qt::endl;

  if (node->mCatchItem)
    {
      out << "blockErrors(blockErrors_" << mCurrentCatchId << ");" << Qt::endl;
    }

  if (!node->mUnsafe)
    {
      out << "if (try_startState_" << mCurrentCatchId << ")" << Qt::endl
          << "delete try_startState_" <<  mCurrentCatchId << ";" << Qt::endl
          << Qt::endl;
    }

  out << "if (false) // the only way to enter here is using goto" << Qt::endl
      << "{" << Qt::endl
      << "__catch_" << mCurrentCatchId << ":" << Qt::endl;

  if (!node->mUnsafe)
    {
      out << "if (try_startState_" << mCurrentCatchId << ")" << Qt::endl
          << "{" << Qt::endl
          << "restoreState(try_startState_" <<  mCurrentCatchId << ");" << Qt::endl
          << "delete try_startState_" <<  mCurrentCatchId << ";" << Qt::endl
          << "}" << Qt::endl;
    }

  if (!node->mCatchItem)
    {
      generateRecovery(node, mCurrentCatchId, out);
      setCatchId(previous_catch_id);
    }
  else
    {
      out << "blockErrors(blockErrors_" << mCurrentCatchId << ");" << Qt::endl
          << "rewind(try_startToken_" << mCurrentCatchId << ");" << Qt::endl
          << Qt::endl;

      setCatchId(previous_catch_id);
      visitNode(node->mCatchItem);
    }

  out << "}" << Qt::endl
      << Qt::endl;
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
      // checkOut << "** WARNING annotation ignored" << endl;
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
              << "tokenStream->index() - 1, memoryPool);" << Qt::endl
              << "yylex();" << Qt::endl
              << Qt::endl;
        }
      else
        {
          if (node->mDeclaration->mStorageType == Model::VariableDeclarationItem::StorageAstMember)
            out << "(*yynode)->";

          out << node->mDeclaration->mName
              << " = tokenStream->index() - 1;" << Qt::endl
              << "yylex();" << Qt::endl
              << Qt::endl;
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
          out << "if (" << __var << "->startToken < (*yynode)->startToken)" << Qt::endl
              << "(*yynode)->startToken = " << __var << "->startToken;" << Qt::endl;
        }

      QString target;
      if (node->mDeclaration->mStorageType == Model::VariableDeclarationItem::StorageAstMember)
        target += "(*yynode)->";

      target += node->mDeclaration->mName;

      if (node->mDeclaration->mIsSequence)
        {
          target += "Sequence";

          out << target << " = " << "snoc(" << target << ", "
              << __var << ", memoryPool);" << Qt::endl
              << Qt::endl;
        }
      else
        {
          out << target << " = " << __var << ";" << Qt::endl
              << Qt::endl;
        }
    }
  else
    Q_ASSERT(0); // ### not supported
}

void CodeGenerator::visitOperator(Model::OperatorItem *node)
{
  out << "bool expectOperator = false;"
      << "while(true) {"
      << "if(expectOperator) {"
      << " ";
  const QString capNode = capitalized(node->mName);
  const QString nodeType = capNode + "Ast";
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
  for(auto i = node->mPost.begin(); i != node->mPost.end(); ++i)
  {
    if(printElse)
      out << "else ";
    printElse = true;
    out << "if(";
    generateTestCondition(i->op.mTok, out);
    if(i->op.mCond.size() != 0)
      out << " && " << i->op.mCond;
    out << ") { const unsigned int priority = " << i->priority << ";";
    out << i->op.mCode;
    out << "AstNode *last = nullptr; bool br = false;";
    out << "while(priority < opStack.last().p + " << i->left << ") {";
    out << "if(opStack.size() == 1) {"
           "if(last)\n"
           "opStack.last().n->endToken = last->endToken;"
           "last = opStack.last().n;"
           "opStack.pop_back();"
           "opStack.push_front(OperatorStackItem((*yynode) = create<Postfix"<< nodeType << ">(last), -2));"
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
        << "opStack.push_back(OperatorStackItem(ref = create<Postfix" << nodeType << ">(last), -2));"
          "ref->endToken = last->endToken + 1;"
          "ref->startToken = last->startToken;"
          "} yylex(); }";
  }
  for(auto i = node->mBin.begin(); i != node->mBin.end(); ++i)
  {
    if(printElse)
      out << "else ";
    printElse = true;
    out << "if(";
    generateTestCondition(i->op.mTok, out);
    if(i->op.mCond.size() != 0)
      out << " && " << i->op.mCond;
    out << ") { const unsigned int priority = " << i->priority << ";";
    out << i->op.mCode;
    out << "AstNode *last = nullptr; bool br = false;";
    out << "while(priority < opStack.last().p + " << i->left << ") {";
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
  for(auto i = node->mTern.begin(); i != node->mTern.end(); ++i)
  {
    if(printElse)
      out << "else ";
    printElse = true;
    out << "if(";
    generateTestCondition(i->first.mTok, out);
    if(i->first.mCond.size() != 0)
      out << " && " << i->first.mCond;
        out << ") { const unsigned int priority = " << i->priority << ";";
    out << i->first.mCode;
    out << "AstNode *last = nullptr; bool br = false;";
    out << "while(priority < opStack.last().p + " << i->left << ") {";
    out << "if(opStack.size() == 1) {"
           "if(last)\n"
           "opStack.last().n->endToken = last->endToken;"
           "last = opStack.last().n;\n"
           "opStack.pop_back();"
           "opStack.push_front(OperatorStackItem((*yynode) = create<Ternary" << nodeType << ">(last), priority));"
           "(*yynode)->startToken = last->startToken;"
           "yylex();";
    QString __var = generateParserCall(&ntItem, mCurrentCatchId, out);
    out << "if(!(";
    generateTestCondition(i->second.mTok, out);
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
  for(auto i = node->mPre.begin(); i != node->mPre.end(); ++i)
  {
    if(printElse)
      out << "else ";
    printElse = true;
    out << "if(";
    generateTestCondition(i->op.mTok, out);
    if(i->op.mCond.size() != 0)
      out << " && " << i->op.mCond;
    out << ") { const unsigned int priority = " << i->priority << ";";
    out << i->op.mCode
        << "Prefix" << nodeType << " *node = create<Prefix" << nodeType << ">();"
           "if(opStack.empty())\n"
           "(*yynode) = node;"
           "else"
           "{\n"
           "void *last = opStack.last().n;"
           "if(reinterpret_cast<Prefix" << nodeType << "*>(last)->first == nullptr)\n"
           "reinterpret_cast<Prefix" << nodeType << "*>(last)->first = node;"
           "else if(reinterpret_cast<Binary" << nodeType << "*>(last)->second == nullptr)\n"
           "reinterpret_cast<Binary" << nodeType << "*>(last)->second = node;"
           "else\n"
           "reinterpret_cast<Ternary" << nodeType << "*>(last)->third = node;"
           "}"
           "opStack.push_back(OperatorStackItem(node, priority));"
           "node->startToken = tokenStream->index() - 1;"
           "yylex();"
           "}" << Qt::endl;
  }
  for(auto i = node->mParen.begin(); i != node->mParen.end(); ++i)
  {
    if(printElse)
      out << "else ";
    printElse = true;
    out << "if(";
    generateTestCondition(i->first.mTok, out);
    if(i->first.mCond.size() != 0)
      out << " && " << i->first.mCond;
    out << ") { yylex();"
           "if(";
    generateTestCondition(mSym, out);
    out << ") {";
    QString __var = generateParserCall(&ntItem, mCurrentCatchId, out);
    out << "if(!(";
    generateTestCondition(i->second.mTok, out);
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
  if(reinterpret_cast<Prefix" << nodeType << "*>(last)->first == nullptr)\n\
    reinterpret_cast<Prefix" << nodeType << "*>(last)->first = " << __var << ";" << Qt::endl; \
  out << "else if(reinterpret_cast<Binary" << nodeType << "*>(last)->second == nullptr)\n\
  reinterpret_cast<Binary" << nodeType << "*>(last)->second = " << __var << ";\
  else\nreinterpret_cast<Ternary" << nodeType << "*>(last)->third = " << __var << ";}\
else\n\
(*yynode) = " << __var << ";\
opStack.push_back(OperatorStackItem(" << __var << ", -2));";
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
  out << "else"
         "{"
         "expectedSymbol(AstNode::" << capNode << "Kind"
         ", \"" << node->mName << "\");return false;"
         "} } }";
  /// @TODO Further: empty binary operator
}


void GenerateForwardParserRule::operator()(QPair<QString, Model::SymbolItem*> const &__it)
{
  Model::SymbolItem *sym = __it.second;
  out << "bool" << " " << "parse" << sym->mCapitalizedName << "(";

  GenerateParseMethodSignature gen_signature(out, nullptr);
  gen_signature(sym);

  out << ");" << Qt::endl;
}

void GenerateParserRule::operator()(QPair<QString, Model::SymbolItem*> const &__it)
{
  mNames.clear();
  Model::SymbolItem *sym = __it.second;
  CodeGenerator cg(out, &mNames, sym);

  out << "bool Parser::parse" << sym->mCapitalizedName << "(";

  GenerateParseMethodSignature gen_signature(out, &mNames);
  gen_signature(sym);

  out << ")" << Qt::endl
      << "{" << Qt::endl;

  if (globalSystem.generateAst)
    {
      if(isOperatorSymbol(sym))
        out << "QList<OperatorStackItem> opStack;" << Qt::endl;
      else
      {
        out << "*yynode = create<" << sym->mCapitalizedName << "Ast" << ">();" << Qt::endl << Qt::endl
            << "(*yynode)->startToken = tokenStream->index() - 1;" << Qt::endl;
        //Generate initialization for this ast nodes token-members using -1 as invalid value
        GenerateTokenVariableInitialization gentokenvar( out );
        gentokenvar(sym);
        out << Qt::endl;
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

  out << "else" << Qt::endl << "{ return false; }" << Qt::endl
      << Qt::endl;


  if (globalSystem.generateAst)
    {
      if(isOperatorSymbol(sym))
      {
        out << "AstNode *olast, *last = nullptr;"
               "while(!opStack.empty())\n"
               "{"
               "olast = last;"
               "last = opStack.last().n;"
               "if(olast)\n"
               "last->endToken = olast->endToken;"
               "opStack.pop_back();"
               "}" << Qt::endl;
      }
      else
      {
        out << "(*yynode)->endToken = tokenStream->index() - 2;" << Qt::endl
            << Qt::endl;
      }
    }

  out << "return true;" << Qt::endl
      << "}" << Qt::endl
      << Qt::endl;
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
      if ((mNames == nullptr) || mNames->find(node->mName) == mNames->end())
        {
          GenerateVariableDeclaration<true, true> gen_var_decl(out);
          gen_var_decl(node);

          if (node->mVariableType == Model::VariableDeclarationItem::TypeToken
              || node->mVariableType == Model::VariableDeclarationItem::TypeNode
              || node->mIsSequence)
            {
              out << " = 0";
            }

          out << ";" << Qt::endl << Qt::endl;

          if (mNames != nullptr)
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
          << node->mName << sequence_suffix << ";" << Qt::endl;

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

          out << argument_startToken << " < (*yynode)->startToken)" << Qt::endl
              << "(*yynode)->startToken = " << argument_startToken << ";"
            << Qt::endl << Qt::endl;
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

          if (mNames != nullptr)
            mNames->insert(node->mName);
        }
    }

  DefaultVisitor::visitVariableDeclaration(node);
}

namespace GenerateVariableDeclarationImpl
{
void printType(QTextStream &out, Model::VariableDeclarationItem *node)
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

void printName(QTextStream &out, Model::VariableDeclarationItem *node)
{
  out << node->mName;

  if (node->mIsSequence)
    out << "Sequence";
}
}

void GenerateMemberCode::operator()(Settings::MemberItem* m)
{
  if ((mKindMask & m->mMemberKind) != 0)
    {
      if (m->mMemberKind == Settings::MemberItem::PublicDeclaration)
        out << "public:" << Qt::endl;
      else if (m->mMemberKind == Settings::MemberItem::ProtectedDeclaration)
        out << "protected:" << Qt::endl;
      else if (m->mMemberKind == Settings::MemberItem::PrivateDeclaration)
        out << "private:" << Qt::endl;

      out << m->mCode << Qt::endl;
    }
}

void GenerateParserDeclarations::operator()()
{
  out << "class " << globalSystem.exportMacro << " Parser : ";
  if(!globalSystem.parserBaseClass.isEmpty())
    out << "public " << globalSystem.parserBaseClass << ", ";
  out << "public TokenTypeWrapper\n{"
      << "public:" << Qt::endl
      << "typedef " << globalSystem.tokenStream << "::Token Token;" << Qt::endl
      << globalSystem.tokenStream << " *tokenStream;" << Qt::endl
      << "int yytoken;" << Qt::endl;
  if(globalSystem.needOperatorStack)
    out << "struct OperatorStackItem{AstNode *n; int unsigned p;"
           "inline OperatorStackItem(AstNode *n, int unsigned p)\n"
           ": n(n), p(p)\n{}\n"
           "inline OperatorStackItem()\n{}\n"
           "inline OperatorStackItem(const OperatorStackItem& o)\n"
           ": n(o.n), p(o.p)\n"
           "{}\n};" << Qt::endl;
  out << Qt::endl
      << "inline Token LA(qint64 k = 1) const" << Qt::endl
      << "{ qint64 idx = tokenStream->index() - 1 + k - 1; qint64 oldidx = tokenStream->index(); tokenStream->rewind(tokenStream->size()); while(idx >= tokenStream->size()) tokenStream->read(); tokenStream->rewind(oldidx); return tokenStream->at(idx); }"
      << Qt::endl
      << "inline int yylex() {" << Qt::endl
      << "yytoken = tokenStream->read().kind; return yytoken;" << Qt::endl
      << "}" << Qt::endl
      << "inline void rewind(qint64 index) {" << Qt::endl
      << "tokenStream->rewind(index);" << Qt::endl
      << "yylex();" << Qt::endl
      << "}" << Qt::endl
      << Qt::endl;

  out << "// token stream" << Qt::endl
      << "void setTokenStream(" << globalSystem.tokenStream << " *s)" << Qt::endl
      << "{ tokenStream = s; }" << Qt::endl
      << Qt::endl;

  out << "// error handling" << Qt::endl
      << "void expectedSymbol(int kind, const QString& name);" << Qt::endl
      << "void expectedToken(int kind, qint64 token, const QString& name);" << Qt::endl
      << Qt::endl
      << "bool mBlockErrors;" << Qt::endl
      << "inline bool blockErrors(bool block) {" << Qt::endl
      << "bool previous = mBlockErrors;" << Qt::endl
      << "mBlockErrors = block;" << Qt::endl
      << "return previous;" << Qt::endl
      << "}" << Qt::endl;

  out << Qt::endl;

    if (globalSystem.generateAst)
      {
        out << "// memory pool" << Qt::endl
            << "typedef KDevPG::MemoryPool memoryPoolType;" << Qt::endl
            << Qt::endl
            << "KDevPG::MemoryPool *memoryPool;" << Qt::endl
            << "void setMemoryPool(KDevPG::MemoryPool *p)" << Qt::endl
            << "{ memoryPool = p; }" << Qt::endl
            << "template <class T>" << Qt::endl
            << "inline T *create()" << Qt::endl
            << "{" << Qt::endl
            << "T *node = new (memoryPool->allocate(sizeof(T))) T();" << Qt::endl
            << "node->kind = T::KIND;" << Qt::endl
            << "return node;" << Qt::endl
            << "}" << Qt::endl
            << "template <class T>" << Qt::endl
            << "inline T *create(AstNode *u)" << Qt::endl
            << "{" << Qt::endl
            << "T *node = new (memoryPool->allocate(sizeof(T))) T(u);" << Qt::endl
            << "node->kind = T::KIND;" << Qt::endl
            << "return node;" << Qt::endl
            << "}" << Qt::endl
            << Qt::endl;
      }

  if (globalSystem.parserclassMembers.declarations.empty() == false)
    {
      out << "// user defined declarations:" << Qt::endl;
      GenerateMemberCode gen(out, Settings::MemberItem::PublicDeclaration
                            | Settings::MemberItem::ProtectedDeclaration
                            | Settings::MemberItem::PrivateDeclaration);
      for( QList<Settings::MemberItem*>::iterator it = globalSystem.parserclassMembers.declarations.begin();
                    it != globalSystem.parserclassMembers.declarations.end(); ++it )
      {
                    gen(*it);
      }
      out << Qt::endl << "public:" << Qt::endl;
    }

  if (globalSystem.needStateManagement)
    {
      out << "// The copyCurrentState() and restoreState() methods are only declared" << Qt::endl
          << "// if you are using try blocks in your grammar, and have to be" << Qt::endl
          << "// implemented by yourself, and you also have to define a" << Qt::endl
          << "// \"struct ParserState\" inside a %parserclass directive." << Qt::endl
          << Qt::endl
          << "// This method should create a new ParserState object and return it," << Qt::endl
          << "// or return 0 if no state variables need to be saved." << Qt::endl
          << "ParserState *copyCurrentState();" << Qt::endl
          << Qt::endl
          << "// This method is only called for ParserState objects != 0" << Qt::endl
          << "// and should restore the parser state given as argument." << Qt::endl
          << "void restoreState(ParserState *state);" << Qt::endl;
    }

  out << "Parser() {" << Qt::endl;
  if (globalSystem.generateAst)
    {
      out << "memoryPool = nullptr;" << Qt::endl;
    }

  out << "tokenStream = nullptr;" << Qt::endl
      << "yytoken = Token_EOF;" << Qt::endl
      << "mBlockErrors = false;" << Qt::endl;

  if (globalSystem.parserclassMembers.constructorCode.empty() == false)
    {
      out << Qt::endl << "// user defined constructor code:" << Qt::endl;
      GenerateMemberCode gen(out, Settings::MemberItem::ConstructorCode);
      for(QList<Settings::MemberItem*>::iterator it =
            globalSystem.parserclassMembers.constructorCode.begin();
            it != globalSystem.parserclassMembers.constructorCode.end(); ++it )
      {
        gen(*it);
      }
    }

  out << "}" << Qt::endl << Qt::endl;

  out << "virtual ~Parser() {";

  if (globalSystem.parserclassMembers.destructorCode.empty() == false)
    {
      out << Qt::endl
          << "// user defined destructor code:" << Qt::endl;

      GenerateMemberCode gen(out, Settings::MemberItem::DestructorCode);
      for(QList<Settings::MemberItem*>::iterator it = globalSystem.parserclassMembers.destructorCode.begin();
                    it != globalSystem.parserclassMembers.destructorCode.end(); ++it )
      {
        gen(*it);
      }
    }

  out << "}" << Qt::endl << Qt::endl;

  GenerateForwardParserRule genfwdparserrule(out);
  for( World::SymbolSet::iterator it = globalSystem.symbols.begin();
       it != globalSystem.symbols.end(); ++it )
  {
    genfwdparserrule(qMakePair(it.key(), *it));
  }

  out << "};" << Qt::endl;
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
      out << "(*yynode)->" << node->mName << " = -1;" << Qt::endl;
  }
}


void GenerateTokenTexts::operator()()
{
  out << "switch (token) {" << Qt::endl;
  for(World::TerminalSet::iterator it = globalSystem.terminals.begin(); it != globalSystem.terminals.end(); ++it )
  {
    Model::TerminalItem* t = *it;
    out << "    case TokenTypeWrapper::Token_" << t->mName << ":" << Qt::endl;
    QString text = t->mDescription;
    text.replace('\\', "\\\\").replace('"', "\\\"");
    out << "        return QStringLiteral(\"" <<  text << "\");" << Qt::endl;
  }
  out << "    default:" << Qt::endl;
  out << "        return QStringLiteral(\"unknown token\");" << Qt::endl;
  out << "}" << Qt::endl;
}


} // namespace KDevPG
