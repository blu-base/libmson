#ifndef PROPERTYTYPE_EIGHTBYTESOFDATA_H
#define PROPERTYTYPE_EIGHTBYTESOFDATA_H

#include "IPropertyType.h"
#include <QByteArray>
#include <QtCore/qglobal.h>

namespace MSONcommon {

class PropertyType_EightBytesOfData : public IPropertyType {
private:
  QByteArray m_data;

public:
  PropertyType_EightBytesOfData();

  // IPropertyType interface
  QByteArray data() const;
  void setData(const QByteArray &data);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // PROPERTYTYPE_ONEBYTEOFDATA_H
