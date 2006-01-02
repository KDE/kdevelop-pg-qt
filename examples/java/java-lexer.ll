
%{
#include "java.h"

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



 /* TODO: return the string value instead of only the last found part (") */
 // "\""                               BEGIN(IN_STRING);
 // <IN_STRING>"\""                      BEGIN(INITIAL); return java::Token_STRING_LITERAL;
 // <IN_STRING><<EOF>>                   printf("Unclosed string at the end of the file.\n"); assert(0);
 // <IN_STRING>\n                        printf("Line break in an open string.\n"); assert(0);
 // <IN_STRING>{ESCAPE_SEQUENCE}         /*advance*/ ;
 // <IN_STRING>\\.                       printf("Invalid string escape: %s\n", yytext); assert(0);
 // <IN_STRING>.                         /*advance*/ ;
%}

%x IN_STRING
%x IN_BLOCKCOMMENT

/* TODO: preprocess file so that unicode escapes
         are converted before the file is lexed.
         UNICODE_VALUE can then be removed from ESCAPE_VALUE. */
UNICODE_VALUE     u+([0-9a-fA-f]{4,4})

OCTAL_VALUE       ([0-7]{1,2}|[0-3][0-7][0-7])
ESCAPE_SEQUENCE   \\([btnfr]|\'|\"|\\|{OCTAL_VALUE}|{UNICODE_VALUE})

HEX_NUMERAL       0[xX][0-9a-fA-F]+
HEX_FLOAT_NUMERAL 0[xX][0-9a-fA-F]*\.[0-9a-fA-F]+

EXPONENT          [eE][\+\-]?[0-9]+
BINARY_EXPONENT   [pP][\+\-]?[0-9]+

%%

[ \t\f\r\n]+  /* skip */ ;


 /* comments */

"//".*                      /* line comments, skip */ ;

"/*"                        BEGIN(IN_BLOCKCOMMENT);
<IN_BLOCKCOMMENT>"*/"         BEGIN(INITIAL);
<IN_BLOCKCOMMENT><<EOF>>      printf("Unclosed block comment at the end of the file.\n"); assert(0);
<IN_BLOCKCOMMENT>\n           /*advance*/ ;
<IN_BLOCKCOMMENT>.            /*advance*/ ;


 /* reserved words */

"abstract"      return java::Token_ABSTRACT;
"assert"        return java::Token_ASSERT;
"boolean"       return java::Token_BOOLEAN;
"break"         return java::Token_BREAK;
"byte"          return java::Token_BYTE;
"case"          return java::Token_CASE;
"catch"         return java::Token_CATCH;
"char"          return java::Token_CHAR;
"class"         return java::Token_CLASS;
"const"         return java::Token_CONST;
"continue"      return java::Token_CONTINUE;
"default"       return java::Token_DEFAULT;
"do"            return java::Token_DO;
"double"        return java::Token_DOUBLE;
"else"          return java::Token_ELSE;
"enum"          return java::Token_ENUM;
"extends"       return java::Token_EXTENDS;
"false"         return java::Token_FALSE;
"final"         return java::Token_FINAL;
"finally"       return java::Token_FINALLY;
"float"         return java::Token_FLOAT;
"for"           return java::Token_FOR;
"goto"          return java::Token_GOTO;
"if"            return java::Token_IF;
"implements"    return java::Token_IMPLEMENTS;
"import"        return java::Token_IMPORT;
"instanceof"    return java::Token_INSTANCEOF;
"int"           return java::Token_INT;
"interface"     return java::Token_INTERFACE;
"long"          return java::Token_LONG;
"native"        return java::Token_NATIVE;
"new"           return java::Token_NEW;
"null"          return java::Token_NULL;
"package"       return java::Token_PACKAGE;
"private"       return java::Token_PRIVATE;
"protected"     return java::Token_PROTECTED;
"public"        return java::Token_PUBLIC;
"return"        return java::Token_RETURN;
"short"         return java::Token_SHORT;
"static"        return java::Token_STATIC;
"strictfp"      return java::Token_STRICTFP;
"super"         return java::Token_SUPER;
"switch"        return java::Token_SWITCH;
"synchronized"  return java::Token_SYNCHRONIZED;
"this"          return java::Token_THIS;
"throw"         return java::Token_THROW;
"throws"        return java::Token_THROWS;
"transient"     return java::Token_TRANSIENT;
"true"          return java::Token_TRUE;
"try"           return java::Token_TRY;
"void"          return java::Token_VOID;
"volatile"      return java::Token_VOLATILE;
"while"         return java::Token_WHILE;


 /* seperators */

"("             return java::Token_LPAREN;
")"             return java::Token_RPAREN;
"{"             return java::Token_LBRACE;
"}"             return java::Token_RBRACE;
"["             return java::Token_LBRACKET;
"]"             return java::Token_RBRACKET;
";"             return java::Token_SEMICOLON;
","             return java::Token_COMMA;
"."             return java::Token_DOT;
"@"             return java::Token_AT;


 /* operators */

"="             return java::Token_ASSIGN;
"<"             return java::Token_LESSTHAN;
"!"             return java::Token_BANG;
"~"             return java::Token_TILDE;
"?"             return java::Token_QUESTION;
":"             return java::Token_COLON;
"=="            return java::Token_EQUAL;
"<="            return java::Token_LESSEQUAL;
">="            return java::Token_GREATEREQUAL;
"!="            return java::Token_NOTEQUAL;
"&&"            return java::Token_LOG_AND;
"||"            return java::Token_LOG_OR;
"++"            return java::Token_INCREMENT;
"--"            return java::Token_DECREMENT;
"+"             return java::Token_PLUS;
"-"             return java::Token_MINUS;
"*"             return java::Token_STAR;
"/"             return java::Token_SLASH;
"&"             return java::Token_BIT_AND;
"|"             return java::Token_BIT_OR;
"^"             return java::Token_XOR;
"%"             return java::Token_REMAINDER;
"<<"            return java::Token_LSHIFT;
"+="            return java::Token_PLUSASSIGN;
"-="            return java::Token_MINUSASSIGN;
"*="            return java::Token_STARASSIGN;
"/="            return java::Token_SLASHASSIGN;
"&="            return java::Token_ANDASSIGN;
"|="            return java::Token_ORASSIGN;
"^="            return java::Token_XORASSIGN;
"%="            return java::Token_REMAINDERASSIGN;
"<<="           return java::Token_LSHIFTASSIGN;
">>="           return java::Token_RSIGNEDSHIFTASSIGN;
">>>="          return java::Token_RUNSIGNEDSHIFTASSIGN;
"..."           return java::Token_TRIPLEDOT;


 /* generics deserve special handling for ">", ">>" and ">>>" */

">"             return java::Token_GREATERTHAN;
">>"            return java::Token_RSIGNEDSHIFT;
">>>"           return java::Token_RUNSIGNEDSHIFT;


 /* identifiers: lame implementation, missing unicode and non-latin-letter support */

[a-zA-Z_$][0-9a-zA-Z_$]*  return java::Token_IDENTIFIER;


 /* literals */

 /* integers: decimal, hexadecimal and octal */
([1-9][0-9]*|0)[lL]?               return java::Token_INTEGER_LITERAL;
{HEX_NUMERAL}[lL]?                 return java::Token_INTEGER_LITERAL;
0[0-7]+[lL]?                       return java::Token_INTEGER_LITERAL;

 /* decimal floats */
[0-9]+\.[0-9]*{EXPONENT}?[fFdD]?   return java::Token_FLOATING_POINT_LITERAL;
\.[0-9]+{EXPONENT}?[fFdD]?          return java::Token_FLOATING_POINT_LITERAL;
[0-9]+{EXPONENT}[fFdD]?             return java::Token_FLOATING_POINT_LITERAL;
[0-9]+{EXPONENT}?[fFdD]             return java::Token_FLOATING_POINT_LITERAL;

 /* hexadecimal floats */
{HEX_NUMERAL}\.?{BINARY_EXPONENT}[fFdD]?     return java::Token_FLOATING_POINT_LITERAL;
{HEX_FLOAT_NUMERAL}{BINARY_EXPONENT}[fFdD]?  return java::Token_FLOATING_POINT_LITERAL;

 /* characters */
\'(.|\"|{ESCAPE_SEQUENCE})\'       return java::Token_CHARACTER_LITERAL;
("''"|\'..+\')                     printf("Invalid character escape: %s\n", yytext); assert(0);
 /* as flex can't handle unicode, the last one also dismisses many special characters,
    because it believes they consist of two characters (which isn't correct). */

 /* strings */
\"({ESCAPE_SEQUENCE}|[^\\\n])*\"   return java::Token_STRING_LITERAL;


. return yytext[0];

%%

int yywrap() { return 1; }
