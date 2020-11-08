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

class RevisionStoreChunkContainer;

namespace libmson {
namespace priv {



class RevisionStoreFile {
public:
  RevisionStoreFile();

  std::list<RSChunkContainer_SPtr_t> getChunks() const { return m_chunks; };
  std::list<RSChunkContainer_SPtr_t>& chunks()  { return m_chunks; };

private:
  /// File name such as "Notebook.one". Does not include any path information.
  QString m_fileName;

  QDataStream m_ds;
  std::list<RSChunkContainer_SPtr_t> m_chunks;
  std::map<quint32, RSChunkContainer_WPtr_t> m_fileNodeListFragments;

  QMap<quint32, quint32> m_fileNodeCountMapping;
};



enum class RevisionStoreFileType { one, onetoc2, onepkg };

} // namespace priv
} // namespace libmson

#endif // REVISIONSTOREFILE2_H
