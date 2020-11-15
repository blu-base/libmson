#ifndef FREECHUNK_H
#define FREECHUNK_H

#include "Chunkable.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

/// This chunk represents an empty section of given size within the
/// RevisionStoreFile
class FreeChunk : public Chunkable {
private:
  quint64 m_size;

public:
  FreeChunk(
      const quint64 size, const quint64 initialStp = 0,
      const quint64 initialCb = 0);

  quint64 getSize() const;
  void setSize(const quint64& size);

  friend class RevisionStoreFileWriter;
  friend class RevisionStoreFileParser;


private:
  // Chunkable interface
  virtual quint64 cb() const override;
  virtual RevisionStoreChunkType getType() const override;
};

typedef std::shared_ptr<FreeChunk> FreeChunk_SPtr_t;
typedef std::weak_ptr<FreeChunk> FreeChunk_WPtr_t;

} // namespace priv
} // namespace libmson

#endif // FREECHUNK_H
