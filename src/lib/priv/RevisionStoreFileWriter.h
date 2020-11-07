#ifndef REVISIONSTOREFILEWRITER_H
#define REVISIONSTOREFILEWRITER_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <memory>

#include "common/RevisionStoreChunk.h"
#include "common/RevisionStoreFile2.h"

namespace libmson {

namespace priv {

typedef std::shared_ptr<RevisionStoreChunkContainer> RSChunkContainer_SharedPtr_t;

class RevisionStoreFileWriter {
public:
  RevisionStoreFileWriter( QDataStream& outputStream, RevisionStoreFile& revisionStoreFile );


private:
  bool writeChunk( RSChunkContainer_SharedPtr_t chunk );

  // Chunk writers
  bool writeRevisionStoreFileHeader();
  bool writeFileNode( RSChunkContainer_SharedPtr_t& fileNode );
  bool writeFileNodeListFragment( RSChunkContainer_SharedPtr_t& fileNodeListFragment );
  bool writeFreeChunkListFragment( RSChunkContainer_SharedPtr_t freeChunklistFragment );
  bool writeFreeChunk( RSChunkContainer_SharedPtr_t freeChunk );
  bool writeTransactionLogFragment( RSChunkContainer_SharedPtr_t transactionLogFragment );
  bool writeFileDataStoreObject( RSChunkContainer_SharedPtr_t fileDataStoreObject );
  bool writeObjectSpaceObjectPropSet( RSChunkContainer_SharedPtr_t objectSpaceObjectPropSet );
  bool writeObjectInfoDependencyOverrideData( RSChunkContainer_SharedPtr_t objectInfoDependencyOverrideData );
  bool writeEncryptedFragment( RSChunkContainer_SharedPtr_t encryptedFragment );


  // write utilities
  quint64 stpFromChunk( RSChunkContainer_SharedPtr_t chunk );


  quint64
  stpTillIterator( const std::list<RSChunkContainer_SharedPtr_t>& list, const RSChunkContainer_SharedPtr_t& chunk );

  MSONcommon::FileChunkReference64x32 getFcr64x32FromChunk( RSChunkContainer_SharedPtr_t chunk );

  MSONcommon::FileChunkReference64 getFcr64FromChunk( RSChunkContainer_SharedPtr_t chunk );
};

} // namespace priv
} // namespace libmson

#endif // REVISIONSTOREFILEWRITER_H
