#include "Charset.h"
namespace libmson {
Charset::Charset() {}

Charset::Charset(const CHARSET charset) : m_charset(charset) {}


CHARSET Charset::getCharset() const { return m_charset; }

void Charset::setCharset(const CHARSET& charset) { m_charset = charset; }

QString Charset::toString() const { return toString(m_charset); }

QString Charset::toString(const CHARSET& charset)
{
  switch (charset) {
  case CHARSET::ANSI:
    return "ANSI";
  case CHARSET::DEFAULT:
    return "DEFAULT";
  case CHARSET::SYMBOL:
    return "SYMBOL";
  case CHARSET::MAC:
    return "MAC";
  case CHARSET::SHIFTJIS:
    return "SHIFTJIS";
  case CHARSET::HANGUL:
    return "HANGUL";
  case CHARSET::JOHAB:
    return "JOHAB";
  case CHARSET::GB2312:
    return "GB2312";
  case CHARSET::CHINESEBIG5:
    return "CHINESEBIG5";
  case CHARSET::GREEK:
    return "GREEK";
  case CHARSET::TURKISH:
    return "TURKISH";
  case CHARSET::VIETNAMESE:
    return "VIETNAMESE";
  case CHARSET::HEBREW:
    return "HEBREW";
  case CHARSET::ARABIC:
    return "ARABIC";
  case CHARSET::BALTIC:
    return "BALTIC";
  case CHARSET::RUSSIAN:
    return "RUSSIAN";
  case CHARSET::THAI:
    return "THAI";
  case CHARSET::EASTEUROPE:
    return "EASTEUROPE";
  case CHARSET::OEM:
    return "OEM";
  default:
    return "UNDEFINED";
  }
}

void libmson::Charset::deserialize(QDataStream& ds)
{
  uint8_t val;
  ds >> val;

  m_charset = static_cast<CHARSET>(val);
}

void libmson::Charset::serialize(QDataStream& ds) const
{
  ds << static_cast<uint8_t>(m_charset);
}

} // namespace libmson
