#include "PSFtoXml.h"

#include "../../lib/priv/utils/ChunkableUtils.h"
#include "../../lib/priv/utils/Helper.h"

#include "../../lib/priv/commonTypes/CellId.h"
#include "../../lib/priv/packageTypes/DataElement.h"
#include "../../lib/priv/packageTypes/StorageIndex.h"
#include "../../lib/priv/packageTypes/StorageManifest.h"
#include "../../lib/priv/packageTypes/StreamObjectHeader.h"

#include "../../lib/priv/packageTypes/streamObjects/StorageManifestRootDeclare.h"


#include <QDataStream>
#include <QDebug>
#include <QXmlStreamWriter>

#include <memory>


bool PSFtoXml::writeSequence(
    QFile& outputFile,
    const std::shared_ptr<packStore::PackageStoreFile>& packageStoreFile)
{
  if (!outputFile.open(QIODevice::WriteOnly)) {
    qInfo() << "Couldn't open file: " << outputFile.fileName();
    return false;
  }
  QXmlStreamWriter xmlWriter(&outputFile);
  xmlWriter.setAutoFormatting(true);
  xmlWriter.writeStartDocument();

  xmlWriter.writeStartElement("PackageStoreFile");
  writePackagingStructure(packageStoreFile, xmlWriter);

  xmlWriter.writeEndElement();
  xmlWriter.writeEndDocument();

  outputFile.close();

  return true;
}

