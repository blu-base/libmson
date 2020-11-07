#ifndef FILENODELISTFRAGMENTHEADER_H
#define FILENODELISTFRAGMENTHEADER_H

#include "Chunkable.h"
#include <QtCore/qglobal.h>
#include <list>
#include <memory>

#include "../RevisionStoreChunk.h"

namespace libmson {

class FileNodeListFragment : public Chunkable {
private:
  quint32 m_fileNodeListID;
  quint32 m_nFragmentSequence;

  std::list<std::shared_ptr<RevisionStoreChunkContainer>> m_fileNodes;

  quint64 m_paddingLength;
  std::weak_ptr<RevisionStoreChunkContainer> m_nextFragment;

public:
  FileNodeListFragment();

  std::list<std::shared_ptr<RevisionStoreChunkContainer>> fileNodes() const;
  std::list<std::shared_ptr<RevisionStoreChunkContainer>> &getFileNodes();

  void
  setFileNodes(const std::list<std::shared_ptr<RevisionStoreChunkContainer>> &fileNodes);

  std::weak_ptr<RevisionStoreChunkContainer> getNextFragment();
  void setNextFragment(std::weak_ptr<RevisionStoreChunkContainer> chunk);

  // Chunkable interface
  virtual quint64 cb() const override;
  virtual RevisionStoreChunkType getType() const override;

  friend class RevisionStoreFile;

private:
  static constexpr const quint64 header_magic_id = 0xA4567AB1F5F7F4C4;
  static constexpr const quint64 footer_magic_id = 0x8BC215C38233BA4B;

  // member functions
  static const quint32 minSizeInFile = 36;
  static const quint32 headerSize = 16;
};

} // namespace libmson

#endif // FILENODELISTFRAGMENTHEADER_H
