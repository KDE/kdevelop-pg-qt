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

#ifndef KDEV_PG_REGEXP_HELPER
#define KDEV_PG_REGEXP_HELPER

#include <kdev-pg-char-sets.h>

#include <iomanip>

namespace KDevPG
{

template<CharEncoding codec>
class SeqCharSet;

inline void printChar(ostream& o, uint x)
{
  auto flags = o.flags();
  auto width = o.width();
  auto fill = o.fill();
  if(x == '\\')
    o << "'\\\\'";
  else if(x == '\'')
    o << "'\\\\''";
  else if(x == '"')
    o << "'\\\"'";
  else if(x >= 32 && x <= 126)
    o << '\'' << (char)x << '\'';
  else
    o << hex << "\\" << setw(2) << setfill('0') << x;
  o.fill(fill);
  o.width(width);
  o.flags(flags);
}

inline void printChar(QTextStream& o, uint x)
{
  auto base = o.integerBase();
  auto width = o.fieldWidth();
  auto pad = o.padChar();
  if(x == '\\')
    o << "'\\\\'";
  else if(x == '\'')
    o << "'\\\\''";
  else if(x == '"')
    o << "'\\\"'";
  else if(x >= 32 && x <= 126)
    o << '\'' << (char)x << '\'';
  else
    o << Qt::hex << "\\" << qSetFieldWidth(2) << qSetPadChar('0') << x;
  o.setPadChar(pad);
  o.setFieldWidth(width);
  o.setIntegerBase(base);
}

template<typename Stream, CharEncoding codec>
Stream& operator<<(Stream&, const SeqCharSet<codec>&);

template<class cs> class CharSetCondition;

template<CharEncoding _codec>
class SeqCharSet
{
public:
    static const CharEncoding codec = _codec;
private:
    typedef typename Codec2Int<codec>::Result Int;
    typedef SeqCharSet<codec> Self;
    vector<pair<Int, Int> > data;
    bool mEpsilon: 1;
    template<typename Stream, CharEncoding codec> /* when using fixed codec I get linker errors (undefined reference), templates do not get recognized to be the same */
    friend Stream& operator<<(Stream&, const SeqCharSet<codec>&);
    friend class CharSetCondition< SeqCharSet<codec> >;
public:
    SeqCharSet(const QString& s ) : mEpsilon(false)
    {
      auto str = qString2Codec<codec>(s);
      sort(str.begin(), str.end());
      Int last = -1;
      for(int i = 0; i != str.size(); ++i)
      {
        Int x = str[i];
        if(x == last)
          last = ++data.back().second;
        else
          data.push_back(make_pair(x, last = x+1));
      }
    }
    SeqCharSet(Int chr) : mEpsilon(false)
    {
      data.push_back(make_pair(chr, chr + 1));
    }
    SeqCharSet() : mEpsilon(true)
    {}
    SeqCharSet(const Self& o) : data(o.data), mEpsilon(o.mEpsilon)
    {
    }
    static Self fullSet()
    {
      Self ret;
      ret.mEpsilon = false;
      ret.data.push_back(make_pair(Int(0), Int(Codec2Size<codec>::value)));
      return ret;
    }
    static Self range(Int begin, Int end)
    {
      Self ret;
      ret.mEpsilon = false;
      if(begin < end)
        ret.data.push_back(make_pair(begin, end));
      return ret;
    }
    static Self emptySet()
    {
      Self ret;
      ret.mEpsilon = false;
      return ret;
    }
    SeqCharSet& operator=(const Self& o)
    {
      data = o.data;
      mEpsilon = o.mEpsilon;
      return *this;
    }
    bool epsilon() const
    {
        return mEpsilon;
    }
    bool empty() const
    {
        return data.empty();
    }
    bool accepts(Int x) const
    {
        int l = 0, r = data.size();
        while(l != r)
        {
          int m = (l + r) / 2;
          if(data[m].first <= x)
          {
            if(data[m].second > x)
              return true;
            l = m + 1;
          }
          else
            r = m;
        }
        return false;
    }
    Self intersection(const Self& o) const
    {
        Self ret;
        ret.mEpsilon = false;
        size_t tpos = 0, opos = 0;
        while(tpos != data.size() && opos != o.data.size())
        {
          if(data[tpos].first >= o.data[opos].second)
            ++opos;
          else if(o.data[opos].first >= data[tpos].second)
            ++tpos;
          else
          {
            ret.data.push_back(make_pair(max(o.data[opos].first, data[tpos].first), min(o.data[opos].second, data[tpos].second)));
            if(data[tpos].second > o.data[opos].second)
              ++opos;
            else
              ++tpos;
          }
        }
        // the end??
        return ret;
    }
    Self& intersect(const Self& o)
    {
        *this = this->intersection(o);
        return *this;
    }
    Self& negate()
    {
        if(!mEpsilon)
        {
          if(data.size() == 0)
          {
            data.push_back(make_pair(0, Int(Codec2Size<codec>::value)));
          }
          else if(data.front().first == 0)
          {
            for(size_t i = 0; i != data.size()-1; ++i)
            {
              data[i].first = data[i].second;
              data[i].second = data[i+1].first;
            }
            if(data.back().second == Codec2Size<codec>::value)
              data.pop_back();
            else
            {
              data.back().first = data.back().second;
              data.back().second = Codec2Size<codec>::value;
            }
          }
          else
          {
            Int tmpfirst = 0;
            for(size_t i = 0; i != data.size(); ++i)
            {
              Int tmptmpfirst = data[i].first;
              data[i].first = tmpfirst;
              tmpfirst = data[i].second;
              data[i].second = tmptmpfirst;
            }
            if(data.back().second != Codec2Size<codec>::value)
              data.push_back(make_pair(tmpfirst, Int(Codec2Size<codec>::value)));
          }
        }
        return *this;
    }
    Self difference(const Self& o) const
    {
        Self ret;
        ret.mEpsilon = false;
        size_t tpos = 0, opos = 0;
        bool inT = false, inO = false;
        size_t start = -1; // if there is a -1 we will know what happened
        while(tpos != data.size() && opos != o.data.size())
        {
          if(inT)
          {
            if(inO)
            {
              if(o.data[opos].second >= data[tpos].second)
              {
                inT = false;
                ++tpos;
              }
              else
              {
                start = o.data[opos].second;
                inO = false;
                ++opos;
              }
            }
            else
            {
              if(o.data[opos].first >= data[tpos].second)
              {
                if(start != data[tpos].second)
                  ret.data.push_back(make_pair(start, data[tpos].second));
                ++tpos;
                inT = false;
              }
              else
              {
                if(o.data[opos].first > start)
                  ret.data.push_back(make_pair(start, o.data[opos].first));
                inO = true;
              }
            }
          }
          else
          {
            if(inO)
            {
              if(o.data[opos].second <= data[tpos].first)
              {
                inO = false;
                ++opos;
              }
              else
              {
                inT = true;
                start = o.data[opos].second;
              }
            }
            else
            {
              if(data[tpos].first < o.data[opos].first)
              {
                inT = true;
                start = data[tpos].first;
              }
              else
              {
                inO = true;
              }
            }
          }
        }
        if(inT)
          ret.data.push_back(make_pair(start, data[tpos++].second));
        while(tpos != data.size())
          ret.data.push_back(data[tpos++]);
        return ret;
    }
    Self getUnion(const Self& o) const
    {
        Self ret;
        ret.mEpsilon = false;
        size_t tpos = 0, opos = 0;
        bool inT = false, inO = false;
        size_t start = -1; // if there is a -1 we will know what happened
        while(tpos != data.size() && opos != o.data.size())
        {
          if(inT)
          {
            if(inO)
            {
              if(o.data[opos].second >= data[tpos].second)
              {
                inT = false;
                ++tpos;
              }
              else
              {
                inO = false;
                ++opos;
              }
            }
            else
            {
              if(o.data[opos].first > data[tpos].second)
              {
                if(start != data[tpos].second)
                  ret.data.push_back(make_pair(start, data[tpos].second));
                ++tpos;
                inT = false;
              }
              else
              {
                inO = true;
              }
            }
          }
          else
          {
            if(inO)
            {
              if(o.data[opos].second < data[tpos].first)
              {
                if(start != o.data[opos].second)
                  ret.data.push_back(make_pair(start, o.data[opos].second));
                inO = false;
                ++opos;
              }
              else
              {
                inT = true;
              }
            }
            else
            {
              if(data[tpos].first < o.data[opos].first)
              {
                inT = true;
                start = data[tpos].first;
              }
              else
              {
                inO = true;
                start = o.data[opos].first;
              }
            }
          }
        }
        if(inT)
          ret.data.push_back(make_pair(start, data[tpos++].second));
        while(tpos != data.size())
          ret.data.push_back(data[tpos++]);
        if(inO)
          ret.data.push_back(make_pair(start, o.data[opos++].second));
        while(opos != o.data.size())
          ret.data.push_back(o.data[opos++]);
        return ret;
    }
    Self& unite(const Self& o)
    {
        data = getUnion(o).data;
        return *this;
    }
    bool operator==(const Self& o) const
    {
        return mEpsilon == o.mEpsilon && data == o.data;
    }
};

template<typename Stream, CharEncoding codec>
Stream& operator<<(Stream &o, const SeqCharSet<codec> &cs)
{
  typedef typename Codec2Int<codec>::Result Int;
  if(cs.mEpsilon)
    o << "&epsilon;";
  else
  {
    for(auto i = cs.data.begin(); i != cs.data.end(); ++i)
    {
      if(i != cs.data.begin())
        o << ", ";
      const auto &p = *i;
      if(p.first == p.second - 1)
        printChar(o, p.first);
      else
      {
        printChar(o, p.first);
        o << "-";
        printChar(o, (uint)p.second-1);
      }
    }
  }
  return o;
}

template<CharEncoding codec>
class TableCharSet;

template<typename Stream, CharEncoding codec>
Stream& operator<<(Stream&, const TableCharSet<codec>&);

template<CharEncoding _codec>
class TableCharSet
{
public:
  static const CharEncoding codec = _codec;
private:
  static const size_t nChars = Codec2Size<codec>::value;
  typedef bitset<nChars> BitArray;
  static const BitArray nullData;
  bitset<Codec2Size<codec>::value> data;
  bool mEpsilon: 1;
  typedef TableCharSet<codec> Self;
  typedef typename Codec2Int<codec>::Result Int;
  template<typename Stream, CharEncoding codec> /* when using fixed codec I get linker errors (undefined reference), templates do not get recognized to be the same */
  friend Stream& KDevPG::operator<<(Stream&, const TableCharSet<codec>&);
public:
  TableCharSet(const QString& s) : mEpsilon(false)
  {
      const auto str = qString2Codec<codec>(s);
      Int last = -1;
      for(int i = 0; i != str.size(); ++i)
      {
        Int x = str[i];
        data[x] = true;
      }
  }
  TableCharSet(Int chr) : mEpsilon(false)
  {
    data[chr] = true;
  }
  TableCharSet() : mEpsilon(true)
  {}
  static Self emptySet()
  {
    Self ret;
    ret.mEpsilon = false;
    return ret;
  }
  static Self fullSet()
  {
    Self ret;
    ret.data.set();
    ret.mEpsilon = false;
    return ret;
  }
  static Self range(Int begin, Int end)
  {
    Self ret;
    if(begin < end)
      for(Int i = begin; i != end; ++i)
        ret.data[i] = true;
    ret.mEpsilon = false;
    return ret;
  }
  Self& negate()
  {
    data.flip();
    return *this;
  }
  bool accepts(Int x) const
  {
    return data[x];
  }
  bool empty() const
  {
    return data == nullData;
  }
  bool epsilon() const
  {
    return mEpsilon;
  }
  Self& intersect(const Self& o)
  {
    data &= o.data;
    return *this;
  }
  Self intersection(const Self& o) const
  {
    Self ret(*this);
    ret.data &= o.data;
    return ret;
  }
  Self difference(const Self& o) const
  {
    Self ret(o);
    ret.data.flip();
    ret.data &= data;
    return ret;
  }
  Self getUnion(const Self& o) const
  {
    Self ret(*this);
    ret.data |= o.data;
    return ret;
  }
  Self& unite(const Self& o)
  {
    data |= o.data;
    return *this;
  }
  bool operator==(const Self& o) const
  {
    return mEpsilon == o.mEpsilon && data == o.data;
  }
};

template<typename Stream, CharEncoding codec>
Stream& operator<<(Stream &o, const TableCharSet<codec> &cs)
{
  typedef typename Codec2Int<codec>::Result Int;
  if(cs.mEpsilon)
    o << "&epsilon;";
  else
  {
    for(size_t i = 0; i != cs.data.size(); ++i)
      if(cs.data[i])
        printChar(o, (uint)i);
  }
  return o;
}

template<class CharSet>
class CharSetCondition
{
};

template<CharEncoding codec>
class CharSetCondition<TableCharSet<codec> >
{
  typedef typename Codec2Int<codec>::Result Int;
public:
  void operator()(QTextStream& str, const vector<pair<TableCharSet<codec>, size_t> >& transition)
  {
    str << "switch(chr) { ";
    for(size_t j = 0; j != transition.size(); ++j)
    {
      if(!transition[j].first.empty())
      {
        for(quint64 i = 0; i != Codec2Size<codec>::value; ++i)
        {
          if(transition[j].first.accepts(i))
            str << "case " << quint64(i) << ":\n";
        }
        str << "goto _state_" << transition[j].second << ";";
      }
    }
    str << "default: goto _end;\n}\n";
  }
};

template<CharEncoding codec>
class CharSetCondition<SeqCharSet<codec> >
{
  typedef typename Codec2Int<codec>::Result Int;
  void codegen(QTextStream& str, const vector<pair<pair<Int, Int>, size_t> >& data, size_t l, size_t r, size_t tmin, size_t tmax)
  {
    if(l == r)
      str << "goto _end;";
    else if(r == l + 1)
    {
      if(data[l].first.first == tmin)
      {
        if(data[l].first.second == tmax)
          str << "goto _state_" << data[l].second << ";";
        else
        {
          if(data[l].first.second == data[l].first.first + 1)
            str << "if(chr == " << quint64(data[l].first.first) << ")";
          else
            str << "if(chr < " << quint64(data[l].first.second) << ")";
          str << "\ngoto _state_" << data[l].second << "; else\ngoto _end;\n";
        }
      }
      else
      {
        if(data[l].first.second == tmax)
        {
          if(data[l].first.second == data[l].first.first + 1)
            str << "if(chr == " << quint64(data[l].first.first) << ")";
          else
            str << "if(chr >= " << quint64(data[l].first.first) << ")";
          str << "\ngoto _state_" << data[l].second << "; else\ngoto _end;\n";
        }
        else
        {
          if(data[l].first.first == data[l].first.second - 1)
            str << "if(chr == " << quint64(data[l].first.first) << ")";
          else if(data[l].first.first == data[l].first.second - 2)
            str << "if(chr == " << quint64(data[l].first.first) << " || chr == " << quint64(data[l].first.first + 1) << ")";
          else
            str << "if(chr >= " << quint64(data[l].first.first) << " && chr < " << quint64(data[l].first.second) << ")";
          str << "\ngoto _state_" << data[l].second << "; else\ngoto _end;\n";
        }
      }
    }
    else
    {
      size_t mid = (l + r) / 2;
      str << "if(chr < " << quint64(data[mid].first.first) << ") {";
      codegen(str, data, l, mid, tmin, data[mid].first.first);
      str << "} else {";
      codegen(str, data, mid, r, data[mid].first.first, tmax);
      str << "}";
    }
  }
public:
  void operator()(QTextStream& str, const vector<pair<SeqCharSet<codec>, size_t> >& transition)
  {
    vector<pair<pair<Int, Int>, size_t> > data;
    for(size_t i = 0; i != transition.size(); ++i)
    {
      for(size_t j = 0; j != transition[i].first.data.size(); ++j)
        data.push_back(make_pair(transition[i].first.data[j], transition[i].second));
    }
    sort(data.begin(), data.end());
    codegen(str, data, 0, data.size(), 0, Codec2Size<codec>::value);
  }
};

// just for the case QTextCodec may be needed
/*
class QAsciiCodec : public QTextCodec
{
public:
  QAsciiCodec() : QTextCodec()
  {
  }
  QList<QByteArray> aliases() const
  {
    QList<QByteArray> ret;
    ret << "ascii" << "us-ascii" << "usascii";
    return ret;
  }
  QByteArray convertFromUnicode(const QChar* in, int length, ConverterState* state) const
  {
    Q_UNUSED(state);
    return QString(in, length).toAscii();
  }
  virtual QString convertToUnicode(const char* in, int length, ConverterState* state) const
  {
    Q_UNUSED(state);
    return QString::fromAscii(in, length);
  }
  virtual int mibEnum() const
  {
    return 47110815; // pseudo random, should be unique
  }
  virtual QByteArray name() const
  {
    return "us-ascii";
  }
} qAsciiCodec;
*/

}

#endif
