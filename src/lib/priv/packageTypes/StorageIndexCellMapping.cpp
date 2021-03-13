#include "StorageIndexCellMapping.h"

#include "dataTypes/CompactExtGuid.h"

namespace libmson {
namespace fsshttpb {

CellId StorageIndexCellMapping::getCellId() const
{
  return m_cellId;
}

void StorageIndexCellMapping::setCellId(const CellId& cellId)
{
  m_cellId = cellId;
}

priv::ExtendedGUID StorageIndexCellMapping::getExtendedGuid() const
{
  return m_extendedGuid;
}

void StorageIndexCellMapping::setExtendedGuid(
    const priv::ExtendedGUID& extendedGuid)
{
  m_extendedGuid = extendedGuid;
}

LongExtGuid StorageIndexCellMapping::getSerialNumber() const
{
  return m_serialNumber;
}

void StorageIndexCellMapping::setSerialNumber(
    const LongExtGuid& serialNumber)
{
  m_serialNumber = serialNumber;
}

quint64 StorageIndexCellMapping::strObjBody_cb() const
{
  return m_cellId.getSizeInFile() +
         CompactExtGuid(m_extendedGuid).getSizeInFile() +
         m_serialNumber.getSizeInFile();
}

quint64 StorageIndexCellMapping::cbNextHeader() const
{
  return strObjBody_cb();
}


void StorageIndexCellMapping::push_back(IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(obj);
}

IStreamObj_It_t StorageIndexCellMapping::insert(
    libmson::fsshttpb::IStreamObj_It_t pos,
    const libmson::fsshttpb::IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(pos);
  Q_UNUSED(obj);
  m_children.clear();
  return m_children.end();
}

void StorageIndexCellMapping::deserializeStrObj(QDataStream& ds)
{

  ds >> m_cellId;

  CompactExtGuid guid;
  ds >> guid;
  m_extendedGuid = guid.getExtendedGUID();

  ds >> m_serialNumber;
}

void StorageIndexCellMapping::serializeStrObj(QDataStream& ds) const
{
  ds << m_cellId;
  ds << CompactExtGuid(m_extendedGuid);
  ds << m_serialNumber;
}


} // namespace fsshttpb
} // namespace libmson
