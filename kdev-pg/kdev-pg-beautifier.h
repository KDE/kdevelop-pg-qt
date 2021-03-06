/* This file is part of kdev-pg-qt
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

#ifndef KDEV_PG_BEAUTIFIER_H
#define KDEV_PG_BEAUTIFIER_H

#include <QTextStream>

#include "astyle.h"

#include <string>

namespace KDevPG
{

class IteratorQTextStream : public astyle::ASSourceIterator
{
public:
  IteratorQTextStream(QTextStream& stream);

  bool hasMoreLines() const override;
  std::string nextLine(bool emptyLineWasDeleted = false) override;
  std::string peekNextLine() override;
  void peekReset() override;

private:
  QTextStream& m_stream;
  qint64 m_peekStart;
};

void format(QTextStream &in, const QString& oname);

}

#endif // KDEV_PG_BEAUTIFIER_H
