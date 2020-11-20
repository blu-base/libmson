#ifndef REVISIONMANIFESTLIST_H
#define REVISIONMANIFESTLIST_H

#include <QtCore/qglobal.h>

#include "ObjectGroupList.h"
#include "RevisionManifest.h"
#include "chunkables/FileNode.h"
#include "chunkables/FileNodeListFragment.h"
#include "commonTypes/FileNodeChunkReference.h"

#include <QDataStream>
#include <QDebug>
#include <vector>

class ObjectSpaceManifestList;

namespace libmson {
namespace priv {


class RevisionManifestList {
private:
  std::weak_ptr<ObjectSpaceManifestList> m_parent;

//  FileNodeChunkReference m_ref;

  std::vector<std::shared_ptr<FileNodeListFragment>> m_FileNodeListFragments;
  std::vector<std::shared_ptr<RevisionManifest>> m_RevisionManifests;
  std::vector<std::shared_ptr<FileNode>> m_RevisionRoleDeclarations;

  std::vector<std::shared_ptr<FileNode>> m_RevisionRoleAndContextDeclarations;

  std::vector<std::shared_ptr<ObjectGroupList>> m_ObjectGroupLists;

  std::vector<std::shared_ptr<FileNode>> m_FileNodeSequence;

public:
  RevisionManifestList(std::shared_ptr<ObjectSpaceManifestList> parent);
  ~RevisionManifestList() = default;

  std::vector<std::shared_ptr<FileNodeListFragment>>
  getFileNodeListFragments() const;
  void setFileNodeListFragments(
      const std::vector<std::shared_ptr<FileNodeListFragment>>& value);

  std::vector<std::shared_ptr<RevisionManifest>> getRevisionManifests() const;
  void setRevisionManifests(
      const std::vector<std::shared_ptr<RevisionManifest>>& value);

  std::vector<std::shared_ptr<FileNode>> getRevisionRoleDeclarations() const;
  void setRevisionRoleDeclarations(
      const std::vector<std::shared_ptr<FileNode>>& value);

  std::vector<std::shared_ptr<FileNode>>
  getRevisionRoleAndContextDeclarations() const;
  void setRevisionRoleAndContextDeclarations(
      const std::vector<std::shared_ptr<FileNode>>& value);

  std::vector<std::shared_ptr<ObjectGroupList>> getObjectGroupLists() const;
  void setObjectGroupLists(
      const std::vector<std::shared_ptr<ObjectGroupList>>& value);

  std::vector<std::shared_ptr<FileNode>> getFileNodeSequence() const;
  void setFileNodeSequence(const std::vector<std::shared_ptr<FileNode>>& value);

};

} // namespace priv
} // namespace libmson

#endif // REVISIONMANIFESTLIST_H
