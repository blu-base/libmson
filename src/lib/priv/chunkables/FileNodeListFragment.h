#ifndef FILENODELISTFRAGMENTHEADER_H
#define FILENODELISTFRAGMENTHEADER_H

#include "Chunkable.h"
#include <QtCore/qglobal.h>
#include <list>
#include <memory>

#include "RevisionStoreChunkContainer.h"

namespace libmson {
namespace priv {

class FileNodeListFragment : public Chunkable {
private:
  quint32 m_fileNodeListID;
  quint32 m_nFragmentSequence;

  std::list<RSChunkContainer_SPtr_t> m_fileNodes;

  quint64 m_paddingLength;
  std::weak_ptr<RevisionStoreChunkContainer> m_nextFragment;

public:
  FileNodeListFragment();

  std::list<RSChunkContainer_SPtr_t>& fileNodes();
  std::list<RSChunkContainer_SPtr_t> getFileNodes() const;

  void setFileNodes(const std::list<RSChunkContainer_SPtr_t>& fileNodes);

  RSChunkContainer_WPtr_t getNextFragment();
  void setNextFragment(RSChunkContainer_WPtr_t chunk);

  // Chunkable interface
  virtual quint64 cb() const override;
  virtual RevisionStoreChunkType getType() const override;

  static const quint32 minSizeInFile = 36;
  static const quint32 headerSize    = 16;

  friend class RevisionStoreFileWriter;
  friend class RevisionStoreFileParser;

private:
  static constexpr const quint64 header_magic_id = 0xA4567AB1F5F7F4C4;
  static constexpr const quint64 footer_magic_id = 0x8BC215C38233BA4B;

  // member functions
};

} // namespace priv
} // namespace libmson

#endif // FILENODELISTFRAGMENTHEADER_H
