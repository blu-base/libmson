#include "IDebugOutputable.h"


namespace MSONcommon {

QDebug &operator<<(QDebug &dbg, const IDebugOutputable &obj) {
  QDebugStateSaver stateSaver(dbg);
  obj.toDebugString(dbg);
  return dbg;
}

} // namespace MSONcommon
