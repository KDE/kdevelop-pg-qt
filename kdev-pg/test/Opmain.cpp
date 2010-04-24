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

int main(int argc, char **argv)
{
    KDevPG::TokenStream token_stream;
    Parser::memoryPoolType memory_pool;
    Parser parser;
    parser.setTokenStream(&token_stream);
    parser.setMemoryPool(&memory_pool);
    QString str = argc == 1 ? "1-*2^3" : argv[1];
    #define A(t) addToken(token_stream, Parser::Token_##t);
    for(int i = 0 ; i != str.size(); ++i)
    {
      if(str[i] == '-')
        A(INV)
      else if(str[i] == '+')
        A(PLUS)
      else if(str[i] == '*')
        A(MUL)
      else if(str[i] == '^')
        A(POW)
      else if(str[i] == '!')
        A(NOT)
      else
        A(NUM)
    }
    A(EOF)
    token_stream.rewind(0);
    parser.yylex();
    DocumentAst *doc;
    kDebug() << parser.parseDocument(&doc);
    DebugVisitor v(&token_stream, str);
    v.visitDocument(doc);
}

