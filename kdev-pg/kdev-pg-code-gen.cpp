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

#include "kdev-pg.h"
#include "kdev-pg-code-gen.h"

#include <list>
#include <stack>
#include <iostream>
#include <cassert>

namespace KDevPG
{
  void generateCondition(World::NodeSet const &s, std::ostream &out)
  {
    bool initial = true;
    Model::Node *item = globalSystem.zero();

    World::NodeSet::iterator it = s.begin();
    while (it != s.end())
      {
        item = *it++;

        if (Model::TerminalItem *t = nodeCast<Model::TerminalItem*>(item))
          {
            if (!initial)
              out << std::endl << "|| ";

            out << "yytoken == Token_" << t->mName;
            initial = false;
          }
      }

    if (initial && isZero(item))
      out << "true /*epsilon*/";
  }

  void generateTestCondition(Model::Node *node, std::ostream &out)
  {
    World::NodeSet s = globalSystem.first(node);
    generateCondition(s, out);
  }

  std::string generateParserCall(Model::NonTerminalItem *node, int catch_id, std::ostream &out)
  {
    static int __id = 0;
    static char __var[1024];
    char const *symbol_name = node->mSymbol->mName;

    if (globalSystem.GenerateAst)
      {
        sprintf(__var, "__node_%d", __id++);

        out << symbol_name << "_ast *" << __var << " = 0;" << std::endl
            << "if (!parse_" << symbol_name << "(&" << __var;

        if (node->mArguments[0] != '\0') // read: if (mArguments != "")
            out << ", " << node->mArguments;

        out << "))" << std::endl;
      }
    else
      {
        out << "if (!parse_" << symbol_name << "(" << node->mArguments << "))"
            << std::endl;
      }

    if (!catch_id)
      {
        out << "{" << std::endl;

        if (globalSystem.needStateManagement)
          out <<   "if (!yy_block_errors) {" << std::endl;

        out << "yy_expected_symbol(ast_node::Kind_" << symbol_name
            << ", \"" << symbol_name << "\"" << ");" << std::endl;

        if (globalSystem.needStateManagement)
          out << "}" << std::endl;

        out << "return false;" << std::endl
            << "}" << std::endl;
      }
    else
      {
        out << "{ goto __catch_" << catch_id << "; }" << std::endl;
      }

    return __var;
  }

  void generateTokenTest(Model::TerminalItem *node, int catch_id, std::ostream &out)
  {
    out << "if (yytoken != Token_" << node->mName << ")" << std::endl;
    if (!catch_id)
      {
        out << "{" << std::endl;

        if (globalSystem.needStateManagement)
          out << "if (!yy_block_errors) {" << std::endl;

        out << "yy_expected_token(yytoken, Token_" << node->mName
            << ", \"" << node->mDescription << "\");" << std::endl;

        if (globalSystem.needStateManagement)
          out << "}" << std::endl;

        out << "return false;" << std::endl
            << "}" << std::endl;
      }
    else
      {
        out << "goto __catch_" << catch_id << ";" << std::endl;
      }
  }

