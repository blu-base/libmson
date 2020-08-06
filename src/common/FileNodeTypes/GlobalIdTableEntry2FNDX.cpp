#include "GlobalIdTableEntry2FNDX.h"

GlobalIdTableEntry2FNDX::GlobalIdTableEntry2FNDX()
    : m_iIndexMapFrom{0}, m_iIndexMapTo{0} {}

quint32 GlobalIdTableEntry2FNDX::getIIndexMapFrom() const {
  return m_iIndexMapFrom;
}

void GlobalIdTableEntry2FNDX::setIIndexMapFrom(const quint32 &value) {
  m_iIndexMapFrom = value;
}

quint32 GlobalIdTableEntry2FNDX::getIIndexMapTo() const { return m_iIndexMapTo; }

void GlobalIdTableEntry2FNDX::setIIndexMapTo(const quint32 &value) {
  m_iIndexMapTo = value;
}

void GlobalIdTableEntry2FNDX::deserialize(QDataStream &ds) {
  ds >> m_iIndexMapFrom;
  ds >> m_iIndexMapTo;
}

void GlobalIdTableEntry2FNDX::serialize(QDataStream &ds) const {
  ds << m_iIndexMapFrom;
  ds << m_iIndexMapTo;
}

void GlobalIdTableEntry2FNDX::toDebugString(QDebug dbg) const {
  dbg << " GlobalIdTableEntry2FNDX: \n"
      << " iIndexMapFrom: " << m_iIndexMapFrom << " iIndexMapTo: " << m_iIndexMapTo
      << '\n';
}


void GlobalIdTableEntry2FNDX::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("GlobalIdTableEntry2FNDX");
    xmlWriter.writeAttribute("iIndexMapFrom",QString::number(m_iIndexMapFrom));
    xmlWriter.writeAttribute("iIndexMapTo",QString::number(m_iIndexMapTo));
    xmlWriter.writeEndElement();
}
