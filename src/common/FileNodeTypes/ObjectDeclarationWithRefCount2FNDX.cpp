#include "ObjectDeclarationWithRefCount2FNDX.h"

#include "../helper/Helper.h"

ObjectDeclarationWithRefCount2FNDX::ObjectDeclarationWithRefCount2FNDX(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : m_objectRef(stpFormat, cbFormat) {}

ObjectDeclarationWithRefCount2FNDX::ObjectDeclarationWithRefCount2FNDX(
    quint8 stpFormat, quint8 cbFormat)
    : m_objectRef(stpFormat, cbFormat) {}

ObjectDeclarationWithRefCount2FNDX::~ObjectDeclarationWithRefCount2FNDX() {}

FileNodeChunkReference
ObjectDeclarationWithRefCount2FNDX::getObjectRef() const {
  return m_objectRef;
}

void ObjectDeclarationWithRefCount2FNDX::setObjectRef(
    const FileNodeChunkReference &value) {
  m_objectRef = value;
}

ObjectDeclarationWithRefCountBody
ObjectDeclarationWithRefCount2FNDX::getBody() const {
  return m_body;
}

void ObjectDeclarationWithRefCount2FNDX::setBody(
    const ObjectDeclarationWithRefCountBody &value) {
  m_body = value;
}

quint32 ObjectDeclarationWithRefCount2FNDX::getCRef() const { return m_cRef; }

void ObjectDeclarationWithRefCount2FNDX::setCRef(const quint32 &value) {
  m_cRef = value;
}

void ObjectDeclarationWithRefCount2FNDX::deserialize(QDataStream &ds) {
  ds >> m_objectRef;
  ds >> m_body;
  ds >> m_cRef;
}

void ObjectDeclarationWithRefCount2FNDX::serialize(QDataStream &ds) const {
  ds << m_objectRef;
  ds << m_body;
  ds << m_cRef;
}

void ObjectDeclarationWithRefCount2FNDX::toDebugString(QDebug dbg) const {
  dbg << " ObjectDeclarationWithRefCount2FNDX:\n"
      << " objectRef: " << m_objectRef << '\n'
      << " body: " << m_body << '\n'
      << " cRef: " << m_cRef << '\n';
}

void ObjectDeclarationWithRefCount2FNDX::generateXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ObjectDeclarationWithRefCount2FNDX");

  xmlWriter.writeAttribute("cRef", qStringHex(m_cRef, 8));

  m_objectRef.generateXml(xmlWriter);
  m_body.generateXml(xmlWriter);

  xmlWriter.writeEndElement();
}
