#include "ObjectInfoDependencyOverridesFND.h"

namespace MSONcommon {

ObjectInfoDependencyOverridesFND::ObjectInfoDependencyOverridesFND(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : m_ref(stpFormat, cbFormat) {}

ObjectInfoDependencyOverridesFND::ObjectInfoDependencyOverridesFND(
    quint8 stpFormat, quint8 cbFormat)
    : m_ref(stpFormat, cbFormat) {}

ObjectInfoDependencyOverridesFND::~ObjectInfoDependencyOverridesFND() {}

ObjectInfoDependencyOverrideData
ObjectInfoDependencyOverridesFND::getData() const {
  return m_data;
}

void ObjectInfoDependencyOverridesFND::setData(
    const ObjectInfoDependencyOverrideData &value) {
  m_data = value;
}

FileNodeChunkReference ObjectInfoDependencyOverridesFND::getRef() const {
  return m_ref;
}

void ObjectInfoDependencyOverridesFND::setRef(
    const FileNodeChunkReference &value) {
  m_ref = value;
}

/**
 * @brief ObjectInfoDependencyOverridesFND::deserialize
 * @param ds
 *
 * \todo check if device/seek stuff is working
 */
void ObjectInfoDependencyOverridesFND::deserialize(QDataStream &ds) {
  ds >> m_ref;

  if (m_ref.is_fcrNil()) {
    ds >> m_data;
  } else {
    quint64 currentloc = ds.device()->pos();
    ds.device()->seek(m_ref.stp());
    ds >> m_data;
    ds.device()->seek(currentloc);
  }
}

/**
 * @brief ObjectInfoDependencyOverridesFND::serialize
 * @param ds
 *
 * \todo likely contains bugs
 * \todo ObjectInfoDependencyOverrideData is not yet parsed.
 */
void ObjectInfoDependencyOverridesFND::serialize(QDataStream &ds) const {
  ds << m_ref;

  if (m_ref.is_fcrNil()) {
            ds << m_data;
  } else {
    quint64 currentloc = ds.device()->pos();
    ds.device()->seek(m_ref.stp());
            ds << m_data;
    ds.device()->seek(currentloc);
  }
}

void ObjectInfoDependencyOverridesFND::toDebugString(QDebug dbg) const {
  dbg << " ObjectInfoDependencyOverridesFND:\n"
      << " ref: " << m_ref << "data: " << m_data << '\n';
}

void ObjectInfoDependencyOverridesFND::generateXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ObjectInfoDependencyOverridesFND");
  m_ref.generateXml(xmlWriter);

  m_data.generateXml(xmlWriter);

  xmlWriter.writeEndElement();
}

} // namespace MSONcommon
