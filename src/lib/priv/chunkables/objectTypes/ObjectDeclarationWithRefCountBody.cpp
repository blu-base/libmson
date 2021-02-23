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

  quint16 tail;
  ds >> tail;

  m_fReserved2 = (tail << 14) + (temp << 17);
}

void ObjectDeclarationWithRefCountBody::serialize(QDataStream& ds) const
{

  ds << m_oid;
  quint64 temp{};

  temp += m_fHasOsidReferences << 17;
  temp += m_fHasOidReferences << 16;
  temp += m_odcs << 10;
  temp += m_jci & 0x3FF;

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

quint16 ObjectDeclarationWithRefCountBody::getJci() const { return m_jci; }

void ObjectDeclarationWithRefCountBody::setJci(const quint16& value)
{
  m_jci = value & 0x3FF;
}

CompactID ObjectDeclarationWithRefCountBody::getOid() const { return m_oid; }

void ObjectDeclarationWithRefCountBody::setOid(const CompactID& value)
{
  m_oid = value;
}

quint8 ObjectDeclarationWithRefCountBody::getFReserved1() const
{
  return m_fReserved1;
}

quint32 ObjectDeclarationWithRefCountBody::getFReserved2() const
{
  return m_fReserved2;
}

} // namespace priv
} // namespace libmson
