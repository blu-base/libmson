#include "StorageIndexRevisionMapping.h"
namespace libmson {
namespace packStore {
namespace streamObj {


StorageIndexRevisionMapping::StorageIndexRevisionMapping() {}

CompactExtGuid StorageIndexRevisionMapping::getRevision() const
{
  return m_revision;
}

void StorageIndexRevisionMapping::setRevision(const CompactExtGuid& revision)
{
  m_revision = revision;
}

CompactExtGuid StorageIndexRevisionMapping::getExtendedGuid() const
{
  return m_extendedGuid;
}

void StorageIndexRevisionMapping::setExtendedGuid(const CompactExtGuid& extendedGuid)
{
  m_extendedGuid = extendedGuid;
}


void StorageIndexRevisionMapping::deserialize(QDataStream& ds)
{
  StreamObjectHeader header;
  ds >> header;

  if (header.getType() != getType()) {
    qFatal("Trying to deserialze StreamObject of incorrect header type "
           "(StorageIndexRevisionMapping)");
  }

  qint64 origPos = ds.device()->pos();
  ds >> m_revision;
  ds >> m_extendedGuid;
  ds >> m_serialNumber;

  if ((origPos + header.getLength()) != (quint64)ds.device()->pos()) {
    qFatal("Something went wrong parsing StorageIndexRevisionMapping");
  }
}

void StorageIndexRevisionMapping::serialize(QDataStream& ds) const
{
  StreamObjectHeader header(getType(), body_cb());

  ds << header;
  ds << m_revision;
  ds << m_extendedGuid;
  ds << m_serialNumber;

}

quint64 StorageIndexRevisionMapping::body_cb() const
{
  quint64 subtotal;
  subtotal += m_revision.getSizeInFile();
  subtotal += m_extendedGuid.getSizeInFile();
  subtotal += m_serialNumber.getSizeInFile();

  return subtotal;
}

StreamObjectType StorageIndexRevisionMapping::getType() const
{
    return StreamObjectType::StorageIndexRevisionMapping;
}


} // namespace streamObj
} // namespace packStore
} // namespace libmson
