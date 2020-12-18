#include "ObjectGroupObjectExcludedData.h"

namespace libmson {
namespace packStore {
namespace streamObj {
ObjectGroupObjectExcludedData::ObjectGroupObjectExcludedData() {}


CompactExtGuidArray ObjectGroupObjectExcludedData::getExtendedGuidArray() const
{
  return m_extendedGuidArray;
}

void ObjectGroupObjectExcludedData::setExtendedGuidArray(
    const CompactExtGuidArray& extendedGuidArray)
{
  m_extendedGuidArray = extendedGuidArray;
}

CellIdArray ObjectGroupObjectExcludedData::getCellIdArray() const
{
  return m_cellIdArray;
}

void ObjectGroupObjectExcludedData::setCellIdArray(
    const CellIdArray& cellIdArray)
{
  m_cellIdArray = cellIdArray;
}

quint64 ObjectGroupObjectExcludedData::getDataSize() const
{
  return m_dataSize;
}

void ObjectGroupObjectExcludedData::setDataSize(const quint64& dataSize)
{
  m_dataSize = dataSize;
}


void ObjectGroupObjectExcludedData::deserialize(QDataStream& ds)
{
  StreamObjectHeader header;
  ds >> header;
  if (header.getType() != getType()) {
    qFatal("Trying to deserialze StreamObject of incorrect header type "
           "(ObjectGroupObjectExcludedData)");
  }
  qint64 origPos = ds.device()->pos();

  ds >> m_extendedGuidArray;
  ds >> m_cellIdArray;

  CompactUInt64 dataSize;
  ds >> dataSize;

  m_dataSize = dataSize.getValue();

  if ((origPos + header.getLength()) != (quint64)ds.device()->pos()) {
    qFatal("Something went wrong parsing ObjectGroupObjectExcludedData");
  }
}

void ObjectGroupObjectExcludedData::serialize(QDataStream& ds) const {
  StreamObjectHeader header(getType(), body_cb());

  ds << header;

  ds << m_extendedGuidArray;
  ds << m_cellIdArray;
  ds << CompactUInt64(m_dataSize);
}

quint64 ObjectGroupObjectExcludedData::body_cb() const {
  return m_extendedGuidArray.getSizeInFile() + m_cellIdArray.getSizeInFile() +
         CompactUInt64::getSizeInFile(m_dataSize);
}

StreamObjectType ObjectGroupObjectExcludedData::getType() const
{
  return StreamObjectType::ObjectGroupObjectExcludedData;
}


} // namespace streamObj
} // namespace packStore
} // namespace libmson
