/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>
    SPDX-FileCopyrightText: 2006 Adam Treat <treat@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg-serialize-visitor-gen.h"
#include "kdev-pg.h"

namespace KDevPG
{

void GenerateSerializeVisitor::operator()()
{
  out << "class " << globalSystem.exportMacro << " Serialize: public DefaultVisitor {" << Qt::endl
      << "public:" << Qt::endl;

  out << "static void read(KDevPG::MemoryPool *p," << Qt::endl
      << "AstNode *node, QIODevice* i) { " << Qt::endl
      << "Serialize(p, node, i); " << Qt::endl
      << "}" << Qt::endl << Qt::endl;

  out << "static void write(AstNode *node, QIODevice* o) { " << Qt::endl
      << "Serialize(node, o); " << Qt::endl
      << "}" << Qt::endl << Qt::endl;

  out << "private:" << Qt::endl;
  out << "Serialize(KDevPG::MemoryPool *p," << Qt::endl
      << "AstNode *node, QIODevice* i) : in(i) {" << Qt::endl
      << "memoryPool = p;" << Qt::endl
      << "if ( !node )" << Qt::endl
      << "node = create<" << (*globalSystem.start.begin())->mCapitalizedName << "Ast>();" << Qt::endl
      << "visitNode( node );" << Qt::endl
      << "}" << Qt::endl << Qt::endl;

  out << "Serialize(AstNode *node, QIODevice *o) : out(o) {" << Qt::endl
      << "visitNode( node );" << Qt::endl
      << "}" << Qt::endl << Qt::endl;

  out << "QDataStream in;" << Qt::endl;
  out << "QDataStream out;" << Qt::endl << Qt::endl;

  out << "// memory pool" << Qt::endl
      << "typedef KDevPG::MemoryPool memoryPoolType;" << Qt::endl
      << "KDevPG::MemoryPool *memoryPool;" << Qt::endl
      << "template <class T>" << Qt::endl
      << "inline T *create() {" << Qt::endl
      << "T *node = new (memoryPool->allocate(sizeof(T))) T();" << Qt::endl
      << "node->kind = T::KIND;" << Qt::endl
      << "return node;" << Qt::endl
      << "}" << Qt::endl;

  out << "template <class T, class E>" << Qt::endl
      << "void handleListNode(const KDevPG::ListNode<T> *t, E *e) {" << Qt::endl
      << "if (in) {" << Qt::endl

      //list in
      << "bool b;" << Qt::endl
      << "in >> b;" << Qt::endl
      << "if (b) {" << Qt::endl
      << "qint64 count;" << Qt::endl
      << "in >> count;" << Qt::endl
      << "for ( qint64 i = 0; i < count; ++i ) {" << Qt::endl
      << "    e = create<E>();" << Qt::endl // FIXME: what about token
      << "    t = KDevPG::snoc(t, e, memoryPool);" << Qt::endl
      << "}" << Qt::endl
      << "}" << Qt::endl
      //end list in

      << "} else if (out) {" << Qt::endl

      //list out
      <<"if (t) {" << Qt::endl
      << "out << true;" << Qt::endl
      << "out << t->count();" << Qt::endl
      << "} else {" << Qt::endl
      << "out << false;" << Qt::endl
      << "}" << Qt::endl << Qt::endl
      //end list out

      << "}" << Qt::endl
      << "}" << Qt::endl << Qt::endl;

  out << "template <class T>" << Qt::endl
      << "void handleAstNode(T *t) {" << Qt::endl
      << "if (in) {" << Qt::endl

      //ast in
      << "bool b;" << Qt::endl
      << "in >> b;" << Qt::endl
      << "if (b) {" << Qt::endl
      << "t = create<T>();" << Qt::endl

      << "in >> t->startToken;" << Qt::endl
      << "in >> t->endToken;" << Qt::endl
      << "}" << Qt::endl
      //end ast in

      << "} else if (out) {" << Qt::endl

      //ast out
      << "if (t) {" << Qt::endl
      << "bool b = true;" << Qt::endl
      << "out << true;" << Qt::endl
      << "out << t->startToken;" << Qt::endl
      << "out << t->endToken;" << Qt::endl
      << "} else {" << Qt::endl
      << "out << false;" << Qt::endl
      << "}" << Qt::endl << Qt::endl
      //end ast out

      << "}" << Qt::endl
      << "}" << Qt::endl << Qt::endl;

  out << "template <class T>" << Qt::endl
      << "void handleVariable(T *t) {" << Qt::endl
      << "if (in) {" << Qt::endl
      << "in >> t;" << Qt::endl
      << "} else if (out) {" << Qt::endl
      << "out << t;" << Qt::endl
      << "}" << Qt::endl
      << "}" << Qt::endl << Qt::endl;


  GenerateSerializeVisitorRule gen(out);
  for( World::SymbolSet::iterator it = globalSystem.symbols.begin();
       it != globalSystem.symbols.end(); ++it )
  {
    gen(qMakePair(it.key(), *it));
  }

  out << "};" << Qt::endl;
}

void GenerateSerializeVisitorRule::operator()(QPair<QString,
                                          Model::SymbolItem*> const &__it)
{
  mNames.clear();
  mVariableDeclarations.clear();

  Model::SymbolItem *sym = __it.second;

  bool has_members = false;
  HasMemberNodes hms(has_members);
  hms(sym);

  out << "void visit" << sym->mCapitalizedName
      << "(" << sym->mCapitalizedName << "Ast *" << "node"
      << ") override {" << Qt::endl;

  Model::EvolveItem *e = globalSystem.searchRule(sym);
  visitNode(e);
  
  out << "DefaultVisitor::visit" << sym->mCapitalizedName
      << "(" << "node"
      << ");" << Qt::endl;

  out << "}" << Qt::endl << Qt::endl;
}

void GenerateSerializeVisitorRule::visitVariableDeclaration(Model::VariableDeclarationItem *node)
{
  do
  {
    if (node->mStorageType != Model::VariableDeclarationItem::StorageAstMember)
      break;

    if (mNames.find(node->mName) != mNames.end())
      break;

    QString ext =
        ( node->mVariableType == Model::VariableDeclarationItem::TypeNode ?
        QStringLiteral("Ast") : QString());

    QString type = node->mType + ext;
    QString name = node->mName;

    if (node->mVariableType == Model::VariableDeclarationItem::TypeToken)
      type = QStringLiteral("qint64");

    if (node->mIsSequence)
    {
      out << "{" << Qt::endl
          << type << " *e = 0;" << Qt::endl
          << "handleListNode(node->" << name << "Sequence, e);" << Qt::endl
          << "}" << Qt::endl;
    }
    else if (node->mVariableType == Model::VariableDeclarationItem::TypeNode)
    {
      out << "handleAstNode(node->" << name << ");" << Qt::endl;
    }
    else if (node->mVariableType == Model::VariableDeclarationItem::TypeVariable
             || node->mVariableType == Model::VariableDeclarationItem::TypeToken)
    {
      out << "handleVariable(&node->" << name << ");" << Qt::endl;
    }
    else
    {
      Q_ASSERT(0); // every variable type must be supported
    }

    mNames.insert(node->mName);
    mVariableDeclarations.push_back(node);

  } while(false);

  DefaultVisitor::visitVariableDeclaration(node);
}

}
