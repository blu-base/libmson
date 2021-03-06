#include "Chunkable.h"

#include <QDebug>

namespace libmson {
namespace priv {

bool Chunkable::isParsed() const { return m_isParsed; }

void Chunkable::setIsChanged() { m_isChanged = true; }

bool Chunkable::isChanged() const { return m_isChanged;
}

Chunkable::Chunkable(const quint64 initialStp, const quint64 initialCb)
    : m_initialStp(initialStp), m_initialCb(initialCb), m_cb(initialCb),
      m_isParsed(false), m_isChanged(false)
{
}

quint64 Chunkable::getInitialStp() const { return m_initialStp; }

quint64 Chunkable::getInitialCb() const { return m_initialCb; }

quint64 Chunkable::getSizeInFile()
{
  if (!m_isParsed) {
    return m_initialCb;
  }

  if (m_isChanged) {
    m_cb = cb();
  }

  return m_cb;
}

RevisionStoreChunkType Chunkable::type() const { return getType(); }

QString Chunkable::typeString(RevisionStoreChunkType type)
{
  switch (type) {
  case RevisionStoreChunkType::RevisionStoreFileHeader:
    return "RevisionStoreFileHeader";
  case RevisionStoreChunkType::FileNodeListFragment:
    return "FileNodeListFragment";
  case RevisionStoreChunkType::FileNode:
    return "FileNode";
  case RevisionStoreChunkType::FreeChunkListFragment:
    return "FreeChunkListFragment";
  case RevisionStoreChunkType::FreeChunk:
    return "FreeChunk";
  case RevisionStoreChunkType::TransactionLogFragment:
    return "TransactionLogFragment";
  case RevisionStoreChunkType::FileDataStoreObject:
    return "FileDataStoreObject";
  case RevisionStoreChunkType::ObjectSpaceObjectPropSet:
    return "ObjectSpaceObjectPropSet";
  case RevisionStoreChunkType::ObjectInfoDependencyOverrideData:
    return "ObjectInfoDependencyOverrideData";
  case RevisionStoreChunkType::EncryptedData:
    return "EncryptedData";
  case RevisionStoreChunkType::OrphanedAllocation:
    return "OrphanedAllocation";
  case RevisionStoreChunkType::Invalid:
    return "Invalid";
  }

  return "UndefinedType";
}


} // namespace priv
} // namespace libmson
