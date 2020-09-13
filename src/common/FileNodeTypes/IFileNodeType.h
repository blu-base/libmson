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
};

} // namespace MSONcommon

#endif // IFILENODETYPE_H
