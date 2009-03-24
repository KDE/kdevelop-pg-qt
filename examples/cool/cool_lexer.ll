
%option c++
%option yyclass="cool::Lexer"
%option noyywrap


%{

#define DONT_INCLUDE_FLEXLEXER
#include "cool_lexer.h"

%}


Whitespace  [ \t\f\n]

%x IN_BLOCKCOMMENT

%%

 /* whitespace, newlines and comments */

{Whitespace}+   /* skip */ ;
"--".*          /* line comments, skip */ ;

"(*"                    BEGIN(IN_BLOCKCOMMENT);
<IN_BLOCKCOMMENT>{
"*)"            BEGIN(INITIAL);
<<EOF>>         return cool::Parser::Token_EOF;
[\n]            /* skip */ ;
.               /* skip */ ;
}


 /* seperators */

"("             return cool::Parser::Token_LPAREN;
")"             return cool::Parser::Token_RPAREN;
"{"             return cool::Parser::Token_LBRACE;
"}"             return cool::Parser::Token_RBRACE;
";"             return cool::Parser::Token_SEMICOLON;
","             return cool::Parser::Token_COMMA;
"."             return cool::Parser::Token_DOT;
"@"             return cool::Parser::Token_AT;


 /* operators */

"+"             return cool::Parser::Token_PLUS;
"-"             return cool::Parser::Token_MINUS;
"*"             return cool::Parser::Token_STAR;
"/"             return cool::Parser::Token_SLASH;
"="             return cool::Parser::Token_EQUAL;
"<="            return cool::Parser::Token_LESS_EQUAL;
"<"             return cool::Parser::Token_LESS;
":"             return cool::Parser::Token_COLON;
"<-"            return cool::Parser::Token_ARROW_LEFT;
"=>"            return cool::Parser::Token_ARROW_RIGHT;
"~"             return cool::Parser::Token_TILDE;
"not"           return cool::Parser::Token_NOT;
"isvoid"        return cool::Parser::Token_ISVOID;


 /* reserved words */

"case"          return cool::Parser::Token_CASE;
"esac"          return cool::Parser::Token_ESAC;
"class"         return cool::Parser::Token_CLASS;
"Class"         return cool::Parser::Token_CLASS;
"else"          return cool::Parser::Token_ELSE;
"false"         return cool::Parser::Token_FALSE;
"if"            return cool::Parser::Token_IF;
"in"            return cool::Parser::Token_IN;
"fi"            return cool::Parser::Token_FI;
"inherits"      return cool::Parser::Token_INHERITS;
"let"           return cool::Parser::Token_LET;
"loop"          return cool::Parser::Token_LOOP;
"new"           return cool::Parser::Token_NEW;
"of"            return cool::Parser::Token_OF;
"pool"          return cool::Parser::Token_POOL;
"then"          return cool::Parser::Token_THEN;
"true"          return cool::Parser::Token_TRUE;
"while"         return cool::Parser::Token_WHILE;


 /* literals */

"\""([^"\\]|\\.)*"\""   return cool::Parser::Token_STRING;

[A-Z][a-zA-Z0-9_]*      return cool::Parser::Token_TYPE;
[a-z_][a-zA-Z0-9_]*     return cool::Parser::Token_IDENTIFIER;
[0-9]+          return cool::Parser::Token_INTEGER;


 /* everything else is not a valid lexeme */

.               return cool::Parser::Token_INVALID;

%%

namespace cool
{

Lexer::Lexer( Parser *parser, char *contents )
{
    restart( parser, contents );
}

void Lexer::restart( Parser *parser, char *contents )
{
    m_parser = parser;
    m_locationTable = parser->tokenStream->locationTable();
    m_contents = contents;
    m_tokenBegin = m_tokenEnd = 0;
    m_currentOffset = 0;

    // check for and ignore the UTF-8 byte order mark
    unsigned char *ucontents = (unsigned char *) m_contents;
    if ( ucontents[0] == 0xEF && ucontents[1] == 0xBB && ucontents[2] == 0xBF )
    {
        m_tokenBegin = m_tokenEnd = 3;
        m_currentOffset = 3;
    }

    yyrestart(NULL);
    BEGIN(INITIAL); // is not set automatically by yyrestart()
}

// reads a character, and returns 1 as the number of characters read
// (or 0 when the end of the string is reached)
int Lexer::LexerInput( char *buf, int /*max_size*/ )
{
    int c = m_contents[ m_currentOffset++ ];

    switch(c)
    {
    case '\r':
        c = '\n'; // only have one single line break character: '\n'
        if ( m_contents[m_currentOffset + 1] == '\n' )
        {
            m_currentOffset++;
            m_tokenEnd++;
        }

        // fall through
    case '\n':
        m_locationTable->newline( m_currentOffset );
        break;

    default:
        break;
    }

    return (c == 0) ? 0 : (buf[0] = c, 1);
}

} // end of namespace cool

