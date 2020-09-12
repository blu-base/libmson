#include "BodyTextAlignment.h"

#include <QDataStream>

namespace MSONcommon {

BodyTextAlignment::BodyTextAlignment() : m_value() {}

void BodyTextAlignment::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("BodyTextAlignment");
  xmlWriter.writeCharacters(QString::number(m_value));
  xmlWriter.writeEndElement();
}

quint32 BodyTextAlignment::value() const { return m_value; }

void BodyTextAlignment::setValue(const quint32 val) { m_value = val; }


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
