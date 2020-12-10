#include "PageSize.h"

namespace libmson {

PageSize::PageSize() : m_type() {}

void PageSize::setPageType(const PageSizeType& id)
{
  m_type = static_cast<quint32>(id);
}

PageSizeType PageSize::getPageType() const
{
  return static_cast<PageSizeType>(m_type);
}

void PageSize::setPageTypeValue(const quint32 type) { m_type = type; }

quint32 PageSize::getPageTypeValue() const { return m_type; }

// void PageSize::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
// xmlWriter.writeStartElement("PageSize");
// xmlWriter.writeCharacters(typeToString(m_type));
// xmlWriter.writeEndElement();
// }

void PageSize::deserialize(QDataStream& ds) { ds >> m_type; }

void PageSize::serialize(QDataStream& ds) const { ds << m_type; }

QString PageSize::typeToString(const PageSizeType type)
{
  switch (type) {
  case PageSizeType::fitToContent:
    return "fitToContent";
  case PageSizeType::us_statement:
    return "us_statement";
  case PageSizeType::ansi_letter:
    return "ansi_letter";
  case PageSizeType::ansi_tabloid:
    return "ansi_tabloid";
  case PageSizeType::us_legel:
    return "us_legel";
  case PageSizeType::a3:
    return "a3";
  case PageSizeType::a4:
    return "a4";
  case PageSizeType::a5:
    return "a5";
  case PageSizeType::a6:
    return "a6";
  case PageSizeType::b4:
    return "b4";
  case PageSizeType::b5:
    return "b5";
  case PageSizeType::b6:
    return "b6";
  case PageSizeType::japPostcard:
    return "japPostcard";
  case PageSizeType::indexCard:
    return "indexCard";
  case PageSizeType::billfold:
    return "billfold";
  case PageSizeType::custom:
    return "custom";

  default:
    return "invalid";
  }
}

QString PageSize::typeToString(const quint32 type)
{
  return typeToString(static_cast<PageSizeType>(type));
}

} // namespace libmson
