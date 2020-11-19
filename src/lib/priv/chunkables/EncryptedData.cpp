#include "EncryptedData.h"

namespace libmson {
namespace priv {


EncryptedData::EncryptedData(const quint64 initialStp, const quint64 initialCb)
    : Chunkable(initialStp, initialCb)
{
}

EncryptedData::EncryptedData(const QByteArray& data) : m_data(data) {}

QByteArray EncryptedData::getData() const { return m_data; }

void EncryptedData::setData(const QByteArray& encryptionData)
{
  m_isChanged = true;
  m_data      = encryptionData;
}

quint64 libmson::priv::EncryptedData::cb() const
{
  return minSizeInFile + m_data.size();
}

RevisionStoreChunkType libmson::priv::EncryptedData::getType() const
{
  return RevisionStoreChunkType::EncryptedData;
}


} // namespace priv
} // namespace libmson
