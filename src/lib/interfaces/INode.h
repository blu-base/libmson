#ifndef INODE_H
#define INODE_H

#include <QtCore/qglobal.h>
#include <memory>

namespace libmson {


class Section;

enum class INodeType {
  Notebook,
  Section,
  PageSeries,
  Page,
  Title,
  OutlineGroup,
  Outline,
  OutlineElement,
  Table,
  TableRow,
  TableCell,
  VersionHistory
};


/**
 * @brief Interface for [MS-ONE] nodes
 */
class INode {
protected:
  INode()          = default;
  virtual ~INode() = default;

public:
  virtual INode* getParent() = 0;

  std::vector<std::shared_ptr<INode>> getChildren() { return m_children; }

  /** return the reference to the vector of child nodes
   */
  std::vector<std::shared_ptr<INode>>& children() { return m_children; }


  /**
   * @brief returns the number of children nodes in this instance
   * @return
   */
  size_t size() { return getChildren().size(); }

  bool hasChildren() { return !getChildren().empty(); }

  virtual INodeType type() = 0;

  /** Get the section which containes the calling INode
   */
  virtual std::weak_ptr<Section> getSection() = 0;

private:
  std::weak_ptr<INode> m_parent;

  std::vector<std::shared_ptr<INode>> m_children;
};

typedef std::shared_ptr<INode> INode_SPtr_t;
typedef std::weak_ptr<INode> INode_WPtr_t;


} // namespace libmson

#endif // INODE_H
