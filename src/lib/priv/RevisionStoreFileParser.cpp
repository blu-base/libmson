#include "RevisionStoreFileParser.h"


#include "chunkables/fileNodeTypes/FileNodeTypes.h"

#include "utils/ChunkableUtils.h"
#include "utils/Helper.h"

#include "ObjectGroupList.h"
#include "ObjectSpaceManifestList.h"
#include "RevisionManifest.h"

#include <iterator>

#include <QDebug>

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
  auto header = parseRevisionStoreFileHeader(m_ds);


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

        if (m_file->m_objectSpaceManifestRootFN == nullptr) {
          m_file->m_objectSpaceManifestRootFN = fn;
        }
        else {
          qWarning("There is an additional ObjectSpaceManifestRootFND present. "
                   "Ignoring it.");
        }
      }
    }
  }


  // Traverse RootFileNodeList to parse ObjectSpaceManifestListReferences
  for (const auto& frag : m_file->m_rootFileNodeList) {
    for (const auto& fn : frag.lock()->getFileNodes()) {
      if (fn->getFileNodeTypeID() ==
          FileNodeTypeID::ObjectSpaceManifestListReferenceFND) {

        auto fnd =
            std::static_pointer_cast<ObjectSpaceManifestListReferenceFND>(
                fn->getFnt());

        auto manifestList = parseObjectSpaceManifestList(m_ds, fn);
        m_file->m_objectSpaceManifestLists.emplace(
            manifestList->getGosid(), manifestList);
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

  // Parsing HashedChunkList
  m_file->m_hashedChunkListFragments =
      parseFileNodeList(m_ds, header->m_fcrHashedChunkList.lock());


  // Parsing FreeChunkList
  parseFreeChunkListFragments(m_ds, header->getFcrFreeChunkList().lock());


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

    for (const auto& fileReference : fileDataStoreObjects) {
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
        m_file->m_undiscovered.push_back(*it);
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


// -----------------------------------------------------------------------------

void RevisionStoreFileParser::parseChunk(
    QDataStream& ds, const Chunkable_SPtr_t& chunk)
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
    parseFreeChunk(std::static_pointer_cast<FreeChunk>(chunk));
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

// -----------------------------------------------------------------------------

void RevisionStoreFileParser::parseEncryptedData(
    QDataStream& ds, const EncryptedData_WPtr_t& chunk)
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

// -----------------------------------------------------------------------------

RevisionStoreFileHeader_SPtr_t
RevisionStoreFileParser::parseRevisionStoreFileHeader(QDataStream& ds)
{

  if (ds.device()->bytesAvailable() < 0x400) {
    qWarning("File size insufficient to be OneNote file.");
    return RevisionStoreFileHeader_SPtr_t();
  }
  // if byte order is big endian, change to little endian
  if (ds.byteOrder() == QDataStream::BigEndian) {
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
    return RevisionStoreFileHeader_SPtr_t();
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

// -----------------------------------------------------------------------------


FileNode_SPtr_t RevisionStoreFileParser::parseFileNode(
    QDataStream& ds, const FileNode_SPtr_t& fileNode)
{
  return parseFileNode(ds, fileNode->getInitialStp(), fileNode->getParent());
}


FileNode_SPtr_t RevisionStoreFileParser::parseFileNode(
    QDataStream& ds, const quint64 stp,
    const FileNodeListFragment_WPtr_t& parent)
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


  fn->fnt = parseFileNodeType(ds, fn);

  fn->m_isParsed = true;

  registerFileNodeData(fn);

  return fn;
}

// -----------------------------------------------------------------------------


void RevisionStoreFileParser::parseFileDataStoreObject(
    QDataStream& ds, const FileDataStoreObject_WPtr_t& fileData)
{


  auto chunk = fileData.lock();

  if (chunk != nullptr) {
    quint64 originalStp = ds.device()->pos();


    ds.device()->seek(chunk->getInitialStp());

    ds >> *chunk;

    chunk->m_isParsed = true;

    ds.device()->seek(originalStp);
  }
}

// -----------------------------------------------------------------------------

void RevisionStoreFileParser::parseFreeChunkListFragments(
    QDataStream& ds, const FreeChunkListFragment_WPtr_t& firstFragment)
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

// -----------------------------------------------------------------------------

void RevisionStoreFileParser::parseFreeChunk(const FreeChunk_SPtr_t& freeChunk)
{
  freeChunk->m_isParsed = true;
}
// -----------------------------------------------------------------------------

void RevisionStoreFileParser::parseObjectInfoDependencyOverrideData(
    QDataStream& ds, const ObjectInfoDependencyOverrideData_SPtr_t& objectInfo)
{
  if (objectInfo != nullptr) {

    quint64 originalStp = ds.device()->pos();


    ds.device()->seek(objectInfo->getInitialStp());

    ds >> *objectInfo;

    objectInfo->m_isParsed = true;


    ds.device()->seek(originalStp);
  }
}

// -----------------------------------------------------------------------------

ObjectSpaceObjectPropSet_SPtr_t
RevisionStoreFileParser::parseObjectSpaceObjectPropSet(
    QDataStream& ds, const ObjectSpaceObjectPropSet_SPtr_t& objectPropSet)
{
  qint64 originalPos = ds.device()->pos();
  ds.device()->seek(objectPropSet->getInitialStp());


  quint64 propSetStart = ds.device()->pos();
  ds >> objectPropSet->m_OIDs;

  if (objectPropSet->m_OIDs.getHeader().isOsidStreamNotPresent() == false) {
    ds >> objectPropSet->m_OSIDs;

    if (objectPropSet->m_OSIDs.getHeader().isExtendedStreamPresent() == true) {
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

// -----------------------------------------------------------------------------

FileNodeListFragment_SPtr_t RevisionStoreFileParser::parseFileNodeListFragment(
    QDataStream& ds, const FileNodeListFragment_SPtr_t& fragment)
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
  if (ds.byteOrder() == QDataStream::BigEndian) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }


  quint64 headerTest;
  ds >> headerTest;
  if (headerTest != FileNodeListFragment::header_magic_id) {
    qWarning("FileNodeListFragment header is invalid.");
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

// -----------------------------------------------------------------------------

std::vector<FileNodeListFragment_WPtr_t>
RevisionStoreFileParser::parseFileNodeList(
    QDataStream& ds, const FileNodeListFragment_WPtr_t& firstFragment)
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

// -----------------------------------------------------------------------------

bool RevisionStoreFileParser::parseTransactionLogFragment(
    QDataStream& ds, const TransactionLogFragment_SPtr_t& firstFragment)
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
      TransactionEntry_SPtr_t entry = std::make_shared<TransactionEntry>();
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


// -----------------------------------------------------------------------------

void RevisionStoreFileParser::parseUnknownBlob(
    QDataStream& ds, const UnknownBlob_SPtr_t& unknownBlob)
{
  qint64 originalStp = ds.device()->pos();

  ds.device()->seek(unknownBlob->getInitialStp());

  unknownBlob->m_blob = ds.device()->read(unknownBlob->getInitialCb());

  unknownBlob->m_isParsed = true;

  ds.device()->seek(originalStp);
}

void RevisionStoreFileParser::registerFileNodeData(const FileNode_SPtr_t& fn)
{
  //  Q_ASSERT(
  //      fn->getFileNodeTypeID() == FileNodeTypeID::GlobalIdTableEntry2FNDX ||
  //      fn->getFileNodeTypeID() == FileNodeTypeID::GlobalIdTableEntry3FNDX ||
  //      fn->getFileNodeTypeID() == FileNodeTypeID::GlobalIdTableEntryFNDX ||
  //      fn->getFileNodeTypeID() ==
  //      FileNodeTypeID::RevisionManifestListStartFND ||
  //      fn->getFileNodeTypeID() == FileNodeTypeID::RevisionManifestStart4FND
  //      || fn->getFileNodeTypeID() ==
  //      FileNodeTypeID::RevisionManifestStart6FND || fn->getFileNodeTypeID()
  //      ==
  //          FileNodeTypeID::RevisionRoleAndContextDeclarationFND ||
  //      fn->getFileNodeTypeID() ==
  //      FileNodeTypeID::RevisionRoleDeclarationFND);

  switch (fn->getFileNodeTypeID()) {
  case FileNodeTypeID::GlobalIdTableEntry2FNDX: {
    auto fnd = std::static_pointer_cast<GlobalIdTableEntry2FNDX>(fn->getFnt());
    auto dependentRevision =
        m_file->m_revisionsMap.at(m_file->m_currentRevision).getDependent();

    auto guid = m_file->m_revisionsMap.at(dependentRevision)
                    .m_globalId.at(fnd->m_iIndexMapFrom);

    if (guid.isNull()) {
      qWarning() << "GlobalIdTableEntry2FNDX could not find indexMapFrom GUID";
    }

    auto& rev = m_file->m_revisionsMap.at(m_file->m_currentRevision);
    rev.m_globalId.insert_or_assign(fnd->m_iIndexMapTo, guid);

    break;
  }
  case FileNodeTypeID::GlobalIdTableEntry3FNDX: {
    auto fnd = std::static_pointer_cast<GlobalIdTableEntry3FNDX>(fn->getFnt());
    const auto& dependentRevision =
        m_file->m_revisionsMap.at(m_file->m_currentRevision).getDependent();


    for (size_t i = 0; i < fnd->m_cEntriesToCopy; i++) {
      auto& globalIdMap =
          m_file->m_revisionsMap.at(dependentRevision).m_globalId;
      const auto& guid = globalIdMap.at(fnd->m_iIndexCopyFromStart + i);

      auto& currentIdMap =
          m_file->m_revisionsMap.at(m_file->m_currentRevision).m_globalId;

      currentIdMap.insert_or_assign(fnd->m_iIndexCopyToStart + i, guid);
    }

    break;
  }
  case FileNodeTypeID::GlobalIdTableEntryFNDX: {
    auto fnd  = std::static_pointer_cast<GlobalIdTableEntryFNDX>(fn->getFnt());
    auto& rev = m_file->m_revisionsMap.at(m_file->m_currentRevision);
    rev.m_globalId.insert_or_assign(fnd->m_index, fnd->m_guid);
    break;
  }
  case FileNodeTypeID::RevisionManifestListStartFND: {
    auto fnd =
        std::static_pointer_cast<RevisionManifestListStartFND>(fn->getFnt());
    registerRevisionManifestList(fnd->m_gosid, fn);
    break;
  }
  case FileNodeTypeID::RevisionManifestStart4FND: {
    registerRevisionManifest(fn);
    break;
  }
  case FileNodeTypeID::RevisionManifestStart6FND: {
    auto fnd =
        std::static_pointer_cast<RevisionManifestStart6FND>(fn->getFnt());
    registerAdditionalRevisionRole(
        fnd->m_rid, fnd->m_revisionRole, fnd->m_ridDependent);
    registerRevisionManifest(fn);
    break;
  }
  case FileNodeTypeID::RevisionRoleAndContextDeclarationFND: {
    auto fnd = std::static_pointer_cast<RevisionRoleAndContextDeclarationFND>(
        fn->getFnt());
    registerAdditionalRevisionRole(
        fnd->m_base.m_rid, fnd->m_base.m_RevisionRole, fnd->m_gctxid);
    break;
  }
  case FileNodeTypeID::RevisionRoleDeclarationFND: {
    auto fnd =
        std::static_pointer_cast<RevisionRoleDeclarationFND>(fn->getFnt());
    registerAdditionalRevisionRole(
        fnd->m_rid, fnd->m_RevisionRole, ExtendedGUID());
    break;
  }

  case FileNodeTypeID::FileDataStoreObjectReferenceFND: {

    auto fnd =
        std::static_pointer_cast<FileDataStoreObjectReferenceFND>(fn->getFnt());
    m_file->m_guidToRefMap.insert_or_assign(
        ExtendedGUID(fnd->getGuidReference(), 0),
        std::static_pointer_cast<Chunkable>(fnd->getBlobRef().lock()));
    break;
  }
  default: {
    // nothing to do
    break;
  }
  }
}

// -----------------------------------------------------------------------------


std::shared_ptr<IFileNodeType> RevisionStoreFileParser::parseFileNodeType(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{

  switch (fn->getFileNodeTypeID()) {

    // type 0 ------------------------------------------------------------------
  case FileNodeTypeID::ChunkTerminatorFND: {
    return parseChunkTerminatorFND(fn);
  }
  case FileNodeTypeID::DataSignatureGroupDefinitionFND: {
    return parseDataSignatureGroupDefinitionFND(ds, fn);
  }
  case FileNodeTypeID::GlobalIdTableEndFNDX: {
    return parseGlobalIdTableEndFNDX(fn);
  }
  case FileNodeTypeID::GlobalIdTableEntry2FNDX: {
    return parseGlobalIdTableEntry2FNDX(ds, fn);
  }
  case FileNodeTypeID::GlobalIdTableEntry3FNDX: {
    return parseGlobalIdTableEntry3FNDX(ds, fn);
  }
  case FileNodeTypeID::GlobalIdTableEntryFNDX: {
    return parseGlobalIdTableEntryFNDX(ds, fn);
  }
  case FileNodeTypeID::GlobalIdTableStart2FND: {
    return parseGlobalIdTableStart2FND(fn);
  }
  case FileNodeTypeID::GlobalIdTableStartFNDX: {
    return parseGlobalIdTableStartFNDX(ds, fn);
  }
  case FileNodeTypeID::ObjectDeclarationFileData3LargeRefCountFND: {
    return parseObjectDeclarationFileData3LargeRefCountFND(ds, fn);
  }
  case FileNodeTypeID::ObjectDeclarationFileData3RefCountFND: {
    return parseObjectDeclarationFileData3RefCountFND(ds, fn);
  }
  case FileNodeTypeID::ObjectGroupEndFND: {
    return parseObjectGroupEndFND(fn);
  }
  case FileNodeTypeID::ObjectGroupStartFND: {
    return parseObjectGroupStartFND(ds, fn);
  }
  case FileNodeTypeID::ObjectSpaceManifestListStartFND: {
    return parseObjectSpaceManifestListStartFND(ds, fn);
  }
  case FileNodeTypeID::ObjectSpaceManifestRootFND: {
    return parseObjectSpaceManifestRootFND(ds, fn);
  }
  case FileNodeTypeID::RevisionManifestEndFND: {
    return parseRevisionManifestEndFND(fn);
  }
  case FileNodeTypeID::RevisionManifestListStartFND: {
    return parseRevisionManifestListStartFND(ds, fn);
  }
  case FileNodeTypeID::RevisionManifestStart4FND: {
    return parseRevisionManifestStart4FND(ds, fn);
  }
  case FileNodeTypeID::RevisionManifestStart6FND: {
    return parseRevisionManifestStart6FND(ds, fn);
  }
  case FileNodeTypeID::RevisionManifestStart7FND: {
    return parseRevisionManifestStart7FND(ds, fn);
  }
  case FileNodeTypeID::RevisionRoleAndContextDeclarationFND: {
    return parseRevisionRoleAndContextDeclarationFND(ds, fn);
  }
  case FileNodeTypeID::RevisionRoleDeclarationFND: {
    return parseRevisionRoleDeclarationFND(ds, fn);
  }
  case FileNodeTypeID::RootObjectReference2FNDX: {
    return parseRootObjectReference2FNDX(ds, fn);
  }
  case FileNodeTypeID::RootObjectReference3FND: {
    return parseRootObjectReference3FND(ds, fn);
  }

  // type 1 ------------------------------------------------------------------
  case FileNodeTypeID::FileDataStoreObjectReferenceFND: {
    return parseFileDataStoreObjectReferenceFND(ds, fn);
  }
  case FileNodeTypeID::HashedChunkDescriptor2FND: {
    return parseHashedChunkDescriptor2FND(ds, fn);
  }
  case FileNodeTypeID::ObjectDataEncryptionKeyV2FNDX: {
    return parseObjectDataEncryptionKeyV2FNDX(ds, fn);
  }
  case FileNodeTypeID::ObjectDeclaration2LargeRefCountFND: {
    return parseObjectDeclaration2LargeRefCountFND(ds, fn);
  }
  case FileNodeTypeID::ObjectDeclaration2RefCountFND: {
    return parseObjectDeclaration2RefCountFND(ds, fn);
  }
  case FileNodeTypeID::ObjectDeclarationWithRefCount2FNDX: {
    return parseObjectDeclarationWithRefCount2FNDX(ds, fn);
  }
  case FileNodeTypeID::ReadOnlyObjectDeclaration2LargeRefCountFND: {
    return parseReadOnlyObjectDeclaration2LargeRefCountFND(ds, fn);
  }
  case FileNodeTypeID::ReadOnlyObjectDeclaration2RefCountFND: {
    return parseReadOnlyObjectDeclaration2RefCountFND(ds, fn);
  }
  case FileNodeTypeID::ObjectDeclarationWithRefCountFNDX: {
    return parseObjectDeclarationWithRefCountFNDX(ds, fn);
  }
  case FileNodeTypeID::ObjectInfoDependencyOverridesFND: {
    return parseObjectInfoDependencyOverridesFND(ds, fn);
  }
  case FileNodeTypeID::ObjectRevisionWithRefCount2FNDX: {
    return parseObjectRevisionWithRefCount2FNDX(ds, fn);
  }
  case FileNodeTypeID::ObjectRevisionWithRefCountFNDX: {
    return parseObjectRevisionWithRefCountFNDX(ds, fn);
  }

  // type 2 --------------------------------------------------------------------
  case FileNodeTypeID::FileDataStoreListReferenceFND: {
    return parseFileDataStoreListReferenceFND(ds, fn);
  }
  case FileNodeTypeID::ObjectGroupListReferenceFND: {
    return parseObjectGroupListReferenceFND(ds, fn);
  }
  case FileNodeTypeID::ObjectSpaceManifestListReferenceFND: {
    return parseObjectSpaceManifestListReferenceFND(ds, fn);
  }
  case FileNodeTypeID::RevisionManifestListReferenceFND: {
    return parseRevisionManifestListReferenceFND(ds, fn);
  }


  // needed to let FileNodeListFragment parser break out from loop
  case FileNodeTypeID::NullFnd: {
    return nullptr;
  }

  case FileNodeTypeID::InvalidFND:
  default:
    qInfo() << "FileNodeID: " << fn->getFileNodeID();
    qFatal("FileNode has a fileNodeTypeID which switches to "
           "default. Should not happen.");
  }
}

// FileNodeType parsers ------------------------------------------------------
// type 0 --------------------------------------------------------------------
ChunkTerminatorFND_SPtr_t
RevisionStoreFileParser::parseChunkTerminatorFND(const FileNode_SPtr_t& fn)
{
  Q_ASSERT(fn->getFileNodeTypeID() == FileNodeTypeID::ChunkTerminatorFND);

  auto fnd = std::make_shared<ChunkTerminatorFND>(fn);

  // no data

  return fnd;
}

DataSignatureGroupDefinitionFND_SPtr_t
RevisionStoreFileParser::parseDataSignatureGroupDefinitionFND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() ==
      FileNodeTypeID::DataSignatureGroupDefinitionFND);

  auto fnd = std::make_shared<DataSignatureGroupDefinitionFND>(fn);

  ds >> fnd->m_dataSignatureGroup;

  return fnd;
}

GlobalIdTableEndFNDX_SPtr_t
RevisionStoreFileParser::parseGlobalIdTableEndFNDX(const FileNode_SPtr_t& fn)
{
  Q_ASSERT(fn->getFileNodeTypeID() == FileNodeTypeID::GlobalIdTableEndFNDX);

  auto fnd = std::make_shared<GlobalIdTableEndFNDX>(fn);

  // no data

  return fnd;
}

GlobalIdTableEntry2FNDX_SPtr_t
RevisionStoreFileParser::parseGlobalIdTableEntry2FNDX(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(fn->getFileNodeTypeID() == FileNodeTypeID::GlobalIdTableEntry2FNDX);

  auto fnd = std::make_shared<GlobalIdTableEntry2FNDX>(fn);

  ds >> fnd->m_iIndexMapFrom;
  ds >> fnd->m_iIndexMapTo;


  return fnd;
}

GlobalIdTableEntry3FNDX_SPtr_t
RevisionStoreFileParser::parseGlobalIdTableEntry3FNDX(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(fn->getFileNodeTypeID() == FileNodeTypeID::GlobalIdTableEntry3FNDX);

  auto fnd = std::make_shared<GlobalIdTableEntry3FNDX>(fn);

  ds >> fnd->m_iIndexCopyFromStart;
  ds >> fnd->m_cEntriesToCopy;
  ds >> fnd->m_iIndexCopyToStart;


  return fnd;
}

GlobalIdTableEntryFNDX_SPtr_t
RevisionStoreFileParser::parseGlobalIdTableEntryFNDX(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(fn->getFileNodeTypeID() == FileNodeTypeID::GlobalIdTableEntryFNDX);

  auto fnd = std::make_shared<GlobalIdTableEntryFNDX>(fn);

  ds >> fnd->m_index;
  ds >> fnd->m_guid;

  return fnd;
}

GlobalIdTableStart2FND_SPtr_t
RevisionStoreFileParser::parseGlobalIdTableStart2FND(const FileNode_SPtr_t& fn)
{
  Q_ASSERT(fn->getFileNodeTypeID() == FileNodeTypeID::GlobalIdTableStart2FND);

  auto fnd = std::make_shared<GlobalIdTableStart2FND>(fn);

  // no data

  return fnd;
}

GlobalIdTableStartFNDX_SPtr_t
RevisionStoreFileParser::parseGlobalIdTableStartFNDX(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(fn->getFileNodeTypeID() == FileNodeTypeID::GlobalIdTableStartFNDX);

  auto fnd = std::make_shared<GlobalIdTableStartFNDX>(fn);

  ds >> fnd->m_reserved;

  return fnd;
}

ObjectDeclarationFileData3LargeRefCountFND_SPtr_t
RevisionStoreFileParser::parseObjectDeclarationFileData3LargeRefCountFND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() ==
      FileNodeTypeID::ObjectDeclarationFileData3LargeRefCountFND);

  auto fnd = std::make_shared<ObjectDeclarationFileData3LargeRefCountFND>(fn);

  ds >> fnd->m_oid;
  ds >> fnd->m_jcid;
  ds >> fnd->m_cRef;
  ds >> fnd->m_FileDataReference;
  ds >> fnd->m_Extension;

  return fnd;
}

ObjectDeclarationFileData3RefCountFND_SPtr_t
RevisionStoreFileParser::parseObjectDeclarationFileData3RefCountFND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() ==
      FileNodeTypeID::ObjectDeclarationFileData3RefCountFND);

  auto fnd = std::make_shared<ObjectDeclarationFileData3RefCountFND>(fn);

  ds >> fnd->m_oid;
  ds >> fnd->m_jcid;
  ds >> fnd->m_cRef;
  ds >> fnd->m_FileDataReference;
  ds >> fnd->m_Extension;

  return fnd;
}

ObjectGroupEndFND_SPtr_t
RevisionStoreFileParser::parseObjectGroupEndFND(const FileNode_SPtr_t& fn)
{
  Q_ASSERT(fn->getFileNodeTypeID() == FileNodeTypeID::ObjectGroupEndFND);

  auto fnd = std::make_shared<ObjectGroupEndFND>(fn);

  // nodata

  return fnd;
}

ObjectGroupStartFND_SPtr_t RevisionStoreFileParser::parseObjectGroupStartFND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(fn->getFileNodeTypeID() == FileNodeTypeID::ObjectGroupStartFND);

  auto fnd = std::make_shared<ObjectGroupStartFND>(fn);

  ds >> fnd->m_oid;

  return fnd;
}

ObjectSpaceManifestListStartFND_SPtr_t
RevisionStoreFileParser::parseObjectSpaceManifestListStartFND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() ==
      FileNodeTypeID::ObjectSpaceManifestListStartFND);

  auto fnd = std::make_shared<ObjectSpaceManifestListStartFND>(fn);

  ds >> fnd->m_gosid;

  return fnd;
}

