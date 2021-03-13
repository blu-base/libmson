#include "ObjectGroupObjectDataBLOBReference.h"

#include "dataTypes/CellIdArray.h"
#include "dataTypes/CompactExtGuid.h"
#include "dataTypes/CompactExtGuidArray.h"

namespace libmson {
namespace fsshttpb {

ObjectGroupObjectDataBLOBReference::ObjectGroupObjectDataBLOBReference() {}


std::vector<priv::ExtendedGUID>
ObjectGroupObjectDataBLOBReference::getObjectExtGuidArray() const
{
  return m_objectExtGuidArray;
}

void ObjectGroupObjectDataBLOBReference::setObjectExtGuidArray(
    const std::vector<priv::ExtendedGUID>& objectExtGuidArray)
{
  m_objectExtGuidArray = objectExtGuidArray;
}

std::vector<CellId> ObjectGroupObjectDataBLOBReference::getCellIdArray() const
{
  return m_cellIdArray;
}

void ObjectGroupObjectDataBLOBReference::setCellIdArray(
    const std::vector<CellId>& cellIdArray)
{
  m_cellIdArray = cellIdArray;
}

priv::ExtendedGUID ObjectGroupObjectDataBLOBReference::getExtendedGuid() const
{
  return m_extendedGuid;
}

void ObjectGroupObjectDataBLOBReference::setExtendedGuid(
    const priv::ExtendedGUID& extendedGuid)
{
  m_extendedGuid = extendedGuid;
}


quint64 ObjectGroupObjectDataBLOBReference::strObjBody_cb() const
{

  return CompactExtGuidArray::getSizeInFile(m_objectExtGuidArray) +
         CellIdArray::getSizeInFile(m_cellIdArray) +
         CompactExtGuid::getSizeInFile(m_extendedGuid);
}

quint64 ObjectGroupObjectDataBLOBReference::cbNextHeader() const
{
  return strObjBody_cb();
}

StreamObjectType ObjectGroupObjectDataBLOBReference::getType() const
{
  return StreamObjectType::ObjectGroupObjectDataBLOBReference;
}


void ObjectGroupObjectDataBLOBReference::push_back(IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(obj);
}

IStreamObj_It_t ObjectGroupObjectDataBLOBReference::insert(
    IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(pos);
  Q_UNUSED(obj);
  return m_children.end();
}

void ObjectGroupObjectDataBLOBReference::deserializeStrObj(QDataStream& ds)
{
  CompactExtGuidArray guidArray;
  ds >> guidArray;
  m_objectExtGuidArray = guidArray.getElements();

  CellIdArray cellIdArray;
  ds >> cellIdArray;
  m_cellIdArray = cellIdArray.getElements();

  CompactExtGuid guid;
  ds >> guid;
  m_extendedGuid = guid.getExtendedGUID();
}

void ObjectGroupObjectDataBLOBReference::serializeStrObj(QDataStream& ds) const
{
  ds << CompactExtGuidArray(m_objectExtGuidArray);
  ds << CellIdArray(m_cellIdArray);
  ds << CompactExtGuid(m_extendedGuid);
}

} // namespace fsshttpb
} // namespace libmson
