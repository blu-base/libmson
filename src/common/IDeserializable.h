#ifndef IDESERIALIZABLE_H
#define IDESERIALIZABLE_H

#include <QtCore/qglobal.h>

namespace MSONcommon {

class IDeserializable {
protected:
  IDeserializable() = default;
  virtual ~IDeserializable() = default;

public:
  friend QDataStream &operator>>(QDataStream &ds, IDeserializable &obj);

private:
  virtual void deserialize(QDataStream &ds) = 0;
};

}; // namespace MSONcommon

#endif // IDESERIALIZABLE_H
