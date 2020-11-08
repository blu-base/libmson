#include "FileNodeListFragment.h"
#include <numeric>

namespace libmson {
namespace priv {

FileNodeListFragment::FileNodeListFragment() : m_fileNodeListID(), m_nFragmentSequence(0), m_paddingLength(0) {}

std::list<std::shared_ptr<RevisionStoreChunkContainer>>& FileNodeListFragment::fileNodes() { return m_fileNodes; }

std::list<std::shared_ptr<RevisionStoreChunkContainer>> FileNodeListFragment::getFileNodes() const
{
  return m_fileNodes;
}

void FileNodeListFragment::setFileNodes(const std::list<std::shared_ptr<RevisionStoreChunkContainer>>& fileNodes)
{
  m_fileNodes = fileNodes;
}

RSChunkContainer_WPtr_t FileNodeListFragment::getNextFragment() { return m_nextFragment; }

void FileNodeListFragment::setNextFragment(RSChunkContainer_WPtr_t chunk) { m_nextFragment = chunk; }

quint64 FileNodeListFragment::cb() const
{
  if (m_fileNodes.empty()) {
    if (!m_nextFragment.expired()) {
      // if there is a next Fragment, this fragment needs to be terminated with
      // ChunkTerminator fileNode
      return minSizeInFile + 4;
    }
    return minSizeInFile;
  }
  else {

    auto addCb = [](quint64 a, std::shared_ptr<RevisionStoreChunkContainer> b) { return std::move(a) + b->cb(); };

    return minSizeInFile + m_paddingLength + std::accumulate(m_fileNodes.begin(), m_fileNodes.end(), 0, addCb);
  }
}

RevisionStoreChunkType FileNodeListFragment::getType() const { return RevisionStoreChunkType::FileNodeListFragment; }

} // namespace priv
} // namespace libmson
