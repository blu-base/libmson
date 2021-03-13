#include "StorageIndexManifestMapping.h"

#include "dataTypes/CompactExtGuid.h"

namespace libmson {
namespace fsshttpb {

priv::ExtendedGUID StorageIndexManifestMapping::getExtendedGuid() const
{
  return m_extendedGuid;
}

void StorageIndexManifestMapping::setExtendedGuid(
    const priv::ExtendedGUID& extendedGuid)
{
  m_extendedGuid = extendedGuid;
}

LongExtGuid StorageIndexManifestMapping::getSerialNumber() const
{
  return m_serialNumber;
}

void StorageIndexManifestMapping::setSerialNumber(
    const LongExtGuid& serialNumber)
{
  m_serialNumber = serialNumber;
}


quint64 StorageIndexManifestMapping::strObjBody_cb() const
{
  return CompactExtGuid(m_extendedGuid).getSizeInFile() +
         m_serialNumber.getSizeInFile();
}

quint64 StorageIndexManifestMapping::cbNextHeader() const
{
  return strObjBody_cb();
}


void StorageIndexManifestMapping::push_back(
    IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(obj);
}

IStreamObj_It_t
StorageIndexManifestMapping::insert(
    IStreamObj_It_t pos,
    const IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(pos);
  Q_UNUSED(obj);
  m_children.clear();
  return m_children.end();
}

void StorageIndexManifestMapping::deserializeStrObj(
    QDataStream& ds)
{
  CompactExtGuid guid;
  ds >> guid;
  m_extendedGuid = guid.getExtendedGUID();

  ds >> m_serialNumber;
}

void StorageIndexManifestMapping::serializeStrObj(
    QDataStream& ds) const
{
  ds << CompactExtGuid(m_extendedGuid);
  ds << m_serialNumber;
}


} // namespace fsshttpb
} // namespace libmson
