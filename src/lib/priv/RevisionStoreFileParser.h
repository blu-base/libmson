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


namespace libmson {
namespace priv {

class RevisionStoreFileParser {
private:
  QDataStream& m_ds;
  std::shared_ptr<RevisionStoreFile> m_file;

public:
  RevisionStoreFileParser(QDataStream& inputStream, const QString& fileName);


  std::shared_ptr<RevisionStoreFile> parse();

private:
  // parsers

  void parseChunk(QDataStream& ds, Chunkable_SPtr_t chunk);


  void parseEncryptedData(QDataStream& ds, EncryptedData_WPtr_t chunk);


  void parseFileDataStoreObject(
      QDataStream& ds, FileDataStoreObject_WPtr_t fileData);


  FileNode_SPtr_t parseFileNode(
      QDataStream& ds, const quint64 stp, FileNodeListFragment_WPtr_t parent);

  FileNode_SPtr_t parseFileNode(QDataStream& ds, FileNode_SPtr_t fileNode);

  /// parses a fragment. Returns a RSChunkContainer_SPtr_t if there is a next
  /// Fragment specified That RSChunkContainer_SPtr_t is not inserted to any
  /// std::list<RSChunkContainer_SPtr_t>& chunkList. This has to be done by
  /// calling method.
  FileNodeListFragment_SPtr_t parseFileNodeListFragment(
      QDataStream& ds, FileNodeListFragment_SPtr_t fragment);

  /// parses a fragment tree. Returns a RSChunkContainer_WPtr_t list
  std::vector<FileNodeListFragment_WPtr_t>
  parseFileNodeList(QDataStream& ds, FileNodeListFragment_WPtr_t firstFragment);


  /// parses the FreeChunkListFrragments and adds ChunkContainer to m_file
  void parseFreeChunkListFragments(
      QDataStream& ds, FreeChunkListFragment_WPtr_t firstFragment);

  void parseFreeChunk(QDataStream& ds, FreeChunk_SPtr_t freeChunk);

  void parseObjectInfoDependencyOverrideData(
      QDataStream& ds, ObjectInfoDependencyOverrideData_SPtr_t objectInfo);

  ObjectSpaceObjectPropSet_SPtr_t parseObjectSpaceObjectPropSet(
      QDataStream& ds, ObjectSpaceObjectPropSet_SPtr_t objectPropSet);

  /// parses the header, adds the containers to m_file and returns the pointer
  /// to the header container
  RevisionStoreFileHeader_WPtr_t parseRevisionStoreFileHeader(QDataStream& ds);

  bool parseTransactionLogFragment(
      QDataStream& ds, TransactionLogFragment_SPtr_t firstFragment);


  void parseUnknownBlob(QDataStream& ds, UnknownBlob_SPtr_t unknownBlob);

  /// Iterates through the list and checks whether chunk is already present at
  /// the specified location (stp, and cb must be equal)
  /// If it does not find an identical Chunkable in chunkList, it will return
  /// chunk;
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
};

} // namespace priv
} // namespace libmson

#endif // REVISIONSTOREFILEPARSER_H
