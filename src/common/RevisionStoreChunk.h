#ifndef REVISIONSTORECHUNK2_H
#define REVISIONSTORECHUNK2_H

#include <QtCore/qglobal.h>

#include <memory>

#include "chunks/Chunkable.h"
#include "RevisionStoreFile2.h"

namespace libmson {

class RevisionStoreChunk {
private:
  qint64 m_initialStp;

  std::shared_ptr<Chunkable> m_chunkable;

public:
  RevisionStoreChunk(std::shared_ptr<Chunkable> chunkable,
                     const quint64 initialLocationInFile);

  std::shared_ptr<Chunkable> getChunk();

  RevisionStoreChunkType getType();

  quint64 getInitialStp() const;

  quint64 cb() { return m_chunkable->cb(); };
};

} // namespace libmson

#endif // REVISIONSTORECHUNK2_H
