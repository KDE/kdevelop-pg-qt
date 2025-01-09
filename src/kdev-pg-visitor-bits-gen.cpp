/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>
    SPDX-FileCopyrightText: 2010 Jonathan Schmidt-Dominé <devel@the-user.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg-visitor-bits-gen.h"
#include "kdev-pg.h"
#include <map>
#include <iostream>


namespace KDevPG
{

void GenerateVisitorBits::operator()()
{
  QMap<QString, Model::SymbolItem*>::iterator it = globalSystem.symbols.begin();
  
  if (globalSystem.visitorTable)
  {
    out << "Visitor::ParserFuncType Visitor::sParserTable[] = {" << Qt::endl;

    while (it != globalSystem.symbols.end())
      {
        Model::SymbolItem *sym = *it++;
        
        #define O(str) \
            out << "reinterpret_cast<ParserFuncType>(&Visitor::visit" << str << ")";
        
        if(isOperatorSymbol(sym))
        {
          O(QLatin1String("Prefix") + sym->mCapitalizedName)
          out << ",\n";
          O(QLatin1String("Postfix") + sym->mCapitalizedName)
          out << ",\n";
          O(QLatin1String("Binary") + sym->mCapitalizedName)
          out << ",\n";
          O(QLatin1String("Ternary") + sym->mCapitalizedName)
          out << ",\n0";
        }
        else
          O(sym->mCapitalizedName)

        if (it != globalSystem.symbols.end())
          out << ",";

        out << Qt::endl;
        
        #undef O
      }

    out << "}; // sParserTable[]" << Qt::endl;
    
    out << "void Visitor::visitNode(AstNode *node) { "
        << "if (node) (this->*sParserTable[node->kind - 1000])(node); "
        << "}" << Qt::endl;
  }
  else
  {
    out << "void Visitor::visitNode(AstNode *node) { if(node) {"
           "switch(node->kind) {";
    while (it != globalSystem.symbols.end())
    {
      Model::SymbolItem *sym = *it++;
      
      #define O(str) \
        out << "case AstNode::" << str << "Kind:\n" \
               "visit" << str << "(reinterpret_cast<" << str << "Ast*>(node)); break;";
      
      if(isOperatorSymbol(sym))
        {
          O(QLatin1String("Prefix") + sym->mCapitalizedName)
          O(QLatin1String("Postfix") + sym->mCapitalizedName)
          O(QLatin1String("Binary") + sym->mCapitalizedName)
          O(QLatin1String("Ternary") + sym->mCapitalizedName)
        }
      else
        O(sym->mCapitalizedName)
      
      #undef O
    }
      
    out << "default: Q_ASSERT(false); } } }"
        << Qt::endl;
  }
}

}

