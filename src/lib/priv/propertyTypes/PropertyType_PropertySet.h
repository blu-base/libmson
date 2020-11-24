#ifndef PROPERTYTYPE_PROPERTYSET_H
#define PROPERTYTYPE_PROPERTYSET_H

#include "IPropertyType.h"
#include "PropertySet.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

class PropertyType_PropertySet : public IPropertyType {
private:
  PropertySet m_data;

public:
  PropertyType_PropertySet();

  PropertySet data() const;
  void setData(const PropertySet& data);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // PROPERTYTYPE_PROPERTYSET_H
