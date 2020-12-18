#ifndef OBJECTGROUPDATA_H
#define OBJECTGROUPDATA_H

#include <QtCore/qglobal.h>

#include <vector>

#include "../../IStreamable.h"
#include "ObjectGroupObjectData.h"
#include "ObjectGroupObjectDataBlobReference.h"
#include "ObjectGroupObjectExcludedData.h"
#include "StreamObject.h"

namespace libmson {
namespace packStore {
namespace streamObj {

class ObjectGroupData
    : public StreamObject
    , public libmson::priv::IStreamable {
private:
  std::vector<StreamObject_SPtr_t> m_objects;

public:
  ObjectGroupData();

  std::vector<StreamObject_SPtr_t> getObjects() const;

  std::vector<ObjectGroupObjectData_SPtr_t> getObjectData() const;
  std::vector<ObjectGroupObjectDataBlobReference_SPtr_t>
  getObjectDataBlobReferences() const;
  std::vector<ObjectGroupObjectExcludedData_SPtr_t>
  getObjectExcludedData() const;


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

typedef std::shared_ptr<ObjectGroupData> ObjectGroupData_SPtr_t;
typedef std::weak_ptr<ObjectGroupData> ObjectGroupData_WPtr_t;


} // namespace streamObj
} // namespace packStore
} // namespace libmson
#endif // OBJECTGROUPDATA_H
