#ifndef REVISIONMANIFESTLIST_H
#define REVISIONMANIFESTLIST_H

#include <QtCore/qglobal.h>

#include "FileNode.h"
#include "FileNodeListFragment.h"
#include "ObjectGroupList.h"
#include "RevisionManifest.h"
#include "commonTypes/FileNodeChunkReference.h"

#include <QDataStream>
#include <QDebug>
#include <vector>
namespace MSONcommon {
class RevisionManifestList {
private:
  FileNodeChunkReference m_Ref;

  std::vector<FileNodeListFragment> m_FileNodeListFragments;
  std::vector<RevisionManifest *> m_RevisionManifests;
  std::vector<FileNode> m_RevisionRoleDeclarations;

  std::vector<FileNode> m_RevisionRoleAndContextDeclarations;

  std::vector<ObjectGroupList *> m_ObjectGroupLists;

  std::vector<FileNode> m_FileNodeSequence;

public:
  RevisionManifestList(FileNodeChunkReference ref);
  ~RevisionManifestList();

  std::vector<FileNodeListFragment> getFileNodeListFragments() const;
  void
  setFileNodeListFragments(const std::vector<FileNodeListFragment> &value);
  std::vector<RevisionManifest *> getRevisionManifests() const;
  void setRevisionManifests(const std::vector<RevisionManifest *> &value);
  std::vector<FileNode> getRevisionRoleDeclarations() const;
  void setRevisionRoleDeclarations(const std::vector<FileNode> &value);
  std::vector<FileNode> getRevisionRoleAndContextDeclarations() const;
  void
  setRevisionRoleAndContextDeclarations(const std::vector<FileNode> &value);
  std::vector<ObjectGroupList *> getObjectGroupLists() const;
  void setObjectGroupLists(const std::vector<ObjectGroupList *> &value);
  std::vector<FileNode> getFileNodeSequence() const;
  void setFileNodeSequence(const std::vector<FileNode> &value);
  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &ref);

  //  friend QDataStream &operator<<(QDataStream &ds, const RevisionManifestList
  //  &obj);
  friend QDataStream &operator>>(QDataStream &ds, RevisionManifestList &obj);
  friend QDebug operator<<(QDebug dbg, const RevisionManifestList &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

private:
  /**
   * @brief creates RevisionManifestList from QDataStream
   * @param ds <QDataStream> containing the deserializable
   * RevisionManifestList
   */
  void deserialize(QDataStream &ds);
  //  /**
  //   * @brief creates byte stream from RevisionManifestList object
  //   * @param ds <QDataStream> is the output stream to which the serialized
  //   * RevisionManifestList is send
  //   */
  //  void serialize(QDataStream &ds) const;

  /**
   * @brief prints the RevisionManifestList to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  void toDebugString(QDebug dbg) const;
};

} // namespace MSONcommon

#endif // REVISIONMANIFESTLIST_H
