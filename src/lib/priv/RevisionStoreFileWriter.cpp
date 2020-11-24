#include "RevisionStoreFileWriter.h"

#include <array>
#include <memory>

//#include "chunkables/Chunkable.h"
#include "chunkables/EncryptedData.h"
#include "chunkables/FileDataStoreObject.h"
#include "chunkables/FileNode.h"
#include "chunkables/FileNodeListFragment.h"
#include "chunkables/FreeChunk.h"
#include "chunkables/FreeChunkListFragment.h"
#include "chunkables/ObjectInfoDependencyOverrideData.h"
#include "chunkables/ObjectSpaceObjectPropSet.h"
#include "chunkables/RevisionStoreFileHeader.h"
#include "chunkables/TransactionLogFragment.h"
#include "chunkables/UnknownBlob.h"


#include "commonTypes/FileChunkReference64.h"
#include "commonTypes/FileChunkReference64x32.h"

#include "utils/CrcAlgorithms.h"

#include "chunkables/fileNodeTypes/ChunkTerminatorFND.h"
#include "chunkables/fileNodeTypes/DataSignatureGroupDefinitionFND.h"
#include "chunkables/fileNodeTypes/FileDataStoreListReferenceFND.h"
#include "chunkables/fileNodeTypes/FileDataStoreObjectReferenceFND.h"
#include "chunkables/fileNodeTypes/GlobalIdTableEndFNDX.h"
#include "chunkables/fileNodeTypes/GlobalIdTableEntry2FNDX.h"
#include "chunkables/fileNodeTypes/GlobalIdTableEntry3FNDX.h"
#include "chunkables/fileNodeTypes/GlobalIdTableEntryFNDX.h"
#include "chunkables/fileNodeTypes/GlobalIdTableStart2FND.h"
#include "chunkables/fileNodeTypes/GlobalIdTableStartFNDX.h"
#include "chunkables/fileNodeTypes/HashedChunkDescriptor2FND.h"
#include "chunkables/fileNodeTypes/ObjectDataEncryptionKeyV2FNDX.h"
#include "chunkables/fileNodeTypes/ObjectDeclaration2LargeRefCountFND.h"
#include "chunkables/fileNodeTypes/ObjectDeclaration2RefCountFND.h"
#include "chunkables/fileNodeTypes/ObjectDeclarationFileData3LargeRefCountFND.h"
#include "chunkables/fileNodeTypes/ObjectDeclarationFileData3RefCountFND.h"
#include "chunkables/fileNodeTypes/ObjectDeclarationWithRefCount2FNDX.h"
#include "chunkables/fileNodeTypes/ObjectDeclarationWithRefCountFNDX.h"
#include "chunkables/fileNodeTypes/ObjectGroupEndFND.h"
#include "chunkables/fileNodeTypes/ObjectGroupListReferenceFND.h"
#include "chunkables/fileNodeTypes/ObjectGroupStartFND.h"
#include "chunkables/fileNodeTypes/ObjectInfoDependencyOverridesFND.h"
#include "chunkables/fileNodeTypes/ObjectRevisionWithRefCount2FNDX.h"
#include "chunkables/fileNodeTypes/ObjectRevisionWithRefCountFNDX.h"
#include "chunkables/fileNodeTypes/ObjectSpaceManifestListReferenceFND.h"
#include "chunkables/fileNodeTypes/ObjectSpaceManifestListStartFND.h"
#include "chunkables/fileNodeTypes/ObjectSpaceManifestRootFND.h"
#include "chunkables/fileNodeTypes/ReadOnlyObjectDeclaration2LargeRefCountFND.h"
#include "chunkables/fileNodeTypes/ReadOnlyObjectDeclaration2RefCountFND.h"
#include "chunkables/fileNodeTypes/RevisionManifestEndFND.h"
#include "chunkables/fileNodeTypes/RevisionManifestListReferenceFND.h"
#include "chunkables/fileNodeTypes/RevisionManifestListStartFND.h"
#include "chunkables/fileNodeTypes/RevisionManifestStart4FND.h"
#include "chunkables/fileNodeTypes/RevisionManifestStart6FND.h"
#include "chunkables/fileNodeTypes/RevisionManifestStart7FND.h"
#include "chunkables/fileNodeTypes/RevisionRoleAndContextDeclarationFND.h"
#include "chunkables/fileNodeTypes/RevisionRoleDeclarationFND.h"
#include "chunkables/fileNodeTypes/RootObjectReference2FNDX.h"
#include "chunkables/fileNodeTypes/RootObjectReference3FND.h"

#include <QCryptographicHash>

#include "ObjectSpaceManifestList.h"
#include "RevisionManifest.h"
#include "RevisionManifestList.h"


