/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg.h"
#include "kdev-pg-allocator.h"
#include "kdev-pg-memory-pool.h"

namespace KDevPG
{
QFile file;
KDevPG::Allocator<char> globalMemoryPool;
KDevPG::World globalSystem;

}
