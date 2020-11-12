#ifndef FREECHUNKLISTFRAGMENT_H
#define FREECHUNKLISTFRAGMENT_H

#include <QtCore/qglobal.h>

#include <memory>

#include "Chunkable.h"
#include "RevisionStoreChunkContainer.h"

namespace libmson {
namespace priv {

class FreeChunkListFragment : public Chunkable {
private:
  quint32 m_crc;

  std::weak_ptr<RevisionStoreChunkContainer> m_fcrNextFragment;

  std::vector<std::weak_ptr<RevisionStoreChunkContainer>> m_fcrFreeChunks;

  static const qint64 minSizeInFile = 16;

public:
  FreeChunkListFragment();
  FreeChunkListFragment(const quint64 size);

  quint32 getCrc() const;
  void setCrc(const quint32 value);

  std::weak_ptr<RevisionStoreChunkContainer> getFcrNextFragment();
  void setFcrNextFragment(std::weak_ptr<RevisionStoreChunkContainer> value);

  std::vector<std::weak_ptr<RevisionStoreChunkContainer>> fcrFreeChunks() const;
  std::vector<std::weak_ptr<RevisionStoreChunkContainer>>& getFcrFreeChunks();
  void setFcrFreeChunks(
      const std::vector<std::weak_ptr<RevisionStoreChunkContainer>>& value);

  // Chunkable interface
  virtual quint64 cb() const override;
  virtual RevisionStoreChunkType getType() const override;

  friend class RevisionStoreFileWriter;
  friend class RevisionStoreFileParser;
};

} // namespace priv
} // namespace libmson

#endif // FREECHUNKLISTFRAGMENT_H
