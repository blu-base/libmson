#include "RevisionManifestObjectGroupReference.h"
namespace libmson {
namespace packStore {
namespace streamObj {
RevisionManifestObjectGroupReference::RevisionManifestObjectGroupReference() {}

CompactExtGuid RevisionManifestObjectGroupReference::getObjectGroup() const
{
  return m_objectGroup;
}

void RevisionManifestObjectGroupReference::setObjectGroup(
    const CompactExtGuid& objectGroup)
{
  m_objectGroup = objectGroup;
}

void RevisionManifestObjectGroupReference::deserialize(QDataStream& ds)
{
  StreamObjectHeader header;
  ds >> header;

  if (header.getType() != getType()) {
    qFatal("Trying to deserialze StreamObject of incorrect header type "
           "(RevisionManifestObjectGroupReference)");
  }

  qint64 origPos = ds.device()->pos();

  ds >> m_objectGroup;

  if ((origPos + header.getLength()) != (quint64)ds.device()->pos()) {
    qFatal("Something went wrong parsing RevisionManifestObjectGroupReference");
  }
}

void RevisionManifestObjectGroupReference::serialize(QDataStream& ds) const
{
  StreamObjectHeader header(getType(), body_cb());

  ds << header;
  ds << m_objectGroup;
}

quint64 RevisionManifestObjectGroupReference::body_cb() const
{
  return m_objectGroup.getSizeInFile();
}

StreamObjectType RevisionManifestObjectGroupReference::getType() const
{
  return StreamObjectType::RevisionManifestObjectGroupReference;
  ;
}

} // namespace streamObj
} // namespace packStore
} // namespace libmson
