/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg-beautifier.h"

#include <QFile>
#include <QFileInfo>

namespace KDevPG
{

IteratorQTextStream::IteratorQTextStream( QTextStream& stream )
  : m_stream(stream)
  , m_peekStart(-1)
{
}

bool IteratorQTextStream::hasMoreLines() const
{
  return !m_stream.atEnd();
}

std::string IteratorQTextStream::nextLine(bool emptyLineWasDeleted)
{
  Q_UNUSED(emptyLineWasDeleted)
  return m_stream.readLine().toStdString();
}

string IteratorQTextStream::peekNextLine()
{
    if (m_peekStart == -1) {
        m_peekStart = m_stream.pos();
    }
    return m_stream.readLine().toUtf8().data();
}

void IteratorQTextStream::peekReset()
{
    if(m_peekStart != -1)
        m_stream.seek(m_peekStart);
    m_peekStart = -1; // invalid
}

void format(QTextStream& in, const QString& oname)
{
  QFile ofile(oname);
  ofile.open(QIODevice::WriteOnly);
  QTextStream out(&ofile);
  
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
    out << QString::fromStdString( f.nextLine() ) << Qt::endl;
  }
  while (f.hasMoreLines());
}

}
