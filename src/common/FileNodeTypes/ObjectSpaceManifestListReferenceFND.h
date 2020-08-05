#ifndef OBJECTSPACEMANIFESTLISTREFERENCEFND_H
#define OBJECTSPACEMANIFESTLISTREFERENCEFND_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "../commonTypes/FileNodeChunkReference.h"
#include "IFileNodeType.h"

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
public:
  ObjectSpaceManifestListReferenceFND(FNCR_STP_FORMAT stpFormat,
                                      FNCR_CB_FORMAT cbFormat);
  ObjectSpaceManifestListReferenceFND(quint8 stpFormat, quint8 cbFormat);

  ~ObjectSpaceManifestListReferenceFND();
  /**
   * @brief specifies the location and size of the first FileNodeListFragment
   * @var ref
   */
  FileNodeChunkReference ref;

  /**
   * @brief specifies the identity of the ObjectSpaceManifestList
   * @var gosid
   * specified by the object space manifest list.
   * MUST NOT be {{00000000-0000-0000-0000-000000000000},0}
   * and MUST be unique relative to the other
   * ObjectSpaceManifestListReferenceFND.gosid fields in this file.
   */
  ExtendedGUID gosid;

  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &value);

  ExtendedGUID getGosid() const;
  void setGosid(const ExtendedGUID &value);

  // IFileNodeType interface
private:
  void deserialize(QDataStream &ds);
  void serialize(QDataStream &ds) const;
  void toDebugString(QDebug dbg) const;
};

#endif // OBJECTSPACEMANIFESTLISTREFERENCEFND_H