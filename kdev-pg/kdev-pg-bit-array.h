/* This file is part of kdev-pg-qt
   Copyright (C) 2010 Jonathan Schmidt-Dominé <devel@the-user.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include <iostream>
#include <cstring>
#include <tr1/unordered_set>

using namespace std;
using namespace tr1;

class BitArray
{
  size_t mSize;
  unsigned char *mData;
  friend struct ::std::tr1::hash<BitArray>;
public:
  struct BitRef
  {
    unsigned char &byte;
    unsigned char bit: 3;
    inline BitRef(unsigned char &byte, unsigned char bit) : byte(byte), bit(bit)
    {}
    inline operator bool() const
    {
      return byte & (1 << bit);
    }
    inline BitRef& operator=(bool val)
    {
      if(val)
        byte |= (1 << bit);
      else
        byte &= ~(1 << bit);
      return *this;
    }
    inline BitRef& operator=(BitRef val)
    {
      return *this = (bool)val;
    }
  };
  inline BitArray(size_t size, bool val = false) : mSize(size), mData(reinterpret_cast<unsigned char*>(malloc((size + 8 * sizeof(size_t) - 1) / 8)))
  {
//     if(val)
//     {
//       for(size_t *i = reinterpret_cast<size_t*>(mData); i != reinterpret_cast<size_t*>(mData) + (mSize + 8 * sizeof(size_t) - 1) / 8 / sizeof(size_t); ++i)
//         *i = ~(size_t(0));
//     }
//     else
//     {
//       for(size_t *i = reinterpret_cast<size_t*>(mData); i != reinterpret_cast<size_t*>(mData) + (mSize + 8 * sizeof(size_t) - 1) / 8 / sizeof(size_t); ++i)
//         *i = 0;
//     }
    memset(mData, (val ? (~(size_t(0))) : 0), (size + 8 * sizeof(size_t) - 1) / 8);
  }
  inline BitArray() : mSize(0), mData((unsigned char*)malloc(0))
  {
  }
  inline BitArray(const BitArray& o) : mSize(o.mSize), mData(reinterpret_cast<unsigned char*>(malloc((mSize + 8 * sizeof(size_t) - 1) / 8)))
  {
    for(size_t *i = reinterpret_cast<size_t*>(mData), *j = reinterpret_cast<size_t*>(o.mData); i != reinterpret_cast<size_t*>(mData) + (mSize + 8 * sizeof(size_t) - 1) / 8 / sizeof(size_t); ++i, ++j)
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
    for(i = reinterpret_cast<size_t*>(mData), j = reinterpret_cast<size_t*>(o.mData); i != reinterpret_cast<size_t*>(mData) + (mSize + 8 * sizeof(size_t) - 1) / 8 / sizeof(size_t) - 1; ++i, ++j)
    {
      if(*i < *j)
        return true;
      if(*j < *i)
        return false;
    }
    return (*i & (1 << (8 * sizeof(size_t) - size() % (8 * sizeof(size_t))))) < (*j & (1 << (8 * sizeof(size_t) - size() % (8 * sizeof(size_t)))));
  }
  inline ~BitArray()
  {
    free(mData);
  }
  inline bool operator==(const BitArray& o) const
  {
    if(o.size() != size())
      return false;
    if(size() == 0)
      return true;
    size_t *i, *j;
    for(i = reinterpret_cast<size_t*>(mData), j = reinterpret_cast<size_t*>(o.mData); i != reinterpret_cast<size_t*>(mData) + (mSize + 8 * sizeof(size_t) - 1) / 8 / sizeof(size_t) - 1; ++i, ++j)
      if(*i != *j)
        return false;
    return (*i & (1 << (8 * sizeof(size_t) - size() % (8 * sizeof(size_t))))) == (*j & (1 << (8 * sizeof(size_t) - size() % (8 * sizeof(size_t)))));
  }
  inline BitArray& operator[](const BitArray& o)
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
    return size_t(mData[x >> 3]) & (1 << (x & 7));
  }
  inline BitRef operator[](size_t x)
  {
    return BitRef(mData[x >> 3], x & 7);
  }
  inline void resize(size_t size)
  {
    mData = reinterpret_cast<unsigned char*>(realloc(mData, size / 8));
    if(size > mSize)
    {
      memset(reinterpret_cast<size_t*>(mData) + (mSize + 8 * sizeof(size_t) - 1) / 8 / sizeof(size_t), 0,  (size + 8 * sizeof(size_t) - 1) / 8 / sizeof(size_t) - (mSize + 8 * sizeof(size_t) - 1) / 8 / sizeof(size_t));
      mData[(mSize - 1) / 8 / sizeof(size_t)] &= ((~size_t(0)) << (sizeof(size_t) * 8 - mSize % (sizeof(size_t) * 8)));
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
  namespace tr1
  {
    template<> struct hash<BitArray>
    {
      inline size_t operator()(const BitArray &x) const
      {
        size_t ret = 0;
        for(size_t *i = reinterpret_cast<size_t*>(x.mData); i != reinterpret_cast<size_t*>(x.mData) + (x.mSize + 8 * sizeof(size_t) - 1) / 8 / sizeof(size_t); ++i)
          ret ^= *i;
        return ret;
      }
    };
  }
}


/*int main()
{
  BitArray x(380);
  x[341] = x[4] = true;
  cout << x[3] << x[4] << x[341] << endl;
  BitArray y(x);
  cout << y[3] << y[4] << y[341] << endl;
  cout << (x == y) <<  (x < y) << (y < x) << endl;
  BitArray z(48, true);
  z[45] = z[47] = false;
  cout << z[45] << z[46] << z[47] << endl;
  z.resize(200);
  cout << z[45] << z[46] << z[47] << endl << z[48] << z[49] << endl;
//   z.resize(500);
//   cout << z[379] << endl;
}*/

