#include "CompactExtGuidArray.h"

#include "CompactUInt64.h"

namespace libmson {
namespace packStore {
CompactExtGuidArray::CompactExtGuidArray() {}

quint64 CompactExtGuidArray::getCount() const { return m_elements.size(); }

std::vector<CompactExtGuid> CompactExtGuidArray::getElements() const
{
  return m_elements;
}

void CompactExtGuidArray::setElements(
    const std::vector<CompactExtGuid>& elements)
{
  m_elements = elements;
}

quint64 CompactExtGuidArray::getSizeInFile() const
{
  quint64 total = CompactUInt64::getSizeInFile(m_elements.size());

  total += std::accumulate(
      m_elements.begin(), m_elements.end(), 0,
      [](quint64 sub, const CompactExtGuid& entry) {
        return sub + entry.getSizeInFile();
      });

  return total;
}


void CompactExtGuidArray::deserialize(QDataStream& ds)
{
  CompactUInt64 count;
  ds >> count;

  for (size_t i = 0; i < count.getValue(); i++) {
    CompactExtGuid eguid;
    ds >> eguid;
    m_elements.push_back(eguid);
  }
}

void CompactExtGuidArray::serialize(QDataStream& ds) const
{
  ds << CompactUInt64(m_elements.size());

  for (const auto& entry : m_elements) {
    ds << entry;
  }
}


} // namespace packStore
} // namespace libmson
