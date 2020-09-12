#include "IProperty.h"
#include <QDataStream>
#include <QDebug>

namespace MSONcommon {

QDebug operator<<(QDebug dbg, const IProperty &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

} // namespace MSONcommon
