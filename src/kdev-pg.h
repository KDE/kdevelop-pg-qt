/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>
    SPDX-FileCopyrightText: 2006 Alexander Dymo <adymo@kdevelop.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEV_PG_H
#define KDEV_PG_H

#include "kdev-pg-ast.h"

#include <QSet>
#include <QMap>
#include <QList>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QMultiMap>
#include <QtGlobal>
#include <QTextStream>

#include <vector>
#include <algorithm>

namespace KDevPG
{
  class GNFA;
  class GDFA;
  void deleteNFA(GNFA*);
  void deleteDFA(GDFA*);
  Model::ZeroItem *zero();
  Model::PlusItem *plus(Model::Node *item);
  Model::StarItem *star(Model::Node *item);
  Model::SymbolItem *symbol(const QString& name);
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
  Model::InlinedNonTerminalItem *inlinedNonTerminal(Model::SymbolItem *symbol);
  Model::ConditionItem *condition(const QString& code, Model::Node *item);
  Model::AnnotationItem *annotation(
      const QString& name, Model::Node *item, bool isSequence,
      Model::VariableDeclarationItem::StorageType storageType
  );
  Model::VariableDeclarationItem *variableDeclaration(
      Model::VariableDeclarationItem::DeclarationType declarationType,
      Model::VariableDeclarationItem::StorageType     storageType,
      Model::VariableDeclarationItem::VariableType    variableType,
      bool isSequence, const QString& name, const QString& type
  );
  bool isOperatorSymbol(Model::SymbolItem *node);
  Settings::MemberItem *member(Settings::MemberItem::MemberKind kind, const QString& code);
  
  Model::Operator *makeOperator(Model::Node *tok, const QString& cond, const QString& code);
  
  inline void capitalize(QString& str)
  {
    if(!str.isEmpty())
      str.replace(0, 1, str.at(0).toUpper());
  }
  
  inline QString capitalized(const QString& str)
  {
    QString ret(str);
    capitalize(ret);
    return ret;
  }
  
  QString unescaped(const QByteArray& str);
  
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
    : tokenStream(QStringLiteral("KDevPG::TokenStream")), language(), ns(), decl(), bits(),
      exportMacro(), exportMacroHeader(), astCode(), namespaceCode(),
      inputStream(QStringLiteral("KDevPG::QUtf16ToUcs4Iterator")),
      generateAst(true), hasLexer(false), generateSerializeVisitor(false),
      generateDebugVisitor(false), generateTokenText(false),
      needStateManagement(false), needOperatorStack(false),
      lineNumberPolicy(FullLineNumbers), visitorTable(false),
      conflictHandling(Permissive), mZero(nullptr),
      lexerBaseClass(QStringLiteral("KDevPG::TokenStream"))
  {}
  
  ~World()
  {
    for(auto i = regexpById.begin(); i != regexpById.end(); ++i)
      deleteNFA(*i);
    for(auto i = lexerEnvResults.begin(); i != lexerEnvResults.end(); ++i)
      deleteNFA(*i);
    for(auto i = dfaForNfa.begin(); i != dfaForNfa.end(); ++i)
      deleteDFA(*i);
  }

  // options
  QString tokenStream;
  QString language;
  QString ns;
  QString decl;
  QString bits;
  QString lexerBits;
  QString exportMacro;
  QString exportMacroHeader;
  QString astCode;
  QString namespaceCode;
  QStringList parserDeclarationHeaders;
  QStringList parserBitsHeaders;
  QStringList astHeaders;
  QStringList lexerDeclarationHeaders;
  QStringList lexerBitsHeaders;
  QString inputStream;
  bool generateAst: 1;
  bool hasLexer: 1;
  bool generateSerializeVisitor: 1;
  bool generateDebugVisitor: 1;
  bool generateTokenText: 1;
  bool needStateManagement: 1;
  bool needOperatorStack: 1;
  enum { BeautifulCode, CompatibilityLineNumbers, FullLineNumbers } lineNumberPolicy;
  bool beautifulCode: 1;
  bool visitorTable: 1;
  enum { Ignore = 0, Permissive = 1, Strict = 2 } conflictHandling: 2;

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
    Q_ASSERT(e != nullptr);

    rules.push_back(e);
  }

  void pushParserClassMember(Model::Node *member)
  {
    Settings::MemberItem *m = nodeCast<Settings::MemberItem*>(member);
    Q_ASSERT(m != nullptr);

    if (m->mMemberKind == Settings::MemberItem::ConstructorCode)
      parserclassMembers.constructorCode.push_back(m);
    else if (m->mMemberKind == Settings::MemberItem::DestructorCode)
      parserclassMembers.destructorCode.push_back(m);
    else // public, protected or private declaration
      parserclassMembers.declarations.push_back(m);
  }
  
  void pushLexerClassMember(Model::Node *member)
  {
    Settings::MemberItem *m = nodeCast<Settings::MemberItem*>(member);
    Q_ASSERT(m != nullptr);
    
    if (m->mMemberKind == Settings::MemberItem::ConstructorCode)
      lexerclassMembers.constructorCode.push_back(m);
    else if (m->mMemberKind == Settings::MemberItem::DestructorCode)
      lexerclassMembers.destructorCode.push_back(m);
    else // public, protected or private declaration
      lexerclassMembers.declarations.push_back(m);
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
    {
      it = symbols.insert(name, KDevPG::symbol(__name));
      start.insert(*it);
    }
    else
      start.remove(*it);

    return (*it);
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
  
  void pushLexerBitsHeader(QString file)
  {
    lexerBitsHeaders << file;
  }
  
  void pushLexerDeclarationHeader(QString file)
  {
    lexerDeclarationHeaders << file;
  }
  
  inline static bool ruleComp(Model::Node *a, Model::Node *b)
  {
    if(a != nullptr && a->kind == Model::NodeKindEvolve)
      a = ((Model::EvolveItem*)a)->mSymbol;
    if(b != nullptr && b->kind == Model::NodeKindEvolve)
      b = ((Model::EvolveItem*)b)->mSymbol;
    return a < b;
  }
  
  void finishedParsing()
  {
    std::sort(rules.begin(), rules.end(), &ruleComp);
  }
  
  Model::EvolveItem *searchRule(Model::SymbolItem *sym)
  {
    auto i = std::lower_bound(rules.begin(), rules.end(), sym, &ruleComp);
    if(i == rules.end() || (*i)->mSymbol != sym)
      return nullptr;
    return *i;
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

  QSet<Model::SymbolItem*> start;
  Model::ZeroItem *mZero;

  SymbolSet symbols;
  TerminalSet terminals;
  QList<Model::EvolveItem*> rules;
  MemberCode parserclassMembers, lexerclassMembers;
  AstBaseClasses astBaseClasses;
  QString parserBaseClass, lexerBaseClass;
  QMap<QString, std::vector<GNFA*> > lexerEnvs;
  QMap<QString, GNFA*> lexerEnvResults;
  QMap<QString, std::vector<QString> > lexerActions;
  QMap<QString, GNFA*> regexpById;
  QMap<QString, QString> enteringCode, leavingCode;
  QMap<GNFA*, GDFA*> dfaForNfa;
  
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
