#ifndef PROPERTYTYPE_ONEBYTEOFDATA_H
#define PROPERTYTYPE_ONEBYTEOFDATA_H

#include "IPropertyType.h"
#include <QByteArray>
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

class PropertyType_OneByteOfData : public IPropertyType {
private:
  QByteArray m_data;

public:
  PropertyType_OneByteOfData();

  QByteArray data() const;
  void setData(const QByteArray& data);

  virtual quint64 getSizeInFile() const override { return sizeInFile; };
  virtual PropertyIDType getType() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;


  static const quint64 sizeInFile = 1;
};

} // namespace priv
} // namespace libmson

#endif // PROPERTYTYPE_ONEBYTEOFDATA_H
