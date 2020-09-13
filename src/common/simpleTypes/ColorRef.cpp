#include "ColorRef.h"

#include "../helper/Helper.h"

namespace MSONcommon {

ColorRef::ColorRef() : m_colorVal() {}

ColorRef::ColorRef(const quint32 colorVal) : m_colorVal(colorVal) {}

void ColorRef::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("COLORREF");
  xmlWriter.writeCharacters(qStringHex(m_colorVal, 8));
  xmlWriter.writeEndElement();
}

bool ColorRef::isSpecifiesColor() const { return (m_colorVal >> 6) == 0xFF; }

quint32 ColorRef::getColorRef() const { return m_colorVal; }

void ColorRef::deserialize(QDataStream &ds) {
  ds.setByteOrder(QDataStream::LittleEndian);
  ds >> m_colorVal;
}

void ColorRef::serialize(QDataStream &ds) const { ds << m_colorVal; }

void ColorRef::toDebugString(QDebug &dbg) const {
  dbg << "ColorRef:\n" << qStringHex(m_colorVal, 8);
}

} // namespace MSONcommon
