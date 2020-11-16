#ifndef UNKNOWNBLOB_H
#define UNKNOWNBLOB_H

#include "Chunkable.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

/// This chunk represents an empty section of given size within the
/// RevisionStoreFile
class UnknownBlob : public Chunkable {
private:
  QByteArray m_blob;

public:
  UnknownBlob(const quint64 initialStp = 0,
      const quint64 initialCb = 0);



  friend class RevisionStoreFileWriter;
  friend class RevisionStoreFileParser;


  QByteArray getBlob() const;
  void setBlob(const QByteArray& blob);

private:
  // Chunkable interface
  virtual quint64 cb() const override;
  virtual RevisionStoreChunkType getType() const override;
};

typedef std::shared_ptr<UnknownBlob> UnknownBlob_SPtr_t;
typedef std::weak_ptr<UnknownBlob> UnknownBlob_WPtr_t;

} // namespace priv
} // namespace libmson


#endif // UNKNOWNBLOB_H
