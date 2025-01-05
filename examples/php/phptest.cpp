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
  try
  {
    lex.rewind(0);
    parser.yylex();
    cout << "Parse: " << parser.parseStart(&root) << endl;
    qDebug() << root->statementsSequence;
    qDebug() << root->statementsSequence->element;
  //   cout << tokenText(lex.front().kind).toStdString() << endl;
  //   cout << tokenText(lex.curr().kind).toStdString() << endl;
  //   cout << tokenText(lex.back().kind).toStdString() << endl;
  }
  catch(...)
  {
    cout << "ERROR!!" << endl;
  }
  lex.rewind(0);
  cout << "blub" << endl;
  Php::DebugVisitor vis(&lex, QString(qcode));
  vis.visitStart(root);
  while(true)
  {
    auto t = lex.curr();
    lex.read();
    cout << t.begin << ".." << t.end << tokenText(t.kind).toStdString() << ": " << qcode.mid(t.begin, t.end - t.begin + 1).data() << endl << "---" << endl;
    if(lex.index() == lex.size())
      break;
  }
}
