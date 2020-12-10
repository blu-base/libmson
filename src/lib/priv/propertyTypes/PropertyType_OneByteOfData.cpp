#include "PropertyType_OneByteOfData.h"

namespace libmson {
namespace priv {

QByteArray PropertyType_OneByteOfData::data() const { return m_data; }

void PropertyType_OneByteOfData::setData(const QByteArray& data)
{
  m_data = data;
}


PropertyType_OneByteOfData::PropertyType_OneByteOfData() : m_data() {}

PropertyIDType PropertyType_OneByteOfData::getType() const
{
  return PropertyIDType::OneByteOfData;
}

void PropertyType_OneByteOfData::deserialize(QDataStream& ds)
{

  m_data = ds.device()->read(1);
}

void PropertyType_OneByteOfData::serialize(QDataStream& ds) const
{
  ds.writeRawData(m_data.data(), 1);
}

} // namespace priv
} // namespace libmson
