/* 
 * Copyright 2005, 2006 Jakob Petsovits <jpetso@gmx.at>
 * Based on QMake Parser Copyright 2006 Andreas Pakulat <apaku@gmx.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include "factlexer.h"

#include <QString>
#include <QStringList>
#include <QDebug>
#include "factparser.h"
#include <kdev-pg-location-table.h>
#include <kdev-pg-token-stream.h>

using namespace fact;

Lexer::Lexer( Parser* _parser, const QString& content ):
        m_content( content ), m_parser( _parser ),
        m_curpos( 0 ), m_contentSize( m_content.size() ),
        m_tokenBegin( 0 ), m_tokenEnd( 0 )
{
    pushState( ErrorState );
    pushState( DefaultState );
}

int Lexer::state() const
{
    return mState.top();
}

void Lexer::pushState( int state )
{
    mState.push( state );
}

void Lexer::popState()
{
    mState.pop();
}

int Lexer::nextTokenKind()
{
    int token = Parser::Token_INVALID;
    if ( m_curpos >= m_contentSize )
    {
        return 0;
    }
    QChar* it = m_content.data();
    it += m_curpos;

    // Ignore whitespace
    while ( m_curpos < m_contentSize && ( it->isSpace() ) )
    {
        if (it->unicode() == '\n') {
            createNewline(m_curpos);
        }
        ++it;
        ++m_curpos;
    }

    switch ( state() )
    {
        case DefaultState:
            m_tokenBegin = m_curpos;
            if ( m_curpos < m_contentSize )
            {
                if ( it->isLetter() )
                {
                    QString identifier;
                    while ( m_curpos < m_contentSize && ( it->isLetter() || it->isDigit() ) && !it->isSpace() ) {
                        identifier.append(*it);
                        ++it;
                        ++m_curpos;
                    }
                    m_curpos--;
                    QChar* it1 = m_content.data();
                    it1 += m_curpos;

                    if ( identifier == "if" ) {
                        token = Parser::Token_IF;
                    } else if ( identifier == "else" ) {
                        token = Parser::Token_ELSE;
                    } else if ( identifier == "var" ) {
                        token = Parser::Token_VAR;
                    } else if ( identifier == "function" ) {
                        token = Parser::Token_FUNCTION;
                    } else if ( identifier == "return" ) {
                        token = Parser::Token_RETURN;
                    } else {
                        token = Parser::Token_IDENTIFIER;
                    }
                }
                else if ( it->isDigit() )
                {
                    token = Parser::Token_NUMBER;
                    while ( m_curpos < m_contentSize && ( it->isDigit() ) ) {
                        ++it;
                        ++m_curpos;
                    }
                    --m_curpos;
                }
                else
                {
                    switch ( it->unicode() )
                    {
                        case ',':
                            token = Parser::Token_COMMA;
                            break;
                        case ';':
                            token = Parser::Token_SEMICOLON;
                            break;
                        case '(':
                            token = Parser::Token_LPAREN;
                            break;
                        case ')':
                            token = Parser::Token_RPAREN;
                            break;
                        case '{':
                            token = Parser::Token_LBRACE;
                            break;
                        case '}':
                            token = Parser::Token_RBRACE;
                            break;
                        case '=':
                        {
                            QChar* c2 = m_curpos < m_contentSize ? it + 1 : 0 ;
                            if ( c2 && c2->unicode() == '=' )
                            {
                                m_curpos++;
                                token = Parser::Token_EQUAL;
                            } else {
                                token = Parser::Token_ASSIGN;
                            }
                            break;
                        }
                        case '*':
                            token = Parser::Token_STAR;
                            break;
                        case '-':
                            token = Parser::Token_MINUS;
                            break;
                        default:
                            break;
                    }
                }
            }
            break;
        default:
            token = Parser::Token_INVALID;
            break;
    }
    if ( m_curpos >= m_contentSize )
    {
        return 0;
    }
    m_tokenEnd = m_curpos;
    m_curpos++;
    return token;
}

qint64 Lexer::tokenBegin() const
{
  return m_tokenBegin;
}

qint64 Lexer::tokenEnd() const
{
  return m_tokenEnd;
}

void Lexer::createNewline( int pos )
{
    if( m_parser )
        m_parser->tokenStream->locationTable()->newline( pos );
}
// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
