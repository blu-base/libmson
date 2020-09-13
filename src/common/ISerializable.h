#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <QtCore/qglobal.h>

namespace MSONcommon {

class ISerializable {
protected:
  ISerializable() = default;
  virtual ~ISerializable() = default;

public:
  friend QDataStream &operator<<(QDataStream &ds, const ISerializable &obj);

  friend QByteArray &operator<<(QByteArray &ba, const ISerializable &obj);

protected:
  virtual void serialize(QDataStream &ds) const = 0;
};

}; // namespace MSONcommon

#endif // ISERIALIZABLE_H
