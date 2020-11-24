#ifndef OBJECTSPACEMANIFESTLISTSTARTFND_H
#define OBJECTSPACEMANIFESTLISTSTARTFND_H

#include "../../IStreamable.h"
#include "../../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {
/**
 * @brief specifies the beginning of an object space manifest list
 * @class ObjectSpaceManifestListStartFND
 *
 * FileNode Type defined by [MS-ONESTORE]
 * 2.5.3 ObjectSpaceManifestListStartFND
 *
 * There must be only one ObjectSpaceManifestRootFND in the MSON File
 *
 * It must be in the root file node list
 */
class ObjectSpaceManifestListStartFND
    : public IFileNodeType
    , public IStreamable {
private:
  /**
   * @brief specifies the identity of the object space
   * @var gosidRoot
   *
   * must be equal with ObjectSpaceManifestListReferenceFND.gosid
   * of the FileNode structure that referenced this file node list
   */
  ExtendedGUID m_gosid;

public:
  ObjectSpaceManifestListStartFND(FileNode_SPtr_t parentFileNode);
  virtual ~ObjectSpaceManifestListStartFND() = default;

  ExtendedGUID gosid() const;
  void setGosid(const ExtendedGUID& value);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTSPACEMANIFESTLISTSTARTFND_H
