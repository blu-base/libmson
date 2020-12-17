#ifndef STORAGEMANIFESTROOTDECLARE_H
#define STORAGEMANIFESTROOTDECLARE_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/CellId.h"
#include "../../commonTypes/CompactExtGuid.h"
#include "StreamObject.h"

namespace libmson {
namespace packStore {
namespace streamObj {

class StorageManifestRootDeclare
    : public StreamObject
    , public libmson::priv::IStreamable {
private:
  CompactExtGuid m_extendedGuid;
  CellId m_cellId;

public:
  StorageManifestRootDeclare();
  ~StorageManifestRootDeclare() = default;


  CompactExtGuid getExtendedGuid() const;
  void setExtendedGuid(const CompactExtGuid& extendedGuid);
  CellId getCellId() const;
  void setCellId(const CellId& cellId);

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

typedef std::shared_ptr<StorageManifestRootDeclare>
    StorageManifestRootDeclare_SPtr_t;
typedef std::weak_ptr<StorageManifestRootDeclare>
    StorageManifestRootDeclare_WPtr_t;

} // namespace streamObj
} // namespace packStore
} // namespace libmson

#endif // STORAGEMANIFESTROOTDECLARE_H
