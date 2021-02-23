#ifndef REVISIONSTOREFILEPARSER_H
#define REVISIONSTOREFILEPARSER_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <memory>

#include "RevisionStoreFile.h"
#include "chunkables/Chunkable.h"

#include "chunkables/EncryptedData.h"
#include "chunkables/FileDataStoreObject.h"
#include "chunkables/FileNode.h"
#include "chunkables/FileNodeListFragment.h"
#include "chunkables/FreeChunk.h"
#include "chunkables/FreeChunkListFragment.h"
#include "chunkables/ObjectInfoDependencyOverrideData.h"
#include "chunkables/ObjectSpaceObjectPropSet.h"
#include "chunkables/RevisionStoreFileHeader.h"
#include "chunkables/TransactionLogFragment.h"
#include "chunkables/UnknownBlob.h"

#include "chunkables/fileNodeTypes/FileNodeTypes.h"
#include "chunkables/fileNodeTypes/IFileNodeType.h"

#include "ObjectGroupList.h"
#include "ObjectSpaceManifestList.h"
#include "RevisionManifest.h"
#include "RevisionManifestList.h"


namespace libmson {
namespace priv {

/**
 * @brief Parser for MS Onenote files according to the MS-ONESTORE spec
 * this only includes file versions as early as Onenote 2010
 */
class RevisionStoreFileParser {
private:
  QDataStream& m_ds;
  std::shared_ptr<RevisionStoreFile> m_file;

public:
  RevisionStoreFileParser(QDataStream& inputStream, const QString& fileName);


  std::shared_ptr<RevisionStoreFile> parse();

private:
  // Chunkable parsers ---------------------------------------------------------

  void parseChunk(QDataStream& ds, const Chunkable_SPtr_t& chunk);

  void parseEncryptedData(QDataStream& ds, const EncryptedData_WPtr_t& chunk);

  void parseFileDataStoreObject(
      QDataStream& ds, const FileDataStoreObject_WPtr_t& fileData);


  FileNode_SPtr_t parseFileNode(
      QDataStream& ds, const quint64 stp,
      const FileNodeListFragment_WPtr_t& parent);

  FileNode_SPtr_t
  parseFileNode(QDataStream& ds, const FileNode_SPtr_t& fileNode);

  /// parses a fragment. Returns a RSChunkContainer_SPtr_t if there is a next
  /// Fragment specified That RSChunkContainer_SPtr_t is not inserted to any
  /// std::list<RSChunkContainer_SPtr_t>& chunkList. This has to be done by
  /// calling method.
  FileNodeListFragment_SPtr_t parseFileNodeListFragment(
      QDataStream& ds, const FileNodeListFragment_SPtr_t& fragment);

  /// parses a fragment tree. Returns a RSChunkContainer_WPtr_t list
  std::vector<FileNodeListFragment_WPtr_t> parseFileNodeList(
      QDataStream& ds, const FileNodeListFragment_WPtr_t& firstFragment);


  /// parses the FreeChunkListFrragments and adds ChunkContainer to m_file
  void parseFreeChunkListFragments(
      QDataStream& ds, const FreeChunkListFragment_WPtr_t& firstFragment);

  void parseFreeChunk(const FreeChunk_SPtr_t& freeChunk);

  void parseObjectInfoDependencyOverrideData(
      QDataStream& ds,
      const ObjectInfoDependencyOverrideData_SPtr_t& objectInfo);

  ObjectSpaceObjectPropSet_SPtr_t parseObjectSpaceObjectPropSet(
      QDataStream& ds, const ObjectSpaceObjectPropSet_SPtr_t& objectPropSet);

  /// parses the header, adds the containers to m_file and returns the pointer
  /// to the header container
  RevisionStoreFileHeader_SPtr_t parseRevisionStoreFileHeader(QDataStream& ds);

  bool parseTransactionLogFragment(
      QDataStream& ds, const TransactionLogFragment_SPtr_t& firstFragment);

  void parseUnknownBlob(QDataStream& ds, const UnknownBlob_SPtr_t& unknownBlob);


  // FileNodeType parsers ------------------------------------------------------
  /// \todo should the FND parses return their full class type?

  /// encapsulation layer for parsing FileNode data
  IFileNodeType_SPtr_t
  parseFileNodeType(QDataStream& ds, const FileNode_SPtr_t& fn);

  void registerFileNodeData(const FileNode_SPtr_t& fn);


