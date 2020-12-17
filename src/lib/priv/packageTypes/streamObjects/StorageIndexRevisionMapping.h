#ifndef STORAGEINDEXREVISIONMAPPING_H
#define STORAGEINDEXREVISIONMAPPING_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/CompactExtGuid.h"
#include "SeriallyNumbered.h"
#include "StreamObject.h"

namespace libmson {
namespace packStore {
namespace streamObj {


class StorageIndexRevisionMapping
    : public StreamObject
    , public SeriallyNumbered
    , public libmson::priv::IStreamable {
private:
  CompactExtGuid m_revision;

  CompactExtGuid m_extendedGuid;

public:
  StorageIndexRevisionMapping();

  CompactExtGuid getRevision() const;
  void setRevision(const CompactExtGuid& revision);

  CompactExtGuid getExtendedGuid() const;
  void setExtendedGuid(const CompactExtGuid& extendedGuid);

  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;

  // StreamObject interface
protected:
  virtual quint64 body_cb() const override;

public:
  virtual StreamObjectType getType() const override;
};

typedef std::shared_ptr<StorageIndexRevisionMapping>
    StorageIndexRevisionMapping_SPtr_t;
typedef std::weak_ptr<StorageIndexRevisionMapping>
    StorageIndexRevisionMapping_WPtr_t;

} // namespace streamObj
} // namespace packStore
} // namespace libmson

#endif // STORAGEINDEXREVISIONMAPPING_H
