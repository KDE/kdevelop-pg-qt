/*
    SPDX-FileCopyrightText: 2009 Jonathan Schmidt-Dominé <devel@the-user.org>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#include <iostream>
#include <fstream>
#include <climits>
#include <QDebug>
#include "dumptree.h"
#include "ccparser.h"
#include "lexer.h"

using namespace cc;
using namespace std;

int main(int argc, char** argv)
{
	if(argc == 1)
	{
		cerr << "Simply use some preprocessed C-code-files (output of gcc -E) as arguments" << endl;
		return -1;
	}
	for(int i = 1; i != argc; ++i)
	{
		ifstream filestr(argv[i]);
		char* contents;
		if(filestr.is_open())
		{
			long size;
			filestr.ignore(10000);
			size = filestr.tellg();
			filestr.close();
			contents = new char[size+2];
			filestr.open(argv[i]);
			filestr.read(contents, size);
			contents[size] = '\n';
			contents[size+1] = '\0';
			filestr.close();
		}
		else
		{
			cerr << "File not found: " << argv[i] << endl;
			return -1;
		}
		KDevPG::TokenStream token_stream;
		Parser::memoryPoolType memory_pool;
		Parser parser;
		parser.setTokenStream(&token_stream);
		parser.setMemoryPool(&memory_pool);
		Lexer lexer(&parser, contents);
	        int kind = Parser::Token_EOF;
		do
		{
			kind = lexer.yylex();
			if ( !kind ) // when the lexer returns 0, the end of file is reached
				kind = Parser::Token_EOF;
                        qDebug() << kind;
			Parser::Token &t = token_stream.push();
			t.kind = kind;
			t.begin = lexer.tokenBegin();
			t.end = lexer.tokenEnd();
		}
		while ( kind != Parser::Token_EOF );
		token_stream.rewind(0);
		parser.yylex();
		DocumentAst *ast = 0;
		bool matched = parser.parseDocument(&ast);
		if(matched)
		{
			DumpTree dt;
			dt.dump(ast);
		}
		else
		{
			qDebug() << "Parsing failed";
		}
		delete[] contents;
	}
	return 0;
}

