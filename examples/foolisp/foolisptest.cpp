#include "foolispparser.h"
#include "foolisplexer.h"
#include "foolispdebugvisitor.h"

using namespace FooLisp;
using namespace KDevPG;

#include <iostream>
using namespace std;

int main()
{
  string str;
  getline(cin, str);
  QString qcode = QString::fromUtf8(str.c_str(), str.size());
  QUtf16ToUcs4Iterator iter(qcode);
  qDebug() << qcode.size() << iter.hasNext();
  FooLisp::Lexer lex(iter);
  FooLisp::Parser parser;
  parser.setMemoryPool(new KDevPG::MemoryPool);
  parser.setTokenStream(&lex);
  int kind;
  while((kind = lex.next().kind) != Parser::Token_EOF)
    qDebug() << kind;
  parser.rewind(0);
  StartAst *ast;
  parser.parseStart(&ast);
  DebugVisitor vis(&lex, qcode);
  vis.visitNode(ast);
  qDebug() << ast->sexp;
}
