#include "ObjectDeclarationWithRefCountBody.h"
#include <QDataStream>

namespace libmson {
namespace priv {

ObjectDeclarationWithRefCountBody::ObjectDeclarationWithRefCountBody()
    : m_jci(), m_odcs(), m_fReserved1(), m_fHasOidReferences(false),
      m_fHasOsidReferences(false), m_fReserved2()
{
}


void ObjectDeclarationWithRefCountBody::deserialize(QDataStream& ds)
{
  ds >> m_oid;
  quint32 temp;

  ds >> temp;
  m_jci                = temp & 0x3FF;
  m_odcs               = (temp >> 10) & 0xF;
  m_fReserved1         = (temp >> 14) & 0x3;
  m_fHasOidReferences  = (temp >> 16) & 0x1;
  m_fHasOsidReferences = (temp >> 17) & 0x1;

  ds.device()->skip(2u);
}

void ObjectDeclarationWithRefCountBody::serialize(QDataStream& ds) const
{

  ds << m_oid;
  quint64 temp{};

  temp += m_fHasOsidReferences << 17;
  temp += m_fHasOidReferences << 16;
  temp += m_odcs << 10;
  temp += m_jci;

  ds << temp;
}


bool ObjectDeclarationWithRefCountBody::getFHasOsidReferences() const
{
  return m_fHasOsidReferences;
}

void ObjectDeclarationWithRefCountBody::setFHasOsidReferences(bool value)
{
  m_fHasOsidReferences = value;
}

const quint64 ObjectDeclarationWithRefCountBody::sizeInFile =
    CompactID::getSizeInFile() + 8;

quint64 ObjectDeclarationWithRefCountBody::getSizeInFile()
{
  return sizeInFile;
}

bool ObjectDeclarationWithRefCountBody::getFHasOidReferences() const
{
  return m_fHasOidReferences;
}

void ObjectDeclarationWithRefCountBody::setFHasOidReferences(bool value)
{
  m_fHasOidReferences = value;
}

quint8 ObjectDeclarationWithRefCountBody::getOdc() const { return m_odcs; }

void ObjectDeclarationWithRefCountBody::setOdc(const quint8& value)
{
  m_odcs = value;
}

quint8 ObjectDeclarationWithRefCountBody::getJci() const { return m_jci; }

void ObjectDeclarationWithRefCountBody::setJci(const quint8& value)
{
  m_jci = value;
}

CompactID ObjectDeclarationWithRefCountBody::getOid() const { return m_oid; }

void ObjectDeclarationWithRefCountBody::setOid(const CompactID& value)
{
  m_oid = value;
}

// void ObjectDeclarationWithRefCountBody::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("ObjectDeclarationWithRefCountBody");
//  xmlWriter.writeAttribute("jci", qStringHex(m_jci, 2));
//  xmlWriter.writeAttribute("odcs", qStringHex(m_odcs, 1));
//  xmlWriter.writeAttribute("fReserved1", qStringHex(m_fReserved1, 1));
//  xmlWriter.writeAttribute("fReserved2", qStringHex(m_fReserved2, 8));
//  xmlWriter.writeAttribute("fHasOidReferences",
//                           m_fHasOsidReferences ? "true" : "false");
//  xmlWriter.writeAttribute("fHasOsidReferences",
//                           m_fHasOsidReferences ? "true" : "false");

//  xmlWriter << m_oid;

//  xmlWriter.writeEndElement();
//}

// void ObjectDeclarationWithRefCountBody::toDebugString(QDebug &dbg) const {
//  dbg << "ObjectDeclarationWithRefCountBody:\n"
//      << "oid: " << m_oid << '\n'
//      << "jci: " << m_jci << '\n'
//      << "odcs: " << m_odcs << '\n'
//      << "fHasOidReferences: " << m_fHasOidReferences << " fHasOsidReferences"
//      << m_fHasOsidReferences << '\n';
//}

} // namespace priv
} // namespace libmson
