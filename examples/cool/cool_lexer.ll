
%{
#include "cool.h"

#include <iostream>

/* call this before calling yylex(): */
void lexer_restart(cool::parser* parser);

extern std::size_t _G_token_begin, _G_token_end;
extern char *_G_contents;



/* the rest of these declarations are internal to the lexer,
 * don't use them outside of this file. */

std::size_t _G_current_offset;
cool::parser* _G_parser;


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

Whitespace  [ \t\f\r\n]

%x IN_BLOCKCOMMENT

%%

 /* whitespace, newlines and comments */

{Whitespace}+   /* skip */ ;
"--".*          /* line comments, skip */ ;

"(*"                    BEGIN(IN_BLOCKCOMMENT);
<IN_BLOCKCOMMENT>{
"*)"            BEGIN(INITIAL);
<<EOF>>         return cool::parser::Token_EOF;
"\r\n"|\r|\n    /* advance */ ;
.               /* advance */ ;
}


 /* seperators */

"("             return cool::parser::Token_LPAREN;
")"             return cool::parser::Token_RPAREN;
"{"             return cool::parser::Token_LBRACE;
"}"             return cool::parser::Token_RBRACE;
";"             return cool::parser::Token_SEMICOLON;
","             return cool::parser::Token_COMMA;
"."             return cool::parser::Token_DOT;
"@"             return cool::parser::Token_AT;


 /* operators */

"+"             return cool::parser::Token_PLUS;
"-"             return cool::parser::Token_MINUS;
"*"             return cool::parser::Token_STAR;
"/"             return cool::parser::Token_SLASH;
"="             return cool::parser::Token_EQUAL;
"<="            return cool::parser::Token_LESS_EQUAL;
"<"             return cool::parser::Token_LESS;
":"             return cool::parser::Token_COLON;
"<-"            return cool::parser::Token_ARROW_LEFT;
"=>"            return cool::parser::Token_ARROW_RIGHT;
"~"             return cool::parser::Token_TILDE;
"not"           return cool::parser::Token_NOT;
"isvoid"        return cool::parser::Token_ISVOID;


 /* reserved words */

"case"          return cool::parser::Token_CASE;
"esac"          return cool::parser::Token_ESAC;
"class"         return cool::parser::Token_CLASS;
"Class"         return cool::parser::Token_CLASS;
"else"          return cool::parser::Token_ELSE;
"false"         return cool::parser::Token_FALSE;
"if"            return cool::parser::Token_IF;
"in"            return cool::parser::Token_IN;
"fi"            return cool::parser::Token_FI;
"inherits"      return cool::parser::Token_INHERITS;
"let"           return cool::parser::Token_LET;
"loop"          return cool::parser::Token_LOOP;
"new"           return cool::parser::Token_NEW;
"of"            return cool::parser::Token_OF;
"pool"          return cool::parser::Token_POOL;
"then"          return cool::parser::Token_THEN;
"true"          return cool::parser::Token_TRUE;
"while"         return cool::parser::Token_WHILE;


 /* literals */

"\""([^"\\]|\\.)*"\""   return cool::parser::Token_STRING;

[A-Z][a-zA-Z0-9_]*      return cool::parser::Token_TYPE;
[a-z_][a-zA-Z0-9_]*     return cool::parser::Token_IDENTIFIER;
[0-9]+          return cool::parser::Token_INTEGER;


 /* everything else is not a valid lexeme */

.               return cool::parser::Token_INVALID;

%%

void lexer_restart(cool::parser* _parser) {
  _G_parser = _parser;
  yyrestart(NULL);
  BEGIN(INITIAL); // is not set automatically by yyrestart()
  YY_USER_INIT
}

int yywrap() { return 1; }
