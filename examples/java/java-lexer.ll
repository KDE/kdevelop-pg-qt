%{
#include <iostream>
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

void reportProblem (const char* message)
{
  std::cerr << "Warning: " << message << std::endl;
}

/*
#define MAX_STRING_BUF 1024
char string_buf[MAX_STRING_BUF];
char* string_buf_ptr = 0;
 */

%}

HexDigit        [0-9a-fA-F]
Digit           [0-9]
OctalDigit      [0-7]
NonZeroDigit    [1-9]

Unicode         [\\][u]+{HexDigit}{HexDigit}{HexDigit}{HexDigit}
Octal           [\\]{OctalDigit}({Digit}({Digit})?)?
Escape          [\\]([r]|[n]|[b]|[f]|[t]|[\\]|[']|["])|{Unicode}|{Octal}

IntSuffix       ([l]|[L])
DecimalNum      ([0]|{NonZeroDigit}{Digit}*){IntSuffix}?
OctalNum        [0]{OctalDigit}+{IntSuffix}?
HexNum          [0]([x]|[X]){HexDigit}+{IntSuffix}?
IntegerLiteral  ({DecimalNum}|{OctalNum}|{HexNum})

Sign            ([\+]|[\-])
FloatSuffix     ([f]|[F]|[d]|[D])
SignedInt       {Sign}?{Digit}+
DecimalExpSign  ([e]|[E])
BinaryExpSign   ([p]|[P])
DecimalExponent {DecimalExpSign}{SignedInt}?
BinaryExponent  {BinaryExpSign}{SignedInt}?
Float1          {Digit}+[\.]{Digit}*{DecimalExponent}?{FloatSuffix}?
Float2          [\.]{Digit}+{DecimalExponent}?{FloatSuffix}?
Float3          {Digit}+{DecimalExponent}{FloatSuffix}?
Float4          {Digit}+{DecimalExponent}?{FloatSuffix}
HexFloatNum     [0]([x]|[X]){HexDigit}*[\.]{HexDigit}+
HexFloat1       {HexNum}[\.]?{BinaryExponent}{FloatSuffix}?
HexFloat2       {HexFloatNum}{BinaryExponent}{FloatSuffix}?
FloatingPoint   ({Float1}|{Float2}|{Float3}|{Float4}|{HexFloat1}|{HexFloat2})


 // %x IN_STRING  // for the ANTLR version, not used at the moment
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
    if (compatibility_mode() >= java15_compatibility)
      return java::Token_AT;
    else {
      reportProblem("Annotations are not supported by Java 1.4 or earlier.");
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
    if (compatibility_mode() >= java15_compatibility)
      return java::Token_TRIPLE_DOT;
    else {
      reportProblem("Variable-length argument lists are not supported "
                    "by Java 1.4 or earlier.");
      return java::Token_INVALID;
    }
}

[ \f\t]         /* skip */ ;
"\r\n"|\r|\n    /* { newLine(); } */ ;

"//"[^\r\n]*          /* line comments, skip */ ;

"/*"            BEGIN(IN_BLOCKCOMMENT);
<IN_BLOCKCOMMENT>{
[^*\r\n]*       /* eat anything that's not a '*' */ ;
"*"+[^*/\r\n]*  /* eat up '*'s not followed by '/'s */ ;
"\r\n"|\r|\n    /* { newLine(); } */ ;
"*"+"/"         BEGIN(INITIAL);
}


 /* characters and strings */

[\']({Escape}|[^\r\n\'])[\']    return java::Token_CHARACTER_LITERAL;
[\']({Escape}|[\\][^\\\r\n\']|[^\\\r\n\'])*(([\\]?([\r]|[\n]))|[\']) {
    reportProblem("Invalid character literal...");
    std::cerr << yytext << std::endl;
    return java::Token_CHARACTER_LITERAL;
}

[\"]({Escape}|[^\\\r\n\"])*\"  return java::Token_STRING_LITERAL;
[\"]({Escape}|[\\][^\\\r\n\"]|[^\\\r\n\"])*(([\\]?([\r]|[\n]))|[\"]) {
    reportProblem("Invalid string literal...");
    std::cerr << yytext << std::endl;
    return java::Token_STRING_LITERAL;
}


 /* This is the ANTLR version, counting newlines and storing
  * string values in a seperate buffer.
[\"] {
    BEGIN(IN_STRING);
    string_buf_ptr = string_buf;
}
<string>{
\" {
    BEGIN(INITIAL);
    *string_buf_ptr = '\0';
    return java::Token_STRING_LITERAL;
}
{Octal} {
    int result;
    sscanf( yytext + 1, "%o", &result );
    *string_buf_ptr++ = result;
}
{Unicode} {
    int result;
    sscanf( yytext + 1, "%x", &result );
    *string_buf_ptr++ = result;
}
\\n         *string_buf_ptr++ = '\n';
\\t         *string_buf_ptr++ = '\t';
\\r         *string_buf_ptr++ = '\r';
\\b         *string_buf_ptr++ = '\b';
\\f         *string_buf_ptr++ = '\f';
\\(.|\n)    *string_buf_ptr++ = yytext[1];
[^\\\n\"]+ {
    char *yptr = yytext;

    while ( *yptr )
        *string_buf_ptr++ = *yptr++;
    }
}	// end string states
 */

 /* reserved words */

"abstract"      return java::Token_ABSTRACT;
"assert"        {
    if (compatibility_mode() >= java14_compatibility)
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
"const"         return java::Token_CONST;
"continue"      return java::Token_CONTINUE;
"default"       return java::Token_DEFAULT;
"do"            return java::Token_DO;
"double"        return java::Token_DOUBLE;
"else"          return java::Token_ELSE;
"enum"          {
    if (compatibility_mode() >= java15_compatibility)
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



 /* identifiers: lame implementation, missing unicode and non-latin-letter support */

[a-zA-Z_$#][0-9a-zA-Z_$#]*  return java::Token_IDENTIFIER;

{IntegerLiteral}   return java::Token_INTEGER_LITERAL;
{FloatingPoint}    return java::Token_FLOATING_POINT_LITERAL;

.               return java::Token_INVALID;

%%

int yywrap() { return 1; }