ObjectSpaceManifestRootFND_SPtr_t
RevisionStoreFileParser::parseObjectSpaceManifestRootFND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() == FileNodeTypeID::ObjectSpaceManifestRootFND);

  auto fnd = std::make_shared<ObjectSpaceManifestRootFND>(fn);

  ds >> fnd->m_gosidRoot;

  return fnd;
}

RevisionManifestEndFND_SPtr_t
RevisionStoreFileParser::parseRevisionManifestEndFND(const FileNode_SPtr_t& fn)
{
  Q_ASSERT(fn->getFileNodeTypeID() == FileNodeTypeID::RevisionManifestEndFND);

  auto fnd = std::make_shared<RevisionManifestEndFND>(fn);

  // no data

  return fnd;
}

RevisionManifestListStartFND_SPtr_t
RevisionStoreFileParser::parseRevisionManifestListStartFND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() == FileNodeTypeID::RevisionManifestListStartFND);

  auto fnd = std::make_shared<RevisionManifestListStartFND>(fn);

  ds >> fnd->m_gosid;
  ds >> fnd->m_nInstance;


  return fnd;
}

RevisionManifestStart4FND_SPtr_t
RevisionStoreFileParser::parseRevisionManifestStart4FND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() == FileNodeTypeID::RevisionManifestStart4FND);

  auto fnd = std::make_shared<RevisionManifestStart4FND>(fn);

  ds >> fnd->m_rid;
  ds >> fnd->m_ridDependent;
  ds >> fnd->m_timeCreation;
  ds >> fnd->m_revisionRole;
  ds >> fnd->m_odcsDefault;

  return fnd;
}

