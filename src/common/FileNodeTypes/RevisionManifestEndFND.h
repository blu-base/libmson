#ifndef REVISIONMANIFESTENDFND_H
#define REVISIONMANIFESTENDFND_H

#include <QtCore/qglobal.h>
#include "IFileNodeType.h"
class RevisionManifestEndFND : public IFileNodeType
{
public:
  RevisionManifestEndFND();

  // IFileNodeType interface
private:
  void deserialize(QDataStream& ds) override;
  void serialize(QDataStream& ds) const override;
  void toDebugString(QDebug dbg) const override;

  // IFileNodeType interface
public:
  virtual void generateXml(QXmlStreamWriter& xmlWriter) const override;
};

#endif // REVISIONMANIFESTENDFND_H
