#include "StorageManifestSchemaGUID.h"

namespace libmson {
namespace fsshttpb {

QUuid StorageManifestSchemaGUID::getGuid() const { return m_guid; }

void StorageManifestSchemaGUID::setGuid(QUuid guid) { m_guid = guid; }


quint64 StorageManifestSchemaGUID::strObjBody_cb() const
{
  // sizeof(QUuid)
  return 16;
}

quint64 StorageManifestSchemaGUID::cbNextHeader() const
{
  return strObjBody_cb();
}

StreamObjectType StorageManifestSchemaGUID::getType() const
{
  return StreamObjectType::StorageManifestSchemaGUID;
}

void StorageManifestSchemaGUID::push_back(IStreamObject_SPtr_t& obj) {
      Q_UNUSED(obj);
}

IStreamObj_It_t StorageManifestSchemaGUID::insert(
    IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(pos);
  Q_UNUSED(obj);
  m_children.clear();
  return m_children.end();
}

void StorageManifestSchemaGUID::deserializeStrObj(QDataStream& ds)
{
  ds >> m_guid;
}

void StorageManifestSchemaGUID::serializeStrObj(QDataStream& ds) const
{
  ds << m_guid;
}

} // namespace fsshttpb
} // namespace libmson


