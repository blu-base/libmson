#ifndef OBJECTSPACEMANIFESTLIST_H
#define OBJECTSPACEMANIFESTLIST_H

#include <QXmlStreamWriter>
#include <QtCore/qglobal.h>
#include <vector>

#include "IRevisionStoreFileObject.h"

#include "FileNode.h"
#include "FileNodeListFragment.h"

#include "RevisionManifestList.h"

namespace libmson {
namespace priv {

class ObjectSpaceManifestList : public IRevisionStoreFileObject {
private:

  std::vector<std::shared_ptr<FileNodeListFragment>> m_fileNodeListFragments;

  std::shared_ptr<FileNode> m_objectSpaceManifestListStart;

  std::vector<std::shared_ptr<RevisionManifestList>> m_revisionManifestLists;

  std::vector<std::shared_ptr<FileNode>> m_fileNodeSequence;

public:
  ObjectSpaceManifestList(const FileNodeChunkReference &ref);
  ~ObjectSpaceManifestList() = default;

  std::vector<std::shared_ptr<FileNodeListFragment>>
  getFileNodeListFragments() const;
  void setFileNodeListFragments(
      const std::vector<std::shared_ptr<FileNodeListFragment>> &value);

  std::shared_ptr<FileNode> getObjectSpaceManifestListStart() const;

};

} // namespace priv
} // namespace libmson

#endif // OBJECTSPACEMANIFESTLIST_H
