#include "Opparser.cpp"
#include "Opdebugvisitor.h"


using namespace Op;

inline void addToken(KDevPG::TokenStream& str, Parser::TokenType kind)
{
  static int i = 0;
  Parser::Token &t = str.next();
  t.kind = kind;
  t.begin = i;
  t.end = i;
  ++i;
}

int main()
{
    KDevPG::TokenStream token_stream;
    Parser::memoryPoolType memory_pool;
    Parser parser;
    parser.setTokenStream(&token_stream);
    parser.setMemoryPool(&memory_pool);
    #define A(t) addToken(token_stream, Parser::Token_##t);
    A(NUM)
    A(INV)
    A(MUL)
    A(NUM)
    A(POW)
    A(NUM)
    A(EOF)
    token_stream.rewind(0);
    parser.yylex();
    DocumentAst *doc;
    kDebug() << parser.parseDocument(&doc);
    DebugVisitor v(&token_stream, "1-*2^3");
    v.visitDocument(doc);
    Op::BinaryExprAst *b = (Op::BinaryExprAst*)doc->exprSequence->element;
    int *x = 0;
    kDebug() << *x;
}

