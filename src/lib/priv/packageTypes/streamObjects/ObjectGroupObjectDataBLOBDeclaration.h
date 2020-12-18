#ifndef OBJECTGROUPOBJECTDATABLOBDECLARATION_H
#define OBJECTGROUPOBJECTDATABLOBDECLARATION_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/CompactExtGuid.h"
#include "../../commonTypes/CompactUInt64.h"
#include "StreamObject.h"

namespace libmson {
namespace packStore {
namespace streamObj {


class ObjectGroupObjectDataBLOBDeclaration
    : public StreamObject
    , public libmson::priv::IStreamable {
private:
  CompactExtGuid m_extendedGuid;
  CompactExtGuid m_blobExtendedGuid;

  quint64 m_partitionId;
  quint64 m_objectReferencesCount;
  quint64 m_cellReferencesCount;

public:
  ObjectGroupObjectDataBLOBDeclaration();
  CompactExtGuid getExtendedGuid() const;
  void setExtendedGuid(const CompactExtGuid& extendedGuid);
  CompactExtGuid getBlobExtendedGuid() const;
  void setBlobExtendedGuid(const CompactExtGuid& blobExtendedGuid);
  quint64 getPartitionId() const;
  void setPartitionId(const quint64& partitionId);
  quint64 getObjectReferencesCount() const;
  void setObjectReferencesCount(const quint64& objectReferencesCount);
  quint64 getCellReferencesCount() const;
  void setCellReferencesCount(const quint64& cellReferencesCount);

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


typedef std::shared_ptr<ObjectGroupObjectDataBLOBDeclaration>
ObjectGroupObjectDataBLOBDeclaration_SPtr_t;
typedef std::weak_ptr<ObjectGroupObjectDataBLOBDeclaration>
    ObjectGroupObjectDataBLOBDeclaration_WPtr_t;

} // namespace streamObj
} // namespace packStore
} // namespace libmson

#endif // OBJECTGROUPOBJECTDATABLOBDECLARATION_H
