#include "ObjectRevisionWithRefCountFNDX.h"

ObjectRevisionWithRefCountFNDX::ObjectRevisionWithRefCountFNDX(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : ref{FileNodeChunkReference(stpFormat, cbFormat)} {}
ObjectRevisionWithRefCountFNDX::ObjectRevisionWithRefCountFNDX(quint8 stpFormat,
                                                               quint8 cbFormat)
    : ref{FileNodeChunkReference(stpFormat, cbFormat)} {}

bool ObjectRevisionWithRefCountFNDX::getFHasOsidReferences() const {
  return fHasOsidReferences;
}

void ObjectRevisionWithRefCountFNDX::setFHasOsidReferences(bool value) {
  fHasOsidReferences = value;
}

bool ObjectRevisionWithRefCountFNDX::getFHasOidReferences() const {
  return fHasOidReferences;
}

void ObjectRevisionWithRefCountFNDX::setFHasOidReferences(bool value) {
  fHasOidReferences = value;
}

quint8 ObjectRevisionWithRefCountFNDX::getCRef() const { return cRef; }

void ObjectRevisionWithRefCountFNDX::setCRef(const quint8 &value) {
  cRef = value;
}

CompactID ObjectRevisionWithRefCountFNDX::getOid() const { return oid; }

void ObjectRevisionWithRefCountFNDX::setOid(const CompactID &value) {
  oid = value;
}

FileNodeChunkReference ObjectRevisionWithRefCountFNDX::getRef() const {
  return ref;
}

void ObjectRevisionWithRefCountFNDX::setRef(
    const FileNodeChunkReference &value) {
  ref = value;
}

void ObjectRevisionWithRefCountFNDX::deserialize(QDataStream &ds) {

  ds.setByteOrder(QDataStream::LittleEndian);

  ds >> ref;
  ds >> oid;
  ds >> cRef;

  cRef = cRef >> 2;
  fHasOidReferences = cRef & 0x1;
  fHasOsidReferences = cRef & 0x2;
}

void ObjectRevisionWithRefCountFNDX::serialize(QDataStream &ds) const {

  ds.setByteOrder(QDataStream::LittleEndian);

  ds << ref;
  ds << oid;

  quint8 temp = cRef >> 2;
  temp += fHasOidReferences;
  temp += fHasOsidReferences << 1;

  ds << temp;
}

void ObjectRevisionWithRefCountFNDX::toDebugString(QDebug dbg) const {
  dbg << " ObjectRevisionWithRefCountFNDX:\n"
      << " Ref: " << ref << "oid: " << oid << "cRef: " << cRef
      << " fHasOidReferences: " << fHasOidReferences
      << " fHasOsidReferences: " << fHasOsidReferences << '\n';
}