  void generateRecovery(Model::Node *node, int catch_id, std::ostream &out)
  {
    World::NodeSet s = globalSystem.follow(node);
    Model::Node *item = globalSystem.zero();

    out << "if (try_start_token_" << catch_id
        << " == tokenStream->index() - 1)" << std::endl
        << "yylex();" << std::endl
        << std::endl;

    out << "while (yytoken != Token_EOF";

    World::NodeSet::iterator it = s.begin();
    while (it != s.end())
      {
        item = *it++;

        if (Model::TerminalItem *t = nodeCast<Model::TerminalItem*>(item))
          out << std::endl << "&& yytoken != Token_" << t->mName;
      }

    out << ")" << std::endl
        << "{ yylex(); }" << std::endl;
  }


void CodeGenerator::operator()(Model::Node *node)
{
  mEvolve = nodeCast<Model::EvolveItem*>(node);
  assert(mEvolve != 0);
  visitNode(node);
}

void CodeGenerator::visitZero(Model::ZeroItem *node)
{
  // out << " /* nothing to do */" << std::endl;
}

void CodeGenerator::visitSymbol(Model::SymbolItem *node)
{
  // out << " /* nothing to do */" << std::endl;
}

void CodeGenerator::visitNonTerminal(Model::NonTerminalItem *node)
{
  generateParserCall(node, mCurrentCatchId, out);
}

void CodeGenerator::visitTerminal(Model::TerminalItem *node)
{
  generateTokenTest(node, mCurrentCatchId, out);

  out << "yylex();" << std::endl
      << std::endl;
}

void CodeGenerator::visitPlus(Model::PlusItem *node)
{
  out << "do {" << std::endl;
  visitNode(node->mItem);
  out << "} while (";
  generateTestCondition(node, out);
  out << ");" << std::endl;
}

void CodeGenerator::visitStar(Model::StarItem *node)
{
  out << "while (";
  generateTestCondition(node, out);
  out << ") {" << std::endl;
  visitNode(node->mItem);
  out << "}" << std::endl;
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
  std::list<Model::Node*> top_level_nodes;

  std::stack<Model::Node*> working_list;
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

  std::list<Model::Node*>::iterator it = top_level_nodes.begin();
  while (it != top_level_nodes.end())
    {
      Model::Node *n = *it++;
      Model::ConditionItem *cond = nodeCast<Model::ConditionItem*>(n);

      out << "if (";

      if (cond)
        out << "(";

      generateTestCondition(n, out);

      if (cond)
        out << ") && (" << cond->mCode << ")";

      out << ") {" << std::endl;
      visitNode(n);
      out << "}";

      if (it != top_level_nodes.end())
        out << "else ";
      else
        {
          out << "else {" << std::endl;

          if (!mCurrentCatchId)
              out << "return false;" << std::endl;
          else
              out << "goto __catch_" << mCurrentCatchId << ";";

          out << "}" << std::endl;
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

  out << ") {" << std::endl;

  GenerateLocalDeclarations gen_locals(out, mNames);
  gen_locals(node->mItem);

  out << node->mCode;

  visitNode(node->mItem);

  if (node == globalSystem.start)
    out << "if (Token_EOF != yytoken) { return false; }" << std::endl;

  out << "}" << std::endl;
}

void CodeGenerator::visitTryCatch(Model::TryCatchItem *node)
{
  static int tryCatch_counter = 0;
  int previous_catch_id = setCatchId(++tryCatch_counter);

  if (node->mCatchItem) // node is a try/rollback block
    {
      out << "bool block_errors_" << mCurrentCatchId
          << " = block_errors(true);" << std::endl;
    }

  out << "std::size_t try_start_token_" << mCurrentCatchId
      << " = tokenStream->index() - 1;" << std::endl;

  if (!node->mUnsafe)
    {
      out << "parser_state *try_start_state_" << mCurrentCatchId
          << " = copy_current_state();" << std::endl;
    }

  out << "{" << std::endl;
  visitNode(node->mTryItem);
  out << "}" << std::endl;

  if (node->mCatchItem)
    {
      out << "block_errors(block_errors_" << mCurrentCatchId << ");" << std::endl;
    }

  if (!node->mUnsafe)
    {
      out << "if (try_start_state_" << mCurrentCatchId << ")" << std::endl
          << "delete try_start_state_" <<  mCurrentCatchId << ";" << std::endl
          << std::endl;
    }

  out << "if (false) // the only way to enter here is using goto" << std::endl
      << "{" << std::endl
      << "__catch_" << mCurrentCatchId << ":" << std::endl;

  if (!node->mUnsafe)
    {
      out << "if (try_start_state_" << mCurrentCatchId << ")" << std::endl
          << "{" << std::endl
          << "restore_state(try_start_state_" <<  mCurrentCatchId << ");" << std::endl
          << "delete try_start_state_" <<  mCurrentCatchId << ";" << std::endl
          << "}" << std::endl;
    }

  if (!node->mCatchItem)
    {
      generateRecovery(node, mCurrentCatchId, out);
      setCatchId(previous_catch_id);
    }
  else
    {
      out << "block_errors(block_errors_" << mCurrentCatchId << ");" << std::endl
          << "rewind(try_start_token_" << mCurrentCatchId << ");" << std::endl
          << std::endl;

      setCatchId(previous_catch_id);
      visitNode(node->mCatchItem);
    }

  out << "}" << std::endl
      << std::endl;
}

int CodeGenerator::setCatchId(int catch_id)
{
  int previous = mCurrentCatchId;
  mCurrentCatchId = catch_id;
  return previous;
}

void CodeGenerator::visitAlias(Model::AliasItem *node)
{
  assert(0); // ### not implemented yet
}

void CodeGenerator::visitAnnotation(Model::AnnotationItem *node)
{
  if (!globalSystem.GenerateAst)
    {
      // std::cerr << "** WARNING annotation ignored" << std::endl;
      visitNode(node->mItem);
      return;
    }

  if (Model::TerminalItem *t = nodeCast<Model::TerminalItem*>(node->mItem))
    {
      generateTokenTest(t, mCurrentCatchId, out);

      if (node->mDeclaration->mIsSequence)
        {
          std::string target;

          if (node->mDeclaration->mStorageType == Model::VariableDeclarationItem::StorageAstMember)
            target += "(*yynode)->";

          target += node->mDeclaration->mName;
          target += "_sequence";

          out << target << " = snoc(" << target << ", "
              << "tokenStream->index() - 1, memory_pool);" << std::endl
              << "yylex();" << std::endl
              << std::endl;
        }
      else
        {
          if (node->mDeclaration->mStorageType == Model::VariableDeclarationItem::StorageAstMember)
            out << "(*yynode)->";

          out << node->mDeclaration->mName
              << " = tokenStream->index() - 1;" << std::endl
              << "yylex();" << std::endl
              << std::endl;
        }
    }
  else if (Model::NonTerminalItem *nt = nodeCast<Model::NonTerminalItem*>(node->mItem))
    {
      std::string __var = generateParserCall(nt, mCurrentCatchId, out);

      bool check_start_token = false;
      World::Environment::iterator it = globalSystem.env.find(nt->mSymbol);
      while (it != globalSystem.env.end())
        {
          Model::EvolveItem *e = (*it).second;
          if ((*it).first != nt->mSymbol)
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
                  check_start_token = true;
                  break;
                }

              current_decl = current_decl->mNext;
            }
        }

      if (check_start_token == true)
        {
          check_start_token = false;
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
                  check_start_token = true;
                  break;
                }

              current_decl = current_decl->mNext;
            }
        }

