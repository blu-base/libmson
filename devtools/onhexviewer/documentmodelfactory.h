#ifndef DOCUMENTMODELFACTORY_H
#define DOCUMENTMODELFACTORY_H

#include <memory>

#include <QString>
#include <QtCore/qglobal.h>


#include "documentitem.h"
#include "documentmodel.h"

#include "../../../src/lib/priv/RevisionStoreFile.h"
#include "../../../src/lib/priv/RevisionStoreFileParser.h"

#include "../../../src/lib/priv/utils/ChunkableUtils.h"

#include "../../../src/lib/priv/chunkables/fileNodeTypes/FileNodeTypes.h"

#include "../../../src/lib/priv/propertyTypes/PropertyTypes.h"

// namespace libmson::priv {
// class RevisionStoreFile;


// class Chunkable_SPtr_t;
// class RevisionStoreFileHeader_SPtr_t;
//}

namespace libmson::packStore {
class PackageStoreFile;

}

class DocumentModelFactory {
public:
  DocumentModelFactory(const QString& fileName);
  ~DocumentModelFactory() = default;


  void createModel(DocumentModel* tree);
  DocumentModel* createModel(QObject* parent = nullptr);


private:
  static void
  createRevisionStoreModel(DocumentModel* tree, const QString& fileName);
  static void
  createPackageStoreModel(DocumentModel* tree, const QString& fileName);

  static std::shared_ptr<libmson::priv::RevisionStoreFile>
  getRevisionStoreDocument(const QString& fileName);
  static std::shared_ptr<libmson::packStore::PackageStoreFile>
  getPackageStoreDocument(const QString& fileName);


  // class specific tree appends
private:
  // generic
  static DocumentItem* appendNewChild(
      const QString& name, const QString& type, const QVariant& value,
      const quint64 stp, const quint64 cb, DocumentItem* parent);

  // chunkables
  static void appendRevisionStoreFileHeader(
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);

  static void appendFileNodeListFragment(
      const libmson::priv::FileNodeListFragment_SPtr_t& chunk,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);
  static void appendFileNode(
      const libmson::priv::FileNode_SPtr_t& chunk,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);
  static void appendFreeChunkListFragment(
      const libmson::priv::FreeChunkListFragment_SPtr_t& chunk,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);
  static void appendFreeChunk(
      const libmson::priv::FreeChunk_SPtr_t& chunk, DocumentItem* parent);
  static void appendTransactionLogFragment(
      const libmson::priv::TransactionLogFragment_SPtr_t& chunk,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);
  static void appendFileDataStoreObject(
      const libmson::priv::FileDataStoreObject_SPtr_t& chunk,
      DocumentItem* parent);
  static void appendObjectSpaceObjectPropSet(
      const libmson::priv::ObjectSpaceObjectPropSet_SPtr_t& chunk,
      DocumentItem* parent);
  static void appendObjectInfoDependencyOverrideData(
      const libmson::priv::ObjectInfoDependencyOverrideData_SPtr_t& chunk,
      DocumentItem* parent);
  static void appendEncryptedData(
      const libmson::priv::EncryptedData_SPtr_t& chunk, DocumentItem* parent);
  static void appendUnknownBlob(
      const libmson::priv::UnknownBlob_SPtr_t& chunk, DocumentItem* parent);


  // fileNodeTypes
  static void appendFileNodeData(
      const libmson::priv::FileNode_SPtr_t& chunk,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);

