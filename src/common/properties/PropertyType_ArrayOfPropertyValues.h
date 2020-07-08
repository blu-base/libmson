#ifndef PROPERTYTYPE_ARRAYOFPROPERTYVALUES_H
#define PROPERTYTYPE_ARRAYOFPROPERTYVALUES_H

#include "IPropertyType.h"
#include "prtArrayOfPropertyValues.h"
#include <QByteArray>
#include <QtCore/qglobal.h>

class PropertyType_ArrayOfPropertyValues : public IPropertyType {
private:
  prtArrayOfPropertyValues m_data;

public:
  PropertyType_ArrayOfPropertyValues();

  // IPropertyType interface
  prtArrayOfPropertyValues data() const;
  void setData(const prtArrayOfPropertyValues &data);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // PROPERTYTYPE_ARRAYOFPROPERTYVALUES_H
