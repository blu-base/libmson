#include "RevisionStoreFileParser.h"

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

#include "utils/ChunkableUtils.h"
#include "utils/Helper.h"

namespace libmson {
namespace priv {

RevisionStoreFileParser::RevisionStoreFileParser(
    QDataStream& inputStream, const QString& fileName)
    : m_ds(inputStream), m_file(std::make_shared<RevisionStoreFile>())
{
  m_file->m_fileName = fileName;
}


std::shared_ptr<RevisionStoreFile> RevisionStoreFileParser::parse()
{
  auto header = parseRevisionStoreFileHeader(m_ds).lock();


  // Parsing FreeChunkList
  parseFreeChunkListFragments(m_ds, header->getFcrFreeChunkList().lock());

  // Parsing TransactionLog
  parseTransactionLogFragment(m_ds, header->getFcrTransactionLog().lock());

  // Parsing RootFileNodeList
  m_file->m_rootFileNodeList =
      parseFileNodeList(m_ds, header->fcrFileNodeListRoot.lock());

  // search for ObjectSpaceManifestRootFND in RootFileNodeList and verify only
  // one ObjectSpaceManifestRootFND is present
  for (const auto& frag : m_file->m_rootFileNodeList) {
    for (const auto& fn : frag.lock()->getFileNodes()) {
      if (fn->getFileNodeTypeID() ==
          FileNodeTypeID::ObjectSpaceManifestRootFND) {

        if (m_file->m_objectSpaceManifestRoot.lock() == nullptr) {
          m_file->m_objectSpaceManifestRoot = fn;
        }
        else {
          qWarning("There is an additional ObjectSpaceManifestRootFND present");
        }
      }
    }
  }

  // Parsing HashedChunkList
  m_file->m_hashedChunkListFragments =
      parseFileNodeList(m_ds, header->fcrHashedChunkList.lock());


  // Traverse RootFileNodeList to parse ObjectSpaceManifests

  for (const auto& frag : m_file->m_rootFileNodeList) {
    for (const auto& fn : frag.lock()->getFileNodes()) {
      if (fn->getFileNodeTypeID() ==
          FileNodeTypeID::ObjectSpaceManifestListReferenceFND) {

        auto fndRef =
            std::static_pointer_cast<ObjectSpaceManifestListReferenceFND>(
                fn->fnt);
        m_file->m_objectSpaceManifests.push_back(fndRef->getRef());
      }
    }
  }


  /*
  //    for (const auto &entry : objectSpaceManifestListReferences) {
  //      const FileNodeChunkReference osmlr =
  //
  std::dynamic_pointer_cast<ObjectSpaceManifestListReferenceFND>(entry->getFnt())
  //              ->getRef();

  //      std::shared_ptr<ObjectSpaceManifestList> osml =
  //          std::make_shared<ObjectSpaceManifestList>(osmlr);

  //      ds >> *osml;

  //      m_objectSpaceManifestList.push_back(osml);
  //    }
  */

  //  for (auto& manifest : objectSpaceManifests) {
  //    m_file->m_objectSpaceManifests.push_back(parseFileNodeList(m_ds,
  //    std::static_pointer_cast<FileNodeListFragment_WPtr_t>(manifest)));
  //  }

  // Traverse RevisionManifests and stuff


  // Traverse RootFileNodeList to parse FileDataStoreList
  for (const auto& frag : m_file->m_rootFileNodeList) {
    for (const auto& fn : frag.lock()->getFileNodes()) {
      if (fn->getFileNodeTypeID() ==
          FileNodeTypeID::FileDataStoreListReferenceFND) {
        if (m_file->m_fileDataStoreListReference.lock() == nullptr) {
          m_file->m_fileDataStoreListReference = fn;
        }
        else {
          qWarning(
              "There is an additional FileDataStoreListReferenceFND present");
        }
      }
    }
  }

  auto fdslr = m_file->m_fileDataStoreListReference.lock();

  if (fdslr != nullptr) {

    auto fdslrFnd =
        std::static_pointer_cast<FileDataStoreListReferenceFND>(fdslr->fnt);


    // collecting references to parse FileDataStoreObjects

    std::vector<FileDataStoreObject_WPtr_t> fileDataStoreObjects{};

    auto fragments = parseFileNodeList(m_ds, fdslrFnd->getRef());

    auto fragment = fragments.at(0).lock();
    while (fragment != nullptr) {
      for (const auto& fn : fragment->getFileNodes()) {
        if (fn->getFileNodeTypeID() ==
            FileNodeTypeID::FileDataStoreObjectReferenceFND) {

          fileDataStoreObjects.push_back(
              std::static_pointer_cast<FileDataStoreObjectReferenceFND>(
                  fn->getFnt())
                  ->getBlobRef());
        }
      }

      fragment = fragment->getNextFragment().lock();
    }

    for (auto fileReference : fileDataStoreObjects) {
      parseFileDataStoreObject(m_ds, fileReference);
    }
  }


  return m_file;
}

void RevisionStoreFileParser::parseEncryptedData(
    QDataStream& ds, EncryptedData_WPtr_t chunk)
{
  auto data = chunk.lock();

  if (data != nullptr) {
    qint64 originalStp = ds.device()->pos();


    ds.device()->seek(data->getInitialStp());

    quint64 headerTest;
    ds >> headerTest;
    if (headerTest != EncryptedData::header) {
      qFatal("EncryptedData header is invalid.");
    }

    quint64 length = data->getInitialCb() - EncryptedData::minSizeInFile;


    data->m_data.resize(length);

    ds >> data->m_data;

    quint64 footerTest;
    ds >> footerTest;
    if (footerTest != EncryptedData::footer) {
      qFatal("EncryptedData footer is invalid.");
    }


    data->m_isParsed = true;

    ds.device()->seek(originalStp);
  }
}

RevisionStoreFileHeader_WPtr_t
RevisionStoreFileParser::parseRevisionStoreFileHeader(QDataStream& ds)
{

  if (m_ds.device()->bytesAvailable() < 0x400) {
    qWarning("File size insufficient to be OneNote file.");
    return RevisionStoreFileHeader_WPtr_t();
  }
  // if byte order is big endian, change to little endian
  if (m_ds.byteOrder() == QDataStream::BigEndian) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  auto header = std::make_shared<RevisionStoreFileHeader>(
      0u, RevisionStoreFileHeader::sizeInFile);


  m_file->chunks().push_back(header);

  ds >> header->guidFileType;
  ds >> header->guidFile;
  ds >> header->guidLegacyFileVersion;
  if (header->guidLegacyFileVersion != header->v_guidLegacyFileVersion) {
    qWarning(
        "guidLegacyFileVersion of the RevisionStoreFileHeader is invalid.");
  }
  ds >> header->guidFileFormat;
  if (header->guidFileFormat != header->v_guidFileFormat) {
    qWarning("guidFileFormat of the RevisionStoreFileHeader is invalid.");
    return RevisionStoreFileHeader_WPtr_t();
  }
  ds >> header->ffvLastWriterVersion;
  ds >> header->ffvOldestWriterVersion;
  ds >> header->ffvNewestWriterVersion;
  ds >> header->ffvOldestReader;

  FileChunkReference32 fcrLegacyFreeChunkList;
  ds >> fcrLegacyFreeChunkList;
  if (!fcrLegacyFreeChunkList.is_fcrZero()) {
    qWarning("fcrLegacyFreeChunkList of the RevisionStoreFileHeader is "
             "invalid.");
  }

  FileChunkReference32 fcrLegacyTransactionLog;
  ds >> fcrLegacyTransactionLog;
  if (!fcrLegacyTransactionLog.is_fcrNil()) {
    qWarning("fcrLegacyTransactionLog of the RevisionStoreFileHeader is "
             "invalid.");
  }

  ds >> header->cTransactionsInLog;

  quint32 cbLegacyExpectedFileLength;
  ds >> cbLegacyExpectedFileLength;
  if (cbLegacyExpectedFileLength != 0u) {
    qWarning("cbLegacyExpectedFileLength of the RevisionStoreFileHeader is "
             "invalid.");
  }

  ds >> header->rgbPlaceholder;

  FileChunkReference32 fcrLegacyFileNodeListRoot;
  ds >> fcrLegacyFileNodeListRoot;
  if (!fcrLegacyFileNodeListRoot.is_fcrNil()) {
    qWarning("fcrLegacyFileNodeListRoot of the RevisionStoreFileHeader is "
             "invalid.");
  }

  quint32 cbLegacyFreeSpaceInFreeChunkList;
  ds >> cbLegacyFreeSpaceInFreeChunkList;
  if (cbLegacyFreeSpaceInFreeChunkList != 0u) {
    qWarning("cbLegacyFreeSpaceInFreeChunkList of the RevisionStoreFileHeader "
             "is invalid.");
  }

  ds >> header->fNeedsDefrag;
  ds >> header->fRepairedFile;
  ds >> header->fNeedsGarbageCollect;
  ds >> header->fHasNoEmbeddedFileObjects;
  ds >> header->guidAncestor;
  ds >> header->crcName;

  FileChunkReference64x32 fcrHashedChunkList;
  ds >> fcrHashedChunkList;

  if (!fcrHashedChunkList.is_fcrNil() && !fcrHashedChunkList.is_fcrZero()) {


    auto fcrHashedChunkListFragment = std::make_shared<FileNodeListFragment>(
        fcrHashedChunkList.stp(), fcrHashedChunkList.cb());

    insertChunkSorted(m_file->chunks(), fcrHashedChunkListFragment);

    header->fcrHashedChunkList = fcrHashedChunkListFragment;
  }

  FileChunkReference64x32 fcrTransactionLog;
  ds >> fcrTransactionLog;
  if (!fcrTransactionLog.is_fcrNil() && !fcrTransactionLog.is_fcrZero()) {

    auto fcrTransactionLogFragment = std::make_shared<TransactionLogFragment>(
        fcrTransactionLog.stp(), fcrTransactionLog.cb());

    insertChunkSorted(m_file->chunks(), fcrTransactionLogFragment);

    header->fcrTransactionLog = fcrTransactionLogFragment;
  }

  FileChunkReference64x32 fcrFileNodeListRoot;
  ds >> fcrFileNodeListRoot;
  if (!fcrFileNodeListRoot.is_fcrNil() && !fcrFileNodeListRoot.is_fcrZero()) {

    auto fileNodeListRootChunk = std::make_shared<FileNodeListFragment>(
        fcrFileNodeListRoot.stp(), fcrFileNodeListRoot.cb());

    insertChunkSorted(m_file->chunks(), fileNodeListRootChunk);

    header->fcrFileNodeListRoot = fileNodeListRootChunk;
  }

  FileChunkReference64x32 fcrFreeChunkList;
  ds >> fcrFreeChunkList;
  if (!fcrFreeChunkList.is_fcrNil() && !fcrFreeChunkList.is_fcrZero()) {

    auto freeChunkListFragment = std::make_shared<FreeChunkListFragment>(
        fcrFreeChunkList.stp(), fcrFreeChunkList.cb());

    insertChunkSorted(m_file->chunks(), freeChunkListFragment);

    header->fcrFreeChunkList = freeChunkListFragment;
  }

  ds >> header->cbExpectedFileLength;
  ds >> header->cbFreeSpaceInFreeChunkList;
  ds >> header->guidFileVersion;
  ds >> header->nFileVersionGeneration;
  ds >> header->guidDenyReadFileVersion;
  ds >> header->grfDebugLogFlags;

  FileChunkReference64x32 fcrDebugLog;
  ds >> fcrDebugLog;
  if (!fcrDebugLog.is_fcrZero()) {
    qWarning("fcrLegacyFreeChunkList of the RevisionStoreFileHeader is "
             "invalid.");
  }

  FileChunkReference64x32 fcrAllocVerificationFreeChunkList;
  ds >> fcrAllocVerificationFreeChunkList;
  if (!fcrAllocVerificationFreeChunkList.is_fcrZero()) {
    qWarning("fcrLegacyFreeChunkList of the RevisionStoreFileHeader is "
             "invalid.");
  }

  ds >> header->bnCreated;
  ds >> header->bnLastWroteToThisFile;
  ds >> header->bnOldestWritten;
  ds >> header->bnNewestWritten;
  ds.skipRawData(header->def_reservedHeaderTailLength);


  header->m_isParsed = true;
  /// \todo further Validate header
  return header;
}

FileNode_SPtr_t RevisionStoreFileParser::parseFileNode(
    QDataStream& ds, const quint64 stp, FileNodeListFragment_WPtr_t parent)
{

  auto fn = std::make_shared<FileNode>(parent, stp, FileNode::minSizeInFile);


  if (ds.device()->bytesAvailable() < 4) {
    qWarning("Reached end of file stream while parsing FileNode");
  }

  {
    quint32 temp;
    ds >> temp;

    fn->baseType     = (temp >> fNshiftBaseType) & fNmaskBaseType;
    fn->cbFormat     = (temp >> fNshiftCbFormat) & fNmaskCbFormat;
    fn->stpFormat    = (temp >> fNshiftStpFormat) & fNmaskStpFormat;
    fn->fileNodeSize = (temp >> fNshiftFileNodeSize) & fNmaskFileNodeSize;
    fn->fileNodeID   = (temp >> fNshiftFileNodeID) & fNmaskFileNodeID;
  }
  fn->m_initialCb = fn->getFileNodeSize();
  // distinguish by baseType,
  // type 0 does not contain any reference to a chunk, and therefore can be
  // parsed trivially type 1 and type 2 do contain references and must cast
  // chunkContainer


  if (fn->baseType == 0) {

    switch (fn->getFileNodeTypeID()) {
    case FileNodeTypeID::ChunkTerminatorFND: {
      auto thisFnt = std::make_shared<ChunkTerminatorFND>(fn);
      break;
    }
    case FileNodeTypeID::DataSignatureGroupDefinitionFND: {
      auto thisFnt = std::make_shared<DataSignatureGroupDefinitionFND>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::GlobalIdTableEndFNDX: {
      auto thisFnt = std::make_shared<GlobalIdTableEndFNDX>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::GlobalIdTableEntry2FNDX: {
      auto thisFnt = std::make_shared<GlobalIdTableEntry2FNDX>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::GlobalIdTableEntry3FNDX: {
      auto thisFnt = std::make_shared<GlobalIdTableEntry3FNDX>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::GlobalIdTableEntryFNDX: {
      auto thisFnt = std::make_shared<GlobalIdTableEntryFNDX>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::GlobalIdTableStart2FND: {
      auto thisFnt = std::make_shared<GlobalIdTableStart2FND>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::GlobalIdTableStartFNDX: {
      auto thisFnt = std::make_shared<GlobalIdTableStartFNDX>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::ObjectDeclarationFileData3LargeRefCountFND: {
      auto thisFnt =
          std::make_shared<ObjectDeclarationFileData3LargeRefCountFND>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::ObjectDeclarationFileData3RefCountFND: {
      auto thisFnt =
          std::make_shared<ObjectDeclarationFileData3RefCountFND>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::ObjectGroupEndFND: {
      auto thisFnt = std::make_shared<ObjectGroupEndFND>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::ObjectGroupStartFND: {
      auto thisFnt = std::make_shared<ObjectGroupStartFND>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::ObjectSpaceManifestListStartFND: {
      auto thisFnt = std::make_shared<ObjectSpaceManifestListStartFND>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::ObjectSpaceManifestRootFND: {
      auto thisFnt = std::make_shared<ObjectSpaceManifestRootFND>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::RevisionManifestEndFND: {
      auto thisFnt = std::make_shared<RevisionManifestEndFND>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::RevisionManifestListStartFND: {
      auto thisFnt = std::make_shared<RevisionManifestListStartFND>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::RevisionManifestStart4FND: {
      auto thisFnt = std::make_shared<RevisionManifestStart4FND>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::RevisionManifestStart6FND: {
      auto thisFnt = std::make_shared<RevisionManifestStart6FND>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::RevisionManifestStart7FND: {
      auto thisFnt = std::make_shared<RevisionManifestStart7FND>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::RevisionRoleAndContextDeclarationFND: {
      auto thisFnt = std::make_shared<RevisionRoleAndContextDeclarationFND>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::RevisionRoleDeclarationFND: {
      auto thisFnt = std::make_shared<RevisionRoleDeclarationFND>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::RootObjectReference2FNDX: {
      auto thisFnt = std::make_shared<RootObjectReference2FNDX>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }
    case FileNodeTypeID::RootObjectReference3FND: {
      auto thisFnt = std::make_shared<RootObjectReference3FND>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
      break;
    }

    case FileNodeTypeID::NullFnd: {
      fn->fnt = nullptr;
      break;
    }


    default:
      qFatal("FileNode of base type 0 has a fileNodeTypeID which switches to "
             "default. Should not happen.");
    }
  }
  else


      if (fn->baseType == 1) {
    switch (fn->getFileNodeTypeID()) {
    case FileNodeTypeID::FileDataStoreObjectReferenceFND: {
      fn->fnt = std::make_shared<FileDataStoreObjectReferenceFND>(fn);

      auto currentFnt =
          std::static_pointer_cast<FileDataStoreObjectReferenceFND>(fn->fnt);

      FileNodeChunkReference blobRef(fn->stpFormat, fn->cbFormat);
      ds >> blobRef;
      if (!blobRef.is_fcrNil() && !blobRef.is_fcrZero()) {

        auto objectSpaceObjectPropSetChunk =
            std::make_shared<FileDataStoreObject>(blobRef.stp(), blobRef.cb());

        insertChunkSorted(m_file->chunks(), objectSpaceObjectPropSetChunk);

        currentFnt->m_blobRef = objectSpaceObjectPropSetChunk;
      }

      ds >> currentFnt->m_guidReference;

      break;
    }
    case FileNodeTypeID::HashedChunkDescriptor2FND: {
      fn->fnt = std::make_shared<HashedChunkDescriptor2FND>(fn);

      auto currentFnt =
          std::static_pointer_cast<HashedChunkDescriptor2FND>(fn->fnt);

      FileNodeChunkReference blobRef(fn->stpFormat, fn->cbFormat);
      ds >> blobRef;
      if (!blobRef.is_fcrNil() && !blobRef.is_fcrZero()) {

        auto objectSpaceObjectPropSetChunk =
            std::make_shared<ObjectSpaceObjectPropSet>(
                blobRef.stp(), blobRef.cb());

        insertChunkSorted(m_file->chunks(), objectSpaceObjectPropSetChunk);

        currentFnt->m_blobRef = objectSpaceObjectPropSetChunk;
      }

      ds >> currentFnt->m_guidHash;

      break;
    }
    case FileNodeTypeID::ObjectDataEncryptionKeyV2FNDX: {
      fn->fnt = std::make_shared<ObjectDataEncryptionKeyV2FNDX>(fn);

      auto currentFnt =
          std::static_pointer_cast<ObjectDataEncryptionKeyV2FNDX>(fn->fnt);

      FileNodeChunkReference blobRef(fn->stpFormat, fn->cbFormat);
      ds >> blobRef;
      if (!blobRef.is_fcrNil() && !blobRef.is_fcrZero()) {

        auto objectSpaceObjectPropSetChunk =
            std::make_shared<EncryptedData>(blobRef.stp(), blobRef.cb());

        insertChunkSorted(m_file->chunks(), objectSpaceObjectPropSetChunk);

        currentFnt->m_blobRef = objectSpaceObjectPropSetChunk;
      }

      break;
    }

    case FileNodeTypeID::ObjectDeclaration2LargeRefCountFND: {
      fn->fnt = std::make_shared<ObjectDeclaration2LargeRefCountFND>(fn);

      auto currentFnt =
          std::static_pointer_cast<ObjectDeclaration2LargeRefCountFND>(fn->fnt);

      FileNodeChunkReference blobRef(fn->stpFormat, fn->cbFormat);
      ds >> blobRef;
      if (!blobRef.is_fcrNil() && !blobRef.is_fcrZero()) {

        auto objectSpaceObjectPropSetChunk =
            std::make_shared<ObjectSpaceObjectPropSet>(
                blobRef.stp(), blobRef.cb());

        insertChunkSorted(m_file->chunks(), objectSpaceObjectPropSetChunk);

        currentFnt->m_blobRef = objectSpaceObjectPropSetChunk;
      }

      ds >> currentFnt->m_body;
      ds >> currentFnt->m_cRef;

      break;
    }

    case FileNodeTypeID::ObjectDeclaration2RefCountFND: {
      fn->fnt = std::make_shared<ObjectDeclaration2RefCountFND>(fn);

      auto currentFnt =
          std::static_pointer_cast<ObjectDeclaration2RefCountFND>(fn->fnt);

      FileNodeChunkReference blobRef(fn->stpFormat, fn->cbFormat);
      ds >> blobRef;
      if (!blobRef.is_fcrNil() && !blobRef.is_fcrZero()) {

        auto objectSpaceObjectPropSetChunk =
            std::make_shared<ObjectSpaceObjectPropSet>(
                blobRef.stp(), blobRef.cb());

        insertChunkSorted(m_file->chunks(), objectSpaceObjectPropSetChunk);

        currentFnt->m_blobRef = objectSpaceObjectPropSetChunk;
      }

      ds >> currentFnt->m_body;
      ds >> currentFnt->m_cRef;

      break;
    }
    case FileNodeTypeID::ObjectDeclarationWithRefCount2FNDX: {
      fn->fnt = std::make_shared<ObjectDeclarationWithRefCount2FNDX>(fn);

      auto currentFnt =
          std::static_pointer_cast<ObjectDeclarationWithRefCount2FNDX>(fn->fnt);

      FileNodeChunkReference blobRef(fn->stpFormat, fn->cbFormat);
      ds >> blobRef;
      if (!blobRef.is_fcrNil() && !blobRef.is_fcrZero()) {

        auto objectSpaceObjectPropSetChunk =
            std::make_shared<ObjectSpaceObjectPropSet>(
                blobRef.stp(), blobRef.cb());

        insertChunkSorted(m_file->chunks(), objectSpaceObjectPropSetChunk);

        currentFnt->m_objectRef = objectSpaceObjectPropSetChunk;
      }

      ds >> currentFnt->m_body;
      ds >> currentFnt->m_cRef;

      break;
    }
    case FileNodeTypeID::ReadOnlyObjectDeclaration2LargeRefCountFND: {
      fn->fnt =
          std::make_shared<ReadOnlyObjectDeclaration2LargeRefCountFND>(fn);

      auto currentFnt =
          std::static_pointer_cast<ReadOnlyObjectDeclaration2LargeRefCountFND>(
              fn->fnt);

      FileNodeChunkReference blobRef(fn->stpFormat, fn->cbFormat);
      ds >> blobRef;
      if (!blobRef.is_fcrNil() && !blobRef.is_fcrZero()) {

        auto objectSpaceObjectPropSetChunk =
            std::make_shared<ObjectSpaceObjectPropSet>(
                blobRef.stp(), blobRef.cb());

        insertChunkSorted(m_file->chunks(), objectSpaceObjectPropSetChunk);

        currentFnt->m_base.m_blobRef = objectSpaceObjectPropSetChunk;
      }

      ds >> currentFnt->m_base.m_body;
      ds >> currentFnt->m_base.m_cRef;

      break;
    }
    case FileNodeTypeID::ReadOnlyObjectDeclaration2RefCountFND: {
      fn->fnt = std::make_shared<ReadOnlyObjectDeclaration2RefCountFND>(fn);

      auto currentFnt =
          std::static_pointer_cast<ReadOnlyObjectDeclaration2RefCountFND>(
              fn->fnt);

      FileNodeChunkReference blobRef(fn->stpFormat, fn->cbFormat);
      ds >> blobRef;
      if (!blobRef.is_fcrNil() && !blobRef.is_fcrZero()) {

        auto objectSpaceObjectPropSetChunk =
            std::make_shared<ObjectSpaceObjectPropSet>(
                blobRef.stp(), blobRef.cb());

        insertChunkSorted(m_file->chunks(), objectSpaceObjectPropSetChunk);

        currentFnt->m_base.m_blobRef = objectSpaceObjectPropSetChunk;
      }

      ds >> currentFnt->m_base.m_body;
      ds >> currentFnt->m_base.m_cRef;

      break;
    }
    case FileNodeTypeID::ObjectDeclarationWithRefCountFNDX: {
      fn->fnt = std::make_shared<ObjectDeclarationWithRefCountFNDX>(fn);

      auto currentFnt =
          std::static_pointer_cast<ObjectDeclarationWithRefCountFNDX>(fn->fnt);

      FileNodeChunkReference blobRef(fn->stpFormat, fn->cbFormat);
      ds >> blobRef;
      if (!blobRef.is_fcrNil() && !blobRef.is_fcrZero()) {

        auto objectSpaceObjectPropSetChunk =
            std::make_shared<ObjectSpaceObjectPropSet>(
                blobRef.stp(), blobRef.cb());

        insertChunkSorted(m_file->chunks(), objectSpaceObjectPropSetChunk);

        currentFnt->m_objectRef = objectSpaceObjectPropSetChunk;
      }

      ds >> currentFnt->m_body;
      ds >> currentFnt->m_cRef;

      break;
    }
    case FileNodeTypeID::ObjectInfoDependencyOverridesFND: {
      fn->fnt = std::make_shared<ObjectInfoDependencyOverridesFND>(fn);

      auto currentFnt =
          std::static_pointer_cast<ObjectInfoDependencyOverridesFND>(fn->fnt);

      FileNodeChunkReference blobRef(fn->stpFormat, fn->cbFormat);
      ds >> blobRef;
      if (!blobRef.is_fcrNil() && !blobRef.is_fcrZero()) {

        auto objectSpaceObjectPropSetChunk =
            std::make_shared<ObjectInfoDependencyOverrideData>(
                blobRef.stp(), blobRef.cb());

        insertChunkSorted(m_file->chunks(), objectSpaceObjectPropSetChunk);

        currentFnt->m_ref = objectSpaceObjectPropSetChunk;
      }

      if (blobRef.is_fcrNil()) {
        ds >> currentFnt->m_data;
      }


      break;
    }
    case FileNodeTypeID::ObjectRevisionWithRefCount2FNDX: {
      fn->fnt = std::make_shared<ObjectRevisionWithRefCount2FNDX>(fn);

      auto currentFnt =
          std::static_pointer_cast<ObjectRevisionWithRefCount2FNDX>(fn->fnt);

      FileNodeChunkReference blobRef(fn->stpFormat, fn->cbFormat);
      ds >> blobRef;
      if (!blobRef.is_fcrNil() && !blobRef.is_fcrZero()) {

        auto objectSpaceObjectPropSetChunk =
            std::make_shared<ObjectSpaceObjectPropSet>(
                blobRef.stp(), blobRef.cb());

        insertChunkSorted(m_file->chunks(), objectSpaceObjectPropSetChunk);

        currentFnt->m_ref = objectSpaceObjectPropSetChunk;
      }

      ds >> currentFnt->m_oid;

      quint32 temp = 0;
      ds >> temp;
      currentFnt->m_fHasOidReferences  = static_cast<bool>(temp & 0x1);
      currentFnt->m_fHasOsidReferences = static_cast<bool>((temp & 0x2) >> 1);

      ds >> currentFnt->m_cRef;


      break;
    }
    case FileNodeTypeID::ObjectRevisionWithRefCountFNDX: {
      fn->fnt = std::make_shared<ObjectRevisionWithRefCountFNDX>(fn);

      auto currentFnt =
          std::static_pointer_cast<ObjectRevisionWithRefCountFNDX>(fn->fnt);

      FileNodeChunkReference blobRef(fn->stpFormat, fn->cbFormat);
      ds >> blobRef;
      if (!blobRef.is_fcrNil() && !blobRef.is_fcrZero()) {

        auto objectSpaceObjectPropSetChunk =
            std::make_shared<ObjectSpaceObjectPropSet>(
                blobRef.stp(), blobRef.cb());

        insertChunkSorted(m_file->chunks(), objectSpaceObjectPropSetChunk);

        currentFnt->m_ref = objectSpaceObjectPropSetChunk;
      }

      ds >> currentFnt->m_oid;

      ds >> currentFnt->m_cRef;
      currentFnt->m_fHasOidReferences  = ((currentFnt->m_cRef & 0x1) != 0u);
      currentFnt->m_fHasOsidReferences = ((currentFnt->m_cRef & 0x2) != 0u);
      currentFnt->m_cRef >>= 2;


      break;
    }

    default:
      qFatal("FileNode of base type 1 has a fileNodeTypeID which switches to "
             "default. Should not happen.");
    }
  }
  else if (fn->baseType == 2) {
    switch (fn->getFileNodeTypeID()) {

    case FileNodeTypeID::FileDataStoreListReferenceFND: {
      fn->fnt = std::make_shared<FileDataStoreListReferenceFND>(fn);

      auto currentFnt =
          std::static_pointer_cast<FileDataStoreListReferenceFND>(fn->fnt);

      FileNodeChunkReference ref(fn->stpFormat, fn->cbFormat);
      ds >> ref;
      if (!ref.is_fcrNil() && !ref.is_fcrZero()) {

        auto objectSpaceObjectPropSetChunk =
            std::make_shared<FileNodeListFragment>(ref.stp(), ref.cb());

        insertChunkSorted(m_file->chunks(), objectSpaceObjectPropSetChunk);

        currentFnt->m_ref = objectSpaceObjectPropSetChunk;
      }

      break;
    }

    case FileNodeTypeID::ObjectGroupListReferenceFND: {
      fn->fnt = std::make_shared<ObjectGroupListReferenceFND>(fn);

      auto currentFnt =
          std::static_pointer_cast<ObjectGroupListReferenceFND>(fn->fnt);

      FileNodeChunkReference ref(fn->stpFormat, fn->cbFormat);
      ds >> ref;
      if (!ref.is_fcrNil() && !ref.is_fcrZero()) {

        auto fileNodeListFragmentContainer =
            std::make_shared<FileNodeListFragment>(ref.stp(), ref.cb());

        insertChunkSorted(m_file->chunks(), fileNodeListFragmentContainer);

        currentFnt->m_ref = fileNodeListFragmentContainer;
      }
      ds >> currentFnt->m_ObjectGroupID;
      break;
    }

    case FileNodeTypeID::ObjectSpaceManifestListReferenceFND: {
      fn->fnt = std::make_shared<ObjectSpaceManifestListReferenceFND>(fn);

      auto currentFnt =
          std::static_pointer_cast<ObjectSpaceManifestListReferenceFND>(
              fn->fnt);

      FileNodeChunkReference ref(fn->stpFormat, fn->cbFormat);
      ds >> ref;
      if (!ref.is_fcrNil() && !ref.is_fcrZero()) {

        auto fileNodeListFragmentContainer =
            std::make_shared<FileNodeListFragment>(ref.stp(), ref.cb());

        insertChunkSorted(m_file->chunks(), fileNodeListFragmentContainer);

        currentFnt->m_ref = fileNodeListFragmentContainer;
      }

      ds >> currentFnt->m_gosid;
      break;
    }
    case FileNodeTypeID::RevisionManifestListReferenceFND: {
      fn->fnt = std::make_shared<RevisionManifestListReferenceFND>(fn);

      auto currentFnt =
          std::static_pointer_cast<RevisionManifestListReferenceFND>(fn->fnt);

      FileNodeChunkReference ref(fn->stpFormat, fn->cbFormat);
      ds >> ref;
      if (!ref.is_fcrNil() && !ref.is_fcrZero()) {

        auto fileNodeListFragmentContainer =
            std::make_shared<FileNodeListFragment>(ref.stp(), ref.cb());

        insertChunkSorted(m_file->chunks(), fileNodeListFragmentContainer);

        currentFnt->m_ref = fileNodeListFragmentContainer;
      }
      break;
    }
    default:
      qFatal("FileNode of base type 2 has a fileNodeTypeID which switches to "
             "default. Should not happen.");
      fn->fnt = nullptr;
      break;
    }
  }

  fn->m_isParsed = true;
  return fn;
}

void RevisionStoreFileParser::parseFileDataStoreObject(
    QDataStream& ds, FileDataStoreObject_WPtr_t fileData)
{


  auto chunk = fileData.lock();

  if (chunk != nullptr) {
    quint64 originalStp = ds.device()->pos();


    ds.device()->seek(chunk->getInitialStp());

    m_ds >> *chunk;

    chunk->m_isParsed = true;

    ds.device()->seek(originalStp);
  }
}

void RevisionStoreFileParser::parseFreeChunkListFragments(
    QDataStream& ds, FreeChunkListFragment_WPtr_t firstFragment)
{

  qint64 originalStp = ds.device()->pos();


  auto fragment = firstFragment.lock();
  while (fragment != nullptr) {

    ds.device()->seek(fragment->getInitialStp());

    ds >> fragment->m_crc;


    FileChunkReference64x32 fcrNextFragment;
    ds >> fcrNextFragment;
    if (!fcrNextFragment.is_fcrNil() && !fcrNextFragment.is_fcrZero()) {

      auto fcrNextFragmentChunk = std::make_shared<FreeChunkListFragment>(
          fcrNextFragment.stp(), fcrNextFragment.cb());

      insertChunkSorted(m_file->chunks(), fcrNextFragmentChunk);


      fragment->m_fcrNextFragment = fcrNextFragmentChunk;
    }

    quint64 chunksToRead = fragment->cb() / 16 - 1;

    for (size_t i{0}; i < chunksToRead; ++i) {

      FileChunkReference64x32 temp;
      ds >> temp;
      if (!temp.is_fcrNil() && !temp.is_fcrZero()) {

        auto freeChunk = std::make_shared<FreeChunk>(temp.stp(), temp.cb());

        insertChunkSorted(m_file->chunks(), freeChunk);


        fragment->m_fcrFreeChunks.push_back(freeChunk);
      }
    }

    fragment = fragment->m_fcrNextFragment.lock();
  }

  ds.device()->seek(originalStp);
}

void RevisionStoreFileParser::parseObjectInfoDependencyOverrideData(
    QDataStream& ds, ObjectInfoDependencyOverrideData_SPtr_t objectInfo)
{
  if (objectInfo != nullptr) {

    quint64 originalStp = ds.device()->pos();


    ds.device()->seek(objectInfo->getInitialStp());

    m_ds >> *objectInfo;

    objectInfo->m_isParsed = true;


    ds.device()->seek(originalStp);
  }
}

ObjectSpaceObjectPropSet_SPtr_t
RevisionStoreFileParser::parseObjectSpaceObjectPropSet(
    QDataStream& ds, ObjectSpaceObjectPropSet_SPtr_t objectPropSet)
{
  qint64 originalPos = ds.device()->pos();
  ds.device()->seek(objectPropSet->getInitialStp());


  quint64 propSetstart = ds.device()->pos();
  ds >> objectPropSet->m_OIDs;

  if (objectPropSet->m_OIDs.header().OsidStream_isNotPresent() == false) {
    ds >> objectPropSet->m_OSIDs;

    if (objectPropSet->m_OSIDs.header().ExtendedStream_isPresent() == true) {
      ds >> objectPropSet->m_ContextIDs;
    }
  }
  ds >> objectPropSet->m_body;

  //
  objectPropSet->m_paddingLength = 8 - (ds.device()->pos() - propSetstart) % 8;

  ds.skipRawData(objectPropSet->m_paddingLength);

  ds.device()->seek(originalPos);

  return objectPropSet;
}

FileNodeListFragment_SPtr_t RevisionStoreFileParser::parseFileNodeListFragment(
    QDataStream& ds, FileNodeListFragment_SPtr_t chunk)
{
  quint64 stp = chunk->getInitialStp();
  quint64 cb  = chunk->getInitialCb();

  if (static_cast<quint64>(ds.device()->size()) < stp) {
    qFatal("Tried to read past file size.");
  }
  ds.device()->seek(chunk->getInitialStp());

  if (cb < FileNodeListFragment::minSizeInFile) {
    qFatal("Tried to read fileNodeListFragment with invalid size.");
  }

  if (static_cast<quint64>(ds.device()->bytesAvailable()) < cb) {
    qFatal("Remaining file size insufficient to parse FileNodeListFragment.");
  }

  // if byte order is big endian, change to little endian
  if (m_ds.byteOrder() == QDataStream::BigEndian) {
    m_ds.setByteOrder(QDataStream::LittleEndian);
  }


  quint64 headerTest;
  ds >> headerTest;
  if (headerTest != FileNodeListFragment::header_magic_id) {
    qFatal("FileNodeListFragment header is invalid.");
  }

  ds >> chunk->m_fileNodeListID;
  ds >> chunk->m_nFragmentSequence;

  if (m_file->m_fileNodeListFragments.find(chunk->m_nFragmentSequence) !=
      m_file->m_fileNodeListFragments.end()) {
    qWarning("FileNodeListFragment Sequence number already present(duplicate "
             "nFragmentSequence");

    /// \todo figure out how the requirement of strictly sequential numbered
    /// fragments applies
    m_file->m_fileNodeListFragments.emplace(
        chunk->m_nFragmentSequence + 0x1000, chunk);
  }
  else {

    m_file->m_fileNodeListFragments.emplace(chunk->m_nFragmentSequence, chunk);
  }


  quint32 fileNodeCount = UINT32_MAX;

  if (m_file->m_fileNodeCountMapping.contains(chunk->m_fileNodeListID)) {
    fileNodeCount = m_file->m_fileNodeCountMapping[chunk->m_fileNodeListID];
  }

  quint64 remainingBytes = cb - FileNodeListFragment::headerSize;
  do {

    auto fnc = parseFileNode(ds, ds.device()->pos(), chunk);

    FileNodeTypeID fileNodeID = fnc->getFileNodeTypeID();

    if (fileNodeID != FileNodeTypeID::NullFnd) {
      chunk->m_fileNodes.push_back(fnc);
      if (fileNodeID != FileNodeTypeID::ChunkTerminatorFND) {
        fileNodeCount--;
      }
      else {
        /// \todo When ChunkTerminator found, is there really no filenode
        /// left?
        //        qWarning() << "ChunkTerminatorFND found";
        break;
      }
    }
    else {
      //      qWarning() << "FileNodeListFragment ended early";
      break;
    }

    remainingBytes -= fnc->getSizeInFile();
  } while ((remainingBytes - 20 > 4) && (fileNodeCount > 0));

  if (m_file->m_fileNodeCountMapping.contains(chunk->m_fileNodeListID)) {
    m_file->m_fileNodeCountMapping[chunk->m_fileNodeListID] = fileNodeCount;
  }

  chunk->m_paddingLength = remainingBytes - 20;

  // Skip to end. Ignore ChunkTerminatorFND
  ds.device()->seek(stp + cb - 20);

  // footer
  FileChunkReference64x32 nextFragment;
  ds >> nextFragment;

  quint64 footerTest;
  ds >> footerTest;
  if (footerTest != FileNodeListFragment::footer_magic_id) {
    qFatal("FileNodeListFragment footer is invalid.");
  }

  chunk->m_isParsed = true;

  if (!nextFragment.is_fcrNil() && !nextFragment.is_fcrZero()) {
    auto nextFnlf = std::make_shared<FileNodeListFragment>(
        nextFragment.stp(), nextFragment.cb());

    //    insertChunkSorted(targetChunkList, nextFnlf);
    chunk->m_nextFragment = nextFnlf;
    return nextFnlf;
  }


  // return empty if there is no next
  return FileNodeListFragment_SPtr_t();
}

std::vector<FileNodeListFragment_WPtr_t>
RevisionStoreFileParser::parseFileNodeList(
    QDataStream& ds, FileNodeListFragment_WPtr_t firstFragment)
{
  std::vector<FileNodeListFragment_WPtr_t> vec;
  if (firstFragment.expired()) {
    return vec;
  }

  qint64 originalStp = ds.device()->pos();

  ds.device()->seek(firstFragment.lock()->getInitialStp());


  auto fragment = firstFragment.lock();

  while (fragment != nullptr) {
    parseFileNodeListFragment(ds, fragment);

    vec.push_back(fragment);

    fragment = fragment->getNextFragment().lock();
  }

  ds.device()->seek(originalStp);
  return vec;
}

bool RevisionStoreFileParser::parseTransactionLogFragment(
    QDataStream& ds, TransactionLogFragment_SPtr_t firstFragment)
{
  if (firstFragment == nullptr) {
    return true;
  }

  auto fragment = firstFragment;

  qint64 originalStp = ds.device()->pos();

  quint32 countTransactions = 0;

  auto header = std::static_pointer_cast<RevisionStoreFileHeader>(
      *m_file->m_chunks.begin());


  while (fragment != nullptr) {

    ds.device()->seek(fragment->getInitialStp());

    quint64 num_entries = (firstFragment->getInitialCb() -
                           FileChunkReference64x32::getSizeInFile()) /
                          TransactionEntry::getSizeInFile();

    for (size_t i{0}; i < num_entries; i++) {
      std::shared_ptr<TransactionEntry> entry =
          std::make_shared<TransactionEntry>();

      ds >> *entry;
      fragment->sizeTable.push_back(entry);
    }


    FileChunkReference64x32 nextFragmentFCR;
    ds >> nextFragmentFCR;
    if (!nextFragmentFCR.is_fcrNil() && !nextFragmentFCR.is_fcrZero()) {

      auto nextTransactionLogFragmentContainer =
          std::make_shared<TransactionLogFragment>(
              nextFragmentFCR.stp(), nextFragmentFCR.cb());

      insertChunkSorted(m_file->chunks(), nextTransactionLogFragmentContainer);

      fragment->nextFragment = nextTransactionLogFragmentContainer;
    }


    /// test for mismatch
    /// \todo deduct when there is a mismatch between a given Size of a
    /// TransactionLogFragment and the accumulated size of its contents

    quint64 contentAlignedFooter =
        num_entries * TransactionEntry::getSizeInFile();

    quint64 tailAlignedFooter =
        fragment->getInitialCb() - FileChunkReference64x32::getSizeInFile();

    if (contentAlignedFooter != tailAlignedFooter) {
      qInfo().noquote().nospace()
          << "There is a mismatch of "
          << tailAlignedFooter - contentAlignedFooter
          << " bytes in the TransactionLogFragments given size and used size "
             "at stp: "
          << qStringHex(fragment->getInitialStp(), 16)
          << " cb: " << qStringHex(fragment->getInitialCb(), 16);

      fragment->setPaddingLength(tailAlignedFooter - contentAlignedFooter);
    }

    ds.skipRawData(fragment->getPaddingLength());


    fragment->m_isParsed = true;

    m_file->m_transactionLogs.push_back(fragment);


    // now process Transactions to fill RevisionStoreFile maps
    for (const auto& entry : fragment->getSizeTable()) {
      if (entry->getSrcID() != 0x00000001) {

        if (m_file->m_fileNodeCountMapping.contains(entry->getSrcID())) {
          if (m_file->m_fileNodeCountMapping[entry->getSrcID()] <
              entry->getTransactionEntrySwitch()) {
            m_file->m_fileNodeCountMapping[entry->getSrcID()] =
                entry->getTransactionEntrySwitch();
          }
        }
        else {
          m_file->m_fileNodeCountMapping.insert(
              entry->getSrcID(), entry->getTransactionEntrySwitch());
        }
      }
      else {
        countTransactions++;
        if (countTransactions == header->getCTransactionsInLog()) {
          break;
        }
        else {
          continue;
        }
      }
    }
    if (countTransactions == header->getCTransactionsInLog()) {
      break;
    }

    fragment = fragment->nextFragment.lock();
  };


  ds.device()->seek(originalStp);

  // Reporting when parse was buggy


  if (countTransactions != header->getCTransactionsInLog()) {
    qWarning() << "Only " << QString::number(countTransactions)
               << " TransactionLogFragments parsed, but "
               << QString::number(header->getCTransactionsInLog())
               << " declared.";
    return false;
  }

  return true;
}


void RevisionStoreFileParser::insertChunkSorted(
    std::list<Chunkable_SPtr_t>& chunkList, Chunkable_SPtr_t chunk)
{
  if (chunk->getType() == RevisionStoreChunkType::RevisionStoreFileHeader) {
    qWarning("Did not add second RevisionStoreFileHeader to chunk list.");
    return;
  }

  if (chunkList.size() < 2) {
    chunkList.push_back(chunk);
    return;
  }

  const quint64 chunkInitialStp = chunk->getInitialStp();

  for (auto it = chunkList.rbegin(); it != chunkList.rend(); ++it) {

    const quint64 currentStp = it->get()->getInitialStp();
    if (currentStp < chunkInitialStp) {

      chunkList.insert(it.base(), chunk);
      return;
    }
  }
}


} // namespace priv
} // namespace libmson
