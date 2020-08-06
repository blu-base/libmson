#ifndef REVISIONMANIFESTLISTREFERENCEFND_H
#define REVISIONMANIFESTLISTREFERENCEFND_H

#include <QtCore/qglobal.h>

#include "../commonTypes/FileNodeChunkReference.h"
#include "IFileNodeType.h"

/**
 * @brief specifies the reference to a revision manifest list for the current
 * object space
 * @class RevisionManifestListReferenceFND
 *
 * FileNode Type defined by [MS-ONESTORE]
 * 2.5.4 ObjectSpaceManifestRootFND
 */
class RevisionManifestListReferenceFND : public IFileNodeType {
private:
    /**
     * @brief specifies the location and size of the first FileNodeListFragment
     * structure in the revision manifest list.
     * @var ref
     */
    FileNodeChunkReference m_ref;
public:
  RevisionManifestListReferenceFND(FNCR_STP_FORMAT stpFormat,
                                   FNCR_CB_FORMAT cbFormat);
  RevisionManifestListReferenceFND(quint8 stpFormat, quint8 cbFormat);

  ~RevisionManifestListReferenceFND();



  // IFileNodeType interface
  FileNodeChunkReference getRef() const;
  void setRef(const FileNodeChunkReference &value);

private:
  void deserialize(QDataStream &ds);
  void serialize(QDataStream &ds) const;
  void toDebugString(QDebug dbg) const;

  // IFileNodeType interface
public:
  virtual void generateXml(QXmlStreamWriter& xmlWriter) const override;
};

#endif // REVISIONMANIFESTLISTREFERENCEFND_H
