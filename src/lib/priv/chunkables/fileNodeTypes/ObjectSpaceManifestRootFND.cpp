#include "ObjectSpaceManifestRootFND.h"

namespace libmson {
namespace priv {

ObjectSpaceManifestRootFND::ObjectSpaceManifestRootFND(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode))
{
}

ExtendedGUID ObjectSpaceManifestRootFND::getGosidRoot() const
{
  return m_gosidRoot;
}

void ObjectSpaceManifestRootFND::setGosidRoot(const ExtendedGUID& value)
{
  m_gosidRoot = value;
}

quint64 ObjectSpaceManifestRootFND::getSizeInFile() const
{
  return ExtendedGUID::getSizeInFile();
}

void ObjectSpaceManifestRootFND::deserialize(QDataStream& ds)
{
  ds >> m_gosidRoot;
}

void ObjectSpaceManifestRootFND::serialize(QDataStream& ds) const
{
  ds << m_gosidRoot;
}

} // namespace priv
} // namespace libmson
