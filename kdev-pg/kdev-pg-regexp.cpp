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
#include <iostream>

using namespace KDevPG;

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
