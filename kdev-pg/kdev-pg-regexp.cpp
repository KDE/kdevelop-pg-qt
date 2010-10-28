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
// #include "kdev-pg-bit-array.h"

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <stack>
#include <string>
#include <cassert>
#include <initializer_list>
#include <tr1/unordered_set>
#include <tr1/unordered_map>

#include <QBitArray>
#include <QTextCodec>


using namespace std;
using namespace tr1;

#include <QString>
#include <QFile>
#include <QStringList>
#include "kdev-pg.h"

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

typedef vector<bool> UsedBitArray;
typedef SeqCharSet<Ucs4> CharSet;
typedef QUtf8ToUcs4Iterator Iterator;
// typedef TableCharSet<Ascii> CharSet;

class DFA
{
    size_t nstates;
    vector<vector<pair<CharSet, size_t> > > rules;
    size_t numActions;
    vector<size_t> accept;
    vector<QString> actions;
    friend class NFA;
public:
    void codegen(QTextStream& str)
    {
      str << "class " << KDevPG::globalSystem.exportMacro << " "
          << KDevPG::globalSystem.tokenStream << " : public KDevPG::TokenStream, public QUtf8ToUcs4Iterator {"
          << "typedef QUtf8ToUcs4Iterator Iterator; public: inline KDevPG::Token& next() { \n#define CURR_POS Iterator::plain()\n"
          << "#define NEXT_CHR __extension__( { if(!Iterator::hasNext()) goto _end; Iterator::next(); } )\nconst Iterator::InputInt *lpos = Iterator::plain();\nIterator::Int chr = 0;\nint lstate = 0;\n";
      
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
        str << actions[i] << "\n";
      }
      str << "}\n}\n};\n";
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
    DFA& filterStates(const UsedBitArray& active)
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
    DFA& eliminateUnarrivableStates()
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
    DFA& eliminateInactiveStates()
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
    DFA& minimize()
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

class NFA
{
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
    NFA(const CharSet& set) : nstates(2), rules(2), accept(1)
    {
        rules[0].push_back(make_pair(set, 1));
    }
    NFA(std::initializer_list<NFA> list)
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
    NFA& operator|=(const NFA& o)
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
    NFA& operator&=(const NFA& o)
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
    NFA& operator*()
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
    DFA dfa()
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
        DFA _;
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

NFA keyword(const QString& str)
{
    NFA r;
    for(auto i = str.begin(); i != str.end(); ++i)
        r &= CharSet(*i);
    return r;
}

int main()
{
  
  cout << SeqCharSet<Ucs2>("abcdef").intersection(SeqCharSet<Ucs2>("deq")) << endl;
//     cout << keyword("while").dfa().accepts("while") << endl;
//     NFA n(CharSet("abc"));
//     {
//         DFA d = n.dfa();
//         d.minimize();
//         cout << d.accepts("a") << endl;
//     }
    NFA n;
//     n |= CharSet("x");
//     n &= CharSet("v");
    n = keyword("for");
    n.inspect();
    n |= keyword("foo");
    n |= keyword("if");
    n |= keyword("fi");
    n |= keyword("while");
    n |= keyword("struct");
    n |= keyword("union");
    n |= keyword("extern");
    n |= keyword("export");
    n |= keyword("static");
    n |= keyword("do");
    n |= keyword("template");
    n |= keyword("using");
    n |= keyword("namespace");
    n |= keyword("until");
    n |= keyword("int");
    n |= keyword("float");
    n |= keyword("double");
    n |= keyword("long");
    n |= keyword("unsigned");
    n |= keyword("class");
    n |= keyword("auto");
    n |= keyword("mutable");
    n |= keyword("inline");
    n |= keyword("public");
    n |= keyword("private");
    n |= keyword("protected");
    n |= keyword("friend");
    NFA ws(CharSet(" \t\n"));
    *ws;
    ws &= NFA(CharSet(" \t\n"));
    n |= ws;
    NFA num(CharSet("0123456789"));
    *num;
    NFA floatstuff(CharSet("."));
    floatstuff &= num;
    num &= CharSet("0123456789");
    floatstuff |= NFA();
    num &= floatstuff;
    DFA numd = num.dfa();
    n |= num;
    *n;
//     {
//         cout << endl << endl;
//         n.inspect();
//         DFA d = n.dfa();
//         cout << endl << endl;
//         d.inspect();
//         d.minimize();
//         cout << endl << endl;
//         d.inspect();
//         cout << d.accepts("foo  462.1011346  union") << endl;
//     }
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
    NFA dispatch({ws, num, keyword("foo"), keyword("bar"), keyword("baz"), keyword("foobar"), keyword("for"), keyword("äöü"), keyword("bähh, I do not like §s")});
    dispatch.inspect();
    DFA ddispatch = dispatch.dfa();
    ddispatch.inspect();
    ddispatch.minimize();
    ddispatch.inspect();
    string str;
    getline(cin, str);
    QByteArray qba(str.c_str(), str.size());
    pair<Iterator, size_t> last(Iterator(qba), 0);
    Iterator begin = last.first;
    const char* names[] = {"ERROR", "whitespace", "dec-number", "foo", "bar", "baz", "foobar", "for", "umlauts", "anti-law"};
    while(last.first.hasNext())
    {
      Iterator llast = last.first;
      last = ddispatch.nextAction(llast);
      if(last.second == -1)
      {
        if(last.first.hasNext())
          cout << "ERROR" << endl;
        break;
      }
      cout << names[last.second] << ": " << str.substr(llast - begin, last.first - llast) << endl;
    }
    QFile fout("regexp.cpp");
    fout.open(QIODevice::WriteOnly);
    QTextStream stream(&fout);
    ddispatch.codegen(stream);
    fout.close();
}
