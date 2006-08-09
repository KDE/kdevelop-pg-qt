
%option c++
%option yyclass="fact::Lexer"
%option noyywrap


%{

#define DONT_INCLUDE_FLEXLEXER
#include "fact_lexer.h"


#define YY_USER_ACTION \
_M_token_begin = _M_token_end; \
_M_token_end += yyleng;

%}


Letter      [a-zA-Z_]
Digit       [0-9]
Whitespace  [ \t\f\r\n]
%%

{Whitespace}+   /* skip */ ;


 /* operators and seperators */

"("         return parser::Token_LPAREN;
")"         return parser::Token_RPAREN;
"{"         return parser::Token_LBRACE;
"}"         return parser::Token_RBRACE;
","         return parser::Token_COMMA;
";"         return parser::Token_SEMICOLON;
"=="        return parser::Token_EQUAL;
"="         return parser::Token_ASSIGN;
"*"         return parser::Token_STAR;
"-"         return parser::Token_MINUS;


 /* reserved words */

"if"        return parser::Token_IF;
"else"      return parser::Token_ELSE;
"var"       return parser::Token_VAR;
"function"  return parser::Token_FUNCTION;
"return"    return parser::Token_RETURN;


 /* identifiers and number literals */

{Letter}({Letter}|{Digit})*   return parser::Token_IDENTIFIER;
{Digit}+    return parser::Token_NUMBER;


 /* everything else is not a valid lexeme */

.           return parser::Token_INVALID;

%%

namespace fact
{

void Lexer::restart(parser *parser, char *contents)
{
  _M_parser = parser;
  _M_contents = contents;
  _M_token_begin = _M_token_end = 0;
  _M_current_offset = 0;

  // check for and ignore the UTF-8 byte order mark
  unsigned char *ucontents = (unsigned char *) _M_contents;
  if (ucontents[0] == 0xEF && ucontents[1] == 0xBB && ucontents[2] == 0xBF)
    {
      _M_token_begin = _M_token_end = 3;
      _M_current_offset = 3;
    }

  yyrestart(NULL);
  BEGIN(INITIAL); // is not set automatically by yyrestart()
}

} // end of namespace fact

