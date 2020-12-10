#ifndef OBJECTSPACEMANIFESTLISTREFERENCEFND_H
#define OBJECTSPACEMANIFESTLISTREFERENCEFND_H

#include <QtCore/qglobal.h>

#include "../../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

namespace libmson {
namespace priv {

typedef std::shared_ptr<class FileNodeListFragment> FileNodeListFragment_SPtr_t;
typedef std::weak_ptr<class FileNodeListFragment> FileNodeListFragment_WPtr_t;

/**
 * @brief specifies the reference to an object space manifest list
 * @class ObjectSpaceManifestListReferenceFND
 *
 * FileNode Type defined by [MS-ONESTORE]
 * 2.5.2 ObjectSpaceManifestRootFND
 *
 * There must be only one ObjectSpaceManifestRootFND in the MSON File
 *
 * It must be in the root file node list
 */
class ObjectSpaceManifestListReferenceFND : public IFileNodeType {
private:
  /**
   * @brief specifies the location and size of the first FileNodeListFragment
   * @var ref
   */
  FileNodeListFragment_WPtr_t m_ref;

  /**
   * @brief specifies the identity of the ObjectSpaceManifestList
   * @var gosid
   * specified by the object space manifest list.
   * MUST NOT be {{00000000-0000-0000-0000-000000000000},0}
   * and MUST be unique relative to the other
   * ObjectSpaceManifestListReferenceFND.gosid fields in this file.
   */
  ExtendedGUID m_gosid;

public:
  ObjectSpaceManifestListReferenceFND(FileNode_SPtr_t parentFileNode);
  virtual ~ObjectSpaceManifestListReferenceFND() = default;

  FileNodeListFragment_WPtr_t getRef() const;
  void setRef(const FileNodeListFragment_SPtr_t value);

  ExtendedGUID getGosid() const;
  void setGosid(const ExtendedGUID& value);


  virtual quint64 getSizeInFile() const override;
  virtual FileNodeTypeID getType() const override
  {
    return FileNodeTypeID::ObjectSpaceManifestListReferenceFND;
  };

  friend class RevisionStoreFileParser;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTSPACEMANIFESTLISTREFERENCEFND_H
