#include "phplexer.h"
#include "phpparser.h"
#include "phptokentext.h"

using namespace Php;
using namespace KDevPG;

#include <iostream>
using namespace std;

int main()
{
  qDebug() << "eevl";
  string str;
  getline(cin, str);
//   QString qcode(QByteArray(str.c_str(), str.size()));
//   QStringIterator iter(qcode);
  QByteArray qcode(str.c_str(), str.size());
  QByteArrayIterator iter(qcode);
  qDebug() << qcode.size() << iter.hasNext();
  Php::Lexer lex(iter);
  int kind;
  while((kind = lex.advance().kind) != Parser::Token_EOF)
  {
//     cout << tokenText(kind).toStdString() << endl;
  }
  lex.rewind(0);
  forever
  {
    auto t = lex.advance();
    cout << tokenText(t.kind).toStdString() << ": " << qcode.mid(t.begin, t.end - t.begin + 1).data() << endl << "---" << endl;
    if(t.kind == Php::Parser::Token_EOF)
      break;
  }
}
