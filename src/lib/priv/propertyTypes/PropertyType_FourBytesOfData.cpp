#include "PropertyType_FourBytesOfData.h"

#include <QDataStream>
#include <QDebug>

namespace libmson {
namespace priv {

QByteArray PropertyType_FourBytesOfData::data() const { return m_data; }

void PropertyType_FourBytesOfData::setData(const QByteArray& data)
{
  m_data = data;
}


PropertyType_FourBytesOfData::PropertyType_FourBytesOfData() {}

void PropertyType_FourBytesOfData::deserialize(QDataStream& ds)
{

  m_data = ds.device()->read(4);
}

void PropertyType_FourBytesOfData::serialize(QDataStream& ds) const
{

  ds.writeRawData(m_data.data(), 4);
}

// void PropertyType_FourBytesOfData::toDebugString(QDebug &dbg) const {}

// void PropertyType_FourBytesOfData::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("FourBytesOfData");
//  xmlWriter.writeCharacters(m_data.toHex());
//  xmlWriter.writeEndElement();
//}

} // namespace priv
} // namespace libmson
