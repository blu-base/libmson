#ifndef FILENODETYPE_H
#define FILENODETYPE_H

#include <QDataStream>
#include <QDebug>
#include <QtCore/qglobal.h>

#include "commonTypes/CompactID.h"
#include "commonTypes/ExtendedGUID.h"
#include "commonTypes/FileChunkReference.h"

class FileNodeType {

private:
  ExtendedGUID eguid1;
  ExtendedGUID eguid2;
  ExtendedGUID eguid3;

  QUuid uuid1;

  CompactID id;

  quint32 uint1;
  quint32 uint2;
  quint32 uint3;

  quint64 ulong1;
  quint64 ulong2;

  quint32 nInstance;

  quint64 timeCreation;

  qint32 RevisionRole;

  bool fHasOidReferences;
  bool fHasOsidReferences;

  quint64 reservedLength;

public:
  enum FileNodeData {
    ObjectSpaceManifestRootFND = 0x004,
    ObjectSpaceManifestListReferenceFND = 0x008,
    ObjectSpaceManifestListStartFND = 0x00C,
    RevisionManifestListReferenceFND = 0x010,
    RevisionManifestListStartFND = 0x014,
    RevisionManifestStart4FND = 0x01B,
    RevisionManifestEndFND = 0x01C,
    RevisionManifestStart6FND = 0x01E,
    RevisionManifestStart7FND = 0x01F,
    GlobalIdTableStartFNDX = 0x021,
    GlobalIdTableStart2FND = 0x022,
    GlobalIdTableEntryFNDX = 0x024,
    GlobalIdTableEntry2FNDX = 0x025,
    GlobalIdTableEntry3FNDX = 0x026,
    GlobalIdTableEndFNDX = 0x028,
    ObjectDeclarationWithRefCountFNDX = 0x02D,
    ObjectDeclarationWithRefCount2FNDX = 0x02E,
    ObjectRevisionWithRefCountFNDX = 0x041,
    ObjectRevisionWithRefCount2FNDX = 0x042,
    RootObjectReference2FNDX = 0x059,
    RootObjectReference3FND = 0x05A,
    RevisionRoleDeclarationFND = 0x05C,
    RevisionRoleAndContextDeclarationFND = 0x05D,
    ObjectDeclarationFileData3RefCountFND = 0x072,
    ObjectDeclarationFileData3LargeRefCountFND = 0x073,
    ObjectDataEncryptionKeyV2FNDX = 0x07C,
    ObjectInfoDependencyOverridesFND = 0x084,
    DataSignatureGroupDefinitionFND = 0x08C,
    FileDataStoreListReferenceFND = 0x090,
    FileDataStoreObjectReferenceFND = 0x094,
    ObjectDeclaration2RefCountFND = 0x0A4,
    ObjectDeclaration2LargeRefCountFND = 0x0A5,
    ObjectGroupListReferenceFND = 0x0B0,
    ObjectGroupStartFND = 0x0B4,
    ObjectGroupEndFND = 0x0B8,
    HashedChunkDescriptor2FND = 0x0C2,
    ReadOnlyObjectDeclaration2RefCountFND = 0x0C4,
    ReadOnlyObjectDeclaration2LargeRefCountFND = 0x0C5,
    ChunkTerminatorFND = 0x0FF
  };

protected:
public:
  FileNodeType();
  FileNodeType(FileNodeData);
  ~FileNodeType();

  friend QDataStream &operator<<(QDataStream &ds, const FileNodeType &obj) {
    obj.serialize(ds);
    return ds;
  };
  friend QDataStream &operator>>(QDataStream &ds, FileNodeType &obj) {
    obj.parse(ds);
    return ds;
  };

  friend QDebug operator<<(QDebug dbg, const FileNodeType &obj) {
    obj.toDebugString(dbg);
    return dbg;
  };

private:
  virtual void parse(QDataStream &ds) = 0;
  virtual void serialize(QDataStream &ds) const = 0;
  virtual void toDebugString(QDebug dbg) const = 0;
};

// class ObjectSpaceManifestListReferenceFND : public FileNodeType {

// public:
//  ObjectSpaceManifestListReferenceFND();
//  ObjectSpaceManifestListReferenceFND(const quint8 stpFormat,
//                                      const quint8 cbFormat);

//  ObjectSpaceManifestListReferenceFND(
//      const ObjectSpaceManifestListReferenceFND &source);

//  ~ObjectSpaceManifestListReferenceFND();

//  virtual void parse(QDataStream &ds) override;
//  virtual void serialize(QDataStream &ds) const override;
//  virtual void toDebugString(QDebug dbg) const override;

//  FileNodeChunkReference ref;
//  ExtendedGUID gosid;

//};

#endif // FILENODETYPE_H
