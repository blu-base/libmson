#include "ObjectDeclaration2Body.h"

ObjectDeclaration2Body::ObjectDeclaration2Body() {}

quint8 ObjectDeclaration2Body::getFReserved2() const { return fReserved2; }

void ObjectDeclaration2Body::setFReserved2(const quint8 &value) {
  fReserved2 = value;
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

void ObjectDeclaration2Body::deserialize(QDataStream &ds) {}

void ObjectDeclaration2Body::serialize(QDataStream &ds) const {}

void ObjectDeclaration2Body::toDebugString(QDebug dbg) const {}

bool ObjectDeclaration2Body::getFHasOsidReferences() const {
  return fHasOsidReferences;
}

void ObjectDeclaration2Body::setFHasOsidReferences(bool value) {
  fHasOsidReferences = value;
}

bool ObjectDeclaration2Body::getFHasOidReferences() const {
  return fHasOidReferences;
}

void ObjectDeclaration2Body::setFHasOidReferences(bool value) {
  fHasOidReferences = value;
}

JCID ObjectDeclaration2Body::getJcid() const { return jcid; }

void ObjectDeclaration2Body::setJcid(const JCID &value) { jcid = value; }

CompactID ObjectDeclaration2Body::getOid() const { return oid; }

void ObjectDeclaration2Body::setOid(const CompactID &value) { oid = value; }
