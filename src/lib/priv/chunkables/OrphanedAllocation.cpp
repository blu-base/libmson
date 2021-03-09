#include "OrphanedAllocation.h"

namespace libmson {
namespace priv {

OrphanedAllocation::OrphanedAllocation(const quint64 initialStp, const quint64 initialCb)
    : Chunkable(initialStp, initialCb)
{
  m_blob.resize(initialCb);
}


QByteArray OrphanedAllocation::getBlob() const { return m_blob; }

void OrphanedAllocation::setBlob(const QByteArray& blob)
{
  m_isChanged = true;
  m_blob      = blob;
}

quint64 OrphanedAllocation::cb() const { return m_blob.size(); }

RevisionStoreChunkType OrphanedAllocation::getType() const
{
  return RevisionStoreChunkType::OrphanedAllocation;
}

} // namespace priv
} // namespace libmson
