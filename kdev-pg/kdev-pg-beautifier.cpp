/* This file is part of kdev-pg
   Copyright (C) 2005 Roberto Raggi <roberto@kdevelop.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "kdev-pg-beautifier.h"


namespace KDevPG
{

IteratorQTextStream::IteratorQTextStream( QTextStream& stream )
  : strm(stream)
{
  strcpy(outputEOL, "\n");
}
bool IteratorQTextStream::hasMoreLines() const
{
  return !strm.atEnd();
}
std::string IteratorQTextStream::nextLine()
{
  return strm.readLine().toStdString();
}

void format(QTextStream& in, QTextStream& out)
{
  astyle::ASFormatter f;

  f.setCStyle();

  f.setBlockIndent(false);
  f.setBracketIndent(false);
  f.setSpaceIndentation(4);
  f.setTabSpaceConversionMode(true);
  f.setMinConditionalIndentLength(f.getIndentLength());
  f.setMaxInStatementIndentLength(40);
  f.setOperatorPaddingMode(false);
  f.setBracketFormatMode(astyle::BREAK_MODE);
  f.setClassIndent(false);
  f.setSwitchIndent(false);
  f.setNamespaceIndent(false);
  f.setBreakElseIfsMode(false);
  f.setParensUnPaddingMode(false);
  f.setEmptyLineFill(false);
  IteratorQTextStream strm(in);
  f.init(&strm);

  do
  {
    out << QString::fromStdString( f.nextLine() ) << endl;
  }
  while (f.hasMoreLines());
}

}
