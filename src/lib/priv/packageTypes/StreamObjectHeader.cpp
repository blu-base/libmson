#include "StreamObjectHeader.h"

#include <QDebug>

#include "StreamObjectHeaderEnd.h"
#include "dataTypes/CompactUInt64.h"


namespace libmson {
namespace fsshttpb {

StreamObjectHeader::StreamObjectHeader()
    : m_type(StreamObjectType::Invalid), m_length()
{
}
StreamObjectHeader::StreamObjectHeader(
    const StreamObjectType& type, const uint64_t& length)
    : m_type(type), m_length(length)
{
}

StreamObjectType StreamObjectHeader::getType() const { return m_type; }

void StreamObjectHeader::setType(const StreamObjectType& type)
{
  m_type = type;
}

uint64_t StreamObjectHeader::getLength() const { return m_length; }

void StreamObjectHeader::setLength(const uint64_t& length)
{
  m_length = length;
}

StreamObjectHeaderEnd StreamObjectHeader::getEnd() const
{
  return StreamObjectHeaderEnd(m_type);
}

quint64 StreamObjectHeader::getSizeInFile() const
{
  return getSizeInFile(m_length,m_type);
}

quint64 StreamObjectHeader::getSizeInFile(
    const quint64& length, const StreamObjectType& type)
{
  uint16_t typeBits = static_cast<uint16_t>(type);
  if (length < 127 && (typeBits >> 6) == 0) {
    return 2;
  }
  else {

    if (length > 0x7FFE) {
      return 4 + CompactUInt64::getSizeInFile(length);
    }
    return 4;
  }
}

void StreamObjectHeader::deserialize(QDataStream& ds)
{


  uint16_t composite;

  ds >> composite;

  /*16 bit header*/
  if ((composite & 0x3) == 0) {
    uint8_t typeVal = (composite >> 3) & 0x3F;

    if (validStreamObjectTypeValues.find(typeVal) !=
        validStreamObjectTypeValues.end()) {
      m_type = static_cast<StreamObjectType>(typeVal);
    }
    else {
      qDebug() << "TypeVal: " << QString::number(typeVal);
      m_type = StreamObjectType::Invalid;
    }
    // test if compound bit is correct
    if (((composite >> 2) & 0x1) != compoundType.at(m_type)) {
      m_type = StreamObjectType::Invalid;
    }

    m_length = (composite >> 9) & 0x7F;
  }
  /* 32 bit header */
  else if ((composite & 0x3) == 2) {

    uint16_t highBytes;
    ds >> highBytes;

    uint16_t typeVal = ((highBytes & 0x1) << 13) + ((composite >> 3) & 0x1FFF);
    if (validStreamObjectTypeValues.find(typeVal) !=
        validStreamObjectTypeValues.end()) {
      m_type = static_cast<StreamObjectType>(typeVal);
    }
    else {
      qDebug() << "TypeVal: " << QString::number(typeVal);
      m_type = StreamObjectType::Invalid;
    }
    // test if compound bit is correct
    if (((composite >> 2) & 0x1) != compoundType.at(m_type)) {
      m_type = StreamObjectType::Invalid;
    }


    uint16_t subtotal = highBytes >> 1;

    if (subtotal == 0x7FFF) {
      /* large length */

      CompactUInt64 total;
      ds >> total;

      m_length = total.getValue();
    }
    else {
      m_length = subtotal;
    }
  }
  else {
    m_type = StreamObjectType::Invalid;
  }
}

void StreamObjectHeader::serialize(QDataStream& ds) const
{

  uint16_t typeBits = static_cast<uint16_t>(m_type);
  if (m_length < 127 && (typeBits >> 6) == 0) {
    /*16 bit header*/
    typeBits <<= 3;

    typeBits += compoundType.at(m_type) << 2;

    typeBits += m_length << 9;

    ds << typeBits;
  }
  else {
    /* 32 bit header */
    uint32_t composite = 2;

    composite += compoundType.at(m_type) << 2;

    composite += typeBits << 3;
    if (m_length < 0x7FFF) {
      composite += m_length << 17;
      ds << composite;
    }
    else {
      composite += 0x7FFF << 17;
      ds << composite;

      CompactUInt64 large(m_length);
      ds << large;
    }
  }
}

} // namespace fsshttpb
} // namespace libmson
