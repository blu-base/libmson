#ifndef PROPERTYTYPE_CONTEXTID_H
#define PROPERTYTYPE_CONTEXTID_H

#include "../commonTypes/CompactID.h"
#include "IPropertyType.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

class PropertyType_ContextID : public IPropertyType {
private:
  CompactID m_data;

public:
  PropertyType_ContextID();

  // IPropertyType interface
  CompactID data() const;
  void setData(const CompactID& data);

  virtual quint64 getSizeInFile() const override { return sizeInFile; };

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;


  static const quint64 sizeInFile = CompactID::getSizeInFile();
};

} // namespace priv
} // namespace libmson

#endif // PROPERTYTYPE_CONTEXTID_H
