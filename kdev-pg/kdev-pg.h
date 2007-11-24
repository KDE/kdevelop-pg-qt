/* This file is part of kdev-pg
   Copyright (C) 2005 Roberto Raggi <roberto@kdevelop.org>
   Copyright (C) 2006 Jakob Petsovits <jpetso@gmx.at>
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

#ifndef KDEV_PG_H
#define KDEV_PG_H

#include "kdev-pg-ast.h"

#include <set>
#include <map>
#include <deque>
#include <string>
#include <cassert>

namespace KDevPG
{
  Model::ZeroItem *zero();
  Model::PlusItem *plus(Model::Node *item);
  Model::StarItem *star(Model::Node *item);
  Model::SymbolItem *symbol(char const *name);
  Model::ActionItem *action(Model::Node *item, char const *code);
  Model::AlternativeItem *alternative(Model::Node *left, Model::Node *right);
  Model::ConsItem *cons(Model::Node *left, Model::Node *right);
  Model::EvolveItem *evolve(
      Model::Node *item, Model::SymbolItem *symbol,
      Model::VariableDeclarationItem *declarations, char const *code
  );
  Model::TryCatchItem *tryCatch(Model::Node *try_item, Model::Node *catch_item);
  Model::AliasItem *alias(char const *code, Model::SymbolItem *symbol);
  Model::TerminalItem *terminal(char const *name, char const *description);
  Model::NonTerminalItem *nonTerminal(Model::SymbolItem *symbol, char const *arguments);
  Model::ConditionItem *condition(char const *code, Model::Node *item);
  Model::AnnotationItem *annotation(
      char const *name, Model::Node *item, bool isSequence,
      Model::VariableDeclarationItem::StorateType storageType
  );
  Model::VariableDeclarationItem *variableDeclaration(
      Model::VariableDeclarationItem::DeclarationType declarationType,
      Model::VariableDeclarationItem::StorateType     storageType,
      Model::VariableDeclarationItem::VariableType    variableType,
      bool isSequence, char const* name, char const *type
  );
  Settings::MemberItem *member(Settings::MemberItem::MemberKind kind, char const *code);

class World
{
public:
  typedef struct MemberCode {
    std::deque<Settings::MemberItem*> declarations;
    std::deque<Settings::MemberItem*> constructorCode;
    std::deque<Settings::MemberItem*> destructorCode;
  };
  typedef std::set<Model::Node*> NodeSet;
  typedef std::map<std::string, Model::SymbolItem*> SymbolSet;
  typedef std::map<std::string, Model::TerminalItem*> TerminalSet;
  typedef std::multimap<Model::SymbolItem*, Model::EvolveItem*> Environment;
  typedef std::multimap<std::string, std::string> NamespaceSet;

  typedef std::map<std::pair<Model::Node*, int>, NodeSet> FirstSet;
  typedef std::map<std::pair<Model::Node*, int>, NodeSet> FollowSet;

  /**pair: list of rules whose FIRST set is used to calculate FOLLOW,
  list of rules whose FOLLOW set is used to calculate FOLLOW*/
  typedef std::pair<NodeSet, NodeSet> FollowDep;
  /**key: rule whose FOLLOW set has a dependency on other rules' FIRST and FOLLOW,
  value: follow set dependency*/
  typedef std::map<Model::Node*, FollowDep> FollowDeps;

  World()
    : tokenStream("kdev_pg_tokenStream"), language(0), ns(0), decl(0), bits(0),
      exportMacro(""), exportMacroHeader(0), GenerateAst(true),
      generateSerializeVisitor(false), generateDebugVisitor(false),
      needStateManagement(false), start(0), mZero(0)
  {}

  // options
  char const *tokenStream;
  char const *language;
  char const *ns;
  char const *decl;
  char const *bits;
  char const *exportMacro;
  char const *exportMacroHeader;
  bool GenerateAst;
  bool generateSerializeVisitor;
  bool generateDebugVisitor;
  bool needStateManagement;

  Model::ZeroItem *zero()
  {
    if (!mZero)
      mZero = KDevPG::zero();
    return mZero;
  }

  Model::TerminalItem *terminal(char const *__name)
  {
    std::string name = __name;
    TerminalSet::iterator it = terminals.find(name);
    if (it == terminals.end())
      return KDevPG::terminal(__name, __name);

    return (*it).second;
  }

  void pushRule(Model::Node *rule)
  {
    Model::EvolveItem *e = nodeCast<Model::EvolveItem*>(rule);
    assert(e != 0);

    if (rules.empty())
      start = e;
    rules.push_back(e);
  }

  void pushNamespace(char const *name, char const *code)
  {
    namespaces.insert(std::make_pair(name, code));
  }

  void pushParserClassMember(Model::Node *member)
  {
    Settings::MemberItem *m = nodeCast<Settings::MemberItem*>(member);
    assert(m != 0);

    if (m->mMemberKind == Settings::MemberItem::ConstructorCode)
      parserclassMembers.constructorCode.push_back(m);
    else if (m->mMemberKind == Settings::MemberItem::DestructorCode)
      parserclassMembers.destructorCode.push_back(m);
    else // public, protected or private declaration
      parserclassMembers.declarations.push_back(m);
  }

  Model::TerminalItem *pushTerminal(char const *__name, char const *__description)
  {
    std::string name = __name;
    TerminalSet::iterator it = terminals.find(name);
    if (it == terminals.end())
      it = terminals.insert(std::make_pair(name, KDevPG::terminal(__name, __description))).first;

    return (*it).second;
  }

  Model::SymbolItem *pushSymbol(char const *__name)
  {
    std::string name = __name;
    SymbolSet::iterator it = symbols.find(name);
    if (it == symbols.end())
      it = symbols.insert(std::make_pair(name, KDevPG::symbol(__name))).first;

    return (*it).second;
  }

  FirstSet::iterator firstBegin() { return firstSet.begin(); }
  FirstSet::iterator firstEnd() { return firstSet.end(); }

  FollowSet::iterator followBegin() { return followSet.begin(); }
  FollowSet::iterator followEnd() { return followSet.end(); }

  NodeSet &first(Model::Node *node, int K = 1)
  { return firstSet[std::make_pair(node, K)]; }

  NodeSet &follow(Model::Node *node, int K = 1)
  { return followSet[std::make_pair(node, K)]; }

  FollowDep &followDep(Model::Node *node)
  { return followDeps[node]; }

  FirstSet::iterator findInFirst(Model::Node *node, int K = 1)
  { return firstSet.find(std::make_pair(node, K)); }

  FollowSet::iterator findInFollow(Model::Node *node, int K = 1)
  { return followSet.find(std::make_pair(node, K)); }

  Model::EvolveItem *start;
  Model::ZeroItem *mZero;

  SymbolSet symbols;
  TerminalSet terminals;
  std::deque<Model::Node*> rules;
  NamespaceSet namespaces;
  MemberCode parserclassMembers;

  Environment env;

private:
  FirstSet firstSet;
  FollowSet followSet;
  FollowDeps followDeps;
};


bool reducesToEpsilon(Model::Node *node);
bool isZero(Model::Node *node);
std::ostream &operator << (std::ostream &out, Model::Node const *__node);

}

extern KDevPG::World globalSystem;
extern FILE *file;

#endif // KDEV_PG_H
