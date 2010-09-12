































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
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>

using namespace std;

#include <QString>
#include <QByteArray>
#include <QVector>

#define NC(...) __VA_ARGS__


class TreeCharSet
{
    set<QChar> data;
    bool mEpsilon: 1;
    friend ostream& operator<<(ostream&, const TreeCharSet&);
public:
    TreeCharSet(const QString& str ) : mEpsilon(false)
    {
        for(int i = 0; i != str.size(); ++i)
            data.insert(str[i]);
    }
    TreeCharSet() : mEpsilon(true)
    {}
    TreeCharSet(const TreeCharSet& o) : data(o.data), mEpsilon(o.mEpsilon)
    {
    }
    TreeCharSet& operator=(const TreeCharSet& o)
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
    bool accepts(QChar chr) const
    {
        return data.count(chr);
    }
    TreeCharSet intersection(const TreeCharSet& o) const
    {
        TreeCharSet ret;
        ret.mEpsilon = false;
        set_intersection(data.begin(), data.end(), o.data.begin(), o.data.end(), inserter(ret.data, ret.data.begin()));
        return ret;
    }
    TreeCharSet difference(const TreeCharSet& o) const
    {
        TreeCharSet ret;
        ret.mEpsilon = false;
        set_difference(data.begin(), data.end(), o.data.begin(), o.data.end(), inserter(ret.data, ret.data.begin()));
        return ret;
    }
    TreeCharSet getUnion(const TreeCharSet& o) const
    {
        TreeCharSet ret;
        ret.mEpsilon = false;
        set_union(data.begin(), data.end(), o.data.begin(), o.data.end(), inserter(ret.data, ret.data.begin()));
        return ret;
    }
    TreeCharSet& unite(const TreeCharSet& o)
    {
        for(auto i = o.data.begin(); i != o.data.end(); ++i)
            data.insert(*i);
        return *this;
    }
    bool operator==(const TreeCharSet& o) const
    {
        return mEpsilon == o.mEpsilon && data == o.data;
    }
};

ostream& operator<<(ostream& o, const TreeCharSet& c)
{
    foreach(QChar x, c.data)
        o << x.toLatin1();
    return o;
}

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
typename Codec2Container<codec>::Result qString2Codec(const QString& str)
{
  static_assert(Codec2False<codec>::value, "Unknown codec");
}

template<>
QByteArray qString2Codec<Ascii>(const QString& str)
{
  return str.toAscii();
}

template<>
QByteArray qString2Codec<Latin1>(const QString& str)
{
  return str.toLatin1();
}

template<>
QVector<quint32> qString2Codec<Ucs4>(const QString& str)
{
  return str.toUcs4();
}

template<>
QVector<quint16> qString2Codec<Ucs2>(const QString& str)
{
  QVector<quint16> ret(str.size());
  memcpy(&ret[0], str.utf16(), 2*str.size());
  return ret;
}

template<CharEncoding codec>
class SeqCharSet;

template<CharEncoding codec>
ostream& operator<<(ostream&, const SeqCharSet<codec>&);

template<CharEncoding codec>
class SeqCharSet
{
    typedef typename Codec2Int<codec>::Result Int;
    typedef SeqCharSet<codec> Self;
    vector<pair<Int, Int> > data;
    bool mEpsilon: 1;
    friend ostream& operator<< <>(ostream&, const Self&);
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
    SeqCharSet() : mEpsilon(true)
    {}
    SeqCharSet(const Self& o) : data(o.data), mEpsilon(o.mEpsilon)
    {
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
        int tpos = 0, opos = 0;
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
    Self difference(const Self& o) const
    {
        Self ret;
        ret.mEpsilon = false;
        int tpos = 0, opos = 0;
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
        int tpos = 0, opos = 0;
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

template<CharEncoding codec>
ostream& operator<<(ostream &o, const SeqCharSet<codec> &cs)
{
  typedef typename Codec2Int<codec>::Result Int;
  o << "[u" << 8*sizeof(Int);
  foreach(NC(pair<Int, Int> p), cs.data)
    o << ", " << QChar(p.first).toLatin1() << "-" << QChar(p.second).toLatin1();
  o << "]";
  return o;
}

template<CharEncoding codec>
class TableCharSet;

template<CharEncoding codec>
ostream& operator<<(ostream&, const TableCharSet<codec>&);

template<CharEncoding codec>
class TableCharSet
{
  static const bitset<Codec2Size<codec>::value> nullData;
  bitset<Codec2Size<codec>::value> data;
  bool mEpsilon: 1;
  typedef TableCharSet<codec> Self;
  typedef typename Codec2Int<codec>::Result Int;
  friend ostream& operator<< <>(ostream&, const Self&);
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
  TableCharSet() : mEpsilon(true)
  {}
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

template<CharEncoding codec>
const bitset<Codec2Size<codec>::value> TableCharSet<codec>::nullData;

template<CharEncoding codec>
ostream& operator<<(ostream &o, const TableCharSet<codec> &cs)
{
  typedef typename Codec2Int<codec>::Result Int;
  o << "[t" << 8*sizeof(Int) << ":";
  for(size_t i = 0; i != cs.data.size(); ++i)
    if(cs.data[i])
      o << QChar(i).toLatin1();
  o << "]";
  return o;
}

/*int main()
{
    string a, b;
    cin >> a >> b;
    SeqCharSet A(a.c_str()), B(b.c_str());
    cout << A << endl << B << endl << A.intersection(B) << endl << B.intersection(A) << endl << A.difference(B) << endl << B.difference(A) << endl << A.getUnion(B) << endl << B.getUnion(A) << endl;
}*/
