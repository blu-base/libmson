#include "ObjectGroupListReferenceFND.h"

namespace MSONcommon {

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

quint64 ObjectGroupListReferenceFND::getSizeInFile() const
{
  return m_ref.getSizeInFile() + ExtendedGUID::getSizeInFile();
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

void ObjectGroupListReferenceFND::toDebugString(QDebug &dbg) const {
  dbg << " ObjectGroupListReferenceFND:\n"
      << " ref:           " << m_ref << '\n'
      << " ObjectGroupID: " << m_ObjectGroupID << '\n';
}

void ObjectGroupListReferenceFND::writeLowLevelXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ObjectGroupListReferenceFND");

  xmlWriter << m_ref;

  xmlWriter << m_ObjectGroupID;

  xmlWriter.writeEndElement();
}

} // namespace MSONcommon
