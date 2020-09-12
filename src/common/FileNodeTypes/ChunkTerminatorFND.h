#ifndef CHUNKTERMINATORFND_H
#define CHUNKTERMINATORFND_H

#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace MSONcommon {

class ChunkTerminatorFND : public IFileNodeType {
public:
  ChunkTerminatorFND() = default;
  virtual ~ChunkTerminatorFND() = default;

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // CHUNKTERMINATORFND_H
