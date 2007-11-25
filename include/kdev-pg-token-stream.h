/*
  This file is part of kdev-pg
  Copyright 2005, 2006 Roberto Raggi <roberto@kdevelop.org>

  Permission to use, copy, modify, distribute, and sell this software and its
  documentation for any purpose is hereby granted without fee, provided that
  the above copyright notice appear in all copies and that both that
  copyright notice and this permission notice appear in supporting
  documentation.

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
  KDEVELOP TEAM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
  AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

//krazy:exclude-all=inline
#ifndef KDEV_PG_TOKEN_STREAM_H
#define KDEV_PG_TOKEN_STREAM_H

#include <QtCore/QtGlobal>

#include "kdev-pg-location-table.h"

namespace KDevPG
{

class TokenStream
{
public:
  class Token
  {
  public:
    int kind;
    qint64 begin;
    qint64 end;
  };

public:
  TokenStream()
    : mTokenBuffer(0),
      mTokenBufferSize(0),
      mIndex(0),
      mTokenCount(0),
      mLocationTable(0)
  {
    reset();
  }

  ~TokenStream()
  {
    if (mTokenBuffer)
      ::free(mTokenBuffer);
    if (mLocationTable)
      delete mLocationTable;
  }

  inline void reset()
  {
    mIndex = 0;
    mTokenCount = 0;
  }

  inline qint64 size() const
  {
    return mTokenCount;
  }

  inline qint64 index() const
  {
    return mIndex;
  }

  inline qint64 yytokenIndex() const
  {
    if( mIndex )
      return mIndex - 1;
    return mIndex;
  }

  inline void rewind(qint64 index)
  {
    mIndex = index;
  }

  inline Token const &token(qint64 index) const
  {
    return mTokenBuffer[index];
  }

  inline Token &token(qint64 index)
  {
    return mTokenBuffer[index];
  }

  inline int nextToken()
  {
    return mTokenBuffer[mIndex++].kind;
  }

  inline Token &next()
  {
    if (mTokenCount == mTokenBufferSize)
      {
        if (mTokenBufferSize == 0)
          mTokenBufferSize = 1024;

        mTokenBufferSize <<= 2;

        mTokenBuffer = reinterpret_cast<Token*>
          (::realloc(mTokenBuffer, mTokenBufferSize * sizeof(Token)));
      }

    return mTokenBuffer[mTokenCount++];
  }

  inline LocationTable *location_table()
  {
    if (!mLocationTable)
      mLocationTable = new LocationTable();

    return mLocationTable;
  }

  inline void startPosition(qint64 index, size_t *line, size_t *column)
  {
    if (!mLocationTable)
      {
        *line = 0; *column = 0;
      }
    else
      mLocationTable->positionAt(token(index).begin, line, column);
  }

  inline void endPosition(qint64 index, size_t *line, size_t *column)
  {
    if (!mLocationTable)
      {
        *line = 0; *column = 0;
      }
    else
      mLocationTable->positionAt(token(index).end, line, column);
  }

private:
  Token *mTokenBuffer;
  qint64 mTokenBufferSize;
  qint64 mIndex;
  qint64 mTokenCount;
  LocationTable *mLocationTable;

private:
  TokenStream(TokenStream const &other);
  void operator = (TokenStream const &other);
};

}

#endif // KDEV_PG_TOKEN_STREAM_H

