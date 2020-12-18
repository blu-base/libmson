#include "StorageIndexCellMapping.h"
namespace libmson {
namespace packStore {
namespace streamObj {

StorageIndexCellMapping::StorageIndexCellMapping() {}

CellId StorageIndexCellMapping::getCellId() const { return m_cellId; }

void StorageIndexCellMapping::setCellId(const CellId& cellId)
{
  m_cellId = cellId;
}

CompactExtGuid StorageIndexCellMapping::getExtendedGuid() const
{
  return m_extendedGuid;
}

void StorageIndexCellMapping::setExtendedGuid(
    const CompactExtGuid& extendedGuid)
{
  m_extendedGuid = extendedGuid;
}


quint64 StorageIndexCellMapping::body_cb() const
{
  quint64 subtotal{};
  subtotal += m_cellId.getSizeInFile();
  subtotal += m_extendedGuid.getSizeInFile();
  subtotal += m_serialNumber.getSizeInFile();

  return subtotal;
}

StreamObjectType StorageIndexCellMapping::getType() const
{
  return StreamObjectType::StorageIndexCellMapping;
}


void StorageIndexCellMapping::deserialize(QDataStream& ds)
{

  StreamObjectHeader header;
  ds >> header;

  if (header.getType() != getType()) {
    qFatal("Trying to deserialze StreamObject of incorrect header type "
           "(StorageIndexCellMapping)");
  }

  qint64 origPos = ds.device()->pos();

  ds >> m_cellId;
  ds >> m_extendedGuid;
  ds >> m_serialNumber;

  if ((origPos + header.getLength()) != (quint64)ds.device()->pos()) {
    qFatal("Something went wrong parsing StorageIndexCellMapping");
  }
}

void StorageIndexCellMapping::serialize(QDataStream& ds) const
{

  StreamObjectHeader header(getType(), body_cb());

  ds << header;
  ds << m_cellId;
  ds << m_extendedGuid;
  ds << m_serialNumber;
}

} // namespace streamObj
} // namespace packStore
} // namespace libmson
