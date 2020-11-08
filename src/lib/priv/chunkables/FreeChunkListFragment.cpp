#include "FreeChunkListFragment.h"

namespace libmson {

FreeChunkListFragment::FreeChunkListFragment() {}

FreeChunkListFragment::FreeChunkListFragment(const quint64 size) {
  if (size > minSizeInFile) {
    m_fcrFreeChunks.resize((size - minSizeInFile) / 16u);
  }
}

quint32 FreeChunkListFragment::getCrc() const { return m_crc; }

void FreeChunkListFragment::setCrc(const quint32 value) { m_crc = value; }

std::weak_ptr<RevisionStoreChunkContainer> FreeChunkListFragment::getFcrNextFragment() {
  return m_fcrNextFragment;
}

void FreeChunkListFragment::setFcrNextFragment(
    std::weak_ptr<RevisionStoreChunkContainer> value) {
  m_fcrNextFragment = value;
}

std::vector<std::weak_ptr<RevisionStoreChunkContainer>>
FreeChunkListFragment::fcrFreeChunks() const {
  return m_fcrFreeChunks;
}

std::vector<std::weak_ptr<RevisionStoreChunkContainer>> &
FreeChunkListFragment::getFcrFreeChunks() {
  return m_fcrFreeChunks;
}

void FreeChunkListFragment::setFcrFreeChunks(
    const std::vector<std::weak_ptr<RevisionStoreChunkContainer>> &value) {
  m_fcrFreeChunks = value;
}

quint64 FreeChunkListFragment::cb() const {
  return minSizeInFile + m_fcrFreeChunks.size() * 16;
}

RevisionStoreChunkType FreeChunkListFragment::getType() const {
  return RevisionStoreChunkType::FreeChunkListFragment;
}

} // namespace libmson
