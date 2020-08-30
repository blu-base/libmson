#include "ObjectGroupListReferenceFND.h"

ObjectGroupListReferenceFND::ObjectGroupListReferenceFND(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : m_ref(stpFormat, cbFormat) {}

ObjectGroupListReferenceFND::ObjectGroupListReferenceFND(quint8 stpFormat,
                                                         quint8 cbFormat)
    : m_ref(stpFormat, cbFormat) {}

ExtendedGUID ObjectGroupListReferenceFND::objectGroupID() const {
  return m_ObjectGroupID;
}

void ObjectGroupListReferenceFND::setObjectGroupID(
    const ExtendedGUID &objectGroupID) {
  m_ObjectGroupID = objectGroupID;
}

FileNodeChunkReference ObjectGroupListReferenceFND::ref() const {
  return m_ref;
}

void ObjectGroupListReferenceFND::setRef(const FileNodeChunkReference &ref) {
  m_ref = ref;
}

void ObjectGroupListReferenceFND::deserialize(QDataStream &ds) {
  ds >> m_ref;
  ds >> m_ObjectGroupID;
}

void ObjectGroupListReferenceFND::serialize(QDataStream &ds) const {
  ds << m_ref;
  ds << m_ObjectGroupID;
}

void ObjectGroupListReferenceFND::toDebugString(QDebug dbg) const {
  dbg << " ObjectGroupListReferenceFND:\n"
      << " ref:           " << m_ref << '\n'
      << " ObjectGroupID: " << m_ObjectGroupID << '\n';
}

void ObjectGroupListReferenceFND::generateXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ObjectGroupListReferenceFND");

  m_ref.generateXml(xmlWriter);

  m_ObjectGroupID.generateXml(xmlWriter);

  xmlWriter.writeEndElement();
}
