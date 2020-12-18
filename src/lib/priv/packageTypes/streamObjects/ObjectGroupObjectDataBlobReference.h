#ifndef OBJECTGROUPOBJECTDATABLOBREFERENCE_H
#define OBJECTGROUPOBJECTDATABLOBREFERENCE_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/CellIdArray.h"
#include "../../commonTypes/CompactExtGuid.h"
#include "../../commonTypes/CompactExtGuidArray.h"
#include "StreamObject.h"

namespace libmson {
namespace packStore {
namespace streamObj {

class ObjectGroupObjectDataBlobReference
    : public StreamObject
    , public libmson::priv::IStreamable {
private:
  CompactExtGuidArray m_objectExtGuidArray;
  CellIdArray m_cellIdArray;
  CompactExtGuid m_extendedGuid;

public:
  ObjectGroupObjectDataBlobReference();
  CompactExtGuidArray getObjectExtGuidArray() const;
  void setObjectExtGuidArray(const CompactExtGuidArray& objectExtGuidArray);
  CellIdArray getCellIdArray() const;
  void setCellIdArray(const CellIdArray& cellIdArray);
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

typedef std::shared_ptr<ObjectGroupObjectDataBlobReference>
    ObjectGroupObjectDataBlobReference_SPtr_t;
typedef std::weak_ptr<ObjectGroupObjectDataBlobReference>
    ObjectGroupObjectDataBlobReference_WPtr_t;

} // namespace streamObj
} // namespace packStore
} // namespace libmson
#endif // OBJECTGROUPOBJECTDATABLOBREFERENCE_H
