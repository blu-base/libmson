#ifndef PROPERTYTYPE_NODATA_H
#define PROPERTYTYPE_NODATA_H

#include "IPropertyType.h"
#include <QtCore/qglobal.h>

namespace libmson{
namespace priv{

class PropertyType_NoData : public IPropertyType {
public:
  PropertyType_NoData();

  virtual quint64 getSizeInFile() const override { return 0; };

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;




};

} //namespace priv
} // namespace libmson

#endif // PROPERTYTYPE_NODATA_H