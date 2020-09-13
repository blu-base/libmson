#ifndef IDEBUGOUTPUTABLE_H
#define IDEBUGOUTPUTABLE_H

#include <QtCore/qglobal.h>
#include <QDebug>
namespace MSONcommon {

class IDebugOutputable {
protected:
  IDebugOutputable() = default;
  virtual ~IDebugOutputable() = default;

public:
  friend QDebug &operator<<(QDebug &dbg, const IDebugOutputable &obj);

private:
  virtual void toDebugString(QDebug &dbg) const = 0;
};

}; // namespace MSONcommon

#endif // IDEBUGOUTPUTABLE_H
