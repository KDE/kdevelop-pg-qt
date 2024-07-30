#include "Op2parser.cpp"
#include "Op2debugvisitor.h"
#include "Op2tokenstream.h"

#include <QFile>
#include <kdebug.h>

using namespace Op2;

int main(int argc, char **argv)
{
    if(argc != 2)
    {
      kDebug() << "Usage: " << argv[0] << " filename";
      return -1;
    }
    QFile file(argv[1]);
    file.open(QIODevice::ReadOnly);
    QString content = file.readAll();
    Op2::TokenStream token_stream(content);
    Parser::memoryPoolType memory_pool;
    Parser parser;
    parser.setTokenStream(&token_stream);
    parser.setMemoryPool(&memory_pool);
    parser.yylex();
    DocumentAst *doc;
    kDebug() << parser.parseDocument(&doc);
    DebugVisitor v(&token_stream, content);
    v.visitDocument(doc);
}

