#ifndef FILENODE_H
#define FILENODE_H

#include <QtCore/qglobal.h>

#include <memory>

#include "../RevisionStoreChunk.h"
#include "Chunkable.h"

#include "../FileNodeTypes/IFileNodeType.h"

#include "../commonTypes/Enums.h"

#include "../IRevisionStoreFileObject.h"

namespace libmson {

class FileNode : public Chunkable {

private:
  std::weak_ptr<libmson::RevisionStoreChunkContainer> m_parent;

  quint16 fileNodeID;
  quint16 fileNodeSize;

  quint8 stpFormat;
  quint8 cbFormat;

  quint8 baseType;

  quint8 reserved;

  std::shared_ptr<MSONcommon::IFileNodeType> fnt;

public:
  FileNode(
      std::weak_ptr<libmson::RevisionStoreChunkContainer> parent_fileNodeListFragment);

  quint16 getFileNodeID() const;
  void setFileNodeID(const quint16 &value);
  MSONcommon::FileNodeTypeID getFileNodeTypeID() const;

  quint16 getFileNodeSize() const;
  void setFileNodeSize(const quint16 &value);

  quint8 getStpFormat() const;
  void setStpFormat(const quint8 &value);

  quint8 getCbFormat() const;
  void setCbFormat(const quint8 &value);

  quint8 getBaseType() const;
  void setBaseType(const quint8 &value);

  void setFileNodeType(const std::shared_ptr<MSONcommon::IFileNodeType> &value);
  std::shared_ptr<MSONcommon::IFileNodeType> getFnt() const;

  std::weak_ptr<libmson::RevisionStoreChunkContainer> getParent();

  // Chunkable interface
  virtual quint64 cb() const override;
  virtual RevisionStoreChunkType getType() const override;

private:
  /**
   * @brief maskReserved
   *
   * masks and shifts for parsing filenode
   */
  static constexpr const quint32 maskReserved = 0x1;
  static constexpr const quint32 maskBaseType = 0xF;
  static constexpr const quint32 maskCbFormat = 0x3;
  static constexpr const quint32 maskStpFormat = 0x3;
  static constexpr const quint32 maskFileNodeSize = 0x1FFF;
  static constexpr const quint32 maskFileNodeID = 0x3FF;

  static constexpr const quint32 shiftReserved = 31;
  static constexpr const quint32 shiftBaseType = 27;
  static constexpr const quint32 shiftCbFormat = 25;
  static constexpr const quint32 shiftStpFormat = 23;
  static constexpr const quint32 shiftFileNodeSize = 10;
  static constexpr const quint32 shiftFileNodeID = 0;

  static constexpr const quint32 minSizeInFile = 4;

  friend class libmson::RevisionStoreFile;
};

} // namespace libmson

#endif // FILENODE_H
