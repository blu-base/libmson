#include "CellManifestCurrentRevision.h"

#include "dataTypes/CompactExtGuid.h"

namespace libmson {
namespace fsshttpb {

priv::ExtendedGUID CellManifestCurrentRevision::getExtendedGuid() const
{
  return m_extendedGuid;
}

void CellManifestCurrentRevision::setExtendedGuid(
    const priv::ExtendedGUID& extendedGuid)
{
  m_extendedGuid = extendedGuid;
}

CellManifestCurrentRevision::CellManifestCurrentRevision() {}

StreamObjectType CellManifestCurrentRevision::getType() const
{
  return StreamObjectType::CellManifestCurrentRevision;
}

quint64 CellManifestCurrentRevision::strObjBody_cb() const
{
  return CompactExtGuid(m_extendedGuid).getSizeInFile();
}

quint64 CellManifestCurrentRevision::cbNextHeader() const
{
  return strObjBody_cb();
}

void CellManifestCurrentRevision::push_back(IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(obj);
}

IStreamObj_It_t CellManifestCurrentRevision::insert(
    IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(pos);
  Q_UNUSED(obj);
  m_children.clear();
  return m_children.end();
}

void CellManifestCurrentRevision::deserializeStrObj(QDataStream& ds)
{
  CompactExtGuid guid;
  ds >> guid;
  m_extendedGuid = guid.getExtendedGUID();
}

void CellManifestCurrentRevision::serializeStrObj(QDataStream& ds) const
{
  ds << CompactExtGuid(m_extendedGuid);
}

} // namespace fsshttpb
} // namespace libmson
