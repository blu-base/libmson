#include "FreeChunk.h"

namespace libmson {
namespace priv {

quint64 FreeChunk::getSize() const { return m_size; }

void FreeChunk::setSize(const quint64& size) { m_size = size; }

FreeChunk::FreeChunk(
    const quint64 initialStp, const quint64 initialCb)
    : Chunkable(initialStp, initialCb), m_size(initialCb)
{
}

quint64 FreeChunk::cb() const { return m_size; }

RevisionStoreChunkType FreeChunk::getType() const
{
  return RevisionStoreChunkType::FreeChunk;
}

} // namespace priv
} // namespace libmson
