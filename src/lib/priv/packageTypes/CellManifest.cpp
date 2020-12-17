#include "CellManifest.h"


namespace libmson {
namespace packStore {
CellManifest::CellManifest() {}

streamObj::CellManifestCurrentRevision_SPtr_t
CellManifest::getCurrentRevision() const
{
  return m_currentRevision;
}

void CellManifest::setCurrentRevision(
    const streamObj::CellManifestCurrentRevision_SPtr_t& currentRevision)
{
  m_currentRevision = currentRevision;
}


void CellManifest::deserialize(QDataStream& ds)
{

  auto currentRevision =
      std::make_shared<streamObj::CellManifestCurrentRevision>();
  ds >> *currentRevision;
  m_currentRevision = std::move(currentRevision);
}

void CellManifest::serialize(QDataStream& ds) const
{
  ds << *m_currentRevision;
}

quint64 CellManifest::cb() const { return m_currentRevision->getSizeInFile(); }

DataElementType CellManifest::getType() const
{
  return DataElementType::CellManifest;
}

} // namespace packStore
} // namespace libmson
