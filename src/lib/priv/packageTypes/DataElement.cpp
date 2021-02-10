#include "DataElement.h"

namespace libmson {
namespace packStore {

DataElementBody_SPtr_t DataElement::getBody() const { return m_body; }

void DataElement::setBody(const DataElementBody_SPtr_t& body) { m_body = body; }

DataElement::DataElement() : m_dataElementType() {}

DataElement::DataElement(
    const CompactExtGuid& dataElementExtGuid, const LongExtGuid& serialNumber,
    const quint64& dataElementType)
    : m_dataElementExtGuid(dataElementExtGuid), m_serialNumber(serialNumber),
      m_dataElementType(dataElementType)
{
}

CompactExtGuid DataElement::getDataElementExtGuid() const
{
  return m_dataElementExtGuid;
}

void DataElement::setDataElementExtGuid(
    const CompactExtGuid& dataElementExtGuid)
{
  m_dataElementExtGuid = dataElementExtGuid;
}

LongExtGuid DataElement::getSerialNumber() const { return m_serialNumber; }

void DataElement::setSerialNumber(const LongExtGuid& serialNumber)
{
  m_serialNumber = serialNumber;
}

quint64 DataElement::getDataElementType() const { return m_dataElementType; }

void DataElement::setDataElementType(const quint64& dataElementType)
{
  m_dataElementType = dataElementType;
}
DataElementType DataElement::getDataElementTypeEnum() const
{
  return static_cast<DataElementType>(m_dataElementType);
}

void DataElement::setDataElementType(const DataElementType& dataElementType)
{
  m_dataElementType = static_cast<quint64>(dataElementType);
}


} // namespace packStore
} // namespace libmson
