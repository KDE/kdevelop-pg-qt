/* 
    SPDX-FileCopyrightText: 2008 Niko Sams <niko.sams@gmail.com>
    Based on QMake Parser Copyright 2006 Andreas Pakulat <apaku@gmx.de>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "factparser.h"

#include <QStack>
#include <QString>

namespace fact
{

class Parser;

class Lexer
{
public:
    Lexer( fact::Parser *parser, const QString& contents);

    int nextTokenKind();
    qint64 tokenBegin() const;
    qint64 tokenEnd() const;

private:
    QString m_content;
    Parser* m_parser;
    int m_curpos;
    int m_contentSize;
    qint64 m_tokenBegin;
    qint64 m_tokenEnd;

    int state() const;
    void pushState(int state);
    void popState();
    void createNewline( int pos );

    QStack<int> mState;
    enum State
    {
        ErrorState = -1,
        DefaultState = 0
    };
};

} // end of namespace fact

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
