#include "ObjectDeclarationWithRefCount2FNDX.h"

#include "../DocumentManager.h"
#include "../helper/Helper.h"

namespace libmson{
namespace priv{

ObjectDeclarationWithRefCount2FNDX::ObjectDeclarationWithRefCount2FNDX(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : m_objectRef(stpFormat, cbFormat), m_cRef() {}

ObjectDeclarationWithRefCount2FNDX::ObjectDeclarationWithRefCount2FNDX(
    quint8 stpFormat, quint8 cbFormat)
    : m_objectRef(stpFormat, cbFormat), m_cRef() {}

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

ObjectSpaceObjectPropSet
ObjectDeclarationWithRefCount2FNDX::getPropSet() const {
  return m_blob;
}

void ObjectDeclarationWithRefCount2FNDX::setPropSet(
    const ObjectSpaceObjectPropSet &value) {
  m_blob = value;
}

quint64 ObjectDeclarationWithRefCount2FNDX::getSizeInFile() const {
  return m_objectRef.getSizeInFile() + m_body.getSizeInFile() + sizeof(m_cRef);
}

void ObjectDeclarationWithRefCount2FNDX::deserialize(QDataStream &ds) {
  ds >> m_objectRef;
  ds >> m_body;
  ds >> m_cRef;

  m_blob = ObjectSpaceObjectPropSet(ds, m_objectRef);
}

void ObjectDeclarationWithRefCount2FNDX::serialize(QDataStream &ds) const {
  ds << m_objectRef;
  ds << m_body;
  ds << m_cRef;
}

void ObjectDeclarationWithRefCount2FNDX::toDebugString(QDebug &dbg) const {
  dbg << " ObjectDeclarationWithRefCount2FNDX:\n"
      << " objectRef: " << m_objectRef << '\n'
      << " body: " << m_body << '\n'
      << " cRef: " << m_cRef << '\n';
}

void ObjectDeclarationWithRefCount2FNDX::writeLowLevelXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ObjectDeclarationWithRefCount2FNDX");

  xmlWriter.writeAttribute("cRef", qStringHex(m_cRef, 8));

  xmlWriter << m_objectRef;
  xmlWriter << m_body;

  xmlWriter << m_blob;

  xmlWriter.writeEndElement();
}

} //namespace priv
} // namespace libmson
