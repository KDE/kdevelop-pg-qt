/*
    SPDX-FileCopyrightText: 2005, 2006 Roberto Raggi <roberto@kdevelop.org>

    SPDX-License-Identifier: LicenseRef-MIT-KDevelop-PG-Qt
*/

//krazy:excludeall=inline
#ifndef KDEV_PG_MEMORY_POOL
#define KDEV_PG_MEMORY_POOL

#include <QtTypes>

#include <cstring>
#include <cstdlib>

namespace KDevPG
{

class BlockType
{
public:
  qint64 blockSize;
  BlockType *chain;
  char *data;
  char *ptr;
  char *end;

  inline void init(int block_size = 256)
  {
    blockSize = block_size;
    chain = nullptr;
    data = (char*) malloc(blockSize);
    ptr = data;
    end = data + block_size;
  }

  inline void init0(int block_size = 256)
  {
    init(block_size);
    memset(data, '\0', block_size);
  }

  inline void destroy()
  {
    if (chain) {
      chain->destroy();
      free(chain);
    }

    free(data);
  }

  inline void *allocate(size_t size, BlockType **right_most)
  {
    if (end < ptr + size) {
      //            assert( size < block_size );

      if (!chain) {
        chain = (BlockType*) malloc(sizeof(BlockType));
        chain->init0(blockSize << 2);
      }

      return chain->allocate(size, right_most);
    }

    char *r = ptr;
    ptr += size;

    if (right_most)
      *right_most = this;

    return r;
  }

};

class MemoryPool
{
public:
  BlockType blk;
  BlockType *rightMost;

  inline MemoryPool() { blk.init0(); rightMost = &blk; }
  inline ~MemoryPool() { blk.destroy(); }

  inline void *allocate(size_t size)
  { return rightMost->allocate(size, &rightMost); }
};

}

#endif
