/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>
    SPDX-FileCopyrightText: 2006 Adam Treat <treat@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEV_PG_SERIALIZE_VISITORGEN_H
#define KDEV_PG_SERIALIZE_VISITORGEN_H

#include "kdev-pg-default-visitor.h"
#include "kdev-pg-default-visitor-bits-gen.h" // for the HasMemberNodes class

#include <QSet>
#include <QList>
#include <QString>
#include <QTextStream>


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
