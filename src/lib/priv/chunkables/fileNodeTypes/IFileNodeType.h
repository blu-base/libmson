#ifndef IFILENODETYPE_H
#define IFILENODETYPE_H

#include <QtCore/qglobal.h>
#include <memory>
#include <utility> /* to be used by FND implementations for std::move*/

#include "FileNodeTypeIDs.h"

namespace libmson {
namespace priv {

typedef std::shared_ptr<class FileNode> FileNode_SPtr_t;
typedef std::weak_ptr<class FileNode> FileNode_WPtr_t;


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
  IFileNodeType(FileNode_SPtr_t parentFileNode);

  virtual quint64 getSizeInFile() const  = 0;
  virtual FileNodeTypeID getType() const = 0;
};

typedef std::shared_ptr<IFileNodeType> IFileNodeType_SPtr_t;


} // namespace priv
} // namespace libmson

#endif // IFILENODETYPE_H
