#ifndef REVISIONMANIFESTLIST_H
#define REVISIONMANIFESTLIST_H

#include <QtCore/qglobal.h>

//#include "ObjectGroupList.h"
//#include "RevisionManifest.h"
//#include "chunkables/FileNode.h"
//#include "chunkables/FileNodeListFragment.h"

#include <memory>
#include <vector>


namespace libmson {
namespace priv {

class ObjectSpaceManifestList;

typedef std::shared_ptr<class FileNode> FileNode_SPtr_t;
typedef std::shared_ptr<class FileNodeListFragment> FileNodeListFragment_SPtr_t;
typedef std::weak_ptr<class FileNodeListFragment> FileNodeListFragment_WPtr_t;
typedef std::shared_ptr<class RevisionManifest> RevisionManifest_SPtr_t;
typedef std::shared_ptr<class ObjectGroupList> ObjectGroupList_SPtr_t;
typedef std::weak_ptr<class ObjectSpaceManifestList>
    ObjectSpaceManifestList_WPtr_t;
typedef std::shared_ptr<class ObjectSpaceManifestList>
    ObjectSpaceManifestList_SPtr_t;


class RevisionManifestList {
private:
  ObjectSpaceManifestList_WPtr_t m_parent;

  //  FileNodeChunkReference m_ref;

  std::vector<FileNodeListFragment_WPtr_t> m_fileNodeListFragments;
  std::vector<RevisionManifest_SPtr_t> m_RevisionManifests;
  std::vector<FileNode_SPtr_t> m_RevisionRoleDeclarations;

  std::vector<FileNode_SPtr_t> m_RevisionRoleAndContextDeclarations;

  std::vector<ObjectGroupList_SPtr_t> m_ObjectGroupLists;

public:
  RevisionManifestList(const ObjectSpaceManifestList_SPtr_t& parent);
  ~RevisionManifestList() = default;

  std::vector<FileNodeListFragment_SPtr_t> getFileNodeListFragments() const;
  void setFileNodeListFragments(
      const std::vector<FileNodeListFragment_SPtr_t>& value);

  std::vector<RevisionManifest_SPtr_t> getRevisionManifests() const;
  void setRevisionManifests(const std::vector<RevisionManifest_SPtr_t>& value);

  std::vector<FileNode_SPtr_t> getRevisionRoleDeclarations() const;
  void setRevisionRoleDeclarations(const std::vector<FileNode_SPtr_t>& value);

  std::vector<FileNode_SPtr_t> getRevisionRoleAndContextDeclarations() const;
  void setRevisionRoleAndContextDeclarations(
      const std::vector<FileNode_SPtr_t>& value);

  std::vector<ObjectGroupList_SPtr_t> getObjectGroupLists() const;
  void setObjectGroupLists(const std::vector<ObjectGroupList_SPtr_t>& value);

  friend class RevisionStoreFileParser;
};

} // namespace priv
} // namespace libmson

#endif // REVISIONMANIFESTLIST_H
