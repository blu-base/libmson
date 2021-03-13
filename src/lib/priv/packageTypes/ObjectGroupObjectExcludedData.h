#ifndef OBJECTGROUPOBJECTEXCLUDEDDATA_H
#define OBJECTGROUPOBJECTEXCLUDEDDATA_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "dataTypes/CellId.h"
#include "interfaces/IStreamObject.h"

namespace libmson {
namespace fsshttpb {

class ObjectGroupObjectExcludedData : public IStreamObject {
private:
  std::vector<priv::ExtendedGUID> m_extendedGuidArray;
  std::vector<CellId> m_cellIdArray;

  /// \todo unsure if dataSize is directly followed by the excludeData
  quint64 m_dataSize;

public:
  ObjectGroupObjectExcludedData();

  std::vector<priv::ExtendedGUID> getExtendedGuidArray() const;
  void setExtendedGuidArray(
      const std::vector<priv::ExtendedGUID>& extendedGuidArray);
  std::vector<CellId> getCellIdArray() const;
  void setCellIdArray(const std::vector<CellId>& cellIdArray);
  quint64 getDataSize() const;
  void setDataSize(const quint64& dataSize);


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

typedef std::shared_ptr<ObjectGroupObjectExcludedData>
    ObjectGroupObjectExcludedData_SPtr_t;
typedef std::weak_ptr<ObjectGroupObjectExcludedData>
    ObjectGroupObjectExcludedData_WPtr_t;

} // namespace fsshttpb
} // namespace libmson

#endif // OBJECTGROUPOBJECTEXCLUDEDDATA_H
