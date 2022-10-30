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
#include "kdev-pg-bit-array.h"
#include <iostream>
#include <queue>
#include <stack>
#include <QHash>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// TODO: Lookahead operator
// TODO: Line-End etc.
// TODO: Deactivate/activate rules (have to keep the bitsets of possible final states)


#define q_Hash_to_tr1_hash(type) \
namespace std                                               \
{                                                           \
    template<> struct hash< type >                          \
    {                                                       \
      inline size_t operator()(const type &x) const         \
      {                                                     \
        return qHash(x);                                    \
      }                                                     \
    };                                                      \
}

#if (QT_VERSION < QT_VERSION_CHECK(5, 14, 0))
// Qt >= 5.14 already has std::hash for QBitArray
q_Hash_to_tr1_hash(QBitArray)
#endif

namespace KDevPG
{

typedef BitArray UsedBitArray;
typedef QUtf8ToUcs4Iterator Iterator;
// typedef TableCharSet<Ascii> CharSet;

template<typename CharSet> class NFA;

inline QString codeForDot(QString str)
{
  QString out = "";
  int pos = 0;
  forever
  {
    int npos = str.indexOf("\n\01!ASIgnore\"!!\n# ", pos);
    if(npos == -1)
    {
      out += QStringView(str).mid(pos);
      break;
    }
    out += QStringView(str).mid(pos, npos - pos);
    int nlpos = str.indexOf('\n', npos + 17);
    int codeendpos = str.indexOf("\n\01!AS/Ignore\"!!\n", nlpos);
    if(nlpos == -1 || codeendpos == -1)
    {
      out += "<junk>";
      break;
    }
    out += QStringView(str).mid(nlpos + 1, codeendpos - nlpos - 1);
    pos = codeendpos + 17;
  }
  return out.replace('\"', "\\\"").replace('\n', '\t').trimmed();
}

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
      str << "goto _state_0; // no warning about unused label\n";
      CharSetCondition<CharSet> csc;
      for(size_t i = 0; i != nstates; ++i)
      {
        str << "\n_state_" + QString::number(i) + ":\n";
        if(accept[i])
          str << "lpos = lxCURR_POS; lstate = " << accept[i] << ";\n";
        str << "lxNEXT_CHR(chr); ";
        csc(str, rules[i]);
      }
      str << "_end:\nplain() = lpos;\nswitch(lstate) {\n";
      for(size_t i = 0; i <= numActions; ++i)
      {
        str << "case " << QString::number(i) << ": ";
        if(i == 0)
          str << "goto _fail; // no warning about unused label\n_fail: ";
        str << "{" << actions[i] << "\nlxFINISH\n}\n";
      }
      str << "}\n";
    }
    /// .dot-output
    void dotOutput(QTextStream& out, const QString& name)
    {
      out << "digraph " << name << "{" << Qt::endl;
      for(size_t i = 0; i != nstates; ++i)
      {
        out << "s" << i << " [ label = \"" << i << "\"";
        if(i == 0)
          out << ", shape=rect, style=rounded";
        else
          out << ", shape=oval";
        if(accept[i] != 0)
          out << ", penwidth=4";
        out << " ];" << Qt::endl;
      }
      for(size_t i = 1; i <= numActions; ++i)
      {
        out << "f" << i << " [ label = \"" << codeForDot(actions[i]) << "\", shape=rect, penwidth=2 ];" << Qt::endl;
      }
      for(size_t i = 0; i != nstates; ++i)
      {
        for(auto j = rules[i].begin(); j != rules[i].end(); ++j)
        {
          out << "s" << i << " -> " << "s" << j->second << " [ label = \"" << j->first << "\" ];" << Qt::endl;
        }
        if(accept[i] != 0)
        {
          out << "s" << i << " -> " << "f" << accept[i] << ";" << Qt::endl;
        }
      }
      out << "}" << Qt::endl;
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
        foreach(const QChar c, str)
        {
            for(const auto& r : rules[state])
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
        for(const auto& r : rules[state])
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
            for(const auto& i : rules[curr])
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
        for(const auto& i : rules[x])
            xsets[ogroups[i.second]].unite(i.first);
        for(const auto& i : rules[y])
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
            for(const auto& j : rules[i])
                _rules[groups[i]].push_back(make_pair(j.first, groups[j.second]));
        }
        rules = _rules;
        nstates = grinv.size();
        accept = _accept;
        for(size_t i = 0; i != nstates; ++i)
        {
            vector<CharSet> mapping(nstates, CharSet::emptySet());
            for(const auto& j : rules[i])
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
    void dotOutput(QTextStream& out, const QString& name)
    {
      out << "digraph " << name << "{" << Qt::endl;
      for(size_t i = 0; i != nstates; ++i)
      {
        out << "s" << i << " [ label = \"" << i << "\"";
        if(i == 0)
          out << ", shape=rect, style=rounded";
        else
          out << ", shape=oval";
        if(i >= accept)
          out << ", penwidth=4";
        out << " ];" << Qt::endl;
      }
      for(size_t i = 0; i != nstates; ++i)
      {
        for(auto j = rules[i].begin(); j != rules[i].end(); ++j)
        {
          out << "s" << i << " -> " << "s" << j->second << " [ label = \"" << j->first << "\" ];" << Qt::endl;
        }
      }
      out << "}" << Qt::endl;
    }
    /**
     * Accepts no words.
     */
    NFA() : nstates(2), rules(2), accept(1)
    {}
    static NFA<CharSet> emptyWord()
    {
      NFA<CharSet> res;
      res.nstates = 1;
      res.rules.resize(1);
      res.accept = 0;
      return res;
    }
    NFA(const NFA<CharSet>& o) : nstates(o.nstates), rules(o.rules), accept(o.accept)
    {}
    NFA(const CharSet& set) : nstates(2), rules(2), accept(1)
    {
        rules[0].push_back(make_pair(set, 1));
    }
    explicit NFA(const std::vector<NFA<CharSet> >& list)
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
    UsedBitArray closure(const UsedBitArray& states)
    {
        UsedBitArray s(states);
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
        UsedBitArray res(a);
        for(size_t i = 0; i != a.size(); ++i)
            res[i] = res[i] || b[i];
        return res;
    }
    vector< pair<CharSet, UsedBitArray > > follow(const UsedBitArray& states)
    {
        UsedBitArray s(states);
        vector<pair<CharSet, UsedBitArray > > pr(nstates);
        for(size_t i = 0; i != nstates; ++i)
        {
            if(s[i])
            {
                for(const auto& r : rules[i])
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
        unordered_set<UsedBitArray> states;
        unordered_map<UsedBitArray, vector<pair<CharSet, UsedBitArray > > > rules;
        stack<UsedBitArray > todo;
        UsedBitArray start(nstates);
        start[0] = true;
        start = closure(start);
        todo.push(start);
        while(todo.size())
        {
            UsedBitArray x = todo.top();
            todo.pop();
            states.insert(x);
            rules[x];
            vector<pair<CharSet, UsedBitArray > > nxt = follow(x);
            for(const auto& nx : nxt)
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
        unordered_map<UsedBitArray, size_t> st;
        size_t cnt = 0;
        foreach(const UsedBitArray& i, states)
        {
            if(i == start && cnt)
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
            for(const auto& nx : i->second)
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
    bool isEmpty() const
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
          return false;
        foreach(const auto& nx, rules[curr])
        {
          if(!vis[nx.second])
          {
            vis[nx.second] =true;
            todo.push(nx.second);
          }
        }
      }
      return true;
    }
    int minLength() const
    {
      queue<size_t> _todo0, _todo1;
      queue<size_t> *todo0 = &_todo0, *todo1 = &_todo1;
      todo0->push(0);
      UsedBitArray vis(nstates);
      vis[0] = true;
      int length = 0;
      while(!todo0->empty())
      {
        size_t curr = todo0->front();
        todo0->pop();
        if(curr >= accept)
          return length;
        foreach(const auto& nx, rules[curr])
        {
          if(!vis[nx.second])
          {
            vis[nx.second] = true;
            if(nx.first.epsilon())
              todo0->push(nx.second);
            else
              todo1->push(nx.second);
          }
        }
        if(todo0->empty())
        {
          ++length;
          swap(todo0, todo1);
        }
      }
      return -1;
    }
private:
    bool unboundedCheck(size_t x, UsedBitArray& vis) const
    {
      vis[x] = true;
      foreach(const auto& nx, rules[x])
      {
        if(vis[nx.second])
          return true;
        else
          if(unboundedCheck(nx.second, vis))
            return true;
      }
      vis[x] = false;
      return false;
    }
public:
    bool isUnbounded() const
    {
      UsedBitArray vis(nstates);
      return unboundedCheck(0, vis);
    }
    int maxLength() const
    {
      // assumes that there are no circle unarrivable from start
      if(isUnbounded())
        return -2;
      if(isEmpty())
        return -1;
      queue<size_t> _todo0, _todo1;
      queue<size_t> *todo0 = &_todo0, *todo1 = &_todo1;
      vector<int> dist(nstates, -1);
      vector<vector<pair<CharSet, size_t> > > brules(nstates);
      for(size_t i = 0; i != nstates; ++i)
      {
        foreach(const auto& nx, rules[i])
        {
          brules[nx.second].push_back(nx);
          brules[nx.second].back().second = i;
        }
      }
      for(size_t i = accept; i != nstates; ++i)
      {
        todo0->push(i);
        dist[i] = 0;
      }
      int length = 0;
      while(!todo0->empty())
      {
        size_t curr = todo0->front();
        todo0->pop();
        foreach(const auto& nx, brules[curr])
        {
          if(nx.first.epsilon())
          {
            if(dist[nx.second] < length)
            {
              dist[nx.second] = length;
              todo0->push(nx.second);
            }
          }
          else
          {
            if(dist[nx.second] <= length)
            {
              dist[nx.second] = length + 1;
              todo1->push(nx.second);
            }
          }
        }
        if(todo0->empty())
        {
          ++length;
          swap(todo0, todo1);
        }
      }
      return dist[0];
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
  NFA<CharSet> res;
  if(nstates == 0)
    return res;
  res.nstates = nstates;
  res.rules = rules;
  res.accept = nstates;
  for(size_t i = 0; i != nstates; ++i)
  {
    if(nstates + accept[i] > res.nstates)
    {
      res.nstates = nstates + accept[i];
      res.rules.resize(res.nstates);
    }
    if(accept[i] != 0)
      res.rules[i].push_back(make_pair(CharSet(), nstates + accept[i] - 1));
  }
  if(res.nstates == nstates)
  {
    ++res.nstates;
    res.rules.push_back(vector<pair<CharSet, size_t> >());
  }
  return res;
}

// notice: utf8/8bit and utf16/ucs2 do not require different NFAs and DFAs
#define EACH_TYPE(macro) \
switch(GDFA::type) \
{ \
  case SAscii: { typedef SeqCharSet<Ascii> T; macro(s0); } break; \
  case SLatin1: case SUtf8: { typedef SeqCharSet<Latin1> T; macro(s1); } break; \
  case SUcs2: case SUtf16: { typedef SeqCharSet<Ucs2> T; macro(s2); } break; \
  case SUcs4: { typedef SeqCharSet<Ucs4> T; macro(s3); } break; \
  case TAscii: { typedef TableCharSet<Ascii> T; macro(t0); } break; \
  case TLatin1: case TUtf8: { typedef TableCharSet<Latin1> T; macro(t1); } break; \
  case TUcs2: case TUtf16: { typedef TableCharSet<Ucs2> T; macro(t2); } break; \
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
#define macro(x) x = new DFA<T>;
    EACH_TYPE(macro)
#undef macro
}

GDFA::GDFA(const KDevPG::GDFA& o)
{
#define macro(x) x = new DFA<T>(*o.x);
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

void GDFA::dotOutput(QTextStream& o, const QString& name)
{
#define DO_DOT(x) x->dotOutput(o, name);
  EACH_TYPE(DO_DOT)
#undef DO_DOT
}

GNFA GDFA::nfa()
{
  GNFA res;
#define DO_NFA(x) res.x = new NFA<T>(x->nfa());
  EACH_TYPE(DO_NFA)
#undef DO_NFA
  return res;
}

GNFA::GNFA()
{
  /* no initialization */
}

GNFA::GNFA(const KDevPG::GNFA& o)
{
#define macro(x) x = new NFA<T>(*o.x);
  EACH_TYPE(macro)
#undef macro
}

GNFA::GNFA(const std::vector< GNFA* >& init)
{
#define macro(x) vector< NFA<T> > vec(init.size()); for(size_t i = 0; i != init.size(); ++i) vec[i] = *(init[i]->x); x = new NFA<T>(vec);
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

bool GNFA::isEmpty() const
{
#define DO_IE(x) return x->isEmpty();
  EACH_TYPE(DO_IE)
#undef DO_IE
}

bool GNFA::isUnbounded() const
{
#define DO_IU(x) return x->isUnbounded();
  EACH_TYPE(DO_IU)
#undef DO_IU
}

int GNFA::minLength() const
{
#define DO_ML(x) return x->minLength();
  EACH_TYPE(DO_ML)
#undef DO_ML
}

int GNFA::maxLength() const
{
  #define DO_ML(x) return x->maxLength();
  EACH_TYPE(DO_ML)
  #undef DO_ML
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
  *this = dfa().minimize().nfa();
  return *this;
}

void GNFA::inspect()
{
#define DO_INSPECT(x) x->inspect();
  EACH_TYPE(DO_INSPECT)
#undef DO_INSPECT
}

void GNFA::dotOutput(QTextStream& o, const QString& name)
{
#define DO_DOT(x) x->dotOutput(o, name);
  EACH_TYPE(DO_DOT)
#undef DO_DOT
}

GDFA GNFA::dfa()
{
  GDFA res;
#define macro(x) *res.x = x->dfa();
  EACH_TYPE(macro)
#undef macro
  return res;
}

GNFA GNFA::empty()
{
  GNFA res;
#define macro(x) res.x = new NFA<T>;
  EACH_TYPE(macro)
#undef macro
  return res;
}

GNFA GNFA::word(const QString& str)
{
#define macro(x) \
  GNFA res = GNFA::emptyWord(); \
  QByteArray qba(str.toUtf8()); \
  Codec2FromUtf8Iterator<T::codec>::Result iter(qba); \
  while(iter.hasNext()) \
  { \
    *res.x <<= T(iter.next()); \
  } \
  return res;
  EACH_TYPE(macro)
#undef macro
}

GNFA GNFA::collection(const QString& str)
{
  GNFA res = GNFA::empty();
  QUtf16ToUcs4Iterator iter(str);
  while(iter.hasNext())
  {
    quint32 next = iter.next();
    res |= range(next, next+1);
  }
  return res;
}

GNFA GNFA::anyChar()
{
  GNFA res;
#define macro(x) res.x = new NFA<T>(T::fullSet());
  EACH_TYPE(macro)
#undef macro
  // remove the surrogate range
  if(/*GDFA::type == TUcs2 || */GDFA::type == TUtf16)
  {
    *res.t2 ^= NFA<TableCharSet<Ucs2> >(TableCharSet<Ucs2>::range(0xd800, 0xe000));
  }
  else if(/*GDFA::type == SUcs2 || */GDFA::type == SUtf16)
  {
    *res.s2 ^= NFA<SeqCharSet<Ucs2> >(SeqCharSet<Ucs2>::range(0xd800, 0xe000));
  }
  // add surrogate pairs
  if(GDFA::type == SUtf16)
  {
    NFA<SeqCharSet<Ucs2> > surrpairs(SeqCharSet<Ucs2>::range(0xd800, 0xdc00));
    surrpairs <<= NFA<SeqCharSet<Ucs2> >(SeqCharSet<Ucs2>::range(0xdc00, 0xe000));
  }
  if(GDFA::type == TUtf16)
  {
    NFA<TableCharSet<Ucs2> > surrpairs(TableCharSet<Ucs2>::range(0xd800, 0xdc00));
    surrpairs <<= NFA<TableCharSet<Ucs2> >(TableCharSet<Ucs2>::range(0xdc00, 0xe000));
  }
  // all valid utf-8 values
  if(GDFA::type == SUtf8)
  {
    NFA<SeqCharSet<Latin1> > lowerBytes(SeqCharSet<Latin1>::range(0x80, 0xc0));
    NFA<SeqCharSet<Latin1> > ascii(SeqCharSet<Latin1>::range(0, 0x7f));
    NFA<SeqCharSet<Latin1> > topOf2(SeqCharSet<Latin1>::range(0xc0, 0xe0));
    NFA<SeqCharSet<Latin1> > topOf3(SeqCharSet<Latin1>::range(0xe0, 0xf0));
    NFA<SeqCharSet<Latin1> > topOf4(SeqCharSet<Latin1>::range(0xf0, 0x100));
    *res.s1 = (ascii |= (topOf2 <<= lowerBytes) |= ((topOf3 <<= lowerBytes) <<= lowerBytes) |= (((topOf4 <<= lowerBytes) <<= lowerBytes) <<= lowerBytes));
  }
  if(GDFA::type == TUtf8)
  {
    NFA<TableCharSet<Latin1> > lowerBytes(TableCharSet<Latin1>::range(0x80, 0xc0));
    NFA<TableCharSet<Latin1> > ascii(TableCharSet<Latin1>::range(0, 0x7f));
    NFA<TableCharSet<Latin1> > topOf2(TableCharSet<Latin1>::range(0xc0, 0xe0));
    NFA<TableCharSet<Latin1> > topOf3(TableCharSet<Latin1>::range(0xe0, 0xf0));
    NFA<TableCharSet<Latin1> > topOf4(TableCharSet<Latin1>::range(0xf0, 0x100));
    *res.t1 = (ascii |= (topOf2 <<= lowerBytes) |= ((topOf3 <<= lowerBytes) <<= lowerBytes) |= (((topOf4 <<= lowerBytes) <<= lowerBytes) <<= lowerBytes));
  }
  return res;
}

GNFA GNFA::anything()
{
  GNFA any = anyChar();
  return *any;
}

GNFA GNFA::emptyWord()
{
  GNFA res;
#define macro(x) res.x = new NFA<T>(NFA<T>::emptyWord());
  EACH_TYPE(macro)
#undef macro
  return res;
}

#include "generated-kdev-utf8-tuples.h"

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
  GNFA res;
  switch(GDFA::type)
  {
    case SAscii: { res.s0 = new NFA<SeqCharSet<Ascii> >(begin >= 0x80 ? SeqCharSet<Ascii>::emptySet() : SeqCharSet<Ascii>::range(begin, min((quint32)0x80, end))); } break;
    case SLatin1: { res.s1 = new NFA<SeqCharSet<Latin1> >(begin >= 0x100 ? SeqCharSet<Latin1>::emptySet() : SeqCharSet<Latin1>::range(begin, min((quint32)0x100, end))); } break;
    case SUtf8: {
      res.s1 = new NFA<SeqCharSet<Latin1> >();
      addUtf8Range(*res.s1, begin, end);
    } break;
    case SUcs2: {
      res.s2 = new NFA<SeqCharSet<Ucs2> >(begin >= 0x10000 ? SeqCharSet<Ucs2>::emptySet() : SeqCharSet<Ucs2>::range(begin, min((quint32)0x10000, end))/*.difference(SeqCharSet<Ucs2>::range(0xd800, 0xe000))*/);
    } break;
    case SUtf16: {
#define UTF16_IMPL(CS, field) \
      if(end >= 0x110000 || begin >= 0x110000)                                          \
      {                                                                                 \
        res.field = new NFA<CS<Ucs2> >();                                               \
      }                                                                                 \
      else if(end < 0x10000)                                                            \
      {                                                                                 \
        if(begin <= 0xd800)                                                             \
        {                                                                               \
          if(end <= begin)                                                              \
          {                                                                             \
            res.field = new NFA<CS<Ucs2> >();                                           \
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
    case SUcs4: { res.s3 = new NFA<SeqCharSet<Ucs4> >(SeqCharSet<Ucs4>::range(begin, end)); } break;
    case TAscii: { res.t0 = new NFA<TableCharSet<Ascii> >(begin >= 0x80 ? TableCharSet<Ascii>::emptySet() : TableCharSet<Ascii>::range(begin, min((quint32)0x80, end))); } break;
    case TLatin1: { res.t1 = new NFA<TableCharSet<Latin1> >(begin >= 0x100 ? TableCharSet<Latin1>::emptySet() : TableCharSet<Latin1>::range(begin, min((quint32)0x100, end))); } break;
    case TUtf8: {
      res.t1 = new NFA<TableCharSet<Latin1> >();
      addUtf8Range(*res.t1, begin, end);
    } break;
    case TUcs2: {
      res.t2 = new NFA<TableCharSet<Ucs2> >(begin >= 0x10000 ? TableCharSet<Ucs2>::emptySet() : TableCharSet<Ucs2>::range(begin, min((quint32)0x10000, end))/*.difference(TableCharSet<Ucs2>::range(0xd800, 0xe000))*/);
    }
    case TUtf16: {
      UTF16_IMPL(TableCharSet, t2)
      #undef UTF16_IMPL
    } break;
    default: exit(-1);
  }
  // TODO: warning if empty
  return res;
}

GNFA GNFA::character(quint32 codepoint)
{
  return range(codepoint, codepoint+1);
}

void deleteNFA(GNFA *ptr)
{
  delete ptr;
}

void deleteDFA(GDFA *ptr)
{
  delete ptr;
}

AutomatonType GDFA::type = SUcs2;

template<CharEncoding enc>
const typename TableCharSet<enc>::BitArray TableCharSet<enc>::nullData = bitset<TableCharSet<enc>::nChars>();

}
