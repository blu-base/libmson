#ifndef IPROPERTYTYPE_H
#define IPROPERTYTYPE_H

#include <QtCore/qglobal.h>

#include <QXmlStreamWriter>

#include "../IDeserializable.h"
#include "../ISerializable.h"

namespace MSONcommon {

class IPropertyType : public ISerializable, public IDeserializable {
public:
  IPropertyType() = default;

public:
  friend QDebug operator<<(QDebug dbg, const IPropertyType &obj);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const = 0;

private:
  /**
   * @brief prints the IPropertyType to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  virtual void toDebugString(QDebug dbg) const = 0;
};

} // namespace MSONcommon

#endif // IPROPERTYTYPE_H
