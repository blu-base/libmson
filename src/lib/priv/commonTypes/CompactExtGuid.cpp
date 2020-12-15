#include "CompactExtGuid.h"

namespace libmson {
namespace packStore {


CompactExtGuid::CompactExtGuid() : m_base(), m_type(CompactExtGuidWidth::Auto)
{
}

CompactExtGuid::CompactExtGuid(
    const QUuid& guid, const quint32& n, const CompactExtGuidWidth& type)
    : m_base(guid, n), m_type(type)
{
  setSuggestedTypeOrMinimalWidthType(type);
}

CompactExtGuid::CompactExtGuid(
    const priv::ExtendedGUID& extGUID, const CompactExtGuidWidth& type)
    : m_base(extGUID), m_type(type)
{
}

QUuid CompactExtGuid::getGuid() const { return m_base.getGuid(); }

void CompactExtGuid::setGuid(const QUuid& guid) { m_base.setGuid(guid); }

quint32 CompactExtGuid::getN() const { return m_base.getN(); }

void CompactExtGuid::setN(const quint32& n)
{
  m_base.setN(n);

  // keep current type if n fits, or use suitable width
  setSuggestedTypeOrMinimalWidthType(m_type);
}

CompactExtGuidWidth CompactExtGuid::getWidthType() const { return m_type; }

void CompactExtGuid::setWidthType(const CompactExtGuidWidth& type)
{
  setSuggestedTypeOrMinimalWidthType(type);
}

QString CompactExtGuid::toString() const { return m_base.toString(); }

priv::ExtendedGUID CompactExtGuid::getExtendedGUID() const { return m_base; }

uint64_t CompactExtGuid::getSizeInFile() const
{
  switch (m_type) {
  case CompactExtGuidWidth::Auto:
  case CompactExtGuidWidth::Uncompressed:
    return 21;
  case CompactExtGuidWidth::CompressedN17Bit:
    return 19;
  case CompactExtGuidWidth::CompressedN10Bit:
    return 18;
  case CompactExtGuidWidth::CompressedN5Bit:
    return 17;
  case CompactExtGuidWidth::CompressedNull:
    return 1;
  }

  return 0;
}

QString CompactExtGuid::typeToString(const CompactExtGuidWidth& type)
{
  switch (type) {
  case CompactExtGuidWidth::Auto:
  case CompactExtGuidWidth::Uncompressed:
    return "Uncompressed";
  case CompactExtGuidWidth::CompressedN17Bit:
    return "CompressedN17Bit";
  case CompactExtGuidWidth::CompressedN10Bit:
    return "CompressedN10Bit";
  case CompactExtGuidWidth::CompressedN5Bit:
    return "CompressedN5Bit";
  case CompactExtGuidWidth::CompressedNull:
    return "CompressedNull";
  }

  return "Unspecified";
}

void CompactExtGuid::deserialize(QDataStream& ds)
{
  priv::ExtendedGUID newBase;

  uint8_t varWidthByte;
  ds >> varWidthByte;

  if (varWidthByte == 0) {
    newBase = priv::ExtendedGUID(QUuid(), 0);
  }
  else if ((varWidthByte & 0x7) == 4u) {
    QUuid guid;
    ds >> guid;

    newBase = priv::ExtendedGUID(guid, varWidthByte >> 3);
  }
  else if ((varWidthByte & 0x3F) == 32u) {
    uint8_t nFragment;
    ds >> nFragment;

    uint16_t n = (((uint16_t)nFragment) << 2) + (varWidthByte >> 6);

    QUuid guid;
    ds >> guid;

    newBase = priv::ExtendedGUID(guid, n);
  }
  else if ((varWidthByte & 0x7F) == 64u) {
    uint16_t nFragment;
    ds >> nFragment;

    uint32_t n = (((uint32_t)nFragment) << 1) + (varWidthByte >> 7);

    QUuid guid;
    ds >> guid;

    newBase = priv::ExtendedGUID(guid, n);
  }
  else if (varWidthByte == 128u) {
    uint32_t n;
    QUuid guid;

    ds >> n;
    ds >> guid;

    newBase = priv::ExtendedGUID(guid, n);
  }

  m_base = newBase;
}

void CompactExtGuid::serialize(QDataStream& ds) const
{
  switch (m_type) {

  case CompactExtGuidWidth::Auto:
  case CompactExtGuidWidth::Uncompressed: {
    uint8_t varByte = 128u;
    ds << varByte;
    ds << m_base.getN();
    ds << m_base.getGuid();
    break;
  }
  case CompactExtGuidWidth::CompressedN17Bit: {
    uint8_t varByte = 64u;
    varByte += (m_base.getN() & 0x1) << 7;
    ds << varByte;

    uint16_t nFragment = m_base.getN() >> 1;
    ds << nFragment;

    ds << m_base.getGuid();
    break;
  }
  case CompactExtGuidWidth::CompressedN10Bit: {
    uint8_t varByte = 32u;
    varByte += (m_base.getN() & 0x3) << 6;
    ds << varByte;

    uint8_t nFragment = m_base.getN() >> 2;
    ds << nFragment;
    ds << m_base.getGuid();
    break;
  }
  case CompactExtGuidWidth::CompressedN5Bit: {
    uint8_t varByte = 4u;
    varByte += (m_base.getN() & 0x1f) << 3;
    ds << varByte;
    ds << m_base.getGuid();
    break;
  }
  case CompactExtGuidWidth::CompressedNull: {
    uint8_t varByte = 0;
    ds << varByte;
    break;
  }
  }
}

void CompactExtGuid::setSuggestedTypeOrMinimalWidthType(
    const CompactExtGuidWidth& requestedType)
{
  auto suggestedType = determineMinimalWidthType();

  if (requestedType == CompactExtGuidWidth::Auto) {
    m_type = suggestedType;
  }
  else {
    if (static_cast<int8_t>(requestedType) <
        static_cast<int8_t>(suggestedType)) {
      m_type = suggestedType;
    }
    else {
      m_type = requestedType;
    }
  }
}

bool operator==(const CompactExtGuid& lhs, const CompactExtGuid& rhs) noexcept
{
  return lhs.m_base == rhs.m_base;
}
bool operator!=(const CompactExtGuid& lhs, const CompactExtGuid& rhs) noexcept
{
  return lhs.m_base != rhs.m_base;
}
bool operator<=(const CompactExtGuid& lhs, const CompactExtGuid& rhs) noexcept
{
  return lhs.m_base <= rhs.m_base;
}
bool operator>=(const CompactExtGuid& lhs, const CompactExtGuid& rhs) noexcept
{
  return lhs.m_base >= rhs.m_base;
}
bool operator<(const CompactExtGuid& lhs, const CompactExtGuid& rhs) noexcept
{
  return lhs.m_base < rhs.m_base;
}
bool operator>(const CompactExtGuid& lhs, const CompactExtGuid& rhs) noexcept
{
  return lhs.m_base > rhs.m_base;
}


CompactExtGuidWidth CompactExtGuid::determineMinimalWidthType()
{
  auto n = m_base.getN();

  if (m_base.isNull() && n == 0) {
    return CompactExtGuidWidth::CompressedNull;
  }
  else if ((n >> 17) > 0) {
    return CompactExtGuidWidth::Uncompressed;
  }
  else if ((n >> 10) > 0) {
    return CompactExtGuidWidth::CompressedN17Bit;
  }
  else if ((n >> 5) > 0) {
    return CompactExtGuidWidth::CompressedN10Bit;
  }
  else {
    return CompactExtGuidWidth::CompressedN5Bit;
  }
}


} // namespace packStore
} // namespace libmson
