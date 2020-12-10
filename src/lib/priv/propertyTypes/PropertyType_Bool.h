#ifndef PROPERTYTYPE_BOOL_H
#define PROPERTYTYPE_BOOL_H

#include <QtCore/qglobal.h>

#include "IPropertyType.h"

namespace libmson {
namespace priv {

class PropertyType_Bool : public IPropertyType {
public:
  PropertyType_Bool();

  virtual quint64 getSizeInFile() const override { return 0; };
  virtual PropertyIDType getType() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // PROPERTYTYPE_BOOL_H
