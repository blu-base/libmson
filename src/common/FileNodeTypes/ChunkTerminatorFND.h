#ifndef CHUNKTERMINATORFND_H
#define CHUNKTERMINATORFND_H

#include <QtCore/qglobal.h>
#include "IFileNodeType.h"
class ChunkTerminatorFND : public IFileNodeType
{
public:
  ChunkTerminatorFND();

  // IFileNodeType interface
private:
  void deserialize(QDataStream& ds) override;
  void serialize(QDataStream& ds) const override;
  void toDebugString(QDebug dbg) const override;
};

#endif // CHUNKTERMINATORFND_H
