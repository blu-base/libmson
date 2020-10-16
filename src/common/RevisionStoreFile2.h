#ifndef REVISIONSTOREFILE2_H
#define REVISIONSTOREFILE2_H

#include <QtCore/qglobal.h>
#include <list>
#include <memory>

namespace libmson {

class RevisionStoreChunk;
class Chunkable;

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

private:
  std::list<RevisionStoreChunk> m_chunks;
};

enum class RevisionStoreChunkType {

};

class RevisionStoreChunk {
private:
  qint64 m_initialStp;

  std::shared_ptr<Chunkable> m_chunkable;

  std::weak_ptr<RevisionStoreFile> m_parent;

public:
  RevisionStoreChunk(std::shared_ptr<Chunkable> chunkable,
                     const RevisionStoreChunkType chunktype,
                     const qint64 initialLocationInFile,
                     std::weak_ptr<RevisionStoreFile> parent);

  std::shared_ptr<Chunkable> getChunk();

  RevisionStoreChunkType getType();

  qint64 stp();
  qint64 size();
};

template <RevisionStoreChunkType ChunkType> class Chunkable {
public:
  virtual qint64 getSize() const = 0;
  template<>
  virtual RevisionStoreChunkType getType() { return ChunkType; }
};

} // namespace libmson

#endif // REVISIONSTOREFILE2_H
