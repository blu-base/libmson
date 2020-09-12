#ifndef REVISIONMANIFESTLIST_H
#define REVISIONMANIFESTLIST_H

#include <QtCore/qglobal.h>

#include "FileNode.h"
#include "FileNodeListFragment.h"
#include "ObjectGroupList.h"
#include "RevisionManifest.h"
#include "commonTypes/FileNodeChunkReference.h"

#include "IDeserializable.h"
#include "ISerializable.h"

#include <QDataStream>
#include <QDebug>
#include <vector>
namespace MSONcommon {
class RevisionManifestList : public IDeserializable {
private:
  FileNodeChunkReference m_ref;

  std::vector<std::shared_ptr<FileNodeListFragment>> m_FileNodeListFragments;
  std::vector<std::shared_ptr<RevisionManifest>> m_RevisionManifests;
  std::vector<std::shared_ptr<FileNode>> m_RevisionRoleDeclarations;

  std::vector<std::shared_ptr<FileNode>> m_RevisionRoleAndContextDeclarations;

  std::vector<std::shared_ptr<ObjectGroupList>> m_ObjectGroupLists;

  std::vector<std::shared_ptr<FileNode>> m_FileNodeSequence;

public:
  RevisionManifestList(const FileNodeChunkReference &ref);
  ~RevisionManifestList() = default;

  std::vector<std::shared_ptr<FileNodeListFragment>>
  getFileNodeListFragments() const;
  void setFileNodeListFragments(
      const std::vector<std::shared_ptr<FileNodeListFragment>> &value);

  std::vector<std::shared_ptr<RevisionManifest>> getRevisionManifests() const;
  void setRevisionManifests(
      const std::vector<std::shared_ptr<RevisionManifest>> &value);

  std::vector<std::shared_ptr<FileNode>> getRevisionRoleDeclarations() const;
  void setRevisionRoleDeclarations(
      const std::vector<std::shared_ptr<FileNode>> &value);

  std::vector<std::shared_ptr<FileNode>>
  getRevisionRoleAndContextDeclarations() const;
  void setRevisionRoleAndContextDeclarations(
      const std::vector<std::shared_ptr<FileNode>> &value);

  std::vector<std::shared_ptr<ObjectGroupList>> getObjectGroupLists() const;
  void setObjectGroupLists(
      const std::vector<std::shared_ptr<ObjectGroupList>> &value);

  std::vector<std::shared_ptr<FileNode>> getFileNodeSequence() const;
  void setFileNodeSequence(const std::vector<std::shared_ptr<FileNode>> &value);

  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &ref);

  friend QDebug operator<<(QDebug dbg, const RevisionManifestList &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

private:
  virtual void deserialize(QDataStream &ds) override;

  /**
   * @brief prints the RevisionManifestList to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  void toDebugString(QDebug dbg) const;
};

} // namespace MSONcommon

#endif // REVISIONMANIFESTLIST_H
