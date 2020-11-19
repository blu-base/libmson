#include "UnknownBlob.h"
namespace libmson {
namespace priv {

UnknownBlob::UnknownBlob(const quint64 initialStp, const quint64 initialCb)
    : Chunkable(initialStp, initialCb)
{
  m_blob.resize(initialCb);
}


QByteArray UnknownBlob::getBlob() const { return m_blob; }

void UnknownBlob::setBlob(const QByteArray& blob)
{
  m_isChanged = true;
  m_blob      = blob;
}

quint64 UnknownBlob::cb() const { return m_blob.size(); }

RevisionStoreChunkType UnknownBlob::getType() const
{
  return RevisionStoreChunkType::UnknownBlob;
}

} // namespace priv
} // namespace libmson
