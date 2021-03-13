#include "CellId.h"

#include "CompactExtGuid.h"

namespace libmson {
namespace fsshttpb {

CellId::CellId() : m_exguid1(), m_exguid2() {}

CellId::CellId(
    const priv::ExtendedGUID& exguid1, const priv::ExtendedGUID& exguid2)
    : m_exguid1(exguid1), m_exguid2(exguid2)
{
}

priv::ExtendedGUID CellId::getExguid1() const { return m_exguid1; }

void CellId::setExguid1(const priv::ExtendedGUID& exguid1)
{
  m_exguid1 = exguid1;
}

priv::ExtendedGUID CellId::getExguid2() const { return m_exguid2; }

void CellId::setExguid2(const priv::ExtendedGUID& exguid2)
{
  m_exguid2 = exguid2;
}

quint64 CellId::getSizeInFile() const
{
  return getSizeInFile(m_exguid1, m_exguid2);
}

quint64 CellId::getSizeInFile(
    const priv::ExtendedGUID& exguid1, const priv::ExtendedGUID& exguid2)
{
  return CompactExtGuid::getSizeInFile(exguid1) +
         CompactExtGuid::getSizeInFile(exguid2);
}


void CellId::deserialize(QDataStream& ds)
{
  CompactExtGuid guid;
  ds >> guid;
  m_exguid1 = guid.getExtendedGUID();

  ds >> guid;
  m_exguid2 = guid.getExtendedGUID();
}

void CellId::serialize(QDataStream& ds) const
{
  ds << CompactExtGuid(m_exguid1);
  ds << CompactExtGuid(m_exguid2);
}

bool operator==(const CellId& lhs, const CellId& rhs) noexcept
{
  return (lhs.getExguid1() == rhs.getExguid1()) &&
         (lhs.getExguid2() == rhs.getExguid2());
}
bool operator!=(const CellId& lhs, const CellId& rhs) noexcept
{
  return !(lhs == rhs);
}

} // namespace fsshttpb
} // namespace libmson
