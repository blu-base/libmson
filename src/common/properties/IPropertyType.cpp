#include "IPropertyType.h"

#include <QDataStream>
#include <QDebug>

namespace MSONcommon {

QDebug operator<<(QDebug dbg, const IPropertyType &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

} // namespace MSONcommon
