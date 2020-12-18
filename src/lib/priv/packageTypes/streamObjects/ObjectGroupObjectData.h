#ifndef OBJECTGROUPOBJECTDATA_H
#define OBJECTGROUPOBJECTDATA_H

#include <QtCore/qglobal.h>


#include "../../IStreamable.h"
#include "../../commonTypes/BinaryItem.h"
#include "../../commonTypes/CellIdArray.h"
#include "../../commonTypes/CompactExtGuidArray.h"
#include "StreamObject.h"

namespace libmson {
namespace packStore {
namespace streamObj {

class ObjectGroupObjectData
    : public StreamObject
    , public libmson::priv::IStreamable {
private:
  CompactExtGuidArray m_extendedGuidArray;
  CellIdArray m_cellIdArray;
  BinaryItem m_data;

public:
  ObjectGroupObjectData();

  CompactExtGuidArray getExtendedGuidArray() const;
  void setExtendedGuidArray(const CompactExtGuidArray& extendedGuidArray);
  CellIdArray getCellIdArray() const;
  void setCellIdArray(const CellIdArray& cellIdArray);
  BinaryItem getData() const;
  void setData(const BinaryItem& data);

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

typedef std::shared_ptr<ObjectGroupObjectData> ObjectGroupObjectData_SPtr_t;
typedef std::weak_ptr<ObjectGroupObjectData> ObjectGroupObjectData_WPtr_t;

} // namespace streamObj
} // namespace packStore
} // namespace libmson
#endif // OBJECTGROUPOBJECTDATA_H
