#include "RevisionStoreChunk.h"

#include "chunks/FreeChunkListFragment.h"
#include "chunks/RevisionStoreFileHeader.h"

namespace libmson {

RevisionStoreChunkContainer::RevisionStoreChunkContainer(std::shared_ptr<Chunkable> chunkable,
                                       const quint64 initialLocationInFile, const quint64 initialCb)
    : m_initialStp(initialLocationInFile), m_initialCb(initialCb), m_chunkable(chunkable) {

  switch (chunkable->getType()) {

  case RevisionStoreChunkType::RevistionStoreFileHeader:
    m_chunkable = std::make_shared<RevisionStoreFileHeader>();
    break;
  case RevisionStoreChunkType::FileNodeListFragment:
    break;
  case RevisionStoreChunkType::FileNode:
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

std::shared_ptr<Chunkable> RevisionStoreChunkContainer::getContent()
{
  return m_chunkable;
}

RevisionStoreChunkType RevisionStoreChunkContainer::getType()
{
  return m_chunkable->getType();
}

quint64 RevisionStoreChunkContainer::getInitialStp() const
{
  return m_initialStp;
}

quint64 RevisionStoreChunkContainer::getInitialCb() const
{
  return m_initialCb;
}


} // namespace libmson
