#include "DataElementPackage.h"

#include "DataElement.h"


namespace libmson {
namespace fsshttpb {

DataElementPackage::DataElementPackage() {}

std::vector<DataElement_WPtr_t> DataElementPackage::getObjects()
{
  std::vector<DataElement_WPtr_t> vec{};

  vec.reserve(m_children.size());
  std::transform(
      m_children.cbegin(), m_children.cend(), std::back_inserter(vec),
      [](auto& ptr) { return std::dynamic_pointer_cast<DataElement>(ptr); });

  return vec;
}

std::vector<DataElement_WPtr_t> DataElementPackage::getDataElements()
{
  return getObjects();
}

DataElement_WPtr_t DataElementPackage::at(size_t pos)
{
  return std::dynamic_pointer_cast<DataElement>(m_children.at(pos));
}

void DataElementPackage::push_back(IStreamObject_SPtr_t& obj)
{
  if (obj->getType() == StreamObjectType::DataElement) {
    m_children.push_back(obj);
  }
}
void DataElementPackage::push_back(DataElement_SPtr_t& obj)
{
  m_children.push_back(std::static_pointer_cast<IStreamObject>(obj));
}

IStreamObj_It_t
DataElementPackage::insert(IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  if (obj->getType() == StreamObjectType::DataElement) {
    return m_children.insert(pos, obj);
  }

  return m_children.end();
}

IStreamObj_It_t
DataElementPackage::insert(IStreamObj_It_t pos, const DataElement_SPtr_t& obj)
{
  return m_children.insert(pos, std::static_pointer_cast<IStreamObject>(obj));
}

quint64 DataElementPackage::strObjBody_cb() const
{
  quint64 cb = std::accumulate(
      IStreamObject::cbegin(), IStreamObject::cend(), 0,
      [](quint64 sum, auto& ptr) { return sum + ptr->getSizeInFile(); });

  return sizeof(m_reserved) + cb;
}

quint64 DataElementPackage::cbNextHeader() const
{
  return 1;
}

void DataElementPackage::deserializeStrObj(QDataStream& ds)
{
  ds >> m_reserved;

  while (!isObjectStreamEnd(ds)) {
    auto package = std::make_shared<DataElement>();
    m_children.push_back(package);
    ds >> *package;

  }
}

void DataElementPackage::serializeStrObj(QDataStream& ds) const
{
  quint8 reserved = 0;
  ds << reserved;

  for (auto ptr : m_children) {
    ds << *std::dynamic_pointer_cast<DataElement>(ptr);
  }
}


} // namespace fsshttpb
} // namespace libmson
