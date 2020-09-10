#include "ColorRef.h"

#include "../helper/Helper.h"

namespace MSONcommon {

ColorRef::ColorRef() : m_colorVal() {}

ColorRef::ColorRef(const quint32 colorVal) : m_colorVal(colorVal) {}

void ColorRef::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("COLORREF");
    xmlWriter.writeCharacters(qStringHex(m_colorVal,8));
    xmlWriter.writeEndElement();
}

bool ColorRef::isSpecifiesColor() const
{
    return (m_colorVal >> 6) == 0xFF;
}

quint32 ColorRef::getColorRef() const
{
    return m_colorVal;
}



QDataStream &operator<<(QDataStream &ds, const ColorRef &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, ColorRef &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const ColorRef &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

void ColorRef::deserialize(QDataStream &ds) {
  ds.setByteOrder(QDataStream::LittleEndian);
  ds >> m_colorVal;
}

void ColorRef::serialize(QDataStream &ds) const {
  ds << m_colorVal;
}

void ColorRef::toDebugString(QDebug dbg) const {
  dbg << "ColorRef:\n" << qStringHex(m_colorVal,8);
}

} // namespace MSONcommon
