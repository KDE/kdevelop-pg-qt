#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <stack>
#include <cassert>
#include <tr1/unordered_set>
#include <tr1/unordered_map>

using namespace std;
using namespace tr1;

#include <QString>

#define NC(...) __VA_ARGS__

inline size_t rotl(unsigned int value, char shift)
{
    return (value << shift) | (value >> (sizeof(size_t) * 8 - shift));
}

class CharSet
{
    set<QChar> data;
    size_t hash;
    void updateHash()
    {
        hash = 21390587;
        for(__typeof__(data.begin()) i = data.begin(); i != data.end(); ++i)
        {
            hash = rotl(hash, 7);
            hash ^= i->unicode();
        }
    }
    friend ostream& operator<<(ostream&, const CharSet&);
public:
    CharSet(const QString& str)
    {
        for(int i = 0; i != str.size(); ++i)
            data.insert(str[i]);
        updateHash();
    }
    CharSet() : hash(0)
    {}
    CharSet(const CharSet& o) : data(o.data), hash(o.hash)
    {
    }
    bool epsilon() const
    {
        return hash == 0 && empty();
    }
    size_t hashValue() const
    {
        return hash;
    }
    bool empty() const
    {
        return data.empty();
    }
    bool accepts(QChar chr) const
    {
        return data.count(chr);
    }
    CharSet intersection(const CharSet& o) const
    {
        CharSet ret;
        set_intersection(data.begin(), data.end(), o.data.begin(), o.data.end(), inserter(ret.data, ret.data.begin()));
        ret.updateHash();
        return ret;
    }
    CharSet difference(const CharSet& o) const
    {
        CharSet ret;
        set_difference(data.begin(), data.end(), o.data.begin(), o.data.end(), inserter(ret.data, ret.data.begin()));
        ret.updateHash();
        return ret;
    }
    CharSet getUnion(const CharSet& o) const
    {
        CharSet ret;
        set_union(data.begin(), data.end(), o.data.begin(), o.data.end(), inserter(ret.data, ret.data.begin()));
        ret.updateHash();
        return ret;
    }
    CharSet& unite(const CharSet& o)
    {
        for(__typeof__(o.data.begin()) i = o.data.begin(); i != o.data.end(); ++i)
            data.insert(*i);
        updateHash();
        return *this;
    }
    bool operator==(const CharSet& o) const
    {
        return data == o.data;
    }
};

ostream& operator<<(ostream& o, const CharSet& c)
{
    foreach(QChar x, c.data)
        o << x.toAscii();
    return o;
}

namespace std
{
    namespace tr1
    {
        template<> struct hash< CharSet >
        {
            inline size_t operator()(const CharSet &cs) const
            {
                return cs.hashValue();
            }
        };
    }
}

class DFA
{
    size_t nstates;
    vector<vector<pair<CharSet, size_t> > > rules;
    vector<bool> accept;
    friend class NFA;
public:
    void inspect()
    {
        cout << "#states = " << nstates << " accept = <";
        for(size_t i = 0; i != nstates; ++i)
            if(accept[i])
                cout << ", " << i;
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
    bool accepts(const QString& str)
    {
        size_t state = 0;
        foreach(QChar c, str)
        {
            foreach(NC(const pair<CharSet, size_t>& r), rules[state])
            {
                if(r.first.accepts(c))
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
    DFA& eliminateUnarrivableStates()
    {
        vector<bool> arrivable(nstates);
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
        size_t curr = 0;
        vector<size_t> mapping(nstates);
        for(size_t i = 0; i != nstates; ++i)
        {
            if(arrivable[i])
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
        vector<vector<size_t> > grinv(2);
        for(size_t i = 0; i != nstates; ++i)
        {
            if(accept[i])
                grinv[accept[0] ? 0 : 1].push_back(i);
            else
                grinv[accept[0] ? 1 : 0].push_back(i);
        }
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
                    if(sameGroup(ongroups, groups, grinv[j][0], i))
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
        vector<bool> _accept(grinv.size());
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
    vector<bool> closure(vector<bool> s)
    {
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
    vector<bool> vecUnion(const vector<bool>& a, const vector<bool>& b)
    {
        vector<bool> ret(a);
        for(size_t i = 0; i != a.size(); ++i)
            ret[i] = ret[i] || b[i];
        return ret;
    }
    vector< pair<CharSet, vector<bool> > > follow(vector<bool> s)
    {
        vector<pair<CharSet, vector<bool> > > pr(nstates);
        for(size_t i = 0; i != nstates; ++i)
        {
            if(s[i])
            {
                foreach(NC(const pair<CharSet, size_t>& r), rules[i])
                {
                    vector<bool> nxt(nstates);
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
                                vector<bool> v1 = pr[i].second, v2 = pr[j].second;
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
        set<vector<bool> > states;
        map<vector<bool>, vector<pair<CharSet, vector<bool> > > > rules;
        stack<vector<bool> > todo;
        vector<bool> start(nstates);
        start[0] = true;
        todo.push(closure(start));
        while(todo.size())
        {
            vector<bool> x = todo.top();
            todo.pop();
            states.insert(x);
            rules[x];
            vector<pair<CharSet, vector<bool> > > nxt = follow(x);
            foreach(NC(const pair<CharSet, vector<bool> >& nx), nxt)
            {
                if(!nx.first.epsilon())
                {
                    vector<bool> n = closure(nx.second);
                    if(!states.count(n))
                        todo.push(n);
                    rules[x].push_back(make_pair(nx.first, n));
                }
            }
        }
        DFA _;
        _.nstates = states.size();
        _.accept.resize(_.nstates);
        map<vector<bool>, size_t> st;
        foreach(const vector<bool>& i, states)
        {
            if(i[0] && st.size())
            {
                st[*states.begin()] = st.size();
                st[i] = 0;
            }
            else
                st[i] = st.size();
        }
        _.rules.resize(_.nstates);
        for(__typeof__(st.begin()) i = st.begin(); i != st.end(); ++i)
            if(i->first[accept])
                _.accept[i->second] = true;
        for(__typeof__(rules.begin()) i = rules.begin(); i != rules.end(); ++i)
        {
            size_t key = st[i->first];
            foreach(NC(const pair<CharSet, vector<bool> > nx), i->second)
                _.rules[key].push_back(make_pair(nx.first, st[nx.second]));
        }
        return _;
    }
};

NFA keyword(const QString& str)
{
    NFA r;
    for(size_t i = 0; i != str.size(); ++i)
        r &= CharSet(str[i]);
    return r;
}

int main()
{
    cout << keyword("while").dfa().accepts("while") << endl;
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
    {
        cout << endl << endl;
        n.inspect();
        DFA d = n.dfa();
        cout << endl << endl;
        d.inspect();
        d.minimize();
        cout << endl << endl;
        d.inspect();
        cout << d.accepts("foo    354.123   union") << endl;
    }
}
