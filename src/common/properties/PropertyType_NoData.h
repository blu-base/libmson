#ifndef PROPERTYTYPE_NODATA_H
#define PROPERTYTYPE_NODATA_H

#include "IPropertyType.h"
#include <QtCore/qglobal.h>

class PropertyType_NoData : public IPropertyType {
public:
  PropertyType_NoData();

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // PROPERTYTYPE_NODATA_H
