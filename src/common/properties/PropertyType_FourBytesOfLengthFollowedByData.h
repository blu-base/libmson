#ifndef PROPERTYTYPE_FOURBYTESOFLENGTHFOLLOWEDBYDATA_H
#define PROPERTYTYPE_FOURBYTESOFLENGTHFOLLOWEDBYDATA_H

#include "IPropertyType.h"
#include "PropertyType_ArrayOfPropertyValues.h"
#include <QByteArray>
#include <QtCore/qglobal.h>

#include <QByteArray>

#include <QDebug>

namespace MSONcommon {

class PropertyType_FourBytesOfLengthFollowedByData : public IPropertyType {
private:
  quint32 m_cb;
  QByteArray m_data;

public:
  PropertyType_FourBytesOfLengthFollowedByData();

  quint32 cb() const;
  void setCb(const quint32 &cb);

  QByteArray data() const;
  void setData(const QByteArray &data);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // PROPERTYTYPE_FOURBYTESOFLENGTHFOLLOWEDBYDATA_H
