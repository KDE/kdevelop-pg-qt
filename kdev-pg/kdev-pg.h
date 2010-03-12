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

#include <QtCore/QSet>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QMultiMap>
#include <QtCore/QtGlobal>
#include <QtCore/QTextStream>

namespace KDevPG
{
  Model::ZeroItem *zero();
  Model::PlusItem *plus(Model::Node *item);
  Model::StarItem *star(Model::Node *item);
  Model::SymbolItem *symbol(const QString& name);
  Model::OperatorItem *operatorSymbol(const QString& name, const QString& base);
  Model::ActionItem *action(Model::Node *item, const QString& code);
  Model::AlternativeItem *alternative(Model::Node *left, Model::Node *right);
  Model::ConsItem *cons(Model::Node *left, Model::Node *right);
  Model::EvolveItem *evolve(
      Model::Node *item, Model::SymbolItem *symbol,
      Model::VariableDeclarationItem *declarations, const QString& code
  );
  Model::TryCatchItem *tryCatch(Model::Node *try_item, Model::Node *catch_item);
  Model::AliasItem *alias(const QString& code, Model::SymbolItem *symbol);
  Model::TerminalItem *terminal(const QString& name, const QString& description);
  Model::NonTerminalItem *nonTerminal(Model::SymbolItem *symbol, const QString& arguments);
  Model::ConditionItem *condition(const QString& code, Model::Node *item);
  Model::AnnotationItem *annotation(
      const QString& name, Model::Node *item, bool isSequence,
      Model::VariableDeclarationItem::StorateType storageType
  );
  Model::VariableDeclarationItem *variableDeclaration(
      Model::VariableDeclarationItem::DeclarationType declarationType,
      Model::VariableDeclarationItem::StorateType     storageType,
      Model::VariableDeclarationItem::VariableType    variableType,
      bool isSequence, const QString& name, const QString& type
  );
  Settings::MemberItem *member(Settings::MemberItem::MemberKind kind, const QString& code);
  
  Model::Operator *makeOperator(const QString& tok, const QString& cond, const QString& code);
  
  
class World
{
public:
  struct MemberCode {
    QList<Settings::MemberItem*> declarations;
    QList<Settings::MemberItem*> constructorCode;
    QList<Settings::MemberItem*> destructorCode;
  };
  typedef QSet<Model::Node*> NodeSet;
  typedef QMap<QString, Model::SymbolItem*> SymbolSet;
  typedef QMap<QString, Model::TerminalItem*> TerminalSet;
  typedef QMultiMap<Model::SymbolItem*, Model::EvolveItem*> Environment;
  typedef QMultiMap<QString, QString> NamespaceSet;

  typedef QMap<QPair<Model::Node*, int>, NodeSet> FirstSet;
  typedef QMap<QPair<Model::Node*, int>, NodeSet> FollowSet;

  /**pair: list of rules whose FIRST set is used to calculate FOLLOW,
  list of rules whose FOLLOW set is used to calculate FOLLOW*/
  typedef QPair<NodeSet, NodeSet> FollowDep;
  /**key: rule whose FOLLOW set has a dependency on other rules' FIRST and FOLLOW,
  value: follow set dependency*/
  typedef QMap<Model::Node*, FollowDep> FollowDeps;

  typedef QMap<QString, QString> AstBaseClasses;

  World()
    : tokenStream("KDevPG::TokenStream"), language(), ns(), decl(), bits(),
      exportMacro(""), exportMacroHeader(), astCode(""), namespaceCode(""),
      GenerateAst(true), generateSerializeVisitor(false), generateDebugVisitor(false),
      generateTokenText(false), needStateManagement(false), conflictHandling(Permissive), start(0), mZero(0)
  {}

  // options
  QString tokenStream;
  QString language;
  QString ns;
  QString decl;
  QString bits;
  QString exportMacro;
  QString exportMacroHeader;
  QString astCode;
  QString namespaceCode;
  QStringList parserDeclarationHeaders;
  QStringList parserBitsHeaders;
  QStringList astHeaders;
  bool GenerateAst;
  bool generateSerializeVisitor;
  bool generateDebugVisitor;
  bool generateTokenText;
  bool needStateManagement;
  enum { Ignore, Permissive, Strict } conflictHandling;

