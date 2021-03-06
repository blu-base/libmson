#include "PropertyType_FourBytesOfLengthFollowedByData.h"

namespace libmson {
namespace priv {

QByteArray PropertyType_FourBytesOfLengthFollowedByData::data() const
{
  return m_data;
}

void PropertyType_FourBytesOfLengthFollowedByData::setData(
    const QByteArray& data)
{
  m_data = data;
}

quint64 PropertyType_FourBytesOfLengthFollowedByData::getSizeInFile() const
{
  return sizeInFileBase + m_cb;
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
    PropertyType_FourBytesOfLengthFollowedByData()
    : m_cb()
{
}

void PropertyType_FourBytesOfLengthFollowedByData::deserialize(QDataStream& ds)
{

  ds >> m_cb;
  m_data = ds.device()->read(m_cb);
}

void PropertyType_FourBytesOfLengthFollowedByData::serialize(
    QDataStream& ds) const
{
  ds << m_cb;
  ds.writeRawData(m_data.data(), m_cb);
}

PropertyIDType PropertyType_FourBytesOfLengthFollowedByData::getType() const
{
  return PropertyIDType::FourBytesOfLengthFollowedByData;
}

} // namespace priv
} // namespace libmson
