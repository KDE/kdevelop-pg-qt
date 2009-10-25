/*
  Copyright 2009 Milian Wolff <mail@milianw.de>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public
  License version 2 as published by the Free Software Foundation.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Library General Public License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to
  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA 02110-1301, USA.
*/

#include "benchmarks.h"

#include <cstdlib>
#include <cmath>
#include <ctime>

#include "../include/kdev-pg-location-table.h"

#include <QtTest/QTest>
#include <QtCore/QDebug>

using namespace std;

namespace KDevPG
{

class BenchmarkLocationTable : public LocationTable
{
public:
  BenchmarkLocationTable()
    : LocationTable(), m_lastLine(0)
  {

    /// number of lines in each table
    const int lines = 12500;
    /// every i-th line has i chars, which gets reset each \p charResetLine line.
    const int charResetLine = 160;

    tableMaxOffset = 0;
    for ( int i = 0; i < lines; ++i ) {
      tableMaxOffset += tableMaxOffset % charResetLine + 1;
      newline(tableMaxOffset);
    }
  }
  /**
   * Bases the next access to positionAt off the last one,
   * making linear consecutive accesses very fast.
   *
   * Will not perform really good on random access, but I really
   * doubt whether that is required for a parser?
   */
  void positionAtWithMemory(qint64 offset, qint64 *line, qint64 *column)
  {
    if( offset < 0 ) {
      *line = -1;
      *column = -1;
      return;
    }

    qint64 i = m_lastLine;

    if ( lines[m_lastLine] < offset ) {
      // walk forward
      for( ; i < currentLine; ++i ) {
        if( lines[i] > offset ) {
          --i;
          break;
        } else if( lines[i] == offset ) {
          break;
        }
      }
    } else if ( lines[m_lastLine] > offset ) {
      // walk backward
      for( ; i >= 0; --i ) {
        if ( lines[i] <= offset ) {
          break;
        }
      }
    } else {
      // we have a direct match
    }

    if (i == currentLine) {
      --i;
    }

    *line = i;
    *column = offset - lines[i];
    m_lastLine = i;
  }
  /**
   * Implements a bisection algorithm / binary search
   * for the offset.
   *
   * Should perform pretty good for any kind of usage, but potentially not
   * as good as positionAtWithMemory for linear access.
   */
  void positionAtBisection(qint64 offset, qint64 *line, qint64 *column)
  {
    if( offset < 0 ) {
      *line = -1;
      *column = -1;
      return;
    } else if ( offset > lines[currentLine - 1] ) {
      *line = currentLine - 1;
      *column = offset - lines[currentLine - 1];
      return;
    }

    qint64 i = currentLine / 2;
    qint64 upperBound = currentLine;
    qint64 lowerBound = 0;

    while ( i > 0 && !(lines[i] <= offset && lines[i + 1] > offset) ) {
      if ( lines[i] < offset ) {
        lowerBound = i;
        i += float(upperBound - lowerBound) / 2;
      } else {
        upperBound = i;
        i -= float(upperBound - lowerBound) / 2;
      }
    }

    *line = i;
    *column = offset - lines[i];
  }

