#ifndef IREVISIONSTOREFILEOBJECT_H
#define IREVISIONSTOREFILEOBJECT_H

#include <QtCore/qglobal.h>

#include "IDebugOutputable.h"
#include "IDeserializable.h"
#include "IRevisionStoreFileToXmlable.h"
#include "ISerializable.h"

namespace MSONcommon {

/** IRevisionStoreFileObject boiler plate interface.
 * It bundles interfaces into a single interface for convenience only
 */
class IRevisionStoreFileObject : public ISerializable,
                                 public IDeserializable,
                                 public IRevisionStoreFileToXmlable,
                                 public IDebugOutputable {
protected:
  IRevisionStoreFileObject() = default;
  virtual ~IRevisionStoreFileObject() = default;
};

} // namespace MSONcommon

#endif // IREVISIONSTOREFILEOBJECT_H
