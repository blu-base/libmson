#ifndef REVISIONSTOREFILEWRITER_H
#define REVISIONSTOREFILEWRITER_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <memory>

#include "RevisionStoreFile.h"
#include "chunkables/Chunkable.h"

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
  bool writeChunk(QDataStream& ds, Chunkable_SPtr_t chunk);


  // Chunk writers
  bool writeEncryptedData(QDataStream& ds, EncryptedData_SPtr_t encryptedData);

  bool writeFileDataStoreObject(
      QDataStream& ds, FileDataStoreObject_SPtr_t fileDataStoreObject);

  bool writeFileNode(QDataStream& ds, FileNode_SPtr_t& fileNode);

  bool writeFileNodeListFragment(
      QDataStream& ds, FileNodeListFragment_SPtr_t& fileNodeListFragment);

  bool writeFreeChunk(QDataStream& ds, FreeChunk_SPtr_t freeChunk);

  bool writeFreeChunkListFragment(
      QDataStream& ds, FreeChunkListFragment_SPtr_t freeChunklistFragment);

  bool writeObjectSpaceObjectPropSet(
      QDataStream& ds, ObjectSpaceObjectPropSet_SPtr_t propSet);

  bool writeObjectSpaceObjectPropSetUnpadded(
      QDataStream& ds, ObjectSpaceObjectPropSet_SPtr_t propSet);

  bool writeObjectInfoDependencyOverrideData(
      QDataStream& ds, ObjectInfoDependencyOverrideData_SPtr_t data);

  bool writeRevisionStoreFileHeader(
      QDataStream& ds, RevisionStoreFileHeader_SPtr_t header);

  bool writeTransactionLogFragment(
      QDataStream& ds, TransactionLogFragment_SPtr_t transactionLogFragment);

  bool writeUnknownBlob(QDataStream& ds, UnknownBlob_SPtr_t unknownBlob);

  bool writeUnparsedChunk(QDataStream& ds, Chunkable_SPtr_t chunk);


  // write utilities


  /// utility function, which recomputes the sentinal entries' crc sums
  /// \todo crc computing should be in RevisionStoreFile, when ever a new
  /// transaction is added
  void computeTransactionEntryCRCs();
};

} // namespace priv
} // namespace libmson

#endif // REVISIONSTOREFILEWRITER_H
