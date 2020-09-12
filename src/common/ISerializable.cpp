#include "ISerializable.h"

#include <QBuffer>
#include <QDataStream>

namespace MSONcommon {

QDataStream &operator<<(QDataStream &ds, const ISerializable &obj) {
  obj.serialize(ds);
  return ds;
}

/// \todo Test qbytearray operator
QByteArray &operator<<(QByteArray &ba, const ISerializable &obj) {

  QBuffer buffer(&ba);
  buffer.open(QIODevice::WriteOnly);

  QDataStream ds(&buffer);
  ds << obj;

  buffer.close();

  return ba;
}

} // namespace MSONcommon
