#ifndef OBJECTGROUPOBJECTDECLARE_H
#define OBJECTGROUPOBJECTDECLARE_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "interfaces/IStreamObject.h"

namespace libmson {
namespace fsshttpb {

class ObjectGroupObjectDeclare : public IStreamObject {
private:
  priv::ExtendedGUID m_extendedGuid;
  quint64 m_partitionId;

  quint64 m_dataSize;
  quint64 m_objectReferencesCount;
  quint64 m_cellReferencesCount;

public:
  ObjectGroupObjectDeclare();

  priv::ExtendedGUID getExtendedGuid() const;
  void setExtendedGuid(const priv::ExtendedGUID& extendedGuid);
  quint64 getPartitionId() const;
  void setPartitionId(const quint64& partitionId);
  quint64 getDataSize() const;
  void setDataSize(const quint64& dataSize);
  quint64 getObjectReferencesCount() const;
  void setObjectReferencesCount(const quint64& objectReferencesCount);
  quint64 getCellReferencesCount() const;
  void setCellReferencesCount(const quint64& cellReferencesCount);

  // IStreamObject interface
protected:
  virtual quint64 strObjBody_cb() const override;
  virtual quint64 cbNextHeader() const override;

public:
  virtual StreamObjectType getType() const override;
  virtual void push_back(IStreamObject_SPtr_t& obj) override;
  virtual IStreamObj_It_t insert(IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj) override;

private:
  virtual void deserializeStrObj(QDataStream& ds) override;
  virtual void serializeStrObj(QDataStream& ds) const override;
};


typedef std::shared_ptr<ObjectGroupObjectDeclare>
    ObjectGroupObjectDeclare_SPtr_t;
typedef std::weak_ptr<ObjectGroupObjectDeclare> ObjectGroupObjectDeclare_WPtr_t;

} // namespace fsshttpb
} // namespace libmson


#endif // OBJECTGROUPOBJECTDECLARE_H
