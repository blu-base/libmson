#include "GlobalIdTableStartFNDX.h"

namespace MSONcommon {
GlobalIdTableStartFNDX::GlobalIdTableStartFNDX() : m_reserved{0} {}

quint8 GlobalIdTableStartFNDX::getReserved() const { return m_reserved; }

void GlobalIdTableStartFNDX::setReserved(const quint8 &value) {
  m_reserved = value;
}

void GlobalIdTableStartFNDX::deserialize(QDataStream &ds) { ds >> m_reserved; }

void GlobalIdTableStartFNDX::serialize(QDataStream &ds) const {
  ds << m_reserved;
}

void GlobalIdTableStartFNDX::toDebugString(QDebug dbg) const {
  dbg << " GlobalIdTableStartFNDX: reserved: " << m_reserved << '\n';
}

void GlobalIdTableStartFNDX::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("GlobalIdTableStartFNDX");
  xmlWriter.writeAttribute("reserved", QString::number(m_reserved));
  xmlWriter.writeEndElement();
}
} // namespace MSONcommon