namespace libmson {
namespace priv {


RevisionStoreFileWriter::RevisionStoreFileWriter(
    std::shared_ptr<RevisionStoreFile>& revisionStoreFile)
    : m_revStoreFile(revisionStoreFile)
{
}

bool RevisionStoreFileWriter::write(QDataStream& ds)
{
  if (!writeRevisionStoreFileHeader(ds, m_revStoreFile->getHeader())) {
    return false;
  }

  computeTransactionEntryCRCs();


  auto chunks = m_revStoreFile->chunks();


  if (chunks.size() < 1) {
    qFatal("No chunks to write in RevisionStoreFile.");
  }


  for (auto it = chunks.begin(); it != chunks.end(); ++it) {

    bool currentChunkWrite = writeChunk(ds, *it);
    if (!currentChunkWrite) {
      return false;
    }
  }


  return true;
}

bool RevisionStoreFileWriter::writeChunk(
    QDataStream& ds, Chunkable_SPtr_t chunk)
{
  if (!chunk->isParsed()) {
    return writeUnparsedChunk(ds, chunk);
  }

  switch (chunk->type()) {

  case RevisionStoreChunkType::RevisionStoreFileHeader: {
    auto tchunk = std::static_pointer_cast<RevisionStoreFileHeader>(chunk);
    return writeRevisionStoreFileHeader(ds, tchunk);
  }
  case RevisionStoreChunkType::FileNodeListFragment: {
    auto tchunk = std::static_pointer_cast<FileNodeListFragment>(chunk);
    return writeFileNodeListFragment(ds, tchunk);
  }
  case RevisionStoreChunkType::FileNode: {
    auto tchunk = std::static_pointer_cast<FileNode>(chunk);
    return writeFileNode(ds, tchunk);
  }
  case RevisionStoreChunkType::FreeChunkListFragment: {
    auto tchunk = std::static_pointer_cast<FreeChunkListFragment>(chunk);
    return writeFreeChunkListFragment(ds, tchunk);
  }
  case RevisionStoreChunkType::FreeChunk: {
    auto tchunk = std::static_pointer_cast<FreeChunk>(chunk);
    return writeFreeChunk(ds, tchunk);
  }
  case RevisionStoreChunkType::TransactionLogFragment: {
    auto tchunk = std::static_pointer_cast<TransactionLogFragment>(chunk);
    return writeTransactionLogFragment(ds, tchunk);
  }
  case RevisionStoreChunkType::FileDataStoreObject: {
    auto tchunk = std::static_pointer_cast<FileDataStoreObject>(chunk);
    return writeFileDataStoreObject(ds, tchunk);
  }
  case RevisionStoreChunkType::ObjectSpaceObjectPropSet: {
    auto tchunk = std::static_pointer_cast<ObjectSpaceObjectPropSet>(chunk);
    return writeObjectSpaceObjectPropSet(ds, tchunk);
  }
  case RevisionStoreChunkType::ObjectInfoDependencyOverrideData: {
    auto tchunk =
        std::static_pointer_cast<ObjectInfoDependencyOverrideData>(chunk);
    return writeObjectInfoDependencyOverrideData(ds, tchunk);
  }
  case RevisionStoreChunkType::EncryptedData: {
    auto tchunk = std::static_pointer_cast<EncryptedData>(chunk);
    return writeEncryptedData(ds, tchunk);
  }

  case RevisionStoreChunkType::UnknownBlob: {
    auto tchunk = std::static_pointer_cast<UnknownBlob>(chunk);
    return writeUnknownBlob(ds, tchunk);
  }

  case RevisionStoreChunkType::Invalid:
  default:
    qFatal("Failed to initialize invalid RevisionStoreChunkType.");
  }


  return true;
}

bool RevisionStoreFileWriter::writeRevisionStoreFileHeader(
    QDataStream& ds, RevisionStoreFileHeader_SPtr_t header)
{

  // if byte order is big endian, change to little endian
  if (ds.byteOrder() == QDataStream::BigEndian) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }


  quint64 totalFileSize = RevisionStoreFileHeader::sizeInFile;

  auto addCb = [](quint64 a, Chunkable_SPtr_t& b) {
    return std::move(a) + b->getSizeInFile();
  };

  totalFileSize += std::accumulate(
      m_revStoreFile->chunks().begin(), m_revStoreFile->chunks().end(), 0,
      addCb);

  // Updating the header;
  header->setCbExpectedFileLength(totalFileSize);
  header->setCrcName(Crc32::computeCrcName(m_revStoreFile->getFileName()));
  /// \todo update cTransactionsInLog

  ds << header->getGuidFileType();
  ds << header->getGuidFile();
  ds << RevisionStoreFileHeader::guidLegacyFileVersion;
  ds << RevisionStoreFileHeader::guidFileFormat;
  // 0x0040
  ds << header->getFfvLastWriterVersion();
  ds << header->getFfvOldestWriterVersion();
  ds << header->getFfvNewestWriterVersion();
  ds << header->getFfvOldestReader();

  // 0x0050

  // fcrLegacyFreeChunkList
  ds << FileChunkReference32(FCR_INIT::ZERO);
  // fcrLegacyTransactionLog
  ds << FileChunkReference32(FCR_INIT::NIL);

