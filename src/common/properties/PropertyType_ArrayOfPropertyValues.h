#ifndef PROPERTYTYPE_ARRAYOFPROPERTYVALUES_H
#define PROPERTYTYPE_ARRAYOFPROPERTYVALUES_H


#include "PropertyID.h"
#include <QByteArray>
#include <QDataStream>
#include <QtCore/qglobal.h>
#include <vector>

#include "IPropertyType.h"
#include "PropertySet.h"

class PropertyType_ArrayOfPropertyValues : public IPropertyType{
private:
  /**
   * @brief how many Property elements in this array
   */
  quint32 m_cProperties;

  /**
   * @brief specifies the PropertyID of all elements in this array, only
   * present if m_cProperties is not 0;
   *
   */
  PropertyID m_prid;

  std::vector<PropertySet> m_data;

public:
  PropertyType_ArrayOfPropertyValues();

  friend QDataStream &operator<<(QDataStream &ds,
                                 const PropertyType_ArrayOfPropertyValues &obj);
  friend QDataStream &operator>>(QDataStream &ds,
                                 PropertyType_ArrayOfPropertyValues &obj);

  friend QDebug operator<<(QDebug dbg, const PropertyType_ArrayOfPropertyValues &obj);

  virtual void generateXml(QXmlStreamWriter& xmlWriter) const override;

  quint32 cProperties() const;
  void setCProperties(const quint32 &cProperties);

  PropertyID prid() const;
  void setPrid(const PropertyID &prid);

  std::vector<PropertySet> data() const;
  void setData(const std::vector<PropertySet> &data);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;


};

#endif // PROPERTYTYPE_ARRAYOFPROPERTYVALUES_H
