#ifndef ORPHANEDALLOCATION_H
#define ORPHANEDALLOCATION_H

#include "Chunkable.h"
#include <QByteArray>
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

/// This chunk represents an orphaned chunk which is not referenced by any other (valid Chunkable) within a RevisionStoreFile
class OrphanedAllocation : public Chunkable {
private:
  QByteArray m_blob;

public:
  OrphanedAllocation(const quint64 initialStp = 0, const quint64 initialCb = 0);

  QByteArray getBlob() const;
  void setBlob(const QByteArray& blob);

  friend class RevisionStoreFileParser;

private:
  // Chunkable interface
  virtual quint64 cb() const override;
  virtual RevisionStoreChunkType getType() const override;
};

typedef std::shared_ptr<OrphanedAllocation> OrphanedAllocation_SPtr_t;
typedef std::weak_ptr<OrphanedAllocation> OrphanedAllocation_WPtr_t;

} // namespace priv
} // namespace libmson


#endif // ORPHANEDALLOCATION_H
