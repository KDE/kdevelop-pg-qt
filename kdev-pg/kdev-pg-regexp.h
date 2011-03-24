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

#ifndef KDEV_PG_REGEXP
#define KDEV_PG_REGEXP

#include <kdev-pg-char-sets.h>

#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <stack>
#include <string>
#include <cassert>
#include <vector>

#include <QBitArray>

#include <QString>
#include <QFile>
#include <QStringList>

namespace KDevPG
{
  
template<typename T> class DFA;
template<typename T> class NFA;
template<CharEncoding enc> class SeqCharSet;
template<CharEncoding enc> class TableCharSet;

// General

/**
 * Deterministic finite automaton
 */
class GDFA
{
  union
  {
    DFA<SeqCharSet<Ascii> > *s0;
    DFA<SeqCharSet<Latin1> > *s1;
    DFA<SeqCharSet<Ucs2> > *s2;
    DFA<SeqCharSet<Ucs4> > *s3;
    DFA<TableCharSet<Ascii> > *t0;
    DFA<TableCharSet<Latin1> > *t1;
    DFA<TableCharSet<Ucs2> > *t2;
//     DFA<TableCharSet<Ucs4> > *t3;
  };
  friend class GNFA;
public:
  static enum { SAscii, SLatin1, SUtf8, SUcs2, SUtf16, SUcs4, TAscii, TLatin1, TUtf8, TUcs2, TUtf16/*, TUcs4*/ } type;
  /// Generation of the core state-machine
  void codegen(QTextStream& str);
  /// Minimization of the automaton
  GDFA& minimize();
  /// Code used for the detected tokens in the generated code
  void setActions(const vector<QString>& actions);
  GDFA(const GDFA& o);
  ~GDFA();
  GDFA& operator=(const GDFA& o);
private:
  /// Has to be generated using a GNFA
  GDFA();
};

/// Non-deterministic finite automaton
class GNFA
{
  union
  {
    NFA<SeqCharSet<Ascii> > *s0;
    NFA<SeqCharSet<Latin1> > *s1;
    NFA<SeqCharSet<Ucs2> > *s2;
    NFA<SeqCharSet<Ucs4> > *s3;
    NFA<TableCharSet<Ascii> > *t0;
    NFA<TableCharSet<Latin1> > *t1;
    NFA<TableCharSet<Ucs2> > *t2;
//     NFA<TableCharSet<Ucs4> > *t3;
  };
public:
  /// Empty set
  GNFA();
  GNFA(const GNFA& o);
  ~GNFA();
  GNFA& operator=(const GNFA& o);
  GNFA(const std::vector<GNFA*>& init);
  /// Intersection
  GNFA& operator&=(const GNFA& o);
  /// Concatenation
  GNFA& operator<<=(const GNFA& o);
  /// Union
  GNFA& operator|=(const GNFA& o);
  /// Difference
  GNFA& operator^=(const GNFA& o);
  /// Kleene-star
  GNFA& operator*();
  /// Complement
  GNFA& negate();
  /// DFA
  GDFA dfa();
  
  /// Accepts any single character
  static GNFA anyChar();
  /// Accepts the given word
  static GNFA keyword(const QString& str);
  /// Accepts any of the chars in the string
  static GNFA collection(const QString& str);
  /// Accepts only the empty word
  static GNFA emptyWord();
  /// Accepts any character between begin and end (including begin, excluding end)
  static GNFA range(quint32 begin, quint32 end);
};

}

#endif