  // 0x0060
  ds << header->getCTransactionsInLog();

  quint32 cbLegacyExpectedFileLength = 0u;
  ds << cbLegacyExpectedFileLength;

  ds << header->getRgbPlaceholder();

  // fcrLegacyFileNodeListRoot
  ds << FileChunkReference32(FCR_INIT::NIL);

  quint32 cbLegacyFreeSpaceInFreeChunkList = 0u;
  ds << cbLegacyFreeSpaceInFreeChunkList;

  ds << header->getFNeedsDefrag();
  ds << header->getFRepairedFile();
  ds << header->getFNeedsGarbageCollect();
  ds << header->getFHasNoEmbeddedFileObjects();

  // 0x0080
  ds << header->getGuidAncestor();

  // 0x0090
  ds << header->getCrcName();

  // fcrHashedChunkList
  ds << getFcr64x32FromChunk(header->getFcrHashedChunkList());

  // 0x00A0
  // fcrTransactionLog
  ds << getFcr64x32FromChunk(header->getFcrTransactionLog());

  // fcrFileNodeListRoot
  ds << getFcr64x32FromChunk(header->getFcrFileNodeListRoot());

  // fcrFreeChunkList
  ds << getFcr64x32FromChunk(header->getFcrFreeChunkList());

  // 0x00C4
  ds << header->getCbExpectedFileLength();
  ds << header->getCbFreeSpaceInFreeChunkList();
  ds << header->getGuidFileVersion();
  ds << header->getNFileVersionGeneration();
  ds << header->getGuidDenyReadFileVersion();
  ds << header->getGrfDebugLogFlags();

  // 0x0100
  // fcrDebugLog
  ds << FileChunkReference64x32(FCR_INIT::ZERO);

  // fcrAllocVerificationFreeChunkList
  ds << FileChunkReference64x32(FCR_INIT::ZERO);

  ds << header->getBnCreated();
  ds << header->getBnLastWroteToThisFile();
  // 0x0120
  ds << header->getBnOldestWritten();
  ds << header->getBnNewestWritten();

  const std::array<char, RevisionStoreFileHeader::def_reservedHeaderTailLength>
      padding{};

  ds.writeRawData(
      padding.data(), RevisionStoreFileHeader::def_reservedHeaderTailLength);

  return true;
}

bool RevisionStoreFileWriter::writeTransactionLogFragment(
    QDataStream& ds, TransactionLogFragment_SPtr_t transactionLogFragment)
{

  // if byte order is big endian, change to little endian
  if (ds.byteOrder() == QDataStream::BigEndian) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  auto sizeTable = transactionLogFragment->getSizeTable();
  //  std::list<TransactionEntry_SPtr_t> currentGroup;
  for (auto it = sizeTable.begin(); it != sizeTable.end(); ++it) {


    //    quint32 currentSrcID = (*it)->getSrcID();
    //    if (currentSrcID != 0x0 && currentSrcID != 0x1) {
    //      currentGroup.push_back(*it);
    //      ds << **it;
    //      continue;
    //    }

    //    if (currentSrcID == 0x1) {
    //      auto toHash = std::make_unique<QByteArray>(
    //          currentGroup.size() * TransactionEntry::getSizeInFile(), 0x0);

    //      QDataStream data_ds(toHash.get(), QIODevice::WriteOnly);
    //      data_ds.setByteOrder(QDataStream::LittleEndian);

    //      for (const auto& entry : currentGroup) {
    //        data_ds << *entry;
    //      }

    //      /// \todo switch depending on file type
    //      (*it)->setTransactionEntrySwitch(Crc32::computeCRC(*toHash));

    //      ds << **it;
    //      //      currentGroup.clear();
    //      currentGroup.push_back(*it);
    //    }
    //    else {
    //      /// \todo deal with transactions spanning multiple Fragments, likely
    //      need
    //      /// a method which deals with all transactionLogFragment Chunkables
    //    }

    //    if (currentSrcID == 0x0) {
    ds << **it;
    //    }
  }


  ds << getFcr64x32FromChunk(
      transactionLogFragment->getNextFragment(), FCR_INIT::ZERO);


  quint8 zeros{};
  for (quint8 i = 0; i < transactionLogFragment->getPaddingLength(); i++) {
    ds << zeros;
  }

  return true;
}

bool RevisionStoreFileWriter::writeUnknownBlob(
    QDataStream& ds, UnknownBlob_SPtr_t unknownBlob)
{
  // if byte order is big endian, change to little endian
  if (ds.byteOrder() == QDataStream::BigEndian) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }


  ds.writeRawData(unknownBlob->getBlob(), unknownBlob->getBlob().size());

  return true;
}

