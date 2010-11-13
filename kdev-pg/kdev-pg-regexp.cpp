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

#include "kdev-pg-char-sets.h"
#include "kdev-pg-regexp.h"
#include "kdev-pg.h"
#include "kdev-pg-regexp-helper.h"
#include <iostream>
#include <tr1/unordered_set>
#include <tr1/unordered_map>

using namespace std;
using namespace tr1;


#define NC(...) __VA_ARGS__

#define q_Hash_to_tr1_hash(type) \
namespace std                                               \
{                                                           \
  namespace tr1                                             \
  {                                                         \
    template<> struct hash< type >                          \
    {                                                       \
      inline size_t operator()(const type &x) const         \
      {                                                     \
        return qHash(x);                                    \
      }                                                     \
    };                                                      \
  }                                                         \
}

q_Hash_to_tr1_hash(QBitArray)


namespace KDevPG
{

typedef vector<bool> UsedBitArray;
typedef QUtf8ToUcs4Iterator Iterator;
// typedef TableCharSet<Ascii> CharSet;

template<typename CharSet> class NFA;

template<typename CS>
class DFA
{
public:
    typedef CS CharSet;
private:
    size_t nstates;
    vector<vector<pair<CharSet, size_t> > > rules;
    size_t numActions;
    vector<size_t> accept;
    vector<QString> actions;
    friend class NFA<CharSet>;
public:
    void setActions(const vector<QString>& _actions)
    {
      actions = _actions;
      numActions = actions.size() - 1;
    }
    void codegen(QTextStream& str)
    {
      QStringList innerActions;
      innerActions.reserve(nstates);
      for(size_t i = 0; i != nstates; ++i)
      {
        if(accept[i])
          innerActions.push_back("/*" + QString::number(accept[i]) + " action */lpos = CURR_POS; lstate = " + QString::number(accept[i]) + "; goto _state_" + QString::number(i) + ";\n");
        else
          innerActions.push_back("goto _state_" + QString::number(i) + ";");
      }
      CharSetCondition<CharSet> csc;
      for(size_t i = 0; i != nstates; ++i)
      {
        str << "\n_state_" + QString::number(i) + ": chr = NEXT_CHR; ";
        csc(str, rules[i], innerActions);
      }
      str << "_end:\nplain() = lpos;\nswitch(lstate) {\n";
      for(size_t i = 0; i <= numActions; ++i)
      {
        str << "case " << QString::number(i) << ": ";
        if(i == 0)
          str << "_fail: ";
        str << "{" << actions[i] << "}\n";
      }
      str << "}\n";
    }
    void inspect()
    {
        cout << "#states = " << nstates << " accept = <";
        for(size_t i = 0; i != nstates; ++i)
            cout << ", " << accept[i];
        cout << "> rules = {";
        for(size_t i = 0; i != nstates; ++i)
        {
            cout << i << " = {";
            for(size_t j = 0; j != rules[i].size(); ++j)
                cout << rules[i][j].first << " = " << rules[i][j].second << ", ";
            cout << "} ";
        }
        cout << endl;
    }
    size_t accepts(const QString& str)
    {
        size_t state = 0;
        foreach(QChar c, str)
        {
            foreach(NC(const pair<CharSet, size_t>& r), rules[state])
            {
                if(r.first.accepts(c.unicode())) // make it more portable!!
                {
                    state = r.second;
                    goto success;
                }
            }
            return false;
            success:;
        }
        return accept[state];
    }
    // tokenizing
    pair<Iterator, size_t> nextAction(Iterator iter)
    {
      Iterator npos = iter;
      size_t action = -1;
      size_t state = 0;
      while(iter.hasNext())
      {
        if(accept[state])
        {
          npos = iter;
          action = accept[state];
        }
        quint64 chr = iter.next(); // make it more portable!!
        foreach(NC(const pair<CharSet, size_t>& r), rules[state])
        {
          if(r.first.accepts(chr))
          {
            state = r.second;
            goto success;
          }
        }
        return make_pair(npos, action);
        success:;
      }
      if(accept[state])
      {
        npos = iter;
        action = accept[state];
      }
      return make_pair(npos, action);
    }
    DFA<CharSet>& filterStates(const UsedBitArray& active)
    {
        size_t curr = 0;
        vector<size_t> mapping(nstates);
        for(size_t i = 0; i != nstates; ++i)
        {
            if(active[i])
            {
                rules[curr] = rules[i];
                accept[curr] = accept[i];
                mapping[i] = curr;
                ++curr;
            }
        }
        rules.resize(curr);
        accept.resize(curr);
        nstates = curr;
        for(size_t i = 0; i != nstates; ++i)
        {
            for(__typeof__(rules[i].begin()) j = rules[i].begin(); j != rules[i].end(); ++j)
            {
                j->second = mapping[j->second];
            }
        }
        return *this;
    }
    DFA<CharSet>& eliminateUnarrivableStates()
    {
        UsedBitArray arrivable(nstates);
        arrivable[0] = true;
        stack<size_t> todo;
        todo.push(0);
        while(todo.size())
        {
            size_t curr = todo.top();
            todo.pop();
            foreach(NC(const pair<CharSet, size_t>& i), rules[curr])
            {
                if(!arrivable[i.second])
                {
                    arrivable[i.second] = true;
                    todo.push(i.second);
                }
            }
        }
        return filterStates(arrivable);
    }
    DFA<CharSet>& eliminateInactiveStates()
    {
      // should never happen
      UsedBitArray active(nstates);
      for(size_t i = 0; i != nstates; ++i)
        if(accept[i])
          active[i] = true;
      bool changed;
      do
      {
        changed = false;
        for(size_t i = 0; i != nstates; ++i)
        {
          if(!active[i])
          {
            for(size_t j = 0; j != rules[i].size(); ++j)
            {
              if(active[rules[i][j].second])
              {
                active[i] = true;
                changed = true;
                break;
              }
            }
          }
        }
      } while(changed);
      return filterStates(active);
    }
    /// followers in same group for every input
    bool sameGroup(size_t ngroups, const vector<size_t>& ogroups, size_t x, size_t y)
    {
        vector<CharSet> xsets(ngroups), ysets(ngroups);
        foreach(NC(const pair<CharSet, size_t>& i), rules[x])
            xsets[ogroups[i.second]].unite(i.first);
        foreach(NC(const pair<CharSet, size_t>& i), rules[y])
            ysets[ogroups[i.second]].unite(i.first);
        return xsets == ysets;
    }
    DFA<CharSet>& minimize()
    {
        eliminateUnarrivableStates();
        vector<vector<size_t> > grinv(numActions + 1);
        for(size_t i = 0; i != nstates; ++i)
            grinv[(accept[i] - accept[0] + grinv.size()) % grinv.size()].push_back(i);
        size_t ongroups;
        vector<size_t> groups(nstates);
        do
        {
            for(size_t i = 0; i != grinv.size(); ++i)
                for(size_t j = 0; j != grinv[i].size(); ++j)
                    groups[grinv[i][j]] = i;
            ongroups = grinv.size();
            grinv.clear();
            for(size_t i = 0; i != nstates; ++i)
            {
                for(size_t j = 0; j != grinv.size(); ++j)
                {
                    if(groups[grinv[j][0]] == groups[i] && sameGroup(ongroups, groups, grinv[j][0], i))
                    {
                        grinv[j].push_back(i);
                        goto found;
                    }
                }
                grinv.resize(grinv.size()+1);
                grinv.back().push_back(i);
                found:;
            }
        }
        while(ongroups != grinv.size());
        vector<vector<pair<CharSet, size_t> > > _rules(grinv.size());
        vector<size_t> _accept(grinv.size());
        for(size_t i = 0; i != nstates; ++i)
        {
            _accept[groups[i]] = accept[i];
            foreach(NC(const pair<CharSet, size_t>& j), rules[i])
                _rules[groups[i]].push_back(make_pair(j.first, groups[j.second]));
        }
        rules = _rules;
        nstates = grinv.size();
        accept = _accept;
        for(int i = 0; i != nstates; ++i)
        {
            vector<CharSet> mapping(nstates);
            foreach(NC(const pair<CharSet, size_t>& j), rules[i])
                mapping[j.second].unite(j.first);
            rules[i].clear();
            for(int j = 0; j != nstates; ++j)
                if(!mapping[j].empty())
                    rules[i].push_back(make_pair(mapping[j], j));
        }
        return *this;
    }
};

template<typename CS>
class NFA
{
public:
    typedef CS CharSet;
private:
    size_t nstates;
    vector<vector<pair<CharSet, size_t> > > rules;
    size_t accept;
public:
    void inspect()
    {
        cout << "#states = " << nstates << " accept = " << accept << " rules = {";
        for(size_t i = 0; i != nstates; ++i)
        {
            cout << i << " = {";
            for(size_t j = 0; j != rules[i].size(); ++j)
                cout << rules[i][j].first << " = " << rules[i][j].second << ", ";
            cout << "} ";
        }
        cout << endl;
    }
    NFA() : nstates(1), rules(1), accept(0)
    {}
    NFA(const NFA<CharSet>& o) : nstates(o.nstates), rules(o.rules), accept(o.accept)
    {}
    NFA(const CharSet& set) : nstates(2), rules(2), accept(1)
    {
        rules[0].push_back(make_pair(set, 1));
    }
    NFA(const std::vector<NFA<CharSet> >& list)
    {
      if(list.size() == 0)
      {
        nstates = 2;
        rules.resize(2);
        accept = 1;
      }
      else
      {
        accept = 1;
        for(size_t i = 0; i != list.size(); ++i)
          accept += list.begin()[i].nstates;
        nstates = accept + list.size();
        rules.resize(nstates);
        size_t start = 1;
        for(size_t i = 0; i != list.size(); ++i)
        {
          for(size_t j = start; j != start + list.begin()[i].nstates; ++j)
          {
              rules[j] = list.begin()[i].rules[j - start];
              for(size_t k = 0; k != rules[j].size(); ++k)
                  rules[j][k].second += start;
          }
          rules[0].push_back(make_pair(CharSet(), start));
          start += list.begin()[i].nstates;
          rules[start - 1].push_back(make_pair(CharSet(), nstates - list.size() + i));
        }
      }
    }
    void adjust(size_t startnum)
    {
        accept += startnum;
        nstates += startnum;
        rules.resize(nstates);
        for(size_t i = nstates; i != startnum; )
        {
            --i;
            rules[i] = rules[i - startnum];
            for(size_t j = 0; j != rules[i].size(); ++j)
                rules[i][j].second += startnum;
        }
        for(size_t i = 0; i != startnum; ++i)
            rules[i].clear();
    }
    NFA<CharSet>& operator|=(const NFA<CharSet>& o)
    {
        adjust(1);
        rules.resize(o.nstates+nstates+2);
        for(size_t i = nstates; i != nstates + o.nstates; ++i)
        {
            rules[i] = o.rules[i - nstates];
            for(size_t j = 0; j != rules[i].size(); ++j)
                rules[i][j].second += nstates;
        }
        rules[0].push_back(make_pair(CharSet(), 1));
        rules[0].push_back(make_pair(CharSet(), nstates));
        nstates += o.nstates;
        rules[accept].push_back(make_pair(CharSet(), nstates));
        rules[nstates-1].push_back(make_pair(CharSet(), nstates));
        accept = nstates;
        ++nstates;
        return *this;
    }
    NFA<CharSet>& operator&=(const NFA<CharSet>& o)
    {
        rules.resize(nstates + o.nstates + 1);
        rules[accept].push_back(make_pair(CharSet(), nstates));
        accept = o.accept + nstates;
        for(size_t i = nstates; i != nstates+o.nstates; ++i)
        {
            rules[i] = o.rules[i-nstates];
            for(size_t j = 0; j != rules[i].size(); ++j)
                rules[i][j].second += nstates;
        }
        nstates += o.nstates;
        return *this;
    }
    NFA<CharSet>& operator*()
    {
        rules[accept].push_back(make_pair(CharSet(), 0));
        rules[0].push_back(make_pair(CharSet(), nstates));
        accept = nstates;
        ++nstates;
        rules.resize(nstates);
        return *this;
    }
    UsedBitArray closure(UsedBitArray s)
    {
        assert(s.size() == nstates);
        stack<size_t> todo;
        for(size_t i = 0; i != nstates; ++i)
            if(s[i])
                todo.push(i);
        while(todo.size())
        {
            size_t x = todo.top();
            todo.pop();
            for(size_t i = 0; i != rules[x].size(); ++i)
            {
                if(rules[x][i].first.epsilon() && !s[rules[x][i].second])
                {
                    s[rules[x][i].second] = true;
                    todo.push(rules[x][i].second);
                }
            }
        }
        return s;
    }
    UsedBitArray vecUnion(const UsedBitArray& a, const UsedBitArray& b)
    {
        UsedBitArray ret(a);
        for(size_t i = 0; i != a.size(); ++i)
            ret[i] = ret[i] || b[i];
        return ret;
    }
    vector< pair<CharSet, UsedBitArray > > follow(UsedBitArray s)
    {
        vector<pair<CharSet, UsedBitArray > > pr(nstates);
        for(size_t i = 0; i != nstates; ++i)
        {
            if(s[i])
            {
                foreach(NC(const pair<CharSet, size_t>& r), rules[i])
                {
                    UsedBitArray nxt(nstates);
                    nxt[r.second] = true;
                    pr.push_back(make_pair(r.first, nxt));
                }
            }
        }
        bool b = true;
        while(b)
        {
            bool changed = false;
            b = false;
            for(size_t i = 0; i != pr.size(); ++i)
            {
                if(!pr[i].first.epsilon())
                {
                    for(size_t j = 0; j != i; ++j)
                    {
                        if(!pr[j].first.epsilon())
                        {
                            CharSet inter = pr[i].first.intersection(pr[j].first);
                            if(!inter.empty())
                            {
                                CharSet diff1 = pr[i].first.difference(inter);
                                CharSet diff2 = pr[j].first.difference(inter);
                                UsedBitArray v1 = pr[i].second, v2 = pr[j].second;
                                pr[i].first = inter;
                                pr[i].second = vecUnion(pr[i].second, pr[j].second);
                                if(diff1.empty())
                                {
                                    if(diff2.empty())
                                    {
                                        swap(pr[j], pr.back());
                                        pr.pop_back();
                                    }
                                    else
                                    {
                                        pr[j].first = diff2;
                                        pr[j].second = v2;
                                    }
                                }
                                else
                                {
                                    pr[j].first = diff1;
                                    pr[j].second = v1;
                                    if(!diff2.empty())
                                        pr.push_back(make_pair(diff2, v2));
                                }
                                b = true;
                                goto retry;
                            }
                        }
                    }
                }
            }
            retry:;
        }
        return pr;
    }
    DFA<CharSet> dfa()
    {
        /*unordered_*/set<UsedBitArray > states;
        /*unordered_*/map<UsedBitArray, vector<pair<CharSet, UsedBitArray > > > rules;
        stack<UsedBitArray > todo;
        UsedBitArray start(nstates);
        start[0] = true;
        todo.push(closure(start));
        while(todo.size())
        {
            UsedBitArray x = todo.top();
            todo.pop();
            states.insert(x);
            rules[x];
            vector<pair<CharSet, UsedBitArray > > nxt = follow(x);
            foreach(NC(const pair<CharSet, UsedBitArray >& nx), nxt)
            {
                if(!nx.first.epsilon())
                {
                    UsedBitArray n = closure(nx.second);
                    if(!states.count(n))
                        todo.push(n);
                    rules[x].push_back(make_pair(nx.first, n));
                }
            }
        }
        DFA<CharSet> _;
        _.nstates = states.size();
        _.accept.resize(_.nstates);
        _.numActions = nstates - accept;
        _.actions.resize(_.numActions + 1);
        /*unordered_*/map<UsedBitArray, size_t> st;
        size_t cnt = 0;
        foreach(const UsedBitArray& i, states)
        {
            if(i[0] && cnt)
            {
                st[*states.begin()] = cnt;
                st[i] = 0;
            }
            else
                st[i] = cnt;
            ++cnt;
        }
//         for(auto i = st.begin(); i != st.end(); ++i)
//         {
//           cout << i->second << ": <";
//           for(size_t j = 0; j != nstates; ++j)
//             if(i->first[j])
//               cout << ", " << j;
//           cout << ">" << endl;
//         }
        _.rules.resize(_.nstates);
        for(__typeof__(st.begin()) i = st.begin(); i != st.end(); ++i)
        {
          for(size_t j = accept; j != nstates; ++j)
          {
            if(i->first[j])
            {
              _.accept[i->second] = j - accept + 1;
              break;
            }
          }
        }
        for(__typeof__(rules.begin()) i = rules.begin(); i != rules.end(); ++i)
        {
            size_t key = st[i->first];
            foreach(NC(const pair<CharSet, UsedBitArray > nx), i->second)
                _.rules[key].push_back(make_pair(nx.first, st[nx.second]));
        }
        return _;
    }
};

#define EACH_TYPE(macro) \
switch(GDFA::type) \
{ \
  case GDFA::SAscii: { macro(s0); } break; \
  case GDFA::S8Bit: {macro(s1); } break; \
  case GDFA::SUcs2: { macro(s2); } break; \
  case GDFA::SUcs4: { macro(s3); } break; \
  case GDFA::TAscii: { macro(t0); } break; \
  case GDFA::T8Bit: { macro(t1); } break; \
  case GDFA::TUcs2: { macro(t2); } break; \
  default: exit(-1); \
}

void GDFA::codegen(QTextStream& str)
{
#define macro(x) x->codegen(str);
    EACH_TYPE(macro)
#undef macro
}

GDFA& GDFA::minimize()
{
#define macro(x) x->minimize();
  EACH_TYPE(macro)
#undef macro
  return *this;
}

void GDFA::setActions(const std::vector< QString >& actions)
{
#define macro(x) x->setActions(actions);
  EACH_TYPE(macro)
#undef macro
}

GDFA::GDFA()
{
#define macro(x) x = new __typeof__(*x);
    EACH_TYPE(macro)
#undef macro
}

GDFA::GDFA(const KDevPG::GDFA& o)
{
#define macro(x) x = new (__typeof__(*x))(*o.x);
    EACH_TYPE(macro)
#undef macro
}

GDFA::~GDFA()
{
#define macro(x) delete x;
    EACH_TYPE(macro)
#undef macro
}

GDFA& GDFA::operator=(const KDevPG::GDFA& o)
{
#define macro(x) *x = *o.x;
  EACH_TYPE(macro)
#undef macro
  return *this;
}

GNFA::GNFA()
{
#define macro(x) x = new __typeof__(*x);
  EACH_TYPE(macro)
#undef macro
}

GNFA::GNFA(const KDevPG::GNFA& o)
{
#define macro(x) x = new (__typeof__(*x))(*o.x);
  EACH_TYPE(macro)
#undef macro
}

GNFA::GNFA(const std::vector< GNFA* >& init)
{
#define macro(x) vector<__typeof__(*x)> vec(init.size()); for(int i = 0; i != init.size(); ++i) vec[i] = *(init[i]->x); x = new (__typeof__(*x))(vec);
  EACH_TYPE(macro)
#undef macro
}

GNFA::~GNFA()
{
#define macro(x) delete x;
  EACH_TYPE(macro)
#undef macro
}

GNFA& GNFA::operator=(const KDevPG::GNFA& o)
{
#define macro(x) *x = *o.x;
  EACH_TYPE(macro)
#undef macro
  return *this;
}

GNFA& GNFA::operator&=(const KDevPG::GNFA& o)
{
#define DO_AND(x) *x &= *o.x;
  EACH_TYPE(DO_AND)
#undef DO_AND
  return *this;
}

GNFA& GNFA::operator|=(const KDevPG::GNFA& o)
{
#define DO_OR(x) *x |= *o.x;
  EACH_TYPE(DO_OR)
#undef DO_OR
  return *this;
}

GNFA& GNFA::operator*()
{
#define DO_STAR(x) **x;
  EACH_TYPE(DO_STAR)
#undef DO_STAR
  return *this;
}

GDFA GNFA::dfa()
{
  GDFA r;
#define macro(x) *r.x = x->dfa();
  EACH_TYPE(macro)
#undef macro
  return r;
}

GNFA keyword(const QString& str)
{
#define macro(x) \
  GNFA r; \
  QByteArray qba(str.toUtf8()); \
  typedef typeof(*r.x) T; \
  Codec2FromUtf8Iterator<T::CharSet::codec>::Result iter(qba); \
  while(iter.hasNext()) \
  { \
    *r.x &= (typeof(*r.x))(iter.next()); \
  } \
  return r;
  EACH_TYPE(macro)
#undef macro
}

typeof(GDFA::type) GDFA::type = GDFA::SUcs2;

template<CharEncoding enc>
const bitset<TableCharSet<enc>::nChars> TableCharSet<enc>::nullData = bitset<TableCharSet<enc>::nChars>();

}
