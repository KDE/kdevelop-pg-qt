/* This file is part of kdev-pg-qt
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

#ifndef KDEV_PG_SERIALIZE_VISITORGEN_H
#define KDEV_PG_SERIALIZE_VISITORGEN_H

#include "kdev-pg-default-visitor.h"
#include "kdev-pg-default-visitor-bits-gen.h" // for the HasMemberNodes class

#include <QtCore/QSet>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QTextStream>


namespace KDevPG
{

class GenerateSerializeVisitor
{
public:
  QTextStream& out;

public:
  GenerateSerializeVisitor(QTextStream& o): out(o)
  {}

  void operator()();
};

class GenerateSerializeVisitorRule: protected DefaultVisitor
{
public:
  QTextStream& out;
  QSet<QString> mNames;
  QList<Model::VariableDeclarationItem*> mVariableDeclarations;

public:
  GenerateSerializeVisitorRule(QTextStream& o): out(o)
  {}

  void operator()(QPair<QString, Model::SymbolItem*> const &__it);

protected:
  void visitVariableDeclaration(Model::VariableDeclarationItem *node) override;
};

}

#endif // KDEV_PG_SERIALIZE_VISITORGEN_H
