#ifndef FILENODELISTFRAGMENTHEADER_H
#define FILENODELISTFRAGMENTHEADER_H

#include "Chunkable.h"
#include <QtCore/qglobal.h>
#include <list>

#include "Chunkable.h"
#include "FileNode.h"

namespace libmson {
namespace priv {

class FileNodeListFragment;
typedef std::shared_ptr<FileNodeListFragment> FileNodeListFragment_SPtr_t;
typedef std::weak_ptr<FileNodeListFragment> FileNodeListFragment_WPtr_t;

class FileNodeListFragment : public Chunkable {
private:
  quint32 m_fileNodeListID;
  quint32 m_nFragmentSequence;

  std::list<FileNode_SPtr_t> m_fileNodes;

  quint64 m_paddingLength;
  FileNodeListFragment_WPtr_t m_nextFragment;

public:
  FileNodeListFragment(
      const quint64 initialStp = 0, const quint64 initialCb = 0);

  std::list<FileNode_SPtr_t>& fileNodes();
  std::list<FileNode_SPtr_t> getFileNodes() const;

  void setFileNodes(const std::list<FileNode_SPtr_t>& fileNodes);

  FileNodeListFragment_WPtr_t getNextFragment();
  void setNextFragment(FileNodeListFragment_WPtr_t chunk);


  static const quint32 minSizeInFile = 36;
  static const quint32 headerSize    = 16;

  friend class RevisionStoreFileWriter;
  friend class RevisionStoreFileParser;

private:
  // Chunkable interface
  virtual quint64 cb() const override;
  virtual RevisionStoreChunkType getType() const override;

  static constexpr const quint64 header_magic_id = 0xA4567AB1F5F7F4C4;
  static constexpr const quint64 footer_magic_id = 0x8BC215C38233BA4B;

  // member functions
};


} // namespace priv
} // namespace libmson

#endif // FILENODELISTFRAGMENTHEADER_H