RevisionManifestStart6FND_SPtr_t
RevisionStoreFileParser::parseRevisionManifestStart6FND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() == FileNodeTypeID::RevisionManifestStart6FND);

  auto fnd = std::make_shared<RevisionManifestStart6FND>(fn);

  ds >> fnd->m_rid;
  ds >> fnd->m_ridDependent;
  ds >> fnd->m_revisionRole;
  ds >> fnd->m_odcsDefault;

  return fnd;
}

RevisionManifestStart7FND_SPtr_t
RevisionStoreFileParser::parseRevisionManifestStart7FND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() == FileNodeTypeID::RevisionManifestStart7FND);

  auto fnd = std::make_shared<RevisionManifestStart7FND>(fn);

  ds >> fnd->m_base;
  ds >> fnd->m_gctxid;

  return fnd;
}

RevisionRoleAndContextDeclarationFND_SPtr_t
RevisionStoreFileParser::parseRevisionRoleAndContextDeclarationFND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() ==
      FileNodeTypeID::RevisionRoleAndContextDeclarationFND);

  auto fnd = std::make_shared<RevisionRoleAndContextDeclarationFND>(fn);

  ds >> fnd->m_base;
  ds >> fnd->m_gctxid;

  return fnd;
}

RevisionRoleDeclarationFND_SPtr_t
RevisionStoreFileParser::parseRevisionRoleDeclarationFND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() == FileNodeTypeID::RevisionRoleDeclarationFND);

  auto fnd = std::make_shared<RevisionRoleDeclarationFND>(fn);

  ds >> fnd->m_rid;
  ds >> fnd->m_RevisionRole;

  return fnd;
}

