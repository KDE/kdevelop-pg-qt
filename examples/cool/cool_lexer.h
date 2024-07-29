/*
    SPDX-FileCopyrightText: 2005, 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LicenseRef-MIT-KDevelop-PG-Qt
*/

#include "coolparser.h"

#include <iostream>

#include <QString>
#include <string>

#ifndef DONT_INCLUDE_FLEXLEXER
#include <FlexLexer.h>
#endif

// The YY_USER_ACTION macro is called whenever a token is found by Flex
#define YY_USER_ACTION \
m_tokenBegin = m_tokenEnd; \
m_tokenEnd += yyleng;


namespace cool
{

class Lexer : public yyFlexLexer
{
public:
    Lexer( cool::Parser *parser, char *contents );
    void restart( cool::Parser *parser, char *contents );

    int yylex();
    char *contents()         { return m_contents;   }
    std::size_t tokenBegin() { return m_tokenBegin; }
    std::size_t tokenEnd()   { return m_tokenEnd;   }

protected:
    // custom input, replacing the Flex default input stdin
    virtual int LexerInput( char *buf, int max_size );

    // dismisses any lexer output (which should not happen anyways)
    virtual void LexerOutput( const char * /*buf*/, int /*max_size*/ ) { return; }
    virtual void LexerError( const char */*msg*/ ) { return; }

private:
    cool::Parser* m_parser;
    char *m_contents;
    std::size_t m_tokenBegin, m_tokenEnd;
    std::size_t m_currentOffset;
    KDevPG::LocationTable *m_locationTable;
};

} // end of namespace cool

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
