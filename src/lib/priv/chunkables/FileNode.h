#ifndef FILENODE_H
#define FILENODE_H

#include "../commonTypes/FileNodeChunkReference.h"
#include "Chunkable.h"
#include <QtCore/qglobal.h>


namespace libmson {
namespace priv {

class FileNode;

typedef std::shared_ptr<FileNode> FileNode_SPtr_t;
typedef std::weak_ptr<FileNode> FileNode_WPtr_t;

class FileNodeListFragment;


class IFileNodeType;

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
  NullFnd                                    = 0x0,
  InvalidFND                                 = 0xFFF,
};


class FileNode : public Chunkable {

private:
  std::weak_ptr<FileNodeListFragment> m_parent;

  quint16 fileNodeID;
  quint16 fileNodeSize;

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
  void setFileNodeSize(const quint16& value);

  quint8 getStpFormat() const;
  FNCR_STP_FORMAT getStpFormatEnum() const;
  void setStpFormat(const quint8& value);

  quint8 getCbFormat() const;
  FNCR_CB_FORMAT getCbFormatEnum() const;
  void setCbFormat(const quint8& value);

  quint8 getBaseType() const;
  void setBaseType(const quint8& value);

  void setFileNodeType(const std::shared_ptr<IFileNodeType>& value);
  std::shared_ptr<IFileNodeType> getFnt() const;


  quint8 getFileNodeChunkReferenceSize();

  std::weak_ptr<FileNodeListFragment> getParent();


  friend class RevisionStoreFileWriter;
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
