#include "ObjectGroupObjectDataBlobReference.h"
namespace libmson {
namespace packStore {
namespace streamObj {

ObjectGroupObjectDataBlobReference::ObjectGroupObjectDataBlobReference() {}


CompactExtGuidArray
ObjectGroupObjectDataBlobReference::getObjectExtGuidArray() const
{
  return m_objectExtGuidArray;
}

void ObjectGroupObjectDataBlobReference::setObjectExtGuidArray(
    const CompactExtGuidArray& objectExtGuidArray)
{
  m_objectExtGuidArray = objectExtGuidArray;
}

CellIdArray ObjectGroupObjectDataBlobReference::getCellIdArray() const
{
  return m_cellIdArray;
}

void ObjectGroupObjectDataBlobReference::setCellIdArray(
    const CellIdArray& cellIdArray)
{
  m_cellIdArray = cellIdArray;
}

CompactExtGuid ObjectGroupObjectDataBlobReference::getExtendedGuid() const
{
  return m_extendedGuid;
}

void ObjectGroupObjectDataBlobReference::setExtendedGuid(
    const CompactExtGuid& extendedGuid)
{
  m_extendedGuid = extendedGuid;
}


void ObjectGroupObjectDataBlobReference::deserialize(QDataStream& ds)
{
  StreamObjectHeader header;
  ds >> header;
  if (header.getType() != getType()) {
    qFatal("Trying to deserialze StreamObject of incorrect header type "
           "(ObjectGroupObjectDataBlobReference)");
  }
  qint64 origPos = ds.device()->pos();

  ds >> m_objectExtGuidArray;
  ds >> m_cellIdArray;
  ds >> m_extendedGuid;

  if ((origPos + header.getLength()) != (quint64)ds.device()->pos()) {
    qFatal("Something went wrong parsing ObjectGroupObjectDataBlobReference");
  }
}

void ObjectGroupObjectDataBlobReference::serialize(QDataStream& ds) const
{
  StreamObjectHeader header(getType(), body_cb());

  ds << header;

  ds << m_objectExtGuidArray;
  ds << m_cellIdArray;
  ds << m_extendedGuid;
}

quint64 ObjectGroupObjectDataBlobReference::body_cb() const
{
  return m_objectExtGuidArray.getSizeInFile() + m_cellIdArray.getSizeInFile() +
         m_extendedGuid.getSizeInFile();
}

StreamObjectType ObjectGroupObjectDataBlobReference::getType() const
{
  return StreamObjectType::ObjectGroupObjectDataBLOBReference;
}
} // namespace streamObj
} // namespace packStore
} // namespace libmson
