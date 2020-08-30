#ifndef PROPERTYTYPE_FOURBYTESOFDATA_H
#define PROPERTYTYPE_FOURBYTESOFDATA_H

#include "IPropertyType.h"
#include <QByteArray>
#include <QtCore/qglobal.h>

class PropertyType_FourBytesOfData : public IPropertyType {
private:
  QByteArray m_data;

public:
  PropertyType_FourBytesOfData();

  // IPropertyType interface
  QByteArray data() const;
  void setData(const QByteArray &data);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // PROPERTYTYPE_FOURBYTESOFDATA_H
