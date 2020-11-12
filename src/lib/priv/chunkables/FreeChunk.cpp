#include "FreeChunk.h"

namespace libmson {
namespace priv {

FreeChunk::FreeChunk(const quint64 size) : m_size(size) {}

quint64 FreeChunk::cb() const { return m_size; }

RevisionStoreChunkType FreeChunk::getType() const { return RevisionStoreChunkType::FreeChunk; }

} // namespace priv
} // namespace libmson
