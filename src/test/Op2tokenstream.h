#ifndef OP2_TOKENSTREAM
#define OP2_TOKENSTREAM

#include "Op2parser.h"
#include <kdebug.h>
#include <QString>
#include <kdev-pg-token-stream.h>

namespace Op2
{

class TokenStream : public KDevPG::TokenStream
{
    QString m_content;
public:
    TokenStream(const QString& content) : m_content(content)
    {
        for(int i = 0; i != content.size(); ++i)
        {
            if(content[i] == ' ')
            {
                continue;
            }
            
            Parser::Token &t = next();
            t.begin = i;if(content[i] == '\n')
            {
                t.kind = Parser::Token_BR;
                t.end = i;
            }
            else if(content.mid(i, 3) == "bin")
            {
                t.kind = Parser::Token_BIN;
                t.end = i + 2;
            }
            else if(content.mid(i, 4) == "tern")
            {
                t.kind = Parser::Token_TERN;
                t.end = i + 3;
            }
            else if(content.mid(i, 3) == "pre")
            {
                t.kind = Parser::Token_PRE;
                t.end = i + 2;
            }
            else if(content.mid(i, 4) == "post")
            {
                t.kind = Parser::Token_POST;
                t.end = i + 3;
            }
            else if(content.mid(i, 5) == "paren")
            {
                t.kind = Parser::Token_PAREN;
                t.end = i + 4;
            }
            else if(content.mid(i, 4) == "left")
            {
                t.kind = Parser::Token_LEFT;
                t.end = i + 3;
            }
            else if(content.mid(i, 5) == "right")
            {
                t.kind = Parser::Token_RIGHT;
                t.end = i + 4;
            }
            else if(content[i] >= '0' && content[i] <= '9')
            {
                t.end = i + 1;
                while(t.end != content.size() && content[(uint)t.end] >= '0' && content[(uint)t.end] <= '9')
                    ++t.end;
                --t.end;
                t.kind = Parser::Token_NUMBER;
            }
            else
            {
                t.end = i;
                t.kind = Parser::Token_OPERATOR;
            }
            i = t.end;
            kDebug() << t.kind << " " << t.begin << " " << t.end;
        }
        Parser::Token &t = next();
        t.begin = content.size();
        t.end = content.size() - 1;
        t.kind = Parser::Token_EOF;
        rewind(0);
    }
    inline QString tokenString(uint pos)
    {
        return m_content.mid(token(pos).begin, token(pos).end - token(pos).begin + 1);
    }
};

}

#endif
