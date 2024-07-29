/*
    SPDX-FileCopyrightText: 2009 Milian Wolff <mail@milianw.de>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#include "benchmarks.h"

#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>

#include <QtAlgorithms>

#include "../include/kdev-pg-location-table.h"

#include <QTest>
#include <QDebug>

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
   * Implements a bisection algorithm / binary search
   * for the offset.
   *
   * Should perform pretty good for any kind of usage, but potentially not
   * as good as positionAtWithMemory for linear access.
   */
  void positionAtQtBisection(qint64 offset, qint64 *line, qint64 *column) const
  {
    if ( offset < 0 ) {
      *line = -1;
      *column = -1;
      return;
    } else if ( offset > lines[currentLine - 1] ) {
      *line = currentLine - 1;
      *column = offset - lines[currentLine - 1];
      return;
    }

    qint64 i = -1;
    // search relative to last line (next line and the one after that)
    if ( m_lastLine + 1 < currentLine && lines[m_lastLine] <= offset ) {
      if ( lines[m_lastLine + 1] > offset ) {
        // last matched line matches again
        i = m_lastLine;
      } else if ( m_lastLine + 2 < currentLine && lines[m_lastLine + 2] > offset ) {
        // next line relative to last matched matches
        i = m_lastLine + 1;
      }
    }
    if ( i == -1 ) {
      // fallback to binary search
      qint64 *it = std::lower_bound(lines, lines + currentLine, offset);
      Q_ASSERT(it != lines + currentLine);

      if (*it != offset) {
        --it;
      }
      *line = it - lines;
      *column = offset - *it;
    } else {
      *line = i;
      *column = offset - lines[i];
    }

    m_lastLine = *line;
  }
  /**
   * Uses old algorithm as written by Roberto Raggi in r687144 (kdevelop-pg/include/kdev-pg-location-table.h)
   */
  void positionAtSTLBisection(qint64 offset, qint64 *line, qint64 *column) const
  {
    if ( offset < 0 ) {
      *line = -1;
      *column = -1;
      return;
    } else if ( offset > lines[currentLine - 1] ) {
      *line = currentLine - 1;
      *column = offset - lines[currentLine - 1];
      return;
    }

    qint64 i = -1;
    // search relative to last line (next line and the one after that)
    if ( m_lastLine + 1 < currentLine && lines[m_lastLine] <= offset ) {
      if ( lines[m_lastLine + 1] > offset ) {
        // last matched line matches again
        i = m_lastLine;
      } else if ( m_lastLine + 2 < currentLine && lines[m_lastLine + 2] > offset ) {
        // next line relative to last matched matches
        i = m_lastLine + 1;
      }
    }
    if ( i == -1 ) {
      // fallback to binary search
      qint64 *it = std::lower_bound(lines, lines + currentLine, offset);
      Q_ASSERT(it != lines + currentLine);

      if (*it != offset) {
        --it;
      }
      *line = it - lines;
      *column = offset - *it;
    } else {
      *line = i;
      *column = offset - lines[i];
    }

    m_lastLine = *line;
  }
  qint64 tableMaxOffset;

private:
  mutable qint64 m_lastLine;
};

void Benchmarks::initTestCase()
{
  srand ( time(nullptr) );
}

