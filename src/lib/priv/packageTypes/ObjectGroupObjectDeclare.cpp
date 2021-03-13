#include "ObjectGroupObjectDeclare.h"

#include "dataTypes/CompactUInt64.h"
#include "dataTypes/CompactExtGuid.h"

namespace libmson {
namespace fsshttpb {

ObjectGroupObjectDeclare::ObjectGroupObjectDeclare() {}

priv::ExtendedGUID ObjectGroupObjectDeclare::getExtendedGuid() const
{
  return m_extendedGuid;
}

void ObjectGroupObjectDeclare::setExtendedGuid(
    const priv::ExtendedGUID& extendedGuid)
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


quint64 ObjectGroupObjectDeclare::strObjBody_cb() const
{
  quint64 total{};
  total += CompactExtGuid(m_extendedGuid).getSizeInFile();

  total += CompactUInt64::getSizeInFile(m_partitionId);
  total += CompactUInt64::getSizeInFile(m_dataSize);
  total += CompactUInt64::getSizeInFile(m_objectReferencesCount);
  total += CompactUInt64::getSizeInFile(m_cellReferencesCount);

  return total;
}
quint64 ObjectGroupObjectDeclare::cbNextHeader() const
{
  return strObjBody_cb();
}

StreamObjectType ObjectGroupObjectDeclare::getType() const
{
   return StreamObjectType::ObjectGroupObjectDeclare;
}

void ObjectGroupObjectDeclare::push_back(IStreamObject_SPtr_t& obj)
{
    Q_UNUSED(obj);
}

IStreamObj_It_t ObjectGroupObjectDeclare::insert(IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(pos);
  Q_UNUSED(obj);
  m_children.clear();
  return m_children.end();
}

void ObjectGroupObjectDeclare::deserializeStrObj(QDataStream& ds)
{
  CompactExtGuid guid;
  ds >> guid;
  m_extendedGuid = guid.getExtendedGUID();

  CompactUInt64 c_uint;
  ds >> c_uint;
  m_partitionId = c_uint.getValue();

  ds >> c_uint;
  m_dataSize = c_uint.getValue();

  ds >> c_uint;
  m_objectReferencesCount = c_uint.getValue();

  ds >> c_uint;
  m_cellReferencesCount = c_uint.getValue();
}

void ObjectGroupObjectDeclare::serializeStrObj(QDataStream& ds) const
{
  ds << CompactExtGuid(m_extendedGuid);
  ds << CompactUInt64(m_partitionId);
  ds << CompactUInt64(m_dataSize);
  ds << CompactUInt64(m_objectReferencesCount);
  ds << CompactUInt64(m_cellReferencesCount);
}

} // namespace packStore
} // namespace libmson
