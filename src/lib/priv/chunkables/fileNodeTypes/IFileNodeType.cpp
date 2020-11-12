#include "IFileNodeType.h"

namespace libmson {
namespace priv {

IFileNodeType::IFileNodeType(RSChunkContainer_WPtr_t parentFileNode)
    : m_parent(parentFileNode)
{
}


} // namespace priv
} // namespace libmson
