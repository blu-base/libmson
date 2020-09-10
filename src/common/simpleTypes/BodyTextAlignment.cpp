#include "BodyTextAlignment.h"

namespace MSONcommon {

BodyTextAlignment::BodyTextAlignment() : m_value() {}

void BodyTextAlignment::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("BodyTextAlignment");
  xmlWriter.writeCharacters(QString::number(m_value));
  xmlWriter.writeEndElement();
}

quint32 BodyTextAlignment::value() const { return m_value; }

void BodyTextAlignment::setValue(const quint32 val) { m_value = val; }

QDataStream &operator<<(QDataStream &ds, const BodyTextAlignment &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, BodyTextAlignment &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const BodyTextAlignment &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

void BodyTextAlignment::deserialize(QDataStream &ds) { ds >> m_value; }

void BodyTextAlignment::serialize(QDataStream &ds) const { ds << m_value; }

void BodyTextAlignment::toDebugString(QDebug dbg) const {
  dbg << "BodyTextAlignment: " << QString::number(m_value) << '\n';
}

} // namespace MSONcommon
