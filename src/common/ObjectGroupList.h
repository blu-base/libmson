#ifndef OBJECTGROUPLIST_H
#define OBJECTGROUPLIST_H

#include <QtCore/qglobal.h>
#include <vector>

#include <QDataStream>
#include <QDebug>

#include "FileNode.h"
#include "FileNodeListFragment.h"
#include "commonTypes/FileNodeChunkReference.h"

namespace MSONcommon {
class ObjectGroupList {
private:
  FileNodeChunkReference m_ref;

  std::vector<FileNode *> m_fileNodeSequence;

  std::vector<FileNodeListFragment *> m_fileNodeListFragments;

public:
  ObjectGroupList(FileNodeChunkReference ref);
  ~ObjectGroupList();

  std::vector<FileNode *> getFileNodeSequence() const;
  void setFileNodeSequence(const std::vector<FileNode *> &value);

  std::vector<FileNodeListFragment *> getFileNodeListFragments();

  void
  setFileNodeListFragments(const std::vector<FileNodeListFragment *> &value);
  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &ref);

  //  friend QDataStream &operator<<(QDataStream &ds, const ObjectGroupList
  //  &obj);
  friend QDataStream &operator>>(QDataStream &ds, ObjectGroupList &obj);
  friend QDebug operator<<(QDebug dbg, const ObjectGroupList &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

private:
  /**
   * @brief creates ObjectGroupList from QDataStream
   * @param ds <QDataStream> containing the deserializable
   * ObjectGroupList
   */
  void deserialize(QDataStream &ds);
  //  /**
  //   * @brief creates byte stream from ObjectGroupList object
  //   * @param ds <QDataStream> is the output stream to which the serialized
  //   * ObjectGroupList is send
  //   */
  //  void serialize(QDataStream &ds) const;

  /**
   * @brief prints the ObjectGroupList to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  void toDebugString(QDebug dbg) const;
};
} // namespace MSONcommon
#endif // OBJECTGROUPLIST_H
