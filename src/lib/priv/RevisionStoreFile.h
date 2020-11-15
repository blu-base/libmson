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

#include "commonTypes/FileChunkReference32.h"
#include "commonTypes/FileChunkReference64.h"
#include "commonTypes/FileChunkReference64x32.h"

#include "commonTypes/ExtendedGUID.h"

class RevisionStoreChunkContainer;

namespace libmson {
namespace priv {


class RevisionStoreFile {
public:
  RevisionStoreFile() = default;

  std::list<Chunkable_SPtr_t> getChunks() const { return m_chunks; };
  std::list<Chunkable_SPtr_t>& chunks() { return m_chunks; };


  /// returns the ExtendedGUID stored in the ObjectSpaceManifestRootFND of the
  /// FileNodeListRoot
  ExtendedGUID getObjectSpaceManifestRoot();


  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;

private:
  /// File name such as "Notebook.one". Does not include any path information.
  QString m_fileName;

  QDataStream m_ds;
  std::list<Chunkable_SPtr_t> m_chunks;
  std::map<quint32, FileNodeListFragment_WPtr_t> m_fileNodeListFragments;

  std::vector<FileNodeListFragment_WPtr_t> m_rootFileNodeList;
  std::vector<TransactionLogFragment_WPtr_t> m_transactionLogs;
  std::vector<FileNodeListFragment_WPtr_t> m_hashedChunkListFragments;

  Chunkable_WPtr_t m_objectSpaceManifestRoot;
  std::vector<FileNodeListFragment_WPtr_t> m_objectSpaceManifests;
  //  std::vector<std::shared_ptr<ObjectSpaceManifestList>>
  //      m_objectSpaceManifestList;


  FileNode_WPtr_t m_fileDataStoreListReference;

  QMap<quint32, quint32> m_fileNodeCountMapping;
};


enum class RevisionStoreFileType { one, onetoc2, onepkg };

} // namespace priv
} // namespace libmson

#endif // REVISIONSTOREFILE2_H
