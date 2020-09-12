#ifndef OBJECTGROUPLIST_H
#define OBJECTGROUPLIST_H

#include <QtCore/qglobal.h>
#include <vector>


#include <QDebug>

#include "FileNode.h"
#include "FileNodeListFragment.h"
#include "commonTypes/FileNodeChunkReference.h"

#include "IDeserializable.h"
#include "ISerializable.h"

class QDataStream;

namespace MSONcommon {
class ObjectGroupList : public IDeserializable {
private:
  FileNodeChunkReference m_ref;

  std::vector<std::shared_ptr<FileNode>> m_fileNodeSequence;

  std::vector<std::shared_ptr<FileNodeListFragment>> m_fileNodeListFragments;

public:
  ObjectGroupList(const FileNodeChunkReference &ref);
  ~ObjectGroupList() = default;

  std::vector<std::shared_ptr<FileNode>> getFileNodeSequence() const;
  void setFileNodeSequence(const std::vector<std::shared_ptr<FileNode>> &value);

  std::vector<std::shared_ptr<FileNodeListFragment>> getFileNodeListFragments();

  void setFileNodeListFragments(const std::vector<std::shared_ptr<FileNodeListFragment>> &value);
  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &ref);

  friend QDebug operator<<(QDebug dbg, const ObjectGroupList &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

private:
  virtual void deserialize(QDataStream &ds) override;

  /**
   * @brief prints the ObjectGroupList to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  void toDebugString(QDebug dbg) const;
};
} // namespace MSONcommon
#endif // OBJECTGROUPLIST_H
