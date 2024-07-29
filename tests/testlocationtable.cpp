/*
    SPDX-FileCopyrightText: 2009 Milian Wolff <mail@milianw.de>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "testlocationtable.h"

#include <cstdlib>
#include <QTest>
#include <QDebug>

#include "../include/kdev-pg-location-table.h"

namespace KDevPG
{

void TestLocationTable::initTestCase()
{
}

void TestLocationTable::newline()
{
  LocationTable table;
  qint64 offset = 100;
  table.newline(offset);
  qint64 line;
  qint64 column;
  table.positionAt(offset, &line, &column);
  QCOMPARE(line, 0ll);
  QCOMPARE(column, offset);
}

void TestLocationTable::normalAccess()
{
  LocationTable table;
  table.newline(10);
  table.newline(20);
  qint64 line;
  qint64 column;

  qint64 myOffset = 15;
  table.positionAt(myOffset, &line, &column);
  QCOMPARE(line, 1ll);
  QCOMPARE(column, myOffset - table[1]);

  table.positionAt(0, &line, &column);
  QCOMPARE(line, 0ll);
  QCOMPARE(column, 0ll);
}

void TestLocationTable::overflow()
{
  LocationTable table;
  table.newline(10);
  table.newline(20);
  qint64 line;
  qint64 column;
  qint64 myOffset = 200;
  table.positionAt(myOffset, &line, &column);
  QCOMPARE(line, 2ll);
  QCOMPARE(column, myOffset - table[2]);
}

void TestLocationTable::underflow()
{
  LocationTable table;
  table.newline(10);
  table.newline(20);
  qint64 line;
  qint64 column;
  {
    table.positionAt(-1, &line, &column);
    QCOMPARE(line, -1ll);
    QCOMPARE(column, -1ll);
  }
  {
    table.positionAt(-1123, &line, &column);
    QCOMPARE(line, -1ll);
    QCOMPARE(column, -1ll);
  }
}

}

QTEST_MAIN(KDevPG::TestLocationTable)

#include "moc_testlocationtable.cpp"
