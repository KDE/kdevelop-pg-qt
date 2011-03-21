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

// TODO: Lookahead operator
// TODO: Line-End etc.
// TODO: On-context-switch etc.
// TODO: Deactivate/activate rules (have to keep the bitsets of possible final states)


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
            for(auto j = rules[i].begin(); j != rules[i].end(); ++j)
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
        for(size_t i = 0; i != nstates; ++i)
        {
            vector<CharSet> mapping(nstates);
            foreach(NC(const pair<CharSet, size_t>& j), rules[i])
                mapping[j.second].unite(j.first);
            rules[i].clear();
            for(size_t j = 0; j != nstates; ++j)
                if(!mapping[j].empty())
                    rules[i].push_back(make_pair(mapping[j], j));
        }
        return *this;
    }
    NFA<CharSet> nfa() const;
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
    friend class DFA<CharSet>;
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
    /**
     * Accepts no words.
     */
    NFA() : nstates(2), rules(2), accept(1)
    {}
    static NFA<CharSet> emptyWord()
    {
      NFA<CharSet> ret;
      ret.nstates = 1;
      ret.rules.resize(1);
      //ret.accept = 0;
      return ret;
    }
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
    NFA<CharSet>& operator<<=(const NFA<CharSet>& o)
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
        for(auto i = st.begin(); i != st.end(); ++i)
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
        for(auto i = rules.begin(); i != rules.end(); ++i)
        {
            size_t key = st[i->first];
            foreach(NC(const pair<CharSet, UsedBitArray > nx), i->second)
                _.rules[key].push_back(make_pair(nx.first, st[nx.second]));
        }
        return _;
    }
    NFA<CharSet>& negate()
    {
      DFA<CharSet> tmp = dfa();
      tmp.rules.push_back(vector< pair<CharSet, size_t> >());
      tmp.rules.back().push_back(make_pair(CharSet::fullSet(), tmp.nstates));
      ++tmp.nstates;
      for(auto i = tmp.accept.begin(); i != tmp.accept.end(); ++i)
      {
        if(*i == 0)
          *i = 1;
        else
          *i = 0;
        qDebug() << *i;
      }
      tmp.accept.push_back(1);
//       tmp.accept.back() = 1;
      for(auto i = tmp.rules.begin(); i != tmp.rules.end(); ++i)
      {
        CharSet successSet = CharSet::fullSet();
        for(auto j = i->begin(); j != i->end(); ++j)
        {
          CharSet tmp = j->first;
          tmp.negate();
          successSet.intersect(tmp);
        }
        i->push_back(make_pair(successSet, tmp.nstates - 1));
      }
      tmp.eliminateUnarrivableStates();
      tmp.eliminateInactiveStates();
      *this = tmp.nfa();
      qDebug() << nstates << accept;
      for(auto i = rules.begin(); i != rules.end(); ++i)
      {
        qDebug() << (i-rules.begin()) << ":";
        for(auto j = i->begin(); j != i->end(); ++j)
          qDebug() << j->first.epsilon() << j->second;
        qDebug() << endl;
      }
      return *this;
    }
    NFA<CharSet>& operator&=(const NFA<CharSet>& o)
    {
      NFA<CharSet> _o = o;
      _o.negate();
      negate();
      return (*this |= _o).negate();
    }
    NFA<CharSet>& operator^=(const NFA<CharSet>& o)
    {
      negate();
      return (*this |= o).negate();
    }
};

template<typename CharSet>
NFA< CharSet > DFA<CharSet>::nfa() const
{
  NFA<CharSet> ret;
  ret.nstates = nstates;
  ret.rules = rules;
  ret.accept = nstates;
  for(size_t i = 0; i != nstates; ++i)
  {
    if(nstates + accept[i] > ret.nstates)
    {
      ret.nstates = nstates + accept[i];
      ret.rules.resize(ret.nstates);
    }
    if(accept[i] != 0)
      ret.rules[i].push_back(make_pair(CharSet(), nstates + accept[i] - 1));
  }
  return ret;
}

