#include "StorageIndexManifestMapping.h"

#include "../StreamObjectHeader.h"

namespace libmson {
namespace packStore {
namespace streamObj {

CompactExtGuid StorageIndexManifestMapping::getExtendedGuid() const
{
  return m_extendedGuid;
}

void StorageIndexManifestMapping::setExtendedGuid(
    const CompactExtGuid& extendedGuid)
{
  m_extendedGuid = extendedGuid;
}

StorageIndexManifestMapping::StorageIndexManifestMapping() {}

StreamObjectType StorageIndexManifestMapping::getType() const
{
  return StreamObjectType::StorageIndexManifestMapping;
}

quint64 StorageIndexManifestMapping::body_cb() const
{

  quint64 subtotal = m_extendedGuid.getSizeInFile();
  subtotal += m_serialNumber.getSizeInFile();

  return subtotal;
}


void StorageIndexManifestMapping::deserialize(QDataStream& ds)
{

  StreamObjectHeader header;
  ds >> header;

  if (header.getType() != getType()) {
    qFatal("Trying to deserialze StreamObject of incorrect header type "
           "(StorageIndexManifestMapping)");
  }

  qint64 origPos = ds.device()->pos();
  ds >> m_extendedGuid;
  ds >> m_serialNumber;

  if ((origPos + header.getLength()) != (quint64)ds.device()->pos()) {
    qFatal("Something went wrong parsing StorageIndexManifestMapping");
  }
}

void StorageIndexManifestMapping::serialize(QDataStream& ds) const
{

  StreamObjectHeader header(getType(), body_cb());

  ds << header;
  ds << m_extendedGuid;
  ds << m_serialNumber;
}

} // namespace streamObj
} // namespace packStore
} // namespace libmson
