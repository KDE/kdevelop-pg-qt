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
  FooLisp::Lexer lex(iter);
  FooLisp::Parser parser;
  parser.setTokenStream(&lex);
  while(lex.next().kind != Parser::Token_EOF)
    ;
  StartAst *ast;
  parser.parseStart(&ast);
  DebugVisitor vis(&lex, qcode);
  vis.visitNode(ast);
}
