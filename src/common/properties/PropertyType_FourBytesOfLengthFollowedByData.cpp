#include "PropertyType_FourBytesOfLengthFollowedByData.h"

#include <QDataStream>
#include <QDebug>

QByteArray
PropertyType_FourBytesOfLengthFollowedByData::data() const {
  return m_data;
}

void PropertyType_FourBytesOfLengthFollowedByData::setData(
    const QByteArray &data) {
    m_data = data;
}

void PropertyType_FourBytesOfLengthFollowedByData::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("FourBytesOfLengthFollowedByData");
    xmlWriter.writeAttribute("cb", QString::number(m_cb));
    xmlWriter.writeCharacters(m_data.toHex());
    xmlWriter.writeEndElement();
}

quint32 PropertyType_FourBytesOfLengthFollowedByData::cb() const
{
    return m_cb;
}

void PropertyType_FourBytesOfLengthFollowedByData::setCb(const quint32& cb)
{
    m_cb = cb;
}

PropertyType_FourBytesOfLengthFollowedByData::
PropertyType_FourBytesOfLengthFollowedByData() : m_cb(){}

void PropertyType_FourBytesOfLengthFollowedByData::deserialize(
        QDataStream &ds) {

  ds >> m_cb;

  char* rawBody = new char[m_cb];
  ds.readRawData(rawBody, m_cb);

  m_data = QByteArray(QByteArray::fromRawData(rawBody, m_cb));


}

void PropertyType_FourBytesOfLengthFollowedByData::serialize(
    QDataStream &ds) const {
    ds << m_cb;
  ds << m_data;
}

void PropertyType_FourBytesOfLengthFollowedByData::toDebugString(
    QDebug dbg) const {}
