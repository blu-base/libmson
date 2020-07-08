#ifndef PROPERTYTYPE_FOURBYTESOFLENGTHFOLLOWEDBYDATA_H
#define PROPERTYTYPE_FOURBYTESOFLENGTHFOLLOWEDBYDATA_H

#include "IPropertyType.h"
#include "prtArrayOfPropertyValues.h"
#include <QByteArray>
#include <QtCore/qglobal.h>

#include <QDebug>

class PropertyType_FourBytesOfLengthFollowedByData : public IPropertyType {
private:
  prtArrayOfPropertyValues m_data;

public:
  PropertyType_FourBytesOfLengthFollowedByData();

  // IPropertyType interface
  prtArrayOfPropertyValues data() const;
  void setData(const prtArrayOfPropertyValues &data);

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // PROPERTYTYPE_FOURBYTESOFLENGTHFOLLOWEDBYDATA_H
