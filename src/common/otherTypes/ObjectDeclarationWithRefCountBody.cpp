#include "ObjectDeclarationWithRefCountBody.h"

ObjectDeclarationWithRefCountBody::ObjectDeclarationWithRefCountBody() {}

QDataStream &operator<<(QDataStream &ds,
                        const ObjectDeclarationWithRefCountBody &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds,
                        ObjectDeclarationWithRefCountBody &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const ObjectDeclarationWithRefCountBody &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

quint32 ObjectDeclarationWithRefCountBody::getFReserved() const {
  return fReserved;
}

void ObjectDeclarationWithRefCountBody::setFReserved(const quint32 &value) {
  fReserved = value;
}

void ObjectDeclarationWithRefCountBody::deserialize(QDataStream &ds) {}

void ObjectDeclarationWithRefCountBody::serialize(QDataStream &ds) const {}

void ObjectDeclarationWithRefCountBody::toDebugString(QDebug dbg) const {}

bool ObjectDeclarationWithRefCountBody::getFHasOsidReferences() const {
  return fHasOsidReferences;
}

void ObjectDeclarationWithRefCountBody::setFHasOsidReferences(bool value) {
  fHasOsidReferences = value;
}

bool ObjectDeclarationWithRefCountBody::getFHasOidReferences() const {
  return fHasOidReferences;
}

void ObjectDeclarationWithRefCountBody::setFHasOidReferences(bool value) {
  fHasOidReferences = value;
}

quint8 ObjectDeclarationWithRefCountBody::getFReserved1() const {
  return fReserved1;
}

void ObjectDeclarationWithRefCountBody::setFReserved1(const quint8 &value) {
  fReserved1 = value;
}

quint8 ObjectDeclarationWithRefCountBody::getOdc() const { return odc; }

void ObjectDeclarationWithRefCountBody::setOdc(const quint8 &value) {
  odc = value;
}

quint8 ObjectDeclarationWithRefCountBody::getJci() const { return jci; }

void ObjectDeclarationWithRefCountBody::setJci(const quint8 &value) {
  jci = value;
}

CompactID ObjectDeclarationWithRefCountBody::getOid() const { return oid; }

void ObjectDeclarationWithRefCountBody::setOid(const CompactID &value) {
  oid = value;
}
