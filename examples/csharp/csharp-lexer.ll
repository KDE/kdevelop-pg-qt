%{
/*****************************************************************************
 * This file is part of KDevelop.                                            *
 * Copyright (c) 2005, 2006 Jakob Petsovits <jpetso@gmx.at>                  *
 *                                                                           *
 * This program is free software; you can redistribute it and/or             *
 * modify it under the terms of the GNU Library General Public               *
 * License as published by the Free Software Foundation; either              *
 * version 2 of the License, or (at your option) any later version.          *
 *                                                                           *
 * This grammar is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Lesser General Public License for more details.                           *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public License *
 * along with this library; see the file COPYING.LIB.  If not, write to      *
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,      *
 * Boston, MA 02110-1301, USA.                                               *
 *****************************************************************************/


#include <iostream>
#include "csharp.h"

extern std::size_t _M_token_begin, _M_token_end;
extern char *_G_contents;
extern std::size_t _G_current_offset;

#define YY_INPUT(buf, result, max_size) \
  { \
    int c = _G_contents[_G_current_offset++]; \
    result = c == 0 ? YY_NULL : (buf[0] = c, 1); \
  }

#define YY_USER_INIT \
_M_token_begin = _M_token_end = 0; \
_G_current_offset = 0;

#define YY_USER_ACTION \
_M_token_begin = _M_token_end; \
_M_token_end += yyleng;

csharp* parser;

void lexer_restart(csharp* _parser) {
  parser = _parser;
  yyrestart(NULL);
  YY_USER_INIT
}

void reportProblem (const char* message)
{
  std::cerr << "Warning: " << message << std::endl;
}

%}


 /* UTF-8 sequences, generated with the Unicode.hs script from
  * http://lists.gnu.org/archive/html/help-flex/2005-01/msg00043.html */

 /* 0x0041-0x005a, 0x005f, 0x0061-0x007a: one byte in UTF-8 */
Letter1         [A-Z_a-z]
 /* 0x00c0-0x00d6, 0x00d8-0x00f6, 0x00f8-0x00ff */
Letter2         [\xC3]([\x80-\x96]|[\x98-\xB6]|[\xB8-\xBF])
 /* 0x0100-0x1fff */
Letter3         [\xC4-\xDF][\x80-\xBF]|([\xE0][\xA0-\xBF]|[\xE1][\x80-\xBF])[\x80-\xBF]
 /* 0x3040-0x318f */
Letter4         [\xE3]([\x86][\x80-\x8F]|[\x81-\x85][\x80-\xBF])
 /* 0x3300-0x337f */
Letter5         [\xE3][\x8C-\x8D][\x80-\xBF]
 /* 0x3400-0x3d2d */
Letter6         [\xE3](\xB4[\x80-\xAD]|[\x90-\xB3][\x80-\xBF])
 /* 0x4e00-0x9fff */
Letter7         ([\xE4][\xB8-\xBF]|[\xE5-\xE9][\x80-\xBF])[\x80-\xBF]
 /* 0xf900-0xfaff */
Letter8         [\xEF][\xA4-\xAB][\x80-\xBF]

Letter          {Letter1}|{Letter2}|{Letter3}|{Letter4}|{Letter5}|{Letter6}|{Letter7}|{Letter8}


 /* 0x0080-0xffff */
Multibyte1      ([\xC2-\xDF]|[\xE0][\xA0-\xBF]|[\xE1-\xEF][\x80-\xBF])[\x80-\xBF]
 /* 0x10000-0x10ffff */
Multibyte2      (\xF0[\x90-\xBF]|\xF4[\x80-\x8F]|[\xF1-\xF3][\x80-\xBF])[\x80-\xBF][\x80-\xBF]
 /* Unicode characters above 0x10ffff are not supported by C#. */
 /* Any multi-byte Unicode character. Single-byte ones are just . in lex. */
Multibyte       {Multibyte1}|{Multibyte2}


 /* 0x2028 and 0x2029, currently unused in this lexer
    for performance and convenience reasons. */
UnicodeNewLine  [\xE2][\x80][\xA8-\xA9]


 /* non-Unicode stuff */

