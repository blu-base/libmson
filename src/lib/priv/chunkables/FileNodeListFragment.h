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

  quint16 m_paddingLength;
  FileNodeListFragment_WPtr_t m_nextFragment;

  QByteArray m_dormant;

public:
  FileNodeListFragment(
      const quint64 initialStp = 0, const quint64 initialCb = 0);

  quint32 getFileNodeListID() const;
  void setFileNodeListID(const quint32& fileNodeListID);

  quint32 getNFragmentSequence() const;
  void setNFragmentSequence(const quint32& nFragmentSequence);

  std::list<FileNode_SPtr_t>& fileNodes();
  std::list<FileNode_SPtr_t> getFileNodes() const;

  void setFileNodes(const std::list<FileNode_SPtr_t>& fileNodes);

  FileNodeListFragment_WPtr_t getNextFragment();
  void setNextFragment(FileNodeListFragment_WPtr_t chunk);

  quint16 getPaddingLength() const;
  void setPaddingLength(const quint16& paddingLength);

  static const quint32 headerSize              = 16;
  static const quint32 footerSize              = 20;
  static const constexpr quint32 minSizeInFile = headerSize + footerSize;

  static constexpr const quint64 header_magic_id = 0xA4567AB1F5F7F4C4;
  static constexpr const quint64 footer_magic_id = 0x8BC215C38233BA4B;

  friend class RevisionStoreFileParser;


private:
  // Chunkable interface
  virtual quint64 cb() const override;
  virtual RevisionStoreChunkType getType() const override;


  // member functions
};


} // namespace priv
} // namespace libmson

#endif // FILENODELISTFRAGMENTHEADER_H