  // type 0
  static void appendObjectSpaceManifestRootFND(
      const libmson::priv::ObjectSpaceManifestRootFND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb, DocumentItem* parent);
  static void appendObjectSpaceManifestListStartFND(
      const libmson::priv::ObjectSpaceManifestListStartFND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb, DocumentItem* parent);
  static void appendRevisionManifestListStartFND(
      const libmson::priv::RevisionManifestListStartFND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb, DocumentItem* parent);
  static void appendRevisionManifestStart4FND(
      const libmson::priv::RevisionManifestStart4FND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb, DocumentItem* parent);
  static void appendRevisionManifestEndFND(
      const libmson::priv::RevisionManifestEndFND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb, DocumentItem* parent);
  static void appendRevisionManifestStart6FND(
      const libmson::priv::RevisionManifestStart6FND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb, DocumentItem* parent);
  static void appendRevisionManifestStart7FND(
      const libmson::priv::RevisionManifestStart7FND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb, DocumentItem* parent);
  static void appendGlobalIdTableStartFNDX(
      const libmson::priv::GlobalIdTableStartFNDX_SPtr_t& fnd,
      const quint64 stp, const quint64 cb, DocumentItem* parent);
  static void appendGlobalIdTableStart2FND(
      const libmson::priv::GlobalIdTableStart2FND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb, DocumentItem* parent);
  static void appendGlobalIdTableEntryFNDX(
      const libmson::priv::GlobalIdTableEntryFNDX_SPtr_t& fnd,
      const quint64 stp, const quint64 cb, DocumentItem* parent);
  static void appendGlobalIdTableEntry2FNDX(
      const libmson::priv::GlobalIdTableEntry2FNDX_SPtr_t& fnd,
      const quint64 stp, const quint64 cb, DocumentItem* parent);
  static void appendGlobalIdTableEntry3FNDX(
      const libmson::priv::GlobalIdTableEntry3FNDX_SPtr_t& fnd,
      const quint64 stp, const quint64 cb, DocumentItem* parent);
  static void appendGlobalIdTableEndFNDX(
      const libmson::priv::GlobalIdTableEndFNDX_SPtr_t& fnd, const quint64 stp,
      const quint64 cb, DocumentItem* parent);
  static void appendRootObjectReference2FNDX(
      const libmson::priv::RootObjectReference2FNDX_SPtr_t& fnd,
      const quint64 stp, const quint64 cb, DocumentItem* parent);
  static void appendRootObjectReference3FND(
      const libmson::priv::RootObjectReference3FND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb, DocumentItem* parent);
  static void appendRevisionRoleDeclarationFND(
      const libmson::priv::RevisionRoleDeclarationFND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb, DocumentItem* parent);
  static void appendRevisionRoleAndContextDeclarationFND(
      const libmson::priv::RevisionRoleAndContextDeclarationFND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb, DocumentItem* parent);
  static void appendObjectDeclarationFileData3RefCountFND(
      const libmson::priv::ObjectDeclarationFileData3RefCountFND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb, DocumentItem* parent);
  static void appendObjectDeclarationFileData3LargeRefCountFND(
      const libmson::priv::ObjectDeclarationFileData3LargeRefCountFND_SPtr_t&
          fnd,
      const quint64 stp, const quint64 cb, DocumentItem* parent);
  static void appendDataSignatureGroupDefinitionFND(
      const libmson::priv::DataSignatureGroupDefinitionFND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb, DocumentItem* parent);
  static void appendObjectGroupStartFND(
      const libmson::priv::ObjectGroupStartFND_SPtr_t& fnd, const quint64 stp,
      const quint64 cb, DocumentItem* parent);
  static void appendObjectGroupEndFND(
      const libmson::priv::ObjectGroupEndFND_SPtr_t& fnd, const quint64 stp,
      const quint64 cb, DocumentItem* parent);
  static void appendChunkTerminatorFND(
      const libmson::priv::ChunkTerminatorFND_SPtr_t& fnd, const quint64 stp,
      const quint64 cb, DocumentItem* parent);

  // type 1
  static void appendObjectDeclarationWithRefCountFNDX(
      const libmson::priv::ObjectDeclarationWithRefCountFNDX_SPtr_t& fnd,
      const quint64 stp, const quint64 cb,
      const libmson::priv::FileNode_SPtr_t& fn,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);
  static void appendObjectDeclarationWithRefCount2FNDX(
      const libmson::priv::ObjectDeclarationWithRefCount2FNDX_SPtr_t& fnd,
      const quint64 stp, const quint64 cb,
      const libmson::priv::FileNode_SPtr_t& fn,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);
  static void appendObjectRevisionWithRefCountFNDX(
      const libmson::priv::ObjectRevisionWithRefCountFNDX_SPtr_t& fnd,
      const quint64 stp, const quint64 cb,
      const libmson::priv::FileNode_SPtr_t& fn,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);
  static void appendObjectRevisionWithRefCount2FNDX(
      const libmson::priv::ObjectRevisionWithRefCount2FNDX_SPtr_t& fnd,
      const quint64 stp, const quint64 cb,
      const libmson::priv::FileNode_SPtr_t& fn,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);
  static void appendObjectDataEncryptionKeyV2FNDX(
      const libmson::priv::ObjectDataEncryptionKeyV2FNDX_SPtr_t& fnd,
      const quint64 stp, const quint64 cb,
      const libmson::priv::FileNode_SPtr_t& fn,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);
  static void appendObjectInfoDependencyOverridesFND(
      const libmson::priv::ObjectInfoDependencyOverridesFND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb,
      const libmson::priv::FileNode_SPtr_t& fn,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);
  static void appendFileDataStoreObjectReferenceFND(
      const libmson::priv::FileDataStoreObjectReferenceFND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb,
      const libmson::priv::FileNode_SPtr_t& fn,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);
  static void appendObjectDeclaration2RefCountFND(
      const libmson::priv::ObjectDeclaration2RefCountFND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb,
      const libmson::priv::FileNode_SPtr_t& fn,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);
  static void appendObjectDeclaration2LargeRefCountFND(
      const libmson::priv::ObjectDeclaration2LargeRefCountFND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb,
      const libmson::priv::FileNode_SPtr_t& fn,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);
  static void appendHashedChunkDescriptor2FND(
      const libmson::priv::HashedChunkDescriptor2FND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb,
      const libmson::priv::FileNode_SPtr_t& fn,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);
  static void appendReadOnlyObjectDeclaration2RefCountFND(
      const libmson::priv::ReadOnlyObjectDeclaration2RefCountFND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb,
      const libmson::priv::FileNode_SPtr_t& fn,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);
  static void appendReadOnlyObjectDeclaration2LargeRefCountFND(
      const libmson::priv::ReadOnlyObjectDeclaration2LargeRefCountFND_SPtr_t&
          fnd,
      const quint64 stp, const quint64 cb,
      const libmson::priv::FileNode_SPtr_t& fn,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);

