#ifndef OBJECTGROUPDECLARATIONS_H
#define OBJECTGROUPDECLARATIONS_H

#include <QtCore/qglobal.h>

#include <vector>

#include "../../IStreamable.h"
#include "ObjectGroupObjectDataBLOBDeclaration.h"
#include "ObjectGroupObjectDeclare.h"
#include "StreamObject.h"

namespace libmson {
namespace packStore {
namespace streamObj {

class ObjectGroupDeclarations
    : public StreamObject
    , public libmson::priv::IStreamable {
private:
  std::vector<StreamObject_SPtr_t> m_objects;

public:
  ObjectGroupDeclarations();

  std::vector<StreamObject_SPtr_t> getObjects() const;

  std::vector<ObjectGroupObjectDeclare_SPtr_t> getDeclares() const;
  std::vector<ObjectGroupObjectDataBLOBDeclaration_SPtr_t>
  getBlobDeclares() const;
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

typedef std::shared_ptr<ObjectGroupDeclarations> ObjectGroupDeclarations_SPtr_t;
typedef std::weak_ptr<ObjectGroupDeclarations> ObjectGroupDeclarations_WPtr_t;

} // namespace streamObj
} // namespace packStore
} // namespace libmson


#endif // OBJECTGROUPDECLARATIONS_H
