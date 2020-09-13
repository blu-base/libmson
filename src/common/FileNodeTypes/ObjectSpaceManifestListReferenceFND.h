#ifndef OBJECTSPACEMANIFESTLISTREFERENCEFND_H
#define OBJECTSPACEMANIFESTLISTREFERENCEFND_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "../commonTypes/FileNodeChunkReference.h"
#include "IFileNodeType.h"

namespace MSONcommon {
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
  FileNodeChunkReference m_ref;

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
  ObjectSpaceManifestListReferenceFND(FNCR_STP_FORMAT stpFormat,
                                      FNCR_CB_FORMAT cbFormat);
  ObjectSpaceManifestListReferenceFND(quint8 stpFormat, quint8 cbFormat);

  virtual ~ObjectSpaceManifestListReferenceFND() = default;

  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &value);

  ExtendedGUID getGosid() const;
  void setGosid(const ExtendedGUID &value);

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // OBJECTSPACEMANIFESTLISTREFERENCEFND_H
