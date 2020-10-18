#include "RevisionStoreChunk.h"

#include "chunks/FreeChunkListFragment.h"
#include "chunks/RevisionStoreFileHeader.h"

namespace libmson {

RevisionStoreChunk::RevisionStoreChunk(std::shared_ptr<Chunkable> chunkable,
                                       const quint64 initialLocationInFile)
    : m_initialStp(initialLocationInFile), m_chunkable(chunkable) {

  switch (chunkable->getType()) {

  case RevisionStoreChunkType::RevistionStoreFileHeader:
    m_chunkable = std::make_shared<RevisionStoreFileHeader>();
    break;
  case RevisionStoreChunkType::FileNodeListFragmentHeader:
    break;
  case RevisionStoreChunkType::FileNode:
    break;
  case RevisionStoreChunkType::FileNodeListFragmentFooter:
    break;
  case RevisionStoreChunkType::FreeChunkListFragment:
    m_chunkable = std::make_shared<FreeChunkListFragment>();
    break;
  case RevisionStoreChunkType::FreeChunk:
    break;
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
}

std::shared_ptr<Chunkable> RevisionStoreChunk::getChunk()
{
  return m_chunkable;
}

RevisionStoreChunkType RevisionStoreChunk::getType()
{
  return m_chunkable->getType();
}

quint64 RevisionStoreChunk::getInitialStp() const
{
  return m_initialStp;
}


} // namespace libmson
