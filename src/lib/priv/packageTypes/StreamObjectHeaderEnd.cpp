#include "StreamObjectHeaderEnd.h"

#include <QDebug>

#include "StreamObjectHeader.h"

namespace libmson {
namespace fsshttpb {
StreamObjectHeaderEnd::StreamObjectHeaderEnd()
    : m_type(StreamObjectType::Invalid)
{
}

StreamObjectHeaderEnd::StreamObjectHeaderEnd(StreamObjectType type)
    : m_type(type)
{
}

StreamObjectType StreamObjectHeaderEnd::getType() const { return m_type; }

quint64 StreamObjectHeaderEnd::getSizeInFile() const
{
  return StreamObjectHeaderEnd::getSizeInFile(m_type);
}

quint64 StreamObjectHeaderEnd::getSizeInFile(StreamObjectType type)
{
  quint16 typeVal = static_cast<uint16_t>(type);

  if (compoundType.at(type)) {
    if (typeVal < 0x40) {
      return 1;
    }
    return 2;
  }

  return 0;
}

void StreamObjectHeaderEnd::deserialize(QDataStream& ds)
{
  uint8_t typeByte = 0;
  ds >> typeByte;

  uint16_t typeVal = 0;

  quint8 flag = typeByte & 0x3;


  if (flag == 0x1) {
    /* 8 bit header end */
    typeVal = typeByte >> 2;
  }
  else if (flag == 0x3) {
    /* 16 bit header end */
    uint8_t highByte = 0;
    ds >> highByte;

    typeVal = (highByte << 6) + (typeByte >> 2);
  }
  else {
    m_type = StreamObjectType::Invalid;
    return;
  }

  if (validStreamObjectTypeValues.find(typeVal) ==
      validStreamObjectTypeValues.end()) {
    m_type = StreamObjectType::Invalid;
    return;
  }

  m_type = static_cast<StreamObjectType>(typeVal);

  if (!compoundType.at(m_type)) {
    qCritical() << "StreamObjectHeaderEnd's StreamObjectType is not a compound "
                   "StreamObject";
  }
}

void StreamObjectHeaderEnd::serialize(QDataStream& ds) const
{
  if (!compoundType.at(m_type)) {
    return;
  }

  quint16 typeVal = static_cast<uint16_t>(m_type);

  if (typeVal < 0x40) {
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

} // namespace fsshttpb
} // namespace libmson