RootObjectReference2FNDX_SPtr_t
RevisionStoreFileParser::parseRootObjectReference2FNDX(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(fn->getFileNodeTypeID() == FileNodeTypeID::RootObjectReference2FNDX);

  auto fnd = std::make_shared<RootObjectReference2FNDX>(fn);

  ds >> fnd->m_oidRoot;
  ds >> fnd->m_RootRole;

  return fnd;
}

RootObjectReference3FND_SPtr_t
RevisionStoreFileParser::parseRootObjectReference3FND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(fn->getFileNodeTypeID() == FileNodeTypeID::RootObjectReference3FND);

  auto fnd = std::make_shared<RootObjectReference3FND>(fn);

  ds >> fnd->m_oidRoot;
  ds >> fnd->m_RootRole;

  return fnd;
}

// type 1 --------------------------------------------------------------------
FileDataStoreObjectReferenceFND_SPtr_t
RevisionStoreFileParser::parseFileDataStoreObjectReferenceFND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() ==
      FileNodeTypeID::FileDataStoreObjectReferenceFND);

  auto fnd = std::make_shared<FileDataStoreObjectReferenceFND>(fn);

  fnd->m_blobRef = parseFileNodeChunkReference<FileDataStoreObject>(ds, fn);

  ds >> fnd->m_guidReference;

  return fnd;
}

