#include "StorageManifestRootDeclare.h"
namespace libmson {
namespace packStore {
namespace streamObj {
StorageManifestRootDeclare::StorageManifestRootDeclare()
    : m_extendedGuid(), m_cellId()
{
}

CompactExtGuid StorageManifestRootDeclare::getExtendedGuid() const
{
  return m_extendedGuid;
}

void StorageManifestRootDeclare::setExtendedGuid(
    const CompactExtGuid& extendedGuid)
{
  m_extendedGuid = extendedGuid;
}

CellId StorageManifestRootDeclare::getCellId() const { return m_cellId; }

void StorageManifestRootDeclare::setCellId(const CellId& cellId)
{
  m_cellId = cellId;
}


void StorageManifestRootDeclare::deserialize(QDataStream& ds)
{

  StreamObjectHeader header;
  ds >> header;

  if (header.getType() != getType()) {
    qFatal("Trying to deserialze StreamObject of incorrect header type "
           "(StorageManifestRootDeclare)");
  }

  qint64 origPos = ds.device()->pos();
  ds >> m_extendedGuid;
  ds >> m_cellId;

  if ((origPos + header.getLength()) != (quint64)ds.device()->pos()) {
    qFatal("Something went wrong parsing StorageManifestRootDeclare");
  }
}

void StorageManifestRootDeclare::serialize(QDataStream& ds) const
{
  StreamObjectHeader header(getType(), body_cb());

  ds << header;

  ds << m_extendedGuid;
  ds << m_cellId;
}

quint64 StorageManifestRootDeclare::body_cb() const
{
  return m_extendedGuid.getSizeInFile() + m_cellId.getSizeInFile();
}

StreamObjectType StorageManifestRootDeclare::getType() const
{
  return StreamObjectType::StorageManifestRootDeclare;
}

} // namespace streamObj
} // namespace packStore
} // namespace libmson
