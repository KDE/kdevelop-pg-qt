/*
    SPDX-FileCopyrightText: 2005, 2006 Roberto Raggi <roberto@kdevelop.org>

    SPDX-License-Identifier: LicenseRef-MIT-KDevelop-PG-Qt
*/

#ifndef KDEV_PG_ALLOCATOR_H
#define KDEV_PG_ALLOCATOR_H

#include <QtTypes>

#include <memory>
#include <cstdlib>
#include <cstring>

namespace KDevPG
{

template <class _Tp>
class Allocator
{
public:
  typedef _Tp valueType;
  typedef _Tp* pointer;
  typedef const _Tp* constPointer;
  typedef _Tp& reference;
  typedef const _Tp& constReference;
  typedef ::std::size_t sizeType;
  typedef qint64 differenceType;

  static const sizeType maxBlockCount = sizeType( -1);

  Allocator()
  {
    sBlockIndex = sizeType(-1);
    sCurrentIndex = 0;
    sStorage = nullptr;
    sCurrentBlock = nullptr;
  }

  ~Allocator()
  {
      if (sStorage != nullptr)
      {
        for (sizeType index = 0; index <= sBlockIndex; ++index)
          delete[] sStorage[index];
        std::free(sStorage);
      }
  }
  
  bool contains(void* ptr)
  {
    for(sizeType i = 0; i <= sBlockIndex; ++i)
      if(ptr >= (void*)(sStorage[i]) && ptr < (void*)(sStorage[i] + sBlockSize))
        return true;
    return false;
  }

  pointer address(reference __val)
  {
    return &__val;
  }
  constPointer address(constReference __val) const
  {
    return &__val;
  }

  pointer allocate(sizeType __n, const void* = nullptr)
  {
    const sizeType bytes = __n * sizeof(_Tp);

    if (sCurrentBlock == nullptr
        || sBlockSize < sCurrentIndex + bytes)
      {
        ++sBlockIndex;

        sStorage = reinterpret_cast<char**>
          (std::realloc(sStorage, sizeof(char*) * (1 + sBlockIndex)));

        sCurrentBlock = sStorage[sBlockIndex] = reinterpret_cast<char*>
          (new char[sBlockSize]);

        std::memset(sCurrentBlock, 0, sBlockSize);
        sCurrentIndex = 0;
      }

    pointer p = reinterpret_cast<pointer>
      (sCurrentBlock + sCurrentIndex);

    sCurrentIndex += bytes;

    return p;
  }

  void deallocate(pointer /*__p*/, sizeType /*__n*/)
  {}

  sizeType maxSize() const
  {
    return sizeType( -1) / sizeof(_Tp);
  }

  void contruct(pointer __p, constReference __val)
  {
    new (__p) _Tp(__val);
  }
  void destruct(pointer __p)
  {
    __p->~_Tp();
  }

private:
  template <class _Tp1>
  class Rebind
  {
    typedef Allocator<_Tp1> other;
  };

  template <class _Tp1>
  Allocator(const Allocator<_Tp1> &/*__o*/)
  {}

private:
  static const sizeType sBlockSize;
  sizeType sBlockIndex;
  sizeType sCurrentIndex;
  char *sCurrentBlock;
  char **sStorage;
};

template <class _Tp>
const typename Allocator<_Tp>::sizeType
Allocator<_Tp>::sBlockSize = 1 << 16; // 64K

}

#endif // KDEV_PG_ALLOCATOR_H
