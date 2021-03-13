#ifndef STORAGEINDEXREVISIONMAPPING_H
#define STORAGEINDEXREVISIONMAPPING_H

#include <QtCore/qglobal.h>

#include <priv/commonTypes/ExtendedGUID.h>
#include"dataTypes/LongExtGuid.h"

#include "interfaces/IStreamObject.h"

namespace libmson {
namespace fsshttpb {

class StorageIndexRevisionMapping
    : public IStreamObject {
private:
  priv::ExtendedGUID m_revision;
  priv::ExtendedGUID m_extendedGuid;
  LongExtGuid m_serialNumber;

public:
  StorageIndexRevisionMapping();

  priv::ExtendedGUID getRevision() const;
  void setRevision(const priv::ExtendedGUID& revision);
  priv::ExtendedGUID getExtendedGuid() const;
  void setExtendedGuid(const priv::ExtendedGUID& extendedGuid);
  LongExtGuid getSerialNumber() const;
  void setSerialNumber(const LongExtGuid& serialNumber);


  // IStreamObject interface
protected:
  virtual quint64 strObjBody_cb() const override;
  virtual quint64 cbNextHeader() const override;

public:
  virtual StreamObjectType getType() const override{
    return StreamObjectType::StorageIndexRevisionMapping;
  }
  virtual void push_back(IStreamObject_SPtr_t& obj) override;
  virtual IStreamObj_It_t insert(IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj) override;

private:
  virtual void deserializeStrObj(QDataStream& ds) override;
  virtual void serializeStrObj(QDataStream& ds) const override;
};

typedef std::shared_ptr<StorageIndexRevisionMapping>
    StorageIndexRevisionMapping_SPtr_t;
typedef std::weak_ptr<StorageIndexRevisionMapping>
    StorageIndexRevisionMapping_WPtr_t;

} // namespace packStore
} // namespace libmson

#endif // STORAGEINDEXREVISIONMAPPING_H
