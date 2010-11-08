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
#include <QTextCodec>

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
    DFA<TableCharSet<Ucs4> > *t3;
  };
  friend class GNFA;
public:
  static const enum { SAscii, SLatin1, SUcs2, SUcs4, TAscii, TLatin1, TUcs2, TUcs4 } type = SUcs2;
  void codegen(QTextStream& str);
  GDFA();
  GDFA(const GDFA& o);
  ~GDFA();
  GDFA& operator=(const GDFA& o);
};

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
    NFA<TableCharSet<Ucs4> > *t3;
  };
  friend GNFA keyword(const QString&);
public:
  GNFA();
  GNFA(const GNFA& o);
  ~GNFA();
  GNFA& operator=(const GNFA& o);
  GNFA(const std::vector<GNFA*>& init);
  GNFA& operator&=(const GNFA& o);
  GNFA& operator|=(const GNFA& o);
  GNFA& operator*();
  GDFA dfa();
};

GNFA keyword(const QString& str);

}

#endif
