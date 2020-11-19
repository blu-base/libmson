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
      parseFileNodeList(m_ds, header->m_fcrFileNodeListRoot.lock());

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
      parseFileNodeList(m_ds, header->m_fcrHashedChunkList.lock());


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


  /// \todo replace temporary brute-force parsing remaining unparsed chunks
  bool thereAreUnparsed = true;
  while (thereAreUnparsed) {
    bool foundUnparsedThisLoop = false;


    // iterate in copy, since we modify original list
    auto chunks = m_file->getChunks();

    for (auto it = chunks.rbegin(); it != chunks.rend(); ++it) {
      if (!(*it)->isParsed()) {
        foundUnparsedThisLoop = true;
        parseChunk(m_ds, *it);
      }
    }

    if (!foundUnparsedThisLoop) {
      thereAreUnparsed = false;
    }
  }


  {
    /// Check file for unreferenced sections
    auto lChunks = m_file->getChunks();

    //    lChunks.push_front(m_file->m_header);

    auto it   = lChunks.begin();
    auto prev = it;
    it++;
    while (it != lChunks.end()) {

      quint64 lastEnd = (*prev)->getInitialStp() + (*prev)->getInitialCb();
      quint64 start   = (*it)->getInitialStp();

      quint64 diff = start - lastEnd;

      if (diff != 0) {
        qInfo().noquote() << "Found unreferenced blob at"
                          << qStringHex(lastEnd, 16) << "of size"
                          << qStringHex(diff, 8);

        auto unknownBlob = std::make_shared<UnknownBlob>(lastEnd, diff);

        unknownBlob = insertChunkSorted(m_file->chunks(), unknownBlob);
        m_file->m_unkownBlobs.push_back(unknownBlob);


        parseUnknownBlob(m_ds, unknownBlob);
      }

      it++;
      prev++;
    }


    quint64 lastEnd = (*prev)->getInitialStp() + (*prev)->getInitialCb();

    quint64 diff = header->getCbExpectedFileLength() - lastEnd;

    if (diff != 0) {
      qInfo().noquote() << "Found unreferenced blob at"
                        << qStringHex(lastEnd, 16) << "of size"
                        << qStringHex(diff, 8);

      auto unknownBlob = std::make_shared<UnknownBlob>(lastEnd, diff);

      unknownBlob = insertChunkSorted(m_file->chunks(), unknownBlob);


      m_file->m_unkownBlobs.push_back(unknownBlob);

      parseUnknownBlob(m_ds, unknownBlob);
    }
  }

  /*
  /// temporary check regarding intended sizes and reported sizes
  ///
  ///
  std::list<qint64> diffs;

  for (const auto& chunk : m_file->chunks()) {
    diffs.push_back(chunk->getInitialCb() - chunk->getSizeInFile());
  }

  qint64 totalDiff = std::accumulate(diffs.begin(), diffs.end(), 0);
  */


  return m_file;
}

