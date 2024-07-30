/*
    SPDX-FileCopyrightText: 2009 Milian Wolff <mail@milianw.de>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "testmemorypool.h"

#include <cstdlib>
#include <QTest>
#include <QDebug>

#include <kdev-pg-memory-pool.h>

namespace KDevPG
{

void TestMemoryPool::initTestCase()
{
}

void TestMemoryPool::bigAlloc()
{
  MemoryPool pool;

  size_t chunkSize = 256;
  unsigned int chunks = 10000;

  for ( unsigned int i = 0; i < chunks; ++i ) {
    pool.allocate(chunkSize);
  }
}

}

QTEST_MAIN(KDevPG::TestMemoryPool)

#include "moc_testmemorypool.cpp"
