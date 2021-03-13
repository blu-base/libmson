#ifndef OBJECTGROUPOBJECTDATA_H
#define OBJECTGROUPOBJECTDATA_H

#include <QtCore/qglobal.h>

#include <QByteArray>

#include "../commonTypes/ExtendedGUID.h"
#include "dataTypes/CellId.h"
#include "interfaces/IStreamObject.h"

namespace libmson {
namespace fsshttpb {

class ObjectGroupObjectData : public IStreamObject {

private:
  std::vector<priv::ExtendedGUID> m_extendedGuidArray;
  std::vector<CellId> m_cellIdArray;
  QByteArray m_data;

public:
  ObjectGroupObjectData();

  std::vector<priv::ExtendedGUID> getExtendedGuidArray() const;
  void setExtendedGuidArray(
      const std::vector<priv::ExtendedGUID>& extendedGuidArray);
  std::vector<CellId> getCellIdArray() const;
  void setCellIdArray(const std::vector<CellId>& cellIdArray);
  QByteArray getData() const;
  void setData(const QByteArray& data);

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

typedef std::shared_ptr<ObjectGroupObjectData> ObjectGroupObjectData_SPtr_t;
typedef std::weak_ptr<ObjectGroupObjectData> ObjectGroupObjectData_WPtr_t;

} // namespace fsshttpb
} // namespace libmson

#endif // OBJECTGROUPOBJECTDATA_H
