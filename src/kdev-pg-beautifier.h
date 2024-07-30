/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
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
