#ifndef REVISIONSTOREFILE2_H
#define REVISIONSTOREFILE2_H

#include <QMap>
#include <QtCore/qglobal.h>
#include <list>
#include <map>
#include <memory>

#include <QDataStream>

#include "chunkables/Chunkable.h"
#include "chunkables/RevisionStoreChunkContainer.h"
#include "commonTypes/FileChunkReference32.h"
#include "commonTypes/FileChunkReference64.h"
#include "commonTypes/FileChunkReference64x32.h"

#include "commonTypes/ExtendedGUID.h"

class RevisionStoreChunkContainer;

namespace libmson {
namespace priv {


class RevisionStoreFile {
public:
  RevisionStoreFile();

  std::list<RSChunkContainer_SPtr_t> getChunks() const { return m_chunks; };
  std::list<RSChunkContainer_SPtr_t>& chunks() { return m_chunks; };


  /// returns the ExtendedGUID stored in the ObjectSpaceManifestRootFND of the
  /// FileNodeListRoot
  ExtendedGUID getObjectSpaceManifestRoot();


  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;

private:
  /// File name such as "Notebook.one". Does not include any path information.
  QString m_fileName;

  QDataStream m_ds;
  std::list<RSChunkContainer_SPtr_t> m_chunks;
  std::map<quint32, RSChunkContainer_WPtr_t> m_fileNodeListFragments;

  std::vector<RSChunkContainer_WPtr_t> m_rootFileNodeList;
  std::vector<RSChunkContainer_WPtr_t> m_transactionLogs;
  std::vector<RSChunkContainer_WPtr_t> m_hashedChunkListFragments;

  RSChunkContainer_WPtr_t m_objectSpaceManifestRoot;
  std::vector<std::vector<RSChunkContainer_WPtr_t>> m_objectSpaceManifests;
  //  std::vector<std::shared_ptr<ObjectSpaceManifestList>>
  //      m_objectSpaceManifestList;


  RSChunkContainer_WPtr_t m_fileDataStoreListReference;

  QMap<quint32, quint32> m_fileNodeCountMapping;
};


enum class RevisionStoreFileType { one, onetoc2, onepkg };

} // namespace priv
} // namespace libmson

#endif // REVISIONSTOREFILE2_H