      if (check_start_token == true)
        {
          out << "if (" << __var << "->start_token < (*yynode)->start_token)" << std::endl
              << "(*yynode)->start_token = " << __var << "->start_token;" << std::endl;
        }

      std::string target;
      if (node->mDeclaration->mStorageType == Model::VariableDeclarationItem::StorageAstMember)
        target += "(*yynode)->";

      target += node->mDeclaration->mName;

      if (node->mDeclaration->mIsSequence)
        {
          target += "_sequence";

          out << target << " = " << "snoc(" << target << ", "
              << __var << ", memory_pool);" << std::endl
              << std::endl;
        }
      else
        {
          out << target << " = " << __var << ";" << std::endl
              << std::endl;
        }
    }
  else
    assert(0); // ### not supported
}


void GenerateForwardParserRule::operator()(std::pair<std::string, Model::SymbolItem*> const &__it)
{
  Model::SymbolItem *sym = __it.second;
  out << "bool" << " " << "parse_" << sym->mName << "(";

  GenerateParseMethodSignature gen_signature(out, 0);
  gen_signature(sym);

  out << ");" << std::endl;
}

void GenerateParserRule::operator()(std::pair<std::string, Model::SymbolItem*> const &__it)
{
  mNames.clear();
  Model::SymbolItem *sym = __it.second;
  CodeGenerator cg(out, &mNames);

  out << "bool parser::parse_" << sym->mName << "(";

  GenerateParseMethodSignature gen_signature(out, &mNames);
  gen_signature(sym);

  out << ")" << std::endl
      << "{" << std::endl;

  if (globalSystem.GenerateAst)
    {
      out << "*yynode = create<" << sym->mName << "_ast" << ">();" << std::endl << std::endl
          << "(*yynode)->start_token = tokenStream->index() - 1;" << std::endl
          << std::endl;
    }

  World::Environment::iterator it = globalSystem.env.find(sym);
  while (it != globalSystem.env.end())
    {
      Model::EvolveItem *e = (*it).second;
      if ((*it).first != sym)
        break;

      ++it;

      GenerateLocalDeclarations gen_locals(out, &mNames);
      gen_locals(e->mDeclarations);
    }

  it = globalSystem.env.find(sym);
  bool initial = true;
  while (it != globalSystem.env.end())
    {
      Model::EvolveItem *e = (*it).second;
      if ((*it).first != sym)
        break;

      ++it;

      if (!initial)
        out << "else ";

      cg(e);
      initial = false;
    }

  out << "else" << std::endl << "{ return false; }" << std::endl
      << std::endl;


  if (globalSystem.GenerateAst)
    {
      out << "(*yynode)->end_token = tokenStream->index() - 1;" << std::endl
          << std::endl;
    }

  out << "return true;" << std::endl
      << "}" << std::endl
      << std::endl;
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
          GenerateVariableDeclaration gen_var_decl(out);
          gen_var_decl(node);

          if (node->mVariableType == Model::VariableDeclarationItem::TypeToken
              || node->mVariableType == Model::VariableDeclarationItem::TypeNode
              || node->mIsSequence)
            {
              out << " = 0";
            }

          out << ";" << std::endl << std::endl;

          if (mNames != 0)
            mNames->insert(node->mName);
        }
    }

  // for argument member nodes and tokens, check if their index precedes the current one
  else if (node->mStorageType == Model::VariableDeclarationItem::StorageAstMember
           && node->mDeclarationType == Model::VariableDeclarationItem::DeclarationArgument
           && globalSystem.GenerateAst)
    {
      char const *sequence_suffix = (node->mIsSequence) ? "_sequence" : "";

      out << "(*yynode)->" << node->mName << sequence_suffix << " = "
          << node->mName << sequence_suffix << ";" << std::endl;

      if (node->mVariableType != Model::VariableDeclarationItem::TypeVariable)
        {
          std::string argument_start_token = node->mName;
          if (node->mIsSequence)
            argument_start_token += "_sequence->to_front()->element";

          if (node->mVariableType == Model::VariableDeclarationItem::TypeNode)
            argument_start_token += "->start_token";

          out << "if (";

          // check that the variable is not null
          if (node->mVariableType == Model::VariableDeclarationItem::TypeNode
              || node->mIsSequence)
            {
              out << node->mName << sequence_suffix << " && ";
            }

          out << argument_start_token << " < (*yynode)->start_token)" << std::endl
              << "(*yynode)->start_token = " << argument_start_token << ";"
            << std::endl << std::endl;
        }
    }

  DefaultVisitor::visitVariableDeclaration(node);
}

