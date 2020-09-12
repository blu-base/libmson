#include "IDeserializable.h"

namespace MSONcommon {

QDataStream &operator>>(QDataStream &ds, IDeserializable &obj) {
  obj.deserialize(ds);
  return ds;
}

} // namespace MSONcommon
