#include "ObjectGroup.h"
#include "DataElement.h"
namespace libmson {
namespace packStore {
ObjectGroup::ObjectGroup() {}

streamObj::DataElementHash_SPtr_t ObjectGroup::getDataElementHash() const
{
  return m_dataElementHash;
}

void ObjectGroup::setDataElementHash(
    const streamObj::DataElementHash_SPtr_t& dataElementHash)
{
  m_dataElementHash = dataElementHash;
}

streamObj::ObjectGroupDeclarations_SPtr_t
ObjectGroup::getObjectGroupDeclarations() const
{
  return m_objectGroupDeclarations;
}

void ObjectGroup::setObjectGroupDeclarations(
    const streamObj::ObjectGroupDeclarations_SPtr_t& objectGroupDeclarations)
{
  m_objectGroupDeclarations = objectGroupDeclarations;
}

streamObj::ObjectGroupMetadataDeclarations_SPtr_t
ObjectGroup::getObjectGroupMetadataDeclarations() const
{
  return m_objectGroupMetadataDeclarations;
}

void ObjectGroup::setObjectGroupMetadataDeclarations(
    const streamObj::ObjectGroupMetadataDeclarations_SPtr_t&
        objectGroupMetadataDeclarations)
{
  m_objectGroupMetadataDeclarations = objectGroupMetadataDeclarations;
}

streamObj::ObjectGroupData_SPtr_t ObjectGroup::getObjectGroupData() const
{
  return m_objectGroupData;
}

void ObjectGroup::setObjectGroupData(
    const streamObj::ObjectGroupData_SPtr_t& objectGroupData)
{
  m_objectGroupData = objectGroupData;
}

void ObjectGroup::deserialize(QDataStream& ds)
{
  ds.startTransaction();
  auto strmObjHeader = std::make_shared<StreamObjectHeader>();
  ds >> *strmObjHeader;
  ds.rollbackTransaction();

  if (strmObjHeader->getType() == StreamObjectType::DataElementHash) {
    auto dataElementHash = std::make_shared<streamObj::DataElementHash>();
    ds >> *dataElementHash;
    m_dataElementHash = dataElementHash;
  }

  auto objectGroupDeclarations =
      std::make_shared<streamObj::ObjectGroupDeclarations>();
  ds >> *objectGroupDeclarations;
  m_objectGroupDeclarations = objectGroupDeclarations;

  ds.startTransaction();
  strmObjHeader = std::make_shared<StreamObjectHeader>();
  ds >> *strmObjHeader;
  ds.rollbackTransaction();

  if (strmObjHeader->getType() ==
      StreamObjectType::ObjectGroupMetadataDeclarations) {
    auto strmObj =
        std::make_shared<streamObj::ObjectGroupMetadataDeclarations>();
    ds >> *strmObj;

    m_objectGroupMetadataDeclarations = strmObj;
  }

  auto objectGroupData = std::make_shared<streamObj::ObjectGroupData>();
  ds >> *objectGroupData;
  m_objectGroupData = objectGroupData;
}

void ObjectGroup::serialize(QDataStream& ds) const
{
  ds << *m_dataElementHash;

  /// \todo determine if the whole stream object (header +end) is written if
  /// size == 0;
  ds << *m_objectGroupDeclarations;
  //  if (m_objectGroupDeclarations.getObjects().size() != 0) {
  //    ds << m_objectGroupDeclarations;
  //  }

  if (m_objectGroupMetadataDeclarations->getMetaData().size() != 0) {
    ds << *m_objectGroupMetadataDeclarations;
  }

  /// \todo determine if the whole stream object (header +end) is written if
  /// size == 0;
  ds << *m_objectGroupData;
}

quint64 ObjectGroup::cb() const
{

  return m_dataElementHash->getSizeInFile() +
         m_objectGroupDeclarations->getSizeInFile() +
         m_objectGroupMetadataDeclarations->getSizeInFile() +
         m_objectGroupData->getSizeInFile();
}

DataElementType ObjectGroup::getType() const
{
  return DataElementType::ObjectGroup;
}
} // namespace packStore
} // namespace libmson