// notice: utf8/8bit and utf16/ucs2 do not require different NFAs and DFAs
#define EACH_TYPE(macro) \
switch(GDFA::type) \
{ \
  case GDFA::SAscii: { macro(s0); } break; \
  case GDFA::SLatin1: case GDFA::SUtf8: {macro(s1); } break; \
  case GDFA::SUcs2: case GDFA::SUtf16: { macro(s2); } break; \
  case GDFA::SUcs4: { macro(s3); } break; \
  case GDFA::TAscii: { macro(t0); } break; \
  case GDFA::TLatin1: case GDFA::TUtf8: { macro(t1); } break; \
  case GDFA::TUcs2: case GDFA::TUtf16: { macro(t2); } break; \
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

#define UNINITIALIZED_GNFA(name) char _gnfa_##name##_buff[sizeof(GNFA)]; GNFA& name = brutal_cast<GNFA&>(_gnfa_##name##_buff[0]);

GDFA::GDFA()
{
#define macro(x) x = new typeof(*x);
    EACH_TYPE(macro)
#undef macro
}

GDFA::GDFA(const KDevPG::GDFA& o)
{
#define macro(x) x = new (typeof(*x))(*o.x);
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
#define macro(x) x = new typeof(*x);
  EACH_TYPE(macro)
#undef macro
}

GNFA::GNFA(const KDevPG::GNFA& o)
{
#define macro(x) x = new (typeof(*x))(*o.x);
  EACH_TYPE(macro)
#undef macro
}

GNFA::GNFA(const std::vector< GNFA* >& init)
{
#define macro(x) vector<typeof(*x)> vec(init.size()); for(size_t i = 0; i != init.size(); ++i) vec[i] = *(init[i]->x); x = new (typeof(*x))(vec);
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

GNFA& GNFA::operator<<=(const KDevPG::GNFA& o)
{
#define DO_SHIFT(x) *x <<= *o.x;
  EACH_TYPE(DO_SHIFT)
#undef DO_SHIFT
  return *this;
}

GNFA& GNFA::operator|=(const KDevPG::GNFA& o)
{
#define DO_OR(x) *x |= *o.x;
  EACH_TYPE(DO_OR)
#undef DO_OR
  return *this;
}

GNFA& GNFA::operator&=(const KDevPG::GNFA& o)
{
#define DO_AND(x) *x &= *o.x;
  EACH_TYPE(DO_AND)
#undef DO_AND
  return *this;
}

GNFA& GNFA::operator^=(const KDevPG::GNFA& o)
{
  #define DO_BUT(x) *x ^= *o.x;
  EACH_TYPE(DO_BUT)
  #undef DO_BUT
  return *this;
}

GNFA& GNFA::operator*()
{
#define DO_STAR(x) **x;
  EACH_TYPE(DO_STAR)
#undef DO_STAR
  return *this;
}

GNFA& GNFA::negate()
{
#define DO_NEGATE(x) x->negate();
  EACH_TYPE(DO_NEGATE)
#undef DO_NEGATE
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

GNFA GNFA::keyword(const QString& str)
{
#define macro(x) \
  GNFA r = GNFA::emptyWord(); \
  QByteArray qba(str.toUtf8()); \
  typedef typeof(*r.x) T; \
  Codec2FromUtf8Iterator<T::CharSet::codec>::Result iter(qba); \
  while(iter.hasNext()) \
  { \
    *r.x <<= (typeof(*r.x))(iter.next()); \
  } \
  return r;
  EACH_TYPE(macro)
#undef macro
}

GNFA GNFA::collection(const QString& str)
{
  UNINITIALIZED_GNFA(r);
#define macro(x) \
  QByteArray qba(str.toUtf8()); \
  typedef typeof(*r.x) T; \
  Codec2FromUtf8Iterator<T::CharSet::codec>::Result iter(qba); \
  while(iter.hasNext()) \
  { \
    *r.x |= (typeof(*r.x))(iter.next()); \
  } \
  return r;
  EACH_TYPE(macro)
#undef macro
}

GNFA GNFA::anyChar()
{
  // utf16 and utf8 support missing
  UNINITIALIZED_GNFA(ret);
#define macro(x) typedef typeof(*x) T; ret.x = new T(T::CharSet::fullSet());
  EACH_TYPE(macro)
#undef macro
  // remove the surrogate range
  if(GDFA::type == GDFA::TUcs2 || GDFA::type == GDFA::TUtf16)
  {
    *ret.t2 ^= NFA<TableCharSet<Ucs2> >(TableCharSet<Ucs2>::range(0xd800, 0xe000));
  }
  else if(GDFA::type == GDFA::SUcs2 || GDFA::type == GDFA::SUtf16)
  {
    *ret.s2 ^= NFA<SeqCharSet<Ucs2> >(SeqCharSet<Ucs2>::range(0xd800, 0xe000));
  }
  // add surrogate pairs
  if(GDFA::type == GDFA::SUtf16)
  {
    NFA<SeqCharSet<Ucs2> > surrpairs(SeqCharSet<Ucs2>::range(0xd800, 0xdc00));
    surrpairs <<= NFA<SeqCharSet<Ucs2> >(SeqCharSet<Ucs2>::range(0xdc00, 0xe000));
  }
  if(GDFA::type == GDFA::TUtf16)
  {
    NFA<TableCharSet<Ucs2> > surrpairs(TableCharSet<Ucs2>::range(0xd800, 0xdc00));
    surrpairs <<= NFA<TableCharSet<Ucs2> >(TableCharSet<Ucs2>::range(0xdc00, 0xe000));
  }
  // all valid utf-8 values
  if(GDFA::type == GDFA::SUtf8)
  {
    NFA<SeqCharSet<Latin1> > lowerBytes(SeqCharSet<Latin1>::range(0x80, 0xc0));
    NFA<SeqCharSet<Latin1> > ascii(SeqCharSet<Latin1>::range(0, 0x7f));
    NFA<SeqCharSet<Latin1> > topOf2(SeqCharSet<Latin1>::range(0xc0, 0xe0));
    NFA<SeqCharSet<Latin1> > topOf3(SeqCharSet<Latin1>::range(0xe0, 0xf0));
    NFA<SeqCharSet<Latin1> > topOf4(SeqCharSet<Latin1>::range(0xf0, 0x100));
    *ret.s1 = (ascii |= (topOf2 <<= lowerBytes) |= ((topOf3 <<= lowerBytes) <<= lowerBytes) |= (((topOf4 <<= lowerBytes) <<= lowerBytes) <<= lowerBytes));
  }
  if(GDFA::type == GDFA::TUtf8)
  {
    NFA<TableCharSet<Latin1> > lowerBytes(TableCharSet<Latin1>::range(0x80, 0xc0));
    NFA<TableCharSet<Latin1> > ascii(TableCharSet<Latin1>::range(0, 0x7f));
    NFA<TableCharSet<Latin1> > topOf2(TableCharSet<Latin1>::range(0xc0, 0xe0));
    NFA<TableCharSet<Latin1> > topOf3(TableCharSet<Latin1>::range(0xe0, 0xf0));
    NFA<TableCharSet<Latin1> > topOf4(TableCharSet<Latin1>::range(0xf0, 0x100));
    *ret.t1 = (ascii |= (topOf2 <<= lowerBytes) |= ((topOf3 <<= lowerBytes) <<= lowerBytes) |= (((topOf4 <<= lowerBytes) <<= lowerBytes) <<= lowerBytes));
  }
  return ret;
}

GNFA GNFA::emptyWord()
{
  UNINITIALIZED_GNFA(ret);
#define macro(x) typedef typeof(*ret.x) T; ret.x = new T(T::emptyWord());
  EACH_TYPE(macro)
#undef macro
  return ret;
}

GNFA GNFA::range(const quint32 begin, const quint32 end)
{
  // Utf32: take it
  // Latin1, Ascii, Ucs2: cut it
  // Utf8, Utf32: complicate
  UNINITIALIZED_GNFA(res);
  switch(GDFA::type)
  {
    case GDFA::SAscii: { res.s0 = new NFA<SeqCharSet<Ascii> >(begin >= 128 ? SeqCharSet<Ascii>::emptySet() : SeqCharSet<Ascii>::range(begin, min((quint32)128, end))); } break;
    case GDFA::SLatin1: { res.s1 = new NFA<SeqCharSet<Latin1> >(begin >= 256 ? SeqCharSet<Latin1>::emptySet() : SeqCharSet<Latin1>::range(begin, min((quint32)256, end))); } break;
    case GDFA::SUtf8: { 
      
    } break;
    case GDFA::SUcs2: {
      res.s2 = new NFA<SeqCharSet<Ucs2> >(begin >= 65536 ? SeqCharSet<Ucs2>::emptySet() : SeqCharSet<Ucs2>::range(begin, min((quint32)65536, end)).difference(SeqCharSet<Ucs2>::range(0xd800, 0xe000)));
    } break;
    case GDFA::SUtf16: {
      if(end >= 0x110000 || begin >= 0x110000)
      {
        res.s2 = new NFA<SeqCharSet<Ucs2> >();
      }
      else if(end < 65536)
      {
        if(begin <= 0xd800)
        {
          if(end <= begin)
          {
            res.s2 = new NFA<SeqCharSet<Ucs2> >();
          }
          else if(end > 0xe000)
          {
            res.s2 = new NFA<SeqCharSet<Ucs2> >(SeqCharSet<Ucs2>::range(begin, 0xd800).getUnion(SeqCharSet<Ucs2>::range(0xe000, end)));
          }
          else
          {
            res.s2 = new NFA<SeqCharSet<Ucs2> >(SeqCharSet<Ucs2>::range(begin, min(end, (quint32)0xd800)));
          }
        }
        else
        {
          auto mbegin = max(begin, (quint32)0xe000);
          if(end <= mbegin)
          {
            res.s2 = new NFA<SeqCharSet<Ucs2> >();
          }
          else
          {
            res.s2 = new NFA<SeqCharSet<Ucs2> >(SeqCharSet<Ucs2>::range(mbegin, end));
          }
        }
      }
      else if(begin >= 65536)
      {
        if(end <= begin)
        {
          res.s2 = new NFA<SeqCharSet<Ucs2> >();
        }
        else
        {
          // TODO
        }
      }
      else
      {
        if(end <= begin)
        {
          res.s2 = new NFA<SeqCharSet<Ucs2> >();
        }
        else if(begin < 0xd800)
        {
          res.s2 = new NFA<SeqCharSet<Ucs2> >(SeqCharSet<Ucs2>::range(begin, 0xd800).getUnion(SeqCharSet<Ucs2>::range(0xe000, 0x10000)));
          quint32 startHighSurrogate = 0xd800;
          quint32 startLowSurrogate = 0xdc00;
          quint32 lastHighSurrogate = (((end - 0x10000) & 0xffc00) >> 10) + 0xd800;
          quint32 lastLowSurrogate = ((end - 0x10000) & 0x3ff) + 0xdc00;
          if(lastLowSurrogate == 0xdfff)
          {
            auto surrPairs = NFA<SeqCharSet<Ucs2> >(SeqCharSet<Ucs2>::range(startHighSurrogate, lastHighSurrogate + 1));
            surrPairs <<= NFA<SeqCharSet<Ucs2> >(SeqCharSet<Ucs2>::range(startLowSurrogate, 0xe000));
            *res.s2 |= surrPairs;
          }
          else
          {
            if(lastHighSurrogate > startHighSurrogate)
            {
              auto firstPairs = NFA<SeqCharSet<Ucs2> >(SeqCharSet<Ucs2>::range(startHighSurrogate, lastHighSurrogate));
              firstPairs <<= NFA<SeqCharSet<Ucs2> >(SeqCharSet<Ucs2>::range(startLowSurrogate, 0xe000));
              *res.s2 |= firstPairs;
            }
            auto lastPairs = NFA<SeqCharSet<Ucs2> >(SeqCharSet<Ucs2>::range(lastHighSurrogate, lastHighSurrogate + 1));
            lastPairs <<= NFA<SeqCharSet<Ucs2> >(SeqCharSet<Ucs2>::range(startLowSurrogate, lastLowSurrogate + 1));
            *res.s2 |= lastPairs;
          }
        }
      }
    } break;
    case GDFA::SUcs4: { res.s3 = new NFA<SeqCharSet<Ucs4> >(SeqCharSet<Ucs4>::range(begin, end)); } break;
    case GDFA::TAscii: { res.t0 = new NFA<TableCharSet<Ascii> >(begin >= 128 ? TableCharSet<Ascii>::emptySet() : TableCharSet<Ascii>::range(begin, min((quint32)128, end))); } break;
    case GDFA::TLatin1: { res.t1 = new NFA<TableCharSet<Latin1> >(begin >= 256 ? TableCharSet<Latin1>::emptySet() : TableCharSet<Latin1>::range(begin, min((quint32)256, end))); } break;
    case GDFA::TUtf8: { 
      
    } break;
    case GDFA::TUcs2: {
      res.t2 = new NFA<TableCharSet<Ucs2> >(begin >= 65536 ? TableCharSet<Ucs2>::emptySet() : TableCharSet<Ucs2>::range(begin, min((quint32)65536, end)).difference(TableCharSet<Ucs2>::range(0xd800, 0xe000)));
    }
    case GDFA::TUtf16: {
      
    } break;
    default: exit(-1);
  }
  // warning if empty
}

typeof(GDFA::type) GDFA::type = GDFA::SUcs2;

template<CharEncoding enc>
const bitset<TableCharSet<enc>::nChars> TableCharSet<enc>::nullData = bitset<TableCharSet<enc>::nChars>();

}
