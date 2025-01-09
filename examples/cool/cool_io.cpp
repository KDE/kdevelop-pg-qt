
// This file is meant to be specific to the framework in which the parser
// operates, and is likely to be adapted for different environments.
// Specifically, the error output might not always go to std::cerr,
// but will rather be placed as items inside some listbox.


#include "coolparser.h"
#include "cool_lexer.h"

#include <iostream>

void print_token_environment(cool::Parser* parser);


namespace cool
{

void Parser::report_problem( Parser::problem_type type, const QString & message )
{
  if (type == error)
    std::cerr << "** ERROR: " << qPrintable(message) << std::endl;
  else if (type == warning)
    std::cerr << "** WARNING: " << qPrintable(message) << std::endl;
  else if (type == info)
    std::cerr << "** Info: " << qPrintable(message) << std::endl;
}


// custom error recovery
void Parser::expectedToken(int /*expected*/, qint64 /*where*/, const QString & name)
{
  print_token_environment(this);
  report_problem(
    Parser::error,
    QLatin1String("Expected token ``") + name
      //+ "'' instead of ``" + current_token_text
      + QLatin1String("''")
  );
}

void Parser::expectedSymbol(int /*expected_symbol*/, const QString & name)
{
  print_token_environment(this);
  report_problem(
    Parser::error,
    QLatin1String("Expected symbol ``") + name
      //+ "'' instead of ``" + current_token_text
      + QLatin1String("''")
  );
}

} // end of namespace cool

