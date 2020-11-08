#include "RevisionStoreFileWriter.h"


#include "chunkables/FileNode.h"
#include "chunkables/FileNodeListFragment.h"
#include "chunkables/FreeChunk.h"
#include "chunkables/FreeChunkListFragment.h"
#include "chunkables/RevisionStoreFileHeader.h"

#include "utils/CrcAlgorithms.h"


namespace libmson {
namespace priv {


RevisionStoreFileWriter::RevisionStoreFileWriter(std::shared_ptr<RevisionStoreFile>& revisionStoreFile)
    : m_revStoreFile(revisionStoreFile)
{
}

bool RevisionStoreFileWriter::write(QDataStream& ds)
{
  auto chunks = m_revStoreFile->chunks();

  auto it = chunks.begin();


  // write header
  if (!writeRevisionStoreFileHeader(ds, *it)) {
    return false;
  }
  it++;

  // then write the rest
  for (; it != chunks.end(); ++it) {
    if (!writeChunk(ds, *it)) {
      return false;
    }
  }

  return true;
}

bool RevisionStoreFileWriter::writeChunk(QDataStream& ds, RSChunkContainer_SPtr_t chunk)
{
  switch (chunk->getType()) {

  case RevisionStoreChunkType::RevistionStoreFileHeader:
    qWarning("Trying to write another header mid-stream");
    break;
  case RevisionStoreChunkType::FileNodeListFragment:
    return writeFileNodeListFragment(ds, chunk);
  case RevisionStoreChunkType::FileNode:
    return writeFileNode(ds, chunk);
  case RevisionStoreChunkType::FreeChunkListFragment:
    return writeFreeChunkListFragment(ds, chunk);
  case RevisionStoreChunkType::FreeChunk:
    return writeFreeChunk(ds, chunk);
  case RevisionStoreChunkType::TransactionLogFragment:
    break;
  case RevisionStoreChunkType::FileDataStoreObject:
    break;
  case RevisionStoreChunkType::ObjectSpaceObjectPropSet:
    break;
  case RevisionStoreChunkType::ObjectInfoDependencyOverrideData:
    break;
  case RevisionStoreChunkType::EncryptedFragment:
    break;
  case RevisionStoreChunkType::Invalid:
  default:
    qFatal("Failed to initialize invalid RevisionStoreChunkType.");
  }

  return true;
}

quint64 RevisionStoreFileWriter::stpFromChunk(RSChunkContainer_WPtr_t& chunk)
{
  if (chunk.expired()) {
    return UINT64_MAX;
  }
  else {
    auto lchunk = chunk.lock();

    // if chunk is a FileNode, we must first sum up to the parent
    // FileNodeListFragment
    if (lchunk->getType() == RevisionStoreChunkType::FileNode) {
      quint64 stp                    = 0;
      auto fileNodeListFragmentChunk = std::static_pointer_cast<FileNode>(lchunk->getContent())->getParent();

      quint64 subtotal = stpTillIterator(m_revStoreFile->chunks(), fileNodeListFragmentChunk);

      // now summing up within the FileNodeListFragment
      stp += FileNodeListFragment::headerSize;

      subtotal += stpTillIterator(
          std::static_pointer_cast<FileNodeListFragment>(fileNodeListFragmentChunk.lock()->getContent())
              ->getFileNodes(),
          lchunk);

      if (subtotal != UINT64_MAX) {
        return stp + subtotal;
      }
      else {
        return UINT64_MAX;
      }
    }
    else {
      return stpTillIterator(m_revStoreFile->chunks(), chunk);
    }
  }
}

quint64 RevisionStoreFileWriter::stpTillIterator(
    const std::list<std::shared_ptr<RevisionStoreChunkContainer>>& list, const RSChunkContainer_WPtr_t& chunk)
{
  if (chunk.expired()) {
    return UINT64_MAX;
  }
  else {
    auto lchunk = chunk.lock();

    auto it = std::find(list.begin(), list.end(), lchunk);

    auto addCb = [](quint64 a, std::shared_ptr<RevisionStoreChunkContainer> b) { return std::move(a) + b->cb(); };

    return std::accumulate(list.begin(), it, 0, addCb);
  }
}

FileChunkReference64x32 RevisionStoreFileWriter::getFcr64x32FromChunk(RSChunkContainer_WPtr_t& chunk)
{
  if (chunk.expired()) {
    return FileChunkReference64x32(FCR_INIT::NIL);
  }
  else {
    auto lchunk = chunk.lock();
    quint64 stp = stpFromChunk(chunk);
    return FileChunkReference64x32(stp, lchunk->cb());
  }
}

FileChunkReference64 RevisionStoreFileWriter::getFcr64FromChunk(RSChunkContainer_WPtr_t& chunk)
{
  if (chunk.expired()) {
    return FileChunkReference64(FCR_INIT::NIL);
  }
  else {
    auto lchunk = chunk.lock();
    quint64 stp = stpFromChunk(chunk);
    return FileChunkReference64(stp, lchunk->cb());
  }
}

} // namespace priv
} // namespace libmson
