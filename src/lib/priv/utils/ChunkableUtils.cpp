#include "ChunkableUtils.h"

#include "../RevisionStoreFile.h"
#include "../commonTypes/FileChunkReference64.h"
#include "../commonTypes/FileChunkReference64x32.h"
#include "../commonTypes/FileNodeChunkReference.h"

namespace libmson {
namespace priv {

template <typename Chunkably>
std::vector<Chunkable_SPtr_t>
castToChunkable(std::vector<std::shared_ptr<Chunkably>> vec)
{
  return std::transform(
      vec.begin(), vec.end(), vec.begin(), [](Chunkably c) -> Chunkable_SPtr_t {
        return std::static_pointer_cast<Chunkable>(c);
      });
}


template <typename Chunkably>
std::list<Chunkable_SPtr_t>
castToChunkable(std::list<std::shared_ptr<Chunkably>> vec)
{
  return std::transform(
      vec.begin(), vec.end(), vec.begin(), [](Chunkably c) -> Chunkable_SPtr_t {
        return std::static_pointer_cast<Chunkable>(c);
      });
}


quint64
stpFromChunk(RevisionStoreFile_SPtr_t revStoreFile, Chunkable_WPtr_t chunk)
{
  if (chunk.expired()) {
    return UINT64_MAX;
  }
  else {
    auto lchunk = chunk.lock();

    // if chunk is a FileNode, we must first sum up to the parent
    // FileNodeListFragment
    if (lchunk->type() == RevisionStoreChunkType::FileNode) {
      quint64 stp = 0;
      auto fileNodeListFragmentChunk =
          std::static_pointer_cast<FileNode>(lchunk)->getParent().lock();

      quint64 subtotal =
          stpTillIterator(revStoreFile->chunks(), fileNodeListFragmentChunk);

      // now summing up within the FileNodeListFragment
      stp += FileNodeListFragment::headerSize;


      auto fileNodes = fileNodeListFragmentChunk->getFileNodes();

      subtotal += stpTillIterator(fileNodes, lchunk);

      if (subtotal != UINT64_MAX) {
        return stp + subtotal;
      }
      else {
        return UINT64_MAX;
      }
    }
    else {
      return stpTillIterator(revStoreFile->chunks(), chunk);
    }
  }
}

template <typename Chunkably_SPtr_t>
quint64
stpTillIterator(std::list<Chunkably_SPtr_t>& list, Chunkable_WPtr_t chunk)
{
  if (chunk.expired()) {
    return UINT64_MAX;
  }
  else {
    auto lchunk = chunk.lock();

    auto it = std::find(list.begin(), list.end(), lchunk);

    auto addCb = [](quint64 a, Chunkably_SPtr_t b) {
      return std::move(a) + b->getSizeInFile();
    };

    return std::accumulate(
        list.begin(), it, RevisionStoreFileHeader::sizeInFile, addCb);
  }
}

FileChunkReference64x32 getFcr64x32FromChunk(
    RevisionStoreFile_SPtr_t revStoreFile, Chunkable_WPtr_t chunk,
    FCR_INIT preferedState = FCR_INIT::NIL)
{
  if (chunk.expired()) {
    return FileChunkReference64x32(preferedState);
  }
  else {
    auto lchunk = chunk.lock();
    quint64 stp = stpFromChunk(revStoreFile, chunk);
    return FileChunkReference64x32(stp, lchunk->getSizeInFile());
  }
}

FileChunkReference64 getFcr64FromChunk(
    RevisionStoreFile_SPtr_t revStoreFile, Chunkable_WPtr_t chunk,
    FCR_INIT preferedState = FCR_INIT::NIL)
{
  if (chunk.expired()) {
    return FileChunkReference64(preferedState);
  }
  else {
    auto lchunk = chunk.lock();
    quint64 stp = stpFromChunk(revStoreFile, chunk);
    return FileChunkReference64(stp, lchunk->getSizeInFile());
  }
}

FileNodeChunkReference getFncrFromChunk(
    RevisionStoreFile_SPtr_t revStoreFile, Chunkable_WPtr_t chunk,
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat,
    FCR_INIT preferedState = FCR_INIT::NIL)
{
  if (chunk.expired()) {
    return FileNodeChunkReference(
        FNCR_STP_FORMAT::UNCOMPRESED_8BYTE, FNCR_CB_FORMAT::UNCOMPRESED_4BYTE,
        preferedState);
  }
  else {
    auto lchunk = chunk.lock();

    FileNodeChunkReference fncr(stpFormat, cbFormat, preferedState);

    fncr.setStp(stpFromChunk(revStoreFile, lchunk));
    fncr.setCb(lchunk->getSizeInFile());


    return fncr;
  }
}


} // namespace priv
} // namespace libmson
