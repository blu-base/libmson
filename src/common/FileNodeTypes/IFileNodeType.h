#ifndef IFILENODETYPE_H
#define IFILENODETYPE_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>
#include <QXmlStreamWriter>

#include "../IDeserializable.h"
#include "../ISerializable.h"

namespace MSONcommon {
/**
 * @class IFileNodeType
 * @brief The abstract class for the Data contained in FileNodes
 *
 */
class IFileNodeType : public ISerializable, public IDeserializable {
protected:
  IFileNodeType() = default;

public:
  friend QDebug operator<<(QDebug dbg, const IFileNodeType &obj);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const = 0;

private:
  /**
   * @brief prints the IFileNodeType to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  virtual void toDebugString(QDebug dbg) const = 0;
};

} // namespace MSONcommon

#endif // IFILENODETYPE_H
