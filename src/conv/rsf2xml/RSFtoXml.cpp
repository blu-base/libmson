#include "RSFtoXml.h"

#include "../../lib/priv/utils/ChunkableUtils.h"
#include "../../lib/priv/utils/Helper.h"

#include <QDataStream>
#include <QDebug>
#include <QXmlStreamWriter>

#include <memory>


bool RSFtoXml::writeRSFTree(
    QFile& outputFile,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile)
{
  if (!outputFile.open(QIODevice::WriteOnly)) {
    qInfo() << "Couldn't open file: " << outputFile.fileName();
    return false;
  }
  QXmlStreamWriter xmlWriter(&outputFile);
  xmlWriter.setAutoFormatting(true);


  xmlWriter.writeStartDocument();

  xmlWriter.writeStartElement("RevisionstoreFile");
  writeRevisionStoreFileHeader(revisionStoreFile, true, xmlWriter);

  xmlWriter.writeEndElement();
  xmlWriter.writeEndDocument();

  outputFile.close();

  return true;
}

bool RSFtoXml::writeRSFSequence(
    QFile& outputFile,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile)
{
  if (!outputFile.open(QIODevice::WriteOnly)) {
    qInfo() << "Couldn't open file: " << outputFile.fileName();
    return false;
  }
  QXmlStreamWriter xmlWriter(&outputFile);
  xmlWriter.setAutoFormatting(true);
  xmlWriter.writeStartDocument();

  xmlWriter.writeStartElement("RevisionstoreFile");
  writeRevisionStoreFileHeader(revisionStoreFile, false, xmlWriter);

  for (const auto& chunk : revisionStoreFile->getChunks()) {
    writeChunkable(chunk, false, revisionStoreFile, xmlWriter);
  }

  xmlWriter.writeEndElement();
  xmlWriter.writeEndDocument();

  outputFile.close();

  return true;
}


