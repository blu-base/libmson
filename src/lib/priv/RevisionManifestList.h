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
#include <memory>
#include <vector>


namespace libmson {
namespace priv {

class ObjectSpaceManifestList;

class RevisionManifestList {
private:
  std::weak_ptr<ObjectSpaceManifestList> m_parent;

  //  FileNodeChunkReference m_ref;

  std::vector<FileNodeListFragment_WPtr_t> m_fileNodeListFragments;
  std::vector<std::shared_ptr<RevisionManifest>> m_RevisionManifests;
  std::vector<FileNode_SPtr_t> m_RevisionRoleDeclarations;

  std::vector<FileNode_SPtr_t> m_RevisionRoleAndContextDeclarations;

  std::vector<std::shared_ptr<ObjectGroupList>> m_ObjectGroupLists;

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

  std::vector<FileNode_SPtr_t> getRevisionRoleDeclarations() const;
  void setRevisionRoleDeclarations(const std::vector<FileNode_SPtr_t>& value);

  std::vector<FileNode_SPtr_t> getRevisionRoleAndContextDeclarations() const;
  void setRevisionRoleAndContextDeclarations(
      const std::vector<FileNode_SPtr_t>& value);

  std::vector<std::shared_ptr<ObjectGroupList>> getObjectGroupLists() const;
  void setObjectGroupLists(
      const std::vector<std::shared_ptr<ObjectGroupList>>& value);

  friend class RevisionStoreFileParser;
};

} // namespace priv
} // namespace libmson

#endif // REVISIONMANIFESTLIST_H
