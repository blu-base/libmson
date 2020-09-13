#ifndef IFILENODETYPE_H
#define IFILENODETYPE_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>
#include <QXmlStreamWriter>

#include "../IRevisionStoreFileObject.h"

namespace MSONcommon {
/**
 * @class IFileNodeType
 * @brief The abstract class for the Data contained in FileNodes
 *
 */
class IFileNodeType : public IRevisionStoreFileObject {
protected:
  IFileNodeType() = default;
  virtual ~IFileNodeType() = default;

public:
  friend QDebug operator<<(QDebug dbg, const IFileNodeType &obj);

private:
  /**
   * @brief prints the IFileNodeType to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  virtual void toDebugString(QDebug dbg) const = 0;
};

} // namespace MSONcommon

#endif // IFILENODETYPE_H
