#include "ObjectDataBLOB.h"

#include "StreamObjectHeader.h"

namespace libmson {
namespace packStore {
ObjectDataBLOB::ObjectDataBLOB() {}

streamObj::ObjectDataBLOB_SPtr_t ObjectDataBLOB::getObject() const
{
  return m_object;
}

void ObjectDataBLOB::setObject(const streamObj::ObjectDataBLOB_SPtr_t& object)
{
  m_object = object;
}


void ObjectDataBLOB::deserialize(QDataStream& ds)
{
  auto data = std::make_shared<streamObj::ObjectDataBLOB>();
  ds >> *data;
  m_object = std::move(data);
}

void ObjectDataBLOB::serialize(QDataStream& ds) const { ds << *m_object; }

quint64 ObjectDataBLOB::cb() const { return m_object->getSizeInFile(); }

DataElementType ObjectDataBLOB::getType() const
{
  return DataElementType::ObjectDataBLOB;
}

} // namespace packStore
} // namespace libmson
