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
#include "java.h"

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

java* parser;

void lexer_restart(java* _parser) {
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

 /* \u0024, \u0041-\u005a, \u005f, \u0061-\u007a: one byte in UTF-8 */
Letter1         [$A-Z_a-z]
 /* \u00c0-\u00d6, \u00d8-\u00f6, \u00f8-\u00ff */
Letter2         [\xC3]([\x80-\x96]|[\x98-\xB6]|[\xB8-\xBF])
 /* \u0100-\u1fff */
Letter3         [\xC4-\xDF][\x80-\xBF]|([\xE0][\xA0-\xBF]|[\xE1][\x80-\xBF])[\x80-\xBF]
 /* \u3040-\u318f */
Letter4         [\xE3]([\x86][\x80-\x8F]|[\x81-\x85][\x80-\xBF])
 /* \u3300-\u337f */
Letter5         [\xE3][\x8C-\x8D][\x80-\xBF]
 /* \u3400-\u3d2d */
Letter6         [\xE3](\xB4[\x80-\xAD]|[\x90-\xB3][\x80-\xBF])
 /* \u4e00-\u9fff */
Letter7         ([\xE4][\xB8-\xBF]|[\xE5-\xE9][\x80-\xBF])[\x80-\xBF]
 /* \uf900-\ufaff */
Letter8         [\xEF][\xA4-\xAB][\x80-\xBF]

Letter          {Letter1}|{Letter2}|{Letter3}|{Letter4}|{Letter5}|{Letter6}|{Letter7}|{Letter8}

 /* \u0030-\u0039: ISO-LATIN-1 digits */
Digit1          [0-9]
 /* \u0660-\u0669, \u06f0-\u06f9: Arabic-Indic and extended Ar.-Indic digits */
Digit2          [\xD9][\xA0-\xA9]|[\xDB][\xB0-\xB9]
 /* \u0966-\u096f, \u09e6-\u09ef: Devanagari digits */
Digit3          [\xE0]([\xA5]|[\xA7])[\xA6-\xAF]
 /* \u0a66-\u0a6f, \u0ae6-\u0aef */
Digit4          [\xE0]([\xA9]|[\xAB])[\xA6-\xAF]
 /* \u0b66-\u0b6f, \u0be7-\u0bef */
Digit5          [\xE0]([\xAD][\xA6-\xAF]|[\xAF][\xA7-\xAF])
 /* \u0c66-\u0c6f, \u0ce6-\u0cef, \u0d66-\u0d6f */
Digit6          [\xE0]([\xB1]|[\xB3]|[\xB5])[\xA6-\xAF]
 /* \u0e50-\u0e59, \u0ed0-\u0ed9 */
Digit7          [\xE0]([\xB9]|[\xBB])[\x90-\x99]
 /* \u1040-\u1049 */
Digit8          [\xE1][\x81][\x80-\x89]
 /* \uff10-\uff19: Fullwidth digits */
Digit9          [\xEF][\xBC][\x90-\x99]

 /* \u0080-\uffff */
Multibyte1      ([\xC2-\xDF]|[\xE0][\xA0-\xBF]|[\xE1-\xEF][\x80-\xBF])[\x80-\xBF]
 /* \u10000-\u1fffff */
Multibyte2      ([\xF0][\x90-\xBF]|[\xF1-\xF7][\x80-\xBF])[\x80-\xBF][\x80-\xBF]
 /* \u200000-\u3ffffff */
Multibyte3      ([\xF8][\x88-\xBF]|[\xF9-\xFB][\x80-\xBF])[\x80-\xBF][\x80-\xBF][\x80-\xBF]
 /* \u4000000-\u7fffffff */
Multibyte4      ([\xFC][\x84-\xBF]|[\xFD][\x80-\xBF])[\x80-\xBF][\x80-\xBF][\x80-\xBF]
 /* Any multi-byte Unicode character. Single-byte ones are just . in lex. */
Multibyte       {Multibyte1}|{Multibyte2}|{Multibyte3}|{Multibyte4}


 /* non-Unicode stuff */

HexDigit        [0-9a-fA-F]
Digit           {Digit1}|{Digit2}|{Digit3}|{Digit4}|{Digit5}|{Digit6}|{Digit7}|{Digit8}|{Digit9}
OctalDigit      [0-7]
NonZeroDigit    [1-9]

UnicodeEscape   [\\][u]+{HexDigit}{HexDigit}{HexDigit}{HexDigit}
OctalEscape     [\\]{OctalDigit}({Digit}({Digit})?)?
SimpleEscape    [\\]([']|["]|[\\]|[rnbft])
Escape          {SimpleEscape}|{UnicodeEscape}|{OctalEscape}

IntSuffix       [Ll]
DecimalNum      ([0]|{NonZeroDigit}{Digit}*){IntSuffix}?
OctalNum        [0]{OctalDigit}+{IntSuffix}?
HexNum          [0][xX]{HexDigit}+{IntSuffix}?
IntegerLiteral  {DecimalNum}|{OctalNum}|{HexNum}

Sign            [+-]
FloatSuffix     [fF]|[dD]
SignedInt       {Sign}?{Digit}+
DecimalExponent [eE]{SignedInt}?
BinaryExponent  [pP]{SignedInt}?
Float1          {Digit}+[\.]{Digit}*{DecimalExponent}?{FloatSuffix}?
Float2          [\.]{Digit}+{DecimalExponent}?{FloatSuffix}?
Float3          {Digit}+{DecimalExponent}{FloatSuffix}?
Float4          {Digit}+{DecimalExponent}?{FloatSuffix}
HexFloatNum     [0][xX]{HexDigit}*[\.]{HexDigit}+
HexFloat1       {HexNum}[\.]?{BinaryExponent}{FloatSuffix}?
HexFloat2       {HexFloatNum}{BinaryExponent}{FloatSuffix}?
FloatingPoint   {Float1}|{Float2}|{Float3}|{Float4}|{HexFloat1}|{HexFloat2}


%x IN_BLOCKCOMMENT

%%

 /* seperators */

"("             return java::Token_LPAREN;
")"             return java::Token_RPAREN;
"{"             return java::Token_LBRACE;
"}"             return java::Token_RBRACE;
"["             return java::Token_LBRACKET;
"]"             return java::Token_RBRACKET;
","             return java::Token_COMMA;
";"             return java::Token_SEMICOLON;
"."             return java::Token_DOT;
"@"             {
    if (parser->compatibility_mode() >= java::java15_compatibility)
      return java::Token_AT;
    else {
      reportProblem("Annotations are not supported by Java 1.4 or earlier");
      return java::Token_INVALID;
    }
}


 /* operators */

"?"             return java::Token_QUESTION;
":"             return java::Token_COLON;
"!"             return java::Token_BANG;
"~"             return java::Token_TILDE;
"=="            return java::Token_EQUAL;
"<"             return java::Token_LESS_THAN;
"<="            return java::Token_LESS_EQUAL;
">"             return java::Token_GREATER_THAN;
">="            return java::Token_GREATER_EQUAL;
"!="            return java::Token_NOT_EQUAL;
"&&"            return java::Token_LOG_AND;
"||"            return java::Token_LOG_OR;
"++"            return java::Token_INCREMENT;
"--"            return java::Token_DECREMENT;
"="             return java::Token_ASSIGN;
"+"             return java::Token_PLUS;
"+="            return java::Token_PLUS_ASSIGN;
"-"             return java::Token_MINUS;
"-="            return java::Token_MINUS_ASSIGN;
"*"             return java::Token_STAR;
"*="            return java::Token_STAR_ASSIGN;
"/"             return java::Token_SLASH;
"/="            return java::Token_SLASH_ASSIGN;
"&"             return java::Token_BIT_AND;
"&="            return java::Token_BIT_AND_ASSIGN;
"|"             return java::Token_BIT_OR;
"|="            return java::Token_BIT_OR_ASSIGN;
"^"             return java::Token_BIT_XOR;
"^="            return java::Token_BIT_XOR_ASSIGN;
"%"             return java::Token_REMAINDER;
"%="            return java::Token_REMAINDER_ASSIGN;
"<<"            return java::Token_LSHIFT;
"<<="           return java::Token_LSHIFT_ASSIGN;
">>"            return java::Token_SIGNED_RSHIFT;
">>="           return java::Token_SIGNED_RSHIFT_ASSIGN;
">>>"           return java::Token_UNSIGNED_RSHIFT;
">>>="          return java::Token_UNSIGNED_RSHIFT_ASSIGN;
"..."           {
    if (parser->compatibility_mode() >= java::java15_compatibility)
      return java::Token_ELLIPSIS;
    else {
      reportProblem("Variable-length argument lists are not supported "
                    "by Java 1.4 or earlier");
      return java::Token_INVALID;
    }
}


 /* whitespace, newlines and comments */

[ \f\t]+        /* skip */ ;
"\r\n"|\r|\n    /* { newLine(); } */ ;

"//"[^\r\n]*    /* line comments, skip */ ;

"/*"            BEGIN(IN_BLOCKCOMMENT);
<IN_BLOCKCOMMENT>{
[^*\r\n]*       /* eat anything that's not a '*' */ ;
"*"+[^*/\r\n]*  /* eat up '*'s that are not followed by slashes or newlines */;
"\r\n"|\r|\n    /* { newLine(); } */ ;
"*"+"/"         BEGIN(INITIAL);
<<EOF>> {
    reportProblem("Encountered end of file in an unclosed block comment");
    BEGIN(INITIAL); // is not set automatically by yyrestart()
    return java::Token_EOF;
}
}


 /* characters and strings */

[']({Escape}|{Multibyte}|[^\\\r\n\'])[']   return java::Token_CHARACTER_LITERAL;
[']({Escape}|{Multibyte}|[\\][^\\\r\n\']|[^\\\r\n\'])*([\\]?[\r\n]|[']) {
    reportProblem("Invalid character literal");
    std::cerr << yytext << std::endl;
    return java::Token_CHARACTER_LITERAL;
}

["]({Escape}|{Multibyte}|[^\\\r\n\"])*["]  return java::Token_STRING_LITERAL;
["]({Escape}|{Multibyte}|[\\][^\\\r\n\"]|[^\\\r\n\"])*([\\]?[\r\n]|["]) {
    reportProblem("Invalid string literal");
    std::cerr << yytext << std::endl;
    return java::Token_STRING_LITERAL;
}


 /* reserved words */

"abstract"      return java::Token_ABSTRACT;
"assert"        {
    if (parser->compatibility_mode() >= java::java14_compatibility)
      return java::Token_ASSERT;
    else
      return java::Token_IDENTIFIER;
}
"boolean"       return java::Token_BOOLEAN;
"break"         return java::Token_BREAK;
"byte"          return java::Token_BYTE;
"case"          return java::Token_CASE;
"catch"         return java::Token_CATCH;
"char"          return java::Token_CHAR;
"class"         return java::Token_CLASS;
"const"         {
    reportProblem("\"const\": reserved but unused (invalid) keyword");
    return java::Token_CONST;
}
"continue"      return java::Token_CONTINUE;
"default"       return java::Token_DEFAULT;
"do"            return java::Token_DO;
"double"        return java::Token_DOUBLE;
"else"          return java::Token_ELSE;
"enum"          {
    if (parser->compatibility_mode() >= java::java15_compatibility)
      return java::Token_ENUM;
    else
      return java::Token_IDENTIFIER;
}
"extends"       return java::Token_EXTENDS;
"false"         return java::Token_FALSE;
"final"         return java::Token_FINAL;
"finally"       return java::Token_FINALLY;
"float"         return java::Token_FLOAT;
"for"           return java::Token_FOR;
"goto"          {
    reportProblem("\"goto\": reserved but unused (invalid) keyword");
    return java::Token_GOTO;
}
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


 /* identifiers and number literals */

{Letter}({Letter}|{Digit})*  return java::Token_IDENTIFIER;

{IntegerLiteral}   return java::Token_INTEGER_LITERAL;
{FloatingPoint}    return java::Token_FLOATING_POINT_LITERAL;


 /* everything else is not a valid lexeme */

.               return java::Token_INVALID;

%%

int yywrap() { return 1; }