  // type 2
  static void appendFileDataStoreListReferenceFND(
      const libmson::priv::FileDataStoreListReferenceFND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb,
      const libmson::priv::FileNode_SPtr_t& fn,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);
  static void appendObjectSpaceManifestListReferenceFND(
      const libmson::priv::ObjectSpaceManifestListReferenceFND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb,
      const libmson::priv::FileNode_SPtr_t& fn,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);
  static void appendRevisionManifestListReferenceFND(
      const libmson::priv::RevisionManifestListReferenceFND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb,
      const libmson::priv::FileNode_SPtr_t& fn,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);
  static void appendObjectGroupListReferenceFND(
      const libmson::priv::ObjectGroupListReferenceFND_SPtr_t& fnd,
      const quint64 stp, const quint64 cb,
      const libmson::priv::FileNode_SPtr_t& fn,
      const libmson::priv::RevisionStoreFile_SPtr_t& revStoreFile,
      DocumentItem* parent);


  // Transactions
  // increments stp by its size
  static DocumentItem* appendTransactionEntry(
      const libmson::priv::TransactionEntry& entry, const QString& name,
      quint64& stp, DocumentItem* parent);


  // ObjectPropSet components

  // increments stp by its size
  static DocumentItem* appendObjectSpaceObjectStreamHeader(
      const libmson::priv::ObjectSpaceObjectStreamHeader& streamHeader,
      const QString& name, quint64& stp, DocumentItem* parent);

  // increments stp by its size
  static DocumentItem* appendObjectSpaceObjectStreamOfOIDs(
      const libmson::priv::ObjectSpaceObjectStreamOfOIDs& stream,
      const QString& name, quint64& stp, DocumentItem* parent);

  // increments stp by its size
  static DocumentItem* appendObjectSpaceObjectStreamOfOSIDs(
      const libmson::priv::ObjectSpaceObjectStreamOfOSIDs& stream,
      const QString& name, quint64& stp, DocumentItem* parent);

  // increments stp by its size
  static DocumentItem* appendObjectSpaceObjectStreamOfContextIDs(
      const libmson::priv::ObjectSpaceObjectStreamOfContextIDs& stream,
      const QString& name, quint64& stp, DocumentItem* parent);

  // increments stp by its size
  static DocumentItem* appendPropertySet(
      const libmson::priv::PropertySet& prop, const QString& name, quint64& stp,
      DocumentItem* parent);

  // increments stp by its size
  static DocumentItem* appendPropertyID(
      const libmson::priv::PropertyID& propId, quint64& stp,
      DocumentItem* parent);

  // increments stp by its size
  static DocumentItem* appendPTArrayNumber(
      const libmson::priv::PropertyType_ArrayNumber_SPtr_t& pt, quint64& stp,
      DocumentItem* parent);
  // increments stp by its size
  static DocumentItem* appendPTArrayOfPropertyValues(
      const libmson::priv::PropertyType_ArrayOfPropertyValues_SPtr_t& pt,
      quint64& stp, DocumentItem* parent);
  // increments stp by its size
  static DocumentItem* appendPTEightBytesOfData(
      const libmson::priv::PropertyType_EightBytesOfData_SPtr_t& pt,
      quint64& stp, DocumentItem* parent);
  // increments stp by its size
  static DocumentItem* appendPTFourBytesOfData(
      const libmson::priv::PropertyType_FourBytesOfData_SPtr_t& pt,
      quint64& stp, DocumentItem* parent);
  // increments stp by its size
  static DocumentItem* appendPTFourBytesOfLengthFollowedByData(
      const libmson::priv::PropertyType_FourBytesOfLengthFollowedByData_SPtr_t&
          pt,
      quint64& stp, DocumentItem* parent);
  // increments stp by its size
  static DocumentItem* appendPTOneByteOfData(
      const libmson::priv::PropertyType_OneByteOfData_SPtr_t& pt, quint64& stp,
      DocumentItem* parent);
  // increments stp by its size
  static DocumentItem* appendPTPropertySet(
      const libmson::priv::PropertyType_PropertySet_SPtr_t& pt, quint64& stp,
      DocumentItem* parent);
  // increments stp by its size
  static DocumentItem* appendPTTwoBytesOfData(
      const libmson::priv::PropertyType_TwoBytesOfData_SPtr_t& pt, quint64& stp,
      DocumentItem* parent);
  // increments stp by its size
  static DocumentItem* appendPTNoData(quint64& stp, DocumentItem* parent);


