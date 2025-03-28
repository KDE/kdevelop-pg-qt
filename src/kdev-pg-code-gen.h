/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEV_PG_CODEGEN_H
#define KDEV_PG_CODEGEN_H

#include "kdev-pg.h"
#include "kdev-pg-default-visitor.h"

namespace KDevPG
{

/**
 * This class is the LL/shunting yard-parser code generator. It generates the actual parsing code.
 * @todo Investigate whether parts of it are not code-generation, but in fact realy computations which should be handled independently from the output-language.
 */
class CodeGenerator: protected DefaultVisitor
{
public:
  QTextStream& out;
  Model::EvolveItem *mEvolve;
  QSet<QString> *mNames;
  Model::SymbolItem *mSym;

public:
  CodeGenerator(QTextStream& o, QSet<QString> *names, Model::SymbolItem *sym)
    : out(o), mNames(names), mSym(sym), mCurrentCatchId(0)
  {}

  void operator()(Model::Node *node);

protected:
  void visitZero(Model::ZeroItem *node) override;
  void visitSymbol(Model::SymbolItem *node) override;
  void visitNonTerminal(Model::NonTerminalItem *node) override;
  void visitTerminal(Model::TerminalItem *node) override;
  void visitPlus(Model::PlusItem *node) override;
  void visitStar(Model::StarItem *node) override;
  void visitAction(Model::ActionItem *node) override;
  void visitAlternative(Model::AlternativeItem *node) override;
  void visitCons(Model::ConsItem *node) override;
  void visitEvolve(Model::EvolveItem *node) override;
  void visitTryCatch(Model::TryCatchItem *node) override;
  void visitAlias(Model::AliasItem *node) override;
  void visitAnnotation(Model::AnnotationItem *node) override;
  void visitCondition(Model::ConditionItem *node) override;
  void visitOperator(Model::OperatorItem *node) override;

private:
  int mCurrentCatchId;
  int setCatchId(int catch_id);
};

class GenerateForwardParserRule
{
public:
  QTextStream& out;

public:
  GenerateForwardParserRule(QTextStream& o): out(o)
  {}

  void operator()(QPair<QString, Model::SymbolItem*> const &__it);
};

class GenerateParserRule
{
public:
  QTextStream& out;
  QSet<QString> mNames;

public:
  GenerateParserRule(QTextStream& o): out(o)
  {}

  void operator()(QPair<QString, Model::SymbolItem*> const &__it);
};

class GenerateLocalDeclarations: protected DefaultVisitor
{
public:
  QTextStream& out;
  QSet<QString> *mNames;

public:
  GenerateLocalDeclarations(QTextStream& o, QSet<QString> *names)
    : out(o), mNames(names)
  {}

  void operator()(Model::Node *node);
  void visitVariableDeclaration(Model::VariableDeclarationItem *node) override;
};

class GenerateParseMethodSignature: protected DefaultVisitor
{
public:
  QTextStream& out;
  bool firstParameter;
  QSet<QString> *mNames;

public:
  GenerateParseMethodSignature(QTextStream& o, QSet<QString> *names)
    : out(o), firstParameter(true), mNames(names)
  {}

  void operator()(Model::SymbolItem *node);
  void visitVariableDeclaration(Model::VariableDeclarationItem *node) override;
};

class GenerateRecursiveDelegation
{
public:
  QTextStream& out;
  
  GenerateRecursiveDelegation(QTextStream& o)
    : out(o)
  {}
  
  void operator()(Model::SymbolItem *node);
};

namespace GenerateVariableDeclarationImpl
{
  void printType(QTextStream &out, Model::VariableDeclarationItem *node);
  void printName(QTextStream &out, Model::VariableDeclarationItem *node);
};

template<bool printType, bool printName>
class GenerateVariableDeclaration
{
public:
  QTextStream& out;

public:
  GenerateVariableDeclaration(QTextStream& o): out(o)
  {}

  void operator()(Model::VariableDeclarationItem *node)
  {
    if (printType)
      GenerateVariableDeclarationImpl::printType(out, node);
    if (printName)
      GenerateVariableDeclarationImpl::printName(out, node);
  }
};

class GenerateTokenVariableInitialization : public DefaultVisitor
{
public:
  QTextStream& out;
  GenerateTokenVariableInitialization( QTextStream& o) : out(o)
  {
  }

  void operator()(Model::SymbolItem* node);
  void visitVariableDeclaration(Model::VariableDeclarationItem *node) override;
};

class GenerateMemberCode
{
public:
  QTextStream& out;
  int mKindMask;

public:
  GenerateMemberCode(QTextStream& o, int kind_mask)
  : out(o), mKindMask(kind_mask)
  {}

  void operator()(Settings::MemberItem* m);
};

class GenerateParserDeclarations
{
public:
  QTextStream& out;

public:
  GenerateParserDeclarations(QTextStream& o): out(o)
  {}

  void operator()();
};

class GenerateParserBits
{
public:
  QTextStream& out;

public:
  GenerateParserBits(QTextStream& o): out(o)
  {}

  void operator()();
};

class GenerateTokenTexts
{
public:
  QTextStream& out;

public:
  GenerateTokenTexts(QTextStream& o): out(o)
  {}

  void operator()();
};

}

#endif // KDEV_PG_CODEGEN_H
