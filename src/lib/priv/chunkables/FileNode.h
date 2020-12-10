#ifndef FILENODE_H
#define FILENODE_H

#include "../commonTypes/FileNodeChunkReference.h" // needed to pass FNCR_STP/CB_FORMAT
#include "Chunkable.h"
#include <QtCore/qglobal.h>


#include "fileNodeTypes/FileNodeTypeIDs.h"

namespace libmson {
namespace priv {

class FileNode;

typedef std::shared_ptr<FileNode> FileNode_SPtr_t;
typedef std::weak_ptr<FileNode> FileNode_WPtr_t;

class FileNodeListFragment;


class IFileNodeType;


class FileNode : public Chunkable {

private:
  std::weak_ptr<FileNodeListFragment> m_parent;

  quint16 fileNodeID;

  quint8 stpFormat;
  quint8 cbFormat;

  quint8 baseType;

  //  quint8 reserved;

  std::shared_ptr<IFileNodeType> fnt;


public:
  FileNode(
      std::weak_ptr<FileNodeListFragment> parent, const quint64 initialStp = 0,
      const quint64 initialCb = 0);

  quint16 getFileNodeID() const;
  void setFileNodeID(const quint16& value);
  FileNodeTypeID getFileNodeTypeID() const;

  quint16 getFileNodeSize() const;

  quint8 getStpFormat() const;
  FNCR_STP_FORMAT getStpFormatEnum() const;
  void setStpFormat(const quint8& value);

  quint8 getCbFormat() const;
  FNCR_CB_FORMAT getCbFormatEnum() const;
  void setCbFormat(const quint8& value);

  quint8 getBaseType() const;
  void setBaseType(const quint8& value);

  void setFileNodeType(std::shared_ptr<IFileNodeType>& value);
  std::shared_ptr<IFileNodeType> getFnt();


  quint8 getFileNodeChunkReferenceSize();

  std::weak_ptr<FileNodeListFragment> getParent();

  friend class RevisionStoreFileParser;

private:
  // Chunkable interface
  virtual quint64 cb() const override;
  virtual RevisionStoreChunkType getType() const override;

private:
  static constexpr const quint16 minSizeInFile = 4;
};


// masks and shifts for parsing filenode
/// \todo determine wether such global variables are the best place for magic
/// numbers
static constexpr const quint32 fNmaskReserved     = 0x1;
static constexpr const quint32 fNmaskBaseType     = 0xF;
static constexpr const quint32 fNmaskCbFormat     = 0x3;
static constexpr const quint32 fNmaskStpFormat    = 0x3;
static constexpr const quint32 fNmaskFileNodeSize = 0x1FFF;
static constexpr const quint32 fNmaskFileNodeID   = 0x3FF;

static constexpr const quint32 fNshiftReserved     = 31;
static constexpr const quint32 fNshiftBaseType     = 27;
static constexpr const quint32 fNshiftCbFormat     = 25;
static constexpr const quint32 fNshiftStpFormat    = 23;
static constexpr const quint32 fNshiftFileNodeSize = 10;
static constexpr const quint32 fNshiftFileNodeID   = 0;


} // namespace priv
} // namespace libmson

#endif // FILENODE_H
