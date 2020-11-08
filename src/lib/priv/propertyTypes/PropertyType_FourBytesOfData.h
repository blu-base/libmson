#ifndef PROPERTYTYPE_FOURBYTESOFDATA_H
#define PROPERTYTYPE_FOURBYTESOFDATA_H

#include "IPropertyType.h"
#include <QByteArray>
#include <QtCore/qglobal.h>

namespace libmson{
namespace priv{

class PropertyType_FourBytesOfData : public IPropertyType {
private:
  QByteArray m_data;

public:
  PropertyType_FourBytesOfData();

  // IPropertyType interface
  QByteArray data() const;
  void setData(const QByteArray &data);

  virtual quint64 getSizeInFile() const override { return sizeInFile; };

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;





  static const quint64 sizeInFile = 4;
};

} //namespace priv
} // namespace libmson

#endif // PROPERTYTYPE_FOURBYTESOFDATA_H
