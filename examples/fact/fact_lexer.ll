
%{

#include "fact.h"

#include <iostream>

/* call this before calling yylex(): */
void lexer_restart(fact::parser* parser);

extern std::size_t _G_token_begin, _G_token_end;
extern char *_G_contents;



/* the rest of these declarations are internal to the lexer,
 * don't use them outside of this file. */

std::size_t _G_current_offset;
fact::parser* _G_parser;


#define YY_INPUT(buf, result, max_size) \
  { \
    int c = _G_contents[_G_current_offset++]; \
    result = c == 0 ? YY_NULL : (buf[0] = c, 1); \
  }

#define YY_USER_INIT \
_G_token_begin = _G_token_end = 0; \
_G_current_offset = 0;

#define YY_USER_ACTION \
_G_token_begin = _G_token_end; \
_G_token_end += yyleng;

%}

Letter      [a-zA-Z_]
Digit       [0-9]
Whitespace  [ \t\f\r\n]
%%

{Whitespace}+   /* skip */ ;


 /* operators and seperators */

"("         return fact::parser::Token_LPAREN;
")"         return fact::parser::Token_RPAREN;
"{"         return fact::parser::Token_LBRACE;
"}"         return fact::parser::Token_RBRACE;
","         return fact::parser::Token_COMMA;
";"         return fact::parser::Token_SEMICOLON;
"=="        return fact::parser::Token_EQUAL;
"="         return fact::parser::Token_ASSIGN;
"*"         return fact::parser::Token_STAR;
"-"         return fact::parser::Token_MINUS;


 /* reserved words */

"if"        return fact::parser::Token_IF;
"else"      return fact::parser::Token_ELSE;
"var"       return fact::parser::Token_VAR;
"function"  return fact::parser::Token_FUNCTION;
"return"    return fact::parser::Token_RETURN;


 /* identifiers and number literals */

{Letter}({Letter}|{Digit})*   return fact::parser::Token_IDENTIFIER;
{Digit}+    return fact::parser::Token_NUMBER;


 /* everything else is not a valid lexeme */

.           return fact::parser::Token_INVALID;

%%

void lexer_restart(fact::parser* _parser) {
  _G_parser = _parser;
  yyrestart(NULL);
  BEGIN(INITIAL); // is not set automatically by yyrestart()
  YY_USER_INIT
}

int yywrap() { return 1; }