void GenerateParseMethodSignature::operator()(Model::SymbolItem* sym)
{
  if (globalSystem.GenerateAst)
    {
      out << sym->mName << "_ast **yynode";
      firstParameter = false;
    }

  World::Environment::iterator it = globalSystem.env.find(sym);
  if (it != globalSystem.env.end())
    {
      // this creates the method signature using just the first of
      // possibly multiple rules with the same name.
      Model::EvolveItem *e = (*it).second;
      if (e->mDeclarations)
        visitNode(e->mDeclarations);
    }
}

void GenerateParseMethodSignature::visitVariableDeclaration(Model::VariableDeclarationItem *node)
{
  if (node->mDeclarationType == Model::VariableDeclarationItem::DeclarationArgument)
    {
      if (globalSystem.GenerateAst || (node->mStorageType != Model::VariableDeclarationItem::StorageAstMember))
        {
          if (firstParameter)
            firstParameter = false;
          else
            out << ", ";

          GenerateVariableDeclaration gen_var_decl(out);
          gen_var_decl(node);

          if (mNames != 0)
            mNames->insert(node->mName);
        }
    }

  DefaultVisitor::visitVariableDeclaration(node);
}

void GenerateVariableDeclaration::operator()(Model::VariableDeclarationItem *node)
{
  if (node->mIsSequence)
    out << "const list_node<";

  if (node->mVariableType == Model::VariableDeclarationItem::TypeToken)
    out << "std::size_t ";
  else if (node->mVariableType == Model::VariableDeclarationItem::TypeNode)
    out << node->mType << "_ast *";
  else if (node->mVariableType == Model::VariableDeclarationItem::TypeVariable)
    out << node->mType << " ";
  else
    assert(0); // ### not supported

  if (node->mIsSequence)
    out << "> *";

  out << node->mName;

  if (node->mIsSequence)
    out << "_sequence";
}

