/*
    SPDX-FileCopyrightText: 2009 Milian Wolff <mail@milianw.de>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef TESTMEMORYPOOL_H
#define TESTMEMORYPOOL_H

#include <QObject>

namespace KDevPG
{

class TestMemoryPool : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();

    void bigAlloc();
};

}

#endif // TESTMEMORYPOOL_H
