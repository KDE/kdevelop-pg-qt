/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg-ast-gen.h"
#include "kdev-pg-code-gen.h"
#include "kdev-pg.h"

#include <QMap>

namespace KDevPG
{
void GenerateAst::operator()()
{
  out << globalSystem.namespaceCode << Qt::endl;

  out << "struct " << globalSystem.exportMacro << " AstNode";

  out << "{" << Qt::endl
      << "enum AstNodeKind {" << Qt::endl;

  int node_id = 1000;
  for (QMap<QString, Model::SymbolItem*>::iterator it = globalSystem.symbols.begin();
       it != globalSystem.symbols.end(); ++it)
    {
      Model::SymbolItem *sym = (*it);
      if(isOperatorSymbol(sym))
      {
        out << "Prefix" << sym->mCapitalizedName << "Kind" << " = " << node_id << "," << Qt::endl;
        ++node_id;
        out << "Postfix" << sym->mCapitalizedName << "Kind" << " = " << node_id << "," << Qt::endl;
        ++node_id;
        out << "Binary" << sym->mCapitalizedName << "Kind" << " = " << node_id << "," << Qt::endl;
        ++node_id;
        out << "Ternary" << sym->mCapitalizedName << "Kind" << " = " << node_id << "," << Qt::endl;
        ++node_id;
      }
      out << sym->mCapitalizedName << "Kind" << " = " << node_id << "," << Qt::endl;
      ++node_id;
    }

  out << "AST_NODE_KIND_COUNT" << Qt::endl
      << "};" << Qt::endl << Qt::endl
      << "int kind;" << Qt::endl
      << "qint64 startToken;" << Qt::endl
      << "qint64 endToken;" << Qt::endl
      << globalSystem.astCode << Qt::endl
      << "};" << Qt::endl
      << Qt::endl;

  GenerateAstRule gen(out);
  for( World::SymbolSet::const_iterator it = globalSystem.symbols.constBegin(); it != globalSystem.symbols.constEnd(); ++it )
  {
    gen(*it);
  }
  gen.mFirstTime = false;
  while(true)
  {
    int oldSize = gen.mToGenerate.size();
    for(auto i = gen.mToGenerate.begin(); i != gen.mToGenerate.end(); )
    {
      auto next = i;
      ++next;
      gen(*i);
      i = next;
    }
    if(gen.mToGenerate.size() == oldSize)
      break;
  }
  gen.mForce = true;
  for(auto i = gen.mToGenerate.begin(); i != gen.mToGenerate.end(); )
  {
    auto next = i;
    ++next;
    gen(*i);
    i = next;
  }
  out << Qt::endl;
}

void GenerateAstRule::operator()(Model::SymbolItem *sym)
{
  if(!mForce)
  {
    QString base = globalSystem.astBaseClasses.value(sym->mName, QString());
    if(!base.isEmpty() && !mGenerated.contains(base))
    {
      if(mFirstTime)
        mToGenerate.insert(sym);
      return;
    }
  }
  if(!mFirstTime)
    mToGenerate.remove(sym);
  mNames.clear();
  mInAlternative = false;
  mInCons = false;

  World::Environment::iterator it = globalSystem.env.find(sym);
  while (it != globalSystem.env.end())
  {
    Model::EvolveItem *e = *it;
    if (it.key() != sym)
      break;
    
    ++it;
    
    visitNode(e);
  }
}

void GenerateAstRule::visitEvolve(Model::EvolveItem *node)
{
  Model::SymbolItem *sym = node->mSymbol;
  if (node->mItem->kind == Model::OperatorItem::NodeKind)
  {
    out << "struct " << globalSystem.exportMacro << " " << sym->mCapitalizedName << "Ast: public "
        << globalSystem.astBaseClasses.value(sym->mName, QStringLiteral("AstNode"))
        << "{ enum { KIND = " << sym->mCapitalizedName << "Kind }; };" << Qt::endl << Qt::endl;
    #define O(thestr) \
    out << "struct " << globalSystem.exportMacro << thestr << sym->mCapitalizedName << "Ast: public " \
        << sym->mCapitalizedName << "Ast" \
        << " {" << Qt::endl \
        << "enum { KIND =" << thestr << sym->mCapitalizedName << "Kind };" << Qt::endl \
        << "AstNode *first;" << Qt::endl \
        << thestr << sym->mCapitalizedName << "Ast(" \
        << ")" << Qt::endl \
        << "{\n}" << Qt::endl \
        << thestr << sym->mCapitalizedName << "Ast(" \
        << "AstNode *first)" << Qt::endl \
        << ": first(first)" << Qt::endl \
        << "{\n}" << Qt::endl;\
        mGenerated.insert(thestr);
        
    O(QStringLiteral(" Prefix"))

    DefaultVisitor::visitEvolve(node);
      
    out << "};" << Qt::endl << Qt::endl;
    O(QStringLiteral(" Postfix"))

    DefaultVisitor::visitEvolve(node);
      
    out << "};" << Qt::endl << Qt::endl;
    
    #undef O
    
    out << "struct " << globalSystem.exportMacro << " Binary" << sym->mCapitalizedName << "Ast: public "
        << sym->mCapitalizedName << "Ast"
        << " {" << Qt::endl
        << "enum { KIND = Binary" << sym->mCapitalizedName << "Kind };" << Qt::endl
        << "AstNode *first;" << Qt::endl
        << "AstNode *second;" << Qt::endl
        << "Binary" << sym->mCapitalizedName << "Ast("
        << "AstNode *first)" << Qt::endl
        << ": first(first)" << Qt::endl
        << "{\n}" << Qt::endl;
    DefaultVisitor::visitEvolve(node);
    out << "};" << Qt::endl << Qt::endl;
    
    out << "struct " << globalSystem.exportMacro << " Ternary" << sym->mCapitalizedName << "Ast: public "
        << sym->mCapitalizedName << "Ast"
        << " {" << Qt::endl
        << "enum { KIND = Ternary" << sym->mCapitalizedName << "Kind };" << Qt::endl
        << "AstNode *first;" << Qt::endl
        << "AstNode *second;" << Qt::endl
        << "AstNode *third;" << Qt::endl
        << "Ternary" << sym->mCapitalizedName << "Ast("
        << "AstNode *first)" << Qt::endl
        << ": first(first)" << Qt::endl
        << "{\n}" << Qt::endl;
    DefaultVisitor::visitEvolve(node);
    out << "};" << Qt::endl << Qt::endl;
  }
  else
  {
    out << "struct " << globalSystem.exportMacro << " " << sym->mCapitalizedName << "Ast: public "
        << globalSystem.astBaseClasses.value(sym->mName, QStringLiteral("AstNode"))
        << " {" << Qt::endl
        << "enum { KIND = " << sym->mCapitalizedName << "Kind };" << Qt::endl << Qt::endl;

    DefaultVisitor::visitEvolve(node);

    out << "};" << Qt::endl << Qt::endl;
  }
}

void GenerateAstRule::visitVariableDeclaration(Model::VariableDeclarationItem *node)
{
  GenerateVariableDeclaration<true, true> gen_var_decl(out);
  if (node->mStorageType != Model::VariableDeclarationItem::StorageTemporary
      && mNames.find(node->mName) == mNames.end())
    {
      gen_var_decl(node);

      out << ";" << Qt::endl;

      mNames.insert(node->mName);
    }

  DefaultVisitor::visitVariableDeclaration(node);
}

void GenerateAstRule::visitInlinedNonTerminal(Model::InlinedNonTerminalItem* node)
{
  KDevPG::DefaultVisitor::visitEvolve(globalSystem.searchRule(node->mSymbol));
}

void GenerateAstRule::visitAlternative(Model::AlternativeItem *node)
{
  bool in_alternative = switchAlternative(true);

#if defined(AST_OPT_BRANCH)
  if (!in_alternative)
    {
      out << "union" << Qt::endl
          << "{" << Qt::endl
          << "AstNode *__nodeCast;" << Qt::endl
          << "qint64 __token_cast;" << Qt::endl
          << Qt::endl;
    }
#endif

  DefaultVisitor::visitAlternative(node);

#if defined(AST_OPT_BRANCH)
  if (!in_alternative)
    out << "}; // union" << Qt::endl;
#endif

  switchAlternative(in_alternative);
}

void GenerateAstRule::visitCons(Model::ConsItem *node)
{
  bool in_cons = switchCons(true);

#if defined(AST_OPT_BRANCH)
  if (!in_cons)
    {
      out << "struct" << Qt::endl
          << "{" << Qt::endl;
    }
#endif

  DefaultVisitor::visitCons(node);

#if defined(AST_OPT_BRANCH)
  if (!in_cons)
    {
      out << "}; // struct" << Qt::endl;
      mNames.clear();
    }
#endif

  switchCons(in_cons);
}

bool GenerateAstRule::switchAlternative(bool alt)
{
  bool old = mInAlternative;
  mInAlternative = alt;
  return old;
}

bool GenerateAstRule::switchCons(bool c)
{
  bool old = mInCons;
  mInCons = c;
  return old;
}

void GenerateAstFwd::operator()()
{
  out << "struct " << " AstNode;";
  
  for (QMap<QString, Model::SymbolItem*>::iterator it = globalSystem.symbols.begin();
       it != globalSystem.symbols.end(); ++it)
  {
    Model::SymbolItem *sym = *it;
    #define O(name) out << "struct " << name << "Ast;" << Qt::endl;
    O(sym->mCapitalizedName)
    if(isOperatorSymbol(sym))
    {
      O(QLatin1String("Prefix") + sym->mCapitalizedName)
      O(QLatin1String("Postfix") + sym->mCapitalizedName)
      O(QLatin1String("Binary") + sym->mCapitalizedName)
      O(QLatin1String("Ternary") + sym->mCapitalizedName)
    }
    #undef O
  }
}

}
