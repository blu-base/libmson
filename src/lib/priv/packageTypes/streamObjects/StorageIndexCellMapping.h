#ifndef STORAGEINDEXCELLMAPPING_H
#define STORAGEINDEXCELLMAPPING_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/CellId.h"
#include "SeriallyNumbered.h"
#include "StreamObject.h"

namespace libmson {
namespace packStore {
namespace streamObj {

class StorageIndexCellMapping
    : public StreamObject
    , public SeriallyNumbered
    , public libmson::priv::IStreamable {
private:
  CellId m_cellId;
  CompactExtGuid m_extendedGuid;

public:
  StorageIndexCellMapping();
  ~StorageIndexCellMapping() = default;

  CellId getCellId() const;
  void setCellId(const CellId& cellId);
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

typedef std::shared_ptr<StorageIndexCellMapping> StorageIndexCellMapping_SPtr_t;
typedef std::weak_ptr<StorageIndexCellMapping> StorageIndexCellMapping_WPtr_t;

} // namespace streamObj
} // namespace packStore
} // namespace libmson

#endif // STORAGEINDEXCELLMAPPING_H