  qint64 tableMaxOffset;

private:
  qint64 m_lastLine;
};

void Benchmarks::initTestCase()
{
  srand ( time(NULL) );
}

void Benchmarks::positionAt()
{
  QFETCH(int, algorithm);
  QFETCH(int, access);

  BenchmarkLocationTable table;
  qint64 line;
  qint64 column;

  switch ( algorithm) {
    case InitialPositionAt: {
      switch ( access ) {
        case LinearAccess: {
          QBENCHMARK {
            for ( qint64 i = 0; i < table.tableMaxOffset; i += 10 ) {
              table.positionAt(i, &line, &column);
            }
          }
          break;
        }
        case RandomAccess: {
          QBENCHMARK {
            for ( qint64 i = 0; i < table.tableMaxOffset; i += 10 ) {
              table.positionAt(rand() % table.tableMaxOffset, &line, &column);
            }
          }
          break;
        }
        default:
          qFatal("unexpected access type");
          break;
      }
      break;
    }
    case RelativePositionAt: {
      switch ( access ) {
        case LinearAccess: {
          QBENCHMARK {
            for ( qint64 i = 0; i < table.tableMaxOffset; i += 10 ) {
              table.positionAtWithMemory(i, &line, &column);
            }
          }
          break;
        }
        case RandomAccess: {
          QBENCHMARK {
            for ( qint64 i = 0; i < table.tableMaxOffset; i += 10 ) {
              table.positionAtWithMemory(rand() % table.tableMaxOffset, &line, &column);
            }
          }
          break;
        }
        default:
          qFatal("unexpected access type");
          break;
      }
      break;
    }
    case BinaryPositionAt: {
      switch ( access ) {
        case LinearAccess: {
          QBENCHMARK {
            for ( qint64 i = 0; i < table.tableMaxOffset; i += 10 ) {
              table.positionAtBisection(i, &line, &column);
            }
          }
          break;
        }
        case RandomAccess: {
          QBENCHMARK {
            for ( qint64 i = 0; i < table.tableMaxOffset; i += 10 ) {
              table.positionAtBisection(rand() % table.tableMaxOffset, &line, &column);
            }
          }
          break;
        }
        default:
          qFatal("unexpected access type");
          break;
      }
      break;
    }
    default:
      qFatal("unexpected algorithm");
      break;
  }
}

void Benchmarks::positionAt_data()
{
  QTest::addColumn<int>("algorithm");
  QTest::addColumn<int>("access");

  QTest::newRow("initial, linear") << (int) InitialPositionAt << (int) LinearAccess;
  QTest::newRow("initial, random") << (int) InitialPositionAt << (int) RandomAccess;
  QTest::newRow("relative, linear") << (int)  RelativePositionAt << (int) LinearAccess;
  QTest::newRow("relative, random") << (int)  RelativePositionAt << (int) RandomAccess;
  QTest::newRow("binary, linear") << (int) BinaryPositionAt << (int) LinearAccess;
  QTest::newRow("binary, random") << (int) BinaryPositionAt << (int) RandomAccess;
}

void Benchmarks::verifyPositionAt()
{
  QFETCH(int, algorithm);
  QFETCH(int, access);

  BenchmarkLocationTable table;
  qint64 oldLine;
  qint64 oldColumn;
  qint64 newLine;
  qint64 newColumn;
  switch ( algorithm) {
    case RelativePositionAt: {
      switch ( access ) {
        case LinearAccess: {
          for ( qint64 i = 0; i < table.tableMaxOffset; i += 10 ) {
            table.positionAt(i, &oldLine, &oldColumn);
            table.positionAtWithMemory(i, &newLine, &newColumn);
            QCOMPARE(newLine, oldLine);
            QCOMPARE(newColumn, oldColumn);
          }
          break;
        }
        case RandomAccess: {
          for ( qint64 i = 0; i < table.tableMaxOffset; i += 10 ) {
            qint64 offset = rand() % table.tableMaxOffset;
            table.positionAt(offset, &oldLine, &oldColumn);
            table.positionAtWithMemory(offset, &newLine, &newColumn);
            QCOMPARE(newLine, oldLine);
            QCOMPARE(newColumn, oldColumn);
          }
          break;
        }
        default:
          qFatal("unexpected access type");
          break;
      }
      break;
    }
    case BinaryPositionAt: {
      switch ( access ) {
        case LinearAccess: {
          for ( qint64 i = 0; i < table.tableMaxOffset; i += 10 ) {
            table.positionAt(i, &oldLine, &oldColumn);
            table.positionAtBisection(i, &newLine, &newColumn);
            QCOMPARE(newLine, oldLine);
            QCOMPARE(newColumn, oldColumn);
          }
          break;
        }
        case RandomAccess: {
          for ( qint64 i = 0; i < table.tableMaxOffset; i += 10 ) {
            qint64 offset = rand() % table.tableMaxOffset;
            table.positionAt(offset, &oldLine, &oldColumn);
            table.positionAtBisection(offset, &newLine, &newColumn);
            QCOMPARE(newLine, oldLine);
            QCOMPARE(newColumn, oldColumn);
          }
          break;
        }
        default:
          qFatal("unexpected access type");
          break;
      }
      break;
    }
    default:
      qFatal("unexpected algorithm");
      break;
  }
}

void Benchmarks::verifyPositionAt_data()
{
  QTest::addColumn<int>("algorithm");
  QTest::addColumn<int>("access");
  QTest::newRow("relative, linear") << (int) RelativePositionAt << (int) LinearAccess;
  QTest::newRow("relative, random") << (int) RelativePositionAt << (int) RandomAccess;
  QTest::newRow("binary, linear") << (int) BinaryPositionAt << (int) LinearAccess;
  QTest::newRow("binary, random") << (int) BinaryPositionAt << (int) RandomAccess;
}

}

QTEST_MAIN(KDevPG::Benchmarks)

#include "benchmarks.moc"
