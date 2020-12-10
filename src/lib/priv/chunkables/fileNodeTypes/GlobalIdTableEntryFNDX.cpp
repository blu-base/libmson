#include "GlobalIdTableEntryFNDX.h"

namespace libmson {
namespace priv {
GlobalIdTableEntryFNDX::GlobalIdTableEntryFNDX(FileNode_SPtr_t parentFileNode)
    : IFileNodeType(std::move(parentFileNode)), m_index{0}
{
}

QUuid GlobalIdTableEntryFNDX::getGuid() const { return m_guid; }

void GlobalIdTableEntryFNDX::setGuid(const QUuid& value) { m_guid = value; }

quint32 GlobalIdTableEntryFNDX::getIndex() const { return m_index; }

void GlobalIdTableEntryFNDX::setIndex(const quint32& value) { m_index = value; }

void GlobalIdTableEntryFNDX::deserialize(QDataStream& ds)
{
  ds >> m_index;
  ds >> m_guid;
}

void GlobalIdTableEntryFNDX::serialize(QDataStream& ds) const
{
  ds << m_index;
  ds << m_guid;
}

quint64 GlobalIdTableEntryFNDX::getSizeInFile() const { return sizeInFile; }


} // namespace priv
} // namespace libmson
