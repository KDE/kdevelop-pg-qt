/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEV_PG_GENERATE_H
#define KDEV_PG_GENERATE_H

class QString;

namespace KDevPG
{
void generateOutput();
void generateLexer();
void generateVisitor(const QString& name, bool inherit_default);
}

#endif // KDEV_PG_GENERATE_H
