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

#ifndef KDEV_PG_CODEGEN_H
#define KDEV_PG_CODEGEN_H

#include "kdev-pg-default-visitor.h"

namespace KDevPG
{

class CodeGenerator: protected DefaultVisitor
{
public:
  std::ostream &out;
  Model::EvolveItem *mEvolve;
  std::set<std::string> *mNames;

public:
  CodeGenerator(std::ostream &o, std::set<std::string> *names)
    : out(o), mNames(names), mCurrentCatchId(0)
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

private:
  int mCurrentCatchId;
  int setCatchId(int catch_id);
};

class GenerateForwardParserRule
{
public:
  std::ostream &out;

public:
  GenerateForwardParserRule(std::ostream &o): out(o)
  {}

  void operator()(std::pair<std::string, Model::SymbolItem*> const &__it);
};

class GenerateParserRule
{
public:
  std::ostream &out;
  std::set<std::string> mNames;

public:
  GenerateParserRule(std::ostream &o): out(o)
  {}

  void operator()(std::pair<std::string, Model::SymbolItem*> const &__it);
};

class GenerateLocalDeclarations: protected DefaultVisitor
{
public:
  std::ostream &out;
  std::set<std::string> *mNames;

public:
  GenerateLocalDeclarations(std::ostream &o, std::set<std::string> *names)
    : out(o), mNames(names)
  {}

  void operator()(Model::Node *node);
  virtual void visitVariableDeclaration(Model::VariableDeclarationItem *node);
};

class GenerateParseMethodSignature: protected DefaultVisitor
{
public:
  std::ostream &out;
  bool firstParameter;
  std::set<std::string> *mNames;

public:
  GenerateParseMethodSignature(std::ostream &o, std::set<std::string> *names)
    : out(o), firstParameter(true), mNames(names)
  {}

  void operator()(Model::SymbolItem *node);
  virtual void visitVariableDeclaration(Model::VariableDeclarationItem *node);
};

class GenerateVariableDeclaration
{
public:
  std::ostream &out;

public:
  GenerateVariableDeclaration(std::ostream &o): out(o)
  {}

  void operator()(Model::VariableDeclarationItem *node);
};

class GenerateToken
{
public:
  std::ostream &out;
  int mTokenValue;

public:
  GenerateToken(std::ostream &o): out(o), mTokenValue(1000)
  {}

  void operator()(std::pair<std::string, Model::TerminalItem*> const &__it);
};

class GenerateMemberCode
{
public:
  std::ostream &out;
  int mKindMask;

public:
  GenerateMemberCode(std::ostream &o, int kind_mask)
  : out(o), mKindMask(kind_mask)
  {}

  void operator()(Settings::MemberItem* m);
};

class GenerateParserDeclarations
{
public:
  std::ostream &out;

public:
  GenerateParserDeclarations(std::ostream &o): out(o)
  {}

  void operator()();
};

class GenerateParserBits
{
public:
  std::ostream &out;

public:
  GenerateParserBits(std::ostream &o): out(o)
  {}

  void operator()();
};

}

#endif // KDEV_PG_CODEGEN_H
