#ifndef PROPERTYTYPE_OBJECTID_H
#define PROPERTYTYPE_OBJECTID_H

#include "../commonTypes/CompactID.h"
#include "IPropertyType.h"
#include <QByteArray>
#include <QtCore/qglobal.h>

class PropertyType_ObjectID : public IPropertyType {
private:
  CompactID m_data;

public:
  PropertyType_ObjectID();

  // IPropertyType interface
  CompactID data() const;
  void setData(const CompactID &data);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // PROPERTYTYPE_OBJECTID_H
