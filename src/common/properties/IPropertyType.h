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
};

} // namespace MSONcommon

#endif // IPROPERTYTYPE_H
