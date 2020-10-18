#include "FreeChunk.h"

namespace libmson {

FreeChunk::FreeChunk(const quint64 size) : m_size(size) {}

qint64 FreeChunk::cb() const { return m_size; }

RevisionStoreChunkType libmson::FreeChunk::getType() const {
  return RevisionStoreChunkType::FreeChunk;
}
} // namespace libmson
