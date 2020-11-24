#ifndef REVISIONMANIFEST_H
#define REVISIONMANIFEST_H

#include <QtCore/qglobal.h>
#include <memory>
#include <vector>

namespace libmson {
namespace priv {

typedef std::shared_ptr<class ObjectGroupList> ObjectGroupList_SPtr_t;

typedef std::weak_ptr<class RevisionManifestList> RevisionManifestList_WPtr_t;
typedef std::shared_ptr<class RevisionManifestList> RevisionManifestList_SPtr_t;

typedef std::weak_ptr<class FileNode> FileNode_WPtr_t;

/** @brief RevisionManifestList according to MS-ONESTORE, section 2.1.9
 *
 *
 */
class RevisionManifest {
private:
  RevisionManifestList_WPtr_t m_parent;
  std::vector<FileNode_WPtr_t> m_FileNodeSequence;

  std::vector<ObjectGroupList_SPtr_t> m_ObjectGroupLists;

public:
  RevisionManifest(RevisionManifestList_SPtr_t parent);

  RevisionManifestList_WPtr_t getParent() const;

  std::vector<FileNode_WPtr_t> getFileNodeSequence() const;
  void
  setFileNodeSequence(const std::vector<FileNode_WPtr_t>& FileNodeSequence);


  std::vector<ObjectGroupList_SPtr_t> getObjectGroupLists() const;
  void setObjectGroupLists(
      const std::vector<ObjectGroupList_SPtr_t>& ObjectGroupLists);

  friend class RevisionStoreFileParser;
};

typedef std::weak_ptr<RevisionManifest> RevisionManifest_WPtr_t;
typedef std::shared_ptr<RevisionManifest> RevisionManifest_SPtr_t;

} // namespace priv
} // namespace libmson

#endif // REVISIONMANIFEST_H
