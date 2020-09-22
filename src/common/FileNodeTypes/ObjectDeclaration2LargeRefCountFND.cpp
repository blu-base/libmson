#include "ObjectDeclaration2LargeRefCountFND.h"
#include "../helper/Helper.h"

#include "../DocumentManager.h"

namespace MSONcommon {
ObjectDeclaration2LargeRefCountFND::ObjectDeclaration2LargeRefCountFND(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : m_blobRef(stpFormat, cbFormat), m_cRef() {}

ObjectDeclaration2LargeRefCountFND::ObjectDeclaration2LargeRefCountFND(
    quint8 stpFormat, quint8 cbFormat)
    : m_blobRef(stpFormat, cbFormat), m_cRef() {}

ObjectDeclaration2Body ObjectDeclaration2LargeRefCountFND::body() const {
  return m_body;
}

void ObjectDeclaration2LargeRefCountFND::setBody(
    const ObjectDeclaration2Body &body) {
  m_body = body;
}

quint32 ObjectDeclaration2LargeRefCountFND::cRef() const { return m_cRef; }

void ObjectDeclaration2LargeRefCountFND::setCRef(const quint32 &cRef) {
  m_cRef = cRef;
}

quint64 ObjectDeclaration2LargeRefCountFND::getSizeInFile() const {
  return m_blobRef.getSizeInFile() + m_body.getSizeInFile() + sizeof(m_cRef);
}

FileNodeChunkReference ObjectDeclaration2LargeRefCountFND::blobRef() const {
  return m_blobRef;
}

void ObjectDeclaration2LargeRefCountFND::setBlobRef(
    const FileNodeChunkReference &blobRef) {
  m_blobRef = blobRef;
}

void ObjectDeclaration2LargeRefCountFND::deserialize(QDataStream &ds) {
  ds >> m_blobRef;
  ds >> m_body;
  ds >> m_cRef;

  m_blob = ObjectSpaceObjectPropSet(ds, m_blobRef);
}

void ObjectDeclaration2LargeRefCountFND::serialize(QDataStream &ds) const {
  ds << m_blobRef;
  ds << m_body;
  ds << m_cRef;
}

void ObjectDeclaration2LargeRefCountFND::toDebugString(QDebug &dbg) const {
  dbg << " ObjectDeclaration2LargeRefCountFND\n"
      << " blobRef: " << m_blobRef << '\n'
      << " body:\n"
      << m_body << "\n"
      << " cRef: " << qStringHex(m_cRef, 8) << '\n';
}

void ObjectDeclaration2LargeRefCountFND::writeLowLevelXml(
    QXmlStreamWriter &xmlWriter) const {

  xmlWriter.writeStartElement("ObjectDeclaration2LargeRefCountFND");

  xmlWriter.writeAttribute("cRef", qStringHex(m_cRef, 8));

  xmlWriter << m_blobRef;

  xmlWriter << m_body;

  xmlWriter << m_blob;

  xmlWriter.writeEndElement();
}

} // namespace MSONcommon
