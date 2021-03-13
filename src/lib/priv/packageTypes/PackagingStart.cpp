#include "PackagingStart.h"
#include "DataElementPackage.h"

#include "dataTypes/CompactExtGuid.h"
#include <QDebug>

namespace libmson {
namespace fsshttpb {


priv::ExtendedGUID PackagingStart::getStorageIndex() const
{
  return m_storageIndex;
}

void PackagingStart::setStorageIndex(const priv::ExtendedGUID& storageIndex)
{
  m_storageIndex = storageIndex;
}

QUuid PackagingStart::getGuidCellSchemaId() const { return m_guidCellSchemaId; }

void PackagingStart::setGuidCellSchemaId(QUuid guidCellSchemaId)
{
  m_guidCellSchemaId = guidCellSchemaId;
}

DataElementPackage_WPtr_t PackagingStart::getDataElementPackage()
{
  return std::dynamic_pointer_cast<DataElementPackage>(m_children.at(0));
}

void PackagingStart::setDataElementPackage(DataElementPackage_SPtr_t obj)
{
  m_children.clear();
  m_children.push_back(obj);
}

// std::vector<DataElementPackage_WPtr_t> PackagingStart::getObjects()
//{
//  std::vector<DataElementPackage_WPtr_t> vec{};

//  vec.reserve(m_children.size());
//  std::transform(
//      m_children.cbegin(), m_children.cend(), std::back_inserter(vec),
//      [](auto& ptr) {
//        return std::dynamic_pointer_cast<DataElementPackage>(ptr);
//      });

//  return vec;
//}

quint64 PackagingStart::strObjBody_cb() const
{

  quint64 cb = std::accumulate(
      IStreamObject::cbegin(), IStreamObject::cend(), 0,
      [](quint64 sum, auto& ptr) { return sum + ptr->getSizeInFile(); });

  return CompactExtGuid::getSizeInFile(m_storageIndex) +
         sizeof(QUuid) + cb;
}

quint64 PackagingStart::cbNextHeader() const
{
  return CompactExtGuid::getSizeInFile(m_storageIndex) +
         sizeof(QUuid);
}

void PackagingStart::deserializeStrObj(QDataStream& ds)
{

  CompactExtGuid guid;
  ds >> guid;
  m_storageIndex = guid.getExtendedGUID();

  ds >> m_guidCellSchemaId;


  auto dataelementpackage = std::make_shared<DataElementPackage>();
  m_children.clear();
  m_children.push_back(dataelementpackage);

  ds >> *dataelementpackage;



  if (!isObjectStreamEnd(ds)) {
    qCritical()
        << "PackagingStart is not terminated with StreamObjectHeaderEnd";
  }
}

void PackagingStart::serializeStrObj(QDataStream& ds) const
{
  ds << CompactExtGuid(m_storageIndex);
  ds << m_guidCellSchemaId;

  ds << *std::dynamic_pointer_cast<DataElementPackage>(m_children.at(0));
}

void PackagingStart::push_back(IStreamObject_SPtr_t& obj)
{

  if (obj->getType() == StreamObjectType::DataElementPackage) {
    m_children.push_back(obj);
  }
}

//void PackagingStart::push_back(DataElementPackage_SPtr_t& obj)
//{
//  m_children.push_back(std::static_pointer_cast<IStreamObject>(obj));
//}

//IStreamObj_It_t PackagingStart::insert(
//    IStreamObj_It_t pos, const DataElementPackage_SPtr_t& obj)
//{
//  return insert(pos, std::static_pointer_cast<IStreamObject>(obj));
//}

IStreamObj_It_t
PackagingStart::insert(IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  if (obj->getType() == StreamObjectType::DataElementPackage) {
    return m_children.insert(pos, obj);
  }

  return m_children.end();
}

//DataElementPackage_WPtr_t PackagingStart::at(size_t pos)
//{
//  if (!isCompound() && size() > pos) {
//    return std::dynamic_pointer_cast<DataElementPackage>(m_children.at(pos));
//  }

//  return DataElementPackage_WPtr_t();
//}

} // namespace fsshttpb
} // namespace libmson
