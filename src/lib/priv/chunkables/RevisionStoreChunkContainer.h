#ifndef REVISIONSTORECHUNK_H
#define REVISIONSTORECHUNK_H

#include <QtCore/qglobal.h>

#include <memory>

#include "chunkables/Chunkable.h"

namespace libmson {
namespace priv {

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

typedef std::shared_ptr<RevisionStoreChunkContainer> RSChunkContainer_SPtr_t;
typedef std::weak_ptr<RevisionStoreChunkContainer> RSChunkContainer_WPtr_t;


} // namespace priv
} // namespace libmson

#endif // REVISIONSTORECHUNK_H