HashedChunkDescriptor2FND_SPtr_t
RevisionStoreFileParser::parseHashedChunkDescriptor2FND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() == FileNodeTypeID::HashedChunkDescriptor2FND);

  auto fnd = std::make_shared<HashedChunkDescriptor2FND>(fn);

  fnd->m_blobRef =
      parseFileNodeChunkReference<ObjectSpaceObjectPropSet>(ds, fn);


  fnd->m_guidHash = ds.device()->read(HashedChunkDescriptor2FND::guidHashWidth);

  return fnd;
}

ObjectDataEncryptionKeyV2FNDX_SPtr_t
RevisionStoreFileParser::parseObjectDataEncryptionKeyV2FNDX(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() == FileNodeTypeID::ObjectDataEncryptionKeyV2FNDX);

  auto fnd = std::make_shared<ObjectDataEncryptionKeyV2FNDX>(fn);

  fnd->m_blobRef = parseFileNodeChunkReference<EncryptedData>(ds, fn);

  return fnd;
}

ObjectDeclaration2LargeRefCountFND_SPtr_t
RevisionStoreFileParser::parseObjectDeclaration2LargeRefCountFND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() ==
      FileNodeTypeID::ObjectDeclaration2LargeRefCountFND);

  auto fnd = std::make_shared<ObjectDeclaration2LargeRefCountFND>(fn);

  fnd->m_blobRef =
      parseFileNodeChunkReference<ObjectSpaceObjectPropSet>(ds, fn);


  ds >> fnd->m_body;
  ds >> fnd->m_cRef;

  return fnd;
}

