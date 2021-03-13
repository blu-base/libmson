#ifndef OBJECTGROUPOBJECTDATABLOBDECLARATION_H
#define OBJECTGROUPOBJECTDATABLOBDECLARATION_H

#include <QtCore/qglobal.h>

#include "interfaces/IStreamObject.h"
#include "../commonTypes/ExtendedGUID.h"

namespace libmson {
namespace fsshttpb {

class ObjectGroupObjectDataBLOBDeclaration : public IStreamObject{
private:
  priv::ExtendedGUID m_extendedGuid;
  priv::ExtendedGUID m_blobExtendedGuid;

  quint64 m_partitionId;
  quint64 m_objectReferencesCount;
  quint64 m_cellReferencesCount;

public:
  ObjectGroupObjectDataBLOBDeclaration();
  priv::ExtendedGUID getExtendedGuid() const;
  void setExtendedGuid(const priv::ExtendedGUID& extendedGuid);
  priv::ExtendedGUID getBlobExtendedGuid() const;
  void setBlobExtendedGuid(const priv::ExtendedGUID& blobExtendedGuid);
  quint64 getPartitionId() const;
  void setPartitionId(const quint64& partitionId);
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


typedef std::shared_ptr<ObjectGroupObjectDataBLOBDeclaration>
ObjectGroupObjectDataBLOBDeclaration_SPtr_t;
typedef std::weak_ptr<ObjectGroupObjectDataBLOBDeclaration>
    ObjectGroupObjectDataBLOBDeclaration_WPtr_t;

} // namespace packStore
} // namespace libmson

#endif // OBJECTGROUPOBJECTDATABLOBDECLARATION_H
