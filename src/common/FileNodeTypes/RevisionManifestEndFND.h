#ifndef REVISIONMANIFESTENDFND_H
#define REVISIONMANIFESTENDFND_H

#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

class RevisionManifestEndFND : public IFileNodeType {
public:
  RevisionManifestEndFND();

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // REVISIONMANIFESTENDFND_H
