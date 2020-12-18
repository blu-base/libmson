#include "ObjectGroupObjectDataBLOBDeclaration.h"
namespace libmson {
namespace packStore {
namespace streamObj {

ObjectGroupObjectDataBLOBDeclaration::ObjectGroupObjectDataBLOBDeclaration() {}


CompactExtGuid ObjectGroupObjectDataBLOBDeclaration::getExtendedGuid() const
{
  return m_extendedGuid;
}

void ObjectGroupObjectDataBLOBDeclaration::setExtendedGuid(
    const CompactExtGuid& extendedGuid)
{
  m_extendedGuid = extendedGuid;
}

CompactExtGuid ObjectGroupObjectDataBLOBDeclaration::getBlobExtendedGuid() const
{
  return m_blobExtendedGuid;
}

void ObjectGroupObjectDataBLOBDeclaration::setBlobExtendedGuid(
    const CompactExtGuid& blobExtendedGuid)
{
  m_blobExtendedGuid = blobExtendedGuid;
}

quint64 ObjectGroupObjectDataBLOBDeclaration::getPartitionId() const
{
  return m_partitionId;
}

void ObjectGroupObjectDataBLOBDeclaration::setPartitionId(
    const quint64& partitionId)
{
  m_partitionId = partitionId;
}

quint64 ObjectGroupObjectDataBLOBDeclaration::getObjectReferencesCount() const
{
  return m_objectReferencesCount;
}

void ObjectGroupObjectDataBLOBDeclaration::setObjectReferencesCount(
    const quint64& objectReferencesCount)
{
  m_objectReferencesCount = objectReferencesCount;
}

quint64 ObjectGroupObjectDataBLOBDeclaration::getCellReferencesCount() const
{
  return m_cellReferencesCount;
}

void ObjectGroupObjectDataBLOBDeclaration::setCellReferencesCount(
    const quint64& cellReferencesCount)
{
  m_cellReferencesCount = cellReferencesCount;
}


void ObjectGroupObjectDataBLOBDeclaration::deserialize(QDataStream& ds)
{
  StreamObjectHeader header;
  ds >> header;

  if (header.getType() != getType()) {
    qFatal("Trying to deserialze StreamObject of incorrect header type "
           "(ObjectGroupObjectDeclare)");
  }

  qint64 origPos = ds.device()->pos();

  ds >> m_extendedGuid;
  ds >> m_blobExtendedGuid;

  CompactUInt64 c_uint;
  ds >> c_uint;
  m_partitionId = c_uint.getValue();

  ds >> c_uint;
  m_objectReferencesCount = c_uint.getValue();

  ds >> c_uint;
  m_cellReferencesCount = c_uint.getValue();


  if ((origPos + header.getLength()) != (quint64)ds.device()->pos()) {
    qFatal("Something went wrong parsing ObjectGroupObjectDeclare");
  }
}

void ObjectGroupObjectDataBLOBDeclaration::serialize(QDataStream& ds) const
{
  StreamObjectHeader header(getType(), body_cb());

  ds << header;

  ds << m_extendedGuid;
  ds << m_blobExtendedGuid;

  ds << CompactUInt64(m_partitionId);
  ds << CompactUInt64(m_objectReferencesCount);
  ds << CompactUInt64(m_cellReferencesCount);
}

quint64 ObjectGroupObjectDataBLOBDeclaration::body_cb() const
{
  quint64 total{};
  total += m_extendedGuid.getSizeInFile();

  total += CompactUInt64::getSizeInFile(m_partitionId);
  total += CompactUInt64::getSizeInFile(m_objectReferencesCount);
  total += CompactUInt64::getSizeInFile(m_cellReferencesCount);

  return total;
}

StreamObjectType ObjectGroupObjectDataBLOBDeclaration::getType() const
{
  return StreamObjectType::ObjectGroupObjectDataBLOBDeclaration;
}
} // namespace streamObj
} // namespace packStore
} // namespace libmson
