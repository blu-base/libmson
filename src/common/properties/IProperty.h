#ifndef IPROPERTY_H
#define IPROPERTY_H

#include <QtCore/qglobal.h>

#include <QXmlStreamWriter>

#include "../IDeserializable.h"
#include "../ISerializable.h"

namespace MSONcommon {

class IProperty : public ISerializable, public IDeserializable {
protected:
  IProperty() = default;
  virtual ~IProperty() = default;

public:
  friend QDebug operator<<(QDebug dbg, const IProperty &obj);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const = 0;

private:
  /**
   * @brief prints the IProperty to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  virtual void toDebugString(QDebug dbg) const = 0;
};

} // namespace MSONcommon

#endif // IPROPERTY_H
