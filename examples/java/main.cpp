
#include "java.h"

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>

#define MAX_BUFF (500 * 1024)

char *_G_contents;
std::size_t _M_token_begin, _M_token_end;
std::size_t _G_current_offset;
extern char* yytext;

static void tokenize(java &m);
int yylex();


void print_token_environment(java* parser)
{
    static bool done = false;
    if (done)
      return;

    int current_index = parser->token_stream->index() - 1;
    for (int i = current_index - 5; i < current_index + 5; i++)
      {
        if (i < 0 || i >= parser->token_stream->size())
          continue;

        java::token_type* token = &(parser->token_stream->token(i));
        char* current_token_text = new char[ token->end - token->begin + 2 ];

        snprintf( current_token_text, token->end - token->begin + 1, token->text + token->begin );
        current_token_text[ token->end - token->begin + 1 ] = '\0';

        if (i == current_index)
          std::cerr << ">>";

        std::cerr << current_token_text;

        if (i == current_index)
          std::cerr << "<<";

        std::cerr << " ";
        delete[] current_token_text;
      }
    std::cerr << std::endl;

    done = true;
}

// custom error recovery
bool java::yy_expected_token(int /*expected*/, std::size_t where, char const *name)
{
    print_token_environment(this);
    std::cerr << "** ERROR expected token ``" << name
              //<< "'' instead of ``" << current_token_text
              << "''" << std::endl;

    return false;
}

bool java::yy_expected_symbol(int /*expected_symbol*/, char const *name)
{
    print_token_environment(this);
    std::cerr << "** ERROR expected symbol ``" << name
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
      return EXIT_FAILURE;
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
      //std::cerr << yytext << std::endl; //" "; // debug output
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
