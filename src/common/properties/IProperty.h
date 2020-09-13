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
};

} // namespace MSONcommon

#endif // IPROPERTY_H
