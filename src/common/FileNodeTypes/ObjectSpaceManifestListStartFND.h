#ifndef OBJECTSPACEMANIFESTLISTSTARTFND_H
#define OBJECTSPACEMANIFESTLISTSTARTFND_H

#include <QtCore/qglobal.h>

#include "../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

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
class ObjectSpaceManifestListStartFND : public IFileNodeType {
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
  ObjectSpaceManifestListStartFND();
  ~ObjectSpaceManifestListStartFND();

  ExtendedGUID getGosid() const;
  void setGosid(const ExtendedGUID &value);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds);
  void serialize(QDataStream &ds) const;
  void toDebugString(QDebug dbg) const;
};

#endif // OBJECTSPACEMANIFESTLISTSTARTFND_H
