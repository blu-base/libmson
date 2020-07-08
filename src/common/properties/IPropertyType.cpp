#include "IPropertyType.h"

#include <QDataStream>
#include <QDebug>

IPropertyType::IPropertyType() {}

QDataStream &operator<<(QDataStream &ds, const IPropertyType &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, IPropertyType &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const IPropertyType &obj) {
  obj.toDebugString(dbg);
  return dbg;
}
