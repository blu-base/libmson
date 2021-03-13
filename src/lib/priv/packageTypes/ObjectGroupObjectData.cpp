#include "ObjectGroupObjectData.h"

#include "dataTypes/CellIdArray.h"
#include "dataTypes/CompactExtGuidArray.h"
#include "dataTypes/CompactUInt64.h"

namespace libmson {
namespace fsshttpb {


ObjectGroupObjectData::ObjectGroupObjectData() {}

std::vector<priv::ExtendedGUID>
ObjectGroupObjectData::getExtendedGuidArray() const
{
  return m_extendedGuidArray;
}

void ObjectGroupObjectData::setExtendedGuidArray(
    const std::vector<priv::ExtendedGUID>& extendedGuidArray)
{
  m_extendedGuidArray = extendedGuidArray;
}

std::vector<CellId> ObjectGroupObjectData::getCellIdArray() const
{
  return m_cellIdArray;
}

void ObjectGroupObjectData::setCellIdArray(
    const std::vector<CellId>& cellIdArray)
{
  m_cellIdArray = cellIdArray;
}

QByteArray ObjectGroupObjectData::getData() const { return m_data; }

void ObjectGroupObjectData::setData(const QByteArray& data) { m_data = data; }

quint64 ObjectGroupObjectData::strObjBody_cb() const
{

  return CompactExtGuidArray::getSizeInFile(m_extendedGuidArray) +
         CellIdArray::getSizeInFile(m_cellIdArray) +
         CompactUInt64::getSizeInFile(m_data.size()) + m_data.size();
}

quint64 ObjectGroupObjectData::cbNextHeader() const
{
  return strObjBody_cb();
}

StreamObjectType ObjectGroupObjectData::getType() const
{
  return StreamObjectType::ObjectGroupObjectData;
}


void ObjectGroupObjectData::push_back(
    IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(obj);
}

IStreamObj_It_t ObjectGroupObjectData::insert(
    IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(pos);
  Q_UNUSED(obj);
  return m_children.end();
}

void ObjectGroupObjectData::deserializeStrObj(
    QDataStream& ds)
{
  CompactExtGuidArray guidArray;
  ds >> guidArray;
  m_extendedGuidArray = guidArray.getElements();

  CellIdArray cellIdArray;
  ds >> cellIdArray;
  m_cellIdArray = cellIdArray.getElements();

  CompactUInt64 size;
  ds >> size;

  m_data = ds.device()->read(size.getValue());
}

void ObjectGroupObjectData::serializeStrObj(
    QDataStream& ds) const
{

  ds << CompactExtGuidArray(m_extendedGuidArray);
  ds << CellIdArray(m_cellIdArray);
  ds << CompactUInt64(m_data.size());

  ds.writeRawData(m_data.data(), m_data.size());
}

} // namespace fsshttpb
} // namespace libmson
