#include "phplexer.h"
#include "phpparser.h"
#include "phptokentext.h"
#include "phpdebugvisitor.h"

using namespace Php;
using namespace KDevPG;

#include <iostream>
using namespace std;

int main()
{
  qDebug() << "eevl";
  string str;
  while(true)
  {
    string strr;
    getline(cin, strr);
    if(!strr.size())
      break;
    str += strr + "\n";
  }
//   QString qcode(QByteArray(str.c_str(), str.size()));
//   QStringIterator iter(qcode);
  QByteArray qcode(str.c_str(), str.size());
  QByteArrayIterator iter(qcode);
  qDebug() << qcode.size() << iter.hasNext();
  Php::TokenStream lex(iter);
  Php::Parser parser;
  KDevPG::MemoryPool pool;
  parser.setTokenStream(&lex);
  parser.setMemoryPool(&pool);
//   int kind;
//   while((kind = lex.advance().kind) != Parser::Token_EOF)
//   {
//     cout << tokenText(kind).toStdString() << endl;
  //   }
  Php::StartAst *root = 0;
  lex.rewind(0);
//   parser.parseStart(&root);
//   cout << tokenText(lex.front().kind).toStdString() << endl;
//   cout << tokenText(lex.curr().kind).toStdString() << endl;
//   cout << tokenText(lex.back().kind).toStdString() << endl;
//   lex.rewind(0);
  forever
  {
    auto t = lex.advance();
    cout << tokenText(t.kind).toStdString() << ": " << qcode.mid(t.begin, t.end - t.begin + 1).data() << endl << "---" << endl;
    if(t.kind == Php::Parser::Token_EOF)
      break;
  }
  Php::DebugVisitor vis(&lex, QString(qcode));
  vis.visitNode(root);
}
