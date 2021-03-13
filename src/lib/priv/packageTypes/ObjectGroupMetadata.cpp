#include "ObjectGroupMetadata.h"

#include "dataTypes/CompactUInt64.h"

namespace libmson {
namespace fsshttpb {

ObjectGroupMetadata::ObjectGroupMetadata() {}

quint64 ObjectGroupMetadata::getObjectChangeFrequency() const
{
  return m_objectChangeFrequency;
}

void ObjectGroupMetadata::setObjectChangeFrequency(
    const quint64& objectChangeFrequency)
{
  m_objectChangeFrequency = objectChangeFrequency;
}

quint64 ObjectGroupMetadata::strObjBody_cb() const
{
  return CompactUInt64::getSizeInFile(m_objectChangeFrequency);
}

quint64 ObjectGroupMetadata::cbNextHeader() const
{
  return strObjBody_cb();
}

StreamObjectType ObjectGroupMetadata::getType() const
{
  return StreamObjectType::ObjectGroupMetadata;
}

void ObjectGroupMetadata::push_back(IStreamObject_SPtr_t& obj)
{
      Q_UNUSED(obj);
}

IStreamObj_It_t ObjectGroupMetadata::insert(IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  Q_UNUSED(pos);
  Q_UNUSED(obj);
  m_children.clear();
  return m_children.end();
}

void ObjectGroupMetadata::deserializeStrObj(QDataStream& ds)
{
  CompactUInt64 c_uint;
  ds >> c_uint;
  m_objectChangeFrequency = c_uint.getValue();
}

void ObjectGroupMetadata::serializeStrObj(QDataStream& ds) const
{
    ds << CompactUInt64(m_objectChangeFrequency);
}

} // namespace packStore
} // namespace libmson

