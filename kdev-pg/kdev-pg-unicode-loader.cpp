/* This file is part of kdev-pg-qt
 * Copyright (C) 2011 Jonathan Schmidt-Dominé <devel@the-user.org>
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 * 
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
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
            name.replace(' ', '-');
            name.replace('_', '-');
            auto toInsert = GNFA::range(start, end+1);
            if(globalSystem.regexpById[name] == 0)
              globalSystem.regexpById[name] = new GNFA(toInsert);
            else
              *globalSystem.regexpById[name] |= toInsert;
          }
          else
          {
            quint32 single;
            int i = 0;
            SET_CHAR(line, i, single);
            int idxSemicolon = line.indexOf(';', i);
            QByteArray name = line.mid(idxSemicolon+1, (uint)(line.indexOf('#', idxSemicolon + 1)) - idxSemicolon - 1).trimmed().toLower();
            name.replace(' ', '-');
            name.replace('_', '-');
            auto toInsert = GNFA::character(single);
            if(globalSystem.regexpById[name] == 0)
              globalSystem.regexpById[name] = new GNFA(toInsert);
            else
              *globalSystem.regexpById[name] |= toInsert;
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
    standardFormat(":/unidata/Blocks.txt");
    standardFormat(":/unidata/PropList.txt");
    standardFormat(":/unidata/DerivedCoreProperties.txt");
    standardFormat(":/unidata/Scripts.txt");
    standardFormat(":/unidata/ScriptExtensions.txt");
    standardFormat(":/unidata/DerivedNumericType.txt");
    // IndicMatraCategory and IndicSyllabicCategory: same format, but should have a prefix, names like “vowel” are confusing when used for Indian vowels only
    // named sequences: other format
  }
}

}
