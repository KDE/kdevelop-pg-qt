
#include "java.h"
#include "decoder.h"

#include <cstdlib>
#include <iostream>
#include <fstream>

char *_G_contents;
std::size_t _M_token_begin, _M_token_end;
std::size_t _G_current_offset;
extern char* yytext;

static void tokenize(java &m);
static void usage(char const* argv0);
static bool parse_file(char const* filename, java::java_compatibility_mode compatibility_mode);
int yylex();
void lexer_restart(java* parser);


void print_token_environment(java* parser)
{
    static bool done = false;
    if (done)
      return; // don't print with each call when going up the error path

    decoder dec(parser->token_stream);

    int current_index = parser->token_stream->index() - 1;
    for (int i = current_index - 5; i < current_index + 5; i++)
      {
        if (i < 0 || i >= parser->token_stream->size())
          continue;

        if (i == current_index)
          std::cerr << ">>";

        std::cerr << dec.decode_id(i); // print out currently processed token

        if (i == current_index)
          std::cerr << "<<";

        std::cerr << " ";
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


int main(int argc, char *argv[])
{
  java::java_compatibility_mode compatibility_mode = java::java15_compatibility;

  if (argc == 1)
    {
      usage(argv[0]);
      exit(EXIT_FAILURE);
    }
  while (char const *arg = *++argv)
    {
      if (!strncmp(arg, "--compatibility=", 16))
        {
          char const* version = arg + 16;

          if (!strcmp("1.5", version)) {
            compatibility_mode = java::java15_compatibility;
          }
          else if (!strcmp("1.4", version)) {
            compatibility_mode = java::java14_compatibility;
          }
          else if (!strcmp("1.3", version)) {
            compatibility_mode = java::java13_compatibility;
          }
          else {
            std::cerr << "Unsupported Java version: " << version << std::endl;
            usage(argv[0]);
            exit(EXIT_FAILURE);
          }
        }
      else if (!strncmp(arg, "--", 2))
        {
          std::cerr << "Unknown option: " << arg << std::endl;
          usage(argv[0]);
          exit(EXIT_FAILURE);
        }
      else if(!parse_file(arg, compatibility_mode))
        {
          exit(EXIT_FAILURE);
        }
    }
}

bool parse_file(char const *filename, java::java_compatibility_mode compatibility_mode)
{
  std::ifstream filestr(filename);

  if (filestr.is_open())
    {
      std::filebuf *pbuf;
      long size;

      // get pointer to associated buffer object
      pbuf=filestr.rdbuf();

      // get file size using buffer's members
      size=pbuf->pubseekoff(0,std::ios::end,std::ios::in);
      pbuf->pubseekpos(0,std::ios::in);

      // allocate memory to contain file data
      _G_contents=new char[size+1];

      // get file data
      pbuf->sgetn(_G_contents, size);

      _G_contents[size] = '\0';

      filestr.close();
    }
  else
    {
      std::cerr << filename << ": file not found" << std::endl;
      return false;
    }

  java::token_stream_type token_stream;
  java::memory_pool_type memory_pool;

  // 0) setup
  java parser;
  parser.set_compatibility_mode(compatibility_mode);
  parser.set_token_stream(&token_stream);
  parser.set_memory_pool(&memory_pool);

  // 1) tokenize
  tokenize(parser);

  // 2) parse
  compilation_unit_ast *ast = 0;
  bool matched = parser.parse_compilation_unit(&ast);
  if (matched)
    {
      java_default_visitor v;
      v.visit_node(ast);
    }
  else
    {
      parser.yy_expected_symbol(java_ast_node::Kind_compilation_unit, "compilation_unit"); // ### remove me
    }

  delete[] _G_contents;

  return matched;
}

static void tokenize(java &m)
{
  ::lexer_restart(&m);
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

static void usage(char const* argv0)
{
  std::cerr << "usage: " << argv0 << " [options] file.java [file2.java ...]"
     << std::endl << std::endl
     << "Options:" << std::endl
     << "  --compatibility=VERSION: Accept files of the given Java version. " << std::endl
     << "                           VERSION is one of 1.3, 1.4 or 1.5, "
     <<                            "default is 1.5." << std::endl;
}
