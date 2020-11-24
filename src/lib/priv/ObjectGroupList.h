#ifndef OBJECTGROUPLIST_H
#define OBJECTGROUPLIST_H

#include <QtCore/qglobal.h>
#include <memory>
#include <vector>

class QDataStream;

namespace libmson {
namespace priv {


typedef std::weak_ptr<class FileNodeListFragment> FileNodeListFragment_WPtr_t;
typedef std::shared_ptr<class RevisionManifest> RevisionManifest_SPtr_t;
typedef std::weak_ptr<class RevisionManifest> RevisionManifest_WPtr_t;


/**
 * @brief ObjectGroupList class according MS-ONESTORE's section 2.1.13 which is
 * a subset of
 *
 * Contains the following FileNode structures:
 *
 * * ObjectGroupStartFND
 * * GlobalIdentificationTable
 * * Data represented by zero or more of only these FileNode types:
 *   * DataSignatureGroupDefinitionFND
 *   * ObjectDeclaration2RefCountFND
 *   * ObjectDeclaration2LargeRefCountFND
 *   * ReadOnlyObjectDeclaration2RefCountFND
 *   * ReadOnlyObjectDeclaration2LargeRefCountFND
 *   * ObjectDeclarationFileData3RefCountFND
 *   * ObjectDeclarationFileData3LargeRefCountFND
 * * ObjectGroupEndFND
 *
 * @param parent The RevisionManifest which references this ObjectGroupList
 * instance
 *
 * @sa RevisionManifest
 * @sa RevisionManifestList
 */
class ObjectGroupList {
private:
  RevisionManifest_WPtr_t m_parent;

  std::vector<FileNodeListFragment_WPtr_t> m_fileNodeListFragments;

public:
  ObjectGroupList(RevisionManifest_SPtr_t parent);

  friend class RevisionStoreFileParser;
};

typedef std::shared_ptr<ObjectGroupList> ObjectGroupList_SPtr_t;
typedef std::weak_ptr<ObjectGroupList> ObjectGroupList_WPtr_t;

} // namespace priv
} // namespace libmson

#endif // OBJECTGROUPLIST_H
