/*
    SPDX-FileCopyrightText: 2009 Milian Wolff <mail@milianw.de>

    SPDX-License-Identifier: LGPL-2.0-only
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
