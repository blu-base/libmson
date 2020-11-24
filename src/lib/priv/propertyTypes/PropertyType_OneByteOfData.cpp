#include "PropertyType_OneByteOfData.h"

namespace libmson {
namespace priv {

uint8_t PropertyType_OneByteOfData::data() const { return m_data; }

void PropertyType_OneByteOfData::setData(const uint8_t data) { m_data = data; }


PropertyType_OneByteOfData::PropertyType_OneByteOfData() : m_data() {}

void PropertyType_OneByteOfData::deserialize(QDataStream& ds) { ds >> m_data; }

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
