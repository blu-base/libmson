#include "PropertyType_TwoBytesOfData.h"


namespace libmson {
namespace priv {

QByteArray PropertyType_TwoBytesOfData::data() const { return m_data; }

void PropertyType_TwoBytesOfData::setData(const QByteArray& data)
{
  m_data = data;
}


PropertyType_TwoBytesOfData::PropertyType_TwoBytesOfData() {}

void PropertyType_TwoBytesOfData::deserialize(QDataStream& ds)
{

  m_data = ds.device()->read(2);
}

void PropertyType_TwoBytesOfData::serialize(QDataStream& ds) const
{
  ds.writeRawData(m_data.data(), 2);
}


// void PropertyType_TwoBytesOfData::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("TwoBytesOfData");
//  xmlWriter.writeCharacters(m_data.toHex());
//  xmlWriter.writeEndElement();
//}

// void PropertyType_TwoBytesOfData::toDebugString(QDebug &dbg) const {}

} // namespace priv
} // namespace libmson