Whitespace      [ \t\v\f]+
NewLine         "\r\n"|\r|\n
LineComment     "//"[^\r\n]*

DecimalDigit    [0-9]
HexDigit        [0-9a-fA-F]

ShortUnicodeEscape  [\\][u]{HexDigit}{HexDigit}{HexDigit}{HexDigit}
LongUnicodeEscape   [\\][U]{HexDigit}{HexDigit}{HexDigit}{HexDigit}{HexDigit}{HexDigit}{HexDigit}{HexDigit}
UnicodeEscape   {ShortUnicodeEscape}|{LongUnicodeEscape}
HexEscape       [\\][x]{HexDigit}{HexDigit}?{HexDigit}?{HexDigit}?
SimpleEscape    [\\]([']|["]|[\\]|[0abfnrtv])
Escape          {SimpleEscape}|{UnicodeEscape}|{HexEscape}

IntegerSuffix   ([Ll][Uu]?)|([Uu][Ll]?)
IntegerLiteral  {DecimalDigit}+{IntegerSuffix}?
HexNum          [0][xX]{HexDigit}+{IntegerSuffix}?

Sign            [+-]
RealSuffix      [fF]|[dD]|[mM]
Exponent        [eE]{Sign}?{DecimalDigit}+
Real1           {DecimalDigit}+[\.]{DecimalDigit}+{Exponent}?{RealSuffix}?
Real2           [\.]{DecimalDigit}+{Exponent}?{RealSuffix}?
Real3           {DecimalDigit}+{Exponent}{RealSuffix}?
Real4           {DecimalDigit}+{RealSuffix}
RealLiteral     {Real1}|{Real2}|{Real3}|{Real4}
InvalidReal     {DecimalDigit}+[\.]{Exponent}?{RealSuffix}?

AvailableIdentifier {Letter}({Letter}|{DecimalDigit})*
VerbatimIdentifier  [@]{Letter}({Letter}|{DecimalDigit})*
Identifier      {AvailableIdentifier}|{VerbatimIdentifier}

ppPrefix        ^{Whitespace}?[#]{Whitespace}?
ppNewLine       {Whitespace}?{LineComment}?{NewLine}


%x IN_BLOCKCOMMENT
%x PP_DECLARATION
%x PP_IF_CLAUSE
%x PP_ELSE_CLAUSE
%x PP_LINE
%x PP_MESSAGE
%x PP_PRAGMA
%x PP_SKIPPED_SECTION_PART

%%

 /* seperators */

"("             return csharp::Token_LPAREN;
")"             return csharp::Token_RPAREN;
"{"             return csharp::Token_LBRACE;
"}"             return csharp::Token_RBRACE;
"["             return csharp::Token_LBRACKET;
"]"             return csharp::Token_RBRACKET;
","             return csharp::Token_COMMA;
";"             return csharp::Token_SEMICOLON;
"."             return csharp::Token_DOT;


 /* operators */

":"             return csharp::Token_COLON;
"::"            return csharp::Token_COLONCOLON; // TODO: naming... new in 2.0?
"?"             return csharp::Token_QUESTION;
"??"            return csharp::Token_QUESTIONQUESTION; // TODO: naming... new in 2.0?
"!"             return csharp::Token_BANG;
"~"             return csharp::Token_TILDE;
"=="            return csharp::Token_EQUAL;
"<"             return csharp::Token_LESS_THAN;
"<="            return csharp::Token_LESS_EQUAL;
">"             return csharp::Token_GREATER_THAN;
">="            return csharp::Token_GREATER_EQUAL;
"!="            return csharp::Token_NOT_EQUAL;
"&&"            return csharp::Token_LOG_AND;
"||"            return csharp::Token_LOG_OR;
"->"            return csharp::Token_ARROW_RIGHT; // TODO: naming, CSharpParser.g calls it DEREF... new in 2.0 or not?
"++"            return csharp::Token_INCREMENT;
"--"            return csharp::Token_DECREMENT;
"="             return csharp::Token_ASSIGN;
"+"             return csharp::Token_PLUS;
"+="            return csharp::Token_PLUS_ASSIGN;
"-"             return csharp::Token_MINUS;
"-="            return csharp::Token_MINUS_ASSIGN;
"*"             return csharp::Token_STAR;
"*="            return csharp::Token_STAR_ASSIGN;
"/"             return csharp::Token_SLASH;
"/="            return csharp::Token_SLASH_ASSIGN;
"&"             return csharp::Token_BIT_AND;
"&="            return csharp::Token_BIT_AND_ASSIGN;
"|"             return csharp::Token_BIT_OR;
"|="            return csharp::Token_BIT_OR_ASSIGN;
"^"             return csharp::Token_BIT_XOR;
"^="            return csharp::Token_BIT_XOR_ASSIGN;
"%"             return csharp::Token_REMAINDER;
"%="            return csharp::Token_REMAINDER_ASSIGN;
"<<"            return csharp::Token_LSHIFT;
"<<="           return csharp::Token_LSHIFT_ASSIGN;
">>"            return csharp::Token_RSHIFT;
">>="           return csharp::Token_RSHIFT_ASSIGN;


 /* whitespace, newlines and comments */

{Whitespace}    /* skip */ ;
{NewLine}       /* { newLine(); } */ ;

{LineComment}   /* line comments, skip */ ;

"/*"            BEGIN(IN_BLOCKCOMMENT);
<IN_BLOCKCOMMENT>{
[^*\r\n]*       /* eat anything that's not a '*' */ ;
"*"+[^*/\r\n]*  /* eat up '*'s that are not followed by slashes or newlines */;
{NewLine}       /* { newLine(); } */ ;
"*"+"/"         BEGIN(INITIAL);
<<EOF>> {
    reportProblem("Encountered end of file in an unclosed block comment");
    BEGIN(INITIAL); // is not set automatically by yyrestart()
    return csharp::Token_EOF;
}
}


 /* characters and strings */

[']({Escape}|{Multibyte}|[^\\\r\n\'])[']   return csharp::Token_CHARACTER_LITERAL;
[']({Escape}|{Multibyte}|[\\][^\\\r\n\']|[^\\\r\n\'])*(([\\]?[\r\n])|[']) {
    reportProblem("Invalid character literal");
    std::cerr << yytext << std::endl;
    return csharp::Token_CHARACTER_LITERAL;
}

["]({Escape}|{Multibyte}|[^\\\r\n\"])*["]  return csharp::Token_STRING_LITERAL;
["]({Escape}|{Multibyte}|[\\][^\\\r\n\"]|[^\\\r\n\"])*(([\\]?[\r\n])|["]) {
    reportProblem("Invalid string literal");
    std::cerr << yytext << std::endl;
    return csharp::Token_STRING_LITERAL;
}
 /* verbatim strings: */
[@]["](["]["]|[^"])*["]                 return csharp::Token_STRING_LITERAL;


 /* reserved words */

"abstract"      return csharp::Token_ABSTRACT;
"as"            return csharp::Token_AS;
"base"          return csharp::Token_BASE;
"bool"          return csharp::Token_BOOL;
"break"         return csharp::Token_BREAK;
"byte"          return csharp::Token_BYTE;
"case"          return csharp::Token_CASE;
"catch"         return csharp::Token_CATCH;
"char"          return csharp::Token_CHAR;
"checked"       return csharp::Token_CHECKED;
"class"         return csharp::Token_CLASS;
"const"         return csharp::Token_CONST;
"continue"      return csharp::Token_CONTINUE;
"decimal"       return csharp::Token_DECIMAL;
"default"       return csharp::Token_DEFAULT;
"delegate"      return csharp::Token_DELEGATE;
"do"            return csharp::Token_DO;
"double"        return csharp::Token_DOUBLE;
"else"          return csharp::Token_ELSE;
"enum"          return csharp::Token_ENUM;
"event"         return csharp::Token_EVENT;
"explicit"      return csharp::Token_EXPLICIT;
"false"         return csharp::Token_FALSE;
"finally"       return csharp::Token_FINALLY;
"fixed"         return csharp::Token_FIXED;
"float"         return csharp::Token_FLOAT;
"for"           return csharp::Token_FOR;
"foreach"       return csharp::Token_FOREACH;
"goto"          return csharp::Token_GOTO;
"if"            return csharp::Token_IF;
"implicit"      return csharp::Token_IMPLICIT;
"in"            return csharp::Token_IN;
"int"           return csharp::Token_INT;
"interface"     return csharp::Token_INTERFACE;
"internal"      return csharp::Token_INTERNAL;
"is"            return csharp::Token_IS;
"lock"          return csharp::Token_LOCK;
"long"          return csharp::Token_LONG;
"namespace"     return csharp::Token_NAMESPACE;
"new"           return csharp::Token_NEW;
"null"          return csharp::Token_NULL;
"object"        return csharp::Token_OBJECT;
"operator"      return csharp::Token_OPERATOR;
"out"           return csharp::Token_OUT;
"override"      return csharp::Token_OVERRIDE;
"params"        return csharp::Token_PARAMS;
"private"       return csharp::Token_PRIVATE;
"protected"     return csharp::Token_PROTECTED;
"public"        return csharp::Token_PUBLIC;
"readonly"      return csharp::Token_READONLY;
"ref"           return csharp::Token_REF;
"return"        return csharp::Token_RETURN;
"sbyte"         return csharp::Token_SBYTE;
"sealed"        return csharp::Token_SEALED;
"short"         return csharp::Token_SHORT;
"sizeof"        return csharp::Token_SIZEOF;
"stackalloc"    return csharp::Token_STACKALLOC;
"static"        return csharp::Token_STATIC;
"string"        return csharp::Token_STRING;
"struct"        return csharp::Token_STRUCT;
"switch"        return csharp::Token_SWITCH;
"this"          return csharp::Token_THIS;
"throw"         return csharp::Token_THROW;
"true"          return csharp::Token_TRUE;
"try"           return csharp::Token_TRY;
"typeof"        return csharp::Token_TYPEOF;
"uint"          return csharp::Token_UINT;
"ulong"         return csharp::Token_ULONG;
"unchecked"     return csharp::Token_UNCHECKED;
"unsafe"        return csharp::Token_UNSAFE;
"ushort"        return csharp::Token_USHORT;
"using"         return csharp::Token_USING;
"virtual"       return csharp::Token_VIRTUAL;
"void"          return csharp::Token_VOID;
"volatile"      return csharp::Token_VOLATILE;
"while"         return csharp::Token_WHILE;


 /* TODO: what to do with those non-keyword identifiers?

"add"           return csharp::Token_ADD;
"alias"         return csharp::Token_ALIAS;
"get"           return csharp::Token_GET;
"global"        return csharp::Token_GLOBAL;
"partial"       return csharp::Token_PARTIAL;
"remove"        return csharp::Token_REMOVE;
"set"           return csharp::Token_SET;
"value"         return csharp::Token_VALUE;
"where"         return csharp::Token_WHERE;
"yield"         return csharp::Token_YIELD;
 */


 /* the pre-processor */

<INITIAL,PP_SKIPPED_SECTION_PART>{
{ppPrefix}"define"  BEGIN(PP_DECLARATION); return csharp::Token_PP_DEFINE;
{ppPrefix}"undef"   BEGIN(PP_DECLARATION); return csharp::Token_PP_UNDEF;
{ppPrefix}"if"      BEGIN(PP_IF_CLAUSE);   return csharp::Token_PP_IF;
{ppPrefix}"elif"    BEGIN(PP_IF_CLAUSE);   return csharp::Token_PP_ELIF;
{ppPrefix}"else"    BEGIN(PP_ELSE_CLAUSE); return csharp::Token_PP_ELSE;
{ppPrefix}"endif"{ppNewLine}               return csharp::Token_PP_ENDIF;
{ppPrefix}"line"    BEGIN(PP_LINE);        return csharp::Token_PP_LINE;
{ppPrefix}"error"{Whitespace}?      BEGIN(PP_MESSAGE); return csharp::Token_PP_ERROR;
{ppPrefix}"warning"{Whitespace}?    BEGIN(PP_MESSAGE); return csharp::Token_PP_WARNING;
{ppPrefix}"region"{Whitespace}?     BEGIN(PP_MESSAGE); return csharp::Token_PP_REGION;
{ppPrefix}"endregion"{Whitespace}?  BEGIN(PP_MESSAGE); return csharp::Token_PP_ENDREGION;
{ppPrefix}"pragma"{Whitespace}? {
    if( parser->compatibility_mode() >= csharp::csharp20_compatibility ) {
      BEGIN(PP_PRAGMA); return csharp::Token_PP_PRAGMA;
    }
    else {
      reportProblem("#pragma directives are not supported by C# 1.0");
      return csharp::Token_INVALID;
    }
}
{ppPrefix}{Identifier} {
    reportProblem("Invalid pre-processor directive");
    std::cerr << yytext << std::endl;
    return csharp::Token_INVALID;
}
}

<PP_DECLARATION>{
{Whitespace}        /* skip */ ;
"true"|"false" {
    reportProblem("You may not define ``true'' or ``false'' with #define or #undef");
    return csharp::Token_IDENTIFIER;  // we could do Token_INVALID here,
    // but this way the error is shown and the parser continues, I prefer this.
}
{Identifier}        return csharp::Token_PP_CONDITIONAL_SYMBOL; // ...including keywords
{ppNewLine}         BEGIN(INITIAL); return csharp::Token_PP_NEW_LINE;
.                   return csharp::Token_INVALID;
}

<PP_IF_CLAUSE>{
{Whitespace}        /* skip */ ;
"=="                return csharp::Token_EQUAL;
"!="                return csharp::Token_NOT_EQUAL;
"&&"                return csharp::Token_LOG_AND;
"||"                return csharp::Token_LOG_OR;
"!"                 return csharp::Token_BANG;
"true"              return csharp::Token_TRUE;
"false"             return csharp::Token_FALSE;
{Identifier}        return csharp::Token_PP_CONDITIONAL_SYMBOL;
{ppNewLine}         BEGIN(INITIAL); return csharp::Token_PP_NEW_LINE;
.                   return csharp::Token_INVALID;
}

<PP_ELSE_CLAUSE>{
{ppNewLine}         BEGIN(INITIAL); return csharp::Token_PP_NEW_LINE;
.                   return csharp::Token_INVALID;
}

 /* TODO: not yet used, */
 /* has to be switched on and off in collaboration with the parser */
<PP_SKIPPED_SECTION_PART>{
{Whitespace}?([^#\r\n][^\r\n]*)?{NewLine}  /* skip */ ;
.                   return csharp::Token_INVALID;
}

<PP_LINE>{
{Whitespace}        /* skip */ ;
{ppNewLine}         BEGIN(INITIAL);
{DecimalDigit}+     return csharp::Token_PP_LINE_NUMBER;
["][^\"\r\n]["]     return csharp::Token_PP_FILE_NAME;
"default"           return csharp::Token_DEFAULT;
{Identifier}        return csharp::Token_PP_IDENTIFIER_OR_KEYWORD;
.                   return csharp::Token_INVALID;
}

<PP_MESSAGE>{
[^\r\n]             return csharp::Token_PP_MESSAGE;
{NewLine}           BEGIN(INITIAL); return csharp::Token_PP_NEW_LINE;
}

<PP_PRAGMA>{
[^\r\n]             return csharp::Token_PP_PRAGMA_TEXT;
{NewLine}           BEGIN(INITIAL); return csharp::Token_PP_NEW_LINE;
}


 /* identifiers and number literals */

{Identifier}        return csharp::Token_IDENTIFIER;

{IntegerLiteral}    return csharp::Token_INTEGER_LITERAL;
{RealLiteral}       return csharp::Token_REAL_LITERAL;

 /* enable once you know that it doesn't mess up correct programs
{InvalidReal}       {
    reportProblem("Invalid real number: Things like ``1.'' are not allowed, it must be ``1.0''");
    std::cerr << yytext << std::endl;
    return csharp::Token_REAL_LITERAL;
}
 */


 /* everything else is not a valid lexeme */

.                   return csharp::Token_INVALID;

%%

int yywrap() { return 1; }
