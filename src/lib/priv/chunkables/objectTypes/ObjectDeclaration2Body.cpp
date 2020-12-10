#include "ObjectDeclaration2Body.h"

namespace libmson {
namespace priv {

ObjectDeclaration2Body::ObjectDeclaration2Body()
    : m_fHasOidReferences(false), m_fHasOsidReferences(false), m_fReserved2()
{
}

quint8 ObjectDeclaration2Body::getFReserved2() const { return m_fReserved2; }

void ObjectDeclaration2Body::setFReserved2(const quint8& value)
{
  m_fReserved2 = value;
}

const quint64 ObjectDeclaration2Body::sizeInFile =
    CompactID::getSizeInFile() + JCID::getSizeInFile() + 1;

quint64 ObjectDeclaration2Body::getSizeInFile() { return sizeInFile; }


void ObjectDeclaration2Body::deserialize(QDataStream& ds)
{
  ds >> m_oid;
  ds >> m_jcid;

  quint8 temp{};
  ds >> temp;
  m_fHasOidReferences  = temp & 0x1;
  m_fHasOsidReferences = (temp >> 1) & 0x1;
}

void ObjectDeclaration2Body::serialize(QDataStream& ds) const
{
  ds << m_oid;
  ds << m_jcid;
  quint8 temp{};
  temp += m_fHasOidReferences;
  temp += m_fHasOsidReferences << 1;

  ds << temp;
}

bool ObjectDeclaration2Body::getFHasOsidReferences() const
{

  return m_fHasOsidReferences;
}

void ObjectDeclaration2Body::setFHasOsidReferences(bool value)
{
  m_fHasOsidReferences = value;
}

bool ObjectDeclaration2Body::getFHasOidReferences() const
{
  return m_fHasOidReferences;
}

void ObjectDeclaration2Body::setFHasOidReferences(bool value)
{
  m_fHasOidReferences = value;
}

JCID ObjectDeclaration2Body::getJcid() const { return m_jcid; }

void ObjectDeclaration2Body::setJcid(const JCID& value) { m_jcid = value; }

CompactID ObjectDeclaration2Body::getOid() const { return m_oid; }

void ObjectDeclaration2Body::setOid(const CompactID& value) { m_oid = value; }

} // namespace priv
} // namespace libmson
