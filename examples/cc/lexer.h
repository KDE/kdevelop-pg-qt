/*
    SPDX-FileCopyrightText: 2005, 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "ccparser.h"

#include <iostream>

#ifndef DONT_INCLUDE_FLEXLEXER
#include "FlexLexer.h"
#endif

// The YY_USER_ACTION macro is called whenever a token is found by Flex
#define YY_USER_ACTION \
m_tokenBegin = m_tokenEnd; \
m_tokenEnd += yyleng;


namespace cc
{

class Lexer : public yyFlexLexer
{
public:
    Lexer( cc::Parser *parser, char *contents );
    void restart( cc::Parser *parser, char *contents );

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
    cc::Parser* m_parser;
    char *m_contents;
    std::size_t m_tokenBegin, m_tokenEnd;
    std::size_t m_currentOffset;
    KDevPG::LocationTable *m_locationTable;
};

} // end of namespace cc

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
