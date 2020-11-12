#ifndef REVISIONSTOREFILEWRITER_H
#define REVISIONSTOREFILEWRITER_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <memory>

#include "RevisionStoreFile.h"
#include "chunkables/RevisionStoreChunkContainer.h"

namespace libmson {
namespace priv {

class RevisionStoreFileWriter {
private:
  std::shared_ptr<RevisionStoreFile> m_revStoreFile;

public:
  RevisionStoreFileWriter(
      std::shared_ptr<RevisionStoreFile>& revisionStoreFile);

  bool write(QDataStream& ds);

private:
  bool writeChunk(QDataStream& ds, RSChunkContainer_SPtr_t chunk);

  // Chunk writers
  bool writeRevisionStoreFileHeader(
      QDataStream& ds, RSChunkContainer_SPtr_t& fileNode);
  //  bool writeFileNode(QDataStream& ds, RSChunkContainer_SPtr_t& fileNode);
  //  bool writeFileNodeListFragment(QDataStream& ds, RSChunkContainer_SPtr_t&
  //  fileNodeListFragment); bool writeFreeChunkListFragment(QDataStream& ds,
  //  RSChunkContainer_SPtr_t freeChunklistFragment); bool
  //  writeFreeChunk(QDataStream& ds, RSChunkContainer_SPtr_t freeChunk); bool
  //  writeTransactionLogFragment(QDataStream& ds, RSChunkContainer_SPtr_t
  //  transactionLogFragment); bool writeFileDataStoreObject(QDataStream& ds,
  //  RSChunkContainer_SPtr_t fileDataStoreObject); bool
  //  writeObjectSpaceObjectPropSet(QDataStream& ds, RSChunkContainer_SPtr_t
  //  objectSpaceObjectPropSet); bool
  //  writeObjectInfoDependencyOverrideData(QDataStream& ds,
  //  RSChunkContainer_SPtr_t objectInfoDependencyOverrideData); bool
  //  writeEncryptedFragment(QDataStream& ds, RSChunkContainer_SPtr_t
  //  encryptedFragment);

  // write utilities
  quint64 stpFromChunk(RSChunkContainer_WPtr_t& chunk);

  quint64 stpTillIterator(
      const std::list<RSChunkContainer_SPtr_t>& list,
      const RSChunkContainer_WPtr_t& chunk);

  FileChunkReference64x32 getFcr64x32FromChunk(RSChunkContainer_WPtr_t& chunk);

  FileChunkReference64 getFcr64FromChunk(RSChunkContainer_WPtr_t& chunk);
};

} // namespace priv
} // namespace libmson

#endif // REVISIONSTOREFILEWRITER_H
