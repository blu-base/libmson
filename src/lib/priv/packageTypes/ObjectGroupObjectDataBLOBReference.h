#ifndef OBJECTGROUPOBJECTDATABLOBREFERENCE_H
#define OBJECTGROUPOBJECTDATABLOBREFERENCE_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "dataTypes/CellId.h"
#include "interfaces/IStreamObject.h"

namespace libmson {
namespace fsshttpb {

class ObjectGroupObjectDataBLOBReference : public IStreamObject {
private:
  std::vector<priv::ExtendedGUID> m_objectExtGuidArray;
  std::vector<CellId> m_cellIdArray;
  priv::ExtendedGUID m_extendedGuid;


public:
  ObjectGroupObjectDataBLOBReference();
  std::vector<priv::ExtendedGUID> getObjectExtGuidArray() const;
  void setObjectExtGuidArray(
      const std::vector<priv::ExtendedGUID>& objectExtGuidArray);
  std::vector<CellId> getCellIdArray() const;
  void setCellIdArray(const std::vector<CellId>& cellIdArray);
  priv::ExtendedGUID getExtendedGuid() const;
  void setExtendedGuid(const priv::ExtendedGUID& extendedGuid);

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

typedef std::shared_ptr<ObjectGroupObjectDataBLOBReference>
    ObjectGroupObjectDataBLOBReference_SPtr_t;
typedef std::weak_ptr<ObjectGroupObjectDataBLOBReference>
    ObjectGroupObjectDataBLOBReference_WPtr_t;

} // namespace fsshttpb
} // namespace libmson
#endif // OBJECTGROUPOBJECTDATABLOBREFERENCE_H
