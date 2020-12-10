#ifndef PROPERTYTYPE_ARRAYOFPROPERTYVALUES_H
#define PROPERTYTYPE_ARRAYOFPROPERTYVALUES_H

#include "PropertyID.h"

#include "IPropertyType.h"
#include "PropertySet.h"
#include <QtCore/qglobal.h>
#include <vector>

namespace libmson {
namespace priv {

class PropertyType_ArrayOfPropertyValues : public IPropertyType {
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

  quint32 cProperties() const;
  void setCProperties(const quint32& cProperties);

  PropertyID prid() const;
  void setPrid(const PropertyID& prid);

  std::vector<PropertySet> data() const;
  void setData(const std::vector<PropertySet>& data);

  virtual quint64 getSizeInFile() const override;
  virtual PropertyIDType getType() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;


  static const quint64 sizeInFileBase = 4 + PropertyID::getSizeInFile();
};

} // namespace priv
} // namespace libmson

#endif // PROPERTYTYPE_ARRAYOFPROPERTYVALUES_H
