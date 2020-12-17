#include "DataElementPackage.h"
namespace libmson {
namespace packStore {
QByteArray DataElementPackage::getData() const { return m_data; }

void DataElementPackage::setData(const QByteArray& data) { m_data = data; }

std::vector<DataElementPackage_SPtr_t> DataElementPackage::getChildren() const
{
  return m_children;
}

std::vector<DataElementPackage_SPtr_t>& DataElementPackage::children()
{
  return m_children;
}

void DataElementPackage::setChildren(
    const std::vector<DataElementPackage_SPtr_t>& children)
{
  m_children = children;
}

DataElement_SPtr_t DataElementPackage::getDataElement() const
{
  return m_dataElement;
}

void DataElementPackage::setDataElement(const DataElement_SPtr_t& dataElement)
{
  m_dataElement = dataElement;
}

DataElementPackage::DataElementPackage() {}

StreamObjectHeader_SPtr_t DataElementPackage::getHeader() const
{
  return m_header;
}

void DataElementPackage::setHeader(const StreamObjectHeader_SPtr_t& header)
{
  m_header = header;
}

// std::shared_ptr<DataElement> DataElementPackage::getData() const
//{
//  return m_data;
//}

// void DataElementPackage::setData(const std::shared_ptr<DataElement>& data)
//{
//  m_data = data;
//}


} // namespace packStore
} // namespace libmson