QXmlStreamWriter& PSFtoXml::writePackagingStructure(
    const std::shared_ptr<packStore::PackageStoreFile>& packageStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  const auto& header = packageStoreFile->getHeader();

  xmlWriter.writeStartElement("PackagingStructure");

  xmlWriter.writeStartElement("guidFileType");
  xmlWriter.writeCharacters(header->getGuidFileType().toString());
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("guidFile");
  xmlWriter.writeCharacters(header->getGuidFile().toString());
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("guidLegacyFileVersion");
  xmlWriter.writeCharacters(header->getGuidLegacyFileVersion().toString());
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("guidFileFormat");
  xmlWriter.writeCharacters(header->getGuidFileFormat().toString());
  xmlWriter.writeEndElement();

  xmlWriter.writeEmptyElement("rgbReserved");

  xmlWriter.writeStartElement("packagingStart");
  writeStreamObjectHeader(header->getPackagingStart(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("storageIndex");
  writeCompactExtGuid(header->getStorageIndex(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("guidCellSchemaId");
  xmlWriter.writeCharacters(header->getGuidCellSchemaId().toString());
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("DataElements");
  for (const auto& entry : packageStoreFile->getPackages()) {
    writeDataElementPackage(*entry, xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeEmptyElement("packagingEnd");

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeStreamObjectHeader(
    const packStore::StreamObjectHeader_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("StreamObjectHeader");

  xmlWriter.writeStartElement("type");
  //  xmlWriter.writeAttribute(
  //      "compound",
  //      QString::number(packStore::compoundType.at(obj->getType())));
  //  xmlWriter.writeCharacters(
  //      packStore::StreamObjectHeader::typeToString(obj->getType()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("length");
  xmlWriter.writeCharacters(QString::number(obj->getLength()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeDataElementPackage(
    const packStore::DataElementPackage& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("DataElementPackage");

  xmlWriter.writeAttribute(
      "type",
      packStore::StreamObjectHeader::typeToString(obj.getHeader()->getType()));
  xmlWriter.writeAttribute(
      "length", QString::number(obj.getHeader()->getLength()));

  if (packStore::compoundType.at(obj.getHeader()->getType())) {
    xmlWriter.writeAttribute("compound", "True");
  }

  //  writeStreamObjectHeader(obj.getHeader(), xmlWriter);

  if (obj.getHeader()->getType() == packStore::StreamObjectType::DataElement) {
    writeDataElement(obj.getDataElement(), xmlWriter);
  }

  //  xmlWriter.writeStartElement("Data");
  //  xmlWriter.writeComment(obj.getData().toHex());
  //  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("DataElements");
  for (const auto& entry : obj.getChildren()) {
    writeDataElementPackage(*entry, xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeDataElement(
    const packStore::DataElement_SPtr_t& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("DataElement");

  xmlWriter.writeStartElement("dataElementExtGuid");
  writeCompactExtGuid(obj->getDataElementExtGuid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("serialNumber");
  writeLongExtGuid(obj->getSerialNumber(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("type");
  xmlWriter.writeCharacters(
      QString::number(obj->getDataElementType().getValue()));
  xmlWriter.writeEndElement();


  xmlWriter.writeStartElement("Body");
  auto type = static_cast<packStore::DataElementType>(
      obj->getDataElementType().getValue());

  switch (type) {
  case packStore::DataElementType::StorageIndex: {

    auto dataElementType =
        std::dynamic_pointer_cast<packStore::StorageIndex>(obj->getBody());
    writeStorageIndex(dataElementType, xmlWriter);
    break;
  }
  case packStore::DataElementType::StorageManifest: {

    auto dataElementType =
        std::dynamic_pointer_cast<packStore::StorageManifest>(obj->getBody());
    writeStorageManifest(dataElementType, xmlWriter);
    break;
  }
  case packStore::DataElementType::CellManifest: {

    auto dataElementType =
        std::dynamic_pointer_cast<packStore::CellManifest>(obj->getBody());
    writeCellManifest(dataElementType, xmlWriter);
    break;
  }
  case packStore::DataElementType::RevisionManifest: {

    auto dataElementType =
        std::dynamic_pointer_cast<packStore::RevisionManifest>(obj->getBody());
    writeRevisionManifest(dataElementType, xmlWriter);
    break;
  }

  case packStore::DataElementType::ObjectGroup: {

    auto dataElementType =
        std::dynamic_pointer_cast<packStore::ObjectGroup>(obj->getBody());
    writeObjectGroup(dataElementType, xmlWriter);
    break;
  }
  default:
    break;
  }

  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeStorageIndex(
    const packStore::StorageIndex_SPtr_t& obj, QXmlStreamWriter& xmlWriter)
{

  xmlWriter.writeStartElement("StorageIndex");

  writeStorageIndexManifestMapping(obj->getManifestMapping(), xmlWriter);

  xmlWriter.writeStartElement("CellMappings");
  for (const auto& entry : obj->getCellMappings()) {
    writeStorageIndexCellMapping(entry, xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("RevisionMappings");
  for (const auto& entry : obj->getRevisionMappings()) {
    writeStorageIndexRevisionMapping(entry, xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeStorageManifest(
    const packStore::StorageManifest_SPtr_t& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("StorageManifest");

  xmlWriter.writeStartElement("StorageManifestSchema");
  xmlWriter.writeCharacters(obj->getSchema()->getGuid().toString());
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("RootDeclares");
  for (const auto& entry : obj->getRootDeclares()) {
    writeRootDeclare(entry, xmlWriter);
  }
  xmlWriter.writeEndElement();


  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeCellManifest(
    const packStore::CellManifest_SPtr_t& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("CellManifest");

  writeCellManifestCurrentRevision(obj->getCurrentRevision(), xmlWriter);

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeRevisionManifest(
    const packStore::RevisionManifest_SPtr_t& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("RevisionManifest");

  writeRevisionManifest(obj->getRevisionManifest(), xmlWriter);

  xmlWriter.writeStartElement("RootDeclares");
  for (const auto& entry : obj->getRootDeclares()) {
    writeRevisionManifestRootDeclare(entry, xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("ObjectGroupReferences");
  for (const auto& entry : obj->getObjectGroups()) {
    writeRevisionManifestObjectGroupReference(entry, xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
  return xmlWriter;
}

/*--------------------------------------------------------------------------*/
/* stream object Types*/
/*--------------------------------------------------------------------------*/


QXmlStreamWriter& PSFtoXml::writeStorageIndexManifestMapping(
    const packStore::streamObj::StorageIndexManifestMapping_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{


  xmlWriter.writeStartElement("StorageIndexManifestMapping");

  if (obj != nullptr) {
    xmlWriter.writeStartElement("ExtGuid");
    writeCompactExtGuid(obj->getExtendedGuid(), xmlWriter);
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("SerialNumber");
    writeLongExtGuid(obj->getSerialNumber(), xmlWriter);
    xmlWriter.writeEndElement();
  }

  xmlWriter.writeEndElement();
  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeStorageIndexCellMapping(
    const packStore::streamObj::StorageIndexCellMapping_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("StorageIndexCellMapping");
  if (obj != nullptr) {

    writeCellId(obj->getCellId(), xmlWriter);


    xmlWriter.writeStartElement("ExtGuid");
    writeCompactExtGuid(obj->getExtendedGuid(), xmlWriter);
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("SerialNumber");
    writeLongExtGuid(obj->getSerialNumber(), xmlWriter);
    xmlWriter.writeEndElement();
  }

  xmlWriter.writeEndElement();
  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeStorageIndexRevisionMapping(
    const packStore::streamObj::StorageIndexRevisionMapping_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("StorageIndexRevisionMapping");
  if (obj != nullptr) {
    xmlWriter.writeStartElement("Revision");
    writeCompactExtGuid(obj->getExtendedGuid(), xmlWriter);
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("ExtGuid");
    writeCompactExtGuid(obj->getExtendedGuid(), xmlWriter);
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("SerialNumber");
    writeLongExtGuid(obj->getSerialNumber(), xmlWriter);
    xmlWriter.writeEndElement();
  }

  xmlWriter.writeEndElement();
  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeRootDeclare(
    const packStore::streamObj::StorageManifestRootDeclare_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("RootDeclare");
  xmlWriter.writeStartElement("RootExtGuid");
  writeCompactExtGuid(obj->getExtendedGuid(), xmlWriter);
  xmlWriter.writeEndElement();

  writeCellId(obj->getCellId(), xmlWriter);


  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeCellManifestCurrentRevision(
    const packStore::streamObj::CellManifestCurrentRevision_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("CellManifestCurrentRevision");
  writeCompactExtGuid(obj->getExtendedGuid(), xmlWriter);

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeRevisionManifest(
    const packStore::streamObj::RevisionManifest_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("RevisionManifest");

  xmlWriter.writeStartElement("RevisionId");
  writeCompactExtGuid(obj->getRevisionId(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("BaseRevisionId");
  writeCompactExtGuid(obj->getBaseRevisionId(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeObjectGroup(
    const packStore::ObjectGroup_SPtr_t& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectGroup");

  if (obj->getDataElementHash() != nullptr) {
    writeDataElementHash(obj->getDataElementHash(), xmlWriter);
  }
  if (obj->getObjectGroupDeclarations() != nullptr) {
    writeObjectGroupDeclarations(obj->getObjectGroupDeclarations(), xmlWriter);
  }

  if (obj->getObjectGroupMetadataDeclarations() != nullptr) {
    writeObjectGroupMetadataDeclarations(
        obj->getObjectGroupMetadataDeclarations(), xmlWriter);
  }
  if (obj->getObjectGroupData() != nullptr) {
    writeObjectGroupData(obj->getObjectGroupData(), xmlWriter);
  }
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeRevisionManifestObjectGroupReference(
    const packStore::streamObj::RevisionManifestObjectGroupReference_SPtr_t&
        obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("RevisionManifestObjectGroupReference");

  xmlWriter.writeStartElement("ObjectGroup");
  writeCompactExtGuid(obj->getObjectGroup(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeRevisionManifestRootDeclare(
    const packStore::streamObj::RevisionManifestRootDeclare_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("RevisionManifestRootDeclare");

  xmlWriter.writeStartElement("Root");
  writeCompactExtGuid(obj->getRoot(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("Object");
  writeCompactExtGuid(obj->getObject(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeDataElementHash(
    const packStore::streamObj::DataElementHash_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{


  xmlWriter.writeStartElement("DataElementHash");


  xmlWriter.writeStartElement("Scheme");
  xmlWriter.writeCharacters(QString::number(obj->getScheme()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("Data");
  writeBinaryItem(obj->getData(), xmlWriter);
  xmlWriter.writeEndElement();


  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeObjectGroupDeclarations(
    const packStore::streamObj::ObjectGroupDeclarations_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectGroupDeclarations");

  for (const auto& entry : obj->getObjects()) {

    if (entry->getType() ==
        packStore::StreamObjectType::ObjectGroupObjectDeclare) {
      writeObjectGroupObjectDeclare(
          std::dynamic_pointer_cast<
              packStore::streamObj::ObjectGroupObjectDeclare>(entry),
          xmlWriter);
    }
    else if (
        entry->getType() ==
        packStore::StreamObjectType::ObjectGroupObjectDataBLOBDeclaration) {
      writeObjectGroupObjectDataBLOBDeclaration(
          std::dynamic_pointer_cast<
              packStore::streamObj::ObjectGroupObjectDataBLOBDeclaration>(
              entry),
          xmlWriter);
    }
  }


  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeObjectGroupMetadataDeclarations(
    const packStore::streamObj::ObjectGroupMetadataDeclarations_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectGroupMetadataDeclarations");

  for (const auto& entry : obj->getMetaData()) {
    writeObjectGroupMetadata(entry, xmlWriter);
  }
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeObjectGroupData(
    const packStore::streamObj::ObjectGroupData_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectGroupData");

  for (const auto& entry : obj->getObjects()) {

    if (entry->getType() ==
        packStore::StreamObjectType::ObjectGroupObjectDataBLOBReference) {
      writeObjectGroupObjectDataBlobReference(
          std::dynamic_pointer_cast<
              packStore::streamObj::ObjectGroupObjectDataBlobReference>(entry),
          xmlWriter);
    }
    else if (
        entry->getType() ==
        packStore::StreamObjectType::ObjectGroupObjectData) {
      writeObjectGroupObjectData(
          std::dynamic_pointer_cast<
              packStore::streamObj::ObjectGroupObjectData>(entry),
          xmlWriter);
    }
    else if (
        entry->getType() ==
        packStore::StreamObjectType::ObjectGroupObjectExcludedData) {
      writeObjectGroupObjectExcludedData(
          std::dynamic_pointer_cast<
              packStore::streamObj::ObjectGroupObjectExcludedData>(entry),
          xmlWriter);
    }
  }

  xmlWriter.writeEndElement();


  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeObjectGroupObjectDeclare(
    const packStore::streamObj::ObjectGroupObjectDeclare_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectGroupObjectDeclare");

  xmlWriter.writeStartElement("ExtendedGuid");
  writeCompactExtGuid(obj->getExtendedGuid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("PartitionId");
  xmlWriter.writeCharacters(QString::number(obj->getPartitionId()));
  xmlWriter.writeEndElement();
  xmlWriter.writeStartElement("DataSize");
  xmlWriter.writeCharacters(QString::number(obj->getDataSize()));
  xmlWriter.writeEndElement();
  xmlWriter.writeStartElement("ObjectReferencesCount");
  xmlWriter.writeCharacters(QString::number(obj->getObjectReferencesCount()));
  xmlWriter.writeEndElement();
  xmlWriter.writeStartElement("CellReferencesCount");
  xmlWriter.writeCharacters(QString::number(obj->getCellReferencesCount()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeObjectGroupObjectDataBLOBDeclaration(
    const packStore::streamObj::ObjectGroupObjectDataBLOBDeclaration_SPtr_t&
        obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectGroupObjectDataBLOBDeclaration");

  xmlWriter.writeStartElement("ExtendedGuid");
  writeCompactExtGuid(obj->getExtendedGuid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("BlobExtendedGuid");
  writeCompactExtGuid(obj->getBlobExtendedGuid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("PartitionId");
  xmlWriter.writeCharacters(QString::number(obj->getPartitionId()));
  xmlWriter.writeEndElement();
  xmlWriter.writeStartElement("ObjectReferencesCount");
  xmlWriter.writeCharacters(QString::number(obj->getObjectReferencesCount()));
  xmlWriter.writeEndElement();
  xmlWriter.writeStartElement("CellReferencesCount");
  xmlWriter.writeCharacters(QString::number(obj->getCellReferencesCount()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeObjectGroupMetadata(
    const packStore::streamObj::ObjectGroupMetadata_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectGroupMetadata");

  xmlWriter.writeStartElement("ChangeFrequency");
  xmlWriter.writeCharacters(QString::number(obj->getObjectChangeFrequency()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeObjectGroupObjectDataBlobReference(
    const packStore::streamObj::ObjectGroupObjectDataBlobReference_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectGroupMetadata");

  writeCompactExtGuidArray(obj->getObjectExtGuidArray(), xmlWriter);

  writeCellIdArray(obj->getCellIdArray(), xmlWriter);


  xmlWriter.writeStartElement("ExtendedGuid");
  writeCompactExtGuid(obj->getExtendedGuid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeObjectGroupObjectData(
    const packStore::streamObj::ObjectGroupObjectData_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectGroupMetadata");

  writeCompactExtGuidArray(obj->getExtendedGuidArray(), xmlWriter);

  writeCellIdArray(obj->getCellIdArray(), xmlWriter);

  xmlWriter.writeStartElement("Data");
  writeBinaryItem(obj->getData(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeObjectGroupObjectExcludedData(
    const packStore::streamObj::ObjectGroupObjectExcludedData_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectGroupMetadata");

  writeCompactExtGuidArray(obj->getExtendedGuidArray(), xmlWriter);

  writeCellIdArray(obj->getCellIdArray(), xmlWriter);

  xmlWriter.writeStartElement("DataSize");
  xmlWriter.writeCharacters(QString::number(obj->getDataSize()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}


/*--------------------------------------------------------------------------*/
/* common Types*/
/*--------------------------------------------------------------------------*/

QXmlStreamWriter& PSFtoXml::writeCompactID(
    const priv::CompactID& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("CompactID");

  xmlWriter.writeAttribute(
      "guidIndex", priv::qStringHex(obj.getGuidIndex(), 12));
  xmlWriter.writeAttribute("n", QString::number(obj.getN()));

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeExtendedGUID(
    const priv::ExtendedGUID& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ExtendedGUID");

  xmlWriter.writeCharacters(obj.toString());

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter&
PSFtoXml::writeGUID(const QUuid& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("GUID");
  xmlWriter.writeCharacters(obj.toString());

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeCompactExtGuid(
    const packStore::CompactExtGuid& obj, QXmlStreamWriter& xmlWriter)
{
  //  xmlWriter.writeStartElement("CompactExtGuid");
  xmlWriter.writeAttribute(
      "type", packStore::CompactExtGuid::typeToString(obj.getWidthType()));
  xmlWriter.writeCharacters(obj.toString());
  //  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeLongExtGuid(
    const packStore::LongExtGuid& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("LongExtGuid");

  xmlWriter.writeStartElement("guid");
  xmlWriter.writeCharacters(obj.getGuid().toString());
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("serialNumber");
  xmlWriter.writeCharacters(QString::number(obj.getSerialNumber()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter&
PSFtoXml::writeCellId(const packStore::CellId& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("CellId");
  xmlWriter.writeStartElement("ExtGuid1");
  writeCompactExtGuid(obj.getExguid1(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("ExtGuid2");
  writeCompactExtGuid(obj.getExguid2(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeBinaryItem(
    const packStore::BinaryItem& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("BinaryItem");
  xmlWriter.writeAttribute("length", QString::number(obj.getLength()));

  xmlWriter.writeCharacters(obj.getContent().toHex());
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeCompactExtGuidArray(
    const packStore::CompactExtGuidArray& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("CompactExtGuidArray");
  xmlWriter.writeAttribute("count", QString::number(obj.getCount()));

  for (const auto& entry : obj.getElements()) {
    writeCompactExtGuid(entry, xmlWriter);
  }

  xmlWriter.writeEndElement();
  return xmlWriter;
}

QXmlStreamWriter& PSFtoXml::writeCellIdArray(
    const packStore::CellIdArray& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("CellIdArray");
  xmlWriter.writeAttribute("count", QString::number(obj.getCount()));

  for (const auto& entry : obj.getElements()) {
    writeCellId(entry, xmlWriter);
  }


  xmlWriter.writeEndElement();
  return xmlWriter;
}


/*--------------------------------------------------------------------------*/
/* property Types */
/*--------------------------------------------------------------------------*/

// QXmlStreamWriter&
// PSFtoXml::writeJCID(const JCID& obj, QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeStartElement("JCID");

//  xmlWriter.writeAttribute("type", obj.typeToString());
//  xmlWriter.writeAttribute("index", qStringHex(obj.index(), 4));
//  xmlWriter.writeAttribute("isBinary", obj.IsBinary() ? "true" : "false");
//  xmlWriter.writeAttribute(
//      "IsPropertySet", obj.IsPropertySet() ? "true" : "false");
//  xmlWriter.writeAttribute("IsGraphNode", obj.IsGraphNode() ? "true" :
//  "false"); xmlWriter.writeAttribute("IsFileData", obj.IsFileData() ? "true"
//  : "false"); xmlWriter.writeAttribute("IsReadOnly", obj.IsReadOnly() ?
//  "true" : "false");

//  xmlWriter.writeEndElement();

//  return xmlWriter;
//}

// QXmlStreamWriter&
// PSFtoXml::writePropertyID(const PropertyID& obj, QXmlStreamWriter&
// xmlWriter)
//{
//  xmlWriter.writeStartElement("PropertyID");

//  xmlWriter.writeAttribute("Value", qStringHex(obj.value(), 8));
//  xmlWriter.writeAttribute("ID", PropertyID::idToString(obj.id()));
//  xmlWriter.writeAttribute("Type", PropertyID::typeToString(obj.type()));
//  xmlWriter.writeAttribute("boolValue", obj.boolValue() ? "True" : "False");

//  xmlWriter.writeEndElement();

//  return xmlWriter;
//}

// QXmlStreamWriter& PSFtoXml::writeIPropertyType(
//    const std::shared_ptr<IPropertyType>& obj, QXmlStreamWriter& xmlWriter)
//{

//  switch (obj->getType()) {
//  case PropertyIDType::NoData: {
//    writePropertyType_NoData(xmlWriter);
//    break;
//  }
//  case PropertyIDType::Bool: {
//    writePropertyType_Bool(xmlWriter);
//    break;
//  }
//  case PropertyIDType::OneByteOfData: {
//    auto castObj =
//    std::static_pointer_cast<PropertyType_OneByteOfData>(obj);
//    writePropertyType_OneByteOfData(castObj, xmlWriter);
//    break;
//  }
//  case PropertyIDType::TwoBytesOfData: {
//    auto castObj =
//    std::static_pointer_cast<PropertyType_TwoBytesOfData>(obj);
//    writePropertyType_TwoBytesOfData(castObj, xmlWriter);
//    break;
//  }
//  case PropertyIDType::FourBytesOfData: {
//    auto castObj =
//    std::static_pointer_cast<PropertyType_FourBytesOfData>(obj);
//    writePropertyType_FourBytesOfData(castObj, xmlWriter);
//    break;
//  }
//  case PropertyIDType::EightBytesOfData: {
//    auto castObj =
//    std::static_pointer_cast<PropertyType_EightBytesOfData>(obj);
//    writePropertyType_EightBytesOfData(castObj, xmlWriter);
//    break;
//  }
//  case PropertyIDType::FourBytesOfLengthFollowedByData: {
//    auto castObj =
//        std::static_pointer_cast<PropertyType_FourBytesOfLengthFollowedByData>(
//            obj);
//    writePropertyType_FourBytesOfLengthFollowedByData(castObj, xmlWriter);
//    break;
//  }
//  case PropertyIDType::ObjectID: {
//    auto castObj = std::static_pointer_cast<PropertyType_ObjectID>(obj);
//    writePropertyType_ObjectID(castObj, xmlWriter);
//    break;
//  }
//  case PropertyIDType::ObjectSpaceID: {
//    writePropertyType_ObjectSpaceID(xmlWriter);
//    break;
//  }
//  case PropertyIDType::ContextID: {
//    auto castObj = std::static_pointer_cast<PropertyType_ContextID>(obj);
//    writePropertyType_ContextID(castObj, xmlWriter);
//    break;
//  }
//  case PropertyIDType::ArrayOfPropertyValues: {
//    auto castObj =
//        std::static_pointer_cast<PropertyType_ArrayOfPropertyValues>(obj);
//    writePropertyType_ArrayOfPropertyValues(castObj, xmlWriter);
//    break;
//  }
//  case PropertyIDType::PropertySet: {
//    auto castObj = std::static_pointer_cast<PropertyType_PropertySet>(obj);
//    writePropertyType_PropertySet(castObj, xmlWriter);
//    break;
//  }

//  case PropertyIDType::ArrayOfContextIDs:
//  case PropertyIDType::ArrayOfObjectIDs:
//  case PropertyIDType::ArrayOfObjectSpaceIDs:
//  case PropertyIDType::ArrayNumber: {
//    auto castObj = std::static_pointer_cast<PropertyType_ArrayNumber>(obj);
//    writePropertyType_ArrayNumber(castObj, xmlWriter);
//    break;
//  }


//  case PropertyIDType::None:
//  case PropertyIDType::InvalidType:
//    break;
//  default:
//    break;
//  }


//  return xmlWriter;
//}

// QXmlStreamWriter&
// PSFtoXml::writePropertySet(const PropertySet& obj, QXmlStreamWriter&
// xmlWriter)
//{
//  xmlWriter.writeStartElement("PropertySet");

//  xmlWriter.writeAttribute("cProperties",
//  QString::number(obj.cProperties()));

//  for (size_t i{0}; i < obj.rgPrids().size(); i++) {

//    auto currentPrid = obj.rgPrids()[i];
//    auto currentData = obj.rgData()[i];


//    xmlWriter.writeStartElement("PropertyID");

//    xmlWriter.writeAttribute(
//        "ID", PropertyID::idToString(obj.rgPrids()[i].id()));

//    xmlWriter.writeAttribute(
//        "Type", PropertyID::typeToString(currentPrid.type()));
//    xmlWriter.writeAttribute(
//        "boolValue", currentPrid.boolValue() ? "True" : "False");
//    xmlWriter.writeAttribute("Value", qStringHex(currentPrid.value(), 8));

//    switch (currentPrid.id()) {
//    case PropertyIDs::LayoutTightLayout: {
//      xmlWriter.writeStartElement("LayoutTightLayout");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::PageWidth: {
//      xmlWriter.writeStartElement("PageWidth");
//      const auto body =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(body);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float pagewidth;
//      bytes >> pagewidth;
//      // Validity specified by MS-ONE, sec 2.3.6
//      if (pagewidth < 2.0 || pagewidth > 44.0) {
//        xmlWriter.writeAttribute("valid", "False");
//      }
//      xmlWriter.writeCharacters(QString::number(pagewidth, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::PageHeight: {
//      xmlWriter.writeStartElement("PageHeight");
//      const auto body =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(body);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float pageheight;
//      bytes >> pageheight;
//      // Validity specified by MS-ONE, sec 2.3.7,
//      // though does not check: (PageMarginTop + PageMarginBottom + 0.5 <
//      // pageheight)
//      if (pageheight < 0.5 || pageheight > 44.0) {
//        xmlWriter.writeAttribute("valid", "False");
//      }
//      xmlWriter.writeCharacters(QString::number(pageheight, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::OutlineElementChildLevel: {
//      xmlWriter.writeStartElement("IndentationLevel");
//      const auto body =
//          std::dynamic_pointer_cast<PropertyType_OneByteOfData>(currentData)
//              ->data();
//      QDataStream bytes(body);

//      uint8_t val;
//      bytes >> val;

//      xmlWriter.writeCharacters(QString::number(val));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::Bold: {
//      xmlWriter.writeStartElement("Bold");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::Italic: {
//      xmlWriter.writeStartElement("Italic");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::Underline: {
//      xmlWriter.writeStartElement("Underline");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::Strikethrough: {
//      xmlWriter.writeStartElement("Strikethrough");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::Superscript: {
//      xmlWriter.writeStartElement("Superscript");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::Subscript: {
//      xmlWriter.writeStartElement("Subscript");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::Font: {
//      xmlWriter.writeStartElement("Font");
//      if (currentPrid.type() ==
//          PropertyIDType::FourBytesOfLengthFollowedByData) {
//        const auto data =
//            std::dynamic_pointer_cast<
//                PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//                ->data();
//        QString string = QString::fromUtf8(data.constData(), data.size());
//        xmlWriter.writeCharacters(string);
//      }
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::FontSize: {
//      xmlWriter.writeStartElement("FontSize");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_TwoBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      uint16_t val;
//      bytes >> val;
//      // validity given by MS-ONE sec 2.3.16
//      if (val < 12 || val > 288) {
//        xmlWriter.writeAttribute("valid", "false");
//      }
//      xmlWriter.writeCharacters(QString::number(val));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::FontColor: {
//      xmlWriter.writeStartElement("FontColor");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      libmson::ColorRef val;
//      bytes >> val;

//      writeColorRef(val, xmlWriter);

//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::Highlight: {
//      xmlWriter.writeStartElement("Highlight");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      libmson::ColorRef val;
//      bytes >> val;

//      writeColorRef(val, xmlWriter);
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::RgOutlineIndentDistance: {
//      xmlWriter.writeStartElement("RgOutlineIndentDistance");
//      const auto body =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();
//      QDataStream bytes(body);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      quint8 count;
//      bytes >> count;
//      xmlWriter.writeAttribute("count", QString::number(count));
//      const QByteArray unused = bytes.device()->read(3);
//      xmlWriter.writeAttribute("unused-bytes", unused.toHex());

//      xmlWriter.writeStartElement("rgIndents");
//      xmlWriter.writeCharacters("{");
//      for (quint8 j = 0; j < count; j++) {
//        float distance;
//        bytes >> distance;
//        xmlWriter.writeCharacters(QString::number(distance, 'f', 5));

//        if (j + 1 != count) {
//          xmlWriter.writeCharacters(", ");
//        }
//      }
//      xmlWriter.writeCharacters("}");
//      xmlWriter.writeEndElement();

//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::BodyTextAlignment: {
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_OneByteOfData>(currentData)
//              ->data();
//      libmson::BodyTextAlignment bta;
//      QDataStream bytes(data);
//      bytes >> bta;
//      writeBodyTextAlignment(bta, xmlWriter);
//      break;
//    }
//    case PropertyIDs::OffsetFromParentHoriz: {
//      xmlWriter.writeStartElement("OffsetFromParentHoriz");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::OffsetFromParentVert: {
//      xmlWriter.writeStartElement("OffsetFromParentVert");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }
//      //    case PropertyIDs::NumberListFormat:
//      //      m_id_string = "NumberListFormat";
//      //      break;
//    case PropertyIDs::LayoutMaxWidth: {
//      xmlWriter.writeStartElement("LayoutMaxWidth");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::LayoutMaxHeight: {
//      xmlWriter.writeStartElement("LayoutMaxHeight");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }
//      //    case PropertyIDs::ContentChildNodes:
//      //      m_id_string = "ContentChildNodes";
//      //      break;
//      //    case PropertyIDs::ElementChildNodes:
//      //      m_id_string = "ElementChildNodes";
//      //      break;
//    case PropertyIDs::EnableHistory: {
//      xmlWriter.writeStartElement("EnableHistory");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::RichEditTextUnicode: {
//      xmlWriter.writeStartElement("RichEditTextUnicode");
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();
//      QString string = QString::fromUtf16(
//          reinterpret_cast<const ushort*>(data.constData()), data.size() /
//          2);

//      xmlWriter.writeCharacters(string);
//      xmlWriter.writeEndElement();
//      break;
//    }
//      //    case PropertyIDs::ListNodes:
//      //      m_id_string = "ListNodes";
//      //      break;
//    case PropertyIDs::NotebookManagementEntityGuid: {
//      xmlWriter.writeStartElement("NotebookManagementEntityGuid");
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      QUuid val;
//      bytes >> val;
//      xmlWriter.writeCharacters(val.toString());
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::OutlineElementRTL: {
//      xmlWriter.writeStartElement("OutlineElementRTL");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::LanguageID: {

//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      libmson::LCID val;
//      bytes >> val;
//      writeLCID(val, xmlWriter);
//      break;
//    }

//    case PropertyIDs::LayoutAlignmentInParent: {
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      libmson::LayoutAlignment val;
//      bytes >> val;
//      writeLayoutAlignment(val, xmlWriter);
//      break;
//    }
//      //    case PropertyIDs::PictureContainer:
//      //      m_id_string = "PictureContainer";
//      //      break;
//    case PropertyIDs::PageMarginTop: {
//      xmlWriter.writeStartElement("PageMarginTop");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::PageMarginBottom: {
//      xmlWriter.writeStartElement("PageMarginBottom");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::PageMarginLeft: {
//      xmlWriter.writeStartElement("PageMarginLeft");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::PageMarginRight: {
//      xmlWriter.writeStartElement("PageMarginRight");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::ListFont: {
//      xmlWriter.writeStartElement("ListFont");
//      if (currentPrid.type() ==
//          PropertyIDType::FourBytesOfLengthFollowedByData) {
//        const auto body = std::dynamic_pointer_cast<
//            PropertyType_FourBytesOfLengthFollowedByData>(currentData);
//        QString string =
//            QString::fromUtf8(body->data().constData(), body->cb());
//        xmlWriter.writeCharacters(string);
//      }
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::TopologyCreationTimeStamp: {
//      xmlWriter.writeStartElement("TopologyCreationTimeStamp");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_EightBytesOfData>(currentData)
//              ->data();

//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      libmson::FileTime time;
//      bytes >> time;
//      xmlWriter.writeCharacters(
//          time.getTime().toString("dd/MM/yyyy hh:mm:ss AP"));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::LayoutAlignmentSelf: {
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      libmson::LayoutAlignment val;
//      bytes >> val;
//      writeLayoutAlignment(val, xmlWriter);
//      break;
//    }
//    case PropertyIDs::IsTitleTime: {
//      xmlWriter.writeStartElement("IsTitleTime");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::IsBoilerText: {
//      xmlWriter.writeStartElement("IsBoilerText");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::PageSize: {
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      libmson::PageSize ps;
//      bytes >> ps;
//      writePageSize(ps, xmlWriter);
//      break;
//    }

//    case PropertyIDs::PortraitPage: {
//      xmlWriter.writeStartElement("PortraitPage");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::EnforceOutlineStructure: {
//      xmlWriter.writeStartElement("EnforceOutlineStructure");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::EditRootRTL: {
//      xmlWriter.writeStartElement("EditRootRTL");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::CannotBeSelected: {
//      xmlWriter.writeStartElement("CannotBeSelected");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::IsTitleText: {
//      xmlWriter.writeStartElement("IsTitleText");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::IsTitleDate: {
//      xmlWriter.writeStartElement("IsTitleDate");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::ListRestart: {
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);

//      quint32 val;
//      bytes >> val;

//      xmlWriter.writeStartElement("ListRestart");
//      xmlWriter.writeCharacters(QString::number(val));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::IsLayoutSizeSetByUser: {
//      xmlWriter.writeStartElement("IsLayoutSizeSetByUser");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::ListSpacingMu: {
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float val;
//      bytes >> val;

//      xmlWriter.writeStartElement("ListSpacingMu");
//      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::LayoutOutlineReservedWidth: {
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float val;
//      bytes >> val;

//      xmlWriter.writeStartElement("LayoutOutlineReservedWidth");
//      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::LayoutResolveChildCollisions: {
//      xmlWriter.writeStartElement("LayoutResolveChildCollisions");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::IsReadOnly: {
//      xmlWriter.writeStartElement("IsReadOnly");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::LayoutMinimumOutlineWidth: {
//      xmlWriter.writeStartElement("LayoutMinimumOutlineWidth");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::LayoutCollisionPriority: {
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      quint32 val;
//      bytes >> val;

//      xmlWriter.writeStartElement("LayoutCollisionPriority");
//      xmlWriter.writeCharacters(qStringHex(val, 8));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::CachedTitleString: {
//      xmlWriter.writeStartElement("wz");
//      const auto body = std::dynamic_pointer_cast<
//          PropertyType_FourBytesOfLengthFollowedByData>(currentData);
//      QString string = QString::fromUtf8(body->data().constData(),
//      body->cb()); xmlWriter.writeCharacters(string);
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::DescendantsCannotBeMoved: {
//      xmlWriter.writeStartElement("DescendantsCannotBeMoved");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::RichEditTextLangID: {
//      xmlWriter.writeStartElement("RichEditTextLangID");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_TwoBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      libmson::LCID val;
//      bytes >> val;

//      writeLCID(val, xmlWriter);
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::LayoutTightAlignment: {
//      xmlWriter.writeStartElement("LayoutTightAlignment");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::Charset: {
//      xmlWriter.writeStartElement("Charset");
//      auto data =
//          std::dynamic_pointer_cast<PropertyType_OneByteOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      libmson::Charset set;
//      bytes >> set;

//      xmlWriter.writeCharacters(set.toString());
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::CreationTimeStamp: {
//      xmlWriter.writeStartElement("CreationTimeStamp");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();

//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      libmson::Time32 time;
//      bytes >> time;
//      xmlWriter.writeCharacters(
//          time.getTime().toString("dd/MM/yyyy hh:mm:ss AP"));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::Deletable: {
//      xmlWriter.writeStartElement("Deletable");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::ListMSAAIndex: {
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_TwoBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);

//      libmson::ListMSAAIndex index;
//      bytes >> index;

//      writeListMSAAIndex(index, xmlWriter);

//      break;
//    }
//    case PropertyIDs::IsBackground: {
//      xmlWriter.writeStartElement("IsBackground");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::IRecordMedia: {
//      xmlWriter.writeStartElement("IRecordMedia");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();

//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      quint32 val;
//      bytes >> val;
//      xmlWriter.writeCharacters(
//          val == 1 ? "Audio" : (val == 2 ? "Video" : "invalid"));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::CachedTitleStringFromPage: {
//      xmlWriter.writeStartElement("wz");
//      const auto body = std::dynamic_pointer_cast<
//          PropertyType_FourBytesOfLengthFollowedByData>(currentData);
//      QString string = QString::fromUtf8(body->data().constData(),
//      body->cb()); xmlWriter.writeCharacters(string);
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::RowCount: {
//      xmlWriter.writeStartElement("RowCount");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();

//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      quint32 val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::ColumnCount: {
//      xmlWriter.writeStartElement("ColumnCount");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();

//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      quint32 val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val));
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::TableBordersVisible: {
//      xmlWriter.writeStartElement("TableBordersVisible");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }

//      //    case PropertyIDs::StructureElementChildNodes:
//      //      m_id_string = "StructureElementChildNodes";
//      //      break;
//      //    case PropertyIDs::ChildGraphSpaceElementNodes:
//      //      m_id_string = "ChildGraphSpaceElementNodes";
//      //      break;
//    case PropertyIDs::TableColumnWidths: {
//      xmlWriter.writeStartElement("TableColumnWidths");
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      quint8 cColumns;
//      bytes >> cColumns;

//      xmlWriter.writeAttribute("cColumns", QString::number(cColumns));

//      xmlWriter.writeCharacters("{");
//      for (quint8 j = 0; j < cColumns; j++) {
//        float width;
//        bytes >> width;
//        xmlWriter.writeCharacters(QString::number(width, 'f', 5));

//        if (j + 1 != cColumns) {
//          xmlWriter.writeCharacters(", ");
//        }
//      }
//      xmlWriter.writeCharacters("}");
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::Author: {
//      xmlWriter.writeStartElement("Author");
//      const auto body = std::dynamic_pointer_cast<
//          PropertyType_FourBytesOfLengthFollowedByData>(currentData);
//      QString string = QString::fromUtf16(
//          reinterpret_cast<const ushort*>(body->data().constData()));

//      xmlWriter.writeCharacters(string);
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::LastModifiedTimeStamp: {
//      xmlWriter.writeStartElement("LastModifiedTimeStamp");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_EightBytesOfData>(currentData)
//              ->data();

//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      libmson::FileTime time;
//      bytes >> time;
//      writeFileTime(time, xmlWriter);
//      xmlWriter.writeEndElement();
//      break;
//    }
//      //      ObjectID:
//      //    case PropertyIDs::AuthorOriginal:

//      //      ObjectID:
//      //    case PropertyIDs::AuthorMostRecent:

//    case PropertyIDs::LastModifiedTime: {
//      xmlWriter.writeStartElement("LastModifiedTime");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();

//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      libmson::Time32 time;
//      bytes >> time;
//      writeTime32(time, xmlWriter);
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::IsConflictPage: {
//      xmlWriter.writeStartElement("IsConflictPage");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }

//    /// \todo test TableColumnsLocked whether it produces correct output
//    case PropertyIDs::TableColumnsLocked: {
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();

//      quint8 cColumns = data.at(0);
//      quint8 nbytes   = data.size() - 1;

//      xmlWriter.writeStartElement("TableColumnsLocked");
//      xmlWriter.writeAttribute("cColumns", QString::number(cColumns));

//      xmlWriter.writeStartElement("rgfColumnLocked");
//      xmlWriter.writeCharacters("{");
//      quint8 kColumns = 0;
//      for (quint8 j = 1; j < nbytes; j++) {
//        quint8 chunk = data.at(j);
//        for (size_t k = 0; k < 8; k++) {
//          xmlWriter.writeCharacters(QString::number(((chunk >> k) & 0x1)));
//          kColumns++;

//          if (j + 1 != cColumns) {
//            xmlWriter.writeCharacters(", ");
//          }
//          else {
//            break;
//          }
//        }
//      }
//      xmlWriter.writeCharacters("}");
//      xmlWriter.writeEndElement();

//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::SchemaRevisionInOrderToRead: {
//      xmlWriter.writeStartElement("SchemaRevisionInOrderToRead");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      quint32 val;
//      bytes >> val;
//      xmlWriter.writeCharacters(qStringHex(val, 8));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::IsConflictObjectForRender: {
//      xmlWriter.writeStartElement("IsConflictObjectForRender");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//      //    case PropertyIDs::EmbeddedFileContainer:
//      //      m_id_string = "EmbeddedFileContainer";
//      //      break;
//    case PropertyIDs::EmbeddedFileName: {
//      xmlWriter.writeStartElement("EmbeddedFileName");
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();
//      QString string = QString::fromUtf16(
//          reinterpret_cast<const ushort*>(data.constData()), data.size() /
//          2);

//      xmlWriter.writeCharacters(string);
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::SourceFilepath: {
//      xmlWriter.writeStartElement("SourceFilepath");
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();
//      QString string = QString::fromUtf16(
//          reinterpret_cast<const ushort*>(data.constData()), data.size() /
//          2);

//      xmlWriter.writeCharacters(string);
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::ConflictingUserName: {
//      xmlWriter.writeStartElement("ConflictingUserName");
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();
//      QString string = QString::fromUtf8(data.constData(), data.size());
//      xmlWriter.writeCharacters(string);
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::ImageFilename: {
//      xmlWriter.writeStartElement("ImageFilename");
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();
//      QString string = QString::fromUtf16(
//          reinterpret_cast<const ushort*>(data.constData()), data.size() /
//          2);

//      xmlWriter.writeCharacters(string);
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::IsConflictObjectForSelection: {
//      xmlWriter.writeStartElement("IsConflictObjectForSelection");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::PageLevel: {
//      xmlWriter.writeStartElement("PageLevel");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      qint32 val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::TextRunIndex: {
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);

//      QString indices = "";
//      while (!bytes.atEnd()) {
//        quint32 val;
//        bytes >> val;

//        indices += QString::number(val) + ", ";
//      }
//      // remove last ", " characters
//      indices.resize(indices.size() - 2);

//      xmlWriter.writeStartElement("TextRunIndex");
//      xmlWriter.writeCharacters("{");
//      xmlWriter.writeCharacters(indices);
//      xmlWriter.writeCharacters("}");
//      xmlWriter.writeEndElement();
//      break;
//    }
//      //    case PropertyIDs::TextRunFormatting:
//      //      m_id_string = "TextRunFormatting";
//      //      break;
//    case PropertyIDs::Hyperlink: {
//      xmlWriter.writeStartElement("Hyperlink");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::UnderlineType: {
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_OneByteOfData>(currentData)
//              ->data();
//      quint8 val = data.toUInt();
//      xmlWriter.writeStartElement("UnderlineType");
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::Hidden: {
//      xmlWriter.writeStartElement("Hidden");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::HyperlinkProtected: {
//      xmlWriter.writeStartElement("HyperlinkProtected");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::TextRunIsEmbeddedObject: {
//      xmlWriter.writeStartElement("TextRunIsEmbeddedObject");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::ImageAltText: {
//      xmlWriter.writeStartElement("ImageAltText");
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();
//      QString string =
//          QString::fromUtf16(reinterpret_cast<const
//          ushort*>(data.constData()));

//      xmlWriter.writeCharacters(string);
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::MathFormatting: {
//      xmlWriter.writeStartElement("MathFormatting");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//      //    case PropertyIDs::ParagraphStyle: {
//      //      break;
//      //    }
//    case PropertyIDs::ParagraphSpaceBefore: {
//      xmlWriter.writeStartElement("ParagraphSpaceBefore");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::ParagraphSpaceAfter: {
//      xmlWriter.writeStartElement("ParagraphSpaceBefore");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::ParagraphLineSpacingExact: {
//      xmlWriter.writeStartElement("ParagraphLineSpacingExact");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }
//      //          case PropertyIDs::MetaDataObjectsAboveGraphSpace: {

//      ////        QUuid salt ( 0x22a8c031, 0x3600, 0x42ee, 0xb7, 0x14, 0xd7,
//      /// 0xac, 0xda, 0x24, 0x35, 0xe8);

//      //            break;
//      //      }
//      //    case PropertyIDs::TextRunDataObject:
//      //      m_id_string = "TextRunDataObject";
//      //      break;
//      //    case PropertyIDs::TextRunData:
//      //      m_id_string = "TextRunData";
//      //      break;
//    case PropertyIDs::ParagraphStyleId: {
//      xmlWriter.writeStartElement("ParagraphStyleId");
//      if (currentPrid.type() ==
//          PropertyIDType::FourBytesOfLengthFollowedByData) {
//        const auto data =
//            std::dynamic_pointer_cast<
//                PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//                ->data();
//        QString string = QString::fromUtf8(data.constData(), data.size());
//        xmlWriter.writeCharacters(string);
//      }
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::HasVersionPages: {
//      xmlWriter.writeStartElement("HasVersionPages");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::ActionItemType: {

//      if (currentPrid.type() ==
//          PropertyIDType::FourBytesOfLengthFollowedByData) {
//        const auto data =
//            std::dynamic_pointer_cast<PropertyType_TwoBytesOfData>(currentData)
//                ->data();
//        QDataStream ds(data);
//        quint16 val;
//        ds >> val;

//        xmlWriter.writeStartElement("ActionItemType");
//        xmlWriter.writeAttribute("val", QString::number(val));

//        if (val < 100) {
//          xmlWriter.writeCharacters("Tag: " + QString::number(val));
//        }
//        else {
//          switch (val) {
//          case 100:
//            xmlWriter.writeCharacters("Due today");
//            break;
//          case 101:
//            xmlWriter.writeCharacters("Due tomorrow");
//            break;
//          case 102:
//            xmlWriter.writeCharacters("Due this week");
//            break;
//          case 103:
//            xmlWriter.writeCharacters("Due next week");
//            break;
//          case 104:
//            xmlWriter.writeCharacters("No due date");
//            break;
//          case 105:
//            xmlWriter.writeCharacters("Due on a custom date");
//            break;
//          }
//        }
//        xmlWriter.writeEndElement();
//        break;
//      }
//    case PropertyIDs::NoteTagShape: {
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_TwoBytesOfData>(currentData)
//              ->data();

//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      libmson::NoteTagShape shape;
//      bytes >> shape;
//      writeNoteTagShape(shape, xmlWriter);
//      break;
//    }
//    case PropertyIDs::NoteTagHighlightColor: {
//      xmlWriter.writeStartElement("NoteTagHighlightColor");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      libmson::ColorRef val;
//      bytes >> val;
//      writeColorRef(val, xmlWriter);
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::NoteTagTextColor: {
//      xmlWriter.writeStartElement("NoteTagTextColor");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      libmson::ColorRef val;
//      bytes >> val;
//      writeColorRef(val, xmlWriter);
//      xmlWriter.writeEndElement();
//      break;
//    }

//    /// \todo use proper BitReader
//    case PropertyIDs::NoteTagPropertyStatus: {
//      xmlWriter.writeStartElement("NoteTagPropertyStatus");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      quint32 val;
//      bytes >> val;

//      xmlWriter.writeStartElement("hasLabel");
//      xmlWriter.writeCharacters((val & 0x1) == 1 ? "True" : "False");
//      xmlWriter.writeEndElement();
//      xmlWriter.writeStartElement("hasFontColor");
//      xmlWriter.writeCharacters(((val >> 1) & 0x1) == 1 ? "True" : "False");
//      xmlWriter.writeEndElement();
//      xmlWriter.writeStartElement("hasHighlightColor");
//      xmlWriter.writeCharacters(((val >> 2) & 0x1) == 1 ? "True" : "False");
//      xmlWriter.writeEndElement();
//      xmlWriter.writeStartElement("hasIcon");
//      xmlWriter.writeCharacters(((val >> 3) & 0x1) == 1 ? "True" : "False");
//      xmlWriter.writeEndElement();
//      xmlWriter.writeStartElement("DueToday");
//      xmlWriter.writeCharacters(((val >> 6) & 0x1) == 1 ? "True" : "False");
//      xmlWriter.writeEndElement();
//      xmlWriter.writeStartElement("DueTomorrow");
//      xmlWriter.writeCharacters(((val >> 7) & 0x1) == 1 ? "True" : "False");
//      xmlWriter.writeEndElement();
//      xmlWriter.writeStartElement("DueThisWeek");
//      xmlWriter.writeCharacters(((val >> 8) & 0x1) == 1 ? "True" : "False");
//      xmlWriter.writeEndElement();
//      xmlWriter.writeStartElement("DueNextWeek");
//      xmlWriter.writeCharacters(((val >> 9) & 0x1) == 1 ? "True" : "False");
//      xmlWriter.writeEndElement();
//      xmlWriter.writeStartElement("DueLater");
//      xmlWriter.writeCharacters(((val >> 10) & 0x1) == 1 ? "True" :
//      "False"); xmlWriter.writeEndElement();
//      xmlWriter.writeStartElement("DueCustom");
//      xmlWriter.writeCharacters(((val >> 11) & 0x1) == 1 ? "True" :
//      "False"); xmlWriter.writeEndElement();

//      xmlWriter.writeEndElement();
//      break;
//    }

//    /// \todo not sure whether this is the correct string format
//    (utf8/utf16) case PropertyIDs::NoteTagLabel: {
//      xmlWriter.writeStartElement("wz");
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();
//      QString string = QString::fromUtf8(data.constData(), data.size());
//      xmlWriter.writeCharacters(string);
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::NoteTagCreated: {
//      xmlWriter.writeStartElement("NoteTagCreated");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();

//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      libmson::Time32 time;
//      bytes >> time;
//      writeTime32(time, xmlWriter);
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::NoteTagCompleted: {
//      xmlWriter.writeStartElement("NoteTagCompleted");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();

//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      libmson::Time32 time;
//      bytes >> time;
//      writeTime32(time, xmlWriter);
//      xmlWriter.writeEndElement();
//      break;
//    }
//      //    case PropertyIDs::NoteTagDefinitionOid:
//      //      m_id_string = "NoteTagDefinitionOid";
//      //      break;
//      //    case PropertyIDs::NoteTagStates:
//      //      m_id_string = "NoteTagStates";
//      //      break;
//    case PropertyIDs::ActionItemStatus: {
//      xmlWriter.writeStartElement("ActionItemStatus");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_TwoBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      quint16 val;
//      bytes >> val;

//      xmlWriter.writeStartElement("Completed");
//      xmlWriter.writeCharacters((val & 0x1) == 1 ? "True" : "False");
//      xmlWriter.writeEndElement();
//      xmlWriter.writeStartElement("Disabled");
//      xmlWriter.writeCharacters(((val >> 1) & 0x1) == 1 ? "True" : "False");
//      xmlWriter.writeEndElement();
//      xmlWriter.writeStartElement("TaskTag");
//      xmlWriter.writeCharacters(((val >> 2) & 0x1) == 1 ? "True" : "False");
//      xmlWriter.writeEndElement();
//      xmlWriter.writeStartElement("Unsynchronized");
//      xmlWriter.writeCharacters(((val >> 3) & 0x1) == 1 ? "True" : "False");
//      xmlWriter.writeEndElement();
//      xmlWriter.writeStartElement("Removed");
//      xmlWriter.writeCharacters(((val >> 4) & 0x1) == 1 ? "True" : "False");
//      xmlWriter.writeEndElement();

//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::ActionItemSchemaVersion: {
//      xmlWriter.writeStartElement("ActionItemSchemaVersion");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_OneByteOfData>(currentData)
//              ->data();
//      xmlWriter.writeCharacters("0x" + data.toHex());
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::ReadingOrderRTL: {
//      xmlWriter.writeStartElement("ReadingOrderRTL");

//      int val = currentPrid.boolValue();
//      xmlWriter.writeCharacters(
//          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
//      xmlWriter.writeEndElement();
//      break;
//    }
//      /// \todo declare ParagraphAlignment Enum
//    case PropertyIDs::ParagraphAlignment: {

//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_OneByteOfData>(currentData)
//              ->data();

//      QString align;

//      switch (data.toUInt()) {
//      case 0:
//        align = "Left";
//        break;
//      case 1:
//        align = "Center";
//        break;
//      case 2:
//        align = "Right";
//        break;

//      default:
//        align = "invalid";
//        break;
//      }
//      xmlWriter.writeStartElement("ParagraphAlignment");
//      xmlWriter.writeCharacters(align);
//      xmlWriter.writeEndElement();

//      break;
//    }
//      //    case PropertyIDs::VersionHistoryGraphSpaceContextNodes:
//      //      m_id_string = "VersionHistoryGraphSpaceContextNodes";
//      //      break;

//    case PropertyIDs::DisplayedPageNumber: {
//      xmlWriter.writeStartElement("DisplayedPageNumber");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      quint32 val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::SectionDisplayName: {
//      xmlWriter.writeStartElement("wz");
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();
//      QString string = QString::fromUtf8(data.constData(), data.size());
//      xmlWriter.writeCharacters(string);
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::NextStyle: {
//      xmlWriter.writeStartElement("wz");
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();
//      QString string = QString::fromUtf8(data.constData(), data.size());
//      xmlWriter.writeCharacters(string);
//      xmlWriter.writeEndElement();
//      break;
//    }
//      //    case PropertyIDs::WebPictureContainer14:
//      //      m_id_string = "WebPictureContainer14";
//      //      break;
//    case PropertyIDs::ImageUploadState: {

//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_OneByteOfData>(currentData)
//              ->data();

//      QString state;
//      switch (data.toUInt()) {
//      case 0:
//        state = "Upload complete";
//        break;
//      case 1:
//        state = "Upload in progress";
//        break;
//      case 2:
//        state = "Upload failed";
//        break;

//      default:
//        state = "Invalid Upload state";
//        break;
//      }
//      xmlWriter.writeStartElement("ImageUploadState");
//      xmlWriter.writeCharacters(state);
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::TextExtendedAscii: {
//      xmlWriter.writeStartElement("String");
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();
//      QString string = QString::fromUtf8(data.constData(), data.size());
//      xmlWriter.writeCharacters(string);
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::PictureWidth: {
//      xmlWriter.writeStartElement("PictureWidth");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::PictureHeight: {
//      xmlWriter.writeStartElement("PictureHeight");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::PageMarginOriginX: {
//      xmlWriter.writeStartElement("PageMarginOriginX");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::PageMarginOriginY: {
//      xmlWriter.writeStartElement("PageMarginOriginY");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::WzHyperlinkUrl: {
//      xmlWriter.writeStartElement("wz");
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();
//      QString string = QString::fromUtf8(data.constData(), data.size());
//      xmlWriter.writeCharacters(string);
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::TaskTagDueDate: {
//      xmlWriter.writeStartElement("TaskTagDueDate");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();

//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      libmson::Time32 time;
//      bytes >> time;
//      writeTime32(time, xmlWriter);
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::undoc_AuthorInitials: {
//      xmlWriter.writeStartElement("undoc_AuthorInitials");
//      if (currentPrid.type() ==
//          PropertyIDType::FourBytesOfLengthFollowedByData) {
//        const auto data =
//            std::dynamic_pointer_cast<
//                PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//                ->data();
//        QString string = QString::fromUtf8(data.constData(), data.size());
//        xmlWriter.writeCharacters(string);
//      }
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::undoc_ResolutionID: {
//      xmlWriter.writeStartElement("undoc_ResolutionID");
//      if (currentPrid.type() ==
//          PropertyIDType::FourBytesOfLengthFollowedByData) {
//        const auto data =
//            std::dynamic_pointer_cast<
//                PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//                ->data();
//        QString string = QString::fromUtf8(data.constData(), data.size());
//        xmlWriter.writeCharacters(string);
//      }
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::undoc_StrokesBlob: {
//      xmlWriter.writeStartElement("undoc_StrokesBlob");
//      writeIPropertyType(currentData, xmlWriter);
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::undoc_StrokesIndex: {
//      xmlWriter.writeStartElement("undoc_StrokesIndex");
//      if (currentPrid.type() == PropertyIDType::FourBytesOfData) {
//        const auto data =
//            std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//                ->data();
//        QDataStream bytes(data);
//        bytes.setByteOrder(QDataStream::LittleEndian);
//        bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//        uint32_t val;
//        bytes >> val;
//        xmlWriter.writeCharacters(QString::number(val));
//      }
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::unodc_StrokeLanguage: {
//      xmlWriter.writeStartElement("unodc_StrokeLanguage");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_TwoBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      quint16 val;
//      bytes >> val;
//      xmlWriter.writeCharacters(libmson::LCID::languageIDtoString(
//          static_cast<libmson::LanguageID>(val)));
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::undoc_StrokesColor: {
//      xmlWriter.writeStartElement("undoc_StrokesColor");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();

//      xmlWriter.writeCharacters("#" + data.toHex());
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::undoc_StrokesToolSizeHeight: {
//      xmlWriter.writeStartElement("undoc_StrokesToolSizeHeight");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }
//    case PropertyIDs::undoc_StrokesToolSizeWidth: {
//      xmlWriter.writeStartElement("undoc_StrokesToolSizeWidth");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float val;
//      bytes >> val;
//      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::undoc_StrokesCreationTime: {
//      xmlWriter.writeStartElement("undoc_StrokesCreationTime");
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();

//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      libmson::FileTime time;
//      bytes >> time;
//      writeFileTime(time, xmlWriter);
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::undoc_StrokesRecognizedText: {
//      xmlWriter.writeStartElement("undoc_StrokesRecognizedText");
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();

//      QString string = QString::fromUtf16(
//          reinterpret_cast<const ushort*>(data.constData()), data.size() /
//          2);
//      QStringList strings = string.split('\0');
//      for (const auto& str : strings) {
//        if (str.size() > 0) {
//          xmlWriter.writeStartElement("match");
//          xmlWriter.writeCharacters(str);
//          xmlWriter.writeEndElement();
//        }
//      }
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::undoc_StrokesOffsetsVertHoriz: {
//      xmlWriter.writeStartElement("undoc_StrokesOffsetsVertHoriz");
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
//      float vert, horiz;
//      bytes >> vert;
//      bytes >> horiz;

//      xmlWriter.writeStartElement("Vert");
//      xmlWriter.writeCharacters(QString::number(vert, 'f', 5));
//      xmlWriter.writeEndElement();
//      xmlWriter.writeStartElement("Horiz");
//      xmlWriter.writeCharacters(QString::number(horiz, 'f', 5));
//      xmlWriter.writeEndElement();

//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::undoc_StrokesModus: {
//      xmlWriter.writeStartElement("undoc_StrokesModus");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_OneByteOfData>(currentData)
//              ->data();
//      switch (data.toInt()) {
//      case 0:
//        xmlWriter.writeCharacters("HandwrittingAndDrawing");
//        break;
//      case 1:
//        xmlWriter.writeCharacters("DrawingOnly");
//        break;
//      case 2:
//        xmlWriter.writeCharacters("HandwritingOnly");
//        break;
//      default:
//        break;
//      }

//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::undoc_StrokesGUID: {
//      xmlWriter.writeStartElement("undoc_StrokesGUID");
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      QUuid guid;
//      bytes >> guid;

//      xmlWriter.writeCharacters(guid.toString());
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::undoc_RecognizedText: {
//      xmlWriter.writeStartElement("undoc_RecognizedText");
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();

//      QString string = QString::fromUtf16(
//          reinterpret_cast<const ushort*>(data.constData()), data.size() /
//          2);
//      QStringList strings = string.split('\0');
//      for (const auto& str : strings) {
//        if (str.size() > 0) {
//          xmlWriter.writeStartElement("match");
//          xmlWriter.writeCharacters(str);
//          xmlWriter.writeEndElement();
//        }
//      }
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::undoc_tocSectionName: {
//      xmlWriter.writeStartElement("undoc_tocSectionName");
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();

//      QString string = QString::fromUtf16(
//          reinterpret_cast<const ushort*>(data.constData()), data.size() /
//          2);

//      xmlWriter.writeCharacters(string);
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::undoc_tocSectionIndex: {
//      xmlWriter.writeStartElement("undoc_tocSectionIndex");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      quint32 val;
//      bytes >> val;

//      xmlWriter.writeCharacters(QString::number(val));
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::undoc_tocSectionGUID: {
//      xmlWriter.writeStartElement("undoc_tocSectionGUID");
//      const auto data =
//          std::dynamic_pointer_cast<
//              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      QUuid val;
//      bytes >> val;
//      xmlWriter.writeCharacters(val.toString());
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::undoc_tocSectionColor: {
//      xmlWriter.writeStartElement("undoc_tocSectionColor");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      libmson::ColorRef val;
//      bytes >> val;
//      writeColorRef(val, xmlWriter);
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::undoc_SchemaRevisionInOrderToRead: {
//      xmlWriter.writeStartElement("undoc_SchemaRevisionInOrderToRead");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();
//      QDataStream bytes(data);
//      bytes.setByteOrder(QDataStream::LittleEndian);
//      quint32 val;
//      bytes >> val;
//      xmlWriter.writeCharacters(qStringHex(val, 8));
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::undoc_PageBackgroundColor: {
//      xmlWriter.writeStartElement("undoc_PageBackgroundColor");
//      const auto data =
//          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
//              ->data();

//      xmlWriter.writeCharacters("#" + data.toHex());
//      xmlWriter.writeEndElement();
//      break;
//    }

//    case PropertyIDs::None:
//    default:
//      writeIPropertyType(currentData, xmlWriter);
//      break;
//    }
//    }
//    xmlWriter.writeEndElement(); // PropertyID
//  }

//  xmlWriter.writeEndElement();

//  return xmlWriter;
//}

// QXmlStreamWriter& PSFtoXml::writePropertyType_ArrayNumber(
//    const std::shared_ptr<PropertyType_ArrayNumber>& obj,
//    QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeStartElement("ArrayNumber");
//  xmlWriter.writeAttribute("cCID", QString::number(obj->cCIDs()));

//  xmlWriter.writeEndElement();

//  return xmlWriter;
//}

// QXmlStreamWriter& PSFtoXml::writePropertyType_ArrayOfPropertyValues(
//    const std::shared_ptr<PropertyType_ArrayOfPropertyValues>& obj,
//    QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeStartElement("ArrayOfPropertyValues");
//  xmlWriter.writeAttribute(
//      "m_cProperties", QString::number(obj->cProperties()));
//  writePropertyID(obj->prid(), xmlWriter);

//  xmlWriter.writeStartElement("PropertySets");
//  for (const auto& entry : obj->data()) {
//    writePropertySet(entry, xmlWriter);
//  }
//  xmlWriter.writeEndElement();

//  xmlWriter.writeEndElement();

//  return xmlWriter;
//}

// QXmlStreamWriter& PSFtoXml::writePropertyType_Bool(QXmlStreamWriter&
// xmlWriter)
//{
//  xmlWriter.writeEmptyElement("Bool");
//  // no data
//  /// \todo get info from PropertySet

//  return xmlWriter;
//}

// QXmlStreamWriter& PSFtoXml::writePropertyType_ContextID(
//    const std::shared_ptr<PropertyType_ContextID>& obj,
//    QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeStartElement("ContextID");

//  writeCompactID(obj->data(), xmlWriter);

//  xmlWriter.writeEndElement();

//  return xmlWriter;
//}

// QXmlStreamWriter& PSFtoXml::writePropertyType_EightBytesOfData(
//    const std::shared_ptr<PropertyType_EightBytesOfData>& obj,
//    QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeStartElement("EightBytesOfData");

//  xmlWriter.writeCharacters(obj->data().toHex());

//  xmlWriter.writeEndElement();

//  return xmlWriter;
//}

// QXmlStreamWriter& PSFtoXml::writePropertyType_FourBytesOfData(
//    const std::shared_ptr<PropertyType_FourBytesOfData>& obj,
//    QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeStartElement("FourBytesOfData");

//  xmlWriter.writeCharacters(obj->data().toHex());

//  xmlWriter.writeEndElement();

//  return xmlWriter;
//}

// QXmlStreamWriter&
// PSFtoXml::writePropertyType_FourBytesOfLengthFollowedByData(
//    const std::shared_ptr<PropertyType_FourBytesOfLengthFollowedByData>&
//    obj, QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeStartElement("FourBytesOfLengthFollowedByData");

//  xmlWriter.writeAttribute("cb", QString::number(obj->cb()));
//  xmlWriter.writeCharacters(obj->data().toHex());

//  xmlWriter.writeEndElement();

//  return xmlWriter;
//}

// QXmlStreamWriter&
// PSFtoXml::writePropertyType_NoData(QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeEmptyElement("NoData");
//  return xmlWriter;
//}

// QXmlStreamWriter& PSFtoXml::writePropertyType_ObjectID(
//    const std::shared_ptr<PropertyType_ObjectID>& obj,
//    QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeStartElement("ObjectID");

//  writeCompactID(obj->data(), xmlWriter);

//  xmlWriter.writeEndElement();

//  return xmlWriter;
//}

// QXmlStreamWriter&
// PSFtoXml::writePropertyType_ObjectSpaceID(QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeEmptyElement("ObjectSpaceID");
//  // no data
//  /// \todo get info from PropertySet

//  return xmlWriter;
//}

// QXmlStreamWriter& PSFtoXml::writePropertyType_OneByteOfData(
//    const std::shared_ptr<PropertyType_OneByteOfData>& obj,
//    QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeStartElement("OneByteOfData");
//  xmlWriter.writeCharacters(obj->data().toHex());
//  xmlWriter.writeEndElement();

//  return xmlWriter;
//}

// QXmlStreamWriter& PSFtoXml::writePropertyType_PropertySet(
//    const std::shared_ptr<PropertyType_PropertySet>& obj,
//    QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeStartElement("PropertySet");
//  writePropertySet(obj->data(), xmlWriter);
//  xmlWriter.writeEndElement();

//  return xmlWriter;
//}

// QXmlStreamWriter& PSFtoXml::writePropertyType_TwoBytesOfData(
//    const std::shared_ptr<PropertyType_TwoBytesOfData>& obj,
//    QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeStartElement("TwoBytesOfData");
//  xmlWriter.writeCharacters(obj->data().toHex());
//  xmlWriter.writeEndElement();

//  return xmlWriter;
//}


//// MS-ONE stuff
/*--------------------------------------------------------------------------*/
/* simple types */
/*--------------------------------------------------------------------------*/


// QXmlStreamWriter& PSFtoXml::writeBodyTextAlignment(
//    const libmson::BodyTextAlignment& obj, QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeStartElement("BodyTextAlignment");
//  xmlWriter.writeCharacters(QString::number(obj.getValue()));
//  xmlWriter.writeEndElement();

//  return xmlWriter;
//}


// QXmlStreamWriter& PSFtoXml::writeFileTime(
//    const libmson::FileTime& obj, QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeStartElement("FILETIME");
//  xmlWriter.writeCharacters(obj.getTime().toString("dd/MM/yyyy hh:mm:ss
//  AP")); xmlWriter.writeEndElement();

//  return xmlWriter;
//}

// QXmlStreamWriter& PSFtoXml::writeLayoutAlignment(
//    const libmson::LayoutAlignment& obj, QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeStartElement("LayoutAlignment");
//  xmlWriter.writeAttribute(
//      "horizontal",
//      libmson::LayoutAlignment::hAlignmentToString(obj.getHAlignment()));
//  xmlWriter.writeAttribute(
//      "vertial",
//      libmson::LayoutAlignment::vAlignmentToString(obj.getVAlignment()));
//  xmlWriter.writeAttribute("hMargin", obj.getFHorizMargin() ? "true" :
//  "false"); xmlWriter.writeAttribute("vMargin", obj.getFVertMargin() ?
//  "true" : "false"); xmlWriter.writeAttribute("valid", !obj.isNil() ? "true"
//  : "false"); xmlWriter.writeEndElement();

//  return xmlWriter;
//}

// QXmlStreamWriter&
// PSFtoXml::writeLCID(const libmson::LCID& obj, QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeStartElement("LCID");
//  xmlWriter.writeAttribute("SortID", qStringHex(obj.getSortID(), 4));
//  xmlWriter.writeCharacters(obj.languageIDtoString());
//  xmlWriter.writeEndElement();

//  return xmlWriter;
//}

// QXmlStreamWriter& PSFtoXml::writeListMSAAIndex(
//    const libmson::ListMSAAIndex& obj, QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeStartElement("ListMSAAIndex");
//  xmlWriter.writeCharacters(libmson::ListMSAAIndex::IDtoString(obj.getID()));
//  xmlWriter.writeEndElement();

//  return xmlWriter;
//}

// QXmlStreamWriter& PSFtoXml::writeNoteTagShape(
//    const libmson::NoteTagShape& obj, QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeStartElement("NoteTagShape");
//  xmlWriter.writeCharacters(
//      libmson::NoteTagShape::idToString(obj.getShapeID()));
//  xmlWriter.writeEndElement();

//  return xmlWriter;
//}

// QXmlStreamWriter& PSFtoXml::writePageSize(
//    const libmson::PageSize& obj, QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeStartElement("PageSize");
//  xmlWriter.writeCharacters(libmson::PageSize::typeToString(obj.getPageType()));
//  xmlWriter.writeEndElement();

//  return xmlWriter;
//}

// QXmlStreamWriter&
// PSFtoXml::writeTime32(const libmson::Time32& obj, QXmlStreamWriter&
// xmlWriter)
//{
//  xmlWriter.writeStartElement("Time32");
//  xmlWriter.writeCharacters(obj.getTime().toString("dd/MM/yyyy hh:mm:ss
//  AP")); xmlWriter.writeEndElement();

//  return xmlWriter;
//}

/*--------------------------------------------------------------------------*/
/* complex types */
/*--------------------------------------------------------------------------*/
// QXmlStreamWriter& PSFtoXml::writeColorRef(
//    const libmson::ColorRef& obj, QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeStartElement("COLORREF");
//  xmlWriter.writeCharacters(qStringHex(obj.getColorRef(), 8));
//  xmlWriter.writeEndElement();

//  return xmlWriter;
//}

// QXmlStreamWriter& PSFtoXml::writeFcr64orChunk(
//    const Chunkable_SPtr_t& chunk, bool followRecursively, FCR_INIT init,
//    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
//    QXmlStreamWriter& xmlWriter)
//{
//  if (followRecursively) {
//    if (chunk == nullptr) {
//      if (init == FCR_INIT::NIL) {
//        xmlWriter.writeEmptyElement("Nil");
//      }
//      else {
//        xmlWriter.writeEmptyElement("None");
//      }
//      return xmlWriter;
//    }

//    return writeChunkable(
//        chunk, followRecursively, revisionStoreFile, xmlWriter);
//  }

//  auto ref = getFcr64FromChunk(revisionStoreFile, chunk, init);
//  return writeFileChunkReference64(ref, xmlWriter);
//}


// QXmlStreamWriter& PSFtoXml::writeFcr64x32orChunk(
//    const Chunkable_SPtr_t& chunk, bool followRecursively, FCR_INIT init,
//    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
//    QXmlStreamWriter& xmlWriter)
//{
//  if (followRecursively) {
//    if (chunk == nullptr) {
//      if (init == FCR_INIT::NIL) {
//        xmlWriter.writeEmptyElement("Nil");
//      }
//      else {
//        xmlWriter.writeEmptyElement("None");
//      }
//      return xmlWriter;
//    }

//    return writeChunkable(
//        chunk, followRecursively, revisionStoreFile, xmlWriter);
//  }

//  auto ref = getFcr64x32FromChunk(revisionStoreFile, chunk, init);
//  return writeFileChunkReference64x32(ref, xmlWriter);
//}


// QXmlStreamWriter& PSFtoXml::writeFncrOrChunk(
//    const Chunkable_SPtr_t& chunk, bool followRecursively,
//    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat, FCR_INIT init,

//    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
//    QXmlStreamWriter& xmlWriter)
//{
//  if (followRecursively) {
//    if (chunk == nullptr) {
//      if (init == FCR_INIT::NIL) {
//        xmlWriter.writeEmptyElement("Nil");
//      }
//      else {
//        xmlWriter.writeEmptyElement("None");
//      }
//      return xmlWriter;
//    }

//    return writeChunkable(
//        chunk, followRecursively, revisionStoreFile, xmlWriter);
//  }

//  auto ref =
//      getFncrFromChunk(revisionStoreFile, chunk, stpFormat, cbFormat, init);
//  return writeFileNodeChunkReference(ref, xmlWriter);
//}
