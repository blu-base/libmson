#ifndef REVISIONSTOREFILE2_H
#define REVISIONSTOREFILE2_H

#include <QMap>
#include <QtCore/qglobal.h>
#include <list>
#include <map>
#include <memory>

#include <QDataStream>

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

#include "commonTypes/FileChunkReference32.h"
#include "commonTypes/FileChunkReference64.h"
#include "commonTypes/FileChunkReference64x32.h"

#include "commonTypes/ExtendedGUID.h"

#include "ObjectSpaceManifestList.h"


namespace libmson {
namespace priv {


class RevisionStoreFile {
public:
  RevisionStoreFile() = default;

  std::list<Chunkable_SPtr_t> getChunks() const { return m_chunks; };
  std::list<Chunkable_SPtr_t>& chunks() { return m_chunks; };
  void setChunks(const std::list<Chunkable_SPtr_t>& chunks);

  /// returns the ExtendedGUID stored in the ObjectSpaceManifestRootFND of the
  /// FileNodeListRoot
  ExtendedGUID getObjectSpaceManifestRoot();


  friend class RevisionStoreFileParser;

  QString getFileName() const;
  void setFileName(const QString& fileName);

  RevisionStoreFileHeader_SPtr_t getHeader() const;
  void setHeader(const RevisionStoreFileHeader_SPtr_t& header);


  std::vector<TransactionLogFragment_WPtr_t> getTransactionLogs() const;
  void setTransactionLogs(
      const std::vector<TransactionLogFragment_WPtr_t>& transactionLogs);

  FileNode_WPtr_t getFileDataStoreListReference() const;
  void setFileDataStoreListReference(
      const FileNode_WPtr_t& fileDataStoreListReference);

private:
  /// File name such as "Notebook.one". Does not include any path information.
  QString m_fileName;

  bool m_isEncrypted = false;

  RevisionStoreFileHeader_SPtr_t m_header;


  std::list<Chunkable_SPtr_t> m_chunks;
  std::map<quint32, FileNodeListFragment_WPtr_t> m_fileNodeListFragments;

  std::vector<FileNodeListFragment_WPtr_t> m_rootFileNodeList;

  std::vector<TransactionLogFragment_WPtr_t> m_transactionLogs;

  std::vector<FileNodeListFragment_WPtr_t> m_hashedChunkListFragments;

  FileNode_SPtr_t m_objectSpaceManifestRootFN;

  std::map<ExtendedGUID, ObjectSpaceManifestList_SPtr_t>
      m_objectSpaceManifestLists;

  //  std::vector<std::shared_ptr<ObjectSpaceManifestList>>
  //      m_objectSpaceManifestList;


  FileNode_WPtr_t m_fileDataStoreListReference;

  QMap<quint32, quint32> m_fileNodeCountMapping;


  /// A list of Chunkables which have not been parsed during walking the
  /// RootNodeFileList and its references The list ist filled by the
  /// "brute-force" loop in the main parse method of the
  /// RevisionStoreFileParser. At some point this list should be empty, since
  /// all Chunkables should be parsed in and ordered way.
  std::list<Chunkable_WPtr_t> m_undiscovered;


  /// this is a list of binary blobs which do not seem to be referenced
  /// somewhere, or are missed possibly due to bugs in this library.
  std::list<UnknownBlob_WPtr_t> m_unkownBlobs;
};


enum class RevisionStoreFileType { one, onetoc2, onepkg };

} // namespace priv
} // namespace libmson

#endif // REVISIONSTOREFILE2_H
