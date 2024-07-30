/*
    SPDX-FileCopyrightText: 2006 Alexander Dymo <adymo@kdevelop.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEV_PG_DEBUG_VISITORGEN_H
#define KDEV_PG_DEBUG_VISITORGEN_H

#include "kdev-pg-default-visitor.h"
#include "kdev-pg-default-visitor-bits-gen.h" // for the HasMemberNodes class

#include <QSet>
#include <QList>
#include <QString>
#include <QTextStream>

namespace KDevPG
{

class GenerateDebugVisitor
{
public:
  QTextStream& out;

public:
  GenerateDebugVisitor(QTextStream& o): out(o)
  {}

  void operator()();
};

class GenerateDebugVisitorRule: protected DefaultVisitor
{
  QTextStream& out;
  QSet<QString> mNames;

public:
  GenerateDebugVisitorRule(QTextStream& o): out(o)
  {}

  void operator()(QPair<QString, Model::SymbolItem*> const &__it);

protected:
  void visitVariableDeclaration(Model::VariableDeclarationItem *node) override;
};

}

#endif // KDEV_PG_DEBUG_VISITORGEN_H

// kate: space-indent on; indent-width 2; tab-width 2; replace-tabs on
