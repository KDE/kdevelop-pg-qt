/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg-new-visitor-gen.h"
#include "kdev-pg-default-visitor-gen.h"
#include "kdev-pg.h"


namespace KDevPG
{

void GenerateNewVisitor::operator()()
{
  out << "class " << globalSystem.exportMacro << " " << name << ": public DefaultVisitor {" << Qt::endl
      << "public:" << Qt::endl;

  GenerateDefaultVisitorRule gen(out);
  for( World::SymbolSet::iterator it = globalSystem.symbols.begin();
       it != globalSystem.symbols.end(); ++it )
  {
    gen(qMakePair(it.key(), *it));
  }

  out << "};" << Qt::endl;
}

}
