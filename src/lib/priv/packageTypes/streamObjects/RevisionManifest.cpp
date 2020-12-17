#include "RevisionManifest.h"

namespace libmson {
namespace packStore {
namespace streamObj {

RevisionManifest::RevisionManifest() {}

CompactExtGuid RevisionManifest::getRevisionId() const { return m_revisionId; }

void RevisionManifest::setRevisionId(const CompactExtGuid& revisionId)
{
  m_revisionId = revisionId;
}

CompactExtGuid RevisionManifest::getBaseRevisionId() const
{
  return m_baseRevisionId;
}

void RevisionManifest::setBaseRevisionId(const CompactExtGuid& baseRevisionId)
{
  m_baseRevisionId = baseRevisionId;
}


void RevisionManifest::deserialize(QDataStream& ds)
{
  StreamObjectHeader header;
  ds >> header;

  if (header.getType() != getType()) {
    qFatal("Trying to deserialze StreamObject of incorrect header type "
           "(RevisionManifest)");
  }

  qint64 origPos = ds.device()->pos();
  ds >> m_revisionId;
  ds >> m_baseRevisionId;

  if ((origPos + header.getLength()) != (quint64)ds.device()->pos()) {
    qFatal("Something went wrong parsing RevisionManifest");
  }
}

void RevisionManifest::serialize(QDataStream& ds) const
{
  StreamObjectHeader header(getType(), body_cb());

  ds << header;

  ds << m_revisionId;
  ds << m_baseRevisionId;
}

quint64 RevisionManifest::body_cb() const
{
  return m_revisionId.getSizeInFile() + m_baseRevisionId.getSizeInFile();
}

StreamObjectType RevisionManifest::getType() const
{

  return StreamObjectType::RevisionManifest;
}

} // namespace streamObj
} // namespace packStore
} // namespace libmson
