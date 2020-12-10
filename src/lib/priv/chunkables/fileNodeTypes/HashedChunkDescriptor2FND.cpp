#include "HashedChunkDescriptor2FND.h"

#include "../FileNode.h"

namespace libmson {
namespace priv {
HashedChunkDescriptor2FND::HashedChunkDescriptor2FND(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode))
{
}


ObjectSpaceObjectPropSet_WPtr_t HashedChunkDescriptor2FND::getBlobRef() const
{
  return m_blobRef;
}

void HashedChunkDescriptor2FND::setBlobRef(
    const ObjectSpaceObjectPropSet_SPtr_t BlobRef)
{
  m_blobRef = BlobRef;
}

QByteArray HashedChunkDescriptor2FND::getGuidHash() const { return m_guidHash; }

void HashedChunkDescriptor2FND::setGuidHash(const QByteArray& guidHash)
{
  m_guidHash = guidHash;
}

quint64 HashedChunkDescriptor2FND::getSizeInFile() const
{
  return m_parent.lock()->getFileNodeChunkReferenceSize() + guidHashWidth;
}

} // namespace priv
} // namespace libmson
