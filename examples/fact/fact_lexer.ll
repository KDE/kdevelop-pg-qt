
%{

#include "fact.h"

extern std::size_t _M_token_begin, _M_token_end;
extern char *_G_contents;
extern std::size_t _G_current_offset;

#define YY_INPUT(buf, result, max_size) \
 do \
   { \
     int c = _G_contents[_G_current_offset++]; \
     result = c == 0 ? YY_NULL : (buf[0] = c, 1); \
   } \
 while (0)

#define YY_USER_INIT \
  _M_token_begin = _M_token_end = 0; \
  _G_current_offset = 0;

#define YY_USER_ACTION \
  _M_token_begin = _M_token_end; \
  _M_token_end += yyleng; 

%}

ALPHA		[a-zA-Z_]
DIGIT		[0-9]
WS		[ \t\r\n]
%%

"if"					{ return fact::Token_IF; }
"else"					{ return fact::Token_ELSE; }
"var"					{ return fact::Token_VAR; }
"function"				{ return fact::Token_FUNCTION; }
"return"				{ return fact::Token_RETURN; }

{WS}+
{ALPHA}({ALPHA}|{DIGIT})* 		{ return fact::Token_ID; }
{DIGIT}+				{ return fact::Token_NUMBER; }
"("					{ return fact::Token_LPAREN; }
")"					{ return fact::Token_RPAREN; }
"{"					{ return fact::Token_LBRACE; }
"}"					{ return fact::Token_RBRACE; }
","					{ return fact::Token_COMMA; }
";"					{ return fact::Token_SEMICOLON; }
"=="					{ return fact::Token_EQUAL_EQUAL; }
"="					{ return fact::Token_EQUAL; }
"*"					{ return fact::Token_STAR; }
"-"					{ return fact::Token_MINUS; }

%%

#include <cassert>
#include <iostream>
#include <cstdlib>

int yywrap() { return 1; }

