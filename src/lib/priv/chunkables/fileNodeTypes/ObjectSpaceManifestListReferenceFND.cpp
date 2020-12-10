#include "ObjectSpaceManifestListReferenceFND.h"

#include "../FileNode.h"

namespace libmson {
namespace priv {

ObjectSpaceManifestListReferenceFND::ObjectSpaceManifestListReferenceFND(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode))
{
}


ExtendedGUID ObjectSpaceManifestListReferenceFND::getGosid() const
{
  return m_gosid;
}

void ObjectSpaceManifestListReferenceFND::setGosid(const ExtendedGUID& value)
{
  m_gosid = value;
}

quint64 ObjectSpaceManifestListReferenceFND::getSizeInFile() const
{
  return m_parent.lock()->getFileNodeChunkReferenceSize() +
         ExtendedGUID::getSizeInFile();
}

FileNodeListFragment_WPtr_t ObjectSpaceManifestListReferenceFND::getRef() const
{
  return m_ref;
}

void ObjectSpaceManifestListReferenceFND::setRef(
    const FileNodeListFragment_SPtr_t value)
{
  m_ref = value;
}

} // namespace priv
} // namespace libmson
