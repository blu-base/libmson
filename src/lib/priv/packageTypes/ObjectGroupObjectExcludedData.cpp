#include "ObjectGroupObjectExcludedData.h"

#include <QDebug>

#include "dataTypes/CellIdArray.h"
#include "dataTypes/CompactExtGuidArray.h"
#include "dataTypes/CompactUInt64.h"

namespace libmson {
namespace fsshttpb {

ObjectGroupObjectExcludedData::ObjectGroupObjectExcludedData() {}


std::vector<priv::ExtendedGUID>
ObjectGroupObjectExcludedData::getExtendedGuidArray() const
{
  return m_extendedGuidArray;
}

void ObjectGroupObjectExcludedData::setExtendedGuidArray(
    const std::vector<priv::ExtendedGUID>& extendedGuidArray)
{
  m_extendedGuidArray = extendedGuidArray;
}

std::vector<CellId> ObjectGroupObjectExcludedData::getCellIdArray() const
{
  return m_cellIdArray;
}

void ObjectGroupObjectExcludedData::setCellIdArray(
    const std::vector<CellId>& cellIdArray)
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

quint64 ObjectGroupObjectExcludedData::strObjBody_cb() const
{

  return CompactExtGuidArray::getSizeInFile(m_extendedGuidArray) +
         CellIdArray::getSizeInFile(m_cellIdArray) +
         CompactUInt64::getSizeInFile(m_dataSize);
}

quint64 ObjectGroupObjectExcludedData::cbNextHeader() const
{
  return strObjBody_cb();
}

StreamObjectType ObjectGroupObjectExcludedData::getType() const
{
  return StreamObjectType::ObjectGroupObjectExcludedData;
}

void ObjectGroupObjectExcludedData::push_back(IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(obj);
}

IStreamObj_It_t ObjectGroupObjectExcludedData::insert(
    IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(pos);
  Q_UNUSED(obj);
  m_children.clear();
  return m_children.end();
}

void ObjectGroupObjectExcludedData::deserializeStrObj(QDataStream& ds)
{
  qDebug() << "ObjectGroupObjectExcludedData constructured at pos: "
           << QString::number(ds.device()->pos());

  CompactExtGuidArray guidArray;
  ds >> guidArray;
  m_extendedGuidArray = guidArray.getElements();

  CellIdArray cellIdArray;
  ds >> cellIdArray;
  m_cellIdArray = cellIdArray.getElements();

  CompactUInt64 size;
  ds >> size;
  m_dataSize = size.getValue();
}

void ObjectGroupObjectExcludedData::serializeStrObj(QDataStream& ds) const
{
  ds << CompactExtGuidArray(m_extendedGuidArray);
  ds << CellIdArray(m_cellIdArray);
  ds << CompactUInt64(m_dataSize);
}


} // namespace fsshttpb
} // namespace libmson
