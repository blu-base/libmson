#include "PropertyType_EightBytesOfData.h"

#include <QDataStream>
#include <QDebug>

namespace libmson {
namespace priv {

QByteArray PropertyType_EightBytesOfData::data() const { return m_data; }

void PropertyType_EightBytesOfData::setData(const QByteArray& data)
{
  m_data = data;
}


PropertyType_EightBytesOfData::PropertyType_EightBytesOfData() {}

void PropertyType_EightBytesOfData::deserialize(QDataStream& ds)
{

  m_data = ds.device()->read(8);
}

void PropertyType_EightBytesOfData::serialize(QDataStream& ds) const
{
  ds.writeRawData(m_data.data(), 8);
}

// void PropertyType_EightBytesOfData::toDebugString(QDebug &dbg) const {}

// void PropertyType_EightBytesOfData::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("EightBytesOfData");
//  xmlWriter.writeCharacters(m_data.toHex());
//  xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson