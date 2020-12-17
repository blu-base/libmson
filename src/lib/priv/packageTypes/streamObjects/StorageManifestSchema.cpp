#include "StorageManifestSchema.h"
namespace libmson {
namespace packStore {
namespace streamObj {

QUuid StorageManifestSchema::getGuid() const { return m_guid; }

void StorageManifestSchema::setGuid(const QUuid& guid) { m_guid = guid; }

StorageManifestSchema::StorageManifestSchema() {}

void StorageManifestSchema::deserialize(QDataStream& ds)
{
  StreamObjectHeader header;
  ds >> header;

  if (header.getType() != getType()) {
    qFatal("Trying to deserialze StreamObject of incorrect header type "
           "(StorageManifestSchema)");
  }

  qint64 origPos = ds.device()->pos();
  ds >> m_guid;

  if ((origPos + header.getLength()) != (quint64)ds.device()->pos()) {
    qFatal("Something went wrong parsing StorageManifestSchema");
  }
}

void StorageManifestSchema::serialize(QDataStream& ds) const
{
  StreamObjectHeader header(getType(), body_cb());
  ds << header;

  ds << m_guid;
}

quint64 StorageManifestSchema::body_cb() const { return 16; }

StreamObjectType StorageManifestSchema::getType() const
{
  return StreamObjectType::StorageManifestSchemaGUID;
}
} // namespace streamObj
} // namespace packStore
} // namespace libmson
