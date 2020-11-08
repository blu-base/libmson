#ifndef FILENODE_H
#define FILENODE_H

#include <QtCore/qglobal.h>

#include <memory>

#include "Chunkable.h"
#include "RevisionStoreChunkContainer.h"

#include "fileNodeTypes/IFileNodeType.h"

namespace libmson {
namespace priv {

enum class FileNodeTypeID : quint16 {
  ObjectSpaceManifestRootFND                 = 0x004,
  ObjectSpaceManifestListReferenceFND        = 0x008,
  ObjectSpaceManifestListStartFND            = 0x00C,
  RevisionManifestListReferenceFND           = 0x010,
  RevisionManifestListStartFND               = 0x014,
  RevisionManifestStart4FND                  = 0x01B,
  RevisionManifestEndFND                     = 0x01C,
  RevisionManifestStart6FND                  = 0x01E,
  RevisionManifestStart7FND                  = 0x01F,
  GlobalIdTableStartFNDX                     = 0x021,
  GlobalIdTableStart2FND                     = 0x022,
  GlobalIdTableEntryFNDX                     = 0x024,
  GlobalIdTableEntry2FNDX                    = 0x025,
  GlobalIdTableEntry3FNDX                    = 0x026,
  GlobalIdTableEndFNDX                       = 0x028,
  ObjectDeclarationWithRefCountFNDX          = 0x02D,
  ObjectDeclarationWithRefCount2FNDX         = 0x02E,
  ObjectRevisionWithRefCountFNDX             = 0x041,
  ObjectRevisionWithRefCount2FNDX            = 0x042,
  RootObjectReference2FNDX                   = 0x059,
  RootObjectReference3FND                    = 0x05A,
  RevisionRoleDeclarationFND                 = 0x05C,
  RevisionRoleAndContextDeclarationFND       = 0x05D,
  ObjectDeclarationFileData3RefCountFND      = 0x072,
  ObjectDeclarationFileData3LargeRefCountFND = 0x073,
  ObjectDataEncryptionKeyV2FNDX              = 0x07C,
  ObjectInfoDependencyOverridesFND           = 0x084,
  DataSignatureGroupDefinitionFND            = 0x08C,
  FileDataStoreListReferenceFND              = 0x090,
  FileDataStoreObjectReferenceFND            = 0x094,
  ObjectDeclaration2RefCountFND              = 0x0A4,
  ObjectDeclaration2LargeRefCountFND         = 0x0A5,
  ObjectGroupListReferenceFND                = 0x0B0,
  ObjectGroupStartFND                        = 0x0B4,
  ObjectGroupEndFND                          = 0x0B8,
  HashedChunkDescriptor2FND                  = 0x0C2,
  ReadOnlyObjectDeclaration2RefCountFND      = 0x0C4,
  ReadOnlyObjectDeclaration2LargeRefCountFND = 0x0C5,
  ChunkTerminatorFND                         = 0x0FF,
  InvalidFND                                 = 0xFFF,
};

class FileNode : public Chunkable {

private:
  RSChunkContainer_WPtr_t m_parent;

  quint16 fileNodeID;
  quint16 fileNodeSize;

  quint8 stpFormat;
  quint8 cbFormat;

  quint8 baseType;

  quint8 reserved;

  std::shared_ptr<IFileNodeType> fnt;

public:
  FileNode(RSChunkContainer_WPtr_t parent_fileNodeListFragment);

  quint16 getFileNodeID() const;
  void setFileNodeID(const quint16& value);
  FileNodeTypeID getFileNodeTypeID() const;

  quint16 getFileNodeSize() const;
  void setFileNodeSize(const quint16& value);

  quint8 getStpFormat() const;
  void setStpFormat(const quint8& value);

  quint8 getCbFormat() const;
  void setCbFormat(const quint8& value);

  quint8 getBaseType() const;
  void setBaseType(const quint8& value);

  void setFileNodeType(const std::shared_ptr<IFileNodeType>& value);
  std::shared_ptr<IFileNodeType> getFnt() const;

  RSChunkContainer_WPtr_t getParent();

  // Chunkable interface
  virtual quint64 cb() const override;
  virtual RevisionStoreChunkType getType() const override;

private:
  /**
   * @brief maskReserved
   *
   * masks and shifts for parsing filenode
   */
  static constexpr const quint32 maskReserved     = 0x1;
  static constexpr const quint32 maskBaseType     = 0xF;
  static constexpr const quint32 maskCbFormat     = 0x3;
  static constexpr const quint32 maskStpFormat    = 0x3;
  static constexpr const quint32 maskFileNodeSize = 0x1FFF;
  static constexpr const quint32 maskFileNodeID   = 0x3FF;

  static constexpr const quint32 shiftReserved     = 31;
  static constexpr const quint32 shiftBaseType     = 27;
  static constexpr const quint32 shiftCbFormat     = 25;
  static constexpr const quint32 shiftStpFormat    = 23;
  static constexpr const quint32 shiftFileNodeSize = 10;
  static constexpr const quint32 shiftFileNodeID   = 0;

  static constexpr const quint32 minSizeInFile = 4;

  friend class RevisionStoreFileParser;
};



} // namespace priv
} // namespace libmson

#endif // FILENODE_H
