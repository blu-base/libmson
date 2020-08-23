#ifndef OBJECTSPACEMANIFESTLIST_H
#define OBJECTSPACEMANIFESTLIST_H

#include <QtCore/qglobal.h>
#include <vector>

#include "FileNode.h"
#include "FileNodeListFragment.h"
#include "commonTypes/FileNodeChunkReference.h"

#include "RevisionManifestList.h"
namespace MSONcommon {
class ObjectSpaceManifestList {
private:
  FileNodeChunkReference m_ref;

  std::vector<FileNodeListFragment> m_fileNodeListFragments;

  FileNode m_objectSpaceManifestListStart;

  std::vector<RevisionManifestList *> m_revisionManifestLists;

  std::vector<FileNode> m_fileNodeSequence;

public:
  ObjectSpaceManifestList(FileNodeChunkReference &ref);
  ~ObjectSpaceManifestList();

  std::vector<FileNodeListFragment> getFileNodeListFragments() const;
  void
  setFileNodeListFragments(const std::vector<FileNodeListFragment> &value);
  FileNode getObjectSpaceManifestListStart() const;
  void setObjectSpaceManifestListStart(const FileNode &value);
  std::vector<RevisionManifestList *> getRevisionManifestLists();
  void
  setRevisionManifestLists(const std::vector<RevisionManifestList *> &value);
  std::vector<FileNode> getFileNodeSequence() const;
  void setFileNodeSequence(const std::vector<FileNode> &value);
  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &ref);

  //  friend QDataStream &operator<<(QDataStream &ds, const
  //  ObjectSpaceManifestList &obj);
  friend QDataStream &operator>>(QDataStream &ds, ObjectSpaceManifestList &obj);
  friend QDebug operator<<(QDebug dbg, const ObjectSpaceManifestList &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;


private:
  /**
   * @brief creates ObjectSpaceManifestList from QDataStream
   * @param ds <QDataStream> containing the deserializable
   * ObjectSpaceManifestList
   */
  void deserialize(QDataStream &ds);
  //  /**
  //   * @brief creates byte stream from ObjectSpaceManifestList object
  //   * @param ds <QDataStream> is the output stream to which the serialized
  //   * ObjectSpaceManifestList is send
  //   */
  //  void serialize(QDataStream &ds) const;

  /**
   * @brief prints the ObjectSpaceManifestList to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  void toDebugString(QDebug dbg) const;
};
} // namespace MSONcommon
#endif // OBJECTSPACEMANIFESTLIST_H
