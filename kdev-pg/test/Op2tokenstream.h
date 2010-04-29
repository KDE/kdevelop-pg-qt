#ifndef OP2_TOKENSTREAM
#define OP2_TOKENSTREAM

#include <QString>
#include <kdev-pg-tokenstream.h>

namespace Op2
{

class TokenStream : public KDevPG::TokenStream
{
    QString m_content;
public:
    TokenStream(const QString& content) : m_content(content)
    {}
    inline QString tokenString(uint pos)
    {
        return m_content.mid(token(pos).begin, token(pos).end - token(pos).begin + 1);
    }
};

}

#endif
