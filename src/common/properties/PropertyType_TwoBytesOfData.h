#ifndef PROPERTYTYPE_TWOBYTESOFDATA_H
#define PROPERTYTYPE_TWOBYTESOFDATA_H

#include "IPropertyType.h"
#include <QByteArray>
#include <QtCore/qglobal.h>

class PropertyType_TwoBytesOfData : public IPropertyType {
private:
  QByteArray m_data;

public:
  PropertyType_TwoBytesOfData();

  QByteArray data() const;
  void setData(const QByteArray &data);

  virtual void generateXml(QXmlStreamWriter& xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // PROPERTYTYPE_TWOBYTESOFDATA_H
