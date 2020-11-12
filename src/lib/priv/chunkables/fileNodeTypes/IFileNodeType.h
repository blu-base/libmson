#ifndef IFILENODETYPE_H
#define IFILENODETYPE_H

#include <QtCore/qglobal.h>

#include "../RevisionStoreChunkContainer.h"

namespace libmson {
namespace priv {
/**
 * @class IFileNodeType
 * @brief The abstract class for the Data contained in FileNodes
 *
 */
class IFileNodeType {
protected:
  IFileNodeType(RSChunkContainer_WPtr_t parentFileNode);
  virtual ~IFileNodeType() = default;

  /// parent FileNode object. Used to compute getSizeInFile for some
  /// FileNodeTypes.
  RSChunkContainer_WPtr_t m_parent;

public:
  virtual quint64 getSizeInFile() const = 0;
};

} // namespace priv
} // namespace libmson

#endif // IFILENODETYPE_H
