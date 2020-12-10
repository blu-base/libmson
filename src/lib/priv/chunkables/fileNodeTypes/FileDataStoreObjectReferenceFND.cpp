#include "FileDataStoreObjectReferenceFND.h"

#include "../FileNode.h"

namespace libmson {
namespace priv {
FileDataStoreObjectReferenceFND::FileDataStoreObjectReferenceFND(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode))
{
}

FileDataStoreObject_WPtr_t FileDataStoreObjectReferenceFND::getBlobRef() const
{
  return m_blobRef;
}

void FileDataStoreObjectReferenceFND::setBlobRef(
    const FileDataStoreObject_SPtr_t& value)
{
  m_blobRef = value;
}

QUuid FileDataStoreObjectReferenceFND::getGuidReference() const
{
  return m_guidReference;
}

void FileDataStoreObjectReferenceFND::setGuidReference(const QUuid& value)
{
  m_guidReference = value;
}

quint64 FileDataStoreObjectReferenceFND::getSizeInFile() const
{
  return m_parent.lock()->getFileNodeChunkReferenceSize() + sizeOfGUID;
}

} // namespace priv
} // namespace libmson