  // type 0
  ChunkTerminatorFND_SPtr_t parseChunkTerminatorFND(const FileNode_SPtr_t& fn);
  DataSignatureGroupDefinitionFND_SPtr_t parseDataSignatureGroupDefinitionFND(
      QDataStream& ds, const FileNode_SPtr_t& fn);
  GlobalIdTableEndFNDX_SPtr_t
  parseGlobalIdTableEndFNDX(const FileNode_SPtr_t& fn);
  GlobalIdTableEntry2FNDX_SPtr_t
  parseGlobalIdTableEntry2FNDX(QDataStream& ds, const FileNode_SPtr_t& fn);
  GlobalIdTableEntry3FNDX_SPtr_t
  parseGlobalIdTableEntry3FNDX(QDataStream& ds, const FileNode_SPtr_t& fn);
  GlobalIdTableEntryFNDX_SPtr_t
  parseGlobalIdTableEntryFNDX(QDataStream& ds, const FileNode_SPtr_t& fn);
  GlobalIdTableStart2FND_SPtr_t
  parseGlobalIdTableStart2FND(const FileNode_SPtr_t& fn);
  GlobalIdTableStartFNDX_SPtr_t
  parseGlobalIdTableStartFNDX(QDataStream& ds, const FileNode_SPtr_t& fn);
  ObjectDeclarationFileData3LargeRefCountFND_SPtr_t
  parseObjectDeclarationFileData3LargeRefCountFND(
      QDataStream& ds, const FileNode_SPtr_t& fn);
  ObjectDeclarationFileData3RefCountFND_SPtr_t
  parseObjectDeclarationFileData3RefCountFND(
      QDataStream& ds, const FileNode_SPtr_t& fn);
  ObjectGroupEndFND_SPtr_t parseObjectGroupEndFND(const FileNode_SPtr_t& fn);
  ObjectGroupStartFND_SPtr_t
  parseObjectGroupStartFND(QDataStream& ds, const FileNode_SPtr_t& fn);
  ObjectSpaceManifestListStartFND_SPtr_t parseObjectSpaceManifestListStartFND(
      QDataStream& ds, const FileNode_SPtr_t& fn);
  ObjectSpaceManifestRootFND_SPtr_t
  parseObjectSpaceManifestRootFND(QDataStream& ds, const FileNode_SPtr_t& fn);
  RevisionManifestEndFND_SPtr_t
  parseRevisionManifestEndFND(const FileNode_SPtr_t& fn);
  RevisionManifestListStartFND_SPtr_t
  parseRevisionManifestListStartFND(QDataStream& ds, const FileNode_SPtr_t& fn);
  RevisionManifestStart4FND_SPtr_t
  parseRevisionManifestStart4FND(QDataStream& ds, const FileNode_SPtr_t& fn);
  RevisionManifestStart6FND_SPtr_t
  parseRevisionManifestStart6FND(QDataStream& ds, const FileNode_SPtr_t& fn);
  RevisionManifestStart7FND_SPtr_t
  parseRevisionManifestStart7FND(QDataStream& ds, const FileNode_SPtr_t& fn);
  RevisionRoleAndContextDeclarationFND_SPtr_t
  parseRevisionRoleAndContextDeclarationFND(
      QDataStream& ds, const FileNode_SPtr_t& fn);
  RevisionRoleDeclarationFND_SPtr_t
  parseRevisionRoleDeclarationFND(QDataStream& ds, const FileNode_SPtr_t& fn);
  RootObjectReference2FNDX_SPtr_t
  parseRootObjectReference2FNDX(QDataStream& ds, const FileNode_SPtr_t& fn);
  RootObjectReference3FND_SPtr_t
  parseRootObjectReference3FND(QDataStream& ds, const FileNode_SPtr_t& fn);

  // type 1
  FileDataStoreObjectReferenceFND_SPtr_t parseFileDataStoreObjectReferenceFND(
      QDataStream& ds, const FileNode_SPtr_t& fn);
  HashedChunkDescriptor2FND_SPtr_t
  parseHashedChunkDescriptor2FND(QDataStream& ds, const FileNode_SPtr_t& fn);
  ObjectDataEncryptionKeyV2FNDX_SPtr_t parseObjectDataEncryptionKeyV2FNDX(
      QDataStream& ds, const FileNode_SPtr_t& fn);
  ObjectDeclaration2LargeRefCountFND_SPtr_t
  parseObjectDeclaration2LargeRefCountFND(
      QDataStream& ds, const FileNode_SPtr_t& fn);
  ObjectDeclaration2RefCountFND_SPtr_t parseObjectDeclaration2RefCountFND(
      QDataStream& ds, const FileNode_SPtr_t& fn);
  ObjectDeclarationWithRefCount2FNDX_SPtr_t
  parseObjectDeclarationWithRefCount2FNDX(
      QDataStream& ds, const FileNode_SPtr_t& fn);
  ReadOnlyObjectDeclaration2LargeRefCountFND_SPtr_t
  parseReadOnlyObjectDeclaration2LargeRefCountFND(
      QDataStream& ds, const FileNode_SPtr_t& fn);
  ReadOnlyObjectDeclaration2RefCountFND_SPtr_t
  parseReadOnlyObjectDeclaration2RefCountFND(
      QDataStream& ds, const FileNode_SPtr_t& fn);
  ObjectDeclarationWithRefCountFNDX_SPtr_t
  parseObjectDeclarationWithRefCountFNDX(
      QDataStream& ds, const FileNode_SPtr_t& fn);
  ObjectInfoDependencyOverridesFND_SPtr_t parseObjectInfoDependencyOverridesFND(
      QDataStream& ds, const FileNode_SPtr_t& fn);
  ObjectRevisionWithRefCount2FNDX_SPtr_t parseObjectRevisionWithRefCount2FNDX(
      QDataStream& ds, const FileNode_SPtr_t& fn);
  ObjectRevisionWithRefCountFNDX_SPtr_t parseObjectRevisionWithRefCountFNDX(
      QDataStream& ds, const FileNode_SPtr_t& fn);