void GenerateToken::operator()(std::pair<std::string, Model::TerminalItem*> const &__it)
{
  Model::TerminalItem *t = __it.second;
  out << "Token_" << t->mName << " = " << mTokenValue++ << "," << std::endl;
}

void GenerateMemberCode::operator()(Settings::MemberItem* m)
{
  if ((mKindMask & m->mMemberKind) != 0)
    {
      if (m->mMemberKind == Settings::MemberItem::PublicDeclaration)
        out << "public:" << std::endl;
      else if (m->mMemberKind == Settings::MemberItem::ProtectedDeclaration)
        out << "protected:" << std::endl;
      else if (m->mMemberKind == Settings::MemberItem::PrivateDeclaration)
        out << "private:" << std::endl;

      out << m->mCode << std::endl;
    }
}

void GenerateParserDeclarations::operator()()
{
  out << "class " << globalSystem.exportMacro << " parser {"
      << "public:" << std::endl
      << "typedef " << globalSystem.tokenStream << " tokenStream_type;" << std::endl
      << "typedef " << globalSystem.tokenStream << "::token_type token_type;" << std::endl
      << globalSystem.tokenStream << " *tokenStream;" << std::endl
      << "int yytoken;" << std::endl
      << std::endl
      << "inline token_type LA(std::size_t k = 1) const" << std::endl
      << "{ return tokenStream->token(tokenStream->index() - 1 + k - 1); }"
      << std::endl
      << "inline int yylex() {" << std::endl
      << "return (yytoken = tokenStream->next_token());" << std::endl
      << "}" << std::endl
      << "inline void rewind(std::size_t index) {" << std::endl
      << "tokenStream->rewind(index);" << std::endl
      << "yylex();" << std::endl
      << "}" << std::endl
      << std::endl;

  out << "// token stream" << std::endl
      << "void set_tokenStream(" << globalSystem.tokenStream << " *s)" << std::endl
      << "{ tokenStream = s; }" << std::endl
      << std::endl;

  out << "// error handling" << std::endl
      << "void yy_expected_symbol(int kind, char const *name);" << std::endl
      << "void yy_expected_token(int kind, std::size_t token, char const *name);" << std::endl
      << std::endl
      << "bool yy_block_errors;" << std::endl
      << "inline bool block_errors(bool block) {" << std::endl
      << "bool previous = yy_block_errors;" << std::endl
      << "yy_block_errors = block;" << std::endl
      << "return previous;" << std::endl
      << "}" << std::endl;

  out << std::endl;

    if (globalSystem.GenerateAst)
      {
        out << "// memory pool" << std::endl
            << "typedef KDevPG::MemoryPool memory_pool_type;" << std::endl
            << std::endl
            << "KDevPG::MemoryPool *memory_pool;" << std::endl
            << "void set_memory_pool(KDevPG::MemoryPool *p)" << std::endl
            << "{ memory_pool = p; }" << std::endl
            << "template <class T>" << std::endl
            << "inline T *create()" << std::endl
            << "{" << std::endl
            << "T *node = new (memory_pool->allocate(sizeof(T))) T();" << std::endl
            << "node->kind = T::KIND;" << std::endl
            << "return node;" << std::endl
            << "}" << std::endl << std::endl;
      }


  out << "enum token_type_enum" << std::endl << "{" << std::endl;
  std::for_each(globalSystem.terminals.begin(), globalSystem.terminals.end(), GenerateToken(out));
  out << "token_type_size" << std::endl
      << "}; // token_type_enum" << std::endl
      << std::endl;


  if (globalSystem.parserclassMembers.declarations.empty() == false)
    {
      out << "// user defined declarations:" << std::endl;
      std::for_each(globalSystem.parserclassMembers.declarations.begin(),
                    globalSystem.parserclassMembers.declarations.end(),
                    GenerateMemberCode(out, Settings::MemberItem::PublicDeclaration
                                         | Settings::MemberItem::ProtectedDeclaration
                                         | Settings::MemberItem::PrivateDeclaration)
                   );
      out << std::endl << "public:" << std::endl;
    }

  if (globalSystem.needStateManagement)
    {
      out << "// The copy_current_state() and restore_state() methods are only declared" << std::endl
          << "// if you are using try blocks in your grammar, and have to be" << std::endl
          << "// implemented by yourself, and you also have to define a" << std::endl
          << "// \"struct parser_state\" inside a %parserclass directive." << std::endl
          << std::endl
          << "// This method should create a new parser_state object and return it," << std::endl
          << "// or return 0 if no state variables need to be saved." << std::endl
          << "parser_state *copy_current_state();" << std::endl
          << std::endl
          << "// This method is only called for parser_state objects != 0" << std::endl
          << "// and should restore the parser state given as argument." << std::endl
          << "void restore_state(parser_state *state);" << std::endl;
    }

  out << "parser() {" << std::endl;
  if (globalSystem.GenerateAst)
    {
      out << "memory_pool = 0;" << std::endl;
    }

  out << "tokenStream = 0;" << std::endl
      << "yytoken = Token_EOF;" << std::endl
      << "yy_block_errors = false;" << std::endl;

  if (globalSystem.parserclassMembers.constructorCode.empty() == false)
    {
      out << std::endl << "// user defined constructor code:" << std::endl;
      std::for_each(globalSystem.parserclassMembers.constructorCode.begin(),
                    globalSystem.parserclassMembers.constructorCode.end(),
                    GenerateMemberCode(out, Settings::MemberItem::ConstructorCode));
    }

  out << "}" << std::endl << std::endl;

  out << "virtual ~parser() {";

  if (globalSystem.parserclassMembers.destructorCode.empty() == false)
    {
      out << std::endl
          << "// user defined destructor code:" << std::endl;
      std::for_each(globalSystem.parserclassMembers.destructorCode.begin(),
                    globalSystem.parserclassMembers.destructorCode.end(),
                    GenerateMemberCode(out, Settings::MemberItem::DestructorCode));
    }

  out << "}" << std::endl << std::endl;

  std::for_each(globalSystem.symbols.begin(), globalSystem.symbols.end(), GenerateForwardParserRule(out));

  out << "};" << std::endl;
}

void GenerateParserBits::operator()()
{
  std::for_each(globalSystem.symbols.begin(), globalSystem.symbols.end(), GenerateParserRule(out));
}


} // namespace KDevPG
