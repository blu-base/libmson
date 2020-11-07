#ifndef CHUNKABLE_H
#define CHUNKABLE_H

#include <QtCore/qglobal.h>

namespace libmson {

enum class RevisionStoreChunkType {
  RevistionStoreFileHeader,
  FileNodeListFragment,
  FileNode,
  FreeChunkListFragment,
  FreeChunk,
  TransactionLogFragment,
  FileDataStoreObject,
  ObjectSpaceObjectPropSet,
  ObjectInfoDependencyOverrideData,
  EncryptedFragment,

  Invalid
};

class Chunkable {
public:
  virtual quint64 cb() const = 0;
  virtual RevisionStoreChunkType getType() const = 0;
};

} // namespace libmson

#endif // CHUNKABLE_H
