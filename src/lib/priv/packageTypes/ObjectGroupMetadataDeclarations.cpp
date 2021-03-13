#include "ObjectGroupMetadataDeclarations.h"

#include "ObjectGroupMetadata.h"
#include "StreamObjectHeader.h"

namespace libmson {
namespace fsshttpb {

quint64 ObjectGroupMetadataDeclarations::strObjBody_cb() const
{
  const quint64 cb = std::accumulate(
      IStreamObject::cbegin(), IStreamObject::cend(), 0,
      [](quint64 sum, auto& ptr) { return sum + ptr->getSizeInFile(); });

  return cb;
}

quint64 ObjectGroupMetadataDeclarations::cbNextHeader() const
{
  return 0;
}

StreamObjectType ObjectGroupMetadataDeclarations::getType() const
{
  return StreamObjectType::ObjectGroupMetadataDeclarations;
}

void ObjectGroupMetadataDeclarations::push_back(IStreamObject_SPtr_t& obj)
{
  if (obj->getType() == StreamObjectType::ObjectGroupMetadata) {
    return m_children.push_back(obj);
  }
}

IStreamObj_It_t ObjectGroupMetadataDeclarations::insert(
    IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  if (obj->getType() == StreamObjectType::ObjectGroupMetadata) {
    return m_children.insert(pos, obj);
  }

  return pos;
}

void ObjectGroupMetadataDeclarations::deserializeStrObj(QDataStream& ds)
{
  while (!isObjectStreamEnd(
      StreamObjectType::ObjectGroupMetadataDeclarations, ds)) {
    ds.startTransaction();
    StreamObjectHeader head;
    ds >> head;
    ds.rollbackTransaction();

    auto headType = head.getType();
    if (headType == StreamObjectType::Invalid) {
      break;
    }
    if (headType == StreamObjectType::ObjectGroupMetadata) {
      auto objectDeclare = std::make_shared<ObjectGroupMetadata>();
      ds >> *objectDeclare;

      m_children.push_back(objectDeclare);
    }
    else {
      ds >> head;
      ds.device()->skip(head.getLength());
      continue;
    }
  }
}

void ObjectGroupMetadataDeclarations::serializeStrObj(QDataStream& ds) const
{
  for (const auto& ptr : m_children) {
    ds << *ptr;
  }
}

} // namespace fsshttpb
} // namespace libmson
