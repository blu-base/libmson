#include "IFileNodeType.h"

namespace MSONcommon {

QDebug operator<<(QDebug dbg, const IFileNodeType &obj) {
  obj.toDebugString(dbg);
  return dbg;
}
} // namespace MSONcommon
