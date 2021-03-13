#ifndef STORAGEMANIFESTROOTDECLARE_H
#define STORAGEMANIFESTROOTDECLARE_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "dataTypes/CellId.h"
#include "interfaces/IStreamObject.h"

namespace libmson {
namespace fsshttpb {

class StorageManifestRootDeclare : public IStreamObject {
private:
  priv::ExtendedGUID m_extendedGuid;
  CellId m_cellId;

public:
  StorageManifestRootDeclare();
  ~StorageManifestRootDeclare() = default;

  priv::ExtendedGUID getExtendedGuid() const;
  void setExtendedGuid(const priv::ExtendedGUID& extendedGuid);
  CellId getCellId() const;
  void setCellId(const CellId& cellId);

  // IStreamObject interface
protected:
  virtual quint64 strObjBody_cb() const override;
  virtual quint64 cbNextHeader() const override;

public:
  virtual StreamObjectType getType() const override;
  virtual void push_back(IStreamObject_SPtr_t& obj) override;
  virtual IStreamObj_It_t
  insert(IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj) override;

private:
  virtual void deserializeStrObj(QDataStream& ds) override;
  virtual void serializeStrObj(QDataStream& ds) const override;
};

typedef std::shared_ptr<StorageManifestRootDeclare>
    StorageManifestRootDeclare_SPtr_t;
typedef std::weak_ptr<StorageManifestRootDeclare>
    StorageManifestRootDeclare_WPtr_t;

} // namespace fsshttpb
} // namespace libmson

#endif // STORAGEMANIFESTROOTDECLARE_H
