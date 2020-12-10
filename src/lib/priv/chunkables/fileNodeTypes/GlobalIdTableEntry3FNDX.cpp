#include "GlobalIdTableEntry3FNDX.h"

namespace libmson {
namespace priv {
GlobalIdTableEntry3FNDX::GlobalIdTableEntry3FNDX(FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_iIndexCopyFromStart{0},
      m_cEntriesToCopy{0}, m_iIndexCopyToStart{0}
{
}

quint32 GlobalIdTableEntry3FNDX::getIIndexCopyFromStart() const
{
  return m_iIndexCopyFromStart;
}

void GlobalIdTableEntry3FNDX::setIIndexCopyFromStart(const quint32& value)
{
  m_iIndexCopyFromStart = value;
}

quint32 GlobalIdTableEntry3FNDX::getCEntriesToCopy() const
{
  return m_cEntriesToCopy;
}

void GlobalIdTableEntry3FNDX::setCEntriesToCopy(const quint32& value)
{
  m_cEntriesToCopy = value;
}

quint32 GlobalIdTableEntry3FNDX::getIIndexCopyToStart() const
{
  return m_iIndexCopyToStart;
}

void GlobalIdTableEntry3FNDX::setIIndexCopyToStart(const quint32& value)
{
  m_iIndexCopyToStart = value;
}

void GlobalIdTableEntry3FNDX::deserialize(QDataStream& ds)
{

  ds >> m_iIndexCopyFromStart;
  ds >> m_cEntriesToCopy;
  ds >> m_iIndexCopyToStart;
}

void GlobalIdTableEntry3FNDX::serialize(QDataStream& ds) const
{
  ds << m_iIndexCopyFromStart;
  ds << m_cEntriesToCopy;
  ds << m_iIndexCopyToStart;
}

quint64 GlobalIdTableEntry3FNDX::getSizeInFile() const { return sizeInFile; }


} // namespace priv
} // namespace libmson