void RevisionStoreFileParser::parseChunk(
    QDataStream& ds, Chunkable_SPtr_t chunk)
{
  switch (chunk->type()) {

  case RevisionStoreChunkType::RevisionStoreFileHeader: {
    parseRevisionStoreFileHeader(ds);
    qWarning() << "Likely found another RevisionStoreFileHeader, which "
                  "shouldn't be there.";
    break;
  }
  case RevisionStoreChunkType::FileNodeListFragment: {
    parseFileNodeListFragment(
        ds, std::static_pointer_cast<FileNodeListFragment>(chunk));
    break;
  }
  case RevisionStoreChunkType::FileNode: {
    parseFileNode(ds, std::static_pointer_cast<FileNode>(chunk));
    break;
  }
  case RevisionStoreChunkType::FreeChunkListFragment: {
    parseFreeChunkListFragments(
        ds, std::static_pointer_cast<FreeChunkListFragment>(chunk));
    break;
  }
  case RevisionStoreChunkType::FreeChunk: {
    parseFreeChunk(ds, std::static_pointer_cast<FreeChunk>(chunk));
    break;
  }
  case RevisionStoreChunkType::TransactionLogFragment: {
    parseTransactionLogFragment(
        ds, std::static_pointer_cast<TransactionLogFragment>(chunk));
    break;
  }
  case RevisionStoreChunkType::FileDataStoreObject: {
    parseFileDataStoreObject(
        ds, std::static_pointer_cast<FileDataStoreObject>(chunk));
    break;
  }
  case RevisionStoreChunkType::ObjectSpaceObjectPropSet: {
    parseObjectSpaceObjectPropSet(
        ds, std::static_pointer_cast<ObjectSpaceObjectPropSet>(chunk));
    break;
  }
  case RevisionStoreChunkType::ObjectInfoDependencyOverrideData: {
    parseObjectInfoDependencyOverrideData(
        ds, std::static_pointer_cast<ObjectInfoDependencyOverrideData>(chunk));
    break;
  }
  case RevisionStoreChunkType::EncryptedData: {
    parseEncryptedData(ds, std::static_pointer_cast<EncryptedData>(chunk));
    break;
  }
  case RevisionStoreChunkType::UnknownBlob: {
    parseUnknownBlob(ds, std::static_pointer_cast<UnknownBlob>(chunk));
    break;
  }

  case RevisionStoreChunkType::Invalid:
  default:
    qFatal("Failed to initialize invalid RevisionStoreChunkType.");
  }
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


  m_file->m_header = header;

  ds >> header->m_guidFileType;
  ds >> header->m_guidFile;
  ds >> header->m_guidLegacyFileVersion;
  if (header->guidLegacyFileVersion !=
      RevisionStoreFileHeader::guidLegacyFileVersion) {
    qWarning(
        "guidLegacyFileVersion of the RevisionStoreFileHeader is invalid.");
  }
  ds >> header->m_guidFileFormat;
  if (header->guidFileFormat != RevisionStoreFileHeader::guidFileFormat) {
    qWarning("guidFileFormat of the RevisionStoreFileHeader is invalid.");
    return RevisionStoreFileHeader_WPtr_t();
  }
  ds >> header->m_ffvLastWriterVersion;
  ds >> header->m_ffvOldestWriterVersion;
  ds >> header->m_ffvNewestWriterVersion;
  ds >> header->m_ffvOldestReader;

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

  ds >> header->m_cTransactionsInLog;

  quint32 cbLegacyExpectedFileLength;
  ds >> cbLegacyExpectedFileLength;
  if (cbLegacyExpectedFileLength != 0u) {
    qWarning("cbLegacyExpectedFileLength of the RevisionStoreFileHeader is "
             "invalid.");
  }

  ds >> header->m_rgbPlaceholder;

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

  ds >> header->m_fNeedsDefrag;
  ds >> header->m_fRepairedFile;
  ds >> header->m_fNeedsGarbageCollect;
  ds >> header->m_fHasNoEmbeddedFileObjects;
  ds >> header->m_guidAncestor;
  ds >> header->m_crcName;

  FileChunkReference64x32 fcrHashedChunkList;
  ds >> fcrHashedChunkList;

  if (!fcrHashedChunkList.is_fcrNil() && !fcrHashedChunkList.is_fcrZero()) {


    auto fcrHashedChunkListFragment = std::make_shared<FileNodeListFragment>(
        fcrHashedChunkList.stp(), fcrHashedChunkList.cb());

    fcrHashedChunkListFragment =
        insertChunkSorted(m_file->chunks(), fcrHashedChunkListFragment);

    header->m_fcrHashedChunkList = fcrHashedChunkListFragment;
  }

  FileChunkReference64x32 fcrTransactionLog;
  ds >> fcrTransactionLog;
  if (!fcrTransactionLog.is_fcrNil() && !fcrTransactionLog.is_fcrZero()) {

    auto fcrTransactionLogFragment = std::make_shared<TransactionLogFragment>(
        fcrTransactionLog.stp(), fcrTransactionLog.cb());

    fcrTransactionLogFragment =
        insertChunkSorted(m_file->chunks(), fcrTransactionLogFragment);

    header->m_fcrTransactionLog = fcrTransactionLogFragment;
  }

  FileChunkReference64x32 fcrFileNodeListRoot;
  ds >> fcrFileNodeListRoot;
  if (!fcrFileNodeListRoot.is_fcrNil() && !fcrFileNodeListRoot.is_fcrZero()) {

    auto fileNodeListRootChunk = std::make_shared<FileNodeListFragment>(
        fcrFileNodeListRoot.stp(), fcrFileNodeListRoot.cb());

    fileNodeListRootChunk =
        insertChunkSorted(m_file->chunks(), fileNodeListRootChunk);

    header->m_fcrFileNodeListRoot = fileNodeListRootChunk;
  }

  FileChunkReference64x32 fcrFreeChunkList;
  ds >> fcrFreeChunkList;
  if (!fcrFreeChunkList.is_fcrNil() && !fcrFreeChunkList.is_fcrZero()) {

    auto freeChunkListFragment = std::make_shared<FreeChunkListFragment>(
        fcrFreeChunkList.stp(), fcrFreeChunkList.cb());

    freeChunkListFragment =
        insertChunkSorted(m_file->chunks(), freeChunkListFragment);

    header->m_fcrFreeChunkList = freeChunkListFragment;
  }

  ds >> header->m_cbExpectedFileLength;
  ds >> header->m_cbFreeSpaceInFreeChunkList;
  ds >> header->m_guidFileVersion;
  ds >> header->m_nFileVersionGeneration;
  ds >> header->m_guidDenyReadFileVersion;
  ds >> header->m_grfDebugLogFlags;

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

  ds >> header->m_bnCreated;
  ds >> header->m_bnLastWroteToThisFile;
  ds >> header->m_bnOldestWritten;
  ds >> header->m_bnNewestWritten;
  ds.skipRawData(header->def_reservedHeaderTailLength);


  header->m_isParsed = true;
  /// \todo further Validate header
  return header;
}


