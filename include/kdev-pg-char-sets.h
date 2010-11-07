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

#ifndef KDEV_PG_CHAR_SETS
#define KDEV_PG_CHAR_SETS

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>

using namespace std;

#include <QString>
#include <QByteArray>
#include <QVector>
#include <QTextStream>
#include <QStringList>

#define NC(...) __VA_ARGS__

namespace KDevPG
{

enum CharEncoding
{
  Ascii = 0,
  Latin1 = 1,
  Ucs2 = 2,
  Ucs4 = 3
};

template<CharEncoding codec>
struct Codec2False
{
  enum { value = false };
};

template<CharEncoding codec>
struct Codec2Int
{
  typedef uchar Result;
};

template<>
struct Codec2Int<Ucs2>
{
  typedef quint16 Result;
};

template<>
struct Codec2Int<Ucs4>
{
  typedef quint32 Result;
};


template<CharEncoding codec>
struct Codec2Container
{
  typedef QByteArray Result;
};

template<>
struct Codec2Container<Ucs2>
{
  typedef QVector<quint16> Result;
};

template<>
struct Codec2Container<Ucs4>
{
  typedef QVector<quint32> Result;
};

template<CharEncoding codec>
struct Codec2Size
{
  static const quint64 value = 256;
};

template<>
struct Codec2Size<Ascii>
{
  static const quint64 value = 128;
};

template<>
struct Codec2Size<Ucs2>
{
  static const quint64 value = 65536; // That is a really large table!!
};

template<>
struct Codec2Size<Ucs4>
{
//   static_assert(false, "Ucs4-tables are too big");
  static const quint64 value = 4294967296ull; // You should never do this!!
};

template<CharEncoding codec>
inline typename Codec2Container<codec>::Result qString2Codec(const QString& str)
{
  static_assert(Codec2False<codec>::value, "Unknown codec");
}

template<>
inline QByteArray qString2Codec<Ascii>(const QString& str)
{
  return str.toAscii();
}

template<>
inline QByteArray qString2Codec<Latin1>(const QString& str)
{
  return str.toLatin1();
}

template<>
inline QVector<quint32> qString2Codec<Ucs4>(const QString& str)
{
  return str.toUcs4();
}

template<>
inline QVector<quint16> qString2Codec<Ucs2>(const QString& str)
{
  QVector<quint16> ret(str.size());
  memcpy(&ret[0], str.utf16(), 2*str.size());
  return ret;
}

class QStringIterator
{
  QString::const_iterator _begin, iter, end;
public:
  typedef quint16 Int;
  typedef quint16 InputInt;
  QStringIterator(const QString& str) : _begin(str.begin()), iter(str.begin()), end(str.end())
  {
    
  }
  quint16 next()
  {
    return iter++->unicode();
  }
  bool hasNext()
  {
    return iter != end;
  }
  ptrdiff_t operator-(const QStringIterator& other) const
  {
    return iter - other.iter;
  }
  InputInt const*& plain()
  {
    return *reinterpret_cast<InputInt const**>(&iter);
  }
  InputInt const*& begin()
  {
    return *reinterpret_cast<InputInt const**>(&_begin);
  }
};

class QByteArrayIterator
{
  QByteArray::const_iterator _begin, iter, end;
public:
  typedef uchar Int;
  typedef uchar InputInt;
  QByteArrayIterator(const QByteArray& str) : _begin(str.begin()), iter(str.begin()), end(str.end())
  {
    
  }
  uchar next()
  {
    return *iter++;
  }
  bool hasNext()
  {
    return iter != end;
  }
  ptrdiff_t operator-(const QByteArrayIterator& other) const
  {
    return iter - other.iter;
  }
  InputInt const*& plain()
  {
    return *reinterpret_cast<InputInt const**>(&iter);
  }  
  InputInt const*& begin()
  {
    return *reinterpret_cast<InputInt const**>(&_begin);
  }
};

class QUtf16ToUcs4Iterator
{
  union { QChar const *ptr; quint16 const *raw; };
  quint16 const *_begin, *end;
public:
  typedef quint32 Int;
  typedef quint16 InputInt;
  QUtf16ToUcs4Iterator(const QString& str) : _begin(str.utf16()), raw(str.utf16()), end(raw + str.size())
  {
    
  }
  quint32 next()
  {
    quint32 ret = ptr->unicode();
    if(QChar::isHighSurrogate(*raw))
      ret = QChar::surrogateToUcs4(ret, *(++raw));
    ++ptr;
    return ret;
  }
  bool hasNext()
  {
    return raw != end;
  }
  ptrdiff_t operator-(const QUtf16ToUcs4Iterator& other) const
  {
    return ptr - other.ptr;
  }
  InputInt const*& plain()
  {
    return raw;
  }
  InputInt const*& begin()
  {
    return *reinterpret_cast<InputInt const**>(&_begin);
  }
};

class QUtf8ToUcs4Iterator
{
  uchar const *_begin, *ptr, *end;
public:
  typedef quint32 Int;
  typedef uchar InputInt;
  QUtf8ToUcs4Iterator(const QByteArray& qba) : _begin(reinterpret_cast<uchar const*>(qba.data())), ptr(_begin), end(ptr + qba.size())
  {
    
  }
  InputInt const*& plain()
  {
    return ptr;
  }
  quint32 next()
  {
    /*
    Algorithm:
    
    Start:
      case chr < 128
        use it directly
      case (chr & 0xe0) == 0xc0
        (chr & 0x1f) -> add next
      case (chr & 0xf0) == 0xe0
        (chr & 0x0f) -> add next two
      case (chr & 0xf8) == 0xf0
        (chr & 0x07) -> add next three
      default
        invalid
        
    Add:
      condition: (next & 0xc0) == 0x80
      ret = (ret << 6) | (nextChr & 0x3f)
      QChar::isUnicodeNonCharacter -> invalid
    */
    
    while(true)
    {
      uchar chr = *ptr;
      if(chr < 128)
      {
        ++ptr;
        return chr;
      }
      quint32 ret;
      if((chr & 0xe0) == 0xc0)
      {
        ret = ((chr & 0x1f) << 6) | ((*++ptr) & 0x3f);
      }
      if((chr & 0xf0) == 0xe0)
      {
        ret = ((chr & 0x0f) << 6) | ((*++ptr) & 0x3f);
        ret = (ret << 6) | ((*++ptr) & 0x3f);
      }
      if((chr & 0xf8) == 0xf0)
      {
        ret = ((chr & 0x0f) << 6) | ((*++ptr) & 0x3f);
        ret = (ret << 6) | ((*++ptr) & 0x3f);
        ret = (ret << 6) | ((*++ptr) & 0x3f);
      }
      ++ptr;
      if((ret & 0xfffe) != 0xfffe && (ret - 0xfdd0U) > 15)
        return ret;
      // ignore the error, jump back :-)
    }
  }
  bool hasNext()
  {
    return ptr != end;
  }
  ptrdiff_t operator-(const QUtf8ToUcs4Iterator& other) const
  {
    return ptr - other.ptr;
  }
  InputInt const*& begin()
  {
    return *reinterpret_cast<InputInt const**>(&_begin);
  }
};


class QUtf8ToUcs2Iterator
{
  uchar const *_begin, *ptr, *end;
public:
  typedef quint16 Int;
  typedef uchar InputInt;
  QUtf8ToUcs2Iterator(const QByteArray& qba) : _begin(reinterpret_cast<uchar const*>(qba.data())), ptr(_begin), end(ptr + qba.size())
  {
    
  }
  InputInt const*& plain()
  {
    return ptr;
  }
  quint16 next()
  { 
    while(true)
    {
      uchar chr = *ptr;
      if(chr < 128)
      {
        ++ptr;
        return chr;
      }
      quint32 ret;
      if((chr & 0xe0) == 0xc0)
      {
        ret = ((chr & 0x1f) << 6) | ((*++ptr) & 0x3f);
      }
      if((chr & 0xf0) == 0xe0)
      {
        ret = ((chr & 0x0f) << 6) | ((*++ptr) & 0x3f);
        ret = (ret << 6) | ((*++ptr) & 0x3f);
      }
      if((chr & 0xf8) == 0xf0)
      {
        ret = ((chr & 0x0f) << 6) | ((*++ptr) & 0x3f);
        ret = (ret << 6) | ((*++ptr) & 0x3f);
        ret = (ret << 6) | ((*++ptr) & 0x3f);
      }
      ++ptr;
      if(ret <= 0xffff && (ret & 0xfffe) != 0xfffe && (ret - 0xfdd0U) > 15)
        return ret;
      // ignore the error, jump back :-)
    }
  }
  bool hasNext()
  {
    return ptr != end;
  }
  ptrdiff_t operator-(const QUtf8ToUcs2Iterator& other) const
  {
    return ptr - other.ptr;
  }
  InputInt const*& begin()
  {
    return *reinterpret_cast<InputInt const**>(&_begin);
  }
};

}

#endif
