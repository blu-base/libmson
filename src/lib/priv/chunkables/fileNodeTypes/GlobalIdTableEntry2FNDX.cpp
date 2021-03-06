#include "GlobalIdTableEntry2FNDX.h"

namespace libmson {
namespace priv {
GlobalIdTableEntry2FNDX::GlobalIdTableEntry2FNDX(FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_iIndexMapFrom{0},
      m_iIndexMapTo{0}
{
}

quint32 GlobalIdTableEntry2FNDX::getIIndexMapFrom() const
{
  return m_iIndexMapFrom;
}

void GlobalIdTableEntry2FNDX::setIIndexMapFrom(const quint32& value)
{
  m_iIndexMapFrom = value;
}

quint32 GlobalIdTableEntry2FNDX::getIIndexMapTo() const
{
  return m_iIndexMapTo;
}

void GlobalIdTableEntry2FNDX::setIIndexMapTo(const quint32& value)
{
  m_iIndexMapTo = value;
}

void GlobalIdTableEntry2FNDX::deserialize(QDataStream& ds)
{
  ds >> m_iIndexMapFrom;
  ds >> m_iIndexMapTo;
}

void GlobalIdTableEntry2FNDX::serialize(QDataStream& ds) const
{
  ds << m_iIndexMapFrom;
  ds << m_iIndexMapTo;
}

quint64 GlobalIdTableEntry2FNDX::getSizeInFile() const { return sizeInFile; }

} // namespace priv
} // namespace libmson
