#include "ObjectDataEncryptionKeyV2FNDX.h"

#include "../FileNode.h"

namespace libmson {
namespace priv {
ObjectDataEncryptionKeyV2FNDX::ObjectDataEncryptionKeyV2FNDX(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode))
{
}


EncryptedData_WPtr_t ObjectDataEncryptionKeyV2FNDX::getBlobRef() const
{
  return m_blobRef;
}

void ObjectDataEncryptionKeyV2FNDX::setBlobRef(
    const EncryptedData_SPtr_t& value)
{
  m_blobRef = value;
}

quint64 ObjectDataEncryptionKeyV2FNDX::getSizeInFile() const
{
  return m_parent.lock()->getFileNodeChunkReferenceSize();
}

} // namespace priv
} // namespace libmson
