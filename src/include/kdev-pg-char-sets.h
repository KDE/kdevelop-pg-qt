/*
    SPDX-FileCopyrightText: 2010 Jonathan Schmidt-Dominé <devel@the-user.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

//krazy:excludeall=inline
#ifndef KDEV_PG_CHAR_SETS
#define KDEV_PG_CHAR_SETS

#include <QByteArray>
#include <QList>
#include <QString>
#include <QTextStream>

#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>

/**
 * @FILE
 * This file implements various iterator-classes providing character-set specific input streams.
 * Each iterator-class has these members:
 * @li Int: The type of the values returned by the stream
 * @li InputInt: Type of the values in the underlying representation
 * @li PlainIterator: InputInt*-like type used to reference underlying positions
 * @li next(): returns the next value and advances the stream position
 * @li hasNext(): checks if there are elements left
 * @li plain(): returns the PlainIterator for the next position
 * @li operator-(other): distance in the underlying representation between two of the iterators
 * @li begin: returns the PlainIterator at the beginning of the stream
 * @todo implement iterators for QIODevices, FILE and STL-streams, would need more abstraction: differentiate between input handling and decoding
 */

namespace KDevPG
{

enum CharEncoding
{
  Ascii = 0,
  Latin1 = 1,
  Utf8 = 2,
  Utf16 = 3,
  Ucs2 = 4,
  Ucs4 = 5
};

template<CharEncoding codec>
struct Codec2False
{
  enum { value = false };
};

// use a bit more space than necessary, so we will be able to use ranges excluding the end
template<CharEncoding codec>
struct Codec2Int
{
  typedef uchar Result;
};

template<>
struct Codec2Int<Latin1>
{
  typedef quint16 Result;
};

template<>
struct Codec2Int<Utf8>
{
  typedef quint16 Result;
};

template<>
struct Codec2Int<Ucs2>
{
  typedef quint32 Result;
};

template<>
struct Codec2Int<Utf16>
{
  typedef quint32 Result;
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
  typedef QList<quint16> Result;
};

template<>
struct Codec2Container<Utf16>
{
  typedef QList<quint16> Result;
};

template<>
struct Codec2Container<Ucs4>
{
  typedef QList<quint32> Result;
};

template<CharEncoding codec>
struct Codec2Size
{
  enum { value = 256 };
};

template<>
struct Codec2Size<Ascii>
{
  enum { value = 128 };
};

template<>
struct Codec2Size<Ucs2>
{
  enum { value = 65536 }; // That is a really large table!!
};

template<>
struct Codec2Size<Utf16>
{
  enum { value = 65536 }; // That is a really large table!!
};

template<>
struct Codec2Size<Ucs4>
{
  enum { value = 0x110000 }; // You should not do this!!
};

template<CharEncoding codec>
inline typename Codec2Container<codec>::Result qString2Codec(const QString& /*str*/)
{
  static_assert(Codec2False<codec>::value, "Unknown codec");
}

/// @todo check for invalid characters
template<>
inline QByteArray qString2Codec<Ascii>(const QString& str)
{
  /// FIXME: in Qt5 there is no Ascii anymore, and in Qt4 it also was something different
  /// as it was configurable. In Russia, e.g. Ascii was something different than in Europe etc. pp...
  /// See: http://qt-project.org/doc/qt-4.8/qstring.html#toAscii
  /// All of this code here should probably be dropped and replaced by QTextCoded or similar
  return str.toLatin1();
}

template<>
inline QByteArray qString2Codec<Latin1>(const QString& str)
{
  return str.toLatin1();
}

template<>
inline QByteArray qString2Codec<Utf8>(const QString& str)
{
  return str.toUtf8();
}

template<>
inline QList<quint32> qString2Codec<Ucs4>(const QString& str)
{
  return str.toUcs4();
}

template<>
inline QList<quint16> qString2Codec<Ucs2>(const QString& str)
{
  QList<quint16> ret(str.size());
  memcpy(&ret[0], str.utf16(), 2*str.size());
  return ret;
}

template<>
inline QList<quint16> qString2Codec<Utf16>(const QString& str)
{
  QList<quint16> ret(str.size());
  memcpy(&ret[0], str.utf16(), 2*str.size());
  return ret;
}

class QStringIterator
{
  QString::const_iterator _begin, iter, end;
public:
  typedef quint16 Int;
  typedef quint16 InputInt;
  typedef QString::const_iterator PlainIterator;
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
  PlainIterator plain()
  {
    return iter;
  }
  PlainIterator begin()
  {
    return _begin;
  }
};

template<typename String>
class ByteStringIterator
{
  typename String::const_iterator _begin, iter, end;
public:
  typedef uchar Int;
  typedef uchar InputInt;
  typedef typename String::const_iterator PlainIterator;
  ByteStringIterator(const String& str) : _begin(str.begin()), iter(str.begin()), end(str.end())
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
  ptrdiff_t operator-(const ByteStringIterator& other) const
  {
    return iter - other.iter;
  }
  PlainIterator& plain()
  {
    return iter;
  }  
  PlainIterator& begin()
  {
    return _begin;
  }
};

typedef ByteStringIterator<QByteArray> QByteArrayIterator;
typedef ByteStringIterator<std::string> StdStringIterator;

class QUtf16ToUcs4Iterator
{
  union { QChar const *ptr; quint16 const *raw; };
  quint16 const *_begin, *end;
public:
  typedef quint32 Int;
  typedef quint16 InputInt;
  typedef InputInt const* PlainIterator;
  QUtf16ToUcs4Iterator(const QString& str) : raw(str.utf16()), _begin(str.utf16()), end(raw + str.size())
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
  PlainIterator& plain()
  {
    return raw;
  }
  PlainIterator& begin()
  {
    return _begin;
  }
};

template<typename String>
class Utf8ToUcs4Iterator
{
public:
  typedef typename String::const_iterator PlainIterator;
private:
  PlainIterator _begin, ptr, end;
public:
  typedef quint32 Int;
  typedef uchar InputInt;
  Utf8ToUcs4Iterator(const String& str) : _begin(str.begin()), ptr(_begin), end(ptr + str.size())
  {
    
  }
  PlainIterator& plain()
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
      retry:
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
      else if((chr & 0xf0) == 0xe0)
      {
        ret = ((chr & 0x0f) << 6) | ((*++ptr) & 0x3f);
        ret = (ret << 6) | ((*++ptr) & 0x3f);
      }
      else if((chr & 0xf8) == 0xf0)
      {
        ret = ((chr & 0x0f) << 6) | ((*++ptr) & 0x3f);
        ret = (ret << 6) | ((*++ptr) & 0x3f);
        ret = (ret << 6) | ((*++ptr) & 0x3f);
      }
      else
      {
        ++ptr;
        goto retry;
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
  ptrdiff_t operator-(const String& other) const
  {
    return ptr - other.ptr;
  }
  PlainIterator& begin()
  {
    return _begin;
  }
};

typedef Utf8ToUcs4Iterator<QByteArray> QUtf8ToUcs4Iterator;
typedef Utf8ToUcs4Iterator<std::string> StdStringUtf8ToUcs4Iterator;

class QUtf8ToUcs2Iterator
{
  uchar const *_begin, *ptr, *end;
public:
  typedef quint16 Int;
  typedef uchar InputInt;
  typedef InputInt const* PlainIterator;
  QUtf8ToUcs2Iterator(const QByteArray& qba) : _begin(reinterpret_cast<uchar const*>(qba.data())), ptr(_begin), end(ptr + qba.size())
  {
    
  }
  PlainIterator& plain()
  {
    return ptr;
  }
  quint16 next()
  { 
    while(true)
    {
      retry:
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
      else if((chr & 0xf0) == 0xe0)
      {
        ret = ((chr & 0x0f) << 6) | ((*++ptr) & 0x3f);
        ret = (ret << 6) | ((*++ptr) & 0x3f);
      }
      else if((chr & 0xf8) == 0xf0)
      {
        ret = ((chr & 0x0f) << 6) | ((*++ptr) & 0x3f);
        ret = (ret << 6) | ((*++ptr) & 0x3f);
        ret = (ret << 6) | ((*++ptr) & 0x3f);
      }
      else
      {
        ++ptr;
        goto retry;
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
  PlainIterator& begin()
  {
    return _begin;
  }
};

class QUtf8ToUtf16Iterator
{
  uchar const *_begin, *ptr, *end;
  quint16 surrogate;
public:
  typedef quint16 Int;
  typedef uchar InputInt;
  typedef InputInt const* PlainIterator;
  QUtf8ToUtf16Iterator(const QByteArray& qba) : _begin(reinterpret_cast<uchar const*>(qba.data())), ptr(_begin), end(ptr + qba.size()), surrogate(0)
  {
    
  }
  PlainIterator& plain()
  {
    return ptr;
  }
  quint16 next()
  {
    if(surrogate != 0)
    {
      Int tmp = surrogate;
      surrogate = 0;
      return tmp;
    }
    while(true)
    {
      retry:
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
      else if((chr & 0xf0) == 0xe0)
      {
        ret = ((chr & 0x0f) << 6) | ((*++ptr) & 0x3f);
        ret = (ret << 6) | ((*++ptr) & 0x3f);
      }
      else if((chr & 0xf8) == 0xf0)
      {
        ret = ((chr & 0x0f) << 6) | ((*++ptr) & 0x3f);
        ret = (ret << 6) | ((*++ptr) & 0x3f);
        ret = (ret << 6) | ((*++ptr) & 0x3f);
      }
      else
      {
        ++ptr;
        goto retry;
      }
      ++ptr;
      if(ret <= 0xffff)
      {
        if((ret & 0xfffe) != 0xfffe && (ret - 0xfdd0U) > 15)
          return ret;
        // ignoe the error ;)
      }
      else
      {
        surrogate = QChar::lowSurrogate(ret);
        return QChar::highSurrogate(ret);
      }
    }
  }
  bool hasNext()
  {
    return ptr != end;
  }
  ptrdiff_t operator-(const QUtf8ToUtf16Iterator& other) const
  {
    return ptr - other.ptr;
  }
  PlainIterator& begin()
  {
    return _begin;
  }
};

class QUtf8ToAsciiIterator
{
  uchar const *_begin, *ptr, *end;
public:
  typedef uchar Int;
  typedef uchar InputInt;
  typedef InputInt const* PlainIterator;
  QUtf8ToAsciiIterator(const QByteArray& qba) : _begin(reinterpret_cast<uchar const*>(qba.data())), ptr(_begin), end(ptr + qba.size())
  {
    
  }
  PlainIterator& plain()
  {
    return ptr;
  }
  Int next()
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
      // ignore the error, jump back :-)
      // TODO: error handling?
    }
  }
  bool hasNext()
  {
    return ptr != end;
  }
  ptrdiff_t operator-(const QUtf8ToAsciiIterator& other) const
  {
    return ptr - other.ptr;
  }
  PlainIterator& begin()
  {
    return _begin;
  }
};

template<CharEncoding codec>
struct Codec2FromUtf8Iterator
{
  typedef QByteArrayIterator Result;
};

template<>
struct Codec2FromUtf8Iterator<Ascii>
{
  typedef QUtf8ToAsciiIterator Result;
};

template<>
struct Codec2FromUtf8Iterator<Ucs2>
{
  typedef QUtf8ToUcs2Iterator Result;
};

template<>
struct Codec2FromUtf8Iterator<Utf16>
{
  typedef QUtf8ToUtf16Iterator Result;
};

template<>
struct Codec2FromUtf8Iterator<Ucs4>
{
  typedef QUtf8ToUcs4Iterator Result;
};

}

#endif
