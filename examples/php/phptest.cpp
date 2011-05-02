#include "phplexer.h"
#include "phpparser.h"
#include "phptokentext.h"

using namespace Php;
using namespace KDevPG;

#include <iostream>
using namespace std;

int main()
{
  string str;
  getline(cin, str);
  QString qcode(QByteArray(str.c_str(), str.size()));
  QStringIterator iter(qcode);
  qDebug() << qcode.size() << iter.hasNext();
  Php::Lexer lex(iter);
  int kind;
  while((kind = lex.next().kind) != Parser::Token_EOF)
  {
  }
  lex.rewind(0);
  forever
  {
    auto t = lex.next();
    cout << tokenText(t.kind).toStdString() << ": " << qcode.mid(t.begin, t.end - t.begin + 1).toStdString() << endl << "---" << endl;
    if(t.kind == Php::Parser::Token_EOF)
      break;
  }
}
