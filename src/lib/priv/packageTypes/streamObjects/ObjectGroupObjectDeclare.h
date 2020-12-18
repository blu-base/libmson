#ifndef OBJECTGROUPOBJECTDECLARE_H
#define OBJECTGROUPOBJECTDECLARE_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/CompactExtGuid.h"
#include "../../commonTypes/CompactUInt64.h"
#include "StreamObject.h"

namespace libmson {
namespace packStore {
namespace streamObj {

class ObjectGroupObjectDeclare
    : public StreamObject
    , public libmson::priv::IStreamable {
private:
  CompactExtGuid m_extendedGuid;
  quint64 m_partitionId;

  quint64 m_dataSize;
  quint64 m_objectReferencesCount;
  quint64 m_cellReferencesCount;

public:
  ObjectGroupObjectDeclare();

  CompactExtGuid getExtendedGuid() const;
  void setExtendedGuid(const CompactExtGuid& extendedGuid);
  quint64 getPartitionId() const;
  void setPartitionId(const quint64& partitionId);
  quint64 getDataSize() const;
  void setDataSize(const quint64& dataSize);
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


typedef std::shared_ptr<ObjectGroupObjectDeclare>
    ObjectGroupObjectDeclare_SPtr_t;
typedef std::weak_ptr<ObjectGroupObjectDeclare> ObjectGroupObjectDeclare_WPtr_t;

} // namespace streamObj
} // namespace packStore
} // namespace libmson


#endif // OBJECTGROUPOBJECTDECLARE_H
