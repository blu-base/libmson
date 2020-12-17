#ifndef STORAGEINDEXMANIFESTMAPPING_H
#define STORAGEINDEXMANIFESTMAPPING_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/CompactExtGuid.h"
#include "SeriallyNumbered.h"
#include "StreamObject.h"

namespace libmson {
namespace packStore {
namespace streamObj {


class StorageIndexManifestMapping
    : public StreamObject
    , public SeriallyNumbered
    , public libmson::priv::IStreamable {
private:
  CompactExtGuid m_extendedGuid;

public:
  StorageIndexManifestMapping();
  ~StorageIndexManifestMapping() = default;

  CompactExtGuid getExtendedGuid() const;
  void setExtendedGuid(const CompactExtGuid& extendedGuid);

  // StreamObject interface
protected:
  virtual quint64 body_cb() const override;

public:
  virtual StreamObjectType getType() const override;

  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

typedef std::shared_ptr<StorageIndexManifestMapping>
    StorageIndexManifestMapping_SPtr_t;
typedef std::weak_ptr<StorageIndexManifestMapping>
    StorageIndexManifestMapping_WPtr_t;

} // namespace streamObj
} // namespace packStore
} // namespace libmson

#endif // STORAGEINDEXMANIFESTMAPPING_H
