
#include "csharp.h"
#include "decoder.h"

#include <cstdlib>
#include <iostream>
#include <fstream>

char *_G_contents;

static void usage(char const* argv0);
static bool parse_file(char const* filename, csharp::csharp_compatibility_mode compatibility_mode);


void print_token_environment(csharp* parser)
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
  csharp::csharp_compatibility_mode compatibility_mode = csharp::csharp20_compatibility;

  if (argc == 1)
    {
      usage(argv[0]);
      exit(EXIT_FAILURE);
    }
  while (char const *arg = *++argv)
    {
      if (!strncmp(arg, "--compatibility=", 16))
        {
          /*
          char const* version = arg + 16;

          if (!strcmp("1.0", version)) {
            compatibility_mode = csharp::csharp10_compatibility;
          }
          else if (!strcmp("2.0", version)) {
          */
            compatibility_mode = csharp::csharp20_compatibility;
          /*
          }
          else {
            std::cerr << "Unsupported C# version: " << version << std::endl;
            usage(argv[0]);
            exit(EXIT_FAILURE);
          }
          */
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

bool parse_file(char const *filename, csharp::csharp_compatibility_mode compatibility_mode)
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

  csharp::token_stream_type token_stream;
  csharp::memory_pool_type memory_pool;

  // 0) setup
  csharp parser;
  parser.set_compatibility_mode(compatibility_mode);
  parser.set_token_stream(&token_stream);
  parser.set_memory_pool(&memory_pool);

  // 1) tokenize
  parser.tokenize();

  // 2) parse
  compilation_unit_ast *ast = 0;
  bool matched = parser.parse_compilation_unit(&ast);
  if (matched)
    {
      csharp_default_visitor v;
      v.visit_node(ast);
    }
  else
    {
      parser.yy_expected_symbol(csharp_ast_node::Kind_compilation_unit, "compilation_unit"); // ### remove me
    }

  delete[] _G_contents;

  return matched;
}

static void usage(char const* argv0)
{
  std::cerr << "usage: " << argv0 << " [options] file.cs [file2.cs ...]";
     //<< std::endl << std::endl
     //<< "Options:" << std::endl
     //<< "  --compatibility=VERSION: Accept files of the given C# version. " << std::endl
     //<< "                           VERSION is one of 1.0 or 2.0, "
     //<<                            "default is 2.0." << std::endl;
}
