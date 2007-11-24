/* This file is part of kdev-pg
   Copyright (C) 2005 Roberto Raggi <roberto@kdevelop.org>
   Copyright (C) 2006 Jakob Petsovits <jpetso@gmx.at>
   Copyright (C) 2006 Adam Treat <treat@kde.org>

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

#include "kdev-pg-serialize-visitor-gen.h"
#include "kdev-pg.h"

namespace KDevPG
{

void GenerateSerializeVisitor::operator()()
{
  out << "class " << globalSystem.exportMacro << " Serialize: public DefaultVisitor {" << endl
      << "public:" << endl;

  out << "static void read(KDevPG::MemoryPool *p," << endl
      << "AstNode *node, QIODevice* i) { " << endl
      << "Serialize(p, node, i); " << endl
      << "}" << endl << endl;

  out << "static void write(AstNode *node, QIODevice* o) { " << endl
      << "Serialize(node, o); " << endl
      << "}" << endl << endl;

  out << "private:" << endl;
  out << "Serialize(KDevPG::MemoryPool *p," << endl
      << "AstNode *node, QIODevice* i) : in(i) {" << endl
      << "memoryPool = p;" << endl
      << "if ( !node )" << endl
      << "node = create<" << globalSystem.start->mSymbol->mCapitalizedName << "Ast>();" << endl
      << "visitNode( node );" << endl
      << "}" << endl << endl;

  out << "Serialize(AstNode *node, QIODevice *o) : out(o) {" << endl
      << "visitNode( node );" << endl
      << "}" << endl << endl;

  out << "QDataStream in;" << endl;
  out << "QDataStream out;" << endl << endl;

  out << "// memory pool" << endl
      << "typedef KDevPG::MemoryPool memoryPoolType;" << endl
      << "KDevPG::MemoryPool *memoryPool;" << endl
      << "template <class T>" << endl
      << "inline T *create() {" << endl
      << "T *node = new (memoryPool->allocate(sizeof(T))) T();" << endl
      << "node->kind = T::KIND;" << endl
      << "return node;" << endl
      << "}" << endl;

  out << "template <class T, class E>" << endl
      << "void handleListNode(const KDevPG::ListNode<T> *t, E *e) {" << endl
      << "if (in) {" << endl

      //list in
      << "bool b;" << endl
      << "in >> b;" << endl
      << "if (b) {" << endl
      << "qint64 count;" << endl
      << "in >> count;" << endl
      << "for ( qint64 i = 0; i < count; ++i ) {" << endl
      << "    e = create<E>();" << endl // FIXME: what about token
      << "    t = KDevPG::snoc(t, e, memoryPool);" << endl
      << "}" << endl
      << "}" << endl
      //end list in

      << "} else if (out) {" << endl

      //list out
      <<"if (t) {" << endl
      << "out << true;" << endl
      << "out << t->count();" << endl
      << "} else {" << endl
      << "out << false;" << endl
      << "}" << endl << endl
      //end list out

      << "}" << endl
      << "}" << endl << endl;

  out << "template <class T>" << endl
      << "void handleAstNode(T *t) {" << endl
      << "if (in) {" << endl

      //ast in
      << "bool b;" << endl
      << "in >> b;" << endl
      << "if (b) {" << endl
      << "t = create<T>();" << endl

      << "in >> t->startToken;" << endl
      << "in >> t->endToken;" << endl
      << "}" << endl
      //end ast in

      << "} else if (out) {" << endl

      //ast out
      << "if (t) {" << endl
      << "bool b = true;" << endl
      << "out << true;" << endl
      << "out << t->startToken;" << endl
      << "out << t->endToken;" << endl
      << "} else {" << endl
      << "out << false;" << endl
      << "}" << endl << endl
      //end ast out

      << "}" << endl
      << "}" << endl << endl;

  out << "template <class T>" << endl
      << "void handleVariable(T *t) {" << endl
      << "if (in) {" << endl
      << "in >> t;" << endl
      << "} else if (out) {" << endl
      << "out << t;" << endl
      << "}" << endl
      << "}" << endl << endl;


  for( World::SymbolSet::iterator it = globalSystem.symbols.begin();
       it != globalSystem.symbols.end(); it++ )
  {
    GenerateSerializeVisitorRule gen(out);
    gen(qMakePair(it.key(), *it));
  }

  out << "};" << endl;
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

  out << "virtual void visit" << sym->mCapitalizedName
      << "(" << sym->mCapitalizedName << "Ast *" << "node"
      << ") {" << endl;

  World::Environment::iterator it = globalSystem.env.find(sym);
  while (it != globalSystem.env.end())
    {
      Model::EvolveItem *e = (*it);
      if (it.key() != sym)
        break;

      ++it;

      visitNode(e);
    }

  out << "DefaultVisitor::visit" << sym->mCapitalizedName
      << "(" << "node"
      << ");" << endl;

  out << "}" << endl << endl;
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
        "Ast" : "");

    QString type = node->mType + ext;
    QString name = node->mName;

    if (node->mVariableType == Model::VariableDeclarationItem::TypeToken)
      type = "qint64";

    if (node->mIsSequence)
    {
      out << "{" << endl
          << type << " *e = 0;" << endl
          << "handleListNode(node->" << name << "Sequence, e);" << endl
          << "}" << endl;
    }
    else if (node->mVariableType == Model::VariableDeclarationItem::TypeNode)
    {
      out << "handleAstNode(node->" << name << ");" << endl;
    }
    else if (node->mVariableType == Model::VariableDeclarationItem::TypeVariable
             || node->mVariableType == Model::VariableDeclarationItem::TypeToken)
    {
      out << "handleVariable(&node->" << name << ");" << endl;
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
