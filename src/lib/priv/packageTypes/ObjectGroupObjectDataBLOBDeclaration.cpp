#include "ObjectGroupObjectDataBLOBDeclaration.h"

#include "dataTypes/CompactExtGuid.h"
#include "dataTypes/CompactUInt64.h"

namespace libmson {
namespace fsshttpb {

ObjectGroupObjectDataBLOBDeclaration::ObjectGroupObjectDataBLOBDeclaration() {}


priv::ExtendedGUID ObjectGroupObjectDataBLOBDeclaration::getExtendedGuid() const
{
  return m_extendedGuid;
}

void ObjectGroupObjectDataBLOBDeclaration::setExtendedGuid(
    const priv::ExtendedGUID& extendedGuid)
{
  m_extendedGuid = extendedGuid;
}

priv::ExtendedGUID
ObjectGroupObjectDataBLOBDeclaration::getBlobExtendedGuid() const
{
  return m_blobExtendedGuid;
}

void ObjectGroupObjectDataBLOBDeclaration::setBlobExtendedGuid(
    const priv::ExtendedGUID& blobExtendedGuid)
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

quint64 ObjectGroupObjectDataBLOBDeclaration::strObjBody_cb() const
{

  quint64 total = CompactExtGuid(m_extendedGuid).getSizeInFile();

  total += CompactExtGuid::getSizeInFile(m_blobExtendedGuid);
  total += CompactUInt64::getSizeInFile(m_partitionId);
  total += CompactUInt64::getSizeInFile(m_objectReferencesCount);
  total += CompactUInt64::getSizeInFile(m_cellReferencesCount);

  return total;
}

quint64 ObjectGroupObjectDataBLOBDeclaration::cbNextHeader() const
{
  return strObjBody_cb();
}

StreamObjectType ObjectGroupObjectDataBLOBDeclaration::getType() const
{
  return StreamObjectType::ObjectGroupObjectDataBLOBDeclaration;
}

void ObjectGroupObjectDataBLOBDeclaration::push_back(IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(obj);
}

IStreamObj_It_t ObjectGroupObjectDataBLOBDeclaration::insert(
    IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(pos);
  Q_UNUSED(obj);
  m_children.clear();
  return m_children.end();
}

void ObjectGroupObjectDataBLOBDeclaration::deserializeStrObj(QDataStream& ds)
{

  CompactExtGuid guid;
  ds >> guid;
  m_extendedGuid = guid.getExtendedGUID();

  ds >> guid;
  m_blobExtendedGuid = guid.getExtendedGUID();

  CompactUInt64 c_uint;
  ds >> c_uint;
  m_partitionId = c_uint.getValue();

  ds >> c_uint;
  m_objectReferencesCount = c_uint.getValue();

  ds >> c_uint;
  m_cellReferencesCount = c_uint.getValue();
}

void ObjectGroupObjectDataBLOBDeclaration::serializeStrObj(
    QDataStream& ds) const
{
  ds << CompactExtGuid(m_extendedGuid);
  ds << CompactExtGuid(m_blobExtendedGuid);
  ds << CompactUInt64(m_partitionId);
  ds << CompactUInt64(m_objectReferencesCount);
  ds << CompactUInt64(m_cellReferencesCount);
}

} // namespace fsshttpb
} // namespace libmson