ObjectDeclaration2RefCountFND_SPtr_t
RevisionStoreFileParser::parseObjectDeclaration2RefCountFND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() == FileNodeTypeID::ObjectDeclaration2RefCountFND);

  auto fnd = std::make_shared<ObjectDeclaration2RefCountFND>(fn);

  fnd->m_blobRef =
      parseFileNodeChunkReference<ObjectSpaceObjectPropSet>(ds, fn);


  ds >> fnd->m_body;
  ds >> fnd->m_cRef;

  return fnd;
}

ObjectDeclarationWithRefCount2FNDX_SPtr_t
RevisionStoreFileParser::parseObjectDeclarationWithRefCount2FNDX(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() ==
      FileNodeTypeID::ObjectDeclarationWithRefCount2FNDX);

  auto fnd = std::make_shared<ObjectDeclarationWithRefCount2FNDX>(fn);

  fnd->m_objectRef =
      parseFileNodeChunkReference<ObjectSpaceObjectPropSet>(ds, fn);


  ds >> fnd->m_body;
  ds >> fnd->m_cRef;

  return fnd;
}

ReadOnlyObjectDeclaration2LargeRefCountFND_SPtr_t
RevisionStoreFileParser::parseReadOnlyObjectDeclaration2LargeRefCountFND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() ==
      FileNodeTypeID::ReadOnlyObjectDeclaration2LargeRefCountFND);

  auto fnd = std::make_shared<ReadOnlyObjectDeclaration2LargeRefCountFND>(fn);

  fnd->m_blobRef =
      parseFileNodeChunkReference<ObjectSpaceObjectPropSet>(ds, fn);


  ds >> fnd->m_body;
  ds >> fnd->m_cRef;

  fnd->setMd5hash(ds.device()->read(
      ReadOnlyObjectDeclaration2LargeRefCountFND::md5HashSize));

  return fnd;
}

ReadOnlyObjectDeclaration2RefCountFND_SPtr_t
RevisionStoreFileParser::parseReadOnlyObjectDeclaration2RefCountFND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() ==
      FileNodeTypeID::ReadOnlyObjectDeclaration2RefCountFND);

  auto fnd = std::make_shared<ReadOnlyObjectDeclaration2RefCountFND>(fn);

  fnd->m_blobRef =
      parseFileNodeChunkReference<ObjectSpaceObjectPropSet>(ds, fn);


  ds >> fnd->m_body;
  ds >> fnd->m_cRef;

  fnd->setMd5hash(ds.device()->read(
      ReadOnlyObjectDeclaration2LargeRefCountFND::md5HashSize));

  return fnd;
}

ObjectDeclarationWithRefCountFNDX_SPtr_t
RevisionStoreFileParser::parseObjectDeclarationWithRefCountFNDX(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() ==
      FileNodeTypeID::ObjectDeclarationWithRefCountFNDX);

  auto fnd = std::make_shared<ObjectDeclarationWithRefCountFNDX>(fn);

  fnd->m_objectRef =
      parseFileNodeChunkReference<ObjectSpaceObjectPropSet>(ds, fn);

  ds >> fnd->m_body;
  ds >> fnd->m_cRef;

  return fnd;
}

ObjectInfoDependencyOverridesFND_SPtr_t
RevisionStoreFileParser::parseObjectInfoDependencyOverridesFND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() ==
      FileNodeTypeID::ObjectInfoDependencyOverridesFND);

  auto fnd = std::make_shared<ObjectInfoDependencyOverridesFND>(fn);

  fnd->m_ref =
      parseFileNodeChunkReference<ObjectInfoDependencyOverrideData>(ds, fn);

  if (fnd->m_ref.lock() == nullptr) {
    ds >> fnd->m_data;
  }

  return fnd;
}

ObjectRevisionWithRefCount2FNDX_SPtr_t
RevisionStoreFileParser::parseObjectRevisionWithRefCount2FNDX(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() ==
      FileNodeTypeID::ObjectRevisionWithRefCount2FNDX);

  auto fnd = std::make_shared<ObjectRevisionWithRefCount2FNDX>(fn);

  fnd->m_ref = parseFileNodeChunkReference<ObjectSpaceObjectPropSet>(ds, fn);

  ds >> fnd->m_oid;

  quint32 composite = 0;
  ds >> composite;
  fnd->m_fHasOidReferences  = static_cast<bool>(composite & 0x1u);
  fnd->m_fHasOsidReferences = static_cast<bool>((composite & 0x2u) >> 1u);

  ds >> fnd->m_cRef;

  return fnd;
}

ObjectRevisionWithRefCountFNDX_SPtr_t
RevisionStoreFileParser::parseObjectRevisionWithRefCountFNDX(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() ==
      FileNodeTypeID::ObjectRevisionWithRefCountFNDX);

  auto fnd = std::make_shared<ObjectRevisionWithRefCountFNDX>(fn);

  fnd->m_ref = parseFileNodeChunkReference<ObjectSpaceObjectPropSet>(ds, fn);

  ds >> fnd->m_oid;


  /// \todo use temporary storage before assigning just as above
  ds >> fnd->m_cRef;
  fnd->m_fHasOidReferences  = ((fnd->m_cRef & 0x1u) != 0u);
  fnd->m_fHasOsidReferences = ((fnd->m_cRef & 0x2u) != 0u);
  fnd->m_cRef >>= 2u;

  return fnd;
}

