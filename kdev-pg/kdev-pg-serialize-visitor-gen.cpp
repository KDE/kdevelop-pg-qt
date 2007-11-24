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
#include <iostream>


namespace KDevPG
{

void GenerateSerializeVisitor::operator()()
{
  out << "class " << globalSystem.exportMacro << " Serialize: public DefaultVisitor {" << std::endl
      << "public:" << std::endl;

  out << "static void read(KDevPG::MemoryPool *p," << std::endl
      << "AstNode *node, std::ifstream *i) { " << std::endl
      << "serialize(p, node, i); " << std::endl
      << "}" << std::endl << std::endl;

  out << "static void write(AstNode *node, std::ofstream *o) { " << std::endl
      << "serialize(node, o); " << std::endl
      << "}" << std::endl << std::endl;

  out << "private:" << std::endl;
  out << "serialize(KDevPG::MemoryPool *p," << std::endl
      << "AstNode *node, std::ifstream *i) : in(i), out(0) {" << std::endl
      << "memoryPool = p;" << std::endl
      << "if ( !node )" << std::endl
      << "node = create<" << globalSystem.start->mSymbol->mName << "Ast>();" << std::endl
      << "visitNode( node );" << std::endl
      << "}" << std::endl << std::endl;

  out << "serialize(AstNode *node, std::ofstream *o) : in(0), out(o) {" << std::endl
      << "visitNode( node );" << std::endl
      << "}" << std::endl << std::endl;

  out << "std::ifstream *in;" << std::endl;
  out << "std::ofstream *out;" << std::endl << std::endl;

  out << "// memory pool" << std::endl
      << "typedef KDevPG::MemoryPool memoryPoolType;" << std::endl
      << "KDevPG::MemoryPool *memoryPool;" << std::endl
      << "template <class T>" << std::endl
      << "inline T *create() {" << std::endl
      << "T *node = new (memoryPool->allocate(sizeof(T))) T();" << std::endl
      << "node->kind = T::KIND;" << std::endl
      << "return node;" << std::endl
      << "}" << std::endl;

  out << "template <class T, class E>" << std::endl
      << "void handleListNode(const list_node<T> *t, E *e) {" << std::endl
      << "if (in) {" << std::endl

      //list in
      << "bool b;" << std::endl
      << "in->read(reinterpret_cast<char*>(&b), sizeof(bool));" << std::endl
      << "if (b) {" << std::endl
      << "int count;" << std::endl
      << "in->read(reinterpret_cast<char*>(&count), sizeof(int));" << std::endl
      << "for ( int i = 0; i < count; ++i ) {" << std::endl
      << "    e = create<E>();" << std::endl // FIXME: what about token
      << "    t = snoc(t, e, memoryPool);" << std::endl
      << "}" << std::endl
      << "}" << std::endl
      //end list in

      << "} else if (out) {" << std::endl

      //list out
      <<"if (t) {" << std::endl
      << "bool b = true;" << std::endl
      << "out->write(reinterpret_cast<char*>(&b), sizeof(bool));" << std::endl
      << "int c = t->count();" << std::endl
      << "out->write(reinterpret_cast<char*>(&c), sizeof(int));" << std::endl
      << "} else {" << std::endl
      << "bool b = false;" << std::endl
      << "out->write(reinterpret_cast<char*>(&b), sizeof(bool));" << std::endl
      << "}" << std::endl << std::endl
      //end list out

      << "}" << std::endl
      << "}" << std::endl << std::endl;

  out << "template <class T>" << std::endl
      << "void handleAstNode(T *t) {" << std::endl
      << "if (in) {" << std::endl

      //ast in
      << "bool b;" << std::endl
      << "in->read(reinterpret_cast<char*>(&b), sizeof(bool));" << std::endl
      << "if (b) {" << std::endl
      << "t = create<T>();" << std::endl

      << "in->read(reinterpret_cast<char*>(&t->startToken)," << std::endl
      << "sizeof(std::size_t));" << std::endl
      << "in->read(reinterpret_cast<char*>(&t->endToken)," << std::endl
      << "sizeof(std::size_t));" << std::endl
      << "}" << std::endl
      //end ast in

      << "} else if (out) {" << std::endl

      //ast out
      << "if (t) {" << std::endl
      << "bool b = true;" << std::endl
      << "out->write(reinterpret_cast<char*>(&b), sizeof(bool));" << std::endl
      << "out->write(reinterpret_cast<char*>(&t->startToken)," << std::endl
      << "sizeof(std::size_t));" << std::endl
      << "out->write(reinterpret_cast<char*>(&t->endToken)," << std::endl
      << "sizeof(std::size_t));" << std::endl
      << "} else {" << std::endl
      << "bool b = false;" << std::endl
      << "out->write(reinterpret_cast<char*>(&b), sizeof(bool));" << std::endl
      << "}" << std::endl << std::endl
      //end ast out

      << "}" << std::endl
      << "}" << std::endl << std::endl;

  out << "template <class T>" << std::endl
      << "void handleVariable(T *t) {" << std::endl
      << "if (in) {" << std::endl
      << "in->read( reinterpret_cast<char*>(t), sizeof(T));" << std::endl
      << "} else if (out) {" << std::endl
      << "out->write( reinterpret_cast<char*>(t), sizeof(T));" << std::endl
      << "}" << std::endl
      << "}" << std::endl << std::endl;

  std::for_each(globalSystem.symbols.begin(), globalSystem.symbols.end(),
                GenerateSerializeVisitorRule(out));

  out << "};" << std::endl;
}

void GenerateSerializeVisitorRule::operator()(std::pair<std::string,
                                          Model::SymbolItem*> const &__it)
{
  mNames.clear();
  mVariableDeclarations.clear();

  Model::SymbolItem *sym = __it.second;

  bool has_members = false;
  HasMemberNodes hms(has_members);
  hms(sym);

  out << "virtual void visit" << sym->mName
      << "(" << sym->mName << "Ast *" << "node"
      << ") {" << std::endl;

  World::Environment::iterator it = globalSystem.env.find(sym);
  while (it != globalSystem.env.end())
    {
      Model::EvolveItem *e = (*it).second;
      if ((*it).first != sym)
        break;

      ++it;

      visitNode(e);
    }

  out << "DefaultVisitor::visit" << sym->mName
      << "(" << "node"
      << ");" << std::endl;

  out << "}" << std::endl << std::endl;
}

void GenerateSerializeVisitorRule::visitVariableDeclaration(Model::VariableDeclarationItem *node)
{
  do
  {
    if (node->mStorageType != Model::VariableDeclarationItem::StorageAstMember)
      break;

    if (mNames.find(node->mName) != mNames.end())
      break;

    std::string ext =
        ( node->mVariableType == Model::VariableDeclarationItem::TypeNode ?
        "Ast" : "");

    std::string type = std::string(node->mType) + ext;
    std::string name = std::string(node->mName);

    if (node->mVariableType == Model::VariableDeclarationItem::TypeToken)
      type = "std::size_t";

    if (node->mIsSequence)
    {
      out << "{" << std::endl
          << type << " *e = 0;" << std::endl
          << "handleListNode(node->" << name << "_sequence, e);" << std::endl
          << "}" << std::endl;
    }
    else if (node->mVariableType == Model::VariableDeclarationItem::TypeNode)
    {
      out << "handleAstNode(node->" << name << ");" << std::endl;
    }
    else if (node->mVariableType == Model::VariableDeclarationItem::TypeVariable
             || node->mVariableType == Model::VariableDeclarationItem::TypeToken)
    {
      out << "handleVariable(&node->" << name << ");" << std::endl;
    }
    else
    {
      assert(0); // every variable type must be supported
    }

    mNames.insert(node->mName);
    mVariableDeclarations.push_back(node);

  } while(false);

  DefaultVisitor::visitVariableDeclaration(node);
}

}
