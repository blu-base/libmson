#ifndef PROPERTYTYPE_ONEBYTEOFDATA_H
#define PROPERTYTYPE_ONEBYTEOFDATA_H

#include <QtCore/qglobal.h>
#include "IPropertyType.h"
#include <QByteArray>

class PropertyType_OneByteOfData : public IPropertyType
{
private:
    QByteArray m_data;

public:
  PropertyType_OneByteOfData();

  QByteArray data() const;
  void setData(const QByteArray& data);

  virtual void generateXml(QXmlStreamWriter& xmlWriter) const override;

private:
  void deserialize(QDataStream& ds) override;
  void serialize(QDataStream& ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // PROPERTYTYPE_ONEBYTEOFDATA_H
