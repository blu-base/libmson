#include "FreeChunkListFragment.h"

namespace libmson {
namespace priv {

FreeChunkListFragment::FreeChunkListFragment(
    const quint64 initialStp, const quint64 initialCb)
    : Chunkable(initialStp, initialCb), m_crc()
{
}

quint32 FreeChunkListFragment::getCrc() const { return m_crc; }

void FreeChunkListFragment::setCrc(const quint32 value) { m_crc = value; }

FreeChunkListFragment_WPtr_t FreeChunkListFragment::getFcrNextFragment()
{
  return m_fcrNextFragment;
}

void FreeChunkListFragment::setFcrNextFragment(
    FreeChunkListFragment_WPtr_t value)
{
  m_fcrNextFragment = value;
}

std::vector<FreeChunk_WPtr_t> FreeChunkListFragment::fcrFreeChunks() const
{
  return m_fcrFreeChunks;
}

std::vector<FreeChunk_WPtr_t>& FreeChunkListFragment::getFcrFreeChunks()
{
  return m_fcrFreeChunks;
}

void FreeChunkListFragment::setFcrFreeChunks(
    const std::vector<FreeChunk_WPtr_t>& value)
{
  m_fcrFreeChunks = value;
}

quint64 FreeChunkListFragment::cb() const
{
  return minSizeInFile + m_fcrFreeChunks.size() * 16;
}

RevisionStoreChunkType FreeChunkListFragment::getType() const
{
  return RevisionStoreChunkType::FreeChunkListFragment;
}

} // namespace priv
} // namespace libmson
