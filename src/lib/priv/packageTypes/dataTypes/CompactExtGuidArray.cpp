#include "CompactExtGuidArray.h"

#include "CompactExtGuid.h"
#include "CompactUInt64.h"

namespace libmson {
namespace fsshttpb {

CompactExtGuidArray::CompactExtGuidArray() : m_elements{} {}

CompactExtGuidArray::CompactExtGuidArray(std::vector<priv::ExtendedGUID> guids)
    : m_elements(std::move(guids))
{
}

quint64 CompactExtGuidArray::getCount() const { return m_elements.size(); }

std::vector<priv::ExtendedGUID> CompactExtGuidArray::getElements() const
{
  return m_elements;
}

void CompactExtGuidArray::setElements(
    const std::vector<priv::ExtendedGUID>& elements)
{
  m_elements = elements;
}

quint64 CompactExtGuidArray::getSizeInFile() const
{
  return getSizeInFile(m_elements);
}

quint64
CompactExtGuidArray::getSizeInFile(const std::vector<priv::ExtendedGUID>& guids)
{
  quint64 total = CompactUInt64::getSizeInFile(guids.size());

  total += std::accumulate(
      guids.cbegin(), guids.cend(), 0,
      [](quint64 sub, const priv::ExtendedGUID& entry) {
        return sub + CompactExtGuid(entry).getSizeInFile();
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
    m_elements.push_back(eguid.getExtendedGUID());
  }
}

void CompactExtGuidArray::serialize(QDataStream& ds) const
{
  ds << CompactUInt64(m_elements.size());

  for (const auto& entry : m_elements) {
    ds << CompactExtGuid(entry);
  }
}


} // namespace fsshttpb
} // namespace libmson
