#include "ObjectGroupStartFND.h"

namespace libmson {
namespace priv {

ObjectGroupStartFND::ObjectGroupStartFND(FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_oid(ExtendedGUID())
{
}

ExtendedGUID ObjectGroupStartFND::getOid() const { return m_oid; }

void ObjectGroupStartFND::setOid(const ExtendedGUID& oid) { m_oid = oid; }

quint64 ObjectGroupStartFND::getSizeInFile() const
{
  return ExtendedGUID::getSizeInFile();
}

void ObjectGroupStartFND::deserialize(QDataStream& ds) { ds >> m_oid; }

void ObjectGroupStartFND::serialize(QDataStream& ds) const { ds << m_oid; }

} // namespace priv
} // namespace libmson
