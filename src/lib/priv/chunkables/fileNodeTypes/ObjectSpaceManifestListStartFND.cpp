#include "ObjectSpaceManifestListStartFND.h"

namespace libmson {
namespace priv {

ObjectSpaceManifestListStartFND::ObjectSpaceManifestListStartFND(
    FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode))
{
}

ExtendedGUID ObjectSpaceManifestListStartFND::getGosid() const
{
  return m_gosid;
}

void ObjectSpaceManifestListStartFND::setGosid(const ExtendedGUID& value)
{
  m_gosid = value;
}

quint64 ObjectSpaceManifestListStartFND::getSizeInFile() const
{
  return ExtendedGUID::getSizeInFile();
}

void ObjectSpaceManifestListStartFND::deserialize(QDataStream& ds)
{
  ds >> m_gosid;
}

void ObjectSpaceManifestListStartFND::serialize(QDataStream& ds) const
{
  ds << m_gosid;
}

} // namespace priv
} // namespace libmson
