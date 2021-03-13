#include "StorageIndexDataElement.h"
#include "StorageIndexCellMapping.h"
#include "StorageIndexManifestMapping.h"
#include "StorageIndexRevisionMapping.h"
#include <vector>

namespace libmson {
namespace fsshttpb {

StorageIndexManifestMapping_WPtr_t StorageIndex::getManifestMapping() const
{
  auto rawVec = getObjects(StreamObjectType::StorageIndexCellMapping);

  if (rawVec.empty()) {
    return StorageIndexManifestMapping_WPtr_t();
  }

  return std::static_pointer_cast<StorageIndexManifestMapping>(
      rawVec.at(0).lock());
}

void StorageIndex::setManifestMapping(
    const StorageIndexManifestMapping_SPtr_t& manifestMapping)
{
  removeObjects(StreamObjectType::StorageIndexCellMapping);
  /// \todo figure out whether the m_children can be unsorted
  m_children.insert(m_children.begin(), manifestMapping);
}

std::vector<StorageIndexCellMapping_WPtr_t>
StorageIndex::getCellMappings() const
{
  auto rawVec = getObjects(StreamObjectType::StorageIndexCellMapping);

  std::vector<StorageIndexCellMapping_WPtr_t> vec{};

  vec.reserve(m_children.size());
  std::transform(
      rawVec.cbegin(), rawVec.cend(), std::back_inserter(vec), [](auto& ptr) {
        return std::static_pointer_cast<StorageIndexCellMapping>(ptr.lock());
      });

  return vec;
}

void StorageIndex::setCellMappings(
    const std::vector<StorageIndexCellMapping_SPtr_t>& cellMappings)
{
  removeObjects(StreamObjectType::StorageIndexCellMapping);
  m_children.insert(m_children.end(), cellMappings.begin(), cellMappings.end());
}

std::vector<StorageIndexRevisionMapping_WPtr_t>
StorageIndex::getRevisionMappings() const
{
  auto rawVec = getObjects(StreamObjectType::StorageIndexRevisionMapping);

  std::vector<StorageIndexRevisionMapping_WPtr_t> vec{};

  vec.reserve(m_children.size());
  std::transform(
      rawVec.cbegin(), rawVec.cend(), std::back_inserter(vec), [](auto& ptr) {
        return std::static_pointer_cast<StorageIndexRevisionMapping>(
            ptr.lock());
      });

  return vec;
}

void StorageIndex::setRevisionMappings(
    const std::vector<StorageIndexRevisionMapping_SPtr_t>& revisionMappings)
{
  removeObjects(StreamObjectType::StorageIndexRevisionMapping);
  m_children.insert(m_children.end(), revisionMappings.begin(), revisionMappings.end());
}


} // namespace fsshttpb
} // namespace libmson
