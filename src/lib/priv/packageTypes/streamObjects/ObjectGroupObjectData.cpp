#include "ObjectGroupObjectData.h"
namespace libmson {
namespace packStore {
namespace streamObj {


ObjectGroupObjectData::ObjectGroupObjectData() {}

CompactExtGuidArray ObjectGroupObjectData::getExtendedGuidArray() const
{
  return m_extendedGuidArray;
}

void ObjectGroupObjectData::setExtendedGuidArray(
    const CompactExtGuidArray& extendedGuidArray)
{
  m_extendedGuidArray = extendedGuidArray;
}

CellIdArray ObjectGroupObjectData::getCellIdArray() const
{
  return m_cellIdArray;
}

void ObjectGroupObjectData::setCellIdArray(const CellIdArray& cellIdArray)
{
  m_cellIdArray = cellIdArray;
}

BinaryItem ObjectGroupObjectData::getData() const { return m_data; }

void ObjectGroupObjectData::setData(const BinaryItem& data) { m_data = data; }


void ObjectGroupObjectData::deserialize(QDataStream& ds)
{
  StreamObjectHeader header;
  ds >> header;
  if (header.getType() != getType()) {
    qFatal("Trying to deserialze StreamObject of incorrect header type "
           "(ObjectGroupObjectData)");
  }
  qint64 origPos = ds.device()->pos();

  ds >> m_extendedGuidArray;
  ds >> m_cellIdArray;
  ds >> m_data;

  if ((origPos + header.getLength()) != (quint64)ds.device()->pos()) {
    qFatal("Something went wrong parsing ObjectGroupObjectData");
  }
}

void ObjectGroupObjectData::serialize(QDataStream& ds) const
{
  StreamObjectHeader header(getType(), body_cb());

  ds << header;

  ds << m_extendedGuidArray;
  ds << m_cellIdArray;
  ds << m_data;
}

quint64 ObjectGroupObjectData::body_cb() const
{
  return m_extendedGuidArray.getSizeInFile() + m_cellIdArray.getSizeInFile() +
         m_data.getSizeInFile();
}

StreamObjectType ObjectGroupObjectData::getType() const
{
  return StreamObjectType::ObjectGroupObjectData;
}

} // namespace streamObj
} // namespace packStore
} // namespace libmson
