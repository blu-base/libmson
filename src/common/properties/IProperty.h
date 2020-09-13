#ifndef IPROPERTY_H
#define IPROPERTY_H

#include <QtCore/qglobal.h>

#include <QXmlStreamWriter>

#include "../IRevisionStoreFileObject.h"

namespace MSONcommon {

class IProperty : public IRevisionStoreFileObject {
protected:
  IProperty() = default;
  virtual ~IProperty() = default;

public:
  friend QDebug operator<<(QDebug dbg, const IProperty &obj);

private:
  /**
   * @brief prints the IProperty to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  virtual void toDebugString(QDebug dbg) const = 0;
};

} // namespace MSONcommon

#endif // IPROPERTY_H
