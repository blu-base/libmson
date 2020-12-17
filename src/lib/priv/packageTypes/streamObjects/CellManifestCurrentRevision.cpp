#include "CellManifestCurrentRevision.h"
namespace libmson {
namespace packStore {
namespace streamObj {

CompactExtGuid CellManifestCurrentRevision::getExtendedGuid() const
{
  return m_extendedGuid;
}

void CellManifestCurrentRevision::setExtendedGuid(
    const CompactExtGuid& extendedGuid)
{
  m_extendedGuid = extendedGuid;
}

CellManifestCurrentRevision::CellManifestCurrentRevision() {}

void CellManifestCurrentRevision::deserialize(QDataStream& ds)
{

  StreamObjectHeader header;
  ds >> header;

  if (header.getType() != getType()) {
    qFatal("Trying to deserialze StreamObject of incorrect header type "
           "(CellManifestCurrentRevision)");
  }

  qint64 origPos = ds.device()->pos();
  ds >> m_extendedGuid;

  if ((origPos + header.getLength()) != (quint64)ds.device()->pos()) {
    qFatal("Something went wrong parsing CellManifestCurrentRevision");
  }
}

void CellManifestCurrentRevision::serialize(QDataStream& ds) const
{
  StreamObjectHeader header(getType(), body_cb());

  ds << header;

  ds << m_extendedGuid;
}

quint64 CellManifestCurrentRevision::body_cb() const
{
  return m_extendedGuid.getSizeInFile();
}

StreamObjectType CellManifestCurrentRevision::getType() const
{
  return StreamObjectType::CellManifestCurrentRevision;
}
} // namespace streamObj
} // namespace packStore
} // namespace libmson
