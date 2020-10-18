#ifndef REVISIONSTOREFILE2_H
#define REVISIONSTOREFILE2_H

#include <QtCore/qglobal.h>
#include <list>
#include <memory>

#include <QDataStream>

#include "RevisionStoreChunk.h"
#include "chunks/Chunkable.h"
#include "commonTypes/FileChunkReference32.h"
#include "commonTypes/FileChunkReference64x32.h"
#include "commonTypes/FileChunkReference64.h"

class RevisionStoreChunk;

namespace libmson {

class RevisionStoreFile {
public:
  RevisionStoreFile();

  /// returns true if sucessfull
  /// \todo document used open modes
  bool open(const QString &fileName);

  QString fileName() const;

  /// returns true, if the given fileName is a valid name.
  bool setFileName(const QString &fileName);

  /// Write RevisionStoreFile into the saved fileName
  /// Returns true if writing was sucessful
  bool write();

  /// Write RevisionStoreFile into the given fileName
  /// Returns true if writing was sucessful
  bool write(const QString &fileName);

  /// parses the opened file again
  /// returns true if sucessfull (same as open)
  /// \todo will need to deal with mismatched file and in-memory versions
  // bool parse();

  std::list<std::shared_ptr<RevisionStoreChunk>> &getChunks() {
    return m_chunks;
  };

private:
  /// File name such as "Notebook.one". Does not include any path information.
  QString m_fileName;

  QDataStream m_ds;
  std::list<std::shared_ptr<RevisionStoreChunk>> m_chunks;

  bool parseHeader();
  bool writeHeader(QDataStream &ds);

  bool writeChunk(std::shared_ptr<RevisionStoreChunk> chunk);

  bool writeFreeChunkListFragment(std::shared_ptr<RevisionStoreChunk> chunk);
  bool writeFreeChunk(std::shared_ptr<RevisionStoreChunk> chunk);

  /// returns UINT64_MAX if chunk is empty´
  quint64 stpFromChunk(std::weak_ptr<RevisionStoreChunk> chunk);

  MSONcommon::FileChunkReference64x32
  getFcr64x32FromChunk(std::weak_ptr<RevisionStoreChunk> chunk);

  MSONcommon::FileChunkReference64
  getFcr64FromChunk(std::weak_ptr<RevisionStoreChunk> chunk);

  void insertChunkSorted(std::shared_ptr<RevisionStoreChunk> chunk);
};

enum class RevisionStoreFileType { one, onetoc2, onepkg };

} // namespace libmson

#endif // REVISIONSTOREFILE2_H