  Model::ZeroItem *zero()
  {
    if (!mZero)
      mZero = KDevPG::zero();
    return mZero;
  }

  Model::TerminalItem *terminal(QString __name)
  {
    QString name = __name;
    TerminalSet::iterator it = terminals.find(name);
    if (it == terminals.end())
      return KDevPG::terminal(__name, __name);

    return (*it);
  }

  void pushRule(Model::Node *rule)
  {
    Model::EvolveItem *e = nodeCast<Model::EvolveItem*>(rule);
    Q_ASSERT(e != 0);

    if (rules.empty())
      start = e;
    rules.push_back(e);
  }

  void pushParserClassMember(Model::Node *member)
  {
    Settings::MemberItem *m = nodeCast<Settings::MemberItem*>(member);
    Q_ASSERT(m != 0);

    if (m->mMemberKind == Settings::MemberItem::ConstructorCode)
      parserclassMembers.constructorCode.push_back(m);
    else if (m->mMemberKind == Settings::MemberItem::DestructorCode)
      parserclassMembers.destructorCode.push_back(m);
    else // public, protected or private declaration
      parserclassMembers.declarations.push_back(m);
  }

  Model::TerminalItem *pushTerminal(QString __name, QString __description)
  {
    QString name = __name;
    TerminalSet::iterator it = terminals.find(name);
    if (it == terminals.end())
      it = terminals.insert(name, KDevPG::terminal(__name, __description));

    return (*it);
  }

  Model::SymbolItem *pushSymbol(QString __name)
  {
    QString name = __name;
    SymbolSet::iterator it = symbols.find(name);
    if (it == symbols.end())
      it = symbols.insert(name, KDevPG::symbol(__name));

    return (*it);
  }
  
  Model::SymbolItem *pushOperator(Model::OperatorItem *item)
  {
//     SymbolSet::iterator it = symbols.find(item->name);
//     if(it == symbols.end())
//       it = symbols.insert(item->name, item);
//     return *it;
    symbols.insert(item->mName, item);
    return item;
  }

  void pushParserDeclarationHeader(QString file)
  {
    parserDeclarationHeaders << file;
  }

  void pushParserBitsHeader(QString file)
  {
    parserBitsHeaders << file;
  }

  void pushAstHeader(QString file)
  {
    astHeaders << file;
  }

  FirstSet::iterator firstBegin() { return firstSet.begin(); }
  FirstSet::iterator firstEnd() { return firstSet.end(); }

  FollowSet::iterator followBegin() { return followSet.begin(); }
  FollowSet::iterator followEnd() { return followSet.end(); }

  NodeSet &first(Model::Node *node, int K = 1)
  { return firstSet[qMakePair(node, K)]; }

  NodeSet &follow(Model::Node *node, int K = 1)
  { return followSet[qMakePair(node, K)]; }

  FollowDep &followDep(Model::Node *node)
  { return followDeps[node]; }

  FirstSet::iterator findInFirst(Model::Node *node, int K = 1)
  { return firstSet.find(qMakePair(node, K)); }

  FollowSet::iterator findInFollow(Model::Node *node, int K = 1)
  { return followSet.find(qMakePair(node, K)); }

  Model::EvolveItem *start;
  Model::ZeroItem *mZero;

  SymbolSet symbols;
  TerminalSet terminals;
  QList<Model::Node*> rules;
  MemberCode parserclassMembers;
  AstBaseClasses astBaseClasses;
  QString parserBaseClass;

  Environment env;

private:
  FirstSet firstSet;
  FollowSet followSet;
  FollowDeps followDeps;
};


bool reducesToEpsilon(Model::Node *node);
bool isZero(Model::Node *node);

extern KDevPG::World globalSystem;
extern QFile file;

}
QTextStream& operator << (QTextStream& out, KDevPG::Model::Node const *__node);


#endif // KDEV_PG_H
