#ifndef IFILENODETYPE_H
#define IFILENODETYPE_H

#include <QtCore/qglobal.h>

//#include "../Chunkable.h"
#include "../FileNode.h"
#include <memory>


#include <utility> /* to be used by FND implementations for std::move*/


namespace libmson {
namespace priv {
/**
 * @class IFileNodeType
 * @brief The abstract class for the Data contained in FileNodes
 *
 *
 *
 */
class IFileNodeType {
protected:
  virtual ~IFileNodeType() = default;

  /// parent FileNode object. Used to compute getSizeInFile for some
  /// FileNodeTypes.
  FileNode_WPtr_t m_parent;

public:
  IFileNodeType(FileNode_WPtr_t parentFileNode);

  virtual quint64 getSizeInFile() const = 0;
};

} // namespace priv
} // namespace libmson

#endif // IFILENODETYPE_H
