#include "ObjectDeclaration2Body.h"

ObjectDeclaration2Body::ObjectDeclaration2Body() {}

quint8 ObjectDeclaration2Body::getFReserved2() const { return m_fReserved2; }

void ObjectDeclaration2Body::setFReserved2(const quint8 &value) {
  m_fReserved2 = value;
}

void ObjectDeclaration2Body::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ObjectDeclaration2Body");
  xmlWriter.writeAttribute("fHasOidReferences",
                           m_fHasOidReferences ? "true" : "false");
  xmlWriter.writeAttribute("fHasOsidReferences",
                           m_fHasOsidReferences ? "true" : "false");

  m_oid.generateXml(xmlWriter);
  m_jcid.generateXml(xmlWriter);

  xmlWriter.writeEndElement();
}

QDataStream &operator<<(QDataStream &ds, const ObjectDeclaration2Body &obj) {
  obj.serialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const ObjectDeclaration2Body &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

QDataStream &operator>>(QDataStream &ds, ObjectDeclaration2Body &obj) {
  obj.deserialize(ds);
  return ds;
}

void ObjectDeclaration2Body::deserialize(QDataStream &ds) {
  ds >> m_oid;
  ds >> m_jcid;

  quint8 temp;
  ds >> temp;
  m_fHasOidReferences = temp & 0x1;
  m_fHasOsidReferences = (temp >> 1) & 0x1;
}

void ObjectDeclaration2Body::serialize(QDataStream &ds) const {
  ds << m_oid;
  ds << m_jcid;
  quint8 temp{};
  temp += m_fHasOidReferences;
  temp += m_fHasOsidReferences << 1;

  ds << temp;
}

void ObjectDeclaration2Body::toDebugString(QDebug dbg) const {
  dbg << "  ObjectDeclaration2Body:"
      << " HasOid: " << m_fHasOidReferences
      << " HasOsid: " << m_fHasOsidReferences << '\n'
      << "  oid:  " << m_oid << '\n'
      << m_jcid;
}

bool ObjectDeclaration2Body::getFHasOsidReferences() const {
  return m_fHasOsidReferences;
}

void ObjectDeclaration2Body::setFHasOsidReferences(bool value) {
  m_fHasOsidReferences = value;
}

bool ObjectDeclaration2Body::getFHasOidReferences() const {
  return m_fHasOidReferences;
}

void ObjectDeclaration2Body::setFHasOidReferences(bool value) {
  m_fHasOidReferences = value;
}

JCID ObjectDeclaration2Body::getJcid() const { return m_jcid; }

void ObjectDeclaration2Body::setJcid(const JCID &value) { m_jcid = value; }

CompactID ObjectDeclaration2Body::getOid() const { return m_oid; }

void ObjectDeclaration2Body::setOid(const CompactID &value) { m_oid = value; }
