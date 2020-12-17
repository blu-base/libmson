#include "StorageIndex.h"

#include "DataElement.h"

#include "StreamObjectHeaderEnd.h"

namespace libmson {
namespace packStore {
StorageIndex::StorageIndex()
    : m_manifestMapping(), m_cellMappings{}, m_revisionMappings{}
{
}

DataElementType StorageIndex::getType() const
{
  return DataElementType::StorageIndex;
}

streamObj::StorageIndexManifestMapping_SPtr_t
StorageIndex::getManifestMapping() const
{
  return m_manifestMapping;
}

void StorageIndex::setManifestMapping(
    const streamObj::StorageIndexManifestMapping_SPtr_t& manifestMapping)
{
  m_manifestMapping = manifestMapping;
}

std::vector<streamObj::StorageIndexCellMapping_SPtr_t>
StorageIndex::getCellMappings() const
{
  return m_cellMappings;
}

void StorageIndex::setCellMappings(
    const std::vector<streamObj::StorageIndexCellMapping_SPtr_t>& cellMappings)
{
  m_cellMappings = cellMappings;
}

std::vector<streamObj::StorageIndexRevisionMapping_SPtr_t>
StorageIndex::getRevisionMappings() const
{
  return m_revisionMappings;
}

void StorageIndex::setRevisionMappings(
    const std::vector<streamObj::StorageIndexRevisionMapping_SPtr_t>&
        revisionMappings)
{
  m_revisionMappings = revisionMappings;
}


void StorageIndex::deserialize(QDataStream& ds)
{

  char peek[1];

  qint64 peeking = ds.device()->peek(peek, 1);
  if (peeking < 1) {
    qFatal("Error reading bytes during deserialize StorageIndex");
  }


  while (((static_cast<uint8_t>(peek[0]) & 0x3) == 0)) {
    ds.startTransaction();

    auto mapping = std::make_shared<StreamObjectHeader>();
    ds >> *mapping;

    ds.rollbackTransaction();


    if (mapping->getType() == StreamObjectType::StorageIndexManifestMapping) {
      auto manifestMapping =
          std::make_shared<streamObj::StorageIndexManifestMapping>();
      ds >> *manifestMapping;

      m_manifestMapping = manifestMapping;
    }
    else if (mapping->getType() == StreamObjectType::StorageIndexCellMapping) {
      auto cellMapping = std::make_shared<streamObj::StorageIndexCellMapping>();

      ds >> *cellMapping;

      m_cellMappings.push_back(cellMapping);
    }
    else if (
        mapping->getType() == StreamObjectType::StorageIndexRevisionMapping) {
      auto revisionMapping =
          std::make_shared<streamObj::StorageIndexRevisionMapping>();

      ds >> *revisionMapping;

      m_revisionMappings.push_back(revisionMapping);
    }

    ds.device()->peek(peek, 1);
  }
}

void StorageIndex::serialize(QDataStream& ds) const
{

  if (m_manifestMapping != nullptr) {
    ds << *m_manifestMapping;
  }

  for (const auto& entry : m_cellMappings) {
    ds << *entry;
  }

  for (const auto& entry : m_revisionMappings) {
    ds << *entry;
  }
}

quint64 StorageIndex::cb() const
{
  quint64 total{};
  total += m_manifestMapping->getSizeInFile();
  total += std::accumulate(
      m_cellMappings.begin(), m_cellMappings.end(), 0,
      [](quint64 subtotal,
         const streamObj::StorageIndexCellMapping_SPtr_t& entry) {
        return subtotal + entry->getSizeInFile();
      });
  total += std::accumulate(
      m_revisionMappings.begin(), m_revisionMappings.end(), 0,
      [](quint64 subtotal,
         const streamObj::StorageIndexRevisionMapping_SPtr_t& entry) {
        return subtotal + entry->getSizeInFile();
      });

  return total;
}

} // namespace packStore
} // namespace libmson
