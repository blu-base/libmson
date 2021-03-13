#ifndef STORAGEINDEXCELLMAPPING_H
#define STORAGEINDEXCELLMAPPING_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "dataTypes/CellId.h"
#include "dataTypes/LongExtGuid.h"
#include "interfaces/IStreamObject.h"

namespace libmson {
namespace fsshttpb {

class StorageIndexCellMapping : public IStreamObject {
private:
  CellId m_cellId;
  priv::ExtendedGUID m_extendedGuid;
  LongExtGuid m_serialNumber;

public:
  StorageIndexCellMapping()  = default;
  ~StorageIndexCellMapping() = default;

  CellId getCellId() const;
  void setCellId(const CellId& cellId);
  priv::ExtendedGUID getExtendedGuid() const;
  void setExtendedGuid(const priv::ExtendedGUID& extendedGuid);
  LongExtGuid getSerialNumber() const;
  void setSerialNumber(const LongExtGuid& serialNumber);

  // IStreamObject interface
protected:
  virtual quint64 strObjBody_cb() const override;
  virtual quint64 cbNextHeader() const override;

public:
  virtual StreamObjectType getType() const override
  {
    return StreamObjectType::StorageIndexCellMapping;
  }
  virtual void push_back(IStreamObject_SPtr_t& obj) override;
  virtual IStreamObj_It_t
  insert(IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj) override;


private:
  virtual void deserializeStrObj(QDataStream& ds) override;
  virtual void serializeStrObj(QDataStream& ds) const override;
};

typedef std::shared_ptr<StorageIndexCellMapping> StorageIndexCellMapping_SPtr_t;
typedef std::weak_ptr<StorageIndexCellMapping> StorageIndexCellMapping_WPtr_t;

} // namespace fsshttpb
} // namespace libmson

#endif // STORAGEINDEXCELLMAPPING_H
