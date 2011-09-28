#include "foolispparser.h"
#include "foolisplexer.h"
#include "foolispdebugvisitor.h"
#include "foolisptokentext.h"

using namespace FooLisp;
using namespace KDevPG;

#include <iostream>
using namespace std;

int main()
{
  string str;
  getline(cin, str);
  QByteArray qcode(str.c_str(), str.size());
  QUtf8ToUcs4Iterator iter(qcode);
  qDebug() << qcode.size() << iter.hasNext();
  FooLisp::Lexer lex(iter);
  qDebug() << iter.hasNext();
  FooLisp::Parser parser;
  KDevPG::MemoryPool pool;
  parser.setMemoryPool(&pool);
  parser.setTokenStream(&lex);
  int kind;
  qDebug() << iter.hasNext();
  while((kind = lex.read().kind) != Parser::Token_EOF)
    qDebug() << "hi" << tokenText(kind);
  parser.rewind(0);
  StartAst *ast;
  parser.parseStart(&ast);
  DebugVisitor vis(&lex, qcode);
  vis.visitNode(ast);
  qDebug() << ast->sexp;
  qDebug() << ast->sexp->sexpSequence;
}
