#ifndef PROPERTYTYPE_BOOL_H
#define PROPERTYTYPE_BOOL_H

#include <QtCore/qglobal.h>

#include "IPropertyType.h"

namespace MSONcommon {

class PropertyType_Bool : public IPropertyType {
public:
  PropertyType_Bool();

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // PROPERTYTYPE_BOOL_H
