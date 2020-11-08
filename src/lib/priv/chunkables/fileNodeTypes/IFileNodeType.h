#ifndef IFILENODETYPE_H
#define IFILENODETYPE_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>
#include <QXmlStreamWriter>

#include "../../IStreamable.h"

namespace libmson{
namespace priv{
/**
 * @class IFileNodeType
 * @brief The abstract class for the Data contained in FileNodes
 *
 */
class IFileNodeType : public IStreamable {
protected:
  IFileNodeType() = default;
  virtual ~IFileNodeType() = default;

public:
  virtual quint64 getSizeInFile() const = 0;
};

} //namespace priv
} // namespace libmson

#endif // IFILENODETYPE_H
