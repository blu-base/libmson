#ifndef OBJECTGROUPDATA_H
#define OBJECTGROUPDATA_H

#include <QtCore/qglobal.h>
#include "interfaces/IStreamObject.h"

namespace libmson {
namespace fsshttpb {

class ObjectGroupData : public IStreamObject {
public:
  ObjectGroupData() = default;
  ~ObjectGroupData() = default;

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

typedef std::shared_ptr<ObjectGroupData> ObjectGroupData_SPtr_t;
typedef std::weak_ptr<ObjectGroupData> ObjectGroupData_WPtr_t;

} // namespace packStore
} // namespace libmson

#endif // OBJECTGROUPDATA_H
