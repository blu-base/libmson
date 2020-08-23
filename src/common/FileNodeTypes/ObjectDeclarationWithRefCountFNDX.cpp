#include "ObjectDeclarationWithRefCountFNDX.h"

#include "../helper/Helper.h"

ObjectDeclarationWithRefCountFNDX::ObjectDeclarationWithRefCountFNDX(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : m_objectRef(stpFormat, cbFormat), m_cRef{} {}

ObjectDeclarationWithRefCountFNDX::ObjectDeclarationWithRefCountFNDX(
    quint8 stpFormat, quint8 cbFormat)
    : m_objectRef(stpFormat, cbFormat), m_cRef{} {}

ObjectDeclarationWithRefCountFNDX::~ObjectDeclarationWithRefCountFNDX() {}

FileNodeChunkReference ObjectDeclarationWithRefCountFNDX::getObjectRef() const {
  return m_objectRef;
}

void ObjectDeclarationWithRefCountFNDX::setObjectRef(
    const FileNodeChunkReference &value) {
  m_objectRef = value;
}

ObjectDeclarationWithRefCountBody
ObjectDeclarationWithRefCountFNDX::getBody() const {
  return m_body;
}

void ObjectDeclarationWithRefCountFNDX::setBody(
    const ObjectDeclarationWithRefCountBody &value) {
  m_body = value;
}

quint8 ObjectDeclarationWithRefCountFNDX::getCRef() const { return m_cRef; }

void ObjectDeclarationWithRefCountFNDX::setCRef(const quint8 &value) {
  m_cRef = value;
}

ObjectSpaceObjectPropSet ObjectDeclarationWithRefCountFNDX::getPropSet() const {
  return m_blob;
}

void ObjectDeclarationWithRefCountFNDX::setPropSet(
    const ObjectSpaceObjectPropSet &value) {
    m_blob = value;
}


void ObjectDeclarationWithRefCountFNDX::deserialize(QDataStream &ds) {
  ds >> m_objectRef;
  ds >> m_body;
  ds >> m_cRef;

  // getting remote ObjectPropSet
  quint64 curLocation = ds.device()->pos();
  quint64 destLocation = m_objectRef.stp();

  ds.device()->seek(destLocation);
  ds >> m_blob;
  ds.device()->seek(curLocation);
}

void ObjectDeclarationWithRefCountFNDX::serialize(QDataStream &ds) const {
  ds << m_objectRef;
  ds << m_body;
  ds << m_cRef;
}

void ObjectDeclarationWithRefCountFNDX::toDebugString(QDebug dbg) const {
  dbg << " ObjectDeclarationWithRefCountFNDX:\n"
      << " objectRef: " << m_objectRef << '\n'
      << " body: " << m_body << '\n'
      << " cRef: " << qStringHex(m_cRef,2) << '\n';
}


void ObjectDeclarationWithRefCountFNDX::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("ObjectDeclarationWithRefCountFNDX");

    xmlWriter.writeAttribute("cRef", qStringHex(m_cRef,2));

    m_objectRef.generateXml(xmlWriter);
    m_body.generateXml(xmlWriter);

    m_blob.generateXml(xmlWriter);

    xmlWriter.writeEndElement();
}
