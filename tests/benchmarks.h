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
#ifndef BENCHMARKS_H
#define BENCHMARKS_H

#include <QObject>

namespace KDevPG
{
class Benchmarks : public QObject
{
    Q_OBJECT

public Q_SLOTS:
    void initTestCase();

private Q_SLOTS:
    /// benchmarks on of the PositionAtAlgorithms
    void positionAt();
    void positionAt_data();
    /// verifies the new PositionAtAlgorithms by comparing to
    /// the initial algorithm
    void verifyPositionAt();
    void verifyPositionAt_data();

private:
    enum PositionAtAlgorithms {
      CurrentPositionAt,
      QtBinaryPositionAt,
      STLBinaryPositionAt
    };
    enum AccessType {
      LinearAccess,
      RandomAccess
    };
};

}

#endif // BENCHMARKS_H
