#include "PropertyType_OneByteOfData.h"

#include <QDataStream>
#include <QDebug>

namespace libmson {
namespace priv {

QByteArray PropertyType_OneByteOfData::data() const { return m_data; }

void PropertyType_OneByteOfData::setData(const QByteArray& data)
{
  m_data = data;
}


PropertyType_OneByteOfData::PropertyType_OneByteOfData() {}

void PropertyType_OneByteOfData::deserialize(QDataStream& ds)
{
  m_data = ds.device()->read(1);
}

void PropertyType_OneByteOfData::serialize(QDataStream& ds) const
{
  ds << m_data;
}

// void PropertyType_OneByteOfData::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("OneByteOfData");
//  xmlWriter.writeCharacters(m_data.toHex());
//  xmlWriter.writeEndElement();
//}


// void PropertyType_OneByteOfData::toDebugString(QDebug &dbg) const {}

} // namespace priv
} // namespace libmson
