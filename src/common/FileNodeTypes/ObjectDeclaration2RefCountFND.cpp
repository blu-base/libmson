#include "ObjectDeclaration2RefCountFND.h"

ObjectDeclaration2RefCountFND::ObjectDeclaration2RefCountFND(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : blobRef(stpFormat, cbFormat), cRef{} {}

ObjectDeclaration2RefCountFND::ObjectDeclaration2RefCountFND(quint8 stpFormat,
                                                             quint8 cbFormat)
    : blobRef(stpFormat, cbFormat), cRef{} {}

ObjectDeclaration2RefCountFND::~ObjectDeclaration2RefCountFND() {}

quint8 ObjectDeclaration2RefCountFND::getCRef() const { return cRef; }

void ObjectDeclaration2RefCountFND::setCRef(const quint8 &value) {
  cRef = value;
}

ObjectDeclaration2Body ObjectDeclaration2RefCountFND::getBody() const {
  return body;
}

void ObjectDeclaration2RefCountFND::setBody(
    const ObjectDeclaration2Body &value) {
  body = value;
}

FileNodeChunkReference ObjectDeclaration2RefCountFND::getBlobRef() const {
  return blobRef;
}

void ObjectDeclaration2RefCountFND::setBlobRef(
    const FileNodeChunkReference &value) {
  blobRef = value;
}

void ObjectDeclaration2RefCountFND::deserialize(QDataStream &ds) {
  ds >> blobRef;

  ds >> body;
  ds >> cRef;
}

void ObjectDeclaration2RefCountFND::serialize(QDataStream &ds) const {
  ds << blobRef;
  ds << body;
  ds << cRef;
}

void ObjectDeclaration2RefCountFND::toDebugString(QDebug dbg) const {
  dbg << " ObjectDeclaration2RefCountFND:\n"
      << " blobRef: " << blobRef << '\n'
      << " body:\n"
      << body << " cRef: " << cRef << 'n';
}
