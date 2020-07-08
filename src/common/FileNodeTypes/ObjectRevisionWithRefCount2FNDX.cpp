#include "ObjectRevisionWithRefCount2FNDX.h"

ObjectRevisionWithRefCount2FNDX::ObjectRevisionWithRefCount2FNDX(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : ref{FileNodeChunkReference(stpFormat, cbFormat)} {}
ObjectRevisionWithRefCount2FNDX::ObjectRevisionWithRefCount2FNDX(
    quint8 stpFormat, quint8 cbFormat)
    : ref{FileNodeChunkReference(stpFormat, cbFormat)} {}

quint32 ObjectRevisionWithRefCount2FNDX::getCRef() const { return cRef; }

void ObjectRevisionWithRefCount2FNDX::setCRef(const quint32 &value) {
  cRef = value;
}

bool ObjectRevisionWithRefCount2FNDX::getFHasOsidReferences() const {
  return fHasOsidReferences;
}

void ObjectRevisionWithRefCount2FNDX::setFHasOsidReferences(bool value) {
  fHasOsidReferences = value;
}

bool ObjectRevisionWithRefCount2FNDX::getFHasOidReferences() const {
  return fHasOidReferences;
}

void ObjectRevisionWithRefCount2FNDX::setFHasOidReferences(bool value) {
  fHasOidReferences = value;
}

CompactID ObjectRevisionWithRefCount2FNDX::getOid() const { return oid; }

void ObjectRevisionWithRefCount2FNDX::setOid(const CompactID &value) {
  oid = value;
}

FileNodeChunkReference ObjectRevisionWithRefCount2FNDX::getRef() const {
  return ref;
}

void ObjectRevisionWithRefCount2FNDX::setRef(
    const FileNodeChunkReference &value) {
  ref = value;
}

void ObjectRevisionWithRefCount2FNDX::deserialize(QDataStream &ds) {
  ds >> ref;
  ds >> oid;

  quint32 temp;
  ds >> temp;

  fHasOidReferences = temp & 0x1;
  fHasOsidReferences = (temp & 0x2) >> 1;

  ds >> cRef;
}

void ObjectRevisionWithRefCount2FNDX::serialize(QDataStream &ds) const {
  ds << ref;
  ds << oid;

  quint32 temp{0};

  temp += fHasOidReferences;
  temp += fHasOsidReferences << 1;

  ds << temp;

  ds << cRef;
}

void ObjectRevisionWithRefCount2FNDX::toDebugString(QDebug dbg) const {
  dbg << " ObjectRevisionWithRefCount2FNDX: \n"
      << " ref: " << ref << "oid: " << oid
      << " fHasOidReferences: " << fHasOidReferences
      << " fHasOsidReferences: " << fHasOsidReferences << "cRef: " << cRef;
}
