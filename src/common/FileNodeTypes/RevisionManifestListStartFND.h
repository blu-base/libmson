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
private:
  /**
   * @brief gosid
   * @var gosid
   * specifies the identity of the object space being revised
   * by the revisions in this list.
   */
  ExtendedGUID m_gosid;

  /**
   * @brief must be ignored
   * @var nInstance;
   */
  quint32 m_nInstance;

public:
  RevisionManifestListStartFND();

  ExtendedGUID getGosid() const;
  void setGosid(const ExtendedGUID &value);

  quint32 getNInstance() const;
  void setNInstance(const quint32 &value);

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds);
  void serialize(QDataStream &ds) const;
  void toDebugString(QDebug dbg) const;
};

#endif // REVISIONMANIFESTLISTSTARTFND_H