  // common

  // increments stp by its size
  static DocumentItem* appendUInt8(
      const quint8 val, const QString& name, quint64& stp, DocumentItem* parent,
      const bool asHex = true);

  // increments stp by its size
  static DocumentItem* appendUInt16(
      const quint16 val, const QString& name, quint64& stp,
      DocumentItem* parent, const bool asHex = true);

  // increments stp by its size
  static DocumentItem* appendUInt32(
      const quint32 val, const QString& name, quint64& stp,
      DocumentItem* parent, const bool asHex = true);

  // increments stp by its size
  static DocumentItem* appendUInt64(
      const quint64 val, const QString& name, quint64& stp,
      DocumentItem* parent, const bool asHex = true);

  // increments stp by its size
  static DocumentItem* appendInt8(
      const qint8 val, const QString& name, quint64& stp, DocumentItem* parent,
      const bool asHex = true);

  // increments stp by its size
  static DocumentItem* appendInt16(
      const qint16 val, const QString& name, quint64& stp, DocumentItem* parent,
      const bool asHex = true);

  // increments stp by its size
  static DocumentItem* appendInt32(
      const qint32 val, const QString& name, quint64& stp, DocumentItem* parent,
      const bool asHex = true);

  // increments stp by its size
  static DocumentItem* appendInt64(
      const qint64 val, const QString& name, quint64& stp, DocumentItem* parent,
      const bool asHex = true);

  // increments stp by its size
  static DocumentItem* appendGuid(
      const QUuid& guid, const QString& name, quint64& stp,
      DocumentItem* parent);

  // increments stp by its size
  static DocumentItem* appendExtendedGuid(
      const libmson::priv::ExtendedGUID& eguid, const QString& name,
      quint64& stp, DocumentItem* parent);

  // increments stp by its size
  static DocumentItem* appendCompactID(
      const libmson::priv::CompactID& cid, const QString& name, quint64& stp,
      DocumentItem* parent);

  // increments stp by its size
  static DocumentItem* appendObjectInfoDependencyOverrideData(
      const libmson::priv::ObjectInfoDependencyOverrideData& objInfo,
      const QString& name, quint64& stp, DocumentItem* parent);

  // increments stp by its size
  static DocumentItem* appendObjectInfoDependencyOverride8(
      const libmson::priv::ObjectInfoDependencyOverride8& objInfo,
      const QString& name, quint64& stp, DocumentItem* parent);

  // increments stp by its size
  static DocumentItem* appendObjectInfoDependencyOverride32(
      const libmson::priv::ObjectInfoDependencyOverride32& objInfo,
      const QString& name, quint64& stp, DocumentItem* parent);

  // increments stp by its size
  static DocumentItem* appendJCID(
      const libmson::priv::JCID& cid, const QString& name, quint64& stp,
      DocumentItem* parent);

  // increments stp by its size
  static DocumentItem* appendStringInStorageBuffer(
      const libmson::priv::StringInStorageBuffer& buffer, const QString& name,
      quint64& stp, DocumentItem* parent);

  // increments stp by its size
  static DocumentItem* appendObjectDeclarationWithRefCountBody(
      const libmson::priv::ObjectDeclarationWithRefCountBody& declBody,
      const QString& name, quint64& stp, DocumentItem* parent);

  // increments stp by its size
  static DocumentItem* appendObjectDeclaration2Body(
      const libmson::priv::ObjectDeclaration2Body& declBody,
      const QString& name, quint64& stp, DocumentItem* parent);

  // increments stp by its size
  static DocumentItem* appendFileChunkReference32(
      const libmson::priv::FileChunkReference32& ref, const QString& name,
      quint64& stp, DocumentItem* parent);

  // increments stp by its size
  static DocumentItem* appendFileChunkReference64x32(
      const libmson::priv::FileChunkReference64x32& ref, const QString& name,
      quint64& stp, DocumentItem* parent);

  // increments stp by its size
  static DocumentItem* appendFileChunkReference64(
      const libmson::priv::FileChunkReference64& ref, const QString& name,
      quint64& stp, DocumentItem* parent);

  // increments stp by its size
  static DocumentItem* appendFileNodeChunkReference(
      const libmson::priv::FileNodeChunkReference& ref, const QString& name,
      quint64& stp, DocumentItem* parent);


private:
  QString m_fileName;
};

#endif // DOCUMENTMODELFACTORY_H
