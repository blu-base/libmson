#include "FileNodeListFragment.h"
#include <numeric>

namespace libmson {
namespace priv {


FileNodeListFragment::FileNodeListFragment(
    const quint64 initialStp, const quint64 initialCb)
    : Chunkable(initialStp, initialCb), m_fileNodeListID(),
      m_nFragmentSequence(0), m_paddingLength(0)
{
}

quint32 FileNodeListFragment::getFileNodeListID() const
{
  return m_fileNodeListID;
}

void FileNodeListFragment::setFileNodeListID(const quint32& fileNodeListID)
{
  m_isChanged      = true;
  m_fileNodeListID = fileNodeListID;
}

quint32 FileNodeListFragment::getNFragmentSequence() const
{
  return m_nFragmentSequence;
}

void FileNodeListFragment::setNFragmentSequence(
    const quint32& nFragmentSequence)
{
  m_isChanged         = true;
  m_nFragmentSequence = nFragmentSequence;
}


std::list<FileNode_SPtr_t>& FileNodeListFragment::fileNodes()
{
  m_isChanged = true;
  return m_fileNodes;
}

std::list<FileNode_SPtr_t> FileNodeListFragment::getFileNodes() const
{
  return m_fileNodes;
}

void FileNodeListFragment::setFileNodes(
    const std::list<FileNode_SPtr_t>& fileNodes)
{
  m_isChanged = true;
  m_fileNodes = fileNodes;
}

quint16 FileNodeListFragment::getPaddingLength() const
{
  return m_paddingLength;
}

void FileNodeListFragment::setPaddingLength(const quint16& paddingLength)
{
  m_isChanged     = true;
  m_paddingLength = paddingLength;
}


FileNodeListFragment_WPtr_t FileNodeListFragment::getNextFragment()
{
  return m_nextFragment;
}

void FileNodeListFragment::setNextFragment(FileNodeListFragment_WPtr_t chunk)
{
  m_isChanged    = true;
  m_nextFragment = chunk;
}

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

    auto addCb = [](quint64 a, const FileNode_SPtr_t& b) {
      return std::move(a) + b->getSizeInFile();
    };

    return minSizeInFile + m_paddingLength +
           std::accumulate(m_fileNodes.begin(), m_fileNodes.end(), 0, addCb);
  }
}

RevisionStoreChunkType FileNodeListFragment::getType() const
{
  return RevisionStoreChunkType::FileNodeListFragment;
}

} // namespace priv
} // namespace libmson