// type 2 --------------------------------------------------------------------
FileDataStoreListReferenceFND_SPtr_t
RevisionStoreFileParser::parseFileDataStoreListReferenceFND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() == FileNodeTypeID::FileDataStoreListReferenceFND);

  auto fnd = std::make_shared<FileDataStoreListReferenceFND>(fn);

  fnd->m_ref = parseFileNodeChunkReference<FileNodeListFragment>(ds, fn);

  return fnd;
}

ObjectGroupListReferenceFND_SPtr_t
RevisionStoreFileParser::parseObjectGroupListReferenceFND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() == FileNodeTypeID::ObjectGroupListReferenceFND);

  auto fnd = std::make_shared<ObjectGroupListReferenceFND>(fn);

  fnd->m_ref = parseFileNodeChunkReference<FileNodeListFragment>(ds, fn);

  ds >> fnd->m_ObjectGroupID;

  return fnd;
}

ObjectSpaceManifestListReferenceFND_SPtr_t
RevisionStoreFileParser::parseObjectSpaceManifestListReferenceFND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() ==
      FileNodeTypeID::ObjectSpaceManifestListReferenceFND);

  auto fnd = std::make_shared<ObjectSpaceManifestListReferenceFND>(fn);

  fnd->m_ref = parseFileNodeChunkReference<FileNodeListFragment>(ds, fn);

  ds >> fnd->m_gosid;

  return fnd;
}

RevisionManifestListReferenceFND_SPtr_t
RevisionStoreFileParser::parseRevisionManifestListReferenceFND(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() ==
      FileNodeTypeID::RevisionManifestListReferenceFND);

  auto fnd = std::make_shared<RevisionManifestListReferenceFND>(fn);

  fnd->m_ref = parseFileNodeChunkReference<FileNodeListFragment>(ds, fn);

  return fnd;
}


// Other non-chunkables --------------------------------------------------------


ObjectSpaceManifestList_SPtr_t
RevisionStoreFileParser::parseObjectSpaceManifestList(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() ==
      FileNodeTypeID::ObjectSpaceManifestListReferenceFND);

  if (fn->getFileNodeTypeID() !=
      FileNodeTypeID::ObjectSpaceManifestListReferenceFND) {
    qDebug() << "FileNodeID" << fn->getFileNodeID();
    qFatal("parseObjectSpaceManifestList was called with a FileNode which is "
           "not of type ObjectSpaceManifestListReferenceFND");
  }


  auto manifestList = std::make_shared<ObjectSpaceManifestList>(fn);


  auto fndRef =
      std::static_pointer_cast<ObjectSpaceManifestListReferenceFND>(fn->fnt);

  manifestList->m_gosid = fndRef->getGosid();

  manifestList->m_fileNodeListFragments =
      parseFileNodeList(ds, fndRef->getRef());


  // capture the ObjectSpaceManifestListStartFND which should be the first
  // element in the FNLF tree.
  auto firstFragment = manifestList->m_fileNodeListFragments.at(0).lock();

  auto firstFileNodeInFragmentTree = *(firstFragment->getFileNodes().begin());


  if (firstFileNodeInFragmentTree->getFileNodeTypeID() !=
      FileNodeTypeID::ObjectSpaceManifestListStartFND) {
    qFatal("ObjectSpaceManifestList is ill-formed. First element should "
           "be ObjectSpaceManifestListStartFND, but isn't");
  }

  manifestList->m_objectSpaceManifestListStartFND = firstFileNodeInFragmentTree;

  // getting refs for the RevisionManifestLists


  std::vector<FileNode_SPtr_t> revisionManifestListRefs{};

  for (const auto& fragRef : manifestList->m_fileNodeListFragments) {
    auto frag = fragRef.lock();
    std::copy_if(
        frag->m_fileNodes.begin(), frag->m_fileNodes.end(),
        back_inserter(revisionManifestListRefs),
        [](const std::shared_ptr<FileNode>& entry) {
          return entry->getFileNodeTypeID() ==
                 FileNodeTypeID::RevisionManifestListReferenceFND;
        });
  }


  for (const auto& entry : revisionManifestListRefs) {


    manifestList->m_revisionManifestLists.push_back(
        parseRevisionManifestList(ds, entry, manifestList));
  }

  return manifestList;
}

