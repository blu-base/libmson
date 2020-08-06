#include "ObjectRevisionWithRefCountFNDX.h"

#include "../helper/Helper.h"

ObjectRevisionWithRefCountFNDX::ObjectRevisionWithRefCountFNDX(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : m_ref{FileNodeChunkReference(stpFormat, cbFormat)},
      m_fHasOidReferences(false), m_fHasOsidReferences(false), m_cRef(0) {}
ObjectRevisionWithRefCountFNDX::ObjectRevisionWithRefCountFNDX(quint8 stpFormat,
                                                               quint8 cbFormat)
    : m_ref{FileNodeChunkReference(stpFormat, cbFormat)},
      m_fHasOidReferences(false), m_fHasOsidReferences(false), m_cRef(0) {}

bool ObjectRevisionWithRefCountFNDX::getFHasOsidReferences() const {
  return m_fHasOsidReferences;
}

void ObjectRevisionWithRefCountFNDX::setFHasOsidReferences(bool value) {
  m_fHasOsidReferences = value;
}

bool ObjectRevisionWithRefCountFNDX::getFHasOidReferences() const {
  return m_fHasOidReferences;
}

void ObjectRevisionWithRefCountFNDX::setFHasOidReferences(bool value) {
  m_fHasOidReferences = value;
}

quint8 ObjectRevisionWithRefCountFNDX::getCRef() const { return m_cRef; }

void ObjectRevisionWithRefCountFNDX::setCRef(const quint8 &value) {
  m_cRef = value;
}

CompactID ObjectRevisionWithRefCountFNDX::getOid() const { return m_oid; }

void ObjectRevisionWithRefCountFNDX::setOid(const CompactID &value) {
  m_oid = value;
}

FileNodeChunkReference ObjectRevisionWithRefCountFNDX::getRef() const {
  return m_ref;
}

void ObjectRevisionWithRefCountFNDX::setRef(
    const FileNodeChunkReference &value) {
  m_ref = value;
}

void ObjectRevisionWithRefCountFNDX::deserialize(QDataStream &ds) {

  ds.setByteOrder(QDataStream::LittleEndian);

  ds >> m_ref;
  ds >> m_oid;
  ds >> m_cRef;

  m_cRef = m_cRef >> 2;
  m_fHasOidReferences = m_cRef & 0x1;
  m_fHasOsidReferences = m_cRef & 0x2;
}

void ObjectRevisionWithRefCountFNDX::serialize(QDataStream &ds) const {

  ds.setByteOrder(QDataStream::LittleEndian);

  ds << m_ref;
  ds << m_oid;

  quint8 temp = m_cRef >> 2;
  temp += m_fHasOidReferences;
  temp += m_fHasOsidReferences << 1;

  ds << temp;
}

void ObjectRevisionWithRefCountFNDX::toDebugString(QDebug dbg) const {
  dbg << " ObjectRevisionWithRefCountFNDX:\n"
      << " Ref: " << m_ref << "oid: " << m_oid << "cRef: " << m_cRef
      << " fHasOidReferences: " << m_fHasOidReferences
      << " fHasOsidReferences: " << m_fHasOsidReferences << '\n';
}

void ObjectRevisionWithRefCountFNDX::generateXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ObjectRevisionWithRefCountFNDX");

  xmlWriter.writeAttribute("cRef", qStringHex(m_cRef, 8));
  xmlWriter.writeAttribute("fHasOidReferences",
                           m_fHasOidReferences ? "true" : "false");
  xmlWriter.writeAttribute("fHasOsidReferences",
                           m_fHasOsidReferences ? "true" : "false");

  m_ref.generateXml(xmlWriter);

  m_oid.generateXml(xmlWriter);

  xmlWriter.writeEndElement();
}
