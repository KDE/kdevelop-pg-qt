/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

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
