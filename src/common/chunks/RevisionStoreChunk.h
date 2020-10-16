#ifndef REVISIONSTORECHUNK_H
#define REVISIONSTORECHUNK_H

#include <QtCore/qglobal.h>

#include <memory>

class Chunkable;
class RevisionStoreFile;

namespace libmson {

enum class RevisionStoreChunkType {

};

class RevisionStoreChunk {
private:
  qint64 m_initialStp;

  std::shared_ptr<Chunkable> m_chunkable;

  std::weak_ptr<RevisionStoreFile> m_parent;

public:
  RevisionStoreChunk(std::shared_ptr<Chunkable> chunkable,
                     const RevisionStoreChunkType chunktype,
                     const qint64 initialLocationInFile,
                     std::weak_ptr<RevisionStoreFile> parent);

  std::shared_ptr<Chunkable> getChunk();

  RevisionStoreChunkType getType();

  qint64 stp();
  qint64 size();
};

} // namespace libmson

#endif // REVISIONSTORECHUNK_H
