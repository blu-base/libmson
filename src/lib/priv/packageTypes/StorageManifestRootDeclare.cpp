#include "StorageManifestRootDeclare.h"

#include "dataTypes/CompactExtGuid.h"

namespace libmson {
namespace fsshttpb {

StorageManifestRootDeclare::StorageManifestRootDeclare()
    : m_extendedGuid(), m_cellId()
{
}

priv::ExtendedGUID StorageManifestRootDeclare::getExtendedGuid() const
{
  return m_extendedGuid;
}

void StorageManifestRootDeclare::setExtendedGuid(
    const priv::ExtendedGUID& extendedGuid)
{
  m_extendedGuid = extendedGuid;
}

CellId StorageManifestRootDeclare::getCellId() const { return m_cellId; }

void StorageManifestRootDeclare::setCellId(const CellId& cellId)
{
  m_cellId = cellId;
}

quint64 StorageManifestRootDeclare::strObjBody_cb() const
{
  return CompactExtGuid(m_extendedGuid).getSizeInFile() +
         m_cellId.getSizeInFile();
}

quint64 StorageManifestRootDeclare::cbNextHeader() const
{
  return strObjBody_cb();
}

StreamObjectType StorageManifestRootDeclare::getType() const
{
  return StreamObjectType::StorageManifestRootDeclare;
}

void StorageManifestRootDeclare::push_back(IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(obj);
}

IStreamObj_It_t StorageManifestRootDeclare::insert(
    IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(pos);
  Q_UNUSED(obj);
  m_children.clear();
  return m_children.end();
}

void StorageManifestRootDeclare::deserializeStrObj(QDataStream& ds)
{
  CompactExtGuid guid;
  ds >> guid;
  m_extendedGuid = guid.getExtendedGUID();

  ds >> m_cellId;
}

void StorageManifestRootDeclare::serializeStrObj(QDataStream& ds) const
{
  ds << CompactExtGuid(m_extendedGuid);
  ds << m_cellId;
}


} // namespace fsshttpb
} // namespace libmson
