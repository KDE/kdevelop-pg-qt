/*
    SPDX-FileCopyrightText: 2010 Jonathan Schmidt-Dominé <devel@the-user.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEV_PG_BIT_ARRAY
#define KDEV_PG_BIT_ARRAY

#include <iostream>
#include <cstring>
#include <unordered_set>

class BitArray
{
  typedef std::size_t size_t;
  size_t mSize;
  union
  {
    unsigned char *mByte;
    size_t *mWord;
  };
  friend struct ::std::hash<BitArray>;
  enum { BPW = sizeof(size_t) * 8 }; // Bits per word
  static inline size_t words(size_t n)
  {
    return (n + BPW - 1) / BPW;
  }
  inline size_t words() const
  {
    return words(mSize);
  }
  static inline size_t bytes(size_t n)
  {
    return words(n) * sizeof(size_t);
  }
  inline size_t bytes() const
  {
    return bytes(mSize);
  }
  inline void setZerosAtEnd()
  {
    mWord[words() - 1] &= ((~size_t(0)) << (BPW - mSize % BPW));
  }
public:
  struct BitRef
  {
    unsigned char &byte;
    unsigned char bit: 3;
    inline BitRef(unsigned char &byte, unsigned char bit) : byte(byte), bit(bit)
    {}
    inline operator bool() const
    {
      return (byte & (1 << bit)) == (1 << bit);
    }
    inline BitRef& operator=(bool val)
    {
      if(val)
        byte |= (1 << bit);
      else
        byte &= ~(1 << bit);
      return *this;
    }
    inline BitRef& operator=(const BitRef& val)
    {
      return *this = (bool)val;
    }
  };
  inline BitArray(size_t size) : mSize(size), mByte(reinterpret_cast<unsigned char*>(malloc(bytes())))
  {
    memset(mByte, 0, bytes());
    setZerosAtEnd();
  }
  inline BitArray() : mSize(0), mByte((unsigned char*)malloc(0))
  {
  }
  inline BitArray(const BitArray& o) : mSize(o.mSize), mByte(reinterpret_cast<unsigned char*>(malloc(bytes())))
  {
    for(size_t *i = mWord, *j = o.mWord; i != mWord + words(); ++i, ++j)
      *i = *j;
  }
  inline bool operator<(const BitArray& o) const
  {
    if(size() < o.size())
      return true;
    if(o.size() < size())
      return false;
    if(size() == 0)
      return false;
    size_t *i, *j;
    for(i = mWord, j = o.mWord; i != mWord + words(); ++i, ++j)
    {
      if(*i < *j)
        return true;
      if(*j < *i)
        return false;
    }
    return false;
  }
  inline ~BitArray()
  {
    free(mByte);
  }
  inline bool operator==(const BitArray& o) const
  {
    if(o.size() != size())
      return false;
    if(size() == 0)
      return true;
    size_t *i, *j;
    for(i = mWord, j = o.mWord; i != mWord + words(); ++i, ++j)
    {
      if(*i != *j)
        return false;
    }
    return true;
  }
  inline BitArray& operator=(const BitArray& o)
  {
    if(&o != this)
    {
      this->~BitArray();
      new (this)BitArray(o);
    }
    return *this;
  }
  inline bool operator[](size_t x) const
  {
    if(x > size())
      std::cerr << "out of bounds" << std::endl;
    return (mByte[x >> 3] & (1 << (x & 7))) == (1 << (x & 7));
  }
  inline BitRef operator[](size_t x)
  {
    if(x > size())
      std::cerr << "out of bounds" << std::endl;
    return BitRef(mByte[x >> 3], x & 7);
  }
  inline void resize(size_t size)
  {
    mByte = reinterpret_cast<unsigned char*>(realloc(mByte, bytes(size)));
    if(size > mSize)
    {
      memset(mWord + words(), 0, bytes(size) - bytes());
    }
    mSize = size;
  }
  inline size_t size() const
  {
    return mSize;
  }
};

namespace std
{
  template<> struct hash<BitArray>
  {
    inline size_t operator()(const BitArray &x) const
    {
      size_t ret = 0;
      for(size_t *i = x.mWord; i != x.mWord + x.words(); ++i)
      {
        ret ^= *i;
        ret = (ret >> (sizeof(size_t)*8 - 17)) | (ret << 17);
      }
      return ret;
    }
  };
}

std::ostream& operator<<(std::ostream &o, const BitArray &a)
{
  for(size_t i = 0; i != a.size(); ++i)
  {
    o << (int)a[i];
  }
  return o;
}

#endif
