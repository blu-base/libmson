#include "PropertyType_FourBytesOfLengthFollowedByData.h"

#include <QDataStream>
#include <QDebug>

namespace MSONcommon {

QByteArray PropertyType_FourBytesOfLengthFollowedByData::data() const {
  return m_data;
}

void PropertyType_FourBytesOfLengthFollowedByData::setData(
    const QByteArray &data) {
  m_data = data;
}

quint64 PropertyType_FourBytesOfLengthFollowedByData::getSizeInFile() const {
  return sizeInFileBase + m_cb;
}

void PropertyType_FourBytesOfLengthFollowedByData::writeLowLevelXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("FourBytesOfLengthFollowedByData");
  xmlWriter.writeAttribute("cb", QString::number(m_cb));
  xmlWriter.writeCharacters(m_data.toHex());
  xmlWriter.writeEndElement();
}

quint32 PropertyType_FourBytesOfLengthFollowedByData::cb() const {
  return m_cb;
}

void PropertyType_FourBytesOfLengthFollowedByData::setCb(const quint32 &cb) {
  m_cb = cb;
}

PropertyType_FourBytesOfLengthFollowedByData::
    PropertyType_FourBytesOfLengthFollowedByData()
    : m_cb() {}

void PropertyType_FourBytesOfLengthFollowedByData::deserialize(
    QDataStream &ds) {

  ds >> m_cb;

  m_data = ds.device()->read(m_cb);
}

void PropertyType_FourBytesOfLengthFollowedByData::serialize(
    QDataStream &ds) const {
  ds << m_cb;
  ds << m_data;
}

void PropertyType_FourBytesOfLengthFollowedByData::toDebugString(
    QDebug &dbg) const {}

} // namespace MSONcommon
