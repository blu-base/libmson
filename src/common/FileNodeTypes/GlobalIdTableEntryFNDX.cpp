#include "GlobalIdTableEntryFNDX.h"

namespace MSONcommon {
GlobalIdTableEntryFNDX::GlobalIdTableEntryFNDX() : m_index{0} {}

QUuid GlobalIdTableEntryFNDX::getGuid() const { return m_guid; }

void GlobalIdTableEntryFNDX::setGuid(const QUuid &value) { m_guid = value; }

quint32 GlobalIdTableEntryFNDX::getIndex() const { return m_index; }

void GlobalIdTableEntryFNDX::setIndex(const quint32 &value) { m_index = value; }

void GlobalIdTableEntryFNDX::deserialize(QDataStream &ds) {
  ds >> m_index;
  ds >> m_guid;
}

void GlobalIdTableEntryFNDX::serialize(QDataStream &ds) const {
  ds << m_index;
  ds << m_guid;
}

void GlobalIdTableEntryFNDX::toDebugString(QDebug &dbg) const {
  dbg << " GlobalIdTableEntryFNDX: \n"
      << " Index: " << m_index << '\n'
      << " GUID:  " << m_guid << '\n';
}

void GlobalIdTableEntryFNDX::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("GlobalIdTableEntryFNDX");
  xmlWriter.writeAttribute("index", QString::number(m_index));

  xmlWriter.writeStartElement("guid");
  xmlWriter.writeCharacters(m_guid.toString());
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
}

quint64 GlobalIdTableEntryFNDX::getSizeInFile() const { return sizeInFile; }


} // namespace MSONcommon
