#ifndef CHUNKABLE_H
#define CHUNKABLE_H

#include <QtCore/qglobal.h>
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

  OrphanedAllocation,

  Invalid
};

class Chunkable {
protected:
  const quint64 m_initialStp;
  const quint64 m_initialCb;

  quint64 m_cb;

  bool m_isParsed = false;

  /// indicates whether m_cb needs to be recalculated, since this value is
  /// needed often during writing
  bool m_isChanged = false;

  virtual quint64 cb() const                     = 0;
  virtual RevisionStoreChunkType getType() const = 0;

public:
  Chunkable(const quint64 initialStp = 0, const quint64 initialCb = 0);

  quint64 getInitialStp() const;
  quint64 getInitialCb() const;

  /// returns the size in number of bytes this chunk would have in a file.
  /// If the chunk has not been parsed, this function returns the m_initialCb
  /// value.
  /// If the chunk has been changed, it will recalculate this Chunkables size,
  /// store it in m_cb and return it. Otherwise it will return the already
  /// stored m_cb
  quint64 getSizeInFile();
  RevisionStoreChunkType type() const;
  static QString typeString(RevisionStoreChunkType type);


  bool isParsed() const;

  /// sets the isChanged Flag to true.
  void setIsChanged();
  bool isChanged() const;

  friend class RevisionStoreFileParser;
};

typedef std::shared_ptr<Chunkable> Chunkable_SPtr_t;
typedef std::weak_ptr<Chunkable> Chunkable_WPtr_t;


} // namespace priv
} // namespace libmson


#endif // CHUNKABLE_H
