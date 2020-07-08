#ifndef PROPERTYID_H
#define PROPERTYID_H

#include "IProperty.h"
#include <QtCore/qglobal.h>

#include "../commonTypes/Enums.h"

class PropertyID : public IProperty {
private:
  PropertyIDs m_id;
  PropertyIDType m_type;

  bool m_boolValue;

public:
  PropertyID();

  PropertyID(const PropertyIDs &id, const PropertyIDType &type);

  PropertyIDs id() const;
  void setId(const PropertyIDs &id);

  PropertyIDType type() const;
  void setType(const PropertyIDType &type);

  /**
   * @brief returns a bool sized value if PropertyID is of a bool type property
   * @return -1 if PropertyID is not bool type, else 0 for false, 1 for true;
   */
  int boolValue() const;
  void setBoolValue(bool boolValue);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // PROPERTYID_H
