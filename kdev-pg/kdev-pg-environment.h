/* This file is part of kdev-pg
   Copyright (C) 2005 Roberto Raggi <roberto@kdevelop.org>

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

#ifndef KDEV_PG_ENVIRONMENT_H
#define KDEV_PG_ENVIRONMENT_H

#include "kdev-pg-default-visitor.h"
#include "kdev-pg.h"

namespace KDevPG
{
class InitializeEnvironment: protected DefaultVisitor
{
public:
  void operator ()(Model::Node *node)
  {
    visitNode(node);
  }
protected:
  virtual void visitEvolve(Model::EvolveItem *node)
  {
    globalSystem.env.insert(std::make_pair(node->mSymbol, node));
  }
};
}
#endif // KDEV_PG_ENVIRONMENT_H
