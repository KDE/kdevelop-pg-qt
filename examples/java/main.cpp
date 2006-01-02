
#include "java.h"

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>

#define MAX_BUFF (10 * 1024)

char *_G_contents;
std::size_t _M_token_begin, _M_token_end;
std::size_t _G_current_offset;
extern char* yytext;

static void tokenize(java &m);
int yylex();


// custom error recovery
bool java::yy_expected_token(int /*expected*/, std::size_t /*where*/, char const *name)
{
    std::cerr << "** ERROR expected token ``" << name
              //<< "'' instead of ``" << current_token
              << "''" << std::endl;
    return false;
}

bool java::yy_expected_symbol(int /*expected_symbol*/, char const *name)
{
    std::cerr << "** ERROR expected symbol ``" << name
              //<< "'' instead of ``" << current_token
              << "''" << std::endl;
    return false;
}

int main(int, char *argv[])
{
  if (!*++argv)
    {
      std::cerr << "usage: java file.f" << std::endl;
      exit(EXIT_FAILURE);
    }

  if (FILE *fp = fopen(*argv, "r"))
    {
      fread(_G_contents = new char[MAX_BUFF], 1, MAX_BUFF, fp);
      fclose(fp);
    }
  else
    {
      std::cerr << "file not found" << std::endl;
      exit(EXIT_FAILURE);
    }

  java::token_stream_type token_stream;
  java::memory_pool_type memory_pool;

  // 0) setup
  java parser;
  parser.set_token_stream(&token_stream);
  parser.set_memory_pool(&memory_pool);

  // 1) tokenize
  tokenize(parser);

  // 2) parse
  compilation_unit_ast *ast = 0;
  if (parser.parse_compilation_unit(&ast))
    {
      java_default_visitor v;
      v.visit_node(ast);
    }
  else
    {
      parser.yy_expected_symbol(java_ast_node::Kind_compilation_unit, "compilation_unit"); // ### remove me
    }

  delete[] _G_contents;

  return EXIT_SUCCESS;
}

static void tokenize(java &m)
{
  // tokenize
  int kind = java::Token_EOF;
  do
    {
      kind = ::yylex();
      //std::cerr << yytext << " "; // debug output
      if (!kind)
        kind = java::Token_EOF;

      java::token_type &t = m.token_stream->next();
      t.kind = kind;
      t.begin = _M_token_begin;
      t.end = _M_token_end;
      t.text = _G_contents;
    }
  while (kind != java::Token_EOF);

  m.yylex(); // produce the look ahead token
}
