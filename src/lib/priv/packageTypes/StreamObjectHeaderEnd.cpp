#include "StreamObjectHeaderEnd.h"

#include "StreamObjectHeader.h"
namespace libmson {
namespace packStore {
StreamObjectHeaderEnd::StreamObjectHeaderEnd(
    const std::shared_ptr<StreamObjectHeader>& parent)
    : m_parent(parent)
{
}

quint64 StreamObjectHeaderEnd::getSizeInFile() const
{
  quint16 typeVal = static_cast<uint16_t>(m_parent.lock()->getType());

  if ((typeVal >> 6) == 0) {
    return 1;
  }
  else {
    return 2;
  }
}

void StreamObjectHeaderEnd::deserialize(QDataStream& ds)
{
  uint8_t typeByte;
  ds >> typeByte;

  if ((typeByte & 0x3) == 1) {
    /* 8 bit header end */

    uint8_t typeVal = typeByte >> 2;

    if (validStreamObjectTypeValues.find(typeVal) ==
        validStreamObjectTypeValues.end()) {
      qFatal("StreamObjectHeaderEnd contains invalid type value");
    }
    if (static_cast<StreamObjectType>(typeVal) != m_parent.lock()->getType()) {
      qFatal("StreamObjectHeaderEnd's type does not match StreamObjectHeader's "
             "type");
    }
  }
  else {
    /* 16 bit header end */
    uint8_t highByte;
    ds >> highByte;

    uint16_t typeVal = (highByte << 6) + (typeByte >> 2);

    if (validStreamObjectTypeValues.find(typeVal) ==
        validStreamObjectTypeValues.end()) {
      qFatal("StreamObjectHeaderEnd contains invalid type value");
    }
    if (static_cast<StreamObjectType>(typeVal) != m_parent.lock()->getType()) {
      qFatal("StreamObjectHeaderEnd's type does not match StreamObjectHeader's "
             "type");
    }
  }
}

void StreamObjectHeaderEnd::serialize(QDataStream& ds) const
{
  quint16 typeVal = static_cast<uint16_t>(m_parent.lock()->getType());

  if ((typeVal >> 6) == 0) {
    /* 8 bit header end */
    quint8 typeByte = 1;
    typeByte += (typeVal & 0x3F) << 2;

    ds << typeByte;
  }
  else {
    /* 16 bit header end */
    quint16 typeBytes = 3;
    typeBytes += (typeVal & 0x3FFF) << 2;

    ds << typeBytes;
  }
}

} // namespace packStore
} // namespace libmson
