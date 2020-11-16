#ifndef CHUNKABLE_H
#define CHUNKABLE_H


#include <QtCore/qglobal.h>

#include <QMetaEnum>
#include <memory>

namespace libmson {
namespace priv {

enum class RevisionStoreChunkType {
  RevisionStoreFileHeader,
  FileNodeListFragment,
  FileNode,
  FreeChunkListFragment,
  FreeChunk,
  TransactionLogFragment,
  FileDataStoreObject,
  ObjectSpaceObjectPropSet,
  ObjectInfoDependencyOverrideData,
  EncryptedData,

  UnknownBlob,

  Invalid
};

class Chunkable {
protected:
  quint64 m_initialStp;
  quint64 m_initialCb;

  bool m_isParsed = false;

  virtual quint64 cb() const                     = 0;
  virtual RevisionStoreChunkType getType() const = 0;

public:
  Chunkable(const quint64 initialStp = 0, const quint64 initialCb = 0);

  quint64 getInitialStp() const;
  quint64 getInitialCb() const;

  /// returns the size in number of bytes this chunk would have in a file.
  /// If the chunk has not been parsed, this function returns the m_initialCb
  /// value.
  quint64 getSizeInFile() const;
  RevisionStoreChunkType type() const;
  static QString typeString(RevisionStoreChunkType type);


  bool isParsed() const;

  friend class RevisionStoreFileParser;
};

typedef std::shared_ptr<Chunkable> Chunkable_SPtr_t;
typedef std::weak_ptr<Chunkable> Chunkable_WPtr_t;


} // namespace priv
} // namespace libmson


#endif // CHUNKABLE_H
