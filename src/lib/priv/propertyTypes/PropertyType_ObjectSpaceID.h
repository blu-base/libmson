#ifndef PROPERTYTYPE_OBJECTSPACEID_H
#define PROPERTYTYPE_OBJECTSPACEID_H

#include "IPropertyType.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

class PropertyType_ObjectSpaceID : public IPropertyType {
private:
public:
  PropertyType_ObjectSpaceID();

  virtual quint64 getSizeInFile() const override { return 0; };
  virtual PropertyIDType getType() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // PROPERTYTYPE_ONEBYTEOFDATA_H
