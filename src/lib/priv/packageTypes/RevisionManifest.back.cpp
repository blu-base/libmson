#include "RevisionManifest.h"
namespace libmson {
namespace packStore {
streamObj::RevisionManifest_SPtr_t RevisionManifest::getRevisionManifest() const
{
  return m_revisionManifest;
}

void RevisionManifest::setRevisionManifest(
    const streamObj::RevisionManifest_SPtr_t& revisionManifest)
{
  m_revisionManifest = revisionManifest;
}

RevisionManifest::RevisionManifest() {}


std::vector<streamObj::RevisionManifestRootDeclare_SPtr_t>
RevisionManifest::getRootDeclares() const
{
  return m_rootDeclares;
}

void RevisionManifest::setRootDeclares(
    const std::vector<streamObj::RevisionManifestRootDeclare_SPtr_t>&
        rootDeclares)
{
  m_rootDeclares = rootDeclares;
}

std::vector<streamObj::RevisionManifestObjectGroupReference_SPtr_t>
RevisionManifest::getObjectGroups() const
{
  return m_objectGroups;
}

void RevisionManifest::setObjectGroups(
    const std::vector<streamObj::RevisionManifestObjectGroupReference_SPtr_t>&
        objectGroups)
{
  m_objectGroups = objectGroups;
}


void RevisionManifest::deserialize(QDataStream& ds)
{
  auto revManifest = std::make_shared<streamObj::RevisionManifest>();
  ds >> *revManifest;
  m_revisionManifest = std::move(revManifest);

  char peek[1];

  qint64 peeking = ds.device()->peek(peek, 1);
  if (peeking < 1) {
    qFatal("Error reading bytes during deserialize RevisionManifest");
  }


  while (((static_cast<uint8_t>(peek[0]) & 0x3) == 0)) {
    ds.startTransaction();

    auto mapping = std::make_shared<StreamObjectHeader>();
    ds >> *mapping;

    ds.rollbackTransaction();


    if (mapping->getType() == StreamObjectType::RevisionManifestRootDeclare) {
      auto rootDecl =
          std::make_shared<streamObj::RevisionManifestRootDeclare>();
      ds >> *rootDecl;

      m_rootDeclares.push_back(rootDecl);
    }
    else if (
        mapping->getType() ==
        StreamObjectType::RevisionManifestObjectGroupReference) {
      auto objRef =
          std::make_shared<streamObj::RevisionManifestObjectGroupReference>();

      ds >> *objRef;

      m_objectGroups.push_back(objRef);
    }

    ds.device()->peek(peek, 1);
  }
}

void RevisionManifest::serialize(QDataStream& ds) const
{
  ds << *m_revisionManifest;

  for (const auto& entry : m_rootDeclares) {
    ds << *entry;
  }
  for (const auto& entry : m_objectGroups) {
    ds << *entry;
  }
}

quint64 RevisionManifest::cb() const
{
  quint64 total{};
  total += m_revisionManifest->getSizeInFile();

  total += std::accumulate(
      m_rootDeclares.begin(), m_rootDeclares.end(), 0,
      [](quint64 subtotal,
         const streamObj::RevisionManifestRootDeclare_SPtr_t& entry) {
        return subtotal + entry->getSizeInFile();
      });

  total += std::accumulate(
      m_objectGroups.begin(), m_objectGroups.end(), 0,
      [](quint64 subtotal,
         const streamObj::RevisionManifestObjectGroupReference_SPtr_t& entry) {
        return subtotal + entry->getSizeInFile();
      });

  return total;
}

DataElementType RevisionManifest::getType() const
{
  return DataElementType::RevisionManifest;
}
} // namespace packStore
} // namespace libmson
