#include "IProperty.h"
#include <QDataStream>
#include <QDebug>

namespace MSONcommon {

IProperty::IProperty() {}

QDataStream &operator<<(QDataStream &ds, const IProperty &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, IProperty &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const IProperty &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

} // namespace MSONcommon
