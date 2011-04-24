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


/**
 * Deterministic finite automaton.
 */
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
    /// Code used for the detected tokens in the generated code
    void setActions(const vector<QString>& _actions)
    {
      actions = _actions;
      numActions = actions.size() - 1;
    }
    /// Generate code for transitions
    void codegen(QTextStream& str)
    {
      CharSetCondition<CharSet> csc;
      for(size_t i = 0; i != nstates; ++i)
      {
        str << "\n_state_" + QString::number(i) + ":\n";
        if(accept[i])
          str << "lpos = CURR_POS; lstate = " << accept[i] << ";\n";
        str << "NEXT_CHR(chr); ";
        csc(str, rules[i]);
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
    /// Debugging output
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
        cout << "}" << endl;
    }
    /// Test if the string matches the regexp
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
    /// Can be used to test tokenization
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
    /// Remove each state x iff ¬active[x]
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
            auto orules = rules[i];
            rules[i].clear();
            for(auto j = orules.begin(); j != orules.end(); ++j)
            {
                if(active[j->second])
                  rules[i].push_back(make_pair(j->first, mapping[j->second]));
            }
        }
        return *this;
    }
    /// Eliminate each state unarrivable from the start
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
    /// Eliminate each state iff no final state is  arivable from it
    DFA<CharSet>& eliminateInactiveStates()
    {
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
        eliminateInactiveStates();
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
            vector<CharSet> mapping(nstates, CharSet::emptySet());
            foreach(NC(const pair<CharSet, size_t>& j), rules[i])
                mapping[j.second].unite(j.first);
            rules[i].clear();
            for(size_t j = 0; j != nstates; ++j)
                if(!mapping[j].empty())
                    rules[i].push_back(make_pair(mapping[j], j));
        }
        eliminateUnarrivableStates();
        eliminateInactiveStates();
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
        cout << "}" << endl;
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
      ret.accept = 0;
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
    bool acceptsEpsilon() const
    {
      stack<size_t> todo;
      todo.push(0);
      UsedBitArray vis(nstates);
      vis[0] = true;
      while(!todo.empty())
      {
        size_t curr = todo.top();
        todo.pop();
        if(curr >= accept)
          return true;
        foreach(const auto& nx, rules[curr])
        {
          if(nx.first.epsilon() && !vis[nx.second])
          {
            vis[nx.second] = true;
            todo.push(nx.second);
          }
        }
      }
      return false;
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
      }
      tmp.accept.push_back(1);
      for(auto i = tmp.rules.begin(); i != tmp.rules.end(); ++i)
      {
        CharSet successSet = CharSet::fullSet();
        for(auto j = i->begin(); j != i->end(); ++j)
        {
          CharSet tmp = j->first;
          tmp.negate();
          successSet.intersect(tmp);
        }
        if(!successSet.empty())
          i->push_back(make_pair(successSet, tmp.nstates - 1));
      }
      tmp.eliminateUnarrivableStates();
      tmp.eliminateInactiveStates();
      return *this = tmp.nfa();
    }
    NFA<CharSet>& operator&=(const NFA<CharSet>& o)
    {
      NFA<CharSet> _o = o;
      _o.negate();
      negate();
      *this |= _o;
      negate();
      return *this;
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
  if(nstates == 0)
    return ret;
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
  if(ret.nstates == nstates)
  {
    ++ret.nstates;
    ret.rules.push_back(vector<pair<CharSet, size_t> >());
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

void GDFA::inspect()
{
  #define DO_INSPECT(x) x->inspect();
  EACH_TYPE(DO_INSPECT)
  #undef DO_INSPECT
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

bool GNFA::acceptsEpsilon() const
{
#define DO_AE(x) return x->acceptsEpsilon();
  EACH_TYPE(DO_AE)
#undef DO_AE
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

GNFA& GNFA::minimize()
{
#define DO_MINIMIZE(x) *x = x->dfa().minimize().nfa();
  EACH_TYPE(DO_MINIMIZE)
#undef DO_MINIMIZE
  return *this;
}

void GNFA::inspect()
{
#define DO_INSPECT(x) x->inspect();
  EACH_TYPE(DO_INSPECT)
#undef DO_INSPECT
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
  GNFA r;
  QUtf16ToUcs4Iterator iter(str);
  while(iter.hasNext())
  {
    quint32 next = iter.next();
    r |= range(next, next+1);
  }
  return r;
}

GNFA GNFA::anyChar()
{
  // utf16 and utf8 support missing
  UNINITIALIZED_GNFA(ret);
#define macro(x) typedef typeof(*x) T; ret.x = new T(T::CharSet::fullSet());
  EACH_TYPE(macro)
#undef macro
  // remove the surrogate range
  if(/*GDFA::type == GDFA::TUcs2 || */GDFA::type == GDFA::TUtf16)
  {
    *ret.t2 ^= NFA<TableCharSet<Ucs2> >(TableCharSet<Ucs2>::range(0xd800, 0xe000));
  }
  else if(/*GDFA::type == GDFA::SUcs2 || */GDFA::type == GDFA::SUtf16)
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

template<template<CharEncoding> class CharSet, typename... T>
NFA<CharSet<Latin1> > getUtf8Tuples(T... args);

template<template<CharEncoding> class CharSet, typename... Args>
struct GetUtf8Tuples
{
  static_assert((sizeof...(Args)) == 0 || (sizeof...(Args)) != 0, "GetUtf8Tuples takes only codepoints");
};

template<template<CharEncoding> class CharSet>
struct GetUtf8Tuples<CharSet, typename Codec2Int<Latin1>::Result, typename Codec2Int<Latin1>::Result>
{
  typedef typename Codec2Int<Latin1>::Result Int;
  static NFA<CharSet<Latin1> > exec(Int from0, Int to0)
  {
    return NFA<CharSet<Latin1> >(CharSet<Latin1>::range(from0, to0));
  }
};

template<template<CharEncoding> class CharSet, typename... Args>
struct GetUtf8Tuples<CharSet, typename Codec2Int<Latin1>::Result, typename Codec2Int<Latin1>::Result, typename Codec2Int<Latin1>::Result, typename Codec2Int<Latin1>::Result, Args...>
{
  typedef typename Codec2Int<Latin1>::Result Int;
  static NFA<CharSet<Latin1> > exec(Int from0, Int to0, Int from1, Int to1, Args... rest)
  {
    if(from0 == to0)
    {
      auto tuples = NFA<CharSet<Latin1> >(CharSet<Latin1>(from0));
      tuples <<= getUtf8Tuples<CharSet>(from1, to1, rest...);
      return tuples;
    }
    else
    {
      NFA<CharSet<Latin1> > tuples;
      auto firstTuples = NFA<CharSet<Latin1> >(CharSet<Latin1>(from0));
      firstTuples <<= getUtf8Tuples<CharSet>(from1, Int(0x80 + (1<<6)), rest...);
      tuples |= firstTuples;
      auto midTuples = NFA<CharSet<Latin1> >(CharSet<Latin1>::range(from0 + 1, to0));
      midTuples <<= getUtf8Tuples<CharSet>(Int(0x80), Int(0x80 + (1<<6)), rest...);
      tuples |= midTuples;
      auto lastTuples = NFA<CharSet<Latin1> >(CharSet<Latin1>(to0));
      lastTuples <<= getUtf8Tuples<CharSet>(Int(0x80), to1, rest...);
      tuples |= lastTuples;
      return tuples;
    }
  }
};

template<template<CharEncoding> class CharSet, typename... T>
NFA<CharSet<Latin1> > getUtf8Tuples(T... args)
{
  return GetUtf8Tuples<CharSet, T...>::exec(args...);
}

template<template<CharEncoding> class CharSet>
void addUtf8Range(NFA<CharSet<Latin1> >& res, quint32 begin, quint32 end)
{
  typedef typename Codec2Int<Latin1>::Result Int;
  Int from0, from1, from2, from3, to0, to1, to2, to3;
  if(begin < 0x80)
  {
    if(end <= 0x80)
    {
      res |= getUtf8Tuples<CharSet>(Int(begin), Int(end));
      return;
    }
    res |= getUtf8Tuples<CharSet>(Int(begin), Int(0x80));
    begin = 0x80;
  }
  if(begin < 0x800)
  {
    from1 = (begin & 0x3f) + 0x80;
    from0 = (begin >> 6) + 0xc0;
    Int to0, to1;
    if(end <= 0x800)
    {
      to1 = (end & 0x3f) + 0x80;
      to0 = (end >> 6) + 0xc0;
    }
    else
    {
      to1 = 0x80 + (1<<6);
      to0 = 0xc0 + (1<<5);
    }
    res |= getUtf8Tuples<CharSet>(from0, to0, from1, to1);
    if(end <= 0x800)
      return;
    begin = 0x800;
  }
  if(begin < 0x10000)
  {
    from2 = (begin & 0x3f) + 0x80;
    from1 = ((begin >> 6) & 0x3f) + 0x80;
    from0 = (begin >> 12) + 0xe0;
    if(end <= 0x10000)
    {
      to2 = (end & 0x3f) + 0x80;
      to1 = ((end >> 6) & 0x3f) + 0x80;
      to0 = (end >> 12) + 0xe0;
    }
    else
    {
      to2 = to1 = 0x80 + (1<<6);
      to0 = 0xe0 + (1 << 4);
    }
    res |= getUtf8Tuples<CharSet>(from0, to0, from1, to1, from2, to2);
    if(end <= 0x10000)
      return;
    begin = 0x10000;
  }
  from3 = (begin & 0x3f) + 0x80;
  from2 = ((begin >> 6) & 0x3f) + 0x80;
  from1 = ((begin >> 12) & 0x3f) + 0x80;
  from0 = (begin >> 18) + 0xf0;
  to3 = (end & 0x3f) + 0x80;
  to2 = ((end >> 6) & 0x3f) + 0x80;
  to1 = ((end >> 12) & 0x3f) + 0x80;
  to0 = (end >> 18) + 0xf0;
  res |= getUtf8Tuples<CharSet>(from0, to0, from1, to1, from2, to2, from3, to3);
}

GNFA GNFA::range(quint32 begin, quint32 end)
{
  // Utf32: take it
  // Latin1, Ascii, Ucs2: cut it
  // Utf8, Utf32: complicate
  UNINITIALIZED_GNFA(res);
  switch(GDFA::type)
  {
    case GDFA::SAscii: { res.s0 = new NFA<SeqCharSet<Ascii> >(begin >= 0x80 ? SeqCharSet<Ascii>::emptySet() : SeqCharSet<Ascii>::range(begin, min((quint32)0x80, end))); } break;
    case GDFA::SLatin1: { res.s1 = new NFA<SeqCharSet<Latin1> >(begin >= 0x100 ? SeqCharSet<Latin1>::emptySet() : SeqCharSet<Latin1>::range(begin, min((quint32)0x100, end))); } break;
    case GDFA::SUtf8: {
      res.s1 = new NFA<SeqCharSet<Latin1> >();
      addUtf8Range(*res.s1, begin, end);
    } break;
    case GDFA::SUcs2: {
      res.s2 = new NFA<SeqCharSet<Ucs2> >(begin >= 0x10000 ? SeqCharSet<Ucs2>::emptySet() : SeqCharSet<Ucs2>::range(begin, min((quint32)0x10000, end))/*.difference(SeqCharSet<Ucs2>::range(0xd800, 0xe000))*/);
    } break;
    case GDFA::SUtf16: {
#define UTF16_IMPL(CS, field) \
      if(end >= 0x110000 || begin >= 0x110000)                                          \
      {                                                                                 \
        res.field = new NFA<CS<Ucs2> >();                                          \
      }                                                                                 \
      else if(end < 0x10000)                                                            \
      {                                                                                 \
        if(begin <= 0xd800)                                                             \
        {                                                                               \
          if(end <= begin)                                                              \
          {                                                                             \
            res.field = new NFA<CS<Ucs2> >();                                      \
          }                                                                             \
          else if(end > 0xe000)                                                         \
          {                                                                             \
            res.field = new NFA<CS<Ucs2> >(CS<Ucs2>::range(begin, 0xd800).getUnion(CS<Ucs2>::range(0xe000, end))); \
          }                                                                             \
          else                                                                          \
          {                                                                             \
            res.field = new NFA<CS<Ucs2> >(CS<Ucs2>::range(begin, min(end, (quint32)0xd800))); \
          }\
        }\
        else\
        {\
          auto mbegin = max(begin, (quint32)0xe000);\
          if(end <= mbegin)\
          {\
            res.field = new NFA<CS<Ucs2> >();\
          }\
          else\
          {\
            res.field = new NFA<CS<Ucs2> >(CS<Ucs2>::range(mbegin, end));\
          }\
        }\
      }\
      else if(begin >= 0x10000)\
      {\
        if(end <= begin)\
        {\
          res.field = new NFA<CS<Ucs2> >();\
        }\
        else\
        {\
          quint32 startHighSurrogate = (((begin - 0x10000) & 0xffc00) >> 10) + 0xd800;\
          quint32 startLowSurrogate = ((begin - 0x10000) & 0x3ff) + 0xdc00;\
          quint32 endHighSurrogate = (((end - 0x10000) & 0xffc00) >> 10) + 0xd800;\
          quint32 endLowSurrogate = ((end - 0x10000) & 0x3ff) + 0xdc00;\
          if(endLowSurrogate == 0xdc00)\
          {\
            if(startLowSurrogate == 0xdc00)\
            {\
              res.field = new NFA<CS<Ucs2> >(CS<Ucs2>::range(startHighSurrogate, endHighSurrogate));\
              *res.field <<= NFA<CS<Ucs2> >(CS<Ucs2>::range(0xdc00, 0xe000));\
            }\
            else\
            {\
              auto firstPairs = NFA<CS<Ucs2> >(CS<Ucs2>::range(startHighSurrogate, startHighSurrogate + 1));\
              firstPairs <<= NFA<CS<Ucs2> >(CS<Ucs2>::range(startLowSurrogate, 0xe000));\
              res.field = new NFA<CS<Ucs2> >(firstPairs);\
              if(startHighSurrogate < endHighSurrogate)\
              {\
                auto surrPairs = NFA<CS<Ucs2> >(CS<Ucs2>::range(startHighSurrogate + 1, endHighSurrogate + 1));\
                surrPairs <<= NFA<CS<Ucs2> >(CS<Ucs2>::range(0xdc00, 0xe000));\
                *res.field |= surrPairs;\
              }\
            }\
          }\
          else\
          {\
            if(startLowSurrogate == 0xdc00)\
            {\
              res.field = new NFA<CS<Ucs2> >(CS<Ucs2>::range(startHighSurrogate, endHighSurrogate));\
            }\
            else\
            {\
              res.field = new NFA<CS<Ucs2> >(CS<Ucs2>::range(startHighSurrogate, startHighSurrogate + 1));\
              *res.field <<= NFA<CS<Ucs2> >(CS<Ucs2>::range(startLowSurrogate, (startHighSurrogate == endHighSurrogate ? endLowSurrogate : 0xe000)));\
              if(startHighSurrogate != endHighSurrogate)\
              {\
                if(startHighSurrogate + 1 != endHighSurrogate)\
                {\
                  auto midPairs = NFA<CS<Ucs2> >(CS<Ucs2>::range(startHighSurrogate + 1, endHighSurrogate));\
                  midPairs <<= NFA<CS<Ucs2> >(CS<Ucs2>::range(startLowSurrogate, 0xe000));\
                  *res.field |= midPairs;\
                }\
                auto lastPairs = NFA<CS<Ucs2> >(CS<Ucs2>::range(endHighSurrogate, endHighSurrogate + 1));\
                lastPairs <<= NFA<CS<Ucs2> >(CS<Ucs2>::range(startLowSurrogate, endLowSurrogate));\
                *res.field |= lastPairs;\
              }\
            }\
          }\
        }\
      }\
      else\
      {\
        if(end <= begin)\
        {\
          res.field = new NFA<CS<Ucs2> >();\
        }\
        else\
        {\
          if(begin < 0xd800)\
          {\
            res.field = new NFA<CS<Ucs2> >(CS<Ucs2>::range(begin, 0xd800).getUnion(CS<Ucs2>::range(0xe000, 0x10000)));\
          }\
          else\
          {\
            res.field = new NFA<CS<Ucs2> >(CS<Ucs2>::range(max(begin, 0xe000u), 0x10000));\
          }\
          quint32 startHighSurrogate = 0xd800;\
          quint32 startLowSurrogate = 0xdc00;\
          quint32 endHighSurrogate = (((end - 0x10000) & 0xffc00) >> 10) + 0xd800;\
          quint32 endLowSurrogate = ((end - 0x10000) & 0x3ff) + 0xdc00;\
          if(endLowSurrogate == 0xdc00)\
          {\
            auto surrPairs = NFA<CS<Ucs2> >(CS<Ucs2>::range(startHighSurrogate, endHighSurrogate));\
            surrPairs <<= NFA<CS<Ucs2> >(CS<Ucs2>::range(startLowSurrogate, 0xe000));\
            *res.field |= surrPairs;\
          }\
          else\
          {\
            if(endHighSurrogate > startHighSurrogate)\
            {\
              auto midPairs = NFA<CS<Ucs2> >(CS<Ucs2>::range(startHighSurrogate, endHighSurrogate));\
              midPairs <<= NFA<CS<Ucs2> >(CS<Ucs2>::range(startLowSurrogate, 0xe000));\
              *res.field |= midPairs;\
            }\
            auto lastPairs = NFA<CS<Ucs2> >(CS<Ucs2>::range(endHighSurrogate, endHighSurrogate + 1));\
            lastPairs <<= NFA<CS<Ucs2> >(CS<Ucs2>::range(startLowSurrogate, endLowSurrogate));\
            *res.field |= lastPairs;\
          }\
        }\
      }
      UTF16_IMPL(SeqCharSet, s2)
    } break;
    case GDFA::SUcs4: { res.s3 = new NFA<SeqCharSet<Ucs4> >(SeqCharSet<Ucs4>::range(begin, end)); } break;
    case GDFA::TAscii: { res.t0 = new NFA<TableCharSet<Ascii> >(begin >= 0x80 ? TableCharSet<Ascii>::emptySet() : TableCharSet<Ascii>::range(begin, min((quint32)0x80, end))); } break;
    case GDFA::TLatin1: { res.t1 = new NFA<TableCharSet<Latin1> >(begin >= 0x100 ? TableCharSet<Latin1>::emptySet() : TableCharSet<Latin1>::range(begin, min((quint32)0x100, end))); } break;
    case GDFA::TUtf8: {
      res.t1 = new NFA<TableCharSet<Latin1> >();
      addUtf8Range(*res.t1, begin, end);
    } break;
    case GDFA::TUcs2: {
      res.t2 = new NFA<TableCharSet<Ucs2> >(begin >= 0x10000 ? TableCharSet<Ucs2>::emptySet() : TableCharSet<Ucs2>::range(begin, min((quint32)0x10000, end))/*.difference(TableCharSet<Ucs2>::range(0xd800, 0xe000))*/);
    }
    case GDFA::TUtf16: {
      UTF16_IMPL(TableCharSet, t2)
      #undef UTF16_IMPL
    } break;
    default: exit(-1);
  }
  // TODO: warning if empty
  return res;
}

KDevPG::GNFA KDevPG::GNFA::character(quint32 codepoint)
{
  return range(codepoint, codepoint+1);
}

typeof(GDFA::type) GDFA::type = GDFA::SUcs2;

template<CharEncoding enc>
const typename TableCharSet<enc>::BitArray TableCharSet<enc>::nullData = bitset<TableCharSet<enc>::nChars>();

}
