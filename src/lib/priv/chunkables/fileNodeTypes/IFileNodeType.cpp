#include "IFileNodeType.h"

namespace libmson {
namespace priv {

IFileNodeType::IFileNodeType(FileNode_SPtr_t parentFileNode)
    : m_parent(std::move(parentFileNode))
{
}


} // namespace priv
} // namespace libmson
