#include "ObjectDeclarationWithRefCount2FNDX.h"

ObjectDeclarationWithRefCount2FNDX::ObjectDeclarationWithRefCount2FNDX(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : objectRef(stpFormat, cbFormat) {}

ObjectDeclarationWithRefCount2FNDX::ObjectDeclarationWithRefCount2FNDX(
    quint8 stpFormat, quint8 cbFormat)
    : objectRef(stpFormat, cbFormat) {}

ObjectDeclarationWithRefCount2FNDX::~ObjectDeclarationWithRefCount2FNDX() {}

FileNodeChunkReference
ObjectDeclarationWithRefCount2FNDX::getObjectRef() const {
  return objectRef;
}

void ObjectDeclarationWithRefCount2FNDX::setObjectRef(
    const FileNodeChunkReference &value) {
  objectRef = value;
}

ObjectDeclarationWithRefCountBody
ObjectDeclarationWithRefCount2FNDX::getBody() const {
  return body;
}

void ObjectDeclarationWithRefCount2FNDX::setBody(
    const ObjectDeclarationWithRefCountBody &value) {
  body = value;
}

quint32 ObjectDeclarationWithRefCount2FNDX::getCRef() const { return cRef; }

void ObjectDeclarationWithRefCount2FNDX::setCRef(const quint32 &value) {
  cRef = value;
}

void ObjectDeclarationWithRefCount2FNDX::deserialize(QDataStream &ds) {
  ds >> objectRef;
  ds >> body;
  ds >> cRef;
}

void ObjectDeclarationWithRefCount2FNDX::serialize(QDataStream &ds) const {
  ds << objectRef;
  ds << body;
  ds << cRef;
}

void ObjectDeclarationWithRefCount2FNDX::toDebugString(QDebug dbg) const {
  dbg << " ObjectDeclarationWithRefCount2FNDX:\n"
      << " objectRef: " << objectRef << '\n'
      << " body: " << body << '\n'
      << " cRef: " << cRef << '\n';
}
