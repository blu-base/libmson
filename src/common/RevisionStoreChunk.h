#ifndef REVISIONSTORECHUNK2_H
#define REVISIONSTORECHUNK2_H

#include <QtCore/qglobal.h>

#include <memory>

#include "chunks/Chunkable.h"
#include "RevisionStoreFile2.h"

namespace libmson {

class RevisionStoreChunkContainer {
private:
  const quint64 m_initialStp;
  const quint64 m_initialCb;

  std::shared_ptr<Chunkable> m_chunkable;

public:
  RevisionStoreChunkContainer(std::shared_ptr<Chunkable> chunkable,
                     const quint64 initialLocationInFile, const quint64 initialCb);

  std::shared_ptr<Chunkable> getContent();

  RevisionStoreChunkType getType();

  quint64 getInitialStp() const;
  quint64 getInitialCb() const;

  quint64 cb() { return m_chunkable->cb(); };
};

} // namespace libmson

#endif // REVISIONSTORECHUNK2_H
