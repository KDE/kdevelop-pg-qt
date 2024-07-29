/*
    SPDX-FileCopyrightText: 2005, 2006 Roberto Raggi <roberto@kdevelop.org>

    SPDX-License-Identifier: LicenseRef-MIT-KDevelop-PG-Qt
*/

//krazy:excludeall=inline
#ifndef KDEV_PG_TOKEN_STREAM_H
#define KDEV_PG_TOKEN_STREAM_H

#include "kdev-pg-location-table.h"

#include <vector>

/* T& front() ✓
 * T& back() ✓
 * T& curr()                →   ?
 * 
 * T& advance()             →   read()
 * qint64 tokenIndex()      →   delete
 * qint64 index() ✓
 * T& next()                →   push(), push(Token)
 * int nextToken()          →   delete
 * T& token(index)          →   at()
 * ? more
 * 
 * rewind(index) ✓
 * qint64 size() ✓
 * reset() ✓
 * free()                   →   clear()
 * 
 * locationTable() ✓
 * 
 * startPosition(index, line, column) ✓
 * endPosition(index, line, column) ✓
 */

namespace KDevPG
{

class Token {
  public:
    int kind;
    qint64 begin;
    qint64 end;
};

/**
 * Stores a stream of tokens and has an associated location table.
 * You can add tokens and traverse them (Java-style unidirectional iterator with random access).
 * Internal representation similar to a std::vector (capacity gets multiplied if it get exceeded).
 * @todo Fix inconsistencies in naming: advance vs. next vs. nextToken, token vs. nextToken
 */
template<class T>
class TokenStreamBase
{
public:
  typedef T Token;
  TokenStreamBase()
    : mIndex(0),
      mLocationTable(nullptr)
  {
    reset();
  }

  ~TokenStreamBase()
  {
    if (mLocationTable)
      delete mLocationTable;
  }
  
  /**
   * Clears the stream.
   * @note It does not free the reserved memory, because usually as much memory is required as before.
   * @note It will not affect the location table.
   * @sa free
   */
  inline void reset()
  {
    mIndex = 0;
  }
  
  /**
   * Clears the stream and frees all memory.
   * @note It will not affect the location table.
   * @sa reset
   */
  inline void clear()
  {
    mIndex = 0;
    mTokenBuffer.clear();
  }
  
  /**
   * The number of tokens in the stream.
   */
  inline qint64 size() const
  {
    return mTokenBuffer.size();
  }
  
  /**
   * The current position in the stream.
   */
  inline qint64 index() const
  {
    return mIndex;
  }
  
  /**
   * Sets the position in the stream.
   * All tokens will be unaffected.
   */
  inline void rewind(qint64 index)
  {
    Q_ASSERT(0 <= index && index <= size());
    mIndex = index;
  }
  
  /**
   * Returns the token at the specified position in the stream.
   */
  inline T const &at(qint64 index) const
  {
    Q_ASSERT(0 <= index && index < size());
    return mTokenBuffer[index];
  }
  
  /**
   * Returns the token at the specified position in the stream.
   */
  inline T &at(qint64 index)
  {
    Q_ASSERT(0 <= index && index < size());
    return mTokenBuffer[index];
  }
  
  /**
   * Pushes a new token to the stream.
   * @return The new default-initialized token (reference)
   */
  inline T &push()
  {
    mTokenBuffer.push_back({});
    return mTokenBuffer.back();
  }
  
  /**
   * Pushes the specified token to the stream.
   * @return Reference to the inserted token
   */
  inline T &push(const T& t)
  {
    mTokenBuffer.push_back(t);
    return mTokenBuffer.back();
  }
  
  /**
   * Advances and returns the token at the current position.
   */
  inline T &read()
  {
    if(mIndex == size())
    {
      push().kind = 1000;
    }
    return mTokenBuffer[mIndex++];
  }
  
  /**
   * Current token in the stream.
   */
  inline T &curr()
  {
    Q_ASSERT(mIndex < size());
    return mTokenBuffer[mIndex];
  }
  
  /**
   * Last token in the stream.
   */
  inline T &back()
  {
    Q_ASSERT(!mTokenBuffer.empty());
    return mTokenBuffer.back();
  }
  
  /**
   * First token in the stream.
   */
  inline T &front()
  {
    Q_ASSERT(!mTokenBuffer.empty());
    return mTokenBuffer.front();
  }
  
  /**
   * @return The associated location table.
   */
  inline LocationTable *locationTable()
  {
    if (!mLocationTable)
      mLocationTable = new LocationTable();

    return mLocationTable;
  }
  
  /**
   * Coordinates of the beginning of the first token.
   */
  inline void startPosition(qint64 index, qint64 *line, qint64 *column)
  {
    if (!mLocationTable)
      {
        *line = 0; *column = 0;
      }
    else
      mLocationTable->positionAt(at(index).begin, line, column);
  }
  
  /**
   * Coordinate at the end of all tokens.
   */
  inline void endPosition(qint64 index, qint64 *line, qint64 *column)
  {
    if (!mLocationTable)
      {
        *line = 0; *column = 0;
      }
    else
      mLocationTable->positionAt(at(index).end, line, column);
  }

private:
  std::vector<T> mTokenBuffer;
  qint64 mIndex;
  LocationTable *mLocationTable;

private:
  TokenStreamBase(TokenStreamBase const &other);
  void operator = (TokenStreamBase const &other);
};


class TokenStream : public TokenStreamBase<Token>
{
};


}

#endif // KDEV_PG_TOKEN_STREAM_H

