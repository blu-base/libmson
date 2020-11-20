#ifndef REVISIONMANIFESTLISTREFERENCEFND_H
#define REVISIONMANIFESTLISTREFERENCEFND_H

#include <QtCore/qglobal.h>

#include "../../commonTypes/FileNodeChunkReference.h"
#include "../FileNodeListFragment.h"
#include "IFileNodeType.h"

namespace libmson {
namespace priv {
/**
 * @brief specifies the reference to a revision manifest list for the current
 * object space
 * @class RevisionManifestListReferenceFND
 *
 * FileNode Type defined by [MS-ONESTORE]
 * 2.5.4 ObjectSpaceManifestRootFND
 */
class RevisionManifestListReferenceFND : public IFileNodeType {
private:
  /**
   * @brief specifies the location and size of the first FileNodeListFragment
   * structure in the revision manifest list.
   * @var ref
   */
  FileNodeListFragment_WPtr_t m_ref;

public:
  RevisionManifestListReferenceFND(FileNode_WPtr_t parentFileNode);
  ~RevisionManifestListReferenceFND() = default;

  FileNodeListFragment_WPtr_t getRef() const;
  void setRef(const FileNodeListFragment_SPtr_t value);


  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;

  virtual quint64 getSizeInFile() const override;
};

} // namespace priv
} // namespace libmson

#endif // REVISIONMANIFESTLISTREFERENCEFND_H
