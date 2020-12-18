#include "ObjectGroupDeclarations.h"


namespace libmson {
namespace packStore {
namespace streamObj {

ObjectGroupDeclarations::ObjectGroupDeclarations() {}

void ObjectGroupDeclarations::deserialize(QDataStream& ds)
{

  auto header = std::make_shared<StreamObjectHeader>();
  ds >> *header;

  if (header->getType() != getType()) {
    qFatal("Trying to deserialze StreamObject of incorrect header type "
           "(ObjectGroupDeclarations)");
  }

  // the header has length 0...

  qint64 origPos = ds.device()->pos();

  char buff[1];
  qint64 peeking = ds.device()->peek(buff, 1);
  if (peeking < 1) {
    qFatal("Error reading bytes during deserialize ObjectGroupDeclarations");
  }


  while (((static_cast<uint8_t>(buff[0]) & 0x3) != 1)) {
    ds.startTransaction();
    auto mapping = std::make_shared<StreamObjectHeader>();
    ds >> *mapping;
    ds.rollbackTransaction();

    if (mapping->getType() == StreamObjectType::ObjectGroupObjectDeclare) {
      auto obj = std::make_shared<streamObj::ObjectGroupObjectDeclare>();
      ds >> *obj;

      m_objects.push_back(obj);
    }
    else if (
        mapping->getType() ==
        StreamObjectType::ObjectGroupObjectDataBLOBDeclaration) {
      auto obj =
          std::make_shared<streamObj::ObjectGroupObjectDataBLOBDeclaration>();
      ds >> *obj;

      m_objects.push_back(obj);
    }

    ds.device()->peek(buff, 1);
  }

  StreamObjectHeaderEnd end(header);
  ds >> end;
}

void ObjectGroupDeclarations::serialize(QDataStream& ds) const
{
  auto header = std::make_shared<StreamObjectHeader>(getType(), body_cb());

  ds << *header;

  for (const auto& entry : m_objects) {
    if (entry->getType() == StreamObjectType::ObjectGroupObjectDeclare) {
      ds << *std::dynamic_pointer_cast<ObjectGroupObjectDeclare>(entry);
    }
    else if (
        entry->getType() ==
        StreamObjectType::ObjectGroupObjectDataBLOBDeclaration) {
      ds << *std::dynamic_pointer_cast<ObjectGroupObjectDataBLOBDeclaration>(
          entry);
    }
  }

  StreamObjectHeaderEnd end(header);
  ds << end;
}

std::vector<StreamObject_SPtr_t> ObjectGroupDeclarations::getObjects() const
{
  return m_objects;
}

std::vector<ObjectGroupObjectDeclare_SPtr_t>
ObjectGroupDeclarations::getDeclares() const
{
  std::vector<StreamObject_SPtr_t> vec{};

  std::copy_if(
      m_objects.begin(), m_objects.end(), std::back_inserter(vec),
      [&](const StreamObject_SPtr_t& entry) {
        return entry->getType() == StreamObjectType::ObjectGroupObjectDeclare;
      });

  std::vector<ObjectGroupObjectDeclare_SPtr_t> castVec;
  std::transform(
      vec.begin(), vec.end(), std::back_inserter(castVec),
      [](auto const& entry) {
        return std::dynamic_pointer_cast<ObjectGroupObjectDeclare>(entry);
      });

  return castVec;
}

std::vector<ObjectGroupObjectDataBLOBDeclaration_SPtr_t>
ObjectGroupDeclarations::getBlobDeclares() const
{
  std::vector<StreamObject_SPtr_t> vec{};

  std::copy_if(
      m_objects.begin(), m_objects.end(), std::back_inserter(vec),
      [&](const StreamObject_SPtr_t& entry) {
        return entry->getType() ==
               StreamObjectType::ObjectGroupObjectDataBLOBDeclaration;
      });

  std::vector<ObjectGroupObjectDataBLOBDeclaration_SPtr_t> castVec;
  std::transform(
      vec.begin(), vec.end(), std::back_inserter(castVec),
      [](auto const& entry) {
        return std::dynamic_pointer_cast<ObjectGroupObjectDataBLOBDeclaration>(
            entry);
      });

  return castVec;
}

quint64 ObjectGroupDeclarations::body_cb() const
{
  quint64 total{};

  total += std::accumulate(
      m_objects.begin(), m_objects.end(), 0,
      [](quint64 sub, const StreamObject_SPtr_t& entry) {
        return sub + entry->getSizeInFile();
      });

  total += StreamObjectHeaderEnd::getSizeInFile(getType());

  return total;
}

StreamObjectType ObjectGroupDeclarations::getType() const
{


  return StreamObjectType::ObjectGroupDeclarations;
}

} // namespace streamObj
} // namespace packStore
} // namespace libmson
