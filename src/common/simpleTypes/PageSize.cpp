#include "PageSize.h"

namespace MSONcommon {

PageSize::PageSize() : m_type() {}

void PageSize::setPageType(const PageSizeType id) {
  m_type = static_cast<quint32>(id);
}

PageSizeType PageSize::getPageType() const {
  return static_cast<PageSizeType>(m_type);
}

void PageSize::setPageTypeValue(const quint32 type) { m_type = type; }

quint32 PageSize::getPageTypeValue() const { return m_type; }

void PageSize::toDebugString(QDebug &dbg) const {
  dbg << "PageSize: " << typeToString(m_type) << '\n';
}

void PageSize::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("PageSize");
  xmlWriter.writeCharacters(typeToString(m_type));
  xmlWriter.writeEndElement();
}

void PageSize::deserialize(QDataStream &ds) { ds >> m_type; }

void PageSize::serialize(QDataStream &ds) const { ds << m_type; }

QString typeToString(const PageSizeType type) {
  switch (type) {
  case MSONcommon::PageSizeType::fitToContent:
    return "fitToContent";
  case MSONcommon::PageSizeType::us_statement:
    return "us_statement";
  case MSONcommon::PageSizeType::ansi_letter:
    return "ansi_letter";
  case MSONcommon::PageSizeType::ansi_tabloid:
    return "ansi_tabloid";
  case MSONcommon::PageSizeType::us_legel:
    return "us_legel";
  case MSONcommon::PageSizeType::a3:
    return "a3";
  case MSONcommon::PageSizeType::a4:
    return "a4";
  case MSONcommon::PageSizeType::a5:
    return "a5";
  case MSONcommon::PageSizeType::a6:
    return "a6";
  case MSONcommon::PageSizeType::b4:
    return "b4";
  case MSONcommon::PageSizeType::b5:
    return "b5";
  case MSONcommon::PageSizeType::b6:
    return "b6";
  case MSONcommon::PageSizeType::japPostcard:
    return "japPostcard";
  case MSONcommon::PageSizeType::indexCard:
    return "indexCard";
  case MSONcommon::PageSizeType::billfold:
    return "billfold";
  case MSONcommon::PageSizeType::custom:
    return "custom";

  default:
    return "invalid";
  }
}

QString typeToString(const quint32 type) {
  return typeToString(static_cast<PageSizeType>(type));
}

} // namespace MSONcommon
