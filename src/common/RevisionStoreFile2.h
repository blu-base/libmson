#ifndef REVISIONSTOREFILE2_H
#define REVISIONSTOREFILE2_H

#include <QMap>
#include <QtCore/qglobal.h>
#include <list>
#include <map>
#include <memory>

#include <QDataStream>

#include "RevisionStoreChunk.h"
#include "chunks/Chunkable.h"
#include "commonTypes/FileChunkReference32.h"
#include "commonTypes/FileChunkReference64.h"
#include "commonTypes/FileChunkReference64x32.h"

class RevisionStoreChunk;

namespace libmson {

class RevisionStoreFile
{
public:
  RevisionStoreFile();

  /// returns true if sucessfull
  /// \todo document used open modes
  bool open(const QString& fileName);

  QString fileName() const;

  /// returns true, if the given fileName is a valid name.
  bool setFileName(const QString& fileName);

  /// Write RevisionStoreFile into the saved fileName
  /// Returns true if writing was sucessful
  bool write();

  /// Write RevisionStoreFile into the given fileName
  /// Returns true if writing was sucessful
  bool write(const QString& fileName);

  /// parses the opened file again
  /// returns true if sucessfull (same as open)
  /// \todo will need to deal with mismatched file and in-memory versions
  // bool parse();

  std::list<std::shared_ptr<RevisionStoreChunkContainer>>& getChunks()
  {
    return m_chunks;
  };

private:
  /// File name such as "Notebook.one". Does not include any path information.
  QString m_fileName;

  QDataStream m_ds;
  std::list<std::shared_ptr<RevisionStoreChunkContainer>> m_chunks;
  std::map<quint32, std::weak_ptr<RevisionStoreChunkContainer>> m_fileNodeListFragments;

  QMap<quint32, quint32> m_fileNodeCountMapping;

private:
  bool parseHeader();
  bool writeHeader(QDataStream& ds);

  bool writeChunk(std::shared_ptr<RevisionStoreChunkContainer> chunk);

  bool writeFreeChunkListFragment(std::shared_ptr<RevisionStoreChunkContainer> chunk);
  bool writeFreeChunk(std::shared_ptr<RevisionStoreChunkContainer> chunk);

  bool writeFileNodeListFragment(std::shared_ptr<RevisionStoreChunkContainer> chunk);
  std::shared_ptr<RevisionStoreChunkContainer> deserializeFileNodeListFragment(
    QDataStream& ds,
    const quint64 stp,
    const quint64 cb);

  bool deserializeFileNodeListFragment(
    QDataStream& ds,
    std::shared_ptr<RevisionStoreChunkContainer> chunk);

  bool writeFileNode(std::shared_ptr<RevisionStoreChunkContainer> chunk);
  std::shared_ptr<RevisionStoreChunkContainer> deserializeFileNode(
    QDataStream& ds,
    const quint64 stp,
    std::weak_ptr<RevisionStoreChunkContainer> parent);

  /// returns UINT64_MAX if chunk is empty´
  quint64 stpFromChunk(std::weak_ptr<RevisionStoreChunkContainer> chunk);
  quint64 stpTillIterator(
    const std::list<std::shared_ptr<RevisionStoreChunkContainer>>& list,
    const std::weak_ptr<RevisionStoreChunkContainer>& chunk);

  MSONcommon::FileChunkReference64x32 getFcr64x32FromChunk(
    std::weak_ptr<RevisionStoreChunkContainer> chunk);

  MSONcommon::FileChunkReference64 getFcr64FromChunk(
    std::weak_ptr<RevisionStoreChunkContainer> chunk);

  void insertChunkSorted(std::shared_ptr<RevisionStoreChunkContainer> chunk);
};

enum class RevisionStoreFileType
{
  one,
  onetoc2,
  onepkg
};

} // namespace libmson

#endif // REVISIONSTOREFILE2_H
