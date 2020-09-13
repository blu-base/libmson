#ifndef IPROPERTYTYPE_H
#define IPROPERTYTYPE_H

#include <QtCore/qglobal.h>

#include <QXmlStreamWriter>

#include "../IRevisionStoreFileObject.h"

namespace MSONcommon {

class IPropertyType : public IRevisionStoreFileObject {
public:
  IPropertyType() = default;
  virtual ~IPropertyType() = default;

public:
  friend QDebug operator<<(QDebug dbg, const IPropertyType &obj);

private:
  /**
   * @brief prints the IPropertyType to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  virtual void toDebugString(QDebug dbg) const = 0;
};

} // namespace MSONcommon

#endif // IPROPERTYTYPE_H