std::shared_ptr<RevisionManifestList>
RevisionStoreFileParser::parseRevisionManifestList(
    QDataStream& ds, const FileNode_SPtr_t& fn,
    const ObjectSpaceManifestList_SPtr_t& parent)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() ==
      FileNodeTypeID::RevisionManifestListReferenceFND);

  if (fn->getFileNodeTypeID() !=
      FileNodeTypeID::RevisionManifestListReferenceFND) {
    qDebug() << "FileNodeID" << fn->getFileNodeID();
    qFatal("parseRevisionManifestList was called with a FileNode which is "
           "not of type RevisionManifestListReferenceFND");
  }

  auto revisionManifestList = std::make_shared<RevisionManifestList>(parent);

  auto fndRef =
      std::static_pointer_cast<RevisionManifestListReferenceFND>(fn->fnt);

  revisionManifestList->m_fileNodeListFragments =
      parseFileNodeList(ds, fndRef->getRef());


  for (const auto& fragRef : revisionManifestList->m_fileNodeListFragments) {
    auto frag = fragRef.lock();

    std::copy_if(
        frag->m_fileNodes.begin(), frag->m_fileNodes.end(),
        back_inserter(revisionManifestList->m_RevisionRoleDeclarations),
        [](const std::shared_ptr<FileNode>& entry) {
          return entry->getFileNodeTypeID() ==
                 FileNodeTypeID::RevisionRoleDeclarationFND;
        });

    std::copy_if(
        frag->m_fileNodes.begin(), frag->m_fileNodes.end(),
        back_inserter(
            revisionManifestList->m_RevisionRoleAndContextDeclarations),
        [](const std::shared_ptr<FileNode>& entry) {
          return entry->getFileNodeTypeID() ==
                 FileNodeTypeID::RevisionRoleAndContextDeclarationFND;
        });
  }


  auto revManifest = std::make_shared<RevisionManifest>(revisionManifestList);

  for (const auto& fragRef : revisionManifestList->m_fileNodeListFragments) {
    auto frag = fragRef.lock();

    for (const auto& cfn : frag->m_fileNodes) {

      switch (cfn->getFileNodeTypeID()) {
      case FileNodeTypeID::RevisionManifestStart6FND:
      case FileNodeTypeID::RevisionManifestStart7FND:
      case FileNodeTypeID::RevisionManifestStart4FND: {
        revManifest = std::make_shared<RevisionManifest>(revisionManifestList);

        revManifest->m_FileNodeSequence.push_back(cfn);
        break;
      }

      case FileNodeTypeID::RevisionManifestEndFND: {
        revManifest->m_FileNodeSequence.push_back(cfn);
        revisionManifestList->m_RevisionManifests.push_back(revManifest);
        revManifest = std::make_shared<RevisionManifest>(revisionManifestList);
        break;
      }
      case FileNodeTypeID::ChunkTerminatorFND:
      case FileNodeTypeID::RevisionManifestListStartFND:
        break;
      case FileNodeTypeID::ObjectDataEncryptionKeyV2FNDX:
        m_file->m_isEncrypted = true;
        revManifest->m_FileNodeSequence.push_back(cfn);
        break;
      default: {
        revManifest->m_FileNodeSequence.push_back(cfn);
        if (cfn->getFileNodeTypeID() ==
            FileNodeTypeID::ObjectGroupListReferenceFND) {


          revManifest->m_ObjectGroupLists.push_back(
              parseObjectGroupList(ds, cfn, revManifest));
        }
        break;
      }
      }
    }
  }

  return revisionManifestList;
}

std::shared_ptr<ObjectGroupList> RevisionStoreFileParser::parseObjectGroupList(
    QDataStream& ds, const FileNode_SPtr_t& fn,
    const std::shared_ptr<RevisionManifest>& parent)
{
  auto objectGroupList = std::make_shared<ObjectGroupList>(parent);

  const auto objectGroupListRef =
      std::dynamic_pointer_cast<ObjectGroupListReferenceFND>(fn->getFnt())
          ->getRef();


  objectGroupList->m_fileNodeListFragments =
      parseFileNodeList(ds, objectGroupListRef);


  return objectGroupList;
}


// Utility functions -----------------------------------------------------------

template <class Chunkably>
std::shared_ptr<Chunkably> RevisionStoreFileParser::parseFileNodeChunkReference(
    QDataStream& ds, const FileNode_SPtr_t& fn)
{
  FileNodeChunkReference ref(fn->stpFormat, fn->cbFormat);
  ds >> ref;

  if (!ref.is_fcrNil() && !ref.is_fcrZero()) {
    auto chunkable = std::make_shared<Chunkably>(ref.stp(), ref.cb());

    chunkable = insertChunkSorted(m_file->chunks(), chunkable);

    return chunkable;
  }

  /// return nullptr
  return std::make_shared<Chunkably>();
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

  // if iterator(it) is at the end push_front since we are reverse-looping
  chunkList.push_front(chunk);

  return chunk;
}

void RevisionStoreFileParser::registerRevisionManifestList(
    const ExtendedGUID& guid, const FileNode_SPtr_t& fn)
{
  m_file->m_revisionManifestListsMap.insert({guid, fn});
  m_file->m_revisionOrder.push_back(guid);
}

void RevisionStoreFileParser::registerRevisionManifest(
    const FileNode_SPtr_t& fn)
{
  Q_ASSERT(
      fn->getFileNodeTypeID() == FileNodeTypeID::RevisionManifestStart4FND ||
      fn->getFileNodeTypeID() == FileNodeTypeID::RevisionManifestStart6FND ||
      fn->getFileNodeTypeID() == FileNodeTypeID::RevisionManifestStart7FND);

  ExtendedGUID thisGosid;
  ExtendedGUID thisDependent;

  if (fn->getFileNodeTypeID() == FileNodeTypeID::RevisionManifestStart4FND) {
    auto thisFnd =
        std::static_pointer_cast<RevisionManifestStart4FND>(fn->getFnt());

    thisGosid     = thisFnd->getRid();
    thisDependent = thisFnd->getRidDependent();
  }
  else if (
      fn->getFileNodeTypeID() == FileNodeTypeID::RevisionManifestStart6FND) {
    auto thisFnd =
        std::static_pointer_cast<RevisionManifestStart6FND>(fn->getFnt());

    thisGosid     = thisFnd->getRid();
    thisDependent = thisFnd->getRidDependent();
  }
  else if (
      fn->getFileNodeTypeID() == FileNodeTypeID::RevisionManifestStart7FND) {
    auto thisFnd =
        std::static_pointer_cast<RevisionManifestStart7FND>(fn->getFnt());

    thisGosid     = thisFnd->getRid();
    thisDependent = thisFnd->getRidDependent();
  }


  m_file->m_revisionsMap.try_emplace(thisGosid, Revision());

  Revision& toModify = m_file->m_revisionsMap.at(thisGosid);

  //  toModify.m_gosid = thisGosid;  /* seems unnecessary */

  toModify.m_dependent      = thisDependent;
  m_file->m_currentRevision = thisGosid;
}

void RevisionStoreFileParser::registerAdditionalRevisionRole(
    const ExtendedGUID& guid, const quint32 revisionRole,
    const ExtendedGUID& gctxid)
{
  m_file->m_revisionRolesMap.insert({guid, {revisionRole, gctxid}});
}


} // namespace priv
} // namespace libmson
