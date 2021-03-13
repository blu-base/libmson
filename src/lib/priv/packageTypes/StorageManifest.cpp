#include "StorageManifest.h"

#include <numeric>

namespace libmson {
namespace fsshttpb {

StorageManifest::StorageManifest() : m_schema(), m_rootDeclares{} {}

streamObj::StorageManifestSchema_SPtr_t StorageManifest::getSchema() const
{
  return m_schema;
}

void StorageManifest::setSchema(
    const streamObj::StorageManifestSchema_SPtr_t& schema)
{
  m_schema = schema;
}

std::vector<streamObj::StorageManifestRootDeclare_SPtr_t>
StorageManifest::getRootDeclares() const
{
  return m_rootDeclares;
}

void StorageManifest::setRootDeclares(
    const std::vector<streamObj::StorageManifestRootDeclare_SPtr_t>&
        rootDeclares)
{
  m_rootDeclares = rootDeclares;
}

void StorageManifest::deserialize(QDataStream& ds)
{
  auto schema = std::make_shared<streamObj::StorageManifestSchema>();
  ds >> *schema;
  m_schema = std::move(schema);

  char buff[1];
  qint64 peeking = ds.device()->peek(buff, 1);
  if (peeking < 1) {
    qFatal("Error reading bytes during deserialize StorageIndex");
  }


  while (((static_cast<uint8_t>(buff[0]) & 0x3) == 0)) {
    auto rootDecl = std::make_shared<streamObj::StorageManifestRootDeclare>();
    ds >> *rootDecl;

    m_rootDeclares.push_back(rootDecl);

    ds.device()->peek(buff, 1);
  }
}

void StorageManifest::serialize(QDataStream& ds) const
{
  ds << *m_schema;
  for (const auto& entry : m_rootDeclares) {
    ds << *entry;
  }
}

quint64 StorageManifest::cb() const
{
  return std::accumulate(
      m_rootDeclares.begin(), m_rootDeclares.end(), m_schema->getSizeInFile(),
      [](quint64 sub,
         const streamObj::StorageManifestRootDeclare_SPtr_t& entry) {
        return sub + entry->getSizeInFile();
      });
}

DataElementType StorageManifest::getType() const
{
  return DataElementType::StorageManifest;
}


} // namespace packStore
} // namespace libmson
