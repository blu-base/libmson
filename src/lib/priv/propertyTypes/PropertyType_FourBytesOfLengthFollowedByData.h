#ifndef PROPERTYTYPE_FOURBYTESOFLENGTHFOLLOWEDBYDATA_H
#define PROPERTYTYPE_FOURBYTESOFLENGTHFOLLOWEDBYDATA_H

#include "IPropertyType.h"
#include <QByteArray>
#include <QtCore/qglobal.h>


namespace libmson {
namespace priv {

class PropertyType_FourBytesOfLengthFollowedByData : public IPropertyType {
private:
  quint32 m_cb;
  QByteArray m_data;

public:
  PropertyType_FourBytesOfLengthFollowedByData();

  quint32 cb() const;
  void setCb(const quint32& cb);

  QByteArray data() const;
  void setData(const QByteArray& data);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;


  static const quint64 sizeInFileBase = 4;
};

} // namespace priv
} // namespace libmson

#endif // PROPERTYTYPE_FOURBYTESOFLENGTHFOLLOWEDBYDATA_H
