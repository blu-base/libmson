#include "GlobalIdTableEntry3FNDX.h"

namespace libmson {
namespace priv {
GlobalIdTableEntry3FNDX::GlobalIdTableEntry3FNDX(
    RSChunkContainer_WPtr_t parentFileNode)
    : IFileNodeType(parentFileNode), m_iIndexCopyFromStart{0},
      m_cEntriesToCopy{0}, m_iIndexCopyToStart{0}
{
}

quint32 GlobalIdTableEntry3FNDX::getIIndexCopyFromStart() const
{
  return m_iIndexCopyFromStart;
}

void GlobalIdTableEntry3FNDX::setIIndexCopyFromStart(const quint32& value)
{
  m_iIndexCopyFromStart = value;
}

quint32 GlobalIdTableEntry3FNDX::getCEntriesToCopy() const
{
  return m_cEntriesToCopy;
}

void GlobalIdTableEntry3FNDX::setCEntriesToCopy(const quint32& value)
{
  m_cEntriesToCopy = value;
}

quint32 GlobalIdTableEntry3FNDX::getIIndexCopyToStart() const
{
  return m_iIndexCopyToStart;
}

void GlobalIdTableEntry3FNDX::setIIndexCopyToStart(const quint32& value)
{
  m_iIndexCopyToStart = value;
}

void GlobalIdTableEntry3FNDX::deserialize(QDataStream& ds)
{

  ds >> m_iIndexCopyFromStart;
  ds >> m_cEntriesToCopy;
  ds >> m_iIndexCopyToStart;
}

void GlobalIdTableEntry3FNDX::serialize(QDataStream& ds) const
{
  ds << m_iIndexCopyFromStart;
  ds << m_cEntriesToCopy;
  ds << m_iIndexCopyToStart;
}

// void GlobalIdTableEntry3FNDX::toDebugString(QDebug &dbg) const {
//  dbg << " GlobalIdTableEntry3FNDX: \n"
//      << " iIndexCopyFromStart: " << m_iIndexCopyFromStart << '\n'
//      << " cEntriesToCopy:      " << m_cEntriesToCopy << '\n'
//      << " iIndexCopyToStart:   " << m_iIndexCopyToStart << '\n';
//}

// void GlobalIdTableEntry3FNDX::writeLowLevelXml(QXmlStreamWriter &xmlWriter)
// const {
//  xmlWriter.writeStartElement("GlobalIdTableEntry3FNDX");
//  xmlWriter.writeAttribute("iIndexCopyFromStart",
//                           QString::number(m_iIndexCopyFromStart));
//  xmlWriter.writeAttribute("cEntriesToCopy",
//  QString::number(m_cEntriesToCopy));
//  xmlWriter.writeAttribute("iIndexCopyToStart",
//                           QString::number(m_iIndexCopyToStart));
//  xmlWriter.writeEndElement();
//}

quint64 GlobalIdTableEntry3FNDX::getSizeInFile() const { return sizeInFile; }


} // namespace priv
} // namespace libmson
