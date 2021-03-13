#include "PackageStoreFileParser.h"

#include <QDebug>

#include "PackageStoreFile.h"
#include "packageTypes/PackagingHeader.h"

namespace libmson {
namespace packStore {

PackageStoreFileParser::PackageStoreFileParser(
    QDataStream& inputStream, const QString& fileName)
    : m_ds(inputStream), m_file(std::make_shared<PackageStoreFile>())
{
  m_file->m_fileName = fileName;
}

const QUuid PackageStoreFileParser::storageManifestSchemeGuid_One{
    "{1F937CB4-B26F-445F-B9F8-17E20160E461}"};
const QUuid PackageStoreFileParser::storageManifestSchemeGuid_OneToc2 =
    QUuid("{E4DBFD38-E5C7-408B-A8A1-0E7B421E1F5F}");

const priv::ExtendedGUID PackageStoreFileParser::storageManifestRootEGuid =
    priv::ExtendedGUID(QUuid("{1A5A319C-C26b-41AA-B9C5-9BD8C44E07D4}"), 1);


const fsshttpb::CellId PackageStoreFileParser::storageManifestRootCellId =
    fsshttpb::CellId(
        priv::ExtendedGUID(QUuid("{84DEFAB9-AAA3-4A0D-A3A8-520C77AC7073}"), 1),
        priv::ExtendedGUID(QUuid("{111E4CF3-7FEF-4087-AF6A-B9544ACD334D}"), 1));

const priv::ExtendedGUID PackageStoreFileParser::storageManifestDataRootEGuid =
    priv::ExtendedGUID(QUuid("{84DEFAB9-AAA3-4A0D-A3A8-520C77AC7073}"), 2);

const priv::ExtendedGUID
    PackageStoreFileParser::storageManifestDataRootCellIdParticle =
        priv::ExtendedGUID(QUuid("{84DEFAB9-AAA3-4A0D-A3A8-520C77AC7073}"), 1);

std::shared_ptr<PackageStoreFile> PackageStoreFileParser::parse()
{
  m_ds.setByteOrder(QDataStream::LittleEndian);

  m_ds >> m_file->m_header;


  // parsing the file stream
  auto packagingStart = std::make_shared<fsshttpb::PackagingStart>();
  m_file->m_packagingStart = packagingStart;
  m_ds >> *packagingStart;


  //
  //  // following [MS-ONESTORE] section 3.5. StorageIndex, and StorageManifest
  //  // should have been set by parseDataElement method

  //  // step 7
  //  /// \todo StorageManifest RootDecl structure dependent call
  //  const auto dataRoot =
  //      m_file->m_storageManifest.lock()->getRootDeclares().at(1)->getCellId();


  //  // step 8
  //  const auto cellMappings =
  //  m_file->m_storageIndex.lock()->getCellMappings();


  //  const auto dataRootSICMiter = std::find_if(
  //      cellMappings.begin(), cellMappings.end(),
  //      [&](const streamObj::StorageIndexCellMapping_SPtr_t entry) {
  //        return entry->getCellId() == dataRoot;
  //      });

  //  if (dataRootSICMiter == cellMappings.end()) {

  //    qDebug() << "Did not found data Root StorageIndexCellMapping";
  //  }


  //  const streamObj::StorageIndexCellMapping_SPtr_t dataRootSICM =
  //      *dataRootSICMiter;

  //  const CompactExtGuid currentStorageIndexCellMappingEGuid =
  //      dataRootSICM->getExtendedGuid();


  //  // step 9

  //  auto&& elements = m_file->m_elements;

  //  const auto cellManifestCurrentRevisionDataElementIter = std::find_if(
  //      elements.begin(), elements.end(), [&](const DataElement_SPtr_t& entry)
  //      {
  //        return entry->getDataElementExtGuid() ==
  //               currentStorageIndexCellMappingEGuid;
  //      });


  //  DataElement_SPtr_t cellManifestCurrentRevisionDataElement = nullptr;
  //  if (cellManifestCurrentRevisionDataElementIter == elements.end()) {
  //    qWarning("Did not find cellManifestCurrentRevision");
  //    return m_file;
  //  }

  //    cellManifestCurrentRevisionDataElement =
  //        *cellManifestCurrentRevisionDataElementIter;

  //  if (cellManifestCurrentRevisionDataElement->getDataElementTypeEnum() !=
  //      DataElementType::CellManifest) {
  //    qDebug()
  //        << "Found cellManifestCurrentRevisionDataElement is not a
  //        CellManifest";
  //  }
  //  const auto cellManifestCurrentRevision =
  //      std::static_pointer_cast<CellManifest>(
  //          cellManifestCurrentRevisionDataElement->getBody())
  //          ->getCurrentRevision();


  //  // step 10


  return m_file;
}

// PackagingStructure_SPtr_t
// PackageStoreFileParser::parsePackagingStructure(QDataStream& ds)
//{
//  // if byte order is big endian, change to little endian
//  if (ds.byteOrder() == QDataStream::BigEndian) {
//    ds.setByteOrder(QDataStream::LittleEndian);
//  }

//  auto header = std::make_shared<PackagingStructure>();

//  m_file->m_header = header;

//  ds >> header->m_guidFileType;
//  if (header->m_guidFileType != PackagingStructure::guidFileType) {
//    qFatal("guidFileType of the PackagingStructure is invalid.");
//  }

//  ds >> header->m_guidFile;
//  ds >> header->m_guidLegacyFileVersion;
//  if (header->m_guidFile != header->m_guidLegacyFileVersion) {
//    qDebug("Irregular PackagingStructure: guidFile and "
//           "guidLegacyFileVersion are different.");
//  }

//  ds >> header->m_guidFileFormat;
//  if (header->m_guidFileFormat != PackagingStructure::guidFileFormat) {
//    qFatal("guidFileFormat of the PackagingStructure is invalid.");
//  }

//  uint32_t reserved;
//  ds >> reserved;

//  if (reserved != 0) {
//    qDebug("There is a non-zero reserved block in the PackagingStructure");
//  }

//  auto packageStart = std::make_shared<StreamObjectHeader>();
//  ds >> *packageStart;
//  header->m_packagingStart = packageStart;

//  ds >> header->m_storageIndex;
//  ds >> header->m_guidCellSchemaId;

//  if (header->m_guidCellSchemaId != PackagingStructure::guidCellSchemaId_One
//  &&
//      header->m_guidCellSchemaId !=
//          PackagingStructure::guidCellSchemaId_OneToc2) {
//    qFatal("m_guidCellSchemaId of the Packaging Structure is neither .one nor
//    "
//           ".onetoc");
//  }

//  return header;
//}

// StreamObjectHeader_SPtr_t
// PackageStoreFileParser::parseStreamObjectHeader(QDataStream& ds)
//{
//  auto header = std::make_shared<StreamObjectHeader>();
//  ds >> *header;
//  return header;
//}

// StreamObjectHeaderEnd_SPtr_t
// PackageStoreFileParser::parseStreamObjectHeaderEnd(
//    const StreamObjectHeader_SPtr_t& header, QDataStream& ds)
//{
//  auto footer = std::make_shared<StreamObjectHeaderEnd>(header);
//  header->setEnd(footer);
//  ds >> *footer;

//  return footer;
//}

// DataElementPackage_SPtr_t
// PackageStoreFileParser::parseDataElementPackage(QDataStream& ds)
//{
//  quint64 pos  = ds.device()->pos();
//  auto package = std::make_shared<DataElementPackage>();

//  auto packageStart = std::make_shared<StreamObjectHeader>();
//  ds >> *packageStart;
//  package->m_header = packageStart;

//  // reserved byte;
//  ds.skipRawData(1);


//  //  ds.skipRawData(packageStart->getLength());


//  //  if (packStore::compoundType.at(packageStart->getType()) == 1) {
//  //    parseStreamObjectHeaderEnd(packageStart, ds);
//  //  }

//  return package;
//}

// DataElement_SPtr_t PackageStoreFileParser::parseDataElement(QDataStream& ds)
//{

//  //  auto packageStart = std::make_shared<StreamObjectHeader>();
//  //  m_ds >> *packageStart;
//  //  if (packageStart->getType() != StreamObjectType::DataElementPackage) {
//  //    qFatal("Did not find beginning of a Data Element");
//  //  }


//  auto header = std::make_shared<StreamObjectHeader>();
//  ds >> *header;

//  if (header->getType() != StreamObjectType::DataElement) {
//    qFatal("Did not find beginning of a Data Element");
//  }

//  qint64 originalPos = ds.device()->pos();

//  auto element = std::make_shared<DataElement>();


//  ds >> element->m_dataElementExtGuid;
//  ds >> element->m_serialNumber;

//  CompactUInt64 dataElementType;
//  ds >> dataElementType;
//  element->m_dataElementType = dataElementType.getValue();

//  switch (static_cast<DataElementType>(element->m_dataElementType)) {
//  case DataElementType::StorageIndex: {
//    auto storageIndex      = parseStorageIndex(ds);
//    element->m_body        = storageIndex;
//    m_file->m_storageIndex = storageIndex;
//    break;
//  }
//  case DataElementType::StorageManifest: {
//    auto storageManifest      = parseStorageManifest(ds);
//    element->m_body           = storageManifest;
//    m_file->m_storageManifest = storageManifest;
//    break;
//  }
//  case DataElementType::CellManifest: {
//    element->m_body = parseCellManifest(ds);
//    break;
//  }
//  case DataElementType::RevisionManifest: {
//    element->m_body = parseRevisionManifest(ds);
//    break;
//  }
//  case DataElementType::ObjectGroup: {
//    element->m_body = parseObjectGroup(ds);
//    break;
//  }
//  case DataElementType::ObjectDataBLOB: {
//    element->m_body = parseObjectDataBLOB(ds);
//    break;
//  }
//  case DataElementType::DataElementFragment: {
//    element->m_body = parseDataElementFragment(ds);
//    break;
//  } /*
//   default: {
//     /// \todo remove temporary skipping of data
//     ///
//     qDebug() << "skipping data from type" << element->m_dataElementType
//              << " at " << originalPos << ", till "
//              << originalPos + header->getLength() << '\n';
//     ds.device()->seek(originalPos + header->getLength());
//     break;
//   }*/
//  }

//  StreamObjectHeaderEnd end(header);
//  m_ds >> end;
//  //  StreamObjectHeaderEnd packageEnd(packageStart);
//  //  m_ds >> packageEnd;


//  return element;
//}

// StorageIndex_SPtr_t PackageStoreFileParser::parseStorageIndex(QDataStream&
// ds)
//{
//  auto element = std::make_shared<StorageIndex>();

//  ds >> *element;

//  return element;
//}

// StorageManifest_SPtr_t
// PackageStoreFileParser::parseStorageManifest(QDataStream& ds)
//{
//  auto element = std::make_shared<StorageManifest>();

//  ds >> *element;


//  // Checking sturcture following the description in [MS-ONESTORE]
//  section 2.7.1

//  /// \todo file type validity check
//  ///
//  const auto& scheme = element->getSchema()->getGuid();
//  if (scheme != storageManifestSchemeGuid_One &&
//      scheme != storageManifestSchemeGuid_OneToc2) {
//    qWarning("File does have known StorageManifestSchemeGUID");
//  }

//  const auto& rootDecls = element->getRootDeclares();

//  // It is not clear, whether there are always 2 RootDeclare in the
//  // StorageManifest
//  if (rootDecls.size() != 2) {
//    qDebug("There is something unusual with StorageManifest RootDecls");
//  }

//  if (rootDecls.at(0)->getExtendedGuid() != storageManifestRootEGuid) {
//    qFatal("storageManifestRootEGuid is invalid");
//  }

//  if (rootDecls.at(0)->getCellId() != storageManifestRootCellId) {
//    qFatal("storageManifestRootCellId is invalid");
//  }

//  if (rootDecls.at(1)->getExtendedGuid() != storageManifestDataRootEGuid) {
//    qFatal("storageManifestDataRootEGuid is invalid");
//  }

//  if (rootDecls.at(1)->getCellId().getExguid1() !=
//      storageManifestDataRootCellIdParticle) {
//    qFatal("storageManifestDataRootCellId_EGuid1 is invalid");
//  }


//  return element;
//}

// CellManifest_SPtr_t PackageStoreFileParser::parseCellManifest(QDataStream&
// ds)
//{
//  auto element = std::make_shared<CellManifest>();

//  ds >> *element;

//  return element;
//}

// RevisionManifest_SPtr_t
// PackageStoreFileParser::parseRevisionManifest(QDataStream& ds)
//{
//  auto element = std::make_shared<RevisionManifest>();

//  ds >> *element;

//  return element;
//}

// ObjectGroup_SPtr_t PackageStoreFileParser::parseObjectGroup(QDataStream& ds)
//{
//  auto element = std::make_shared<ObjectGroup>();

//  ds >> *element;

//  return element;
//}

// ObjectDataBLOB_SPtr_t
// PackageStoreFileParser::parseObjectDataBLOB(QDataStream& ds)
//{
//  auto element = std::make_shared<ObjectDataBLOB>();

//  ds >> *element;

//  return element;
//}

// DataElementFragment_SPtr_t
// PackageStoreFileParser::parseDataElementFragment(QDataStream& ds)
//{
//  auto element = std::make_shared<DataElementFragment>();

//  ds >> *element;

//  return element;
//}


} // namespace packStore
} // namespace libmson
