#ifndef PROPERTYID_H
#define PROPERTYID_H

#include "IProperty.h"
#include <QtCore/qglobal.h>

#include "../commonTypes/Enums.h"
#include <QXmlStreamWriter>

class PropertyID : public IProperty {
private:
  quint32 m_value;
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

  quint32 value() const;

  static QString idToString(const PropertyIDs &val) ;
  static QString typeToString(const PropertyIDType &val) ;

  /**
   * @brief returns a bool sized value if PropertyID is of a bool type property
   * @return -1 if PropertyID is not bool type, else 0 for false, 1 for true;
   */
  int boolValue() const;
  void setBoolValue(bool boolValue);


  void generateXml(QXmlStreamWriter &xmlWriter) const;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // PROPERTYID_H
