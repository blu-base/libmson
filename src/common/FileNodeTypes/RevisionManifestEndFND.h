#ifndef REVISIONMANIFESTENDFND_H
#define REVISIONMANIFESTENDFND_H

#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace MSONcommon {

class RevisionManifestEndFND : public IFileNodeType {
public:
  RevisionManifestEndFND() = default;

  virtual quint64 getSizeInFile() const override { return 0; }

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;
};

} // namespace MSONcommon

#endif // REVISIONMANIFESTENDFND_H
