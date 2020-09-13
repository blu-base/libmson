#ifndef PROPERTYTYPE_TWOBYTESOFDATA_H
#define PROPERTYTYPE_TWOBYTESOFDATA_H

#include "IPropertyType.h"
#include <QByteArray>
#include <QtCore/qglobal.h>

namespace MSONcommon {

class PropertyType_TwoBytesOfData : public IPropertyType {
private:
  QByteArray m_data;

public:
  PropertyType_TwoBytesOfData();

  QByteArray data() const;
  void setData(const QByteArray &data);

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;
};

} // namespace MSONcommon

#endif // PROPERTYTYPE_TWOBYTESOFDATA_H
