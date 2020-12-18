#include "ObjectGroupObjectDeclare.h"

namespace libmson {
namespace packStore {
namespace streamObj {

ObjectGroupObjectDeclare::ObjectGroupObjectDeclare() {}

CompactExtGuid ObjectGroupObjectDeclare::getExtendedGuid() const
{
  return m_extendedGuid;
}

void ObjectGroupObjectDeclare::setExtendedGuid(
    const CompactExtGuid& extendedGuid)
{
  m_extendedGuid = extendedGuid;
}

quint64 ObjectGroupObjectDeclare::getPartitionId() const
{
  return m_partitionId;
}

void ObjectGroupObjectDeclare::setPartitionId(const quint64& partitionId)
{
  m_partitionId = partitionId;
}

quint64 ObjectGroupObjectDeclare::getDataSize() const { return m_dataSize; }

void ObjectGroupObjectDeclare::setDataSize(const quint64& dataSize)
{
  m_dataSize = dataSize;
}

quint64 ObjectGroupObjectDeclare::getObjectReferencesCount() const
{
  return m_objectReferencesCount;
}

void ObjectGroupObjectDeclare::setObjectReferencesCount(
    const quint64& objectReferencesCount)
{
  m_objectReferencesCount = objectReferencesCount;
}

quint64 ObjectGroupObjectDeclare::getCellReferencesCount() const
{
  return m_cellReferencesCount;
}

void ObjectGroupObjectDeclare::setCellReferencesCount(
    const quint64& cellReferencesCount)
{
  m_cellReferencesCount = cellReferencesCount;
}


void ObjectGroupObjectDeclare::deserialize(QDataStream& ds)
{
  StreamObjectHeader header;
  ds >> header;

  if (header.getType() != getType()) {
    qFatal("Trying to deserialze StreamObject of incorrect header type "
           "(ObjectGroupObjectDeclare)");
  }

  qint64 origPos = ds.device()->pos();

  ds >> m_extendedGuid;

  CompactUInt64 c_uint;
  ds >> c_uint;
  m_partitionId = c_uint.getValue();


  ds >> c_uint;
  m_dataSize = c_uint.getValue();


  ds >> c_uint;
  m_objectReferencesCount = c_uint.getValue();


  ds >> c_uint;
  m_cellReferencesCount = c_uint.getValue();


  if ((origPos + header.getLength()) != (quint64)ds.device()->pos()) {
    qFatal("Something went wrong parsing ObjectGroupObjectDeclare");
  }
}

void ObjectGroupObjectDeclare::serialize(QDataStream& ds) const
{
  StreamObjectHeader header(getType(), body_cb());

  ds << header;

  ds << m_extendedGuid;

  ds << CompactUInt64(m_partitionId);
  ds << CompactUInt64(m_dataSize);
  ds << CompactUInt64(m_objectReferencesCount);
  ds << CompactUInt64(m_cellReferencesCount);
}

quint64 ObjectGroupObjectDeclare::body_cb() const
{
  quint64 total{};
  total += m_extendedGuid.getSizeInFile();

  total += CompactUInt64::getSizeInFile(m_partitionId);
  total += CompactUInt64::getSizeInFile(m_dataSize);
  total += CompactUInt64::getSizeInFile(m_objectReferencesCount);
  total += CompactUInt64::getSizeInFile(m_cellReferencesCount);

  return total;
}

StreamObjectType ObjectGroupObjectDeclare::getType() const
{
  return StreamObjectType::ObjectGroupObjectDeclare;
}

} // namespace streamObj
} // namespace packStore
} // namespace libmson