FileNode_SPtr_t RevisionStoreFileParser::parseFileNode(
    QDataStream& ds, FileNode_SPtr_t fileNode)
{
  return parseFileNode(ds, fileNode->getInitialStp(), fileNode->getParent());
}


FileNode_SPtr_t RevisionStoreFileParser::parseFileNode(
    QDataStream& ds, const quint64 stp, FileNodeListFragment_WPtr_t parent)
{

  quint32 composite;
  ds >> composite;

  quint16 fileNodeSize =
      (composite >> fNshiftFileNodeSize) & fNmaskFileNodeSize;

  auto fn = std::make_shared<FileNode>(parent, stp, fileNodeSize);

  fn->baseType   = (composite >> fNshiftBaseType) & fNmaskBaseType;
  fn->cbFormat   = (composite >> fNshiftCbFormat) & fNmaskCbFormat;
  fn->stpFormat  = (composite >> fNshiftStpFormat) & fNmaskStpFormat;
  fn->fileNodeID = (composite >> fNshiftFileNodeID) & fNmaskFileNodeID;


  // distinguish by baseType,
  // type 0 does not contain any reference to a chunk, and therefore can be
  // parsed trivially type 1 and type 2 do contain references and must cast
  // chunkContainer


  if (fn->baseType == 0) {

    switch (fn->getFileNodeTypeID()) {
    case FileNodeTypeID::ChunkTerminatorFND: {
      auto thisFnt = std::make_shared<ChunkTerminatorFND>(fn);
      ds >> *thisFnt;
      fn->fnt = thisFnt;
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
      qInfo() << "FileNodeID: " << fn->getFileNodeID();
      qWarning("FileNode of base type 0 has a fileNodeTypeID which switches to "
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


        objectSpaceObjectPropSetChunk =
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

        objectSpaceObjectPropSetChunk =
            insertChunkSorted(m_file->chunks(), objectSpaceObjectPropSetChunk);

        currentFnt->m_blobRef = objectSpaceObjectPropSetChunk;
      }

      currentFnt->m_guidHash =
          ds.device()->read(HashedChunkDescriptor2FND::guidHashWidth);

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

        objectSpaceObjectPropSetChunk =
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

        objectSpaceObjectPropSetChunk =
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

        objectSpaceObjectPropSetChunk =
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

        objectSpaceObjectPropSetChunk =
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

        objectSpaceObjectPropSetChunk =
            insertChunkSorted(m_file->chunks(), objectSpaceObjectPropSetChunk);

        currentFnt->m_blobRef = objectSpaceObjectPropSetChunk;
      }

      ds >> currentFnt->m_body;
      ds >> currentFnt->m_cRef;

      currentFnt->setMd5hash(ds.device()->read(
          ReadOnlyObjectDeclaration2LargeRefCountFND::md5HashSize));
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

        objectSpaceObjectPropSetChunk =
            insertChunkSorted(m_file->chunks(), objectSpaceObjectPropSetChunk);

        currentFnt->m_blobRef = objectSpaceObjectPropSetChunk;
      }

      ds >> currentFnt->m_body;
      ds >> currentFnt->m_cRef;

      currentFnt->setMd5hash(ds.device()->read(
          ReadOnlyObjectDeclaration2RefCountFND::md5HashSize));

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

        objectSpaceObjectPropSetChunk =
            insertChunkSorted(m_file->chunks(), objectSpaceObjectPropSetChunk);

        currentFnt->m_objectRef = objectSpaceObjectPropSetChunk;
      }

      ds >> currentFnt->m_body;
      ds >> currentFnt->m_cRef;

      break;
    }
    case FileNodeTypeID::ObjectInfoDependencyOverridesFND: {
      auto currentFnt = std::make_shared<ObjectInfoDependencyOverridesFND>(fn);

      fn->fnt = currentFnt;

      FileNodeChunkReference blobRef(fn->stpFormat, fn->cbFormat);
      ds >> blobRef;
      if (!blobRef.is_fcrNil() && !blobRef.is_fcrZero()) {

        auto objectSpaceObjectPropSetChunk =
            std::make_shared<ObjectInfoDependencyOverrideData>(
                blobRef.stp(), blobRef.cb());

        objectSpaceObjectPropSetChunk =
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

        objectSpaceObjectPropSetChunk =
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

        objectSpaceObjectPropSetChunk =
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
      /// \todo make an unknown blob filenode to cope with undocumented stuff
      qInfo() << "FileNodeID: " << fn->getFileNodeID();
      qWarning("FileNode of base type 1 has a fileNodeTypeID which switches to "
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

        objectSpaceObjectPropSetChunk =
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

        auto fileNodeListFragment =
            std::make_shared<FileNodeListFragment>(ref.stp(), ref.cb());

        fileNodeListFragment =
            insertChunkSorted(m_file->chunks(), fileNodeListFragment);

        currentFnt->m_ref = fileNodeListFragment;
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

        fileNodeListFragmentContainer =
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

        fileNodeListFragmentContainer =
            insertChunkSorted(m_file->chunks(), fileNodeListFragmentContainer);

        currentFnt->m_ref = fileNodeListFragmentContainer;
      }
      break;
    }
    default:

      qInfo() << "FileNodeID: " << fn->getFileNodeID();
      qWarning("FileNode of base type 2 has a fileNodeTypeID which switches to "
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

      fcrNextFragmentChunk =
          insertChunkSorted(m_file->chunks(), fcrNextFragmentChunk);


      fragment->m_fcrNextFragment = fcrNextFragmentChunk;
    }

    quint64 chunksToRead = fragment->cb() / 16 - 1;

    for (size_t i{0}; i < chunksToRead; ++i) {

      FileChunkReference64x32 temp;
      ds >> temp;
      if (!temp.is_fcrNil() && !temp.is_fcrZero()) {

        auto freeChunk = std::make_shared<FreeChunk>(temp.stp(), temp.cb());

        freeChunk = insertChunkSorted(m_file->chunks(), freeChunk);


        fragment->m_fcrFreeChunks.push_back(freeChunk);
      }
    }

    fragment = fragment->m_fcrNextFragment.lock();
  }

  ds.device()->seek(originalStp);
}

