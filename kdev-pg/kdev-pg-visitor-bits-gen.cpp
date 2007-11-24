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

#include "kdev-pg-visitor-bits-gen.h"
#include "kdev-pg.h"
#include <map>
#include <iostream>


namespace KDevPG
{

void GenerateVisitorBits::operator()()
{
  out << "Visitor::ParserFuncType visitor::sParserTable[] = {" << endl;

  QMap<QString, Model::SymbolItem*>::iterator it = globalSystem.symbols.begin();
  while (it != globalSystem.symbols.end())
    {
      Model::SymbolItem *sym = *it++;
      out << "reinterpret_cast<ParserFuncType>(&Visitor::visit" << sym->mCapitalizedName << ")";

      if (it != globalSystem.symbols.end())
        out << ",";

      out << endl;
    }

  out << "}; // sParserTable[]" << endl;
}

}

