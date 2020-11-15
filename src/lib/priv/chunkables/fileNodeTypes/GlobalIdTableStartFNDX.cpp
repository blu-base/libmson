#include "GlobalIdTableStartFNDX.h"

namespace libmson {
namespace priv {
GlobalIdTableStartFNDX::GlobalIdTableStartFNDX(FileNode_WPtr_t parentFileNode)
    : IFileNodeType(parentFileNode), m_reserved{0}
{
}

quint8 GlobalIdTableStartFNDX::getReserved() const { return m_reserved; }

void GlobalIdTableStartFNDX::setReserved(const quint8& value)
{
  m_reserved = value;
}

void GlobalIdTableStartFNDX::deserialize(QDataStream& ds) { ds >> m_reserved; }

void GlobalIdTableStartFNDX::serialize(QDataStream& ds) const
{
  ds << m_reserved;
}

// void GlobalIdTableStartFNDX::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("GlobalIdTableStartFNDX");
//  xmlWriter.writeAttribute("reserved", QString::number(m_reserved));
//  xmlWriter.writeEndElement();
//}

quint64 GlobalIdTableStartFNDX::getSizeInFile() const { return sizeInFile; }

} // namespace priv
} // namespace libmson
