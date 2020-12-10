#include "ObjectGroupListReferenceFND.h"

#include "../FileNode.h"

namespace libmson {
namespace priv {

ObjectGroupListReferenceFND::ObjectGroupListReferenceFND(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode))
{
}


ExtendedGUID ObjectGroupListReferenceFND::getObjectGroupID() const
{
  return m_ObjectGroupID;
}

void ObjectGroupListReferenceFND::setObjectGroupID(
    const ExtendedGUID& objectGroupID)
{
  m_ObjectGroupID = objectGroupID;
}

quint64 ObjectGroupListReferenceFND::getSizeInFile() const
{
  return m_parent.lock()->getFileNodeChunkReferenceSize() +
         ExtendedGUID::getSizeInFile();
}

FileNodeListFragment_WPtr_t ObjectGroupListReferenceFND::getRef() const
{
  return m_ref;
}

void ObjectGroupListReferenceFND::setRef(const FileNodeListFragment_SPtr_t& ref)
{
  m_ref = ref;
}

} // namespace priv
} // namespace libmson
