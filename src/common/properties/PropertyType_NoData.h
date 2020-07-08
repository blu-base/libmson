#ifndef PROPERTYTYPE_NODATA_H
#define PROPERTYTYPE_NODATA_H

#include <QtCore/qglobal.h>
#include "IPropertyType.h"

class PropertyType_NoData : public IPropertyType
{
public:
  PropertyType_NoData();

  // IPropertyType interface
private:
  void deserialize(QDataStream& ds) override;
  void serialize(QDataStream& ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // PROPERTYTYPE_NODATA_H
