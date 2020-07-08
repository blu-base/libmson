#ifndef PROPERTYTYPE_BOOL_H
#define PROPERTYTYPE_BOOL_H

#include <QtCore/qglobal.h>

#include "IPropertyType.h"

class PropertyType_Bool : public IPropertyType
{
public:
  PropertyType_Bool();

  // IPropertyType interface
private:
  void deserialize(QDataStream& ds) override;
  void serialize(QDataStream& ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // PROPERTYTYPE_BOOL_H
