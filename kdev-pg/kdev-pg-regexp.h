/*
    SPDX-FileCopyrightText: 2010 Jonathan Schmidt-Dominé <devel@the-user.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEV_PG_REGEXP
#define KDEV_PG_REGEXP

#include <kdev-pg-char-sets.h>

#include <vector>
#include <algorithm>
#include <stack>
#include <string>
#include <cassert>


#include <QString>

namespace KDevPG
{

template<typename T> class DFA;
template<typename T> class NFA;
template<CharEncoding enc> class SeqCharSet;
template<CharEncoding enc> class TableCharSet;

// General

class GNFA;

enum AutomatonType { SAscii, SLatin1, SUtf8, SUcs2, SUtf16, SUcs4, TAscii, TLatin1, TUtf8, TUcs2, TUtf16/*, TUcs4*/ };

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
  static AutomatonType type;
  /// Generation of the core state-machine
  void codegen(QTextStream& str);
  /// Minimization of the automaton
  GDFA& minimize();
  /// Code used for the detected tokens in the generated code
  void setActions(const std::vector<QString>& actions);
  GDFA(const GDFA& o);
  ~GDFA();
  GDFA& operator=(const GDFA& o);
  /// Debugging-information
  void inspect();
  /// Nice output in .dot-format
  void dotOutput(QTextStream& o, const QString& name);
  /// NFA
  GNFA nfa();
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
  friend class GDFA;
public:
  GNFA(const GNFA& o);
  ~GNFA();
  GNFA& operator=(const GNFA& o);
  explicit GNFA(const std::vector<GNFA*>& init);
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
  /// Whether it accepts the empty word
  bool acceptsEpsilon() const;
  /// Whether it represents the empty set
  bool isEmpty() const;
  /// Whether it contains arrivable loops
  bool isUnbounded() const;
  /// Length of the shortest accepted input (-1 iff isEmpty)
  int minLength() const;
  /// Length of the longest accepted input (-1 iff isEmpty, -2 iff isUnbounded)
  int maxLength() const;
  /// DFA
  GDFA dfa();
  /// Minimize
  GNFA& minimize();
  /// Debugging-information
  void inspect();
  /// Nice output in .dot-format
  void dotOutput(QTextStream& o, const QString& name);
  
  /// Accepts nothing
  static GNFA empty();
  /// Accepts any single character
  static GNFA anyChar();
  /// Accepts the given word
  static GNFA word(const QString& str);
  /// Accepts any of the chars in the string
  static GNFA collection(const QString& str);
  /// Accepts only the empty word
  static GNFA emptyWord();
  /// Accepts anything
  static GNFA anything();
  /// Accepts any character between begin and end (including begin, excluding end)
  static GNFA range(quint32 begin, quint32 end);
  /// Accepts a single codepoint (or nothing if it is not represantable with tha charset)
  static GNFA character(quint32 codepoint);
private:
  GNFA(); // has to be constructed using a static member
};

}

#endif