void Benchmarks::positionAt()
{
  QFETCH(int, algorithm);
  QFETCH(int, access);

  BenchmarkLocationTable table;
  qint64 line;
  qint64 column;

  switch ( algorithm) {
    case CurrentPositionAt: {
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
    case QtBinaryPositionAt: {
      switch ( access ) {
        case LinearAccess: {
          QBENCHMARK {
            for ( qint64 i = 0; i < table.tableMaxOffset; i += 10 ) {
              table.positionAtQtBisection(i, &line, &column);
            }
          }
          break;
        }
        case RandomAccess: {
          QBENCHMARK {
            for ( qint64 i = 0; i < table.tableMaxOffset; i += 10 ) {
              table.positionAtQtBisection(rand() % table.tableMaxOffset, &line, &column);
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
    case STLBinaryPositionAt: {
      switch ( access ) {
        case LinearAccess: {
          QBENCHMARK {
            for ( qint64 i = 0; i < table.tableMaxOffset; i += 10 ) {
              table.positionAtSTLBisection(i, &line, &column);
            }
          }
          break;
        }
        case RandomAccess: {
          QBENCHMARK {
            for ( qint64 i = 0; i < table.tableMaxOffset; i += 10 ) {
              table.positionAtSTLBisection(rand() % table.tableMaxOffset, &line, &column);
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
  }
}

void Benchmarks::positionAt_data()
{
  QTest::addColumn<int>("algorithm");
  QTest::addColumn<int>("access");

  QTest::newRow("current, linear") << (int) CurrentPositionAt << (int) LinearAccess;
  QTest::newRow("current, random") << (int) CurrentPositionAt << (int) RandomAccess;
  QTest::newRow("qt binary, linear") << (int) QtBinaryPositionAt << (int) LinearAccess;
  QTest::newRow("qt binary, random") << (int) QtBinaryPositionAt << (int) RandomAccess;
  QTest::newRow("stl binary, linear") << (int) STLBinaryPositionAt << (int) LinearAccess;
  QTest::newRow("stl binary, random") << (int) STLBinaryPositionAt << (int) RandomAccess;
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
    case QtBinaryPositionAt: {
      switch ( access ) {
        case LinearAccess: {
          for ( qint64 i = 0; i < table.tableMaxOffset; i += 10 ) {
            table.positionAt(i, &oldLine, &oldColumn);
            table.positionAtQtBisection(i, &newLine, &newColumn);
            QCOMPARE(newLine, oldLine);
            QCOMPARE(newColumn, oldColumn);
          }
          // special cases
          // underflow
          table.positionAt(-5, &oldLine, &oldColumn);
          table.positionAtQtBisection(-5, &newLine, &newColumn);
          QCOMPARE(newLine, oldLine);
          QCOMPARE(newColumn, oldColumn);
          // overflow
          table.positionAt(table.tableMaxOffset + 10, &oldLine, &oldColumn);
          table.positionAtQtBisection(table.tableMaxOffset + 10, &newLine, &newColumn);
          QCOMPARE(newLine, oldLine);
          QCOMPARE(newColumn, oldColumn);
          break;
        }
        case RandomAccess: {
          for ( qint64 i = 0; i < table.tableMaxOffset; i += 10 ) {
            qint64 offset = rand() % table.tableMaxOffset;
            table.positionAt(offset, &oldLine, &oldColumn);
            table.positionAtQtBisection(offset, &newLine, &newColumn);
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
    case STLBinaryPositionAt: {
      switch ( access ) {
        case LinearAccess: {
          for ( qint64 i = 0; i < table.tableMaxOffset; i += 10 ) {
            table.positionAt(i, &oldLine, &oldColumn);
            table.positionAtSTLBisection(i, &newLine, &newColumn);
            QCOMPARE(newLine, oldLine);
            QCOMPARE(newColumn, oldColumn);
          }
          // special cases
          // underflow
          table.positionAt(-5, &oldLine, &oldColumn);
          table.positionAtSTLBisection(-5, &newLine, &newColumn);
          QCOMPARE(newLine, oldLine);
          QCOMPARE(newColumn, oldColumn);
          // overflow
          table.positionAt(table.tableMaxOffset + 10, &oldLine, &oldColumn);
          table.positionAtSTLBisection(table.tableMaxOffset + 10, &newLine, &newColumn);
          QCOMPARE(newLine, oldLine);
          QCOMPARE(newColumn, oldColumn);
          break;
        }
        case RandomAccess: {
          for ( qint64 i = 0; i < table.tableMaxOffset; i += 10 ) {
            qint64 offset = rand() % table.tableMaxOffset;
            table.positionAt(offset, &oldLine, &oldColumn);
            table.positionAtSTLBisection(offset, &newLine, &newColumn);
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
  QTest::newRow("qt binary, linear") << (int) QtBinaryPositionAt << (int) LinearAccess;
  QTest::newRow("qt binary, random") << (int) QtBinaryPositionAt << (int) RandomAccess;
  QTest::newRow("stl binary, linear") << (int) STLBinaryPositionAt << (int) LinearAccess;
  QTest::newRow("stl binary, random") << (int) STLBinaryPositionAt << (int) RandomAccess;
}

}

QTEST_MAIN(KDevPG::Benchmarks)

#include "moc_benchmarks.cpp"
