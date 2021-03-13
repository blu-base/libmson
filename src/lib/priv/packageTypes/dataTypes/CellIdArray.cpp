#include "CellIdArray.h"

#include "CompactUInt64.h"

namespace libmson {
namespace fsshttpb {

CellIdArray::CellIdArray() : m_elements{} {}

CellIdArray::CellIdArray(std::vector<CellId> ids) : m_elements(std::move(ids))
{
}

quint64 CellIdArray::getCount() const { return m_elements.size(); }

std::vector<CellId> CellIdArray::getElements() const { return m_elements; }

void CellIdArray::setElements(const std::vector<CellId>& elements)
{
  m_elements = elements;
}

quint64 CellIdArray::getSizeInFile() const { return getSizeInFile(m_elements); }

quint64 CellIdArray::getSizeInFile(const std::vector<CellId>& ids)
{
  quint64 total = CompactUInt64::getSizeInFile(ids.size());

  total += std::accumulate(
      ids.begin(), ids.end(), 0, [](quint64 sub, const CellId& entry) {
        return sub + entry.getSizeInFile();
      });

  return total;
}


void CellIdArray::deserialize(QDataStream& ds)
{
  CompactUInt64 count;
  ds >> count;

  for (size_t i = 0; i < count.getValue(); i++) {
    CellId id;
    ds >> id;
    m_elements.push_back(id);
  }
}

void CellIdArray::serialize(QDataStream& ds) const
{
  ds << CompactUInt64(m_elements.size());

  for (const auto& entry : m_elements) {
    ds << entry;
  }
}
} // namespace fsshttpb
} // namespace libmson
