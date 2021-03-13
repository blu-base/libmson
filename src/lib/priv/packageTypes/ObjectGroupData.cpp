#include "ObjectGroupData.h"

#include "ObjectGroupObjectData.h"
#include "ObjectGroupObjectExcludedData.h"
#include "ObjectGroupObjectDataBLOBReference.h"
#include "StreamObjectHeader.h"

namespace libmson {
namespace fsshttpb {

//std::vector<StreamObject_SPtr_t> ObjectGroupData::getObjects() const
//{
//  return m_objects;
//}

//std::vector<ObjectGroupObjectData_SPtr_t> ObjectGroupData::getObjectData() const
//{
//  std::vector<StreamObject_SPtr_t> vec{};

//  std::copy_if(
//      m_objects.begin(), m_objects.end(), std::back_inserter(vec),
//      [&](const StreamObject_SPtr_t& entry) {
//        return entry->getType() == StreamObjectType::ObjectGroupObjectData;
//      });

//  std::vector<ObjectGroupObjectData_SPtr_t> castVec;
//  std::transform(
//      vec.begin(), vec.end(), std::back_inserter(castVec),
//      [](auto const& entry) {
//        return std::dynamic_pointer_cast<ObjectGroupObjectData>(entry);
//      });

//  return castVec;
//}

//std::vector<ObjectGroupObjectDataBlobReference_SPtr_t>
//ObjectGroupData::getObjectDataBlobReferences() const
//{
//  std::vector<StreamObject_SPtr_t> vec{};

//  std::copy_if(
//      m_objects.begin(), m_objects.end(), std::back_inserter(vec),
//      [&](const StreamObject_SPtr_t& entry) {
//        return entry->getType() ==
//               StreamObjectType::ObjectGroupObjectDataBLOBReference;
//      });

//  std::vector<ObjectGroupObjectDataBlobReference_SPtr_t> castVec;
//  std::transform(
//      vec.begin(), vec.end(), std::back_inserter(castVec),
//      [](auto const& entry) {
//        return std::dynamic_pointer_cast<ObjectGroupObjectDataBlobReference>(
//            entry);
//      });

//  return castVec;
//}

//std::vector<ObjectGroupObjectExcludedData_SPtr_t>
//ObjectGroupData::getObjectExcludedData() const
//{
//  std::vector<StreamObject_SPtr_t> vec{};

//  std::copy_if(
//      m_objects.begin(), m_objects.end(), std::back_inserter(vec),
//      [&](const StreamObject_SPtr_t& entry) {
//        return entry->getType() ==
//               StreamObjectType::ObjectGroupObjectExcludedData;
//      });

//  std::vector<ObjectGroupObjectExcludedData_SPtr_t> castVec;
//  std::transform(
//      vec.begin(), vec.end(), std::back_inserter(castVec),
//      [](auto const& entry) {
//        return std::dynamic_pointer_cast<ObjectGroupObjectExcludedData>(entry);
//      });

//  return castVec;
//}

//void ObjectGroupData::deserialize(QDataStream& ds)
//{
//  auto header = std::make_shared<StreamObjectHeader>();
//  ds >> *header;

//  if (header->getType() != getType()) {
//    qFatal("Trying to deserialze StreamObject of incorrect header type "
//           "(ObjectGroupData)");
//  }

//  // the header states 0 length for this compound, not checking it for validity


//  char buff[1];
//  qint64 peeking = ds.device()->peek(buff, 1);
//  if (peeking < 1) {
//    qFatal("Error reading bytes during deserialize ObjectGroupData");
//  }


//  while (((static_cast<uint8_t>(buff[0]) & 0x3) != 1)) {
//    ds.startTransaction();
//    auto mapping = std::make_shared<StreamObjectHeader>();
//    ds >> *mapping;
//    ds.rollbackTransaction();

//    if (mapping->getType() == StreamObjectType::ObjectGroupObjectData) {
//      auto obj = std::make_shared<streamObj::ObjectGroupObjectData>();
//      ds >> *obj;

//      m_objects.push_back(obj);
//    }
//    else if (
//        mapping->getType() ==
//        StreamObjectType::ObjectGroupObjectDataBLOBReference) {
//      auto obj =
//          std::make_shared<streamObj::ObjectGroupObjectDataBlobReference>();
//      ds >> *obj;

//      m_objects.push_back(obj);
//    }
//    else if (
//        mapping->getType() == StreamObjectType::ObjectGroupObjectExcludedData) {
//      auto obj = std::make_shared<streamObj::ObjectGroupObjectExcludedData>();
//      ds >> *obj;

//      m_objects.push_back(obj);
//    }

//    ds.device()->peek(buff, 1);
//  }


//  StreamObjectHeaderEnd end(header);
//  ds >> end;
//}

//void ObjectGroupData::serialize(QDataStream& ds) const
//{
//  auto header = std::make_shared<StreamObjectHeader>(getType(), body_cb());

//  ds << *header;

//  for (const auto& entry : m_objects) {
//    if (entry->getType() == StreamObjectType::ObjectGroupObjectData) {
//      ds << *std::dynamic_pointer_cast<ObjectGroupObjectData>(entry);
//    }
//    else if (
//        entry->getType() ==
//        StreamObjectType::ObjectGroupObjectDataBLOBReference) {
//      ds << *std::dynamic_pointer_cast<ObjectGroupObjectDataBlobReference>(
//          entry);
//    }
//    else if (
//        entry->getType() == StreamObjectType::ObjectGroupObjectExcludedData) {
//      ds << *std::dynamic_pointer_cast<ObjectGroupObjectExcludedData>(entry);
//    }
//  }

//  StreamObjectHeaderEnd end(header);
//  ds << end;
//}

//quint64 ObjectGroupData::body_cb() const
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


quint64 ObjectGroupData::strObjBody_cb() const
{
  const quint64 cb = std::accumulate(
      IStreamObject::cbegin(), IStreamObject::cend(), 0,
      [](quint64 sum, auto& ptr) { return sum + ptr->getSizeInFile(); });

  return cb;
}

quint64 ObjectGroupData::cbNextHeader() const
{
  return 0;
}

StreamObjectType ObjectGroupData::getType() const
{
  return StreamObjectType::ObjectGroupData;
}

void ObjectGroupData::push_back(IStreamObject_SPtr_t& obj)
{
  auto type = obj->getType();
  if (type == StreamObjectType::ObjectGroupObjectData ||
      type == StreamObjectType::ObjectGroupObjectExcludedData ||
      type == StreamObjectType::ObjectGroupObjectDataBLOBReference) {
    return m_children.push_back(obj);
  }
}

IStreamObj_It_t ObjectGroupData::insert(
    IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  auto type = obj->getType();
  if (type == StreamObjectType::ObjectGroupObjectData ||
      type == StreamObjectType::ObjectGroupObjectExcludedData ||
      type == StreamObjectType::ObjectGroupObjectDataBLOBReference) {
    return m_children.insert(pos, obj);
  }

  return pos;
}

void ObjectGroupData::deserializeStrObj(QDataStream& ds) {
  while (!isObjectStreamEnd(StreamObjectType::ObjectGroupDeclarations, ds)) {
    ds.startTransaction();
    StreamObjectHeader head;
    ds >> head;
    ds.rollbackTransaction();

    auto headType = head.getType();
    if (headType == StreamObjectType::Invalid) {
      break;
    }

    if (headType == StreamObjectType::ObjectGroupObjectData ) {
      auto objectData = std::make_shared<ObjectGroupObjectData>();
      ds >> *objectData;

      m_children.push_back(objectData);
    }
    else if (
        headType == StreamObjectType::ObjectGroupObjectExcludedData) {
      auto excludedObjectData =
          std::make_shared<ObjectGroupObjectExcludedData>();
      ds >> *excludedObjectData;

      m_children.push_back(excludedObjectData);
    }
    else if (
        headType == StreamObjectType::ObjectGroupObjectDataBLOBReference) {
      auto dataBlobReference =
          std::make_shared<ObjectGroupObjectDataBLOBReference>();
      ds >> *dataBlobReference;

      m_children.push_back(dataBlobReference);
    }
    else {
      ds >> head;
      ds.device()->skip(head.getLength());
      continue;
    }
  }
}

void ObjectGroupData::serializeStrObj(QDataStream& ds) const
{
}

} // namespace fsshttpb
} // namespace libmson
