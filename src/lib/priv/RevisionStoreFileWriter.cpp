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


namespace libmson {
namespace priv {


RevisionStoreFileWriter::RevisionStoreFileWriter(
    std::shared_ptr<RevisionStoreFile>& revisionStoreFile)
    : m_revStoreFile(revisionStoreFile)
{
}

bool RevisionStoreFileWriter::write(QDataStream& ds)
{
  auto chunks = m_revStoreFile->chunks();


  if (chunks.size() < 1) {
    qFatal("No chunks to write in RevisionStoreFile.");
  }


  //  auto it = chunks.begin();


  //  // write header
  //  if (!writeRevisionStoreFileHeader(
  //          ds, std::static_pointer_cast<RevisionStoreFileHeader>(*it))) {
  //    return false;
  //  }
  //  ++it;

  // then write the rest

  for (auto it = chunks.begin(); it != chunks.end(); ++it) {
    if (!writeChunk(ds, *it)) {
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


  quint64 totalFileSize = 0;

  auto addCb = [](quint64 a, Chunkable_SPtr_t b) {
    return std::move(a) + b->getSizeInFile();
  };

  totalFileSize = std::accumulate(
      m_revStoreFile->m_chunks.begin(), m_revStoreFile->m_chunks.end(), 0,
      addCb);

  // Updating the header;
  header->cbExpectedFileLength = totalFileSize;
  header->crcName = Crc32::computeCrcName(m_revStoreFile->m_fileName);
  /// \todo update cTransactionsInLog

  ds << header->guidFileType;
  ds << header->guidFile;
  ds << header->v_guidLegacyFileVersion;
  ds << header->v_guidFileFormat;
  // 0x0040
  ds << header->ffvLastWriterVersion;
  ds << header->ffvOldestWriterVersion;
  ds << header->ffvNewestWriterVersion;
  ds << header->ffvOldestReader;

  // 0x0050

  // fcrLegacyFreeChunkList
  ds << FileChunkReference32(FCR_INIT::ZERO);
  // fcrLegacyTransactionLog
  ds << FileChunkReference32(FCR_INIT::NIL);

  // 0x0060
  ds << header->cTransactionsInLog;

  quint32 cbLegacyExpectedFileLength = 0u;
  ds << cbLegacyExpectedFileLength;

  ds << header->rgbPlaceholder;

  // fcrLegacyFileNodeListRoot
  ds << FileChunkReference32(FCR_INIT::NIL);

  quint32 cbLegacyFreeSpaceInFreeChunkList = 0u;
  ds << cbLegacyFreeSpaceInFreeChunkList;

  ds << header->fNeedsDefrag;
  ds << header->fRepairedFile;
  ds << header->fNeedsGarbageCollect;
  ds << header->fHasNoEmbeddedFileObjects;

  // 0x0080
  ds << header->guidAncestor;

  // 0x0090
  ds << header->crcName;

  // fcrHashedChunkList
  ds << getFcr64x32FromChunk(header->fcrHashedChunkList);

  // 0x00A0
  // fcrTransactionLog
  ds << getFcr64x32FromChunk(header->fcrTransactionLog);

  // fcrFileNodeListRoot
  ds << getFcr64x32FromChunk(header->fcrFileNodeListRoot);

  // fcrFreeChunkList
  ds << getFcr64x32FromChunk(header->fcrFreeChunkList);

  // 0x00C4
  ds << header->cbExpectedFileLength;
  ds << header->cbFreeSpaceInFreeChunkList;
  ds << header->guidFileVersion;
  ds << header->nFileVersionGeneration;
  ds << header->guidDenyReadFileVersion;
  ds << header->grfDebugLogFlags;

  // 0x0100
  // fcrDebugLog
  ds << FileChunkReference64x32(FCR_INIT::ZERO);

  // fcrAllocVerificationFreeChunkList
  ds << FileChunkReference64x32(FCR_INIT::ZERO);

  ds << header->bnCreated;
  ds << header->bnLastWroteToThisFile;
  // 0x0120
  ds << header->bnOldestWritten;
  ds << header->bnNewestWritten;

  const std::array<char, RevisionStoreFileHeader::def_reservedHeaderTailLength>
      padding{};

  ds.writeRawData(
      padding.data(), RevisionStoreFileHeader::def_reservedHeaderTailLength);

  return true;
}

bool RevisionStoreFileWriter::writeTransactionLogFragment(
    QDataStream& ds, TransactionLogFragment_SPtr_t transactionLogFragment)
{

  for (const auto& entry : transactionLogFragment->getSizeTable()) {
    ds << *entry;
  }

  ds << getFcr64x32FromChunk(
      transactionLogFragment->getNextFragment(), FCR_INIT::ZERO);


  quint8 zeros{};
  for (quint8 i = 0; i < transactionLogFragment->getPaddingLength(); i++) {
    ds << zeros;
  }

  return true;
}

bool RevisionStoreFileWriter::writeFileNode(
    QDataStream& ds, FileNode_SPtr_t& fileNode)
{
  // updating self size
  fileNode->fileNodeSize = fileNode->getSizeInFile();

  quint32 composite;

  // reserved, must be 1, MS-ONESTORE section 2.4.3 FileNode
  composite = 1u << fNshiftReserved;

  composite += (fileNode->baseType & fNmaskBaseType) << fNshiftBaseType;
  composite += (fileNode->cbFormat & fNmaskCbFormat) << fNshiftCbFormat;
  composite += (fileNode->stpFormat & fNmaskStpFormat) << fNshiftStpFormat;
  composite += (fileNode->fileNodeSize & fNmaskFileNodeSize)
               << fNshiftFileNodeSize;
  composite += (fileNode->fileNodeID & fNmaskFileNodeID) << fNshiftFileNodeID;

  ds << composite;

  if (fileNode->baseType == 0) {
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
    default:
      qInfo() << "FileNodeID: " << fileNode->getFileNodeID();
      qFatal("FileNode of base type 0 has a fileNodeTypeID which switches to "
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

      ds << cFnd->m_guidHash;
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
          cFnd->getBase().getBlobRef(), fileNode->getStpFormatEnum(),
          fileNode->getCbFormatEnum());
      ds << cFnd->getBase().getBody();
      ds << cFnd->getBase().getCRef();

      // #################################################################################
      /// \todo make new md5hash
      // #################################################################################
      ds << cFnd->getMd5hash();
      break;
    }
    case FileNodeTypeID::ReadOnlyObjectDeclaration2RefCountFND: {
      auto cFnd =
          std::static_pointer_cast<ReadOnlyObjectDeclaration2RefCountFND>(
              fileNode->getFnt());
      ds << getFncrFromChunk(
          cFnd->getBase().getBlobRef(), fileNode->getStpFormatEnum(),
          fileNode->getCbFormatEnum());
      ds << cFnd->getBase().getBody();
      ds << cFnd->getBase().getCRef();
      // #################################################################################
      /// \todo make new md5hash
      // #################################################################################
      ds << cFnd->getMd5hash();
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
        ds << getFncrFromChunk(
            ref, fileNode->getStpFormatEnum(), fileNode->getCbFormatEnum());
      }
      else {
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

      quint32 temp{0};

      temp += static_cast<quint32>(cFnd->getFHasOidReferences());
      temp += static_cast<quint32>(cFnd->getFHasOsidReferences() << 1);

      ds << temp;

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


      quint8 temp = cFnd->getCRef() >> 2;
      temp += static_cast<quint32>(cFnd->getFHasOidReferences());
      temp += static_cast<quint32>(cFnd->getFHasOsidReferences() << 1);

      ds << temp;

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
      qFatal("FileNode of base type 1 has a fileNodeTypeID which switches to "
             "default. Should not happen.");
    }
  }


  return true;
}


bool RevisionStoreFileWriter::writeFileNodeListFragment(
    QDataStream& ds, FileNodeListFragment_SPtr_t& fileNodeListFragment)
{


  ds << fileNodeListFragment->header_magic_id;
  ds << fileNodeListFragment->m_fileNodeListID;
  ds << fileNodeListFragment->m_nFragmentSequence;

  for (auto& fn : fileNodeListFragment->m_fileNodes) {
    writeFileNode(ds, fn);
  }

  // not memory friendly. maybe looping is more straight forward here.¸
  ds.device()->write(QByteArray(fileNodeListFragment->m_paddingLength, '\0'));
  ds << getFcr64x32FromChunk(fileNodeListFragment->getNextFragment());
  ds << fileNodeListFragment->footer_magic_id;

  return true;
}


bool RevisionStoreFileWriter::writeFreeChunkListFragment(
    QDataStream& ds, FreeChunkListFragment_SPtr_t freeChunklistFragment)
{


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

  ds << fileDataStoreObject->getGuidHeader();
  ds << fileDataStoreObject->getCbLength();

  const quint32 unused{};
  ds << unused;
  const quint64 reserved{};
  ds << reserved;

  ds << fileDataStoreObject->getFileData();


  ds << fileDataStoreObject->getGuidFooter();


  return true;
}

bool RevisionStoreFileWriter::writeObjectSpaceObjectPropSet(
    QDataStream& ds, ObjectSpaceObjectPropSet_SPtr_t propSet)
{

  ds << propSet->getOIDs();
  if (propSet->getOIDs().header().OsidStream_isNotPresent() == false) {
    ds << propSet->getOSIDs();

    if (propSet->getOSIDs().header().ExtendedStream_isPresent() == true) {
      ds << propSet->getContextIDs();
    }
  }
  ds << propSet->getBody();

  QByteArray padding;

  ds << padding.append('\0', propSet->getPaddingLength());

  return true;
}

bool RevisionStoreFileWriter::writeObjectInfoDependencyOverrideData(
    QDataStream& ds, ObjectInfoDependencyOverrideData_SPtr_t data)
{
  ds << *data;

  return true;
}

bool RevisionStoreFileWriter::writeEncryptedData(
    QDataStream& ds, EncryptedData_SPtr_t encryptedData)
{
  ds << encryptedData->header;
  ds << encryptedData->getData();
  ds << encryptedData->footer;

  return true;
}


/// writting zeros into stream with the size of the unparsed chunk
bool RevisionStoreFileWriter::writeUnparsedChunk(
    QDataStream& ds, Chunkable_SPtr_t chunk)
{

  quint64 size = chunk->getInitialCb();


  //  // trying to split padding into managable sectors

  //  if (size > 4096) {
  //    const std::array<char, 4096> buffer4k{};
  //    while (size / 4096 > 0) {
  //      ds.writeRawData(buffer4k.data(), 4096);
  //      size -= 4096;
  //    }
  //  }

  //  const quint64 zeros64{};
  //  while (size / 64 > 0) {
  //    ds << zeros64;
  //    size -= 64;
  //  }

  //  const quint8 zeros8{};
  //  while (size > 0) {
  //    ds << zeros8;
  //    --size;
  //  }


  /// \todo revert writeUnparsedChunk to section writer after debugging
  /// finished
  const quint8 zeros8{0xee};
  while (size > 0) {
    ds << zeros8;
    --size;
  }

  return true;
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

    return std::accumulate(list.begin(), it, 0, addCb);
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

    FileNodeChunkReference fncr(stpFormat, cbFormat);

    fncr.setStp(stpFromChunk(chunk));
    fncr.setCb(lchunk->getSizeInFile());


    return fncr;
  }
}

} // namespace priv
} // namespace libmson
