#ifndef CHUNKTERMINATORFND_H
#define CHUNKTERMINATORFND_H

#include "../../IStreamable.h"
#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

class ChunkTerminatorFND
    : public IFileNodeType
    , public IStreamable {
public:
  ChunkTerminatorFND(RSChunkContainer_WPtr_t parentFileNode);
  virtual ~ChunkTerminatorFND() = default;

  virtual quint64 getSizeInFile() const override;


  static const quint64 sizeInFile = 0;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // CHUNKTERMINATORFND_H
