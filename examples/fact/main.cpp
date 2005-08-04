
#include "fact.h"

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>

#define MAX_BUFF (10 * 1024)

char *_G_contents;
std::size_t _M_token_begin, _M_token_end;
std::size_t _G_current_offset;

static void tokenize(fact &m);
int yylex();

int main(int, char *argv[])
{
  if (!*++argv)
    {
      std::cerr << "usage: fact file.f" << std::endl;
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

  fact::token_stream_type token_stream;
  fact::memory_pool_type memory_pool;

  // 0) setup
  fact parser;
  parser.set_token_stream(&token_stream);
  parser.set_memory_pool(&memory_pool);

  // 1) tokenize
  tokenize(parser);

  // 2) parse
  program_ast *ast = 0;
  assert(parser.parse_program(&ast));

  delete[] _G_contents;

  return EXIT_SUCCESS;
}

static void tokenize(fact &m)
{
  // tokenize
  int kind = fact::Token_EOF;
  do
    {
      kind = ::yylex();
      if (!kind)
	kind = fact::Token_EOF;

      fact::token_type &t = m.token_stream->next();
      t.kind = kind;
      t.begin = _M_token_begin;
      t.end = _M_token_end;
      t.text = _G_contents;
    }
  while (kind != fact::Token_EOF);

  m.yylex(); // produce the look ahead token
}
