#ifndef OBJECTGROUPDECLARATIONS_H
#define OBJECTGROUPDECLARATIONS_H

#include <QtCore/qglobal.h>

#include "interfaces/IStreamObject.h"

namespace libmson {
namespace fsshttpb {

class ObjectGroupDeclarations : public IStreamObject {

public:
  ObjectGroupDeclarations() = default;
  ~ObjectGroupDeclarations() = default;


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

typedef std::shared_ptr<ObjectGroupDeclarations> ObjectGroupDeclarations_SPtr_t;
typedef std::weak_ptr<ObjectGroupDeclarations> ObjectGroupDeclarations_WPtr_t;

} // namespace fsshttpb
} // namespace libmson


#endif // OBJECTGROUPDECLARATIONS_H
