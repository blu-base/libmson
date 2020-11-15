#ifndef IFILENODETYPE_H
#define IFILENODETYPE_H

#include <QtCore/qglobal.h>

//#include "../Chunkable.h"
#include "../FileNode.h"
#include <memory>


namespace libmson {
namespace priv {

// class FileNode;

// typedef std::shared_ptr<FileNode> FileNode_SPtr_t;
// typedef std::weak_ptr<FileNode> FileNode_WPtr_t;

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
