
#include "IFileNodeType.h"
#include "../FileNode.h"

namespace libmson {
namespace priv {

IFileNodeType::IFileNodeType(FileNode_WPtr_t parentFileNode)
    : m_parent(std::move(parentFileNode))
{
}


} // namespace priv
} // namespace libmson
