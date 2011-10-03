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
  virtual void visitZero(Model::ZeroItem *node);
  virtual void visitSymbol(Model::SymbolItem *node);
  virtual void visitNonTerminal(Model::NonTerminalItem *node);
  virtual void visitTerminal(Model::TerminalItem *node);
  virtual void visitPlus(Model::PlusItem *node);
  virtual void visitStar(Model::StarItem *node);
  virtual void visitAction(Model::ActionItem *node);
  virtual void visitAlternative(Model::AlternativeItem *node);
  virtual void visitCons(Model::ConsItem *node);
  virtual void visitEvolve(Model::EvolveItem *node);
  virtual void visitTryCatch(Model::TryCatchItem *node);
  virtual void visitAlias(Model::AliasItem *node);
  virtual void visitAnnotation(Model::AnnotationItem *node);
  virtual void visitCondition(Model::ConditionItem *node);
  virtual void visitOperator(Model::OperatorItem *node);

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
  virtual void visitVariableDeclaration(Model::VariableDeclarationItem *node);
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
  virtual void visitVariableDeclaration(Model::VariableDeclarationItem *node);
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

template<bool printType, bool printName>
class GenerateVariableDeclaration
{
public:
  QTextStream& out;

public:
  GenerateVariableDeclaration(QTextStream& o): out(o)
  {}

  void operator()(Model::VariableDeclarationItem *node);
};

class GenerateTokenVariableInitialization : public DefaultVisitor
{
public:
  QTextStream& out;
  GenerateTokenVariableInitialization( QTextStream& o) : out(o)
  {
  }

  void operator()(Model::SymbolItem* node);
  virtual void visitVariableDeclaration(Model::VariableDeclarationItem *node);
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
