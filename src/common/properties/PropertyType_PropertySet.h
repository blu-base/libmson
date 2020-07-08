#ifndef PROPERTYTYPE_PROPERTYSET_H
#define PROPERTYTYPE_PROPERTYSET_H

#include "IPropertyType.h"
#include "PropertySet.h"
#include <QByteArray>
#include <QtCore/qglobal.h>

class PropertyType_PropertySet : public IPropertyType {
private:
  PropertySet m_data;

public:
  PropertyType_PropertySet();

  // IPropertyType interface
  PropertySet data() const;
  void setData(const PropertySet &data);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // PROPERTYTYPE_PROPERTYSET_H
