#include "ObjectDeclaration2RefCountFND.h"

#include "../helper/Helper.h"

ObjectDeclaration2RefCountFND::ObjectDeclaration2RefCountFND(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : m_blobRef(stpFormat, cbFormat), m_cRef{} {}

ObjectDeclaration2RefCountFND::ObjectDeclaration2RefCountFND(quint8 stpFormat,
                                                             quint8 cbFormat)
    : m_blobRef(stpFormat, cbFormat), m_cRef{} {}

ObjectDeclaration2RefCountFND::~ObjectDeclaration2RefCountFND() {}

quint8 ObjectDeclaration2RefCountFND::getCRef() const { return m_cRef; }

void ObjectDeclaration2RefCountFND::setCRef(const quint8 &value) {
  m_cRef = value;
}

ObjectDeclaration2Body ObjectDeclaration2RefCountFND::getBody() const {
  return m_body;
}

void ObjectDeclaration2RefCountFND::setBody(
    const ObjectDeclaration2Body &value) {
  m_body = value;
}

FileNodeChunkReference ObjectDeclaration2RefCountFND::getBlobRef() const {
  return m_blobRef;
}

void ObjectDeclaration2RefCountFND::setBlobRef(
    const FileNodeChunkReference &value) {
  m_blobRef = value;
}

void ObjectDeclaration2RefCountFND::deserialize(QDataStream &ds) {
  ds >> m_blobRef;

  ds >> m_body;
  ds >> m_cRef;
}

void ObjectDeclaration2RefCountFND::serialize(QDataStream &ds) const {
  ds << m_blobRef;
  ds << m_body;
  ds << m_cRef;
}

void ObjectDeclaration2RefCountFND::toDebugString(QDebug dbg) const {
  dbg << " ObjectDeclaration2RefCountFND:\n"
      << " blobRef: " << m_blobRef << '\n'
      << " body:\n"
      << m_body << " cRef: " << qStringHex(m_cRef, 2) << 'n';
}


void ObjectDeclaration2RefCountFND::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("ObjectDeclaration2RefCountFND");

    xmlWriter.writeAttribute("cRef", qStringHex(m_cRef, 16));

    m_blobRef.generateXml(xmlWriter);

    m_body.generateXml(xmlWriter);

    xmlWriter.writeEndElement();
}
