#include "StorageIndexRevisionMapping.h"

#include "dataTypes/CompactExtGuid.h"

namespace libmson {
namespace fsshttpb {

StorageIndexRevisionMapping::StorageIndexRevisionMapping() {}

priv::ExtendedGUID StorageIndexRevisionMapping::getRevision() const
{
  return m_revision;
}

void StorageIndexRevisionMapping::setRevision(
    const priv::ExtendedGUID& revision)
{
  m_revision = revision;
}

priv::ExtendedGUID StorageIndexRevisionMapping::getExtendedGuid() const
{
  return m_extendedGuid;
}

void StorageIndexRevisionMapping::setExtendedGuid(
    const priv::ExtendedGUID& extendedGuid)
{
  m_extendedGuid = extendedGuid;
}

LongExtGuid StorageIndexRevisionMapping::getSerialNumber() const
{
  return m_serialNumber;
}

void StorageIndexRevisionMapping::setSerialNumber(
    const LongExtGuid& serialNumber)
{
  m_serialNumber = serialNumber;
}

quint64 StorageIndexRevisionMapping::strObjBody_cb() const {
  quint64 subtotal = CompactExtGuid(m_revision).getSizeInFile();
  subtotal += CompactExtGuid(m_extendedGuid).getSizeInFile();
  subtotal += m_serialNumber.getSizeInFile();

  return subtotal;
}

quint64 StorageIndexRevisionMapping::cbNextHeader() const
{
  return strObjBody_cb();
}


void StorageIndexRevisionMapping::push_back(IStreamObject_SPtr_t& obj) {
    Q_UNUSED(obj);
}

IStreamObj_It_t StorageIndexRevisionMapping::insert(
    IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(pos);
  Q_UNUSED(obj);
  m_children.clear();
  return m_children.end();
}

void StorageIndexRevisionMapping::deserializeStrObj(QDataStream& ds)
{
  CompactExtGuid guid;
  ds >> guid;
  m_revision = guid.getExtendedGUID();
  ds >> guid;
  m_extendedGuid = guid.getExtendedGUID();

  ds >> m_serialNumber;
}

void StorageIndexRevisionMapping::serializeStrObj(QDataStream& ds) const {
  ds << CompactExtGuid(m_revision);
  ds << CompactExtGuid(m_extendedGuid);
  ds << m_serialNumber;
}

} // namespace fsshttpb
} // namespace libmson
