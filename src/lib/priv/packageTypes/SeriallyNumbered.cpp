#include "SeriallyNumbered.h"
namespace libmson {
namespace packStore {
namespace streamObj {

LongExtGuid SeriallyNumbered::getSerialNumber() const
{
  return m_serialNumber;
}

void SeriallyNumbered::setSerialNumber(const LongExtGuid& serialNumber)
{
  m_serialNumber = serialNumber;
}


} // namespace streamObj
} // namespace packStore
} // namespace libmson
