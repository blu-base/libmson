#include "CellId.h"

namespace libmson {
namespace packStore {

CellId::CellId() : m_exguid1(), m_exguid2() {}

CellId::CellId(const CompactExtGuid& exguid1, const CompactExtGuid& exguid2)
    : m_exguid1(exguid1), m_exguid2(exguid2)
{
}

CompactExtGuid CellId::getExguid1() const { return m_exguid1; }

void CellId::setExguid1(const CompactExtGuid& exguid1) { m_exguid1 = exguid1; }

CompactExtGuid CellId::getExguid2() const { return m_exguid2; }

void CellId::setExguid2(const CompactExtGuid& exguid2) { m_exguid2 = exguid2; }

quint64 CellId::getSizeInFile() const
{
  return m_exguid1.getSizeInFile() + m_exguid2.getSizeInFile();
}


void CellId::deserialize(QDataStream& ds)
{
  ds >> m_exguid1;
  ds >> m_exguid2;
}

void CellId::serialize(QDataStream& ds) const
{
  ds << m_exguid1;
  ds << m_exguid2;
}

} // namespace packStore
} // namespace libmson
