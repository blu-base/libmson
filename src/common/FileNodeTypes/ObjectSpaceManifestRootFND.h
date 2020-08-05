#ifndef OBJECTSPACEMANIFESTROOTFND_H
#define OBJECTSPACEMANIFESTROOTFND_H

#include <QtCore/qglobal.h>

#include "IFileNodeType.h"

#include "../commonTypes/ExtendedGUID.h"

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
public:
  ObjectSpaceManifestRootFND();
  ~ObjectSpaceManifestRootFND();

  /**
   * @brief specifies the identity of the root object space
   * @var gosidRoot
   *
   * must be equal with ObjectSpaceManifestListReferenceFND.gosid
   * in the object space manifest list
   */
  ExtendedGUID gosidRoot;

  ExtendedGUID getGosidRoot() const;
  void setGosidRoot(const ExtendedGUID &value);

  // IFileNodeType interface
private:
  void deserialize(QDataStream &ds);
  void serialize(QDataStream &ds) const;
  void toDebugString(QDebug dbg) const;
};

#endif // OBJECTSPACEMANIFESTROOTFND_H