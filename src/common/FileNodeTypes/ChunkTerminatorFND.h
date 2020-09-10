#ifndef CHUNKTERMINATORFND_H
#define CHUNKTERMINATORFND_H

#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace MSONcommon {

class ChunkTerminatorFND : public IFileNodeType {
public:
  ChunkTerminatorFND();

  void generateXml(QXmlStreamWriter &xmlWriter) const override;

private:
  void deserialize(QDataStream &ds) override;
  void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const override;
};

} // namespace MSONcommon

#endif // CHUNKTERMINATORFND_H
