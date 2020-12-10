#include "FileDataStoreListReferenceFND.h"

#include "../FileNode.h"

namespace libmson {
namespace priv {

FileDataStoreListReferenceFND::FileDataStoreListReferenceFND(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode))
{
}


FileNodeListFragment_WPtr_t FileDataStoreListReferenceFND::getRef() const
{
  return m_ref;
}

void FileDataStoreListReferenceFND::setRef(
    const FileNodeListFragment_SPtr_t value)
{
  m_ref = value;
}

quint64 FileDataStoreListReferenceFND::getSizeInFile() const
{
  return m_parent.lock()->getFileNodeChunkReferenceSize();
}

} // namespace priv
} // namespace libmson