QXmlStreamWriter& RSFtoXml::writeChunkable(
    const Chunkable_SPtr_t& chunk, const bool followRecursively,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeComment(
      "Chunkable stp: " +
      qStringHex(stpFromChunk(revisionStoreFile, chunk), 16) +
      " cb: " + qStringHex(chunk->getSizeInFile(), 16));

  switch (chunk->type()) {
  case RevisionStoreChunkType::EncryptedData: {
    writeEncryptedData(
        std::static_pointer_cast<EncryptedData>(chunk), xmlWriter);
    break;
  }
  case RevisionStoreChunkType::FileDataStoreObject: {
    writeFileDataStoreObject(
        std::static_pointer_cast<FileDataStoreObject>(chunk), xmlWriter);
    break;
  }
  case RevisionStoreChunkType::FileNode: {
    writeFileNode(
        std::static_pointer_cast<FileNode>(chunk), followRecursively,
        revisionStoreFile, xmlWriter);
    break;
  }
  case RevisionStoreChunkType::FileNodeListFragment: {
    writeFileNodeListFragment(
        std::static_pointer_cast<FileNodeListFragment>(chunk),
        followRecursively, revisionStoreFile, xmlWriter);
    break;
  }
  case RevisionStoreChunkType::FreeChunk: {
    writeFreeChunk(xmlWriter);
    break;
  }
  case RevisionStoreChunkType::FreeChunkListFragment: {
    writeFreeChunkListFragment(
        std::static_pointer_cast<FreeChunkListFragment>(chunk),
        followRecursively, revisionStoreFile, xmlWriter);
    break;
  }
  case RevisionStoreChunkType::ObjectInfoDependencyOverrideData: {
    writeObjectInfoDependencyOverrideData(
        std::static_pointer_cast<ObjectInfoDependencyOverrideData>(chunk),
        xmlWriter);
    break;
  }
  case RevisionStoreChunkType::ObjectSpaceObjectPropSet: {
    writeObjectSpaceObjectPropSet(
        std::static_pointer_cast<ObjectSpaceObjectPropSet>(chunk), xmlWriter);
    break;
  }
  case RevisionStoreChunkType::TransactionLogFragment: {
    writeTransactionLogFragment(
        std::static_pointer_cast<TransactionLogFragment>(chunk),
        followRecursively, revisionStoreFile, xmlWriter);
    break;
  }
  case RevisionStoreChunkType::UnknownBlob: {
    writeUnknownBlob(std::static_pointer_cast<UnknownBlob>(chunk), xmlWriter);
    break;
  }
  default:
    break;
  }

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeRevisionStoreFileHeader(
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    const bool followRecursively, QXmlStreamWriter& xmlWriter)
{

  const auto& header = revisionStoreFile->getHeader();

  xmlWriter.writeStartElement("Header");

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

  xmlWriter.writeStartElement("ffvLastWriterVersion");
  xmlWriter.writeCharacters(QString::number(header->getFfvLastWriterVersion()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("ffvOldestWriterVersion");
  xmlWriter.writeCharacters(
      QString::number(header->getFfvOldestWriterVersion()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("ffvNewestWriterVersion");
  xmlWriter.writeCharacters(
      QString::number(header->getFfvNewestWriterVersion()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("ffvOldestReader");
  xmlWriter.writeCharacters(QString::number(header->getFfvOldestReader()));
  xmlWriter.writeEndElement();

  // skipping fcrLegacyFreeChunkList
  // skipping fcrLegacyTransactionLog


  xmlWriter.writeStartElement("cTransactionsInLog");
  xmlWriter.writeCharacters(QString::number(header->getCTransactionsInLog()));
  xmlWriter.writeEndElement();

  // skipping cbLegacyExpectedFileLength


  xmlWriter.writeStartElement("rgbPlaceholder");
  xmlWriter.writeCharacters(QString::number(header->getRgbPlaceholder()));
  xmlWriter.writeEndElement();

  // skipping fcrLegacyFileNodeListRoot
  // skipping cbLegacyFreeSpaceInFreeChunkList


  xmlWriter.writeStartElement("fNeedsDefrag");
  xmlWriter.writeCharacters(QString::number(header->getFNeedsDefrag()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fRepairedFile");
  xmlWriter.writeCharacters(QString::number(header->getFRepairedFile()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fNeedsGarbageCollect");
  xmlWriter.writeCharacters(QString::number(header->getFNeedsGarbageCollect()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fHasNoEmbeddedFileObjects");
  xmlWriter.writeCharacters(
      QString::number(header->getFHasNoEmbeddedFileObjects()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("guidAncestor");
  xmlWriter.writeCharacters(header->getGuidAncestor().toString());
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("crcName");
  xmlWriter.writeCharacters(qStringHex(header->getCrcName(), 8));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fcrHashedChunkList");
  writeFcr64x32orChunk(
      header->getFcrHashedChunkList().lock(), followRecursively, FCR_INIT::NIL,
      revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fcrTransactionLog");
  writeFcr64x32orChunk(
      header->getFcrTransactionLog().lock(), followRecursively, FCR_INIT::NIL,
      revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fcrFileNodeListRoot");
  writeFcr64x32orChunk(
      header->getFcrFileNodeListRoot().lock(), followRecursively, FCR_INIT::NIL,
      revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fcrFreeChunkList");
  writeFcr64x32orChunk(
      header->getFcrFreeChunkList().lock(), followRecursively, FCR_INIT::NIL,
      revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("cbExpectedFileLength");
  xmlWriter.writeCharacters(qStringHex(header->getCbExpectedFileLength(), 16));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("cbFreeSpaceInFreeChunkList");
  xmlWriter.writeCharacters(
      qStringHex(header->getCbFreeSpaceInFreeChunkList(), 16));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("guidFileVersion");
  xmlWriter.writeCharacters(header->getGuidFileVersion().toString());
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("nFileVersionGeneration");
  xmlWriter.writeCharacters(
      QString::number(header->getNFileVersionGeneration()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("guidDenyReadFileVersion");
  xmlWriter.writeCharacters(header->getGuidDenyReadFileVersion().toString());
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("grfDebugLogFlags");
  xmlWriter.writeCharacters(QString::number(header->getGrfDebugLogFlags()));
  xmlWriter.writeEndElement();

  // skipping fcrDebugLog
  // skipping fcrAllocVerificationFreeChunkList

  xmlWriter.writeStartElement("bnCreated");
  xmlWriter.writeCharacters(qStringHex(header->getBnCreated(), 8));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("bnLastWroteToThisFile");
  xmlWriter.writeCharacters(qStringHex(header->getBnLastWroteToThisFile(), 8));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("bnOldestWritten");
  xmlWriter.writeCharacters(qStringHex(header->getBnOldestWritten(), 8));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("bnNewestWritten");
  xmlWriter.writeCharacters(qStringHex(header->getBnNewestWritten(), 8));
  xmlWriter.writeEndElement();

  // skipping reserved section

  xmlWriter.writeEndElement(); // Header

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeEncryptedData(
    const std::shared_ptr<EncryptedData>& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("EncryptedData");

  xmlWriter.writeComment("Header: " + QString::number(obj->header, 16));

  xmlWriter.writeStartElement("Data");
  xmlWriter.writeCharacters(obj->getData().toHex());
  xmlWriter.writeEndElement();

  xmlWriter.writeComment("Footer: " + QString::number(obj->footer, 16));

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeFileDataStoreObject(
    const std::shared_ptr<FileDataStoreObject>& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("FileDataStoreObject");

  xmlWriter.writeComment("Header: " + obj->guidHeader.toString());

  xmlWriter.writeStartElement("cbLength");
  xmlWriter.writeCharacters(QString::number(obj->getCbLength()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("Data");
  xmlWriter.writeCharacters(obj->getFileData().toHex());
  xmlWriter.writeEndElement();

  xmlWriter.writeComment("Footer: " + obj->guidFooter.toString());

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeFileNode(
    const std::shared_ptr<FileNode>& fileNode, const bool followRecursively,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("FileNode");

  xmlWriter.writeAttribute(
      "fileNodeID", qStringHex(fileNode->getFileNodeID(), 3));
  xmlWriter.writeAttribute(
      "fileNodeSize", qStringHex(fileNode->getFileNodeSize(), 4));
  xmlWriter.writeAttribute(
      "stpFormat", QString::number(fileNode->getStpFormat()));
  xmlWriter.writeAttribute(
      "cbFormat", QString::number(fileNode->getCbFormat()));
  xmlWriter.writeAttribute("baseType", qStringHex(fileNode->getBaseType(), 2));

  xmlWriter.writeComment(
      "stp: " + qStringHex(stpFromChunk(revisionStoreFile, fileNode), 16));

  writeIFileNodeType(
      fileNode->getFnt(), followRecursively, fileNode, revisionStoreFile,
      xmlWriter);

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeFileNodeListFragment(
    const std::shared_ptr<FileNodeListFragment>& fnlFragment,
    const bool followRecursively,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("FileNodeListFragment");
  xmlWriter.writeAttribute(
      "fileNodeListID", QString::number(fnlFragment->getFileNodeListID()));
  xmlWriter.writeAttribute(
      "nFragmentSequence",
      QString::number(fnlFragment->getNFragmentSequence()));


  xmlWriter.writeStartElement("rgFileNodes");
  for (const auto& entry : fnlFragment->getFileNodes()) {

    writeFileNode(entry, followRecursively, revisionStoreFile, xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("paddingLength");
  xmlWriter.writeCharacters(qStringHex(fnlFragment->getPaddingLength(), 16));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("nextFragment");
  writeFcr64x32orChunk(
      fnlFragment->getNextFragment().lock(), followRecursively, FCR_INIT::NIL,
      revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeFreeChunk(QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeEmptyElement("FreeChunk");

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeFreeChunkListFragment(
    const std::shared_ptr<FreeChunkListFragment>& obj,
    const bool followRecursively,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("FreeChunkListFragment");

  xmlWriter.writeStartElement("crc");
  xmlWriter.writeCharacters(QString::number(obj->getCrc(), 16));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fcrNextChunk");
  writeFcr64x32orChunk(
      obj->getFcrNextFragment().lock(), followRecursively, FCR_INIT::NIL,
      revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fcrFreeChunks");
  for (const auto& entry : obj->getFcrFreeChunks()) {
    writeFcr64orChunk(
        entry.lock(), followRecursively, FCR_INIT::NIL, revisionStoreFile,
        xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectInfoDependencyOverrideData(
    const std::shared_ptr<ObjectInfoDependencyOverrideData>& obj,
    QXmlStreamWriter& xmlWriter)
{
  writeObjectInfoDependencyOverrideData(*obj, xmlWriter);

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectInfoDependencyOverrideData(
    const ObjectInfoDependencyOverrideData& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectInfoDependencyOverrideData");

  xmlWriter.writeStartElement("c8BitOverrides");
  xmlWriter.writeCharacters(QString::number(obj.getC8BitOverrides()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("c32BitOverrides");
  xmlWriter.writeCharacters(QString::number(obj.getC32BitOverrides()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("crc");
  xmlWriter.writeCharacters(QString::number(obj.getCrc(), 16));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("Overrides1");
  for (const auto& entry : obj.getOverrides1()) {
    writeObjectInfoDependencyOverride8(entry, xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("Overrides2");
  for (const auto& entry : obj.getOverrides2()) {
    writeObjectInfoDependencyOverride32(entry, xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectSpaceObjectPropSet(
    const std::shared_ptr<ObjectSpaceObjectPropSet>& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectSpaceObjectPropSet");

  xmlWriter.writeStartElement("OIDs");
  writeObjectSpaceObjectStreamOfOIDs(obj->getOIDs(), xmlWriter);
  xmlWriter.writeEndElement();

  if (obj->getOIDs().getHeader().isOsidStreamNotPresent() == false) {
    xmlWriter.writeStartElement("OSIDs");
    writeObjectSpaceObjectStreamOfOSIDs(obj->getOSIDs(), xmlWriter);
    xmlWriter.writeEndElement();

    if (obj->getOSIDs().getHeader().isExtendedStreamPresent() == true) {
      xmlWriter.writeStartElement("OIDs");
      writeObjectSpaceObjectStreamOfContextIDs(obj->getContextIDs(), xmlWriter);
      xmlWriter.writeEndElement();
    }
  }


  xmlWriter.writeStartElement("body");
  writePropertySet(obj->getBody(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("PaddingLength");
  xmlWriter.writeCharacters(QString::number(obj->getPaddingLength()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeTransactionLogFragment(
    const std::shared_ptr<TransactionLogFragment>& obj,
    const bool followRecursively,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("TransactionLogFragment");

  xmlWriter.writeStartElement("TransactionEntries");
  xmlWriter.writeAttribute(
      "count", QString::number(obj->getSizeTable().size()));
  for (const auto& entry : obj->getSizeTable()) {
    if (!entry->isZero()) {
      xmlWriter.writeStartElement("TransactionEntry");

      xmlWriter.writeAttribute("size", qStringHex(entry->getSrcID(), 8));
      xmlWriter.writeAttribute(
          "TransactionEntrySwitch",
          qStringHex(entry->getTransactionEntrySwitch(), 8));

      xmlWriter.writeEndElement();
    }
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("nextFragment");
  writeFcr64x32orChunk(
      obj->getNextFragment().lock(), followRecursively, FCR_INIT::NIL,
      revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeUnknownBlob(
    const std::shared_ptr<UnknownBlob>& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("UnknownBlob");
  xmlWriter.writeStartElement("Data");
  xmlWriter.writeCharacters(obj->getBlob().toHex());
  xmlWriter.writeEndElement();
  xmlWriter.writeEndElement();

  return xmlWriter;
}


// -----------------------------------------------------------------------------
// file node types
// -----------------------------------------------------------------------------

QXmlStreamWriter& RSFtoXml::writeIFileNodeType(
    const IFileNodeType_SPtr_t& obj, const bool followRecursively,
    const FileNode_SPtr_t& parent,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{

  switch (obj->getType()) {

  case FileNodeTypeID::ChunkTerminatorFND: {
    writeChunkTerminatorFND(xmlWriter);
    break;
  }

  case FileNodeTypeID::DataSignatureGroupDefinitionFND: {
    writeDataSignatureGroupDefinitionFND(
        std::static_pointer_cast<DataSignatureGroupDefinitionFND>(obj),
        xmlWriter);
    break;
  }

  case FileNodeTypeID::FileDataStoreListReferenceFND: {
    writeFileDataStoreListReferenceFND(
        std::static_pointer_cast<FileDataStoreListReferenceFND>(obj),
        followRecursively, parent, revisionStoreFile, xmlWriter);
    break;
  }

  case FileNodeTypeID::FileDataStoreObjectReferenceFND: {
    writeFileDataStoreObjectReferenceFND(
        std::static_pointer_cast<FileDataStoreObjectReferenceFND>(obj),
        followRecursively, parent, revisionStoreFile, xmlWriter);
    break;
  }

  case FileNodeTypeID::GlobalIdTableEndFNDX: {
    writeGlobalIdTableEndFNDX(xmlWriter);
    break;
  }

  case FileNodeTypeID::GlobalIdTableEntry2FNDX: {
    writeGlobalIdTableEntry2FNDX(
        std::static_pointer_cast<GlobalIdTableEntry2FNDX>(obj), xmlWriter);
    break;
  }

  case FileNodeTypeID::GlobalIdTableEntry3FNDX: {
    writeGlobalIdTableEntry3FNDX(
        std::static_pointer_cast<GlobalIdTableEntry3FNDX>(obj), xmlWriter);
    break;
  }

  case FileNodeTypeID::GlobalIdTableEntryFNDX: {
    writeGlobalIdTableEntryFNDX(
        std::static_pointer_cast<GlobalIdTableEntryFNDX>(obj), xmlWriter);
    break;
  }

  case FileNodeTypeID::GlobalIdTableStart2FND: {
    writeGlobalIdTableStart2FND(xmlWriter);
    break;
  }

  case FileNodeTypeID::GlobalIdTableStartFNDX: {
    writeGlobalIdTableStartFNDX(
        std::static_pointer_cast<GlobalIdTableStartFNDX>(obj), xmlWriter);
    break;
  }

  case FileNodeTypeID::HashedChunkDescriptor2FND: {
    writeHashedChunkDescriptor2FND(
        std::static_pointer_cast<HashedChunkDescriptor2FND>(obj),
        followRecursively, parent, revisionStoreFile, xmlWriter);
    break;
  }


  case FileNodeTypeID::ObjectDataEncryptionKeyV2FNDX: {
    writeObjectDataEncryptionKeyV2FNDX(
        std::static_pointer_cast<ObjectDataEncryptionKeyV2FNDX>(obj),
        followRecursively, parent, revisionStoreFile, xmlWriter);
    break;
  }

  case FileNodeTypeID::ObjectDeclaration2LargeRefCountFND: {
    writeObjectDeclaration2LargeRefCountFND(
        std::static_pointer_cast<ObjectDeclaration2LargeRefCountFND>(obj),
        followRecursively, parent, revisionStoreFile, xmlWriter);
    break;
  }

  case FileNodeTypeID::ObjectDeclaration2RefCountFND: {
    writeObjectDeclaration2RefCountFND(
        std::static_pointer_cast<ObjectDeclaration2RefCountFND>(obj),
        followRecursively, parent, revisionStoreFile, xmlWriter);
    break;
  }

  case FileNodeTypeID::ObjectDeclarationFileData3LargeRefCountFND: {
    writeObjectDeclarationFileData3LargeRefCountFND(
        std::static_pointer_cast<ObjectDeclarationFileData3LargeRefCountFND>(
            obj),
        xmlWriter);
    break;
  }

  case FileNodeTypeID::ObjectDeclarationFileData3RefCountFND: {
    writeObjectDeclarationFileData3RefCountFND(
        std::static_pointer_cast<ObjectDeclarationFileData3RefCountFND>(obj),
        xmlWriter);
    break;
  }

  case FileNodeTypeID::ObjectDeclarationWithRefCount2FNDX: {
    writeObjectDeclarationWithRefCount2FNDX(
        std::static_pointer_cast<ObjectDeclarationWithRefCount2FNDX>(obj),
        followRecursively, parent, revisionStoreFile, xmlWriter);
    break;
  }

  case FileNodeTypeID::ObjectDeclarationWithRefCountFNDX: {
    writeObjectDeclarationWithRefCountFNDX(
        std::static_pointer_cast<ObjectDeclarationWithRefCountFNDX>(obj),
        followRecursively, parent, revisionStoreFile, xmlWriter);
    break;
  }

  case FileNodeTypeID::ObjectGroupEndFND: {
    writeObjectGroupEndFND(xmlWriter);
    break;
  }

  case FileNodeTypeID::ObjectGroupListReferenceFND: {
    writeObjectGroupListReferenceFND(
        std::static_pointer_cast<ObjectGroupListReferenceFND>(obj),
        followRecursively, parent, revisionStoreFile, xmlWriter);
    break;
  }

  case FileNodeTypeID::ObjectGroupStartFND: {
    writeObjectGroupStartFND(
        std::static_pointer_cast<ObjectGroupStartFND>(obj), xmlWriter);
    break;
  }

  case FileNodeTypeID::ObjectInfoDependencyOverridesFND: {
    writeObjectInfoDependencyOverridesFND(
        std::static_pointer_cast<ObjectInfoDependencyOverridesFND>(obj),
        followRecursively, parent, revisionStoreFile, xmlWriter);
    break;
  }

  case FileNodeTypeID::ObjectRevisionWithRefCount2FNDX: {
    writeObjectRevisionWithRefCount2FNDX(
        std::static_pointer_cast<ObjectRevisionWithRefCount2FNDX>(obj),
        followRecursively, parent, revisionStoreFile, xmlWriter);
    break;
  }

  case FileNodeTypeID::ObjectRevisionWithRefCountFNDX: {
    writeObjectRevisionWithRefCountFNDX(
        std::static_pointer_cast<ObjectRevisionWithRefCountFNDX>(obj),
        followRecursively, parent, revisionStoreFile, xmlWriter);
    break;
  }

  case FileNodeTypeID::ObjectSpaceManifestListReferenceFND: {
    writeObjectSpaceManifestListReferenceFND(
        std::static_pointer_cast<ObjectSpaceManifestListReferenceFND>(obj),
        followRecursively, parent, revisionStoreFile, xmlWriter);
    break;
  }

  case FileNodeTypeID::ObjectSpaceManifestListStartFND: {
    writeObjectSpaceManifestListStartFND(
        std::static_pointer_cast<ObjectSpaceManifestListStartFND>(obj),
        xmlWriter);
    break;
  }

  case FileNodeTypeID::ObjectSpaceManifestRootFND: {
    writeObjectSpaceManifestRootFND(
        std::static_pointer_cast<ObjectSpaceManifestRootFND>(obj), xmlWriter);
    break;
  }

  case FileNodeTypeID::ReadOnlyObjectDeclaration2LargeRefCountFND: {
    writeReadOnlyObjectDeclaration2LargeRefCountFND(
        std::static_pointer_cast<ReadOnlyObjectDeclaration2LargeRefCountFND>(
            obj),
        followRecursively, parent, revisionStoreFile, xmlWriter);
    break;
  }

  case FileNodeTypeID::ReadOnlyObjectDeclaration2RefCountFND: {
    writeReadOnlyObjectDeclaration2RefCountFND(
        std::static_pointer_cast<ReadOnlyObjectDeclaration2RefCountFND>(obj),
        followRecursively, parent, revisionStoreFile, xmlWriter);
    break;
  }

  case FileNodeTypeID::RevisionManifestEndFND: {
    writeRevisionManifestEndFND(xmlWriter);
    break;
  }

  case FileNodeTypeID::RevisionManifestListReferenceFND: {
    writeRevisionManifestListReferenceFND(
        std::static_pointer_cast<RevisionManifestListReferenceFND>(obj),
        followRecursively, parent, revisionStoreFile, xmlWriter);
    break;
  }

  case FileNodeTypeID::RevisionManifestListStartFND: {
    writeRevisionManifestListStartFND(
        std::static_pointer_cast<RevisionManifestListStartFND>(obj), xmlWriter);
    break;
  }

  case FileNodeTypeID::RevisionManifestStart4FND: {
    writeRevisionManifestStart4FND(
        std::static_pointer_cast<RevisionManifestStart4FND>(obj), xmlWriter);
    break;
  }

  case FileNodeTypeID::RevisionManifestStart6FND: {
    writeRevisionManifestStart6FND(
        std::static_pointer_cast<RevisionManifestStart6FND>(obj), xmlWriter);
    break;
  }

  case FileNodeTypeID::RevisionManifestStart7FND: {
    writeRevisionManifestStart7FND(
        std::static_pointer_cast<RevisionManifestStart7FND>(obj), xmlWriter);
    break;
  }

  case FileNodeTypeID::RevisionRoleAndContextDeclarationFND: {
    writeRevisionRoleAndContextDeclarationFND(
        std::static_pointer_cast<RevisionRoleAndContextDeclarationFND>(obj),
        xmlWriter);
    break;
  }

  case FileNodeTypeID::RevisionRoleDeclarationFND: {
    writeRevisionRoleDeclarationFND(
        std::static_pointer_cast<RevisionRoleDeclarationFND>(obj), xmlWriter);
    break;
  }

  case FileNodeTypeID::RootObjectReference2FNDX: {
    writeRootObjectReference2FNDX(
        std::static_pointer_cast<RootObjectReference2FNDX>(obj), xmlWriter);
    break;
  }

  case FileNodeTypeID::RootObjectReference3FND: {
    writeRootObjectReference3FND(
        std::static_pointer_cast<RootObjectReference3FND>(obj), xmlWriter);
    break;
  }


  default: {
    xmlWriter.writeEmptyElement("NoData");
    break;
  }
  }

  return xmlWriter;
}

// -----------------------------------------------------------------------------

QXmlStreamWriter& RSFtoXml::writeChunkTerminatorFND(QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeEmptyElement("ChunkTerminatorFND");
  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeDataSignatureGroupDefinitionFND(
    const DataSignatureGroupDefinitionFND_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("DataSignatureGroupDefinitionFND");
  xmlWriter.writeStartElement("dataSignatureGroup");
  writeExtendedGUID(obj->getDataSignatureGroup(), xmlWriter);
  xmlWriter.writeEndElement();
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeFileDataStoreListReferenceFND(
    const FileDataStoreListReferenceFND_SPtr_t& obj,
    const bool followRecursively, const FileNode_SPtr_t& parent,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("FileDataStoreListReferenceFND");

  xmlWriter.writeStartElement("ref");
  writeFncrOrChunk(
      obj->getRef().lock(), followRecursively, parent->getStpFormatEnum(),
      parent->getCbFormatEnum(), FCR_INIT::NIL, revisionStoreFile, xmlWriter);

  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeFileDataStoreObjectReferenceFND(
    const FileDataStoreObjectReferenceFND_SPtr_t& obj,
    const bool followRecursively, const FileNode_SPtr_t& parent,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("FileDataStoreObjectReferenceFND");

  xmlWriter.writeStartElement("blobRef");
  writeFncrOrChunk(
      obj->getBlobRef().lock(), followRecursively, parent->getStpFormatEnum(),
      parent->getCbFormatEnum(), FCR_INIT::NIL, revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("guidReference");
  writeGUID(obj->getGuidReference(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}


QXmlStreamWriter&
RSFtoXml::writeGlobalIdTableEndFNDX(QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeEmptyElement("GlobalIdTableEndFNDX");
  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeGlobalIdTableEntry2FNDX(
    const GlobalIdTableEntry2FNDX_SPtr_t& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("GlobalIdTableEntry2FNDX");

  xmlWriter.writeStartElement("iIndexMapFrom");
  xmlWriter.writeCharacters(QString::number(obj->getIIndexMapFrom()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("iIndexMapTo");
  xmlWriter.writeCharacters(QString::number(obj->getIIndexMapTo()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeGlobalIdTableEntry3FNDX(
    const GlobalIdTableEntry3FNDX_SPtr_t& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("GlobalIdTableEntry3FNDX");

  xmlWriter.writeStartElement("iIndexCopyFromStart");
  xmlWriter.writeCharacters(QString::number(obj->getIIndexCopyFromStart()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("cEntriesToCopy");
  xmlWriter.writeCharacters(QString::number(obj->getCEntriesToCopy()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("iIndexCopyToStart");
  xmlWriter.writeCharacters(QString::number(obj->getIIndexCopyToStart()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeGlobalIdTableEntryFNDX(
    const GlobalIdTableEntryFNDX_SPtr_t& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("GlobalIdTableEntryFNDX");

  xmlWriter.writeStartElement("index");
  xmlWriter.writeCharacters(QString::number(obj->getIndex()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("guid");
  writeGUID(obj->getGuid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter&
RSFtoXml::writeGlobalIdTableStart2FND(QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeEmptyElement("GlobalIdTableStart2FND");
  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeGlobalIdTableStartFNDX(
    const GlobalIdTableStartFNDX_SPtr_t& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("GlobalIdTableStartFNDX");
  xmlWriter.writeAttribute("reserved", QString::number(obj->getReserved()));
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeHashedChunkDescriptor2FND(
    const HashedChunkDescriptor2FND_SPtr_t& obj, const bool followRecursively,
    const FileNode_SPtr_t& parent,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("HashedChunkDescriptor2FND");


  xmlWriter.writeStartElement("blobRef");
  writeFncrOrChunk(
      obj->getBlobRef().lock(), followRecursively, parent->getStpFormatEnum(),
      parent->getCbFormatEnum(), FCR_INIT::NIL, revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("guidHash");
  xmlWriter.writeCharacters(obj->getGuidHash().toHex());
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}


QXmlStreamWriter& RSFtoXml::writeObjectDataEncryptionKeyV2FNDX(
    const ObjectDataEncryptionKeyV2FNDX_SPtr_t& obj,
    const bool followRecursively, const FileNode_SPtr_t& parent,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectDataEncryptionKeyV2FNDX");

  xmlWriter.writeStartElement("ref");
  writeFncrOrChunk(
      obj->getBlobRef().lock(), followRecursively, parent->getStpFormatEnum(),
      parent->getCbFormatEnum(), FCR_INIT::NIL, revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectDeclaration2LargeRefCountFND(
    const ObjectDeclaration2LargeRefCountFND_SPtr_t& obj,
    const bool followRecursively, const FileNode_SPtr_t& parent,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectDeclaration2LargeRefCountFND");

  xmlWriter.writeStartElement("blobRef");
  writeFncrOrChunk(
      obj->getBlobRef().lock(), followRecursively, parent->getStpFormatEnum(),
      parent->getCbFormatEnum(), FCR_INIT::NIL, revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("body");
  writeObjectDeclaration2Body(obj->getBody(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("cRef");
  xmlWriter.writeCharacters(QString::number(obj->getCRef()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectDeclaration2RefCountFND(
    const ObjectDeclaration2RefCountFND_SPtr_t& obj,
    const bool followRecursively, const FileNode_SPtr_t& parent,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectDeclaration2RefCountFND");

  xmlWriter.writeStartElement("blobRef");
  writeFncrOrChunk(
      obj->getBlobRef().lock(), followRecursively, parent->getStpFormatEnum(),
      parent->getCbFormatEnum(), FCR_INIT::NIL, revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("body");
  writeObjectDeclaration2Body(obj->getBody(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("cRef");
  xmlWriter.writeCharacters(QString::number(obj->getCRef()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectDeclarationFileData3LargeRefCountFND(
    const ObjectDeclarationFileData3LargeRefCountFND_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectDeclarationFileData3LargeRefCountFND");

  xmlWriter.writeStartElement("oid");
  writeCompactID(obj->getOid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("jcid");
  writeJCID(obj->getJcid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("cRef");
  xmlWriter.writeCharacters(QString::number(obj->getCRef()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("FileDataReference");
  writeStringInStorageBuffer(obj->getFileDataReference(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("Extension");
  writeStringInStorageBuffer(obj->getExtension(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectDeclarationFileData3RefCountFND(
    const ObjectDeclarationFileData3RefCountFND_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectDeclarationFileData3RefCountFND");

  xmlWriter.writeStartElement("oid");
  writeCompactID(obj->getOid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("jcid");
  writeJCID(obj->getJcid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("cRef");
  xmlWriter.writeCharacters(QString::number(obj->getCRef()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("FileDataReference");
  writeStringInStorageBuffer(obj->getFileDataReference(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("Extension");
  writeStringInStorageBuffer(obj->getExtension(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectDeclarationWithRefCount2FNDX(
    const ObjectDeclarationWithRefCount2FNDX_SPtr_t& obj,
    const bool followRecursively, const FileNode_SPtr_t& parent,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectDeclarationWithRefCount2FNDX");

  xmlWriter.writeStartElement("ObjectRef");
  writeFncrOrChunk(
      obj->getObjectRef().lock(), followRecursively, parent->getStpFormatEnum(),
      parent->getCbFormatEnum(), FCR_INIT::NIL, revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("body");
  writeObjectDeclarationWithRefCountBody(obj->getBody(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("cRef");
  xmlWriter.writeCharacters(QString::number(obj->getCRef()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectDeclarationWithRefCountFNDX(
    const ObjectDeclarationWithRefCountFNDX_SPtr_t& obj,
    const bool followRecursively, const FileNode_SPtr_t& parent,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectDeclarationWithRefCountFNDX");

  xmlWriter.writeStartElement("ObjectRef");
  writeFncrOrChunk(
      obj->getObjectRef().lock(), followRecursively, parent->getStpFormatEnum(),
      parent->getCbFormatEnum(), FCR_INIT::NIL, revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("body");
  writeObjectDeclarationWithRefCountBody(obj->getBody(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("cRef");
  xmlWriter.writeCharacters(QString::number(obj->getCRef()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectGroupEndFND(QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeEmptyElement("ObjectGroupEndFND");
  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectGroupListReferenceFND(
    const ObjectGroupListReferenceFND_SPtr_t& obj, const bool followRecursively,
    const FileNode_SPtr_t& parent,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectGroupListReferenceFND");

  xmlWriter.writeStartElement("ref");
  writeFncrOrChunk(
      obj->getRef().lock(), followRecursively, parent->getStpFormatEnum(),
      parent->getCbFormatEnum(), FCR_INIT::NIL, revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("ObjectGroupID");
  writeExtendedGUID(obj->getObjectGroupID(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectGroupStartFND(
    const ObjectGroupStartFND_SPtr_t& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectGroupStartFND");

  xmlWriter.writeStartElement("ObjectGroupID");
  writeExtendedGUID(obj->getOid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectInfoDependencyOverridesFND(
    const ObjectInfoDependencyOverridesFND_SPtr_t& obj,
    const bool followRecursively, const FileNode_SPtr_t& parent,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectInfoDependencyOverridesFND");

  xmlWriter.writeStartElement("ref");
  writeFncrOrChunk(
      obj->getRef().lock(), followRecursively, parent->getStpFormatEnum(),
      parent->getCbFormatEnum(), FCR_INIT::NIL, revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  if (!(obj->getRef().lock() == nullptr)) {
    xmlWriter.writeStartElement("data");
    writeObjectInfoDependencyOverrideData(obj->getData(), xmlWriter);
    xmlWriter.writeEndElement();
  }

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectRevisionWithRefCount2FNDX(
    const ObjectRevisionWithRefCount2FNDX_SPtr_t& obj,
    const bool followRecursively, const FileNode_SPtr_t& parent,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectRevisionWithRefCount2FNDX");

  xmlWriter.writeStartElement("ref");
  writeFncrOrChunk(
      obj->getRef().lock(), followRecursively, parent->getStpFormatEnum(),
      parent->getCbFormatEnum(), FCR_INIT::NIL, revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("oid");
  writeCompactID(obj->getOid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fHasOidReferences");
  xmlWriter.writeCharacters(obj->getFHasOidReferences() ? "True" : "False");
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fHasOsidReferences");
  xmlWriter.writeCharacters(obj->getFHasOsidReferences() ? "True" : "False");
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("cRef");
  xmlWriter.writeCharacters(QString::number(obj->getCRef()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectRevisionWithRefCountFNDX(
    const ObjectRevisionWithRefCountFNDX_SPtr_t& obj,
    const bool followRecursively, const FileNode_SPtr_t& parent,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectRevisionWithRefCountFNDX");

  xmlWriter.writeStartElement("ref");
  writeFncrOrChunk(
      obj->getRef().lock(), followRecursively, parent->getStpFormatEnum(),
      parent->getCbFormatEnum(), FCR_INIT::NIL, revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("oid");
  writeCompactID(obj->getOid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fHasOidReferences");
  xmlWriter.writeCharacters(obj->getFHasOidReferences() ? "True" : "False");
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fHasOsidReferences");
  xmlWriter.writeCharacters(obj->getFHasOsidReferences() ? "True" : "False");
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("cRef");
  xmlWriter.writeCharacters(QString::number(obj->getCRef()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectSpaceManifestListReferenceFND(
    const ObjectSpaceManifestListReferenceFND_SPtr_t& obj,
    const bool followRecursively, const FileNode_SPtr_t& parent,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectSpaceManifestListReferenceFND");
  xmlWriter.writeStartElement("ref");
  writeFncrOrChunk(
      obj->getRef().lock(), followRecursively, parent->getStpFormatEnum(),
      parent->getCbFormatEnum(), FCR_INIT::NIL, revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("gosid");
  writeExtendedGUID(obj->getGosid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectSpaceManifestListStartFND(
    const ObjectSpaceManifestListStartFND_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectSpaceManifestListStartFND");

  xmlWriter.writeStartElement("gosid");
  writeExtendedGUID(obj->getGosid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectSpaceManifestRootFND(
    const ObjectSpaceManifestRootFND_SPtr_t& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectSpaceManifestRootFND");
  xmlWriter.writeStartElement("gosidRoot");
  writeExtendedGUID(obj->getGosidRoot(), xmlWriter);
  xmlWriter.writeEndElement();
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeReadOnlyObjectDeclaration2LargeRefCountFND(
    const ReadOnlyObjectDeclaration2LargeRefCountFND_SPtr_t& obj,
    const bool followRecursively, const FileNode_SPtr_t& parent,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ReadOnlyObjectDeclaration2LargeRefCountFND");

  xmlWriter.writeStartElement("blobRef");
  writeFncrOrChunk(
      obj->getBlobRef().lock(), followRecursively, parent->getStpFormatEnum(),
      parent->getCbFormatEnum(), FCR_INIT::NIL, revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("body");
  writeObjectDeclaration2Body(obj->getBody(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("cRef");
  xmlWriter.writeCharacters(QString::number(obj->getCRef()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("md5Hash");
  xmlWriter.writeCharacters(obj->getMd5hash().toHex());
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeReadOnlyObjectDeclaration2RefCountFND(
    const ReadOnlyObjectDeclaration2RefCountFND_SPtr_t& obj,
    const bool followRecursively, const FileNode_SPtr_t& parent,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ReadOnlyObjectDeclaration2RefCountFND");

  xmlWriter.writeStartElement("blobRef");
  writeFncrOrChunk(
      obj->getBlobRef().lock(), followRecursively, parent->getStpFormatEnum(),
      parent->getCbFormatEnum(), FCR_INIT::NIL, revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("body");
  writeObjectDeclaration2Body(obj->getBody(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("cRef");
  xmlWriter.writeCharacters(QString::number(obj->getCRef()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("md5Hash");
  xmlWriter.writeCharacters(obj->getMd5hash().toHex());
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter&
RSFtoXml::writeRevisionManifestEndFND(QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeEmptyElement("RevisionManifestEndFND");
  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeRevisionManifestListReferenceFND(
    const RevisionManifestListReferenceFND_SPtr_t& obj,
    const bool followRecursively, const FileNode_SPtr_t& parent,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("RevisionManifestListReferenceFND");
  xmlWriter.writeStartElement("ref");
  writeFncrOrChunk(
      obj->getRef().lock(), followRecursively, parent->getStpFormatEnum(),
      parent->getCbFormatEnum(), FCR_INIT::NIL, revisionStoreFile, xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeRevisionManifestListStartFND(
    const RevisionManifestListStartFND_SPtr_t& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("RevisionManifestListStartFND");

  xmlWriter.writeStartElement("gosid");
  writeExtendedGUID(obj->getGosid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("nInstance");
  xmlWriter.writeCharacters(QString::number(obj->getNInstance()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeRevisionManifestStart4FND(
    const RevisionManifestStart4FND_SPtr_t& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("RevisionManifestStart4FND");

  xmlWriter.writeStartElement("rid");
  writeExtendedGUID(obj->getRid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("ridDependent");
  writeExtendedGUID(obj->getRidDependent(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("timeCreation");
  xmlWriter.writeCharacters(QString::number(obj->getTimeCreation()));
  xmlWriter.writeEndElement();


  /// \todo remove comment when format timeCreation is determined(documented in
  /// RevisionManifestStart4FND header and alikes)
  xmlWriter.writeComment(
      "FileTime: " +
      libmson::FileTime(
          obj->getTimeCreation() >> 32, obj->getTimeCreation() & UINT32_MAX)
          .getTime()
          .toString());

  xmlWriter.writeStartElement("RevisionRole");
  xmlWriter.writeCharacters(QString::number(obj->getRevisionRole()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("odcsDefault");
  xmlWriter.writeCharacters(QString::number(obj->getOdcsDefault()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeRevisionManifestStart6FND(
    const RevisionManifestStart6FND_SPtr_t& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("RevisionManifestStart6FND");

  xmlWriter.writeStartElement("rid");
  writeExtendedGUID(obj->getRid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("ridDependent");
  writeExtendedGUID(obj->getRidDependent(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("RevisionRole");
  xmlWriter.writeCharacters(QString::number(obj->getRevisionRole()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("odcsDefault");
  xmlWriter.writeCharacters(QString::number(obj->getOdcsDefault()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeRevisionManifestStart7FND(
    const RevisionManifestStart7FND_SPtr_t& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("RevisionManifestStart7FND");

  xmlWriter.writeStartElement("rid");
  writeExtendedGUID(obj->getRid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("ridDependent");
  writeExtendedGUID(obj->getRidDependent(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("RevisionRole");
  xmlWriter.writeCharacters(QString::number(obj->getRevisionRole()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("odcsDefault");
  xmlWriter.writeCharacters(QString::number(obj->getOdcsDefault()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("gctxid");
  writeExtendedGUID(obj->getGctxid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeRevisionRoleAndContextDeclarationFND(
    const RevisionRoleAndContextDeclarationFND_SPtr_t& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("RevisionRoleAndContextDeclarationFND");

  xmlWriter.writeStartElement("rid");
  writeExtendedGUID(obj->getRid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("RevisionRole");
  xmlWriter.writeCharacters(QString::number(obj->getRevisionRole()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("gctxid");
  writeExtendedGUID(obj->getGctxid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeRevisionRoleDeclarationFND(
    const RevisionRoleDeclarationFND_SPtr_t& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("RevisionRoleDeclarationFND");

  xmlWriter.writeStartElement("rid");
  writeExtendedGUID(obj->getRid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("RevisionRole");
  xmlWriter.writeCharacters(QString::number(obj->getRevisionRole()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeRootObjectReference2FNDX(
    const RootObjectReference2FNDX_SPtr_t& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("RootObjectReference2FNDX");

  xmlWriter.writeStartElement("oidRoot");
  writeCompactID(obj->getOidRoot(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("RootRole");
  xmlWriter.writeCharacters(QString::number(obj->getRootRole()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeRootObjectReference3FND(
    const RootObjectReference3FND_SPtr_t& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("RootObjectReference3FND");

  xmlWriter.writeStartElement("oidRoot");
  writeExtendedGUID(obj->getOidRoot(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("RootRole");
  xmlWriter.writeCharacters(QString::number(obj->getRootRole()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

// -----------------------------------------------------------------------------
// object Types
// -----------------------------------------------------------------------------
QXmlStreamWriter& RSFtoXml::writeIObjectSpaceObjectStream(
    const IObjectSpaceObjectStream& obj, QXmlStreamWriter& xmlWriter)
{
  // no extra level
  writeObjectSpaceObjectStreamHeader(obj.getHeader(), xmlWriter);

  xmlWriter.writeStartElement("CompactIDs");
  for (const auto& entry : obj.getBody()) {
    writeCompactID(entry, xmlWriter);
  }
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectDeclaration2Body(
    const ObjectDeclaration2Body& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectDeclaration2Body");

  xmlWriter.writeStartElement("oid");
  writeCompactID(obj.getOid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("jcid");
  writeJCID(obj.getJcid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fHasOidReferences");
  xmlWriter.writeCharacters(obj.getFHasOidReferences() ? "True" : "False");
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fHasOsidReferences");
  xmlWriter.writeCharacters(obj.getFHasOsidReferences() ? "True" : "False");
  xmlWriter.writeEndElement();

  xmlWriter.writeComment("fReserved2: " + QString::number(obj.getFReserved2()));

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectDeclarationWithRefCountBody(
    const ObjectDeclarationWithRefCountBody& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectDeclarationWithRefCountBody");

  xmlWriter.writeStartElement("oid");
  writeCompactID(obj.getOid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("jci");
  xmlWriter.writeCharacters(QString::number(obj.getJci()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fHasOidReferences");
  xmlWriter.writeCharacters(obj.getFHasOidReferences() ? "True" : "False");
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fHasOsidReferences");
  xmlWriter.writeCharacters(obj.getFHasOsidReferences() ? "True" : "False");
  xmlWriter.writeEndElement();

  xmlWriter.writeComment(
      "fReserved1: " + QString::number(obj.getFReserved1()) +
      ", fReserved2: " + QString::number(obj.getFReserved2()));

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectInfoDependencyOverride32(
    const ObjectInfoDependencyOverride32& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectInfoDependencyOverride32");

  xmlWriter.writeStartElement("oid");
  writeCompactID(obj.getOid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("cRef");
  xmlWriter.writeCharacters(QString::number(obj.getCRef()));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectInfoDependencyOverride8(
    const ObjectInfoDependencyOverride8& obj, QXmlStreamWriter& xmlWriter)
{

  xmlWriter.writeStartElement("oid");
  writeCompactID(obj.getOid(), xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("cRef");
  xmlWriter.writeCharacters(QString::number(obj.getCRef()));
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectSpaceObjectStreamHeader(
    const ObjectSpaceObjectStreamHeader& obj, QXmlStreamWriter& xmlWriter)
{
  // no additional header level, dealt with in writeIObjectSpaceObjectStream

  xmlWriter.writeStartElement("count");
  xmlWriter.writeCharacters(QString::number(obj.getCount()));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("OsidStreamNotPresent");
  xmlWriter.writeCharacters(obj.isOsidStreamNotPresent() ? "True" : "False");
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("ExtendedStreamsPresent");
  xmlWriter.writeCharacters(obj.isExtendedStreamPresent() ? "True" : "False");
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectSpaceObjectStreamOfContextIDs(
    const ObjectSpaceObjectStreamOfContextIDs& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectSpaceObjectStreamOfContextIDs");
  writeIObjectSpaceObjectStream(obj, xmlWriter);
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectSpaceObjectStreamOfOIDs(
    const ObjectSpaceObjectStreamOfOIDs& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectSpaceObjectStreamOfOIDs");
  writeIObjectSpaceObjectStream(obj, xmlWriter);
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeObjectSpaceObjectStreamOfOSIDs(
    const ObjectSpaceObjectStreamOfOSIDs& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectSpaceObjectStreamOfOSIDs");
  writeIObjectSpaceObjectStream(obj, xmlWriter);
  xmlWriter.writeEndElement();

  return xmlWriter;
}

// -----------------------------------------------------------------------------
// common Types
// -----------------------------------------------------------------------------

QXmlStreamWriter&
RSFtoXml::writeCompactID(const CompactID& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("CompactID");

  xmlWriter.writeAttribute("guidIndex", qStringHex(obj.getGuidIndex(), 12));
  xmlWriter.writeAttribute("n", qStringHex(obj.getN(), 2));

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeExtendedGUID(
    const ExtendedGUID& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ExtendedGUID");

  xmlWriter.writeCharacters(obj.toString());

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter&
RSFtoXml::writeGUID(const QUuid& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("GUID");
  xmlWriter.writeCharacters(obj.toString());

  xmlWriter.writeEndElement();

  return xmlWriter;
}

// QXmlStreamWriter& RSFtoXml::writeFileChunkReference32(
//    const FileChunkReference32& obj, QXmlStreamWriter& xmlWriter)
//{
//  xmlWriter.writeStartElement("FileChunkReference32");

//  xmlWriter.writeAttribute("stp", qStringHex(obj.stp(), 8));
//  xmlWriter.writeAttribute("cb", qStringHex(obj.cb(), 8));

//  if (obj.is_fcrNil()) {
//    xmlWriter.writeAttribute("fcrNil", "true");
//  }
//  else if (obj.is_fcrZero()) {
//    xmlWriter.writeAttribute("fcrZero", "true");
//  }

//  xmlWriter.writeEndElement();

//  return xmlWriter;
//}

QXmlStreamWriter& RSFtoXml::writeFileChunkReference64(
    const FileChunkReference64& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("FileChunkReference64");


  xmlWriter.writeAttribute("stp", qStringHex(obj.stp(), 16));
  xmlWriter.writeAttribute("cb", qStringHex(obj.cb(), 16));

  if (obj.is_fcrNil()) {
    xmlWriter.writeAttribute("fcrNil", "true");
  }
  else if (obj.is_fcrZero()) {
    xmlWriter.writeAttribute("fcrZero", "true");
  }


  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeFileChunkReference64x32(
    const FileChunkReference64x32& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("FileChunkReference64x32");

  xmlWriter.writeAttribute("stp", qStringHex(obj.stp(), 16));
  xmlWriter.writeAttribute("cb", qStringHex(obj.cb(), 8));

  if (obj.is_fcrNil()) {
    xmlWriter.writeAttribute("fcrNil", "true");
  }
  else if (obj.is_fcrZero()) {
    xmlWriter.writeAttribute("fcrZero", "true");
  }

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeFileNodeChunkReference(
    const FileNodeChunkReference& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("FileNodeChunkReference");


  xmlWriter.writeAttribute("stp", qStringHex(obj.stp(), 16));
  xmlWriter.writeAttribute("cb", qStringHex(obj.cb(), 16));

  if (obj.is_fcrNil()) {
    xmlWriter.writeAttribute("fcrNil", "true");
  }
  else if (obj.is_fcrZero()) {
    xmlWriter.writeAttribute("fcrZero", "true");
  }

  switch (obj.getStpFormat()) {
  case FNCR_STP_FORMAT::UNCOMPRESED_8BYTE:
    xmlWriter.writeAttribute("stpFormat", "U8");
    break;
  case FNCR_STP_FORMAT::UNCOMPRESED_4BYTE:
    xmlWriter.writeAttribute("stpFormat", "U4");
    break;
  case FNCR_STP_FORMAT::COMPRESSED_4BYTE:
    xmlWriter.writeAttribute("stpFormat", "C4");
    break;
  case FNCR_STP_FORMAT::COMPRESSED_2BYTE:
    xmlWriter.writeAttribute("stpFormat", "C2");
    break;
  }

  switch (obj.getCbFormat()) {
  case FNCR_CB_FORMAT::UNCOMPRESED_8BYTE:
    xmlWriter.writeAttribute("cbFormat", "U8");
    break;
  case FNCR_CB_FORMAT::UNCOMPRESED_4BYTE:
    xmlWriter.writeAttribute("cbFormat", "C4");
    break;
  case FNCR_CB_FORMAT::COMPRESSED_1BYTE:
    xmlWriter.writeAttribute("cbFormat", "C1");
    break;
  case FNCR_CB_FORMAT::COMPRESSED_2BYTE:
    xmlWriter.writeAttribute("cbFormat", "C2");
    break;
  }

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeStringInStorageBuffer(
    const StringInStorageBuffer& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("StringInStorageBuffer");

  xmlWriter.writeAttribute("cch", QString::number(obj.getCch()));

  xmlWriter.writeCharacters(obj.getStringData());

  xmlWriter.writeEndElement();

  return xmlWriter;
}

// -----------------------------------------------------------------------------
// property Types
// -----------------------------------------------------------------------------

QXmlStreamWriter&
RSFtoXml::writeJCID(const JCID& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("JCID");

  xmlWriter.writeAttribute("type", obj.typeToString());
  xmlWriter.writeAttribute("index", qStringHex(obj.index(), 4));
  xmlWriter.writeAttribute("isBinary", obj.IsBinary() ? "true" : "false");
  xmlWriter.writeAttribute(
      "IsPropertySet", obj.IsPropertySet() ? "true" : "false");
  xmlWriter.writeAttribute("IsGraphNode", obj.IsGraphNode() ? "true" : "false");
  xmlWriter.writeAttribute("IsFileData", obj.IsFileData() ? "true" : "false");
  xmlWriter.writeAttribute("IsReadOnly", obj.IsReadOnly() ? "true" : "false");

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter&
RSFtoXml::writePropertyID(const PropertyID& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("PropertyID");

  xmlWriter.writeAttribute("Value", qStringHex(obj.value(), 8));
  xmlWriter.writeAttribute("ID", PropertyID::idToString(obj.id()));
  xmlWriter.writeAttribute("Type", PropertyID::typeToString(obj.type()));
  xmlWriter.writeAttribute("boolValue", obj.boolValue() ? "True" : "False");

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeIPropertyType(
    const std::shared_ptr<IPropertyType>& obj, QXmlStreamWriter& xmlWriter)
{

  switch (obj->getType()) {
  case PropertyIDType::NoData: {
    writePropertyType_NoData(xmlWriter);
    break;
  }
  case PropertyIDType::Bool: {
    writePropertyType_Bool(xmlWriter);
    break;
  }
  case PropertyIDType::OneByteOfData: {
    auto castObj = std::static_pointer_cast<PropertyType_OneByteOfData>(obj);
    writePropertyType_OneByteOfData(castObj, xmlWriter);
    break;
  }
  case PropertyIDType::TwoBytesOfData: {
    auto castObj = std::static_pointer_cast<PropertyType_TwoBytesOfData>(obj);
    writePropertyType_TwoBytesOfData(castObj, xmlWriter);
    break;
  }
  case PropertyIDType::FourBytesOfData: {
    auto castObj = std::static_pointer_cast<PropertyType_FourBytesOfData>(obj);
    writePropertyType_FourBytesOfData(castObj, xmlWriter);
    break;
  }
  case PropertyIDType::EightBytesOfData: {
    auto castObj = std::static_pointer_cast<PropertyType_EightBytesOfData>(obj);
    writePropertyType_EightBytesOfData(castObj, xmlWriter);
    break;
  }
  case PropertyIDType::FourBytesOfLengthFollowedByData: {
    auto castObj =
        std::static_pointer_cast<PropertyType_FourBytesOfLengthFollowedByData>(
            obj);
    writePropertyType_FourBytesOfLengthFollowedByData(castObj, xmlWriter);
    break;
  }
  case PropertyIDType::ObjectID: {
    auto castObj = std::static_pointer_cast<PropertyType_ObjectID>(obj);
    writePropertyType_ObjectID(castObj, xmlWriter);
    break;
  }
  case PropertyIDType::ObjectSpaceID: {
    writePropertyType_ObjectSpaceID(xmlWriter);
    break;
  }
  case PropertyIDType::ContextID: {
    auto castObj = std::static_pointer_cast<PropertyType_ContextID>(obj);
    writePropertyType_ContextID(castObj, xmlWriter);
    break;
  }
  case PropertyIDType::ArrayOfPropertyValues: {
    auto castObj =
        std::static_pointer_cast<PropertyType_ArrayOfPropertyValues>(obj);
    writePropertyType_ArrayOfPropertyValues(castObj, xmlWriter);
    break;
  }
  case PropertyIDType::PropertySet: {
    auto castObj = std::static_pointer_cast<PropertyType_PropertySet>(obj);
    writePropertyType_PropertySet(castObj, xmlWriter);
    break;
  }

  case PropertyIDType::ArrayOfContextIDs:
  case PropertyIDType::ArrayOfObjectIDs:
  case PropertyIDType::ArrayOfObjectSpaceIDs:
  case PropertyIDType::ArrayNumber: {
    auto castObj = std::static_pointer_cast<PropertyType_ArrayNumber>(obj);
    writePropertyType_ArrayNumber(castObj, xmlWriter);
    break;
  }


  case PropertyIDType::None:
  case PropertyIDType::InvalidType:
    break;
  default:
    break;
  }


  return xmlWriter;
}

QXmlStreamWriter&
RSFtoXml::writePropertySet(const PropertySet& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("PropertySet");

  xmlWriter.writeAttribute("cProperties", QString::number(obj.cProperties()));

  for (size_t i{0}; i < obj.rgPrids().size(); i++) {

    auto currentPrid = obj.rgPrids()[i];
    auto currentData = obj.rgData()[i];


    xmlWriter.writeStartElement("PropertyID");

    xmlWriter.writeAttribute(
        "ID", PropertyID::idToString(obj.rgPrids()[i].id()));

    xmlWriter.writeAttribute(
        "Type", PropertyID::typeToString(currentPrid.type()));
    xmlWriter.writeAttribute(
        "boolValue", currentPrid.boolValue() ? "True" : "False");
    xmlWriter.writeAttribute("Value", qStringHex(currentPrid.value(), 8));

    switch (currentPrid.id()) {
    case PropertyIDs::LayoutTightLayout: {
      xmlWriter.writeStartElement("LayoutTightLayout");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PageWidth: {
      xmlWriter.writeStartElement("PageWidth");
      const auto body =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(body);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float pagewidth;
      bytes >> pagewidth;
      // Validity specified by MS-ONE, sec 2.3.6
      if (pagewidth < 2.0 || pagewidth > 44.0) {
        xmlWriter.writeAttribute("valid", "False");
      }
      xmlWriter.writeCharacters(QString::number(pagewidth, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PageHeight: {
      xmlWriter.writeStartElement("PageHeight");
      const auto body =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(body);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float pageheight;
      bytes >> pageheight;
      // Validity specified by MS-ONE, sec 2.3.7,
      // though does not check: (PageMarginTop + PageMarginBottom + 0.5 <
      // pageheight)
      if (pageheight < 0.5 || pageheight > 44.0) {
        xmlWriter.writeAttribute("valid", "False");
      }
      xmlWriter.writeCharacters(QString::number(pageheight, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::OutlineElementChildLevel: {
      xmlWriter.writeStartElement("IndentationLevel");
      const auto body =
          std::dynamic_pointer_cast<PropertyType_OneByteOfData>(currentData)
              ->data();
      QDataStream bytes(body);

      uint8_t val;
      bytes >> val;

      xmlWriter.writeCharacters(QString::number(val));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Bold: {
      xmlWriter.writeStartElement("Bold");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Italic: {
      xmlWriter.writeStartElement("Italic");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Underline: {
      xmlWriter.writeStartElement("Underline");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Strikethrough: {
      xmlWriter.writeStartElement("Strikethrough");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Superscript: {
      xmlWriter.writeStartElement("Superscript");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Subscript: {
      xmlWriter.writeStartElement("Subscript");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::Font: {
      xmlWriter.writeStartElement("Font");
      if (currentPrid.type() ==
          PropertyIDType::FourBytesOfLengthFollowedByData) {
        const auto data =
            std::dynamic_pointer_cast<
                PropertyType_FourBytesOfLengthFollowedByData>(currentData)
                ->data();
        QString string = QString::fromUtf8(data.constData(), data.size());
        xmlWriter.writeCharacters(string);
      }
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::FontSize: {
      xmlWriter.writeStartElement("FontSize");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_TwoBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      uint16_t val;
      bytes >> val;
      // validity given by MS-ONE sec 2.3.16
      if (val < 12 || val > 288) {
        xmlWriter.writeAttribute("valid", "false");
      }
      xmlWriter.writeCharacters(QString::number(val));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::FontColor: {
      xmlWriter.writeStartElement("FontColor");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      libmson::ColorRef val;
      bytes >> val;

      writeColorRef(val, xmlWriter);

      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Highlight: {
      xmlWriter.writeStartElement("Highlight");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      libmson::ColorRef val;
      bytes >> val;

      writeColorRef(val, xmlWriter);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::RgOutlineIndentDistance: {
      xmlWriter.writeStartElement("RgOutlineIndentDistance");
      const auto body =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();
      QDataStream bytes(body);
      bytes.setByteOrder(QDataStream::LittleEndian);
      quint8 count;
      bytes >> count;
      xmlWriter.writeAttribute("count", QString::number(count));
      const QByteArray unused = bytes.device()->read(3);
      xmlWriter.writeAttribute("unused-bytes", unused.toHex());

      xmlWriter.writeStartElement("rgIndents");
      xmlWriter.writeCharacters("{");
      for (quint8 j = 0; j < count; j++) {
        float distance;
        bytes >> distance;
        xmlWriter.writeCharacters(QString::number(distance, 'f', 5));

        if (j + 1 != count) {
          xmlWriter.writeCharacters(", ");
        }
      }
      xmlWriter.writeCharacters("}");
      xmlWriter.writeEndElement();

      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::BodyTextAlignment: {
      const auto data =
          std::dynamic_pointer_cast<PropertyType_OneByteOfData>(currentData)
              ->data();
      libmson::BodyTextAlignment bta;
      QDataStream bytes(data);
      bytes >> bta;
      writeBodyTextAlignment(bta, xmlWriter);
      break;
    }
    case PropertyIDs::OffsetFromParentHoriz: {
      xmlWriter.writeStartElement("OffsetFromParentHoriz");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::OffsetFromParentVert: {
      xmlWriter.writeStartElement("OffsetFromParentVert");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::NumberListFormat:
      //      m_id_string = "NumberListFormat";
      //      break;
    case PropertyIDs::LayoutMaxWidth: {
      xmlWriter.writeStartElement("LayoutMaxWidth");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::LayoutMaxHeight: {
      xmlWriter.writeStartElement("LayoutMaxHeight");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::ContentChildNodes:
      //      m_id_string = "ContentChildNodes";
      //      break;
      //    case PropertyIDs::ElementChildNodes:
      //      m_id_string = "ElementChildNodes";
      //      break;
    case PropertyIDs::EnableHistory: {
      xmlWriter.writeStartElement("EnableHistory");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::RichEditTextUnicode: {
      xmlWriter.writeStartElement("RichEditTextUnicode");
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();
      QString string = QString::fromUtf16(
          reinterpret_cast<const ushort*>(data.constData()), data.size() / 2);

      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::ListNodes:
      //      m_id_string = "ListNodes";
      //      break;
    case PropertyIDs::NotebookManagementEntityGuid: {
      xmlWriter.writeStartElement("NotebookManagementEntityGuid");
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      QUuid val;
      bytes >> val;
      xmlWriter.writeCharacters(val.toString());
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::OutlineElementRTL: {
      xmlWriter.writeStartElement("OutlineElementRTL");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::LanguageID: {

      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      libmson::LCID val;
      bytes >> val;
      writeLCID(val, xmlWriter);
      break;
    }

    case PropertyIDs::LayoutAlignmentInParent: {
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      libmson::LayoutAlignment val;
      bytes >> val;
      writeLayoutAlignment(val, xmlWriter);
      break;
    }
      //    case PropertyIDs::PictureContainer:
      //      m_id_string = "PictureContainer";
      //      break;
    case PropertyIDs::PageMarginTop: {
      xmlWriter.writeStartElement("PageMarginTop");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PageMarginBottom: {
      xmlWriter.writeStartElement("PageMarginBottom");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PageMarginLeft: {
      xmlWriter.writeStartElement("PageMarginLeft");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PageMarginRight: {
      xmlWriter.writeStartElement("PageMarginRight");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ListFont: {
      xmlWriter.writeStartElement("ListFont");
      if (currentPrid.type() ==
          PropertyIDType::FourBytesOfLengthFollowedByData) {
        const auto body = std::dynamic_pointer_cast<
            PropertyType_FourBytesOfLengthFollowedByData>(currentData);
        QString string =
            QString::fromUtf8(body->data().constData(), body->cb());
        xmlWriter.writeCharacters(string);
      }
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::TopologyCreationTimeStamp: {
      xmlWriter.writeStartElement("TopologyCreationTimeStamp");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_EightBytesOfData>(currentData)
              ->data();

      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      libmson::FileTime time;
      bytes >> time;
      xmlWriter.writeCharacters(
          time.getTime().toString("dd/MM/yyyy hh:mm:ss AP"));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::LayoutAlignmentSelf: {
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      libmson::LayoutAlignment val;
      bytes >> val;
      writeLayoutAlignment(val, xmlWriter);
      break;
    }
    case PropertyIDs::IsTitleTime: {
      xmlWriter.writeStartElement("IsTitleTime");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::IsBoilerText: {
      xmlWriter.writeStartElement("IsBoilerText");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PageSize: {
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      libmson::PageSize ps;
      bytes >> ps;
      writePageSize(ps, xmlWriter);
      break;
    }

    case PropertyIDs::PortraitPage: {
      xmlWriter.writeStartElement("PortraitPage");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::EnforceOutlineStructure: {
      xmlWriter.writeStartElement("EnforceOutlineStructure");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::EditRootRTL: {
      xmlWriter.writeStartElement("EditRootRTL");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::CannotBeSelected: {
      xmlWriter.writeStartElement("CannotBeSelected");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::IsTitleText: {
      xmlWriter.writeStartElement("IsTitleText");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::IsTitleDate: {
      xmlWriter.writeStartElement("IsTitleDate");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ListRestart: {
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);

      quint32 val;
      bytes >> val;

      xmlWriter.writeStartElement("ListRestart");
      xmlWriter.writeCharacters(QString::number(val));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::IsLayoutSizeSetByUser: {
      xmlWriter.writeStartElement("IsLayoutSizeSetByUser");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ListSpacingMu: {
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;

      xmlWriter.writeStartElement("ListSpacingMu");
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::LayoutOutlineReservedWidth: {
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;

      xmlWriter.writeStartElement("LayoutOutlineReservedWidth");
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::LayoutResolveChildCollisions: {
      xmlWriter.writeStartElement("LayoutResolveChildCollisions");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::IsReadOnly: {
      xmlWriter.writeStartElement("IsReadOnly");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::LayoutMinimumOutlineWidth: {
      xmlWriter.writeStartElement("LayoutMinimumOutlineWidth");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::LayoutCollisionPriority: {
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      quint32 val;
      bytes >> val;

      xmlWriter.writeStartElement("LayoutCollisionPriority");
      xmlWriter.writeCharacters(qStringHex(val, 8));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::CachedTitleString: {
      xmlWriter.writeStartElement("wz");
      const auto body = std::dynamic_pointer_cast<
          PropertyType_FourBytesOfLengthFollowedByData>(currentData);
      QString string = QString::fromUtf8(body->data().constData(), body->cb());
      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::DescendantsCannotBeMoved: {
      xmlWriter.writeStartElement("DescendantsCannotBeMoved");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::RichEditTextLangID: {
      xmlWriter.writeStartElement("RichEditTextLangID");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_TwoBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      libmson::LCID val;
      bytes >> val;

      writeLCID(val, xmlWriter);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::LayoutTightAlignment: {
      xmlWriter.writeStartElement("LayoutTightAlignment");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Charset: {
      xmlWriter.writeStartElement("Charset");
      auto data =
          std::dynamic_pointer_cast<PropertyType_OneByteOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      libmson::Charset set;
      bytes >> set;

      xmlWriter.writeCharacters(set.toString());
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::CreationTimeStamp: {
      xmlWriter.writeStartElement("CreationTimeStamp");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();

      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      libmson::Time32 time;
      bytes >> time;
      xmlWriter.writeCharacters(
          time.getTime().toString("dd/MM/yyyy hh:mm:ss AP"));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Deletable: {
      xmlWriter.writeStartElement("Deletable");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ListMSAAIndex: {
      const auto data =
          std::dynamic_pointer_cast<PropertyType_TwoBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);

      libmson::ListMSAAIndex index;
      bytes >> index;

      writeListMSAAIndex(index, xmlWriter);

      break;
    }
    case PropertyIDs::IsBackground: {
      xmlWriter.writeStartElement("IsBackground");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::IRecordMedia: {
      xmlWriter.writeStartElement("IRecordMedia");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();

      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      quint32 val;
      bytes >> val;
      xmlWriter.writeCharacters(
          val == 1 ? "Audio" : (val == 2 ? "Video" : "invalid"));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::CachedTitleStringFromPage: {
      xmlWriter.writeStartElement("wz");
      const auto body = std::dynamic_pointer_cast<
          PropertyType_FourBytesOfLengthFollowedByData>(currentData);
      QString string = QString::fromUtf8(body->data().constData(), body->cb());
      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::RowCount: {
      xmlWriter.writeStartElement("RowCount");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();

      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      quint32 val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ColumnCount: {
      xmlWriter.writeStartElement("ColumnCount");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();

      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      quint32 val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val));
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::TableBordersVisible: {
      xmlWriter.writeStartElement("TableBordersVisible");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }

      //    case PropertyIDs::StructureElementChildNodes:
      //      m_id_string = "StructureElementChildNodes";
      //      break;
      //    case PropertyIDs::ChildGraphSpaceElementNodes:
      //      m_id_string = "ChildGraphSpaceElementNodes";
      //      break;
    case PropertyIDs::TableColumnWidths: {
      xmlWriter.writeStartElement("TableColumnWidths");
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      quint8 cColumns;
      bytes >> cColumns;

      xmlWriter.writeAttribute("cColumns", QString::number(cColumns));

      xmlWriter.writeCharacters("{");
      for (quint8 j = 0; j < cColumns; j++) {
        float width;
        bytes >> width;
        xmlWriter.writeCharacters(QString::number(width, 'f', 5));

        if (j + 1 != cColumns) {
          xmlWriter.writeCharacters(", ");
        }
      }
      xmlWriter.writeCharacters("}");
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::Author: {
      xmlWriter.writeStartElement("Author");
      const auto body = std::dynamic_pointer_cast<
          PropertyType_FourBytesOfLengthFollowedByData>(currentData);
      QString string = QString::fromUtf16(
          reinterpret_cast<const ushort*>(body->data().constData()));

      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::LastModifiedTimeStamp: {
      xmlWriter.writeStartElement("LastModifiedTimeStamp");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_EightBytesOfData>(currentData)
              ->data();

      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      libmson::FileTime time;
      bytes >> time;
      writeFileTime(time, xmlWriter);
      xmlWriter.writeEndElement();
      break;
    }
      //      ObjectID:
      //    case PropertyIDs::AuthorOriginal:

      //      ObjectID:
      //    case PropertyIDs::AuthorMostRecent:

    case PropertyIDs::LastModifiedTime: {
      xmlWriter.writeStartElement("LastModifiedTime");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();

      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      libmson::Time32 time;
      bytes >> time;
      writeTime32(time, xmlWriter);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::IsConflictPage: {
      xmlWriter.writeStartElement("IsConflictPage");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }

    /// \todo test TableColumnsLocked whether it produces correct output
    case PropertyIDs::TableColumnsLocked: {
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();

      quint8 cColumns = data.at(0);
      quint8 nbytes   = data.size() - 1;

      xmlWriter.writeStartElement("TableColumnsLocked");
      xmlWriter.writeAttribute("cColumns", QString::number(cColumns));

      xmlWriter.writeStartElement("rgfColumnLocked");
      xmlWriter.writeCharacters("{");
      quint8 kColumns = 0;
      for (quint8 j = 1; j < nbytes; j++) {
        quint8 chunk = data.at(j);
        for (size_t k = 0; k < 8; k++) {
          xmlWriter.writeCharacters(QString::number(((chunk >> k) & 0x1)));
          kColumns++;

          if (j + 1 != cColumns) {
            xmlWriter.writeCharacters(", ");
          }
          else {
            break;
          }
        }
      }
      xmlWriter.writeCharacters("}");
      xmlWriter.writeEndElement();

      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::SchemaRevisionInOrderToRead: {
      xmlWriter.writeStartElement("SchemaRevisionInOrderToRead");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      quint32 val;
      bytes >> val;
      xmlWriter.writeCharacters(qStringHex(val, 8));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::IsConflictObjectForRender: {
      xmlWriter.writeStartElement("IsConflictObjectForRender");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::EmbeddedFileContainer:
      //      m_id_string = "EmbeddedFileContainer";
      //      break;
    case PropertyIDs::EmbeddedFileName: {
      xmlWriter.writeStartElement("EmbeddedFileName");
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();
      QString string = QString::fromUtf16(
          reinterpret_cast<const ushort*>(data.constData()), data.size() / 2);

      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::SourceFilepath: {
      xmlWriter.writeStartElement("SourceFilepath");
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();
      QString string = QString::fromUtf16(
          reinterpret_cast<const ushort*>(data.constData()), data.size() / 2);

      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ConflictingUserName: {
      xmlWriter.writeStartElement("ConflictingUserName");
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();
      QString string = QString::fromUtf8(data.constData(), data.size());
      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ImageFilename: {
      xmlWriter.writeStartElement("ImageFilename");
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();
      QString string = QString::fromUtf16(
          reinterpret_cast<const ushort*>(data.constData()), data.size() / 2);

      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::IsConflictObjectForSelection: {
      xmlWriter.writeStartElement("IsConflictObjectForSelection");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PageLevel: {
      xmlWriter.writeStartElement("PageLevel");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      qint32 val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::TextRunIndex: {
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);

      QString indices = "";
      while (!bytes.atEnd()) {
        quint32 val;
        bytes >> val;

        indices += QString::number(val) + ", ";
      }
      // remove last ", " characters
      indices.resize(indices.size() - 2);

      xmlWriter.writeStartElement("TextRunIndex");
      xmlWriter.writeCharacters("{");
      xmlWriter.writeCharacters(indices);
      xmlWriter.writeCharacters("}");
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::TextRunFormatting:
      //      m_id_string = "TextRunFormatting";
      //      break;
    case PropertyIDs::Hyperlink: {
      xmlWriter.writeStartElement("Hyperlink");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::UnderlineType: {
      const auto data =
          std::dynamic_pointer_cast<PropertyType_OneByteOfData>(currentData)
              ->data();
      quint8 val = data.toUInt();
      xmlWriter.writeStartElement("UnderlineType");
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Hidden: {
      xmlWriter.writeStartElement("Hidden");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::HyperlinkProtected: {
      xmlWriter.writeStartElement("HyperlinkProtected");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::TextRunIsEmbeddedObject: {
      xmlWriter.writeStartElement("TextRunIsEmbeddedObject");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ImageAltText: {
      xmlWriter.writeStartElement("ImageAltText");
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();
      QString string =
          QString::fromUtf16(reinterpret_cast<const ushort*>(data.constData()));

      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::MathFormatting: {
      xmlWriter.writeStartElement("MathFormatting");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::ParagraphStyle: {
      //      break;
      //    }
    case PropertyIDs::ParagraphSpaceBefore: {
      xmlWriter.writeStartElement("ParagraphSpaceBefore");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ParagraphSpaceAfter: {
      xmlWriter.writeStartElement("ParagraphSpaceBefore");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ParagraphLineSpacingExact: {
      xmlWriter.writeStartElement("ParagraphLineSpacingExact");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
      //          case PropertyIDs::MetaDataObjectsAboveGraphSpace: {

      ////        QUuid salt ( 0x22a8c031, 0x3600, 0x42ee, 0xb7, 0x14, 0xd7,
      /// 0xac, 0xda, 0x24, 0x35, 0xe8);

      //            break;
      //      }
      //    case PropertyIDs::TextRunDataObject:
      //      m_id_string = "TextRunDataObject";
      //      break;
      //    case PropertyIDs::TextRunData:
      //      m_id_string = "TextRunData";
      //      break;
    case PropertyIDs::ParagraphStyleId: {
      xmlWriter.writeStartElement("ParagraphStyleId");
      if (currentPrid.type() ==
          PropertyIDType::FourBytesOfLengthFollowedByData) {
        const auto data =
            std::dynamic_pointer_cast<
                PropertyType_FourBytesOfLengthFollowedByData>(currentData)
                ->data();
        QString string = QString::fromUtf8(data.constData(), data.size());
        xmlWriter.writeCharacters(string);
      }
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::HasVersionPages: {
      xmlWriter.writeStartElement("HasVersionPages");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ActionItemType: {

      if (currentPrid.type() ==
          PropertyIDType::FourBytesOfLengthFollowedByData) {
        const auto data =
            std::dynamic_pointer_cast<PropertyType_TwoBytesOfData>(currentData)
                ->data();
        QDataStream ds(data);
        quint16 val;
        ds >> val;

        xmlWriter.writeStartElement("ActionItemType");
        xmlWriter.writeAttribute("val", QString::number(val));

        if (val < 100) {
          xmlWriter.writeCharacters("Tag: " + QString::number(val));
        }
        else {
          switch (val) {
          case 100:
            xmlWriter.writeCharacters("Due today");
            break;
          case 101:
            xmlWriter.writeCharacters("Due tomorrow");
            break;
          case 102:
            xmlWriter.writeCharacters("Due this week");
            break;
          case 103:
            xmlWriter.writeCharacters("Due next week");
            break;
          case 104:
            xmlWriter.writeCharacters("No due date");
            break;
          case 105:
            xmlWriter.writeCharacters("Due on a custom date");
            break;
          }
        }
        xmlWriter.writeEndElement();
        break;
      }
    case PropertyIDs::NoteTagShape: {
      const auto data =
          std::dynamic_pointer_cast<PropertyType_TwoBytesOfData>(currentData)
              ->data();

      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      libmson::NoteTagShape shape;
      bytes >> shape;
      writeNoteTagShape(shape, xmlWriter);
      break;
    }
    case PropertyIDs::NoteTagHighlightColor: {
      xmlWriter.writeStartElement("NoteTagHighlightColor");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      libmson::ColorRef val;
      bytes >> val;
      writeColorRef(val, xmlWriter);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::NoteTagTextColor: {
      xmlWriter.writeStartElement("NoteTagTextColor");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      libmson::ColorRef val;
      bytes >> val;
      writeColorRef(val, xmlWriter);
      xmlWriter.writeEndElement();
      break;
    }

    /// \todo use proper BitReader
    case PropertyIDs::NoteTagPropertyStatus: {
      xmlWriter.writeStartElement("NoteTagPropertyStatus");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      quint32 val;
      bytes >> val;

      xmlWriter.writeStartElement("hasLabel");
      xmlWriter.writeCharacters((val & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("hasFontColor");
      xmlWriter.writeCharacters(((val >> 1) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("hasHighlightColor");
      xmlWriter.writeCharacters(((val >> 2) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("hasIcon");
      xmlWriter.writeCharacters(((val >> 3) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("DueToday");
      xmlWriter.writeCharacters(((val >> 6) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("DueTomorrow");
      xmlWriter.writeCharacters(((val >> 7) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("DueThisWeek");
      xmlWriter.writeCharacters(((val >> 8) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("DueNextWeek");
      xmlWriter.writeCharacters(((val >> 9) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("DueLater");
      xmlWriter.writeCharacters(((val >> 10) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("DueCustom");
      xmlWriter.writeCharacters(((val >> 11) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();

      xmlWriter.writeEndElement();
      break;
    }

    /// \todo not sure whether this is the correct string format (utf8/utf16)
    case PropertyIDs::NoteTagLabel: {
      xmlWriter.writeStartElement("wz");
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();
      QString string = QString::fromUtf8(data.constData(), data.size());
      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::NoteTagCreated: {
      xmlWriter.writeStartElement("NoteTagCreated");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();

      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      libmson::Time32 time;
      bytes >> time;
      writeTime32(time, xmlWriter);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::NoteTagCompleted: {
      xmlWriter.writeStartElement("NoteTagCompleted");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();

      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      libmson::Time32 time;
      bytes >> time;
      writeTime32(time, xmlWriter);
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::NoteTagDefinitionOid:
      //      m_id_string = "NoteTagDefinitionOid";
      //      break;
      //    case PropertyIDs::NoteTagStates:
      //      m_id_string = "NoteTagStates";
      //      break;
    case PropertyIDs::ActionItemStatus: {
      xmlWriter.writeStartElement("ActionItemStatus");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_TwoBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      quint16 val;
      bytes >> val;

      xmlWriter.writeStartElement("Completed");
      xmlWriter.writeCharacters((val & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("Disabled");
      xmlWriter.writeCharacters(((val >> 1) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("TaskTag");
      xmlWriter.writeCharacters(((val >> 2) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("Unsynchronized");
      xmlWriter.writeCharacters(((val >> 3) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("Removed");
      xmlWriter.writeCharacters(((val >> 4) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();

      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ActionItemSchemaVersion: {
      xmlWriter.writeStartElement("ActionItemSchemaVersion");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_OneByteOfData>(currentData)
              ->data();
      xmlWriter.writeCharacters("0x" + data.toHex());
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::ReadingOrderRTL: {
      xmlWriter.writeStartElement("ReadingOrderRTL");

      int val = currentPrid.boolValue();
      xmlWriter.writeCharacters(
          val == 0 ? "False" : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
      /// \todo declare ParagraphAlignment Enum
    case PropertyIDs::ParagraphAlignment: {

      const auto data =
          std::dynamic_pointer_cast<PropertyType_OneByteOfData>(currentData)
              ->data();

      QString align;

      switch (data.toUInt()) {
      case 0:
        align = "Left";
        break;
      case 1:
        align = "Center";
        break;
      case 2:
        align = "Right";
        break;

      default:
        align = "invalid";
        break;
      }
      xmlWriter.writeStartElement("ParagraphAlignment");
      xmlWriter.writeCharacters(align);
      xmlWriter.writeEndElement();

      break;
    }
      //    case PropertyIDs::VersionHistoryGraphSpaceContextNodes:
      //      m_id_string = "VersionHistoryGraphSpaceContextNodes";
      //      break;

    case PropertyIDs::DisplayedPageNumber: {
      xmlWriter.writeStartElement("DisplayedPageNumber");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      quint32 val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::SectionDisplayName: {
      xmlWriter.writeStartElement("wz");
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();
      QString string = QString::fromUtf8(data.constData(), data.size());
      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::NextStyle: {
      xmlWriter.writeStartElement("wz");
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();
      QString string = QString::fromUtf8(data.constData(), data.size());
      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::WebPictureContainer14:
      //      m_id_string = "WebPictureContainer14";
      //      break;
    case PropertyIDs::ImageUploadState: {

      const auto data =
          std::dynamic_pointer_cast<PropertyType_OneByteOfData>(currentData)
              ->data();

      QString state;
      switch (data.toUInt()) {
      case 0:
        state = "Upload complete";
        break;
      case 1:
        state = "Upload in progress";
        break;
      case 2:
        state = "Upload failed";
        break;

      default:
        state = "Invalid Upload state";
        break;
      }
      xmlWriter.writeStartElement("ImageUploadState");
      xmlWriter.writeCharacters(state);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::TextExtendedAscii: {
      xmlWriter.writeStartElement("String");
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();
      QString string = QString::fromUtf8(data.constData(), data.size());
      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PictureWidth: {
      xmlWriter.writeStartElement("PictureWidth");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PictureHeight: {
      xmlWriter.writeStartElement("PictureHeight");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PageMarginOriginX: {
      xmlWriter.writeStartElement("PageMarginOriginX");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PageMarginOriginY: {
      xmlWriter.writeStartElement("PageMarginOriginY");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::WzHyperlinkUrl: {
      xmlWriter.writeStartElement("wz");
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();
      QString string = QString::fromUtf8(data.constData(), data.size());
      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::TaskTagDueDate: {
      xmlWriter.writeStartElement("TaskTagDueDate");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();

      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      libmson::Time32 time;
      bytes >> time;
      writeTime32(time, xmlWriter);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::undoc_AuthorInitials: {
      xmlWriter.writeStartElement("undoc_AuthorInitials");
      if (currentPrid.type() ==
          PropertyIDType::FourBytesOfLengthFollowedByData) {
        const auto data =
            std::dynamic_pointer_cast<
                PropertyType_FourBytesOfLengthFollowedByData>(currentData)
                ->data();
        QString string = QString::fromUtf8(data.constData(), data.size());
        xmlWriter.writeCharacters(string);
      }
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::undoc_ResolutionID: {
      xmlWriter.writeStartElement("undoc_ResolutionID");
      if (currentPrid.type() ==
          PropertyIDType::FourBytesOfLengthFollowedByData) {
        const auto data =
            std::dynamic_pointer_cast<
                PropertyType_FourBytesOfLengthFollowedByData>(currentData)
                ->data();
        QString string = QString::fromUtf8(data.constData(), data.size());
        xmlWriter.writeCharacters(string);
      }
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::undoc_StrokesBlob: {
      xmlWriter.writeStartElement("undoc_StrokesBlob");
      writeIPropertyType(currentData, xmlWriter);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::undoc_StrokesIndex: {
      xmlWriter.writeStartElement("undoc_StrokesIndex");
      if (currentPrid.type() == PropertyIDType::FourBytesOfData) {
        const auto data =
            std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
                ->data();
        QDataStream bytes(data);
        bytes.setByteOrder(QDataStream::LittleEndian);
        bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
        uint32_t val;
        bytes >> val;
        xmlWriter.writeCharacters(QString::number(val));
      }
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::unodc_StrokeLanguage: {
      xmlWriter.writeStartElement("unodc_StrokeLanguage");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_TwoBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      quint16 val;
      bytes >> val;
      xmlWriter.writeCharacters(libmson::LCID::languageIDtoString(
          static_cast<libmson::LanguageID>(val)));
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_StrokesColor: {
      xmlWriter.writeStartElement("undoc_StrokesColor");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();

      xmlWriter.writeCharacters("#" + data.toHex());
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_StrokesToolSizeHeight: {
      xmlWriter.writeStartElement("undoc_StrokesToolSizeHeight");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::undoc_StrokesToolSizeWidth: {
      xmlWriter.writeStartElement("undoc_StrokesToolSizeWidth");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_StrokesCreationTime: {
      xmlWriter.writeStartElement("undoc_StrokesCreationTime");
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();

      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      libmson::FileTime time;
      bytes >> time;
      writeFileTime(time, xmlWriter);
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_StrokesRecognizedText: {
      xmlWriter.writeStartElement("undoc_StrokesRecognizedText");
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();

      QString string = QString::fromUtf16(
          reinterpret_cast<const ushort*>(data.constData()), data.size() / 2);
      QStringList strings = string.split('\0');
      for (const auto& str : strings) {
        if (str.size() > 0) {
          xmlWriter.writeStartElement("match");
          xmlWriter.writeCharacters(str);
          xmlWriter.writeEndElement();
        }
      }
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_StrokesOffsetsVertHoriz: {
      xmlWriter.writeStartElement("undoc_StrokesOffsetsVertHoriz");
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float vert, horiz;
      bytes >> vert;
      bytes >> horiz;

      xmlWriter.writeStartElement("Vert");
      xmlWriter.writeCharacters(QString::number(vert, 'f', 5));
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("Horiz");
      xmlWriter.writeCharacters(QString::number(horiz, 'f', 5));
      xmlWriter.writeEndElement();

      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_StrokesModus: {
      xmlWriter.writeStartElement("undoc_StrokesModus");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_OneByteOfData>(currentData)
              ->data();
      switch (data.toInt()) {
      case 0:
        xmlWriter.writeCharacters("HandwrittingAndDrawing");
        break;
      case 1:
        xmlWriter.writeCharacters("DrawingOnly");
        break;
      case 2:
        xmlWriter.writeCharacters("HandwritingOnly");
        break;
      default:
        break;
      }

      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_StrokesGUID: {
      xmlWriter.writeStartElement("undoc_StrokesGUID");
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();
      QDataStream bytes(data);
      QUuid guid;
      bytes >> guid;

      xmlWriter.writeCharacters(guid.toString());
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_RecognizedText: {
      xmlWriter.writeStartElement("undoc_RecognizedText");
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();

      QString string = QString::fromUtf16(
          reinterpret_cast<const ushort*>(data.constData()), data.size() / 2);
      QStringList strings = string.split('\0');
      for (const auto& str : strings) {
        if (str.size() > 0) {
          xmlWriter.writeStartElement("match");
          xmlWriter.writeCharacters(str);
          xmlWriter.writeEndElement();
        }
      }
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_tocSectionName: {
      xmlWriter.writeStartElement("undoc_tocSectionName");
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();

      QString string = QString::fromUtf16(
          reinterpret_cast<const ushort*>(data.constData()), data.size() / 2);

      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_tocSectionIndex: {
      xmlWriter.writeStartElement("undoc_tocSectionIndex");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      quint32 val;
      bytes >> val;

      xmlWriter.writeCharacters(QString::number(val));
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_tocSectionGUID: {
      xmlWriter.writeStartElement("undoc_tocSectionGUID");
      const auto data =
          std::dynamic_pointer_cast<
              PropertyType_FourBytesOfLengthFollowedByData>(currentData)
              ->data();
      QDataStream bytes(data);
      QUuid val;
      bytes >> val;
      xmlWriter.writeCharacters(val.toString());
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_tocSectionColor: {
      xmlWriter.writeStartElement("undoc_tocSectionColor");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      libmson::ColorRef val;
      bytes >> val;
      writeColorRef(val, xmlWriter);
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_SchemaRevisionInOrderToRead: {
      xmlWriter.writeStartElement("undoc_SchemaRevisionInOrderToRead");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      quint32 val;
      bytes >> val;
      xmlWriter.writeCharacters(qStringHex(val, 8));
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_PageBackgroundColor: {
      xmlWriter.writeStartElement("undoc_PageBackgroundColor");
      const auto data =
          std::dynamic_pointer_cast<PropertyType_FourBytesOfData>(currentData)
              ->data();

      xmlWriter.writeCharacters("#" + data.toHex());
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::None:
    default:
      writeIPropertyType(currentData, xmlWriter);
      break;
    }
    }
    xmlWriter.writeEndElement(); // PropertyID
  }

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writePropertyType_ArrayNumber(
    const std::shared_ptr<PropertyType_ArrayNumber>& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ArrayNumber");
  xmlWriter.writeAttribute("cCID", QString::number(obj->cCIDs()));

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writePropertyType_ArrayOfPropertyValues(
    const std::shared_ptr<PropertyType_ArrayOfPropertyValues>& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ArrayOfPropertyValues");
  xmlWriter.writeAttribute(
      "m_cProperties", QString::number(obj->cProperties()));
  writePropertyID(obj->prid(), xmlWriter);

  xmlWriter.writeStartElement("PropertySets");
  for (const auto& entry : obj->data()) {
    writePropertySet(entry, xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writePropertyType_Bool(QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeEmptyElement("Bool");
  // no data
  /// \todo get info from PropertySet

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writePropertyType_ContextID(
    const std::shared_ptr<PropertyType_ContextID>& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ContextID");

  writeCompactID(obj->data(), xmlWriter);

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writePropertyType_EightBytesOfData(
    const std::shared_ptr<PropertyType_EightBytesOfData>& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("EightBytesOfData");

  xmlWriter.writeCharacters(obj->data().toHex());

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writePropertyType_FourBytesOfData(
    const std::shared_ptr<PropertyType_FourBytesOfData>& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("FourBytesOfData");

  xmlWriter.writeCharacters(obj->data().toHex());

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writePropertyType_FourBytesOfLengthFollowedByData(
    const std::shared_ptr<PropertyType_FourBytesOfLengthFollowedByData>& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("FourBytesOfLengthFollowedByData");

  xmlWriter.writeAttribute("cb", QString::number(obj->cb()));
  xmlWriter.writeCharacters(obj->data().toHex());

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter&
RSFtoXml::writePropertyType_NoData(QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeEmptyElement("NoData");
  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writePropertyType_ObjectID(
    const std::shared_ptr<PropertyType_ObjectID>& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ObjectID");

  writeCompactID(obj->data(), xmlWriter);

  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter&
RSFtoXml::writePropertyType_ObjectSpaceID(QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeEmptyElement("ObjectSpaceID");
  // no data
  /// \todo get info from PropertySet

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writePropertyType_OneByteOfData(
    const std::shared_ptr<PropertyType_OneByteOfData>& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("OneByteOfData");
  xmlWriter.writeCharacters(obj->data().toHex());
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writePropertyType_PropertySet(
    const std::shared_ptr<PropertyType_PropertySet>& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("PropertySet");
  writePropertySet(obj->data(), xmlWriter);
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writePropertyType_TwoBytesOfData(
    const std::shared_ptr<PropertyType_TwoBytesOfData>& obj,
    QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("TwoBytesOfData");
  xmlWriter.writeCharacters(obj->data().toHex());
  xmlWriter.writeEndElement();

  return xmlWriter;
}


// MS-ONE stuff

// -----------------------------------------------------------------------------
// simple types
// -----------------------------------------------------------------------------

QXmlStreamWriter& RSFtoXml::writeBodyTextAlignment(
    const libmson::BodyTextAlignment& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("BodyTextAlignment");
  xmlWriter.writeCharacters(QString::number(obj.getValue()));
  xmlWriter.writeEndElement();

  return xmlWriter;
}


QXmlStreamWriter& RSFtoXml::writeFileTime(
    const libmson::FileTime& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("FILETIME");
  xmlWriter.writeCharacters(obj.getTime().toString("dd/MM/yyyy hh:mm:ss AP"));
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeLayoutAlignment(
    const libmson::LayoutAlignment& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("LayoutAlignment");
  xmlWriter.writeAttribute(
      "horizontal",
      libmson::LayoutAlignment::hAlignmentToString(obj.getHAlignment()));
  xmlWriter.writeAttribute(
      "vertial",
      libmson::LayoutAlignment::vAlignmentToString(obj.getVAlignment()));
  xmlWriter.writeAttribute("hMargin", obj.getFHorizMargin() ? "true" : "false");
  xmlWriter.writeAttribute("vMargin", obj.getFVertMargin() ? "true" : "false");
  xmlWriter.writeAttribute("valid", !obj.isNil() ? "true" : "false");
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter&
RSFtoXml::writeLCID(const libmson::LCID& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("LCID");
  xmlWriter.writeAttribute("SortID", qStringHex(obj.getSortID(), 4));
  xmlWriter.writeCharacters(obj.languageIDtoString());
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeListMSAAIndex(
    const libmson::ListMSAAIndex& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("ListMSAAIndex");
  xmlWriter.writeCharacters(libmson::ListMSAAIndex::IDtoString(obj.getID()));
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeNoteTagShape(
    const libmson::NoteTagShape& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("NoteTagShape");
  xmlWriter.writeCharacters(
      libmson::NoteTagShape::idToString(obj.getShapeID()));
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writePageSize(
    const libmson::PageSize& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("PageSize");
  xmlWriter.writeCharacters(libmson::PageSize::typeToString(obj.getPageType()));
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter&
RSFtoXml::writeTime32(const libmson::Time32& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("Time32");
  xmlWriter.writeCharacters(obj.getTime().toString("dd/MM/yyyy hh:mm:ss AP"));
  xmlWriter.writeEndElement();

  return xmlWriter;
}

// -----------------------------------------------------------------------------
// complex types
// -----------------------------------------------------------------------------
QXmlStreamWriter& RSFtoXml::writeColorRef(
    const libmson::ColorRef& obj, QXmlStreamWriter& xmlWriter)
{
  xmlWriter.writeStartElement("COLORREF");
  xmlWriter.writeCharacters(qStringHex(obj.getColorRef(), 8));
  xmlWriter.writeEndElement();

  return xmlWriter;
}

QXmlStreamWriter& RSFtoXml::writeFcr64orChunk(
    const Chunkable_SPtr_t& chunk, bool followRecursively, FCR_INIT init,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  if (followRecursively) {
    if (chunk == nullptr) {
      if (init == FCR_INIT::NIL) {
        xmlWriter.writeEmptyElement("Nil");
      }
      else {
        xmlWriter.writeEmptyElement("None");
      }
      return xmlWriter;
    }

    return writeChunkable(
        chunk, followRecursively, revisionStoreFile, xmlWriter);
  }

  auto ref = getFcr64FromChunk(revisionStoreFile, chunk, init);
  return writeFileChunkReference64(ref, xmlWriter);
}


QXmlStreamWriter& RSFtoXml::writeFcr64x32orChunk(
    const Chunkable_SPtr_t& chunk, bool followRecursively, FCR_INIT init,
    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  if (followRecursively) {
    if (chunk == nullptr) {
      if (init == FCR_INIT::NIL) {
        xmlWriter.writeEmptyElement("Nil");
      }
      else {
        xmlWriter.writeEmptyElement("None");
      }
      return xmlWriter;
    }

    return writeChunkable(
        chunk, followRecursively, revisionStoreFile, xmlWriter);
  }

  auto ref = getFcr64x32FromChunk(revisionStoreFile, chunk, init);
  return writeFileChunkReference64x32(ref, xmlWriter);
}


QXmlStreamWriter& RSFtoXml::writeFncrOrChunk(
    const Chunkable_SPtr_t& chunk, bool followRecursively,
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat, FCR_INIT init,

    const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
    QXmlStreamWriter& xmlWriter)
{
  if (followRecursively) {
    if (chunk == nullptr) {
      if (init == FCR_INIT::NIL) {
        xmlWriter.writeEmptyElement("Nil");
      }
      else {
        xmlWriter.writeEmptyElement("None");
      }
      return xmlWriter;
    }

    return writeChunkable(
        chunk, followRecursively, revisionStoreFile, xmlWriter);
  }

  auto ref =
      getFncrFromChunk(revisionStoreFile, chunk, stpFormat, cbFormat, init);
  return writeFileNodeChunkReference(ref, xmlWriter);
}
