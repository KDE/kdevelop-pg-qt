
#include "coolparser.h"
#include "cooldefaultvisitor.h"
#include "decoder.h"

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace cool;

static void usage(char const* argv0);
static bool parse_file(char const* filename);


void print_token_environment(Parser* parser)
{
    static bool done = false;
    if (done)
      return; // don't print with each call when going up the error path

    decoder dec(parser->tokenStream, parser);

    std::size_t current_index = parser->tokenStream->index() - 1;
    for (std::size_t i = current_index - 5; i < current_index + 5; ++i)
      {
        if (i < 0 || i >= parser->tokenStream->size())
          continue;

        if (i == current_index)
          std::cerr << ">>";

        std::cerr << dec.decode_id(i).toAscii().constData(); // print out currently processed token

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

  return EXIT_SUCCESS;
}

bool parse_file(char const *filename)
{
  char *contents;
  std::ifstream filestr(filename);

  if (filestr.is_open())
    {
      std::filebuf *pbuf;
      long size;

      // get pointer to associated buffer object
      pbuf = filestr.rdbuf();

      // get file size using buffer's members
      size = pbuf->pubseekoff(0,std::ios::end,std::ios::in);
      pbuf->pubseekpos(0,std::ios::in);

      // allocate memory to contain file data
      contents = new char[size+1];

      // get file data
      pbuf->sgetn(contents, size);

      contents[size] = '\0';

      filestr.close();
    }
  else
    {
      std::cerr << filename << ": file not found" << std::endl;
      return false;
    }

  KDevPG::TokenStream token_stream;
  Parser::memoryPoolType memory_pool;

  // 0) setup
  Parser cool_parser;
  cool_parser.setTokenStream(&token_stream);
  cool_parser.setMemoryPool(&memory_pool);

  // 1) tokenize
  cool_parser.tokenize(contents);

  // 2) parse
  ProgramAst *ast = 0;
  bool matched = cool_parser.parseProgram(&ast);
  if (matched)
    {
      DefaultVisitor v;
      v.visitNode(ast);
    }
  else
    {
      cool_parser.expectedSymbol(AstNode::ProgramKind, "program"); // ### remove me
    }

  delete[] contents;

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
