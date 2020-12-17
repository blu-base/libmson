#ifndef CELLMANIFESTCURRENTREVISION_H
#define CELLMANIFESTCURRENTREVISION_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/CompactExtGuid.h"
#include "StreamObject.h"

namespace libmson {
namespace packStore {
namespace streamObj {

class CellManifestCurrentRevision
    : public StreamObject
    , public libmson::priv::IStreamable {
private:
  CompactExtGuid m_extendedGuid;

public:
  CellManifestCurrentRevision();

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

typedef std::shared_ptr<CellManifestCurrentRevision>
    CellManifestCurrentRevision_SPtr_t;
typedef std::weak_ptr<CellManifestCurrentRevision>
    CellManifestCurrentRevision_WPtr_t;

} // namespace streamObj
} // namespace packStore
} // namespace libmson

#endif // CELLMANIFESTCURRENTREVISION_H
