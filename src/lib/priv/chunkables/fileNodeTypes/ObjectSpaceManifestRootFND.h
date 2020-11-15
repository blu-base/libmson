#ifndef OBJECTSPACEMANIFESTROOTFND_H
#define OBJECTSPACEMANIFESTROOTFND_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

namespace libmson {
namespace priv {
/**
 * @brief specifies the root object space
 * @class ObjectSpaceManifestRootFND
 *
 * FileNode Type defined by [MS-ONESTORE]
 * 2.5.1 ObjectSpaceManifestRootFND
 *
 * There must be only one ObjectSpaceManifestRootFND in the MSON File
 *
 * It must be in the root file node list
 */
class ObjectSpaceManifestRootFND
    : public IFileNodeType
    , public IStreamable {
private:
  /**
   * @brief specifies the identity of the root object space
   * @var gosidRoot
   *
   * must be equal with ObjectSpaceManifestListReferenceFND.gosid
   * in the object space manifest list
   */
  ExtendedGUID m_gosidRoot;

public:
  ObjectSpaceManifestRootFND(FileNode_WPtr_t parentFileNode);
  virtual ~ObjectSpaceManifestRootFND() = default;

  ExtendedGUID getGosidRoot() const;
  void setGosidRoot(const ExtendedGUID& value);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTSPACEMANIFESTROOTFND_H
