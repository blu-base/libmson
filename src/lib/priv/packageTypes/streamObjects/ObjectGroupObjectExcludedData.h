#ifndef OBJECTGROUPOBJECTEXCLUDEDDATA_H
#define OBJECTGROUPOBJECTEXCLUDEDDATA_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/CellIdArray.h"
#include "../../commonTypes/CompactExtGuidArray.h"
#include "../../commonTypes/CompactUInt64.h"
#include "StreamObject.h"

namespace libmson {
namespace packStore {
namespace streamObj {
class ObjectGroupObjectExcludedData
    : public StreamObject
    , public libmson::priv::IStreamable {
private:
  CompactExtGuidArray m_extendedGuidArray;
  CellIdArray m_cellIdArray;

  /// \todo unsure if dataSize is directly followed by the excludeData
  quint64 m_dataSize;

public:
  ObjectGroupObjectExcludedData();

  CompactExtGuidArray getExtendedGuidArray() const;
  void setExtendedGuidArray(const CompactExtGuidArray& extendedGuidArray);
  CellIdArray getCellIdArray() const;
  void setCellIdArray(const CellIdArray& cellIdArray);
  quint64 getDataSize() const;
  void setDataSize(const quint64& dataSize);

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

typedef std::shared_ptr<ObjectGroupObjectExcludedData>
    ObjectGroupObjectExcludedData_SPtr_t;
typedef std::weak_ptr<ObjectGroupObjectExcludedData>
    ObjectGroupObjectExcludedData_WPtr_t;

} // namespace streamObj
} // namespace packStore
} // namespace libmson

#endif // OBJECTGROUPOBJECTEXCLUDEDDATA_H