bool RevisionStoreFileWriter::writeFileNode(
    QDataStream& ds, FileNode_SPtr_t& fileNode)
{
  // if byte order is big endian, change to little endian
  if (ds.byteOrder() == QDataStream::BigEndian) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  {
    quint32 composite;

    // reserved, must be 1, MS-ONESTORE section 2.4.3 FileNode
    composite = 1u << fNshiftReserved;

    composite += (fileNode->getBaseType() & fNmaskBaseType) << fNshiftBaseType;
    composite += (fileNode->getCbFormat() & fNmaskCbFormat) << fNshiftCbFormat;
    composite += (fileNode->getStpFormat() & fNmaskStpFormat)
                 << fNshiftStpFormat;
    composite += (fileNode->getSizeInFile() & fNmaskFileNodeSize)
                 << fNshiftFileNodeSize;
    composite += (fileNode->getFileNodeID() & fNmaskFileNodeID)
                 << fNshiftFileNodeID;

    ds << composite;
  }

  if (fileNode->getBaseType() == 0) {
    switch (fileNode->getFileNodeTypeID()) {


    case FileNodeTypeID::GlobalIdTableEntry2FNDX: {
      ds << *std::static_pointer_cast<GlobalIdTableEntry2FNDX>(
          fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::GlobalIdTableEntry3FNDX: {
      ds << *std::static_pointer_cast<GlobalIdTableEntry3FNDX>(
          fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::GlobalIdTableEntryFNDX: {
      ds << *std::static_pointer_cast<GlobalIdTableEntryFNDX>(
          fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::GlobalIdTableStart2FND: {
      ds << *std::static_pointer_cast<GlobalIdTableStart2FND>(
          fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::GlobalIdTableStartFNDX: {
      ds << *std::static_pointer_cast<GlobalIdTableStartFNDX>(
          fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::ObjectDeclarationFileData3LargeRefCountFND: {
      ds << *std::static_pointer_cast<
          ObjectDeclarationFileData3LargeRefCountFND>(fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::ObjectDeclarationFileData3RefCountFND: {
      ds << *std::static_pointer_cast<ObjectDeclarationFileData3RefCountFND>(
          fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::ObjectGroupEndFND: {
      ds << *std::static_pointer_cast<ObjectGroupEndFND>(fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::ObjectGroupStartFND: {
      ds << *std::static_pointer_cast<ObjectGroupStartFND>(fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::ObjectSpaceManifestListStartFND: {
      ds << *std::static_pointer_cast<ObjectSpaceManifestListStartFND>(
          fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::ObjectSpaceManifestRootFND: {
      ds << *std::static_pointer_cast<ObjectSpaceManifestRootFND>(
          fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::RevisionManifestEndFND: {
      ds << *std::static_pointer_cast<RevisionManifestEndFND>(
          fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::RevisionManifestListStartFND: {
      ds << *std::static_pointer_cast<RevisionManifestListStartFND>(
          fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::RevisionManifestStart4FND: {
      ds << *std::static_pointer_cast<RevisionManifestStart4FND>(
          fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::RevisionManifestStart6FND: {
      ds << *std::static_pointer_cast<RevisionManifestStart6FND>(
          fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::RevisionManifestStart7FND: {
      ds << *std::static_pointer_cast<RevisionManifestStart7FND>(
          fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::RevisionRoleAndContextDeclarationFND: {
      ds << *std::static_pointer_cast<RevisionRoleAndContextDeclarationFND>(
          fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::RevisionRoleDeclarationFND: {
      ds << *std::static_pointer_cast<RevisionRoleDeclarationFND>(
          fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::RootObjectReference2FNDX: {
      ds << *std::static_pointer_cast<RootObjectReference2FNDX>(
          fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::RootObjectReference3FND: {
      ds << *std::static_pointer_cast<RootObjectReference3FND>(
          fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::DataSignatureGroupDefinitionFND: {
      ds << *std::static_pointer_cast<DataSignatureGroupDefinitionFND>(
          fileNode->getFnt());
      break;
    }

    case FileNodeTypeID::ChunkTerminatorFND: {
      ds << *std::static_pointer_cast<ChunkTerminatorFND>(fileNode->getFnt());
      break;
    }
    case FileNodeTypeID::GlobalIdTableEndFNDX: {
      ds << *std::static_pointer_cast<GlobalIdTableEndFNDX>(fileNode->getFnt());
      break;
    }


    case FileNodeTypeID::InvalidFND: {
      qWarning()
          << "Tried to write FileNode with InvalidFND. Should not happen.";
      break;
    }


    default:
      qDebug() << "FileNodeID: " << fileNode->getFileNodeID();
      qFatal("Fatal Error: FileNode of base type 0 has a fileNodeTypeID which "
             "switches to "
             "default. Should not happen.");
    }
  }
  else {
    // fileNode->baseType == 1
    // fileNode->baseType == 2
    switch (fileNode->getFileNodeTypeID()) {
    case FileNodeTypeID::FileDataStoreObjectReferenceFND: {
      auto cFnd = std::static_pointer_cast<FileDataStoreObjectReferenceFND>(
          fileNode->getFnt());

      ds << getFncrFromChunk(
          cFnd->getBlobRef(), fileNode->getStpFormatEnum(),
          fileNode->getCbFormatEnum());

      ds << cFnd->m_guidReference;
      break;
    }
    case FileNodeTypeID::HashedChunkDescriptor2FND: {
      auto cFnd = std::static_pointer_cast<HashedChunkDescriptor2FND>(
          fileNode->getFnt());
      ds << getFncrFromChunk(
          cFnd->getBlobRef(), fileNode->getStpFormatEnum(),
          fileNode->getCbFormatEnum());


      auto propSet = cFnd->getBlobRef().lock();

      auto data = std::make_unique<QByteArray>(propSet->getSizeInFile(), '\0');
      QDataStream data_ds(data.get(), QIODevice::WriteOnly);
      data_ds.setByteOrder(QDataStream::LittleEndian);
      if (propSet != nullptr) {
        writeObjectSpaceObjectPropSet(data_ds, propSet);
      }

      const QByteArray md5hash =
          QCryptographicHash::hash(*data, QCryptographicHash::Md5);
      cFnd->setGuidHash(md5hash);

      ds.writeRawData(md5hash.data(), cFnd->guidHashWidth);
      break;
    }
    case FileNodeTypeID::ObjectDataEncryptionKeyV2FNDX: {
      auto cFnd = std::static_pointer_cast<ObjectDataEncryptionKeyV2FNDX>(
          fileNode->getFnt());
      ds << getFncrFromChunk(
          cFnd->getBlobRef(), fileNode->getStpFormatEnum(),
          fileNode->getCbFormatEnum());
      break;
    }
    case FileNodeTypeID::ObjectDeclaration2LargeRefCountFND: {
      auto cFnd = std::static_pointer_cast<ObjectDeclaration2LargeRefCountFND>(
          fileNode->getFnt());
      ds << getFncrFromChunk(
          cFnd->getBlobRef(), fileNode->getStpFormatEnum(),
          fileNode->getCbFormatEnum());
      ds << cFnd->getBody();
      ds << cFnd->getCRef();
      break;
    }
    case FileNodeTypeID::ObjectDeclaration2RefCountFND: {
      auto cFnd = std::static_pointer_cast<ObjectDeclaration2RefCountFND>(
          fileNode->getFnt());
      ds << getFncrFromChunk(
          cFnd->getBlobRef(), fileNode->getStpFormatEnum(),
          fileNode->getCbFormatEnum());
      ds << cFnd->getBody();
      ds << cFnd->getCRef();
      break;
    }
    case FileNodeTypeID::ObjectDeclarationWithRefCount2FNDX: {
      auto cFnd = std::static_pointer_cast<ObjectDeclarationWithRefCount2FNDX>(
          fileNode->getFnt());
      ds << getFncrFromChunk(
          cFnd->getObjectRef(), fileNode->getStpFormatEnum(),
          fileNode->getCbFormatEnum());
      ds << cFnd->getBody();
      ds << cFnd->getCRef();
      break;
    }
    case FileNodeTypeID::ReadOnlyObjectDeclaration2LargeRefCountFND: {
      auto cFnd =
          std::static_pointer_cast<ReadOnlyObjectDeclaration2LargeRefCountFND>(
              fileNode->getFnt());
      // base
      ds << getFncrFromChunk(
          cFnd->getBlobRef(), fileNode->getStpFormatEnum(),
          fileNode->getCbFormatEnum());
      ds << cFnd->getBody();
      ds << cFnd->getCRef();

      auto propSet = cFnd->getBlobRef().lock();


      auto data = std::make_unique<QByteArray>(propSet->getSizeInFile(), '\0');
      QDataStream data_ds(data.get(), QIODevice::WriteOnly);
      data_ds.setByteOrder(QDataStream::LittleEndian);
      if (propSet != nullptr) {
        writeObjectSpaceObjectPropSet(data_ds, propSet);
      }

      /*
      qDebug() << "\nReadOnlyObjectDeclaration2LargeRefCountFND\nData:\n"
               << data->toHex();
      */

      const QByteArray md5hash =
          QCryptographicHash::hash(*data, QCryptographicHash::Md5);
      cFnd->setMd5hash(md5hash);

      /*
      qDebug() << "Original Md5 hash:\n" << cFnd->getMd5hash().toHex();
      qDebug() << "Computed Md5 hash:\n" << md5hash.toHex();
      */

      ds.writeRawData(md5hash.data(), cFnd->md5HashSize);
    }
    case FileNodeTypeID::ReadOnlyObjectDeclaration2RefCountFND: {
      auto cFnd =
          std::static_pointer_cast<ReadOnlyObjectDeclaration2RefCountFND>(
              fileNode->getFnt());
      ds << getFncrFromChunk(
          cFnd->getBlobRef(), fileNode->getStpFormatEnum(),
          fileNode->getCbFormatEnum());
      ds << cFnd->getBody();
      ds << cFnd->getCRef();

      auto propSet = cFnd->getBlobRef().lock();

      auto data = std::make_unique<QByteArray>(propSet->getSizeInFile(), '\0');
      QDataStream data_ds(data.get(), QIODevice::WriteOnly);
      data_ds.setByteOrder(QDataStream::LittleEndian);
      if (propSet != nullptr) {
        writeObjectSpaceObjectPropSet(data_ds, propSet);
      }

      /*
      qInfo() << "\nReadOnlyObjectDeclaration2RefCountFND\nData:\n"
              << data->toHex();
      */

      const QByteArray md5hash =
          QCryptographicHash::hash(*data, QCryptographicHash::Md5);
      cFnd->setMd5hash(md5hash);
      /*
      qInfo() << "Original Md5 hash:\n" << cFnd->getMd5hash().toHex();
      qInfo() << "Computed Md5 hash:\n" << md5hash.toHex();
      */

      ds.writeRawData(md5hash.data(), cFnd->md5HashSize);
      break;
    }
    case FileNodeTypeID::ObjectDeclarationWithRefCountFNDX: {
      auto cFnd = std::static_pointer_cast<ObjectDeclarationWithRefCountFNDX>(
          fileNode->getFnt());
      ds << getFncrFromChunk(
          cFnd->getObjectRef(), fileNode->getStpFormatEnum(),
          fileNode->getCbFormatEnum());
      ds << cFnd->getBody();
      ds << cFnd->getCRef();
      break;
    }
    case FileNodeTypeID::ObjectInfoDependencyOverridesFND: {
      auto cFnd = std::static_pointer_cast<ObjectInfoDependencyOverridesFND>(
          fileNode->getFnt());

      /// \todo likely contains bugs

      auto ref = cFnd->getRef();

      if (!ref.expired()) {

        auto fncr = getFncrFromChunk(
            ref, fileNode->getStpFormatEnum(), fileNode->getCbFormatEnum());
        ds << fncr;
      }
      else {
        ds << FileNodeChunkReference(
            fileNode->getStpFormatEnum(), fileNode->getCbFormatEnum(),
            FCR_INIT::NIL);
        ds << cFnd->getData();
      }

      break;
    }
    case FileNodeTypeID::ObjectRevisionWithRefCount2FNDX: {
      auto cFnd = std::static_pointer_cast<ObjectRevisionWithRefCount2FNDX>(
          fileNode->getFnt());

      ds << getFncrFromChunk(
          cFnd->getRef(), fileNode->getStpFormatEnum(),
          fileNode->getCbFormatEnum());
      ds << cFnd->getOid();

      quint32 composite{0};

      composite += static_cast<quint32>(cFnd->getFHasOidReferences());
      composite += static_cast<quint32>(cFnd->getFHasOsidReferences() << 1u);

      ds << composite;

      ds << cFnd->getCRef();

      break;
    }
    case FileNodeTypeID::ObjectRevisionWithRefCountFNDX: {
      auto cFnd = std::static_pointer_cast<ObjectRevisionWithRefCountFNDX>(
          fileNode->getFnt());

      ds << getFncrFromChunk(
          cFnd->getRef(), fileNode->getStpFormatEnum(),
          fileNode->getCbFormatEnum());
      ds << cFnd->getOid();


      quint8 composite = cFnd->getCRef() >> 2u;
      composite += static_cast<quint32>(cFnd->getFHasOidReferences());
      composite += static_cast<quint32>(cFnd->getFHasOsidReferences() << 1u);

      ds << composite;

      break;
    }


    case FileNodeTypeID::FileDataStoreListReferenceFND: {
      auto cFnd = std::static_pointer_cast<FileDataStoreListReferenceFND>(
          fileNode->getFnt());

      ds << getFncrFromChunk(
          cFnd->getRef(), fileNode->getStpFormatEnum(),
          fileNode->getCbFormatEnum());
      break;
    }

    case FileNodeTypeID::ObjectGroupListReferenceFND: {
      auto cFnd = std::static_pointer_cast<ObjectGroupListReferenceFND>(
          fileNode->getFnt());
      ds << getFncrFromChunk(
          cFnd->getRef(), fileNode->getStpFormatEnum(),
          fileNode->getCbFormatEnum());

      ds << cFnd->getObjectGroupID();
      break;
    }

    case FileNodeTypeID::ObjectSpaceManifestListReferenceFND: {
      auto cFnd = std::static_pointer_cast<ObjectSpaceManifestListReferenceFND>(
          fileNode->getFnt());
      ds << getFncrFromChunk(
          cFnd->getRef(), fileNode->getStpFormatEnum(),
          fileNode->getCbFormatEnum());

      ds << cFnd->getGosid();
      break;
    }
    case FileNodeTypeID::RevisionManifestListReferenceFND: {
      auto cFnd = std::static_pointer_cast<RevisionManifestListReferenceFND>(
          fileNode->getFnt());
      ds << getFncrFromChunk(
          cFnd->getRef(), fileNode->getStpFormatEnum(),
          fileNode->getCbFormatEnum());
      break;
    }

    default:
      qInfo() << "FileNodeID: " << fileNode->getFileNodeID();
      qFatal("Fatal Error: FileNode of base type 1 has a fileNodeTypeID which "
             "switches to "
             "default. Should not happen.");
    }
  }


  return true;
}


bool RevisionStoreFileWriter::writeFileNodeListFragment(
    QDataStream& ds, FileNodeListFragment_SPtr_t& fileNodeListFragment)
{
  // if byte order is big endian, change to little endian
  if (ds.byteOrder() == QDataStream::BigEndian) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }


  ds << FileNodeListFragment::header_magic_id;
  ds << fileNodeListFragment->getFileNodeListID();
  ds << fileNodeListFragment->getNFragmentSequence();

  for (auto& fn : fileNodeListFragment->getFileNodes()) {
    writeFileNode(ds, fn);
  }

  quint32 size = fileNodeListFragment->getPaddingLength();

  const quint8 zeros8{};
  while (size > 0) {
    ds << zeros8;
    --size;
  }


  ds << getFcr64x32FromChunk(fileNodeListFragment->getNextFragment());
  ds << FileNodeListFragment::footer_magic_id;

  return true;
}


bool RevisionStoreFileWriter::writeFreeChunkListFragment(
    QDataStream& ds, FreeChunkListFragment_SPtr_t freeChunklistFragment)
{
  // if byte order is big endian, change to little endian
  if (ds.byteOrder() == QDataStream::BigEndian) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }


  ds << getFcr64x32FromChunk(freeChunklistFragment->getFcrNextFragment());

  for (const auto& entry : freeChunklistFragment->getFcrFreeChunks()) {
    if (!entry.expired()) {
      ds << getFcr64FromChunk(entry);
    }
  }

  return true;
}

bool RevisionStoreFileWriter::writeFreeChunk(
    QDataStream& ds, FreeChunk_SPtr_t freeChunk)
{

  quint64 size = freeChunk->getSize();


  // trying to split padding into managable sectors
  if (size > 4096) {
    const std::array<char, 4096> buffer4k{};
    while (size / 4096 > 0) {
      ds.writeRawData(buffer4k.data(), 4096);
      size -= 4096;
    }
  }

  const quint64 zeros64{};
  while (size / 64 > 0) {
    ds << zeros64;
    size -= 64;
  }

  const quint8 zeros8{};
  while (size > 0) {
    ds << zeros8;
    --size;
  }

  return true;
}

bool RevisionStoreFileWriter::writeFileDataStoreObject(
    QDataStream& ds, FileDataStoreObject_SPtr_t fileDataStoreObject)
{
  // if byte order is big endian, change to little endian
  if (ds.byteOrder() == QDataStream::BigEndian) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  ds << *fileDataStoreObject;

  return true;
}

bool RevisionStoreFileWriter::writeObjectSpaceObjectPropSet(
    QDataStream& ds, ObjectSpaceObjectPropSet_SPtr_t propSet)
{
  // if byte order is big endian, change to little endian
  if (ds.byteOrder() == QDataStream::BigEndian) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  ds << propSet->getOIDs();
  if (propSet->getOIDs().header().OsidStream_isNotPresent() == false) {
    ds << propSet->getOSIDs();

    if (propSet->getOSIDs().header().ExtendedStream_isPresent() == true) {
      ds << propSet->getContextIDs();
    }
  }
  ds << propSet->getBody();


  /// \todo compute paddingLength from content
  quint8 padding = propSet->getPaddingLength();
  const quint8 zeros8{};
  while (padding > 0) {
    ds << zeros8;
    --padding;
  }

  return true;
}

bool RevisionStoreFileWriter::writeObjectSpaceObjectPropSetUnpadded(
    QDataStream& ds, ObjectSpaceObjectPropSet_SPtr_t propSet)
{
  // if byte order is big endian, change to little endian
  if (ds.byteOrder() == QDataStream::BigEndian) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  ds << propSet->getOIDs();
  if (propSet->getOIDs().header().OsidStream_isNotPresent() == false) {
    ds << propSet->getOSIDs();

    if (propSet->getOSIDs().header().ExtendedStream_isPresent() == true) {
      ds << propSet->getContextIDs();
    }
  }
  ds << propSet->getBody();

  return true;
}


bool RevisionStoreFileWriter::writeObjectInfoDependencyOverrideData(
    QDataStream& ds, ObjectInfoDependencyOverrideData_SPtr_t data)
{
  // if byte order is big endian, change to little endian
  if (ds.byteOrder() == QDataStream::BigEndian) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }


  ds << *data;

  return true;
}

bool RevisionStoreFileWriter::writeEncryptedData(
    QDataStream& ds, EncryptedData_SPtr_t encryptedData)
{
  // if byte order is big endian, change to little endian
  if (ds.byteOrder() == QDataStream::BigEndian) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  ds << encryptedData->header;

  ds.writeRawData(
      encryptedData->getData().data(), encryptedData->getData().size());
  ds << encryptedData->footer;

  return true;
}


/// writting 0xee into stream with the size of the unparsed chunk
bool RevisionStoreFileWriter::writeUnparsedChunk(
    QDataStream& ds, Chunkable_SPtr_t chunk)
{

  quint64 size = chunk->getInitialCb();

  const quint8 filling{0xee};
  while (size > 0) {
    ds << filling;
    --size;
  }

  return true;
}

void RevisionStoreFileWriter::computeTransactionEntryCRCs()
{
  auto toHash = std::make_unique<QByteArray>();

  QDataStream data_ds(toHash.get(), QIODevice::WriteOnly);
  data_ds.setByteOrder(QDataStream::LittleEndian);

  for (auto& fragment : m_revStoreFile->getTransactionLogs()) {
    if (fragment.lock() == nullptr) {
      break;
    }

    auto cFragment = fragment.lock();

    for (auto& entry : cFragment->getSizeTable()) {

      quint32 currentSrcID = (entry)->getSrcID();

      if (currentSrcID == 0x1) {
        entry->setTransactionEntrySwitch(Crc32::computeCRC(*toHash));
      }

      data_ds << *entry;
    }
  }
}

quint64 RevisionStoreFileWriter::stpFromChunk(Chunkable_WPtr_t chunk)
{
  if (chunk.expired()) {
    return UINT64_MAX;
  }
  else {
    auto lchunk = chunk.lock();

    // if chunk is a FileNode, we must first sum up to the parent
    // FileNodeListFragment
    if (lchunk->type() == RevisionStoreChunkType::FileNode) {
      quint64 stp = 0;
      auto fileNodeListFragmentChunk =
          std::static_pointer_cast<FileNode>(lchunk)->getParent().lock();

      quint64 subtotal =
          stpTillIterator(m_revStoreFile->chunks(), fileNodeListFragmentChunk);

      // now summing up within the FileNodeListFragment
      stp += FileNodeListFragment::headerSize;


      auto fileNodes = fileNodeListFragmentChunk->getFileNodes();

      subtotal += stpTillIterator(fileNodes, lchunk);

      if (subtotal != UINT64_MAX) {
        return stp + subtotal;
      }
      else {
        return UINT64_MAX;
      }
    }
    else {
      return stpTillIterator(m_revStoreFile->chunks(), chunk);
    }
  }
}

template <typename Chunkably_SPtr_t>
quint64 RevisionStoreFileWriter::stpTillIterator(
    std::list<Chunkably_SPtr_t>& list, Chunkable_WPtr_t chunk)
{
  if (chunk.expired()) {
    return UINT64_MAX;
  }
  else {
    auto lchunk = chunk.lock();

    auto it = std::find(list.begin(), list.end(), lchunk);

    auto addCb = [](quint64 a, Chunkably_SPtr_t b) {
      return std::move(a) + b->getSizeInFile();
    };

    return std::accumulate(
        list.begin(), it, RevisionStoreFileHeader::sizeInFile, addCb);
  }
}

FileChunkReference64x32 RevisionStoreFileWriter::getFcr64x32FromChunk(
    Chunkable_WPtr_t chunk, FCR_INIT preferedState)
{
  if (chunk.expired()) {
    return FileChunkReference64x32(preferedState);
  }
  else {
    auto lchunk = chunk.lock();
    quint64 stp = stpFromChunk(chunk);
    return FileChunkReference64x32(stp, lchunk->getSizeInFile());
  }
}

FileChunkReference64 RevisionStoreFileWriter::getFcr64FromChunk(
    Chunkable_WPtr_t chunk, FCR_INIT preferedState)
{
  if (chunk.expired()) {
    return FileChunkReference64(preferedState);
  }
  else {
    auto lchunk = chunk.lock();
    quint64 stp = stpFromChunk(chunk);
    return FileChunkReference64(stp, lchunk->getSizeInFile());
  }
}

FileNodeChunkReference RevisionStoreFileWriter::getFncrFromChunk(
    Chunkable_WPtr_t chunk, FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat,
    FCR_INIT preferedState)
{
  if (chunk.expired()) {
    return FileNodeChunkReference(
        FNCR_STP_FORMAT::UNCOMPRESED_8BYTE, FNCR_CB_FORMAT::UNCOMPRESED_4BYTE,
        preferedState);
  }
  else {
    auto lchunk = chunk.lock();

    FileNodeChunkReference fncr(stpFormat, cbFormat, preferedState);

    fncr.setStp(stpFromChunk(lchunk));
    fncr.setCb(lchunk->getSizeInFile());


    return fncr;
  }
}

} // namespace priv
} // namespace libmson
