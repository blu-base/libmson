#include "DataElement.h"

#include "CellManifestCurrentRevision.h"
#include "DataElementFragment.h"
#include "DataElementHash.h"
#include "ObjectDataBLOB.h"
#include "ObjectGroupData.h"
#include "ObjectGroupDeclarations.h"
#include "ObjectGroupMetadataDeclarations.h"
#include "RevisionManifest.h"
#include "RevisionManifestObjectGroupReference.h"
#include "RevisionManifestRootDeclare.h"
#include "StorageIndexCellMapping.h"
#include "StorageIndexManifestMapping.h"
#include "StorageIndexRevisionMapping.h"
#include "StorageManifestRootDeclare.h"
#include "StorageManifestSchemaGUID.h"
#include "StreamObjectHeader.h"

#include "dataTypes/CompactExtGuid.h"
#include "dataTypes/CompactUInt64.h"

namespace libmson {
namespace fsshttpb {

// DataElementBody_SPtr_t DataElement::getBody() const { return m_body; }

// void DataElement::setBody(const DataElementBody_SPtr_t& body) { m_body =
// body; }

DataElement::DataElement() : m_dataElementType() {}

DataElement::DataElement(
    const priv::ExtendedGUID& dataElementExtGuid,
    const LongExtGuid& serialNumber, const quint64& dataElementType)
    : m_dataElementExtGuid(dataElementExtGuid), m_serialNumber(serialNumber),
      m_dataElementType(dataElementType)
{
}

priv::ExtendedGUID DataElement::getDataElementExtGuid() const
{
  return m_dataElementExtGuid;
}

void DataElement::setDataElementExtGuid(
    const priv::ExtendedGUID& dataElementExtGuid)
{
  m_dataElementExtGuid = dataElementExtGuid;
}

LongExtGuid DataElement::getSerialNumber() const { return m_serialNumber; }

void DataElement::setSerialNumber(const LongExtGuid& serialNumber)
{
  m_serialNumber = serialNumber;
}

quint64 DataElement::getDataElementType() const { return m_dataElementType; }

void DataElement::setDataElementType(const quint64& dataElementType)
{
  m_dataElementType = dataElementType;
}
DataElementType DataElement::getDataElementTypeEnum() const
{
  return static_cast<DataElementType>(m_dataElementType);
}

void DataElement::setDataElementType(const DataElementType& dataElementType)
{
  m_dataElementType = static_cast<quint64>(dataElementType);
}

QString DataElement::dataElementTypeToString()
{
  return dataElementTypeToString(getDataElementTypeEnum());
}

QString DataElement::dataElementTypeToString(DataElementType type)
{
  switch (type) {
  case libmson::fsshttpb::DataElementType::StorageIndex:
    return "StorageIndex";
  case libmson::fsshttpb::DataElementType::StorageManifest:
    return "StorageManifest";
  case libmson::fsshttpb::DataElementType::CellManifest:
    return "CellManifest";
  case libmson::fsshttpb::DataElementType::RevisionManifest:
    return "RevisionManifest";
  case libmson::fsshttpb::DataElementType::ObjectGroup:
    return "ObjectGroup";
  case libmson::fsshttpb::DataElementType::DataElementFragment:
    return "DataElementFragment";
  case libmson::fsshttpb::DataElementType::ObjectDataBLOB:
    return "ObjectDataBLOB";
  }
}


quint64 DataElement::strObjBody_cb() const
{
  const quint64 cb = std::accumulate(
      IStreamObject::cbegin(), IStreamObject::cend(), 0,
      [](quint64 sum, auto& ptr) { return sum + ptr->getSizeInFile(); });

  return CompactExtGuid::getSizeInFile(m_dataElementExtGuid) +
         m_serialNumber.getSizeInFile() + CompactUInt64::getSizeInFile(m_dataElementType) + cb;
}

quint64 DataElement::cbNextHeader() const
{
  return CompactExtGuid::getSizeInFile(m_dataElementExtGuid) +
         m_serialNumber.getSizeInFile() + CompactUInt64::getSizeInFile(m_dataElementType);
}

void DataElement::push_back(IStreamObject_SPtr_t& obj)
{
  DataElementType dataType = getDataElementTypeEnum();

  /// \todo add some logic to prevent wrong structures
  switch (dataType) {
  case libmson::fsshttpb::DataElementType::StorageIndex:
  case libmson::fsshttpb::DataElementType::StorageManifest:
  case libmson::fsshttpb::DataElementType::CellManifest:
  case libmson::fsshttpb::DataElementType::RevisionManifest:
  case libmson::fsshttpb::DataElementType::ObjectGroup:
  case libmson::fsshttpb::DataElementType::DataElementFragment:
  case libmson::fsshttpb::DataElementType::ObjectDataBLOB:
  default:
    m_children.push_back(obj);
  }
}

IStreamObj_It_t
DataElement::insert(IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj)
{
  DataElementType dataType = getDataElementTypeEnum();

  /// \todo add some logic to prevent wrong structures
  switch (dataType) {
  case libmson::fsshttpb::DataElementType::StorageIndex:
  case libmson::fsshttpb::DataElementType::StorageManifest:
  case libmson::fsshttpb::DataElementType::CellManifest:
  case libmson::fsshttpb::DataElementType::RevisionManifest:
  case libmson::fsshttpb::DataElementType::ObjectGroup:
  case libmson::fsshttpb::DataElementType::DataElementFragment:
  case libmson::fsshttpb::DataElementType::ObjectDataBLOB:
  default:
    return m_children.insert(pos, obj);
  }
}

void DataElement::deserializeStrObj(QDataStream& ds)
{
  qint64 originalPos = ds.device()->pos();


  CompactExtGuid guid;
  ds >> guid;
  m_dataElementExtGuid = guid.getExtendedGUID();

  ds >> m_serialNumber;

  CompactUInt64 dataElementType;
  ds >> dataElementType;
  m_dataElementType = dataElementType.getValue();


  DataElementType type = static_cast<DataElementType>(m_dataElementType);

  switch (type) {
  case DataElementType::CellManifest:
    parseCellManifest(ds);
    break;
  case DataElementType::DataElementFragment:
    parseDataElementFragment(ds);
    break;
  case DataElementType::ObjectDataBLOB:
    parseObjectBlob(ds);
    break;
  case DataElementType::ObjectGroup:
    parseObjectGroup(ds);
    break;
  case DataElementType::RevisionManifest:
    parseRevisionManifest(ds);
    break;
  case DataElementType::StorageIndex:
    parseStorageIndex(ds);
    break;
  case DataElementType::StorageManifest:
    parseStorageManifest(ds);
    break;
  default: {
    while (!isObjectStreamEnd(StreamObjectType::DataElement, ds)) {
      ds.startTransaction();
      StreamObjectHeader head;
      ds >> head;

      if (head.getType() != StreamObjectType::Invalid) {
        ds.commitTransaction();
        ds.device()->skip(head.getLength());
        continue;
      }

      ds.rollbackTransaction();
      StreamObjectHeaderEnd headerEnd;
      ds >> headerEnd;
    }
  } break;
  }
}

void DataElement::serializeStrObj(QDataStream& ds) const
{

  CompactExtGuid guid(m_dataElementExtGuid);
  ds << guid;

  ds << m_serialNumber;

  CompactUInt64 dataElementType(m_dataElementType);
  ds << dataElementType;


  /// \todo serializing of the DataElement needs to be implemented
}

void DataElement::parseCellManifest(QDataStream& ds)
{
  ds.startTransaction();
  StreamObjectHeader head;
  ds >> head;
  ds.rollbackTransaction();

  auto headType = head.getType();
  if (headType == StreamObjectType::Invalid) {
    return;
  }

  if (headType == StreamObjectType::CellManifestCurrentRevision) {
    auto cellManifest = std::make_shared<CellManifestCurrentRevision>();
    ds >> *cellManifest;

    m_children.push_back(cellManifest);
  }
}


void DataElement::parseDataElementFragment(QDataStream& ds)
{
  while (!isObjectStreamEnd(StreamObjectType::DataElement, ds)) {
    ds.startTransaction();
    StreamObjectHeader head;
    ds >> head;
    ds.rollbackTransaction();

    auto headType = head.getType();
    if (headType == StreamObjectType::Invalid) {
      break;
    }

    if (headType == StreamObjectType::DataElementFragment) {
      auto objectDataBLOB = std::make_shared<DataElementFragment>();
      ds >> *objectDataBLOB;

      m_children.push_back(objectDataBLOB);
    }
    else {
      ds >> head;
      ds.device()->skip(head.getLength());
      continue;
    }
  }
}

void DataElement::parseObjectBlob(QDataStream& ds)
{
  while (!isObjectStreamEnd(StreamObjectType::DataElement, ds)) {
    ds.startTransaction();
    StreamObjectHeader head;
    ds >> head;
    ds.rollbackTransaction();

    auto headType = head.getType();
    if (headType == StreamObjectType::Invalid) {
      break;
    }

    if (headType == StreamObjectType::ObjectDataBLOB) {
      auto objectDataBLOB = std::make_shared<ObjectDataBLOB>();
      ds >> *objectDataBLOB;

      m_children.push_back(objectDataBLOB);
    }
    else {
      ds >> head;
      ds.device()->skip(head.getLength());
      continue;
    }
  }
}

void DataElement::parseObjectGroup(QDataStream& ds)
{
  ds.startTransaction();
  StreamObjectHeader head;
  ds >> head;
  ds.rollbackTransaction();

  auto headType = head.getType();
  if (headType == StreamObjectType::Invalid) {
    return;
  }

  if (headType == StreamObjectType::DataElementHash) {
    auto dataElementHash = std::make_shared<DataElementHash>();
    ds >> *dataElementHash;
    m_children.push_back(dataElementHash);
  }

  while (!isObjectStreamEnd(StreamObjectType::DataElement, ds)) {
    ds.startTransaction();
    ds >> head;
    ds.rollbackTransaction();

    headType = head.getType();
    if (headType == StreamObjectType::Invalid) {
      break;
    }

    if (headType == StreamObjectType::ObjectGroupDeclarations) {
      auto objectGroupDeclarations = std::make_shared<ObjectGroupDeclarations>();
      ds >> *objectGroupDeclarations;

      m_children.push_back(objectGroupDeclarations);
    }
    else if (headType == StreamObjectType::ObjectGroupMetadataDeclarations) {
      auto metaDeclarations =
          std::make_shared<ObjectGroupMetadataDeclarations>();
      ds >> *metaDeclarations;

      m_children.push_back(metaDeclarations);
    }
    else if (headType == StreamObjectType::ObjectGroupData) {
      auto objectGroupData = std::make_shared<ObjectGroupData>();
      ds >> *objectGroupData;

      m_children.push_back(objectGroupData);
    }
    else {
      ds >> head;
      ds.device()->skip(head.getLength());
      continue;
    }
  }
}


void DataElement::parseRevisionManifest(QDataStream& ds)
{
  ds.startTransaction();
  StreamObjectHeader head;
  ds >> head;
  ds.rollbackTransaction();

  auto headType = head.getType();
  if (headType == StreamObjectType::Invalid) {
    return;
  }

  if (headType == StreamObjectType::RevisionManifest) {
    auto revisionManifest = std::make_shared<RevisionManifest>();
    ds >> *revisionManifest;

    m_children.push_back(revisionManifest);
  }

  while (!isObjectStreamEnd(StreamObjectType::DataElement, ds)) {
    ds.startTransaction();
    ds >> head;
    ds.rollbackTransaction();

    auto headType = head.getType();
    if (headType == StreamObjectType::Invalid) {
      break;
    }
    if (headType == StreamObjectType::RevisionManifestRootDeclare) {
      auto rootDeclare = std::make_shared<RevisionManifestRootDeclare>();
      ds >> *rootDeclare;

      m_children.push_back(rootDeclare);
    }
    else if (
        headType == StreamObjectType::RevisionManifestObjectGroupReference) {
      auto groupReference =
          std::make_shared<RevisionManifestObjectGroupReference>();
      ds >> *groupReference;

      m_children.push_back(groupReference);
    }
    else {
      ds >> head;
      ds.device()->skip(head.getLength());
      continue;
    }
  }
}


void DataElement::parseStorageIndex(QDataStream& ds)
{

  while (!isObjectStreamEnd(StreamObjectType::DataElement, ds)) {
    ds.startTransaction();
    StreamObjectHeader head;
    ds >> head;
    ds.rollbackTransaction();

    auto headType = head.getType();
    if (headType == StreamObjectType::Invalid) {
      break;
    }

    if (headType == StreamObjectType::StorageIndexManifestMapping) {
      auto manifestMapping = std::make_shared<StorageIndexManifestMapping>();
      ds >> *manifestMapping;

      m_children.push_back(manifestMapping);
    }
    else if (headType == StreamObjectType::StorageIndexCellMapping) {
      auto cellMapping = std::make_shared<StorageIndexCellMapping>();
      ds >> *cellMapping;

      m_children.push_back(cellMapping);
    }
    else if (headType == StreamObjectType::StorageIndexRevisionMapping) {
      auto revisionMapping = std::make_shared<StorageIndexRevisionMapping>();
      ds >> *revisionMapping;

      m_children.push_back(revisionMapping);
    }
    else {
      ds >> head;
      ds.device()->skip(head.getLength());
      continue;
    }
  }
}

void DataElement::parseStorageManifest(QDataStream& ds)
{
  ds.startTransaction();
  StreamObjectHeader head;
  ds >> head;
  ds.rollbackTransaction();

  auto headType = head.getType();
  if (headType == StreamObjectType::Invalid) {
    return;
  }

  if (headType == StreamObjectType::StorageManifestSchemaGUID) {
    auto manifestSchema = std::make_shared<StorageManifestSchemaGUID>();
    ds >> *manifestSchema;

    m_children.push_back(manifestSchema);
  }

  while (!isObjectStreamEnd(StreamObjectType::DataElement, ds)) {
    ds.startTransaction();
    ds >> head;
    ds.rollbackTransaction();

    auto headType = head.getType();
    if (headType == StreamObjectType::Invalid) {
      break;
    }
    if (headType == StreamObjectType::StorageManifestRootDeclare) {
      auto rootDeclare = std::make_shared<StorageManifestRootDeclare>();
      ds >> *rootDeclare;

      m_children.push_back(rootDeclare);
    }
    else {
      ds >> head;
      ds.device()->skip(head.getLength());
      continue;
    }
  }
}


} // namespace fsshttpb
} // namespace libmson
