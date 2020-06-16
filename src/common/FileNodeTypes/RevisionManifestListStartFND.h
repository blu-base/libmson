#ifndef REVISIONMANIFESTLISTSTARTFND_H
#define REVISIONMANIFESTLISTSTARTFND_H

#include <QtCore/qglobal.h>

#include "IFileNodeType.h"

#include "../commonTypes/ExtendedGUID.h"

/**
 * @brief specifies the beginning of a revision manifest list
 * @class RevisionManifestListStartFND
 *
 * FileNode Type defined by [MS-ONESTORE]
 * 2.5.5 RevisionManifestListStartFND
 */
class RevisionManifestListStartFND : public IFileNodeType {
public:
  RevisionManifestListStartFND();

  /**
   * @brief gosid
   * @var gosid
   * specifies the identity of the object space being revised
   * by the revisions in this list.
   */
  ExtendedGUID gosid;

  /**
   * @brief must be ignored
   * @var nInstance;
   */
  quint32 nInstance;

  ExtendedGUID getGosid() const;
  void setGosid(const ExtendedGUID &value);
  quint32 getNInstance() const;
  void setNInstance(const quint32 &value);

  // IFileNodeType interface

private:
  void deserialize(QDataStream &ds);
  void serialize(QDataStream &ds) const;
  void toDebugString(QDebug dbg) const;
};

#endif // REVISIONMANIFESTLISTSTARTFND_H
