#include "ChunkTerminatorFND.h"

namespace libmson {
namespace priv {

void ChunkTerminatorFND::deserialize(QDataStream& ds) {}

void ChunkTerminatorFND::serialize(QDataStream& ds) const {}

ChunkTerminatorFND::ChunkTerminatorFND(RSChunkContainer_WPtr_t parentFileNode)
    : IFileNodeType(parentFileNode)
{
}

quint64 ChunkTerminatorFND::getSizeInFile() const { return sizeInFile; }

} // namespace priv
} // namespace libmson
