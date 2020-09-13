#include "IDebugOutputable.h"


namespace MSONcommon {

QDebug &operator<<(QDebug &dbg, const IDebugOutputable &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

} // namespace MSONcommon
