#include "ObjectDeclaration2LargeRefCountFND.h"
#include "../helper/Helper.h"

ObjectDeclaration2LargeRefCountFND::ObjectDeclaration2LargeRefCountFND(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : m_BlobRef(stpFormat, cbFormat), m_cRef() {}

ObjectDeclaration2LargeRefCountFND::ObjectDeclaration2LargeRefCountFND(
    quint8 stpFormat, quint8 cbFormat)
    : m_BlobRef(stpFormat, cbFormat), m_cRef() {}

ObjectDeclaration2LargeRefCountFND::~ObjectDeclaration2LargeRefCountFND() {}

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

FileNodeChunkReference ObjectDeclaration2LargeRefCountFND::BlobRef() const {
  return m_BlobRef;
}

void ObjectDeclaration2LargeRefCountFND::setBlobRef(
    const FileNodeChunkReference &BlobRef) {
  m_BlobRef = BlobRef;
}

void ObjectDeclaration2LargeRefCountFND::deserialize(QDataStream &ds) {
  ds >> m_BlobRef;
  ds >> m_body;
  ds >> m_cRef;

  // getting remote ObjectPropSet
  quint64 curLocation = ds.device()->pos();
  quint64 destLocation = m_BlobRef.stp();

  ds.device()->seek(destLocation);
  ds >> m_blob;
  ds.device()->seek(curLocation);
}

void ObjectDeclaration2LargeRefCountFND::serialize(QDataStream &ds) const {
  ds << m_BlobRef;
  ds << m_body;
  ds << m_cRef;
}

void ObjectDeclaration2LargeRefCountFND::toDebugString(QDebug dbg) const {
  dbg << " ObjectDeclaration2LargeRefCountFND\n"
      << " BlobRef: " << m_BlobRef << '\n'
      << " body:\n"
      << m_body << "\n"
      << " cRef: " << qStringHex(m_cRef, 8) << '\n';
}


void ObjectDeclaration2LargeRefCountFND::generateXml(QXmlStreamWriter& xmlWriter) const
{

    xmlWriter.writeStartElement("ObjectDeclaration2LargeRefCountFND");

    xmlWriter.writeAttribute("cRef", qStringHex(m_cRef, 8));

    m_BlobRef.generateXml(xmlWriter);

    m_body.generateXml(xmlWriter);

    m_blob.generateXml(xmlWriter);

    xmlWriter.writeEndElement();
}
