#include "IFileNodeType.h"


IFileNodeType::IFileNodeType()
{

}

QDataStream& operator<<(QDataStream& ds, const IFileNodeType& obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream& operator>>(QDataStream& ds, IFileNodeType& obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const IFileNodeType& obj) {
  obj.toDebugString(dbg);
  return dbg;
}
