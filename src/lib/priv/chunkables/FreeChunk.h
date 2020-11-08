#ifndef FREECHUNK_H
#define FREECHUNK_H

#include "Chunkable.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

/// This chunk represents an empty section of given size within the
/// RevisionStoreFile
class FreeChunk : public Chunkable {
  friend class RevisionStoreFile;

private:
  quint64 m_size;

public:
  FreeChunk(const quint64 size = 0);

  void setSize(const quint64 size);

  // Chunkable interface
  virtual quint64 cb() const override;
  virtual RevisionStoreChunkType getType() const override;
};

} // namespace priv
} // namespace libmson

#endif // FREECHUNK_H
