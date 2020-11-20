#ifndef OBJECTSPACEMANIFESTLIST_H
#define OBJECTSPACEMANIFESTLIST_H

#include <QtCore/qglobal.h>
#include <vector>

#include "chunkables/FileNode.h"
#include "chunkables/FileNodeListFragment.h"

#include "RevisionManifestList.h"

#include "commonTypes/ExtendedGUID.h"

namespace libmson {
namespace priv {

class ObjectSpaceManifestList {
private:
  FileNode_WPtr_t m_objectSpaceManifestListReferenceFND;

  ExtendedGUID m_gosid;

  FileNode_WPtr_t m_objectSpaceManifestListStartFND;

  std::vector<FileNodeListFragment_WPtr_t> m_fileNodeListFragments;


  //  std::shared_ptr<FileNode> m_objectSpaceManifestListStart;

  std::vector<RevisionManifestList> m_revisionManifestLists;

  //  std::vector<std::shared_ptr<FileNode>> m_fileNodeSequence;

public:
  ObjectSpaceManifestList(const FileNode_SPtr_t& referenceFND);

  std::vector<std::shared_ptr<FileNodeListFragment>>
  getFileNodeListFragments() const;
  void setFileNodeListFragments(
      const std::vector<std::shared_ptr<FileNodeListFragment>>& value);
};

} // namespace priv
} // namespace libmson

#endif // OBJECTSPACEMANIFESTLIST_H
