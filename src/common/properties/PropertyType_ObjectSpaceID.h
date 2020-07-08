#ifndef PROPERTYTYPE_OBJECTSPACEID_H
#define PROPERTYTYPE_OBJECTSPACEID_H

#include "IPropertyType.h"
#include <QByteArray>
#include <QtCore/qglobal.h>

class PropertyType_ObjectSpaceID : public IPropertyType {
private:
  QByteArray m_data;

public:
  PropertyType_ObjectSpaceID();

  // IPropertyType interface
  QByteArray data() const;
  void setData(const QByteArray &data);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // PROPERTYTYPE_ONEBYTEOFDATA_H
