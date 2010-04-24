/// WARNING! This file is a technical experiment!!
#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <map>
#include <stdint.h>
#include <cmath>
#include <QtCore/qglobal.h>
using namespace std;

struct state
{
    uint64_t confl[64];
    uchar pos[64];
    uchar num, size;
    state()
    {
        num = 0;
        size = 0;
        for(int i = 0; i != 64; ++i)
            confl[i] = 0;
    }
    state(const state& o)
    {
        for(int i = 0; i != 64; ++i)
        {
            pos[i] = o.pos[i];
            confl[i] = o.confl[i];
        }
        num = o.num;
        size = o.size;
    }
};

int main()
{
    vector<uint64_t> orig, in;
    orig.push_back(0x3);
    orig.push_back(0x1);
    orig.push_back(0x2);
    orig.push_back(0xc);
    orig.push_back(0x4);
    orig.push_back(0x8);
    /*orig.push_back(0xf);
    orig.push_back(0xf0);
    orig.push_back(0x3);
    orig.push_back(0xbb);
    orig.push_back(0x44);
    orig.push_back(0xf00);
    orig.push_back(0x0f0);
    orig.push_back(0xbb0);
    orig.push_back(0x7777);
    orig.push_back(0xf0f0);
    orig.push_back(0xf0000);*/
    vector<uchar> rules[64];
    vector<uchar> map[64] = {};
    for(int i = 0; i != orig.size(); ++i)
    {
        /*for(int j = 0; j != in.size(); ++j)
        {
            if((in[j] & orig[i]) == orig[i])
            {
                map[j].push_back(i);
                goto fail;
            }
        }*/
        cout << hex << orig[i] << endl;
        map[in.size()].push_back(i);
        in.push_back(orig[i]);
        for(int j = 0; j != 64; ++j)
            if(in.back() & (1 << j))
                rules[j].push_back(in.size()-1);
        //fail:;
    }
    cout << dec;
    {
        bool printOr = false;
        for(int i = 0; i != 64; ++i)
        {
            if(rules[i].size() != 0)
            {
                if(printOr)
                    cout << " |";
                else
                    cout << "  ";
                printOr = true;
                for(int j = 0; j != rules[i].size(); ++j)
                {
                    for(int k = 0; k != map[rules[i][j]].size(); ++k)
                        cout << " f" << (int)map[rules[i][j]][k];
                }
                cout << endl;
            }
        }
    }
    uchar num = in.size();
    deque<state> s;
    s.push_back(state());
    while(true)
    {
        state curr = s.front();
        s.pop_front();
        if(curr.num == num)
        {
            vector<uchar> rpos[64] = {};
            for(int i = 0; i != curr.num; ++i)
                rpos[curr.pos[i]].push_back(i);
            for(int i = 0; i != 64 && rpos[i].size() != 0; ++i)
            {
                cout << "union { ";
                for(int j = 0; j != rpos[i].size(); ++j)
                {
                    for(int k = 0; k != map[rpos[i][j]].size(); ++k)
                        cout << "f" << (int)map[rpos[i][j]][k] << "; ";
                }
                cout << "};" << endl;
            }
            break;
        }
        uint64_t next = in[curr.num];
        ++curr.num;
        for(int i = 0; i != curr.size; ++i)
        {
            if((curr.confl[i] & next) == 0)
            {
                state ncurr(curr);
                ncurr.confl[i] |= next;
                ncurr.pos[curr.num-1] = i;
                s.push_front(ncurr);
            }
        }
        curr.confl[curr.size] = next;
        curr.pos[curr.num-1] = curr.size;
        ++curr.size;
        s.push_back(curr);
    }
    
}