  // type 2
  FileDataStoreListReferenceFND_SPtr_t parseFileDataStoreListReferenceFND(
      QDataStream& ds, const FileNode_SPtr_t& fn);
  ObjectGroupListReferenceFND_SPtr_t
  parseObjectGroupListReferenceFND(QDataStream& ds, const FileNode_SPtr_t& fn);
  ObjectSpaceManifestListReferenceFND_SPtr_t
  parseObjectSpaceManifestListReferenceFND(
      QDataStream& ds, const FileNode_SPtr_t& fn);
  RevisionManifestListReferenceFND_SPtr_t parseRevisionManifestListReferenceFND(
      QDataStream& ds, const FileNode_SPtr_t& fn);


  // Other non-chunkables ------------------------------------------------------

  ObjectSpaceManifestList_SPtr_t
  parseObjectSpaceManifestList(QDataStream& ds, const FileNode_SPtr_t& fn);

  std::shared_ptr<RevisionManifestList> parseRevisionManifestList(
      QDataStream& ds, const FileNode_SPtr_t& fn,
      const ObjectSpaceManifestList_SPtr_t& parent);

  std::shared_ptr<ObjectGroupList> parseObjectGroupList(
      QDataStream& ds, const FileNode_SPtr_t& fn,
      const std::shared_ptr<RevisionManifest>& parent);

  // Utility functions ---------------------------------------------------------


  /// parses a FileNodeChunkReference, creates and adds a Chunkable to the
  /// RevisionStoreFile and returns the Chunkable poitner
  template <class Chunkably>
  std::shared_ptr<Chunkably>
  parseFileNodeChunkReference(QDataStream& ds, const FileNode_SPtr_t& fn);

  /// parses a FileChunkReference64, creates and adds a Chunkable to the
  /// RevisionStoreFile and returns the Chunkable poitner
  template <class Chunkably>
  std::shared_ptr<Chunkably>
  parseFileChunkReference64(QDataStream& ds);

  /// parses a FileChunkReference64x32, creates and adds a Chunkable to the
  /// RevisionStoreFile and returns the Chunkable poitner
  template <class Chunkably>
  std::shared_ptr<Chunkably>
  parseFileChunkReference64x32(QDataStream& ds);

  /// parses a FileChunkReference32, creates and adds a Chunkable to the
  /// RevisionStoreFile and returns the Chunkable poitner
  template <class Chunkably>
  std::shared_ptr<Chunkably>
  parseFileChunkReference32(QDataStream& ds);

  /// Iterates through the list and checks whether chunk is already present
  /// at the specified location (stp, and cb must be equal) If it does not
  /// find an identical Chunkable in chunkList, it will return chunk;
  template <class Chunkably>
  std::shared_ptr<Chunkably> preventDuplicate(
      std::list<Chunkable_SPtr_t>& chunkList, std::shared_ptr<Chunkably> chunk);


  /// places chunk into chunkList by checking the initial stp of the chunks
  /// already in chunklist, will call preventDuplicate internally
  /// if it does find a duplicate, it will return it, otherwise it will return
  /// the specified chunk.
  template <class Chunkably>
  std::shared_ptr<Chunkably> insertChunkSorted(
      std::list<Chunkable_SPtr_t>& chunkList, std::shared_ptr<Chunkably> chunk);


  // copied from tika
  void registerRevisionManifestList(
      const ExtendedGUID& guid, const FileNode_SPtr_t& fn);
  void registerRevisionManifest(const FileNode_SPtr_t& fn);

  void registerAdditionalRevisionRole(
      const ExtendedGUID& guid, const quint32 revisionRole,
      const ExtendedGUID& gctxid);
};

} // namespace priv
} // namespace libmson

#endif // REVISIONSTOREFILEPARSER_H
