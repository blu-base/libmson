#ifndef OBJECTGROUPDATA_H
#define OBJECTGROUPDATA_H

#include <QtCore/qglobal.h>

#include <vector>

#include "../../IStreamable.h"
#include "StreamObject.h"

namespace libmson {
namespace packStore {
namespace streamObj {


class ObjectGroupObjectData;
class ObjectGroupObjectDataBlobReference;
class ObjectGroupObjectExcludedData;

class ObjectGroupData
    : public StreamObject
    , public libmson::priv::IStreamable {
private:
  std::vector<StreamObject_SPtr_t> m_objects;

public:
  ObjectGroupData();

  std::vector<StreamObject_SPtr_t> getObjects() const;

  std::vector<std::shared_ptr<ObjectGroupObjectData>> getObjectData() const;
  std::vector<std::shared_ptr<ObjectGroupObjectDataBlobReference>>
  getObjectDataBlobReferences() const;
  std::vector<std::shared_ptr<ObjectGroupObjectExcludedData>>
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
