
#include "cool.h"
#include "decoder.h"

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace cool;

char *_G_contents;

static void usage(char const* argv0);
static bool parse_file(char const* filename);


void print_token_environment(parser* parser)
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


int main(int argc, char *argv[])
{
  if (argc == 1)
    {
      usage(argv[0]);
      exit(EXIT_FAILURE);
    }
  while (char const *arg = *++argv)
    {
      /*if (!strncmp(arg, "--option=", 9))
        {
          char const* option = arg + 9;

          std::cerr << "--option=" << option
                    << " has been given!" << std::endl;
        }
      else */
      if (!strncmp(arg, "--", 2))
        {
          std::cerr << "Unknown option: " << arg << std::endl;
          usage(argv[0]);
          exit(EXIT_FAILURE);
        }
      else if(!parse_file(arg))
        {
          exit(EXIT_FAILURE);
        }
    }
}

bool parse_file(char const *filename)
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

  parser::token_stream_type token_stream;
  parser::memory_pool_type memory_pool;

  // 0) setup
  parser cool_parser;
  cool_parser.set_token_stream(&token_stream);
  cool_parser.set_memory_pool(&memory_pool);

  // 1) tokenize
  cool_parser.tokenize();

  // 2) parse
  program_ast *ast = 0;
  bool matched = cool_parser.parse_program(&ast);
  if (matched)
    {
      default_visitor v;
      v.visit_node(ast);
    }
  else
    {
      cool_parser.yy_expected_symbol(ast_node::Kind_program, "program"); // ### remove me
    }

  delete[] _G_contents;

  return matched;
}

static void usage(char const* argv0)
{
  std::cerr << "usage: " << argv0 /*<< " [options]"*/ << " file1.cl [file2.cl...]"
    << std::endl; /*<< std::endl
    << "Options:" << std::endl
    << "  --option=BLA: Do BLAH while parsing." << std::endl
    << "                BLAH is one of FOO, BAR or KUNG, default is FOO."
    << std::endl;
    */
}
