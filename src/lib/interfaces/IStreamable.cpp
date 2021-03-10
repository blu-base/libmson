#include "IStreamable.h"

#include <QBuffer>

namespace libmson {

QDataStream& operator>>(QDataStream& ds, IStreamable& obj)
{
  obj.deserialize(ds);
  return ds;
}

QDataStream& operator<<(QDataStream& ds, const IStreamable& obj)
{
  obj.serialize(ds);
  return ds;
}

QByteArray& operator<<(QByteArray& ba, const IStreamable& obj)
{
  QBuffer buffer(&ba);
  buffer.open(QIODevice::WriteOnly);

  QDataStream ds(&buffer);
  ds << obj;

  buffer.close();

  return ba;
}

} // namespace libmson
