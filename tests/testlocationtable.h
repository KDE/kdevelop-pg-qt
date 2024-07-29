/*
    SPDX-FileCopyrightText: 2009 Milian Wolff <mail@milianw.de>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef TESTLOCATIONTABLE_H
#define TESTLOCATIONTABLE_H

#include <QObject>

namespace KDevPG
{

class TestLocationTable : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();

    void underflow();
    void newline();
    void overflow();
    void normalAccess();
};

}

#endif // TESTLOCATIONTABLE_H
