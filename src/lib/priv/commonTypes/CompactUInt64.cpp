#include "CompactUInt64.h"
namespace libmson {
namespace packStore {
CompactUInt64::CompactUInt64() : m_value() {}

CompactUInt64::CompactUInt64(const quint64& value) : m_value(value) {}


quint64 CompactUInt64::getValue() const { return m_value; }

void CompactUInt64::setValue(const quint64& value) { m_value = value; }

quint64 CompactUInt64::getSizeInFile() const
{
  if (m_value < limit14bit) {
    return 1;
  }
  else if (m_value < limit21bit) {
    return 2;
  }
  else if (m_value < limit28bit) {
    return 3;
  }
  else if (m_value < limit35bit) {
    return 4;
  }
  else if (m_value < limit42bit) {
    return 5;
  }
  else if (m_value < limit49bit) {
    return 6;
  }
  else if (m_value < limit64bit) {
    return 7;
  }
  else {
    return 9;
  }
}


void CompactUInt64::deserialize(QDataStream& ds)
{
  uint8_t typeByte;
  ds >> typeByte;

  if (typeByte == 0) {
    m_value = 0;
  }
  /* 7bit width */
  else if ((typeByte & 0x1) == 1) {
    m_value = typeByte >> 1;
  }
  /* 14bit width */
  else if ((typeByte & 0x3) == 2) {
    uint8_t highByte;
    ds >> highByte;

    m_value = (((uint16_t)highByte) << 6) + (typeByte >> 2);
  } /* 21bit width */
  else if ((typeByte & 0x7) == 4) {
    std::array<char, 2> buff;
    ds.device()->read(buff.data(), 2);

    m_value += static_cast<uint8_t>(buff.at(1));
    m_value <<= 8u;
    m_value += static_cast<uint8_t>(buff.at(0));
    m_value <<= 5u;
    m_value += (typeByte >> 3u);


  } /* 28bit width */
  else if ((typeByte & 0xF) == 8) {
    std::array<char, 3> buff;
    ds.device()->read(buff.data(), 3);


    m_value += static_cast<uint8_t>(buff.at(2));
    m_value <<= 8u;
    m_value += static_cast<uint8_t>(buff.at(1));
    m_value <<= 8u;
    m_value += static_cast<uint8_t>(buff.at(0));
    m_value <<= 4u;
    m_value += (typeByte >> 4u);

  } /* 35bit width */
  else if ((typeByte & 0x1F) == 16) {
    std::array<char, 4> buff;
    ds.device()->read(buff.data(), 4);

    m_value += static_cast<uint8_t>(buff.at(3));
    m_value <<= 8u;
    m_value += static_cast<uint8_t>(buff.at(2));
    m_value <<= 8u;
    m_value += static_cast<uint8_t>(buff.at(1));
    m_value <<= 8u;
    m_value += static_cast<uint8_t>(buff.at(0));
    m_value <<= 3u;
    m_value += (typeByte >> 5u);

  } /* 42bit width */
  else if ((typeByte & 0x3F) == 32) {
    std::array<char, 5> buff;
    ds.device()->read(buff.data(), 5);

    m_value += static_cast<uint8_t>(buff.at(4));
    m_value <<= 8u;
    m_value += static_cast<uint8_t>(buff.at(3));
    m_value <<= 8u;
    m_value += static_cast<uint8_t>(buff.at(2));
    m_value <<= 8u;
    m_value += static_cast<uint8_t>(buff.at(1));
    m_value <<= 8u;
    m_value += static_cast<uint8_t>(buff.at(0));
    m_value <<= 2u;
    m_value += (typeByte >> 6u);

  } /* 49bit width */
  else if ((typeByte & 0x7F) == 64) {
    std::array<char, 6> buff;
    ds.device()->read(buff.data(), 6);

    m_value += static_cast<uint8_t>(buff.at(5));
    m_value <<= 8u;
    m_value += static_cast<uint8_t>(buff.at(4));
    m_value <<= 8u;
    m_value += static_cast<uint8_t>(buff.at(3));
    m_value <<= 8u;
    m_value += static_cast<uint8_t>(buff.at(2));
    m_value <<= 8u;
    m_value += static_cast<uint8_t>(buff.at(1));
    m_value <<= 8u;
    m_value += static_cast<uint8_t>(buff.at(0));
    m_value <<= 1u;
    m_value += (typeByte >> 7u);
  } /* 64bit width */
  else if ((typeByte & 0x2) == 2) {
    ds >> m_value;
  }
}

void CompactUInt64::serialize(QDataStream& ds) const
{
  uint8_t typeByte;

  if (m_value == 0) {
    const uint8_t zero = 0;
    ds << zero;
  }
  /* 7 bit width */
  else if (m_value < limit14bit) {
    typeByte = 1 + ((m_value & 0x7F) << 1);
    ds << typeByte;
  }
  /* 14 bit width */
  else if (m_value < limit21bit) {
    typeByte = 2 + ((m_value & 0x3F) << 2);
    ds << typeByte;

    uint8_t highByte = m_value >> 6;
    ds << highByte;
  }
  /* 21 bit width */
  else if (m_value < limit28bit) {
    typeByte = 4 + ((m_value & 0x1F) << 3);
    ds << typeByte;

    uint64_t temp = m_value >> 5;
    for (uint8_t i = 0; i < 2; i++) {
      uint8_t byte = (temp & 0xFF);
      ds << byte;

      temp >>= 8;
    }
  }
  /* 28 bit width */
  else if (m_value < limit35bit) {
    typeByte = 8 + ((m_value & 0xF) << 4);
    ds << typeByte;

    uint64_t temp = m_value >> 4;
    for (uint8_t i = 0; i < 3; i++) {
      uint8_t byte = (temp & 0xFF);
      ds << byte;

      temp >>= 8;
    }
  }
  /* 35 bit width */
  else if (m_value < limit42bit) {
    typeByte = 16 + ((m_value & 0x7) << 5);
    ds << typeByte;

    uint64_t temp = m_value >> 3;
    for (uint8_t i = 0; i < 4; i++) {
      uint8_t byte = (temp & 0xFF);
      ds << byte;

      temp >>= 8;
    }
  }
  /* 42 bit width */
  else if (m_value < limit49bit) {
    typeByte = 32 + ((m_value & 0x3) << 6);
    ds << typeByte;

    uint64_t temp = m_value >> 2;
    for (uint8_t i = 0; i < 5; i++) {
      uint8_t byte = (temp & 0xFF);
      ds << byte;

      temp >>= 8;
    }
  }
  /* 49 bit width */
  else if (m_value < limit64bit) {
    typeByte = 64 + ((m_value & 0x1) << 7);
    ds << typeByte;

    uint64_t temp = m_value >> 1;
    for (uint8_t i = 0; i < 6; i++) {
      uint8_t byte = (temp & 0xFF);
      ds << byte;

      temp >>= 8;
    }
  }
  /* 64 bit width */
  else {
    typeByte = 128;
    ds << typeByte;
    ds << m_value;
  }
}
} // namespace packStore
} // namespace libmson
