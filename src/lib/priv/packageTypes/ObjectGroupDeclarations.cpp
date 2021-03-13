#include "ObjectGroupDeclarations.h"

#include "ObjectGroupObjectDataBLOBDeclaration.h"
#include "ObjectGroupObjectDeclare.h"
#include "StreamObjectHeader.h"


namespace libmson {
namespace fsshttpb {

// void ObjectGroupDeclarations::serialize(QDataStream& ds) const
//{
//  auto header = std::make_shared<StreamObjectHeader>(getType(), body_cb());

//  ds << *header;

//  for (const auto& entry : m_objects) {
//    if (entry->getType() == StreamObjectType::ObjectGroupObjectDeclare) {
//      ds << *std::dynamic_pointer_cast<ObjectGroupObjectDeclare>(entry);
//    }
//    else if (
//        entry->getType() ==
//        StreamObjectType::ObjectGroupObjectDataBLOBDeclaration) {
//      ds << *std::dynamic_pointer_cast<ObjectGroupObjectDataBLOBDeclaration>(
//          entry);
//    }
//  }

//  StreamObjectHeaderEnd end(header);
//  ds << end;
//}

// std::vector<StreamObject_SPtr_t> ObjectGroupDeclarations::getObjects() const
//{
//  return m_objects;
//}

// std::vector<ObjectGroupObjectDeclare_SPtr_t>
// ObjectGroupDeclarations::getDeclares() const
//{
//  std::vector<StreamObject_SPtr_t> vec{};

//  std::copy_if(
//      m_objects.begin(), m_objects.end(), std::back_inserter(vec),
//      [&](const StreamObject_SPtr_t& entry) {
//        return entry->getType() == StreamObjectType::ObjectGroupObjectDeclare;
//      });

//  std::vector<ObjectGroupObjectDeclare_SPtr_t> castVec;
//  std::transform(
//      vec.begin(), vec.end(), std::back_inserter(castVec),
//      [](auto const& entry) {
//        return std::dynamic_pointer_cast<ObjectGroupObjectDeclare>(entry);
//      });

//  return castVec;
//}

// std::vector<ObjectGroupObjectDataBLOBDeclaration_SPtr_t>
// ObjectGroupDeclarations::getBlobDeclares() const
//{
//  std::vector<StreamObject_SPtr_t> vec{};

//  std::copy_if(
//      m_objects.begin(), m_objects.end(), std::back_inserter(vec),
//      [&](const StreamObject_SPtr_t& entry) {
//        return entry->getType() ==
//               StreamObjectType::ObjectGroupObjectDataBLOBDeclaration;
//      });

//  std::vector<ObjectGroupObjectDataBLOBDeclaration_SPtr_t> castVec;
//  std::transform(
//      vec.begin(), vec.end(), std::back_inserter(castVec),
//      [](auto const& entry) {
//        return
//        std::dynamic_pointer_cast<ObjectGroupObjectDataBLOBDeclaration>(
//            entry);
//      });

//  return castVec;
//}

// quint64 ObjectGroupDeclarations::body_cb() const
//{
//  quint64 total{};

//  total += std::accumulate(
//      m_objects.begin(), m_objects.end(), 0,
//      [](quint64 sub, const StreamObject_SPtr_t& entry) {
//        return sub + entry->getSizeInFile();
//      });

//  total += StreamObjectHeaderEnd::getSizeInFile(getType());

//  return total;
//}

quint64 ObjectGroupDeclarations::strObjBody_cb() const
{
  const quint64 cb = std::accumulate(
      IStreamObject::cbegin(), IStreamObject::cend(), 0,
      [](quint64 sum, auto& ptr) { return sum + ptr->getSizeInFile(); });

  return cb;
}

quint64 ObjectGroupDeclarations::cbNextHeader() const
{
  return 0;
}

StreamObjectType ObjectGroupDeclarations::getType() const
{
  return StreamObjectType::ObjectGroupDeclarations;
}

void ObjectGroupDeclarations::push_back(IStreamObject_SPtr_t& obj)
{
  auto type = obj->getType();
  if (type == StreamObjectType::ObjectGroupObjectDeclare ||
      type == StreamObjectType::ObjectGroupObjectDataBLOBDeclaration) {
    return m_children.push_back(obj);
  }
}

IStreamObj_It_t ObjectGroupDeclarations::insert(
    IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  auto type = obj->getType();
  if (type == StreamObjectType::ObjectGroupObjectDeclare ||
      type == StreamObjectType::ObjectGroupObjectDataBLOBDeclaration) {
    return m_children.insert(pos, obj);
  }

  return pos;
}

void ObjectGroupDeclarations::deserializeStrObj(QDataStream& ds)
{

  while (!isObjectStreamEnd(StreamObjectType::ObjectGroupDeclarations, ds)) {
    ds.startTransaction();
    StreamObjectHeader head;
    ds >> head;
    ds.rollbackTransaction();

    auto headType = head.getType();
    if (headType == StreamObjectType::Invalid) {
      break;
    }

    if (headType == StreamObjectType::ObjectGroupObjectDeclare) {
      auto objectDeclare = std::make_shared<ObjectGroupObjectDeclare>();
      ds >> *objectDeclare;

      m_children.push_back(objectDeclare);
    }
    else if (
        headType == StreamObjectType::ObjectGroupObjectDataBLOBDeclaration) {
      auto objectDataBlobDeclaration =
          std::make_shared<ObjectGroupObjectDataBLOBDeclaration>();
      ds >> *objectDataBlobDeclaration;

      m_children.push_back(objectDataBlobDeclaration);
    }
    else {
      ds >> head;
      ds.device()->skip(head.getLength());
      continue;
    }
  }
}

void ObjectGroupDeclarations::serializeStrObj(QDataStream& ds) const
{
  for (const auto& ptr : m_children) {
    ds << *ptr;
  }
}

} // namespace fsshttpb
} // namespace libmson
