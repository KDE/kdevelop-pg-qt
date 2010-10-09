#include <iostream>
#include <QString>
#include <QDebug>

class QUtf16Iterator
{
  union { QChar const *ptr; quint16 const *raw; };
public:
  QUtf16Iterator(const QString& str) : raw(str.utf16())
  {
    
  }
  QUtf16Iterator& operator++()
  {
    if(QChar::isHighSurrogate(*raw))
      ++ptr;
    ++ptr;
    return *this;
  }
  quint32 operator*() const
  {
    // big endian
    quint32 ret = ptr->unicode();
    if(QChar::isHighSurrogate(*raw))
      return QChar::surrogateToUcs4(ret, raw[1]);
    return ret;
  }
  quint32 next()
  {
    quint32 ret = ptr->unicode();
    if(QChar::isHighSurrogate(*raw))
      ret = QChar::surrogateToUcs4(ret, *(++raw));
    ++ptr;
    return ret;
  }
  bool atEnd(const QString& str)
  {
    return raw - str.utf16() == str.size();
  }
};

class QUtf8Iterator
{
  uchar const *ptr;
public:
  QUtf8Iterator(const QByteArray& qba) : ptr(reinterpret_cast<uchar const*>(qba.data()))
  {
    
  }
  QUtf8Iterator& operator++()
  {
    qFatal("not implemented");
    return *this;
  }
  quint32 operator*() const
  {
    qFatal("not implemented");
  }
  quint32 next()
  {
    /*
    Algorithm:
    
    Start:
      case chr < 128
        use it directly
      case (chr & 0xe0) == 0xc0
        (chr & 0x1f) -> add next
      case (chr & 0xf0) == 0xe0
        (chr & 0x0f) -> add next two
      case (chr & 0xf8) == 0xf0
        (chr & 0x07) -> add next three
      default
        invalid
        
    Add:
      condition: (next & 0xc0) == 0x80
      ret = (ret << 6) | (nextChr & 0x3f)
      QChar::isUnicodeNonCharacter -> invalid
    */
    
    while(true)
    {
      uchar chr = *ptr;
      if(chr < 128)
      {
        ++ptr;
        return chr;
      }
      quint32 ret;
      if((chr & 0xe0) == 0xc0)
      {
        ret = ((chr & 0x1f) << 6) | ((*++ptr) & 0x3f);
      }
      if((chr & 0xf0) == 0xe0)
      {
        ret = ((chr & 0x0f) << 6) | ((*++ptr) & 0x3f);
        ret = (ret << 6) | ((*++ptr) & 0x3f);
      }
      if((chr & 0xf8) == 0xf0)
      {
        ret = ((chr & 0x0f) << 6) | ((*++ptr) & 0x3f);
        ret = (ret << 6) | ((*++ptr) & 0x3f);
        ret = (ret << 6) | ((*++ptr) & 0x3f);
      }
      ++ptr;
      if((ret & 0xfffe) != 0xfffe && (ret - 0xfdd0U) > 15)
        return ret;
      // ignore the error, jump back :-)
    }
  }
  bool atEnd(const QByteArray& str)
  {
    return ptr - reinterpret_cast<uchar const*>(str.data()) == str.size();
  }
};

int main()
{
  QByteArray utf8("§utf8ärrayßようこそ中華民族𐀃bla"); // linear b character
  QUtf8Iterator utf8i(utf8);
  size_t s = 0;
  while(!utf8i.atEnd(utf8))
  {
    ++s;
    quint32 u = utf8i.next();
    std::cout << u << " " << QString(u).toUtf8().data() << std::endl;
  }
  std::cout << "utf8 size: " << utf8.size() << " real size: " << s << std::endl;
  QString utf16 = QString::fromUtf8("$utf16ärrayßようこそ中華民族𐀃bla");
  QUtf16Iterator utf16i(utf16);
  s = 0;
  while(!utf16i.atEnd(utf16))
  {
    ++s;
    quint32 u = utf16i.next();
    std::cout << u << " " << QString(u).toUtf8().data() << std::endl;
  }
  std::cout << "utf16 size: " << utf16.size() << " real size: " << s << std::endl;
}
