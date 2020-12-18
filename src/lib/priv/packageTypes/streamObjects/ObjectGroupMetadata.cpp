#include "ObjectGroupMetadata.h"


namespace libmson {
namespace packStore {
namespace streamObj {

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


void ObjectGroupMetadata::deserialize(QDataStream& ds)
{
  StreamObjectHeader header;
  ds >> header;

  if (header.getType() != getType()) {
    qFatal("Trying to deserialze StreamObject of incorrect header type "
           "(ObjectGroupObjectDeclare)");
  }

  qint64 origPos = ds.device()->pos();


  CompactUInt64 c_uint;
  ds >> c_uint;
  m_objectChangeFrequency = c_uint.getValue();


  if ((origPos + header.getLength()) != (quint64)ds.device()->pos()) {
    qFatal("Something went wrong parsing ObjectGroupObjectDeclare");
  }
}

void ObjectGroupMetadata::serialize(QDataStream& ds) const
{
  StreamObjectHeader header(getType(), body_cb());

  ds << header;

  ds << CompactUInt64(m_objectChangeFrequency);
}

quint64 ObjectGroupMetadata::body_cb() const
{
  return CompactUInt64::getSizeInFile(m_objectChangeFrequency);
}

StreamObjectType ObjectGroupMetadata::getType() const
{
  return StreamObjectType::ObjectGroupMetadata;
}


} // namespace streamObj
} // namespace packStore
} // namespace libmson
