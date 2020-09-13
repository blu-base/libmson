#ifndef PROPERTYTYPE_NODATA_H
#define PROPERTYTYPE_NODATA_H

#include "IPropertyType.h"
#include <QtCore/qglobal.h>

namespace MSONcommon {

class PropertyType_NoData : public IPropertyType {
public:
  PropertyType_NoData();

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // PROPERTYTYPE_NODATA_H
