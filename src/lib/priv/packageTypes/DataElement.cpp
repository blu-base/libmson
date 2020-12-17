#include "DataElement.h"

namespace libmson {
namespace packStore {

DataElementBody_SPtr_t DataElement::getBody() const { return m_body; }

void DataElement::setBody(const DataElementBody_SPtr_t& body) { m_body = body; }

DataElement::DataElement()
    : m_dataElementExtGuid(), m_serialNumber(), m_dataElementType()
{
}

DataElement::DataElement(
    const CompactExtGuid& dataElementExtGuid, const LongExtGuid& serialNumber,
    const CompactUInt64& dataElementType)
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

CompactUInt64 DataElement::getDataElementType() const
{
  return m_dataElementType;
}

void DataElement::setDataElementType(const CompactUInt64& dataElementType)
{
  m_dataElementType = dataElementType;
}


} // namespace packStore
} // namespace libmson
