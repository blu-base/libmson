#ifndef FREECHUNKLISTFRAGMENT_H
#define FREECHUNKLISTFRAGMENT_H

#include <QtCore/qglobal.h>

#include <memory>

#include "Chunkable.h"
#include "FreeChunk.h"

namespace libmson {
namespace priv {

class FreeChunkListFragment;

typedef std::shared_ptr<FreeChunkListFragment> FreeChunkListFragment_SPtr_t;
typedef std::weak_ptr<FreeChunkListFragment> FreeChunkListFragment_WPtr_t;

class FreeChunkListFragment : public Chunkable {
private:
  quint32 m_crc;

  FreeChunkListFragment_WPtr_t m_fcrNextFragment;

  std::vector<FreeChunk_WPtr_t> m_fcrFreeChunks;

  static const qint64 minSizeInFile = 16;

public:
  FreeChunkListFragment(
      const quint64 initialStp = 0, const quint64 initialCb = 0);

  quint32 getCrc() const;
  void setCrc(const quint32 value);

  FreeChunkListFragment_WPtr_t getFcrNextFragment();
  void setFcrNextFragment(FreeChunkListFragment_WPtr_t value);

  std::vector<FreeChunk_WPtr_t> getFcrFreeChunks() const;
  std::vector<FreeChunk_WPtr_t>& fcrFreeChunks();
  void setFcrFreeChunks(const std::vector<FreeChunk_WPtr_t>& value);


  friend class RevisionStoreFileWriter;
  friend class RevisionStoreFileParser;

private:
  // Chunkable interface
  virtual quint64 cb() const override;
  virtual RevisionStoreChunkType getType() const override;
};


} // namespace priv
} // namespace libmson

#endif // FREECHUNKLISTFRAGMENT_H
