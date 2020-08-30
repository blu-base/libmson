#include "PropertyType_TwoBytesOfData.h"

#include <QDataStream>
#include <QDebug>

QByteArray PropertyType_TwoBytesOfData::data() const { return m_data; }

void PropertyType_TwoBytesOfData::setData(const QByteArray &data) {
  m_data = data;
}

void PropertyType_TwoBytesOfData::generateXml(
    QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("TwoBytesOfData");
  xmlWriter.writeCharacters(m_data.toHex());
  xmlWriter.writeEndElement();
}

PropertyType_TwoBytesOfData::PropertyType_TwoBytesOfData() {}

void PropertyType_TwoBytesOfData::deserialize(QDataStream &ds) {

  m_data = ds.device()->read(2);
}

void PropertyType_TwoBytesOfData::serialize(QDataStream &ds) const {
  ds << m_data;
}

void PropertyType_TwoBytesOfData::toDebugString(QDebug dbg) const {}
