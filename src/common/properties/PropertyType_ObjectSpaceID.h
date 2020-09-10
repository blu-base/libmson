#ifndef PROPERTYTYPE_OBJECTSPACEID_H
#define PROPERTYTYPE_OBJECTSPACEID_H

#include "IPropertyType.h"
#include <QByteArray>
#include <QtCore/qglobal.h>

namespace MSONcommon {

class PropertyType_ObjectSpaceID : public IPropertyType {
private:
public:
  PropertyType_ObjectSpaceID();

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // PROPERTYTYPE_ONEBYTEOFDATA_H
