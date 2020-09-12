#ifndef OBJECTSPACEMANIFESTROOTFND_H
#define OBJECTSPACEMANIFESTROOTFND_H

#include <QtCore/qglobal.h>

#include "IFileNodeType.h"

#include "../commonTypes/ExtendedGUID.h"

namespace MSONcommon {
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
class ObjectSpaceManifestRootFND : public IFileNodeType {
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
  ObjectSpaceManifestRootFND() = default;
  virtual ~ObjectSpaceManifestRootFND() = default;

  ExtendedGUID getGosidRoot() const;
  void setGosidRoot(const ExtendedGUID &value);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // OBJECTSPACEMANIFESTROOTFND_H
