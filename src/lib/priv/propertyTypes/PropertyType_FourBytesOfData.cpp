#include "PropertyType_FourBytesOfData.h"

namespace libmson {
namespace priv {

PropertyType_FourBytesOfData::PropertyType_FourBytesOfData() {}


QByteArray PropertyType_FourBytesOfData::data() const { return m_data; }

void PropertyType_FourBytesOfData::setData(const QByteArray& data)
{
  m_data = data;
}


PropertyIDType PropertyType_FourBytesOfData::getType() const
{
  return PropertyIDType::FourBytesOfData;
}

void PropertyType_FourBytesOfData::deserialize(QDataStream& ds)
{

  m_data = ds.device()->read(4);
}

void PropertyType_FourBytesOfData::serialize(QDataStream& ds) const
{

  ds.writeRawData(m_data.data(), 4);
}

} // namespace priv
} // namespace libmson
