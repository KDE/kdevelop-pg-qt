/*
    SPDX-FileCopyrightText: 2011 Jonathan Schmidt-Dominé <devel@the-user.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg-unicode-loader.h"

#include "kdev-pg.h"
#include "kdev-pg-regexp.h"

#include <QFile>

namespace KDevPG
{

#define SET_CHAR(str, i, x) \
{ \
x = 0; \
for(; ; ++i) \
{ \
  x *= 16; \
  if(str[i] >= 'a' && str[i] <= 'f') \
    x += (str[i] - 'a' + 10); \
  else if(str[i] >= 'A' && str[i] <= 'F') \
    x += (str[i] - 'A' + 10); \
  else if(str[i] >= '0' && str[i] <= '9') \
    x += (str[i] - '0'); \
  else \
    break; \
} \
x /= 16; \
}

void standardFormat(const QString fileName)
{
  QMap<QByteArray, GNFA> res;
  QFile file(fileName);
  if(file.open(QIODevice::ReadOnly))
  {
    while(!file.atEnd())
    {
      auto line = file.readLine();
      if(line.size() > 0 && line[0] != '#')
      {
        if(line[0] != '#')
        {
          int idxDotDot = line.indexOf("..");
          if(idxDotDot != -1)
          {
            quint32 start;
            int i = 0;
            SET_CHAR(line, i, start)
            assert(i <= idxDotDot);
            i += 2;
            quint32 end = 0;
            int idxSemicolon = line.indexOf(';', idxDotDot + 2);
            SET_CHAR(line, i, end)
            assert(i <= idxSemicolon);
            QByteArray name = line.mid(idxSemicolon+1, (uint)(line.indexOf('#', idxSemicolon + 1)) - idxSemicolon - 1).trimmed().toLower();
            name.replace(' ', '_');
            name.replace('-', '_');
            auto toInsert = GNFA::range(start, end+1);
            const QString _name = QString::fromUtf8(name);
            if(globalSystem.regexpById[_name] == nullptr)
              globalSystem.regexpById[_name] = new GNFA(toInsert);
            else
              *globalSystem.regexpById[_name] |= toInsert;
          }
          else
          {
            quint32 single;
            int i = 0;
            SET_CHAR(line, i, single);
            int idxSemicolon = line.indexOf(';', i);
            QByteArray name = line.mid(idxSemicolon+1, (uint)(line.indexOf('#', idxSemicolon + 1)) - idxSemicolon - 1).trimmed().toLower();
            name.replace(' ', '_');
            name.replace('-', '_');
            auto toInsert = GNFA::character(single);
            const QString _name = QString::fromUtf8(name);
            if(globalSystem.regexpById[_name] == nullptr)
              globalSystem.regexpById[_name] = new GNFA(toInsert);
            else
              *globalSystem.regexpById[_name] |= toInsert;
          }
        }
      }
    }
  }
  else
    qFatal("** ERROR Failed to open unicode-data-file ``%s''", fileName.toUtf8().data());
}

void loadUnicodeData()
{
  static bool loaded = false;
  if(!loaded)
  {
    loaded = true;
    standardFormat(QStringLiteral(":/unidata/Blocks.txt"));
    standardFormat(QStringLiteral(":/unidata/PropList.txt"));
    standardFormat(QStringLiteral(":/unidata/DerivedCoreProperties.txt"));
    standardFormat(QStringLiteral(":/unidata/Scripts.txt"));
    standardFormat(QStringLiteral(":/unidata/ScriptExtensions.txt"));
    standardFormat(QStringLiteral(":/unidata/DerivedNumericType.txt"));
    globalSystem.regexpById[QStringLiteral("num")] = new GNFA(*globalSystem.regexpById[QStringLiteral("numeric")]);
    *globalSystem.regexpById[QStringLiteral("num")] |= *globalSystem.regexpById[QStringLiteral("digit")];
    *globalSystem.regexpById[QStringLiteral("num")] |= *globalSystem.regexpById[QStringLiteral("decimal")];
    globalSystem.regexpById[QStringLiteral("ascii-range")] = new GNFA(GNFA::range(0, 0x80));
    globalSystem.regexpById[QStringLiteral("latin1-range")] = new GNFA(GNFA::range(0, 0x100));
    // IndicMatraCategory and IndicSyllabicCategory: same format, but should have a prefix, names like “vowel” are confusing when used for Indian vowels only
    // named sequences: other format
  }
}

}
