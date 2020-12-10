#include "PropertyType_EightBytesOfData.h"

namespace libmson {
namespace priv {

PropertyType_EightBytesOfData::PropertyType_EightBytesOfData() {}


QByteArray PropertyType_EightBytesOfData::data() const { return m_data; }

void PropertyType_EightBytesOfData::setData(const QByteArray& data)
{
  m_data = data;
}


PropertyIDType PropertyType_EightBytesOfData::getType() const
{
  return PropertyIDType::EightBytesOfData;
}


void PropertyType_EightBytesOfData::deserialize(QDataStream& ds)
{

  m_data = ds.device()->read(8);
}

void PropertyType_EightBytesOfData::serialize(QDataStream& ds) const
{
  ds.writeRawData(m_data.data(), 8);
}

} // namespace priv
} // namespace libmson