void RevisionStoreFileParser::parseFreeChunk(
    QDataStream& ds, FreeChunk_SPtr_t freeChunk)
{
  freeChunk->m_isParsed = true;
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


  quint64 propSetStart = ds.device()->pos();
  ds >> objectPropSet->m_OIDs;

  if (objectPropSet->m_OIDs.header().OsidStream_isNotPresent() == false) {
    ds >> objectPropSet->m_OSIDs;

    if (objectPropSet->m_OSIDs.header().ExtendedStream_isPresent() == true) {
      ds >> objectPropSet->m_ContextIDs;
    }
  }
  ds >> objectPropSet->m_body;

  quint8 paddingLength = 8 - (ds.device()->pos() - propSetStart) % 8;

  ds.skipRawData(paddingLength);

  ds.device()->seek(originalPos);

  objectPropSet->m_isParsed = true;

  return objectPropSet;
}

FileNodeListFragment_SPtr_t RevisionStoreFileParser::parseFileNodeListFragment(
    QDataStream& ds, FileNodeListFragment_SPtr_t fragment)
{
  const quint64 stp = fragment->getInitialStp();
  const quint64 cb  = fragment->getInitialCb();

  if (static_cast<quint64>(ds.device()->size()) < stp) {
    qFatal("Tried to read past file size.");
  }
  ds.device()->seek(fragment->getInitialStp());

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

  ds >> fragment->m_fileNodeListID;
  ds >> fragment->m_nFragmentSequence;

  /*
  if (m_file->m_fileNodeListFragments.find(fragment->m_nFragmentSequence) !=
      m_file->m_fileNodeListFragments.end()) {
    qWarning("FileNodeListFragment Sequence number already present(duplicate "
             "nFragmentSequence");

    /// \todo figure out how the requirement of strictly sequential numbered
    /// fragments applies
    //    m_file->m_fileNodeListFragments.emplace(
    //        fragment->m_nFragmentSequence + 0x1000, fragment);
  }
  else {

    m_file->m_fileNodeListFragments.emplace(
        fragment->m_nFragmentSequence, fragment);
  }
  */

  quint32 fileNodeCount = UINT32_MAX;

  if (m_file->m_fileNodeCountMapping.contains(fragment->m_fileNodeListID)) {
    fileNodeCount = m_file->m_fileNodeCountMapping[fragment->m_fileNodeListID];
  }

  quint64 remainingBytes = cb - FileNodeListFragment::minSizeInFile;
  //  quint64 thisStart      = stp + FileNodeListFragment::headerSize;
  //  quint64 diff           = 0;
  do {

    auto fnc = parseFileNode(ds, ds.device()->pos(), fragment);


    //    quint64 rep = fnc->getSizeInFile();
    //    diff        = ds.device()->pos() - thisStart;
    //    thisStart   = ds.device()->pos();

    FileNodeTypeID fileNodeID = fnc->getFileNodeTypeID();


    if (fileNodeID != FileNodeTypeID::NullFnd) {
      fragment->m_fileNodes.push_back(fnc);
      remainingBytes -= fnc->getSizeInFile();
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


  } while ((remainingBytes > 4) && (fileNodeCount > 0));


  if (m_file->m_fileNodeCountMapping.contains(fragment->m_fileNodeListID)) {
    m_file->m_fileNodeCountMapping[fragment->m_fileNodeListID] = fileNodeCount;
  }

  fragment->m_paddingLength = remainingBytes;


  // dormant file nodes section

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

  fragment->m_isParsed = true;

  if (!nextFragment.is_fcrNil() && !nextFragment.is_fcrZero()) {
    auto nextFnlf = std::make_shared<FileNodeListFragment>(
        nextFragment.stp(), nextFragment.cb());

    nextFnlf                 = insertChunkSorted(m_file->chunks(), nextFnlf);
    fragment->m_nextFragment = nextFnlf;
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

  auto header = m_file->m_header;


  while (fragment != nullptr) {

    ds.device()->seek(fragment->getInitialStp());

    quint64 num_entries = (firstFragment->getInitialCb() -
                           FileChunkReference64x32::getSizeInFile()) /
                          TransactionEntry::getSizeInFile();
    std::vector<TransactionEntry_SPtr_t> transactionEntries;
    transactionEntries.reserve(num_entries);
    for (size_t i{0}; i < num_entries; i++) {
      TransactionEntry_SPtr_t entry;
      ds >> *entry;
      transactionEntries.push_back(entry);
    }

    fragment->setSizeTable(transactionEntries);


    FileChunkReference64x32 nextFragmentFCR;
    ds >> nextFragmentFCR;
    if (!nextFragmentFCR.is_fcrNil() && !nextFragmentFCR.is_fcrZero()) {

      auto nextTransactionLogFragmentContainer =
          std::make_shared<TransactionLogFragment>(
              nextFragmentFCR.stp(), nextFragmentFCR.cb());

      nextTransactionLogFragmentContainer = insertChunkSorted(
          m_file->chunks(), nextTransactionLogFragmentContainer);

      fragment->m_nextFragment = nextTransactionLogFragmentContainer;
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

    fragment = fragment->m_nextFragment.lock();
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

void RevisionStoreFileParser::parseUnknownBlob(
    QDataStream& ds, UnknownBlob_SPtr_t unknownBlob)
{
  qint64 originalStp = ds.device()->pos();

  ds.device()->seek(unknownBlob->getInitialStp());

  unknownBlob->m_blob = ds.device()->read(unknownBlob->getInitialCb());

  unknownBlob->m_isParsed = true;

  ds.device()->seek(originalStp);
}

template <class Chunkably>
std::shared_ptr<Chunkably> RevisionStoreFileParser::preventDuplicate(
    std::list<Chunkable_SPtr_t>& chunkList, std::shared_ptr<Chunkably> chunk)
{


  auto foundItem = std::find_if(
      chunkList.begin(), chunkList.end(),
      [&chunk](Chunkable_SPtr_t const& entry) {
        return chunk->getInitialStp() == entry->getInitialStp() &&
               chunk->getInitialCb() == entry->getInitialCb();
      });


  if (foundItem != chunkList.end()) {
    return std::static_pointer_cast<Chunkably>(*foundItem);
  }

  return chunk;
}

template <class Chunkably>
std::shared_ptr<Chunkably> RevisionStoreFileParser::insertChunkSorted(
    std::list<Chunkable_SPtr_t>& chunkList, std::shared_ptr<Chunkably> chunk)
{

  // test for duplicate
  auto thisChunk = preventDuplicate(chunkList, chunk);
  if (thisChunk != chunk) {
    return thisChunk;
  }

  // if there is no duplicate: add new chunk;
  if (chunkList.empty()) {
    chunkList.push_back(chunk);
    return chunk;
  }

  const quint64 chunkInitialStp = chunk->getInitialStp();

  for (auto it = chunkList.rbegin(); it != chunkList.rend(); ++it) {

    const quint64 currentStp = it->get()->getInitialStp();
    if (currentStp < chunkInitialStp) {

      chunkList.insert(it.base(), chunk);
      return chunk;
    }
  }

  // if it's at the end since we are reverse looping before
  chunkList.push_front(chunk);

  return chunk;
}


} // namespace priv
} // namespace libmson
