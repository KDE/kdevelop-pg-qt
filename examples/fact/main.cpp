/* 
 * Copyright 2005, 2006 Jakob Petsovits <jpetso@gmx.at>
 * Copyright 2008 Niko Sams <niko.sams@gmail.com>
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

#include "factparser.h"
#include "factdefaultvisitor.h"
#include "factdebugvisitor.h"

#include <QDebug>
#include <QFile>

using namespace fact;

static void usage(char const* argv0);
static bool parseFile(const QString& filename, bool debug);

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    bool debug = false;
    while (char const *arg = *++argv)
    {
        if (!strncmp(arg, "--debug", 7))
        {
            debug = true;
        }
        else if (!strncmp(arg, "--", 2))
        {
            qDebug() << "Unknown option: " << arg;
            usage(argv[0]);
            exit(EXIT_FAILURE);
        }
        else if(!parseFile(arg, debug))
        {
            exit(EXIT_FAILURE);
        }
    }

  return EXIT_SUCCESS;
}

bool parseFile(const QString& filename, bool debug)
{
    QString contents;
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        contents = file.readAll();
        file.close();
    }
    else
    {
        qDebug() << filename << ": file not found";
        return false;
    }

    KDevPG::TokenStream tokenStream;
    Parser::memoryPoolType memoryPool;

    // 0) setup
    Parser factParser;
    factParser.setTokenStream(&tokenStream);
    factParser.setMemoryPool(&memoryPool);
    factParser.setDebug( debug );

    // 1) tokenize
    factParser.tokenize(contents);

    // 2) parse
    ProgramAst *ast = 0;
    bool matched = factParser.parseProgram(&ast);
    if (matched)
    {
        if (debug) {
            DebugVisitor d(&tokenStream);
            d.visitNode(ast);
        }
    }
    else
    {
        factParser.expectedSymbol(AstNode::ProgramKind, "program");
    }

    return matched;
}

static void usage(char const* argv0)
{
    qDebug() << "usage: " << argv0 << "--debug file1.f [file2.f...]";
}

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
