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

 virtual quint64 getSizeInFile() const override { return 0; };

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;
};

} // namespace MSONcommon

#endif // PROPERTYTYPE_ONEBYTEOFDATA_H
