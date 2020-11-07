#include "RevisionStoreFile2.h"

#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QUuid>

#include "chunks/Chunkable.h"
#include "chunks/FileNode.h"
#include "chunks/FileNodeListFragment.h"
#include "chunks/FreeChunk.h"
#include "chunks/FreeChunkListFragment.h"
#include "chunks/RevisionStoreFileHeader.h"

#include "helper/CrcAlgorithms.h"

#include "FileNodeTypes/ChunkTerminatorFND.h"
#include "FileNodeTypes/DataSignatureGroupDefinitionFND.h"
//#include "FileNodeTypes/FileDataStoreListReferenceFND.h"
//#include "FileNodeTypes/FileDataStoreObjectReferenceFND.h"
#include "FileNodeTypes/GlobalIdTableEndFNDX.h"
#include "FileNodeTypes/GlobalIdTableEntry2FNDX.h"
#include "FileNodeTypes/GlobalIdTableEntry3FNDX.h"
#include "FileNodeTypes/GlobalIdTableEntryFNDX.h"
#include "FileNodeTypes/GlobalIdTableStart2FND.h"
#include "FileNodeTypes/GlobalIdTableStartFNDX.h"
#include "FileNodeTypes/HashedChunkDescriptor2FND.h"
#include "FileNodeTypes/ObjectDataEncryptionKeyV2FNDX.h"
#include "FileNodeTypes/ObjectDeclaration2LargeRefCountFND.h"
#include "FileNodeTypes/ObjectDeclaration2RefCountFND.h"
#include "FileNodeTypes/ObjectDeclarationFileData3LargeRefCountFND.h"
#include "FileNodeTypes/ObjectDeclarationFileData3RefCountFND.h"
#include "FileNodeTypes/ObjectDeclarationWithRefCount2FNDX.h"
#include "FileNodeTypes/ObjectDeclarationWithRefCountFNDX.h"
#include "FileNodeTypes/ObjectGroupEndFND.h"
#include "FileNodeTypes/ObjectGroupListReferenceFND.h"
#include "FileNodeTypes/ObjectGroupStartFND.h"
#include "FileNodeTypes/ObjectInfoDependencyOverridesFND.h"
#include "FileNodeTypes/ObjectRevisionWithRefCount2FNDX.h"
#include "FileNodeTypes/ObjectRevisionWithRefCountFNDX.h"
#include "FileNodeTypes/ObjectSpaceManifestListReferenceFND.h"
#include "FileNodeTypes/ObjectSpaceManifestListStartFND.h"
#include "FileNodeTypes/ObjectSpaceManifestRootFND.h"
#include "FileNodeTypes/ReadOnlyObjectDeclaration2LargeRefCountFND.h"
#include "FileNodeTypes/ReadOnlyObjectDeclaration2RefCountFND.h"
#include "FileNodeTypes/RevisionManifestEndFND.h"
#include "FileNodeTypes/RevisionManifestListReferenceFND.h"
#include "FileNodeTypes/RevisionManifestListStartFND.h"
#include "FileNodeTypes/RevisionManifestStart4FND.h"
#include "FileNodeTypes/RevisionManifestStart6FND.h"
#include "FileNodeTypes/RevisionManifestStart7FND.h"
#include "FileNodeTypes/RevisionRoleAndContextDeclarationFND.h"
#include "FileNodeTypes/RevisionRoleDeclarationFND.h"
#include "FileNodeTypes/RootObjectReference2FNDX.h"
#include "FileNodeTypes/RootObjectReference3FND.h"

namespace libmson {

RevisionStoreFile::RevisionStoreFile() {}

bool RevisionStoreFile::open(const QString &fileName) {
  QFile file(fileName);
  bool couldopen = file.open(QIODevice::ReadOnly);

  if (!couldopen) {
    qWarning("Could not open file.");
    return false;
  }

  m_ds.setDevice(&file);

  if (!parseHeader()) {
    return false;
  }

  auto header = std::static_pointer_cast<RevisionStoreFileHeader>(
      m_chunks.begin()->get()->getContent());

  deserializeFileNodeListFragment(m_ds,header->fcrFileNodeListRoot.lock());

  file.close();

  return couldopen;
}

bool RevisionStoreFile::write(const QString &fileName) {
  QFile file(fileName);

  bool couldopen = file.open(QIODevice::WriteOnly);

  if (!couldopen) {
    qWarning("Could not open file.");
    return false;
  }

  m_ds.setDevice(&file);

  if (!writeHeader(m_ds)) {
    return false;
  }

  for (auto &chunk : m_chunks) {
    writeChunk(chunk);
  }

  return true;
}

bool RevisionStoreFile::parseHeader() {
  if (m_ds.device()->bytesAvailable() < 0x400) {
    qWarning("File size insufficient to be OneNote file.");
    return false;
  }
  // if byte order is big endian, change to little endian
  if (m_ds.byteOrder() == QDataStream::BigEndian) {
    m_ds.setByteOrder(QDataStream::LittleEndian);
  }

  auto headerChunk = std::make_shared<RevisionStoreChunkContainer>(
      std::make_shared<RevisionStoreFileHeader>(), 0u,
      RevisionStoreFileHeader::sizeInFile);

  m_chunks.push_back(headerChunk);

  auto header = std::static_pointer_cast<RevisionStoreFileHeader>(
      headerChunk->getChunk());

  m_ds >> header->guidFileType;
  m_ds >> header->guidFile;
  m_ds >> header->guidLegacyFileVersion;
  if (header->guidLegacyFileVersion != header->v_guidLegacyFileVersion) {
    qWarning(
        "guidLegacyFileVersion of the RevisionStoreFileHeader is invalid.");
  }
  m_ds >> header->guidFileFormat;
  if (header->guidFileFormat != header->v_guidFileFormat) {
    qWarning("guidFileFormat of the RevisionStoreFileHeader is invalid.");
    return false;
  }
  m_ds >> header->ffvLastWriterVersion;
  m_ds >> header->ffvOldestWriterVersion;
  m_ds >> header->ffvNewestWriterVersion;
  m_ds >> header->ffvOldestReader;

  MSONcommon::FileChunkReference32 fcrLegacyFreeChunkList;
  m_ds >> fcrLegacyFreeChunkList;
  if (!fcrLegacyFreeChunkList.is_fcrZero()) {
    qWarning(
        "fcrLegacyFreeChunkList of the RevisionStoreFileHeader is invalid.");
  }

  MSONcommon::FileChunkReference32 fcrLegacyTransactionLog;
  m_ds >> fcrLegacyTransactionLog;
  if (!fcrLegacyTransactionLog.is_fcrNil()) {
    qWarning(
        "fcrLegacyTransactionLog of the RevisionStoreFileHeader is invalid.");
  }

  m_ds >> header->cTransactionsInLog;

  quint32 cbLegacyExpectedFileLength;
  m_ds >> cbLegacyExpectedFileLength;
  if (cbLegacyExpectedFileLength != 0u) {
    qWarning("cbLegacyExpectedFileLength of the RevisionStoreFileHeader is "
             "invalid.");
  }

  m_ds >> header->rgbPlaceholder;

  MSONcommon::FileChunkReference32 fcrLegacyFileNodeListRoot;
  m_ds >> fcrLegacyFileNodeListRoot;
  if (!fcrLegacyFileNodeListRoot.is_fcrNil()) {
    qWarning(
        "fcrLegacyFileNodeListRoot of the RevisionStoreFileHeader is invalid.");
  }

  quint32 cbLegacyFreeSpaceInFreeChunkList;
  m_ds >> cbLegacyFreeSpaceInFreeChunkList;
  if (cbLegacyFreeSpaceInFreeChunkList != 0u) {
    qWarning("cbLegacyFreeSpaceInFreeChunkList of the RevisionStoreFileHeader "
             "is invalid.");
  }

  m_ds >> header->fNeedsDefrag;
  m_ds >> header->fRepairedFile;
  m_ds >> header->fNeedsGarbageCollect;
  m_ds >> header->fHasNoEmbeddedFileObjects;
  m_ds >> header->guidAncestor;
  m_ds >> header->crcName;

  MSONcommon::FileChunkReference64x32 fcrHashedChunkList;
  m_ds >> fcrHashedChunkList;

  if (!fcrHashedChunkList.is_fcrNil() && !fcrHashedChunkList.is_fcrZero()) {

    //    m_chunks.push_back(std::make_shared<RevisionStoreChunk>(
    //        RevisionStoreFileHeader(),
    //        RevisionStoreChunkType::File, 0u))

    //    m_chunks.push_back(headerChunk);
  }

  MSONcommon::FileChunkReference64x32 fcrTransactionLog;
  m_ds >> fcrTransactionLog;
  if (!fcrTransactionLog.is_fcrNil() && !fcrTransactionLog.is_fcrZero()) {
  }

  MSONcommon::FileChunkReference64x32 fcrFileNodeListRoot;
  m_ds >> fcrFileNodeListRoot;
  if (!fcrFileNodeListRoot.is_fcrNil() && !fcrFileNodeListRoot.is_fcrZero()) {

    auto fileNodeListRootChunk = std::make_shared<RevisionStoreChunkContainer>(
        std::make_shared<FileNodeListFragment>(), fcrFileNodeListRoot.stp(),
        fcrFileNodeListRoot.cb());

    insertChunkSorted(fileNodeListRootChunk);

    header->fcrFileNodeListRoot = fileNodeListRootChunk;
  }

  MSONcommon::FileChunkReference64x32 fcrFreeChunkList;
  m_ds >> fcrFreeChunkList;
  if (!fcrFreeChunkList.is_fcrNil() && !fcrFreeChunkList.is_fcrZero()) {

    auto freeChunkListFragment = std::make_shared<RevisionStoreChunkContainer>(
        std::make_shared<FreeChunkListFragment>(fcrFreeChunkList.cb()),
        fcrFreeChunkList.stp(), fcrFreeChunkList.cb());

    insertChunkSorted(freeChunkListFragment);

    header->fcrFreeChunkList = freeChunkListFragment;
  }

  m_ds >> header->cbExpectedFileLength;
  m_ds >> header->cbFreeSpaceInFreeChunkList;
  m_ds >> header->guidFileVersion;
  m_ds >> header->nFileVersionGeneration;
  m_ds >> header->guidDenyReadFileVersion;
  m_ds >> header->grfDebugLogFlags;

  MSONcommon::FileChunkReference64x32 fcrDebugLog;
  m_ds >> fcrDebugLog;
  if (!fcrDebugLog.is_fcrZero()) {
    qWarning(
        "fcrLegacyFreeChunkList of the RevisionStoreFileHeader is invalid.");
  }

  MSONcommon::FileChunkReference64x32 fcrAllocVerificationFreeChunkList;
  m_ds >> fcrAllocVerificationFreeChunkList;
  if (!fcrAllocVerificationFreeChunkList.is_fcrZero()) {
    qWarning(
        "fcrLegacyFreeChunkList of the RevisionStoreFileHeader is invalid.");
  }

  m_ds >> header->bnCreated;
  m_ds >> header->bnLastWroteToThisFile;
  m_ds >> header->bnOldestWritten;
  m_ds >> header->bnNewestWritten;
  m_ds.skipRawData(header->def_reservedHeaderTailLength);

  /// \todo further Validate header
  return true;
}

bool RevisionStoreFile::writeHeader(QDataStream &ds) {
  if (m_chunks.size() < 1) {
    qWarning("Did not find Header chunk in memory");
    return false;
  }

  if (m_chunks.begin()->get()->getType() !=
      RevisionStoreChunkType::RevistionStoreFileHeader) {
    qWarning("First Chunk of RevisionStoreFile in memory is not a "
             "RevistionStoreFileHeader");
    return false;
  }

  // if byte order is big endian, change to little endian
  if (ds.byteOrder() == QDataStream::BigEndian) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  auto header = std::static_pointer_cast<RevisionStoreFileHeader>(
      m_chunks.begin()->get()->getContent());

  quint64 totalFileSize = 0;

  auto addCb = [](quint64 a, std::shared_ptr<RevisionStoreChunkContainer> b) {
    return std::move(a) + b->cb();
  };

  totalFileSize = std::accumulate(m_chunks.begin(), m_chunks.end(), 0, addCb);

  // Updating the header;
  header->cbExpectedFileLength = totalFileSize;
  header->crcName = MSONcommon::Crc32::computeCrcName(m_fileName);
  /// \todo update cTransactionsInLog

  ds << header->guidFileType;
  ds << header->guidFile;
  ds << header->v_guidLegacyFileVersion;
  ds << header->v_guidFileFormat;
  ds << header->ffvLastWriterVersion;
  ds << header->ffvOldestWriterVersion;
  ds << header->ffvNewestWriterVersion;
  ds << header->ffvOldestReader;

  // fcrLegacyFreeChunkList
  ds << MSONcommon::FileChunkReference32(MSONcommon::FCR_INITTYPE::FCRZERO);
  // fcrLegacyTransactionLog
  ds << MSONcommon::FileChunkReference32(MSONcommon::FCR_INITTYPE::FCRNIL);

  ds << header->cTransactionsInLog;

  quint32 cbLegacyExpectedFileLength = 0u;
  ds << cbLegacyExpectedFileLength;

  ds << header->rgbPlaceholder;

  // fcrLegacyFileNodeListRoot
  ds << MSONcommon::FileChunkReference32(MSONcommon::FCR_INITTYPE::FCRNIL);

  quint32 cbLegacyFreeSpaceInFreeChunkList = 0u;
  ds << cbLegacyFreeSpaceInFreeChunkList;

  ds << header->fNeedsDefrag;
  ds << header->fRepairedFile;
  ds << header->fNeedsGarbageCollect;
  ds << header->fHasNoEmbeddedFileObjects;
  ds << header->guidAncestor;
  ds << header->crcName;

  // fcrHashedChunkList
  ds << getFcr64x32FromChunk(header->fcrHashedChunkList);

  // fcrTransactionLog
  ds << getFcr64x32FromChunk(header->fcrTransactionLog);

  // fcrFileNodeListRoot
  ds << getFcr64x32FromChunk(header->fcrFileNodeListRoot);

  // fcrFreeChunkList
  ds << getFcr64x32FromChunk(header->fcrFreeChunkList);

  ds << header->cbExpectedFileLength;
  ds << header->cbFreeSpaceInFreeChunkList;
  ds << header->guidFileVersion;
  ds << header->nFileVersionGeneration;
  ds << header->guidDenyReadFileVersion;
  ds << header->grfDebugLogFlags;

  // fcrDebugLog
  ds << MSONcommon::FileChunkReference64x32(MSONcommon::FCR_INITTYPE::FCRZERO);

  // fcrAllocVerificationFreeChunkList
  ds << MSONcommon::FileChunkReference64x32(MSONcommon::FCR_INITTYPE::FCRZERO);

  ds << header->bnCreated;
  ds << header->bnLastWroteToThisFile;
  ds << header->bnOldestWritten;
  ds << header->bnNewestWritten;

  ds.device()->write(QByteArray(header->def_reservedHeaderTailLength, '\0'));

  return true;
}

bool RevisionStoreFile::writeChunk(std::shared_ptr<RevisionStoreChunkContainer> chunk) {
  switch (chunk->getType()) {

  case RevisionStoreChunkType::RevistionStoreFileHeader:
    qWarning("Trying to write another header mid-stream");
    break;
  case RevisionStoreChunkType::FileNodeListFragment:
    return writeFileNodeListFragment(chunk);
  case RevisionStoreChunkType::FileNode:
    return writeFileNode(chunk);
  case RevisionStoreChunkType::FreeChunkListFragment:
    return writeFreeChunkListFragment(chunk);
  case RevisionStoreChunkType::FreeChunk:
    return writeFreeChunk(chunk);
  case RevisionStoreChunkType::TransactionLogFragment:
    break;
  case RevisionStoreChunkType::FileDataStoreObject:
    break;
  case RevisionStoreChunkType::ObjectSpaceObjectPropSet:
    break;
  case RevisionStoreChunkType::ObjectInfoDependencyOverrideData:
    break;
  case RevisionStoreChunkType::EncryptedFragment:
    break;
  case RevisionStoreChunkType::Invalid:
  default:
    qFatal("Failed to initialize invalid RevisionStoreChunkType.");
  }

  return true;
}

bool RevisionStoreFile::writeFreeChunkListFragment(
    std::shared_ptr<RevisionStoreChunkContainer> chunk) {

  if (chunk->getType() != RevisionStoreChunkType::FreeChunkListFragment) {
    qWarning("Tried writing chunk with wrong method (FreeChunkListFragment)");
    return false;
  }

  auto fclf =
      std::static_pointer_cast<FreeChunkListFragment>(chunk->getChunk());

  m_ds << fclf->getCrc();

  m_ds << getFcr64x32FromChunk(fclf->m_fcrNextFragment);

  for (const auto &entry : fclf->getFcrFreeChunks()) {
    if (!entry.expired()) {
      m_ds << getFcr64FromChunk(entry);
    }
  }

  return true;
}

bool RevisionStoreFile::writeFreeChunk(
    std::shared_ptr<RevisionStoreChunkContainer> chunk) {

  if (chunk->getType() != RevisionStoreChunkType::FreeChunk) {
    qWarning("Tried writing chunk with wrong method (FreeChunk)");
    return false;
  }

  auto fc = std::static_pointer_cast<FreeChunk>(chunk->getChunk());

  m_ds.device()->write(QByteArray(fc->cb(), '\0'));
  return true;
}

bool RevisionStoreFile::writeFileNodeListFragment(
    std::shared_ptr<RevisionStoreChunkContainer> chunk) {

  if (chunk->getType() != RevisionStoreChunkType::FileNodeListFragment) {
    qWarning("Tried writing chunk with wrong method (FileNodeListFragment)");
    return false;
  }

  auto fnlf = std::static_pointer_cast<FileNodeListFragment>(chunk->getChunk());

  m_ds << fnlf->header_magic_id;
  m_ds << fnlf->m_fileNodeListID;
  m_ds << fnlf->m_nFragmentSequence;

  for (auto &fn : fnlf->m_fileNodes) {
    writeFileNode(fn);
  }

  // not memory friendly. maybe looping is more straight forward here.¸
  m_ds.device()->write(QByteArray(fnlf->m_paddingLength,'\0'));
  m_ds << getFcr64x32FromChunk(fnlf->getNextFragment());
  m_ds << fnlf->footer_magic_id;

  return true;
}

std::shared_ptr<RevisionStoreChunkContainer>
RevisionStoreFile::deserializeFileNodeListFragment(QDataStream &ds,
                                                   const quint64 stp,
                                                   const quint64 cb) {
  if (static_cast<quint64>(ds.device()->size()) < stp) {
    qFatal("Tried to read past file size.");
  }
  ds.device()->seek(stp);

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

  auto fnlfc = std::make_shared<RevisionStoreChunkContainer>(
      std::make_shared<libmson::FileNodeListFragment>(), stp, cb);

  auto fnlf = std::static_pointer_cast<libmson::FileNodeListFragment>(
      fnlfc->getChunk());

  quint64 headerTest;
  ds >> headerTest;
  if (headerTest != libmson::FileNodeListFragment::header_magic_id) {
    qFatal("FileNodeListFragment header is invalid.");
    return fnlfc;
  }

  ds >> fnlf->m_fileNodeListID;
  ds >> fnlf->m_nFragmentSequence;

  if (m_fileNodeListFragments.find(fnlf->m_nFragmentSequence) !=
      m_fileNodeListFragments.end()) {
    qFatal("FileNodeListFragment already parsed (duplicate nFragmentSequence");
  } else {
    m_fileNodeListFragments.emplace(fnlf->m_nFragmentSequence, fnlfc);
  }

  quint32 fileNodeCount = UINT32_MAX;

  if (m_fileNodeCountMapping.contains(fnlf->m_fileNodeListID)) {
    fileNodeCount = m_fileNodeCountMapping[fnlf->m_fileNodeListID];
  }

  quint64 remainingBytes = 0;
  do {

    auto fnc = deserializeFileNode(ds, ds.device()->pos(), fnlfc);

    MSONcommon::FileNodeTypeID fileNodeID =
        std::static_pointer_cast<libmson::FileNode>(fnc->getChunk())
            ->getFileNodeTypeID();

    if (static_cast<quint16>(fileNodeID) != 0) {
      fnlf->m_fileNodes.push_back(fnc);
      if (fileNodeID != MSONcommon::FileNodeTypeID::ChunkTerminatorFND) {
        fileNodeCount--;
      } else {
        /// \todo When ChunkTerminator found, is there really no filenode
        /// left?
        //        qWarning() << "ChunkTerminatorFND found";
        break;
      }
    } else {
      //      qWarning() << "FileNodeListFragment ended early";
      break;
    }

    remainingBytes = stp + cb - ds.device()->pos();
  } while ((remainingBytes - 20 > 4) && (fileNodeCount > 0));

  if (m_fileNodeCountMapping.contains(fnlf->m_fileNodeListID)) {
    m_fileNodeCountMapping[fnlf->m_fileNodeListID] = fileNodeCount;
  }

  fnlf->m_paddingLength = stp + cb - ds.device()->pos() - 20;

  // Skip to end. Ignore ChunkTerminatorFND
  ds.device()->seek(stp + cb - 20);

  // footer
  MSONcommon::FileChunkReference64x32 nextFragment;
  ds >> nextFragment;
  if (!nextFragment.is_fcrNil() && !nextFragment.is_fcrZero()) {
    auto nextFnlf = std::make_shared<RevisionStoreChunkContainer>(
        std::make_shared<libmson::FileNodeListFragment>(), nextFragment.stp(),
        nextFragment.cb());

    insertChunkSorted(nextFnlf);

    fnlf->m_nextFragment = nextFnlf;
  }

  quint64 footerTest;
  ds >> footerTest;
  if (footerTest != libmson::FileNodeListFragment::footer_magic_id) {
    qFatal("FileNodeListFragment footer is invalid.");
    return fnlfc;
  }

  return fnlfc;
}

bool RevisionStoreFile::deserializeFileNodeListFragment(
    QDataStream &ds, std::shared_ptr<RevisionStoreChunkContainer> chunk) {

  quint64 stp = chunk->getInitialStp();
  quint64 cb = chunk->getInitialCb();

  if (static_cast<quint64>(ds.device()->size()) < stp) {
    qFatal("Tried to read past file size.");
  }
  ds.device()->seek(chunk->getInitialStp());

  if (cb < FileNodeListFragment::minSizeInFile) {
    qFatal("Tried to read fileNodeListFragment with invalid size.");
  }

  if (static_cast<quint64>(ds.device()->bytesAvailable()) <
     cb) {
    qFatal("Remaining file size insufficient to parse FileNodeListFragment.");
  }

  // if byte order is big endian, change to little endian
  if (m_ds.byteOrder() == QDataStream::BigEndian) {
    m_ds.setByteOrder(QDataStream::LittleEndian);
  }

  auto fnlf = std::static_pointer_cast<libmson::FileNodeListFragment>(
      chunk->getChunk());

  quint64 headerTest;
  ds >> headerTest;
  if (headerTest != libmson::FileNodeListFragment::header_magic_id) {
    qFatal("FileNodeListFragment header is invalid.");
  }

  ds >> fnlf->m_fileNodeListID;
  ds >> fnlf->m_nFragmentSequence;

  if (m_fileNodeListFragments.find(fnlf->m_nFragmentSequence) !=
      m_fileNodeListFragments.end()) {
    qFatal("FileNodeListFragment already parsed (duplicate nFragmentSequence");
  } else {
    m_fileNodeListFragments.emplace(fnlf->m_nFragmentSequence, chunk);
  }

  quint32 fileNodeCount = UINT32_MAX;

  if (m_fileNodeCountMapping.contains(fnlf->m_fileNodeListID)) {
    fileNodeCount = m_fileNodeCountMapping[fnlf->m_fileNodeListID];
  }

  quint64 remainingBytes = 0;
  do {

    auto fnc = deserializeFileNode(ds, ds.device()->pos(), chunk);

    MSONcommon::FileNodeTypeID fileNodeID =
        std::static_pointer_cast<libmson::FileNode>(fnc->getChunk())
            ->getFileNodeTypeID();

    if (static_cast<quint16>(fileNodeID) != 0) {
      fnlf->m_fileNodes.push_back(fnc);
      if (fileNodeID != MSONcommon::FileNodeTypeID::ChunkTerminatorFND) {
        fileNodeCount--;
      } else {
        /// \todo When ChunkTerminator found, is there really no filenode
        /// left?
        //        qWarning() << "ChunkTerminatorFND found";
        break;
      }
    } else {
      //      qWarning() << "FileNodeListFragment ended early";
      break;
    }

    remainingBytes = stp + cb - ds.device()->pos();
  } while ((remainingBytes - 16 > 4) && (fileNodeCount > 0));

  if (m_fileNodeCountMapping.contains(fnlf->m_fileNodeListID)) {
    m_fileNodeCountMapping[fnlf->m_fileNodeListID] = fileNodeCount;
  }

  fnlf->m_paddingLength = stp + cb - ds.device()->pos() - 16;

  // Skip to end. Ignore ChunkTerminatorFND
  ds.device()->seek(stp + cb - 20);

  // footer
  MSONcommon::FileChunkReference64x32 nextFragment;
  ds >> nextFragment;
  if (!nextFragment.is_fcrNil() && !nextFragment.is_fcrZero()) {
    auto nextFnlf = std::make_shared<RevisionStoreChunkContainer>(
        std::make_shared<libmson::FileNodeListFragment>(), nextFragment.stp(),
        nextFragment.cb());

    insertChunkSorted(nextFnlf);

    fnlf->m_nextFragment = nextFnlf;
  }

  quint64 footerTest;
  ds >> footerTest;
  if (footerTest != libmson::FileNodeListFragment::footer_magic_id) {
    qFatal("FileNodeListFragment footer is invalid.");
  }

  return true;
}

bool RevisionStoreFile::writeFileNode(
    std::shared_ptr<RevisionStoreChunkContainer> chunk) {

  auto fn = std::static_pointer_cast<FileNode>(chunk->getChunk());

  // updating self size
  fn->fileNodeSize = chunk->cb();

  quint32 composite;

  // reserved, must be 1, MS-ONESTORE section 2.4.3 FileNode
  composite = 1u << FileNode::shiftReserved;

  composite += (fn->baseType & libmson::FileNode::maskBaseType)<< FileNode::shiftBaseType;
  composite += (fn->cbFormat & libmson::FileNode::maskCbFormat)<< FileNode::shiftCbFormat;
  composite += (fn->stpFormat & libmson::FileNode::maskStpFormat)<< FileNode::shiftStpFormat;
  composite += (fn->fileNodeSize & libmson::FileNode::maskFileNodeSize)<< FileNode::shiftFileNodeSize;
  composite += (fn->fileNodeID & libmson::FileNode::maskFileNodeID)<< FileNode::shiftFileNodeID;

  m_ds << composite;

  m_ds << *fn->fnt;



  return true;
}

std::shared_ptr<RevisionStoreChunkContainer> RevisionStoreFile::deserializeFileNode(
    QDataStream &ds, const quint64 stp,
    std::weak_ptr<libmson::RevisionStoreChunkContainer> parent) {

  auto fnc = std::make_shared<RevisionStoreChunkContainer>(
      std::make_shared<libmson::FileNode>(parent), stp,
      FileNode::minSizeInFile);

  auto fn = std::static_pointer_cast<libmson::FileNode>(fnc->getChunk());

  if (ds.device()->bytesAvailable() < 4) {
    qFatal("Reached end of file stream while parsing FileNode");
  }
  quint32 temp;
  ds >> temp;

  fn->reserved = (temp >> libmson::FileNode::shiftReserved) &
                 libmson::FileNode::maskReserved;
  fn->baseType = (temp >> libmson::FileNode::shiftBaseType) &
                 libmson::FileNode::maskBaseType;
  fn->cbFormat = (temp >> libmson::FileNode::shiftCbFormat) &
                 libmson::FileNode::maskCbFormat;
  fn->stpFormat = (temp >> libmson::FileNode::shiftStpFormat) &
                  libmson::FileNode::maskStpFormat;
  fn->fileNodeSize = (temp >> libmson::FileNode::shiftFileNodeSize) &
                     libmson::FileNode::maskFileNodeSize;
  fn->fileNodeID = (temp >> libmson::FileNode::shiftFileNodeID) &
                   libmson::FileNode::maskFileNodeID;

  switch (fn->getFileNodeTypeID()) {
  case MSONcommon::FileNodeTypeID::ChunkTerminatorFND:
    fn->fnt = std::make_shared<MSONcommon::ChunkTerminatorFND>();
    break;
  case MSONcommon::FileNodeTypeID::DataSignatureGroupDefinitionFND:
    fn->fnt = std::make_shared<MSONcommon::DataSignatureGroupDefinitionFND>();
    break;
    //  case MSONcommon::FileNodeTypeID::FileDataStoreListReferenceFND:
    //    fn->fnt =
    //    std::make_shared<MSONcommon::FileDataStoreListReferenceFND>(fn->stpFormat,
    //    fn->cbFormat); break;
    //  case MSONcommon::FileNodeTypeID::FileDataStoreObjectReferenceFND:
    //    fn->fnt =
    //        std::make_shared<MSONcommon::FileDataStoreObjectReferenceFND>(fn->stpFormat,
    //        fn->cbFormat);
    //    break;
  case MSONcommon::FileNodeTypeID::GlobalIdTableEndFNDX:
    fn->fnt = std::make_shared<MSONcommon::GlobalIdTableEndFNDX>();
    break;
  case MSONcommon::FileNodeTypeID::GlobalIdTableEntry2FNDX:
    fn->fnt = std::make_shared<MSONcommon::GlobalIdTableEntry2FNDX>();
    break;
  case MSONcommon::FileNodeTypeID::GlobalIdTableEntry3FNDX:
    fn->fnt = std::make_shared<MSONcommon::GlobalIdTableEntry3FNDX>();
    break;
  case MSONcommon::FileNodeTypeID::GlobalIdTableEntryFNDX:
    fn->fnt = std::make_shared<MSONcommon::GlobalIdTableEntryFNDX>();
    break;
  case MSONcommon::FileNodeTypeID::GlobalIdTableStart2FND:
    fn->fnt = std::make_shared<MSONcommon::GlobalIdTableStart2FND>();
    break;
  case MSONcommon::FileNodeTypeID::GlobalIdTableStartFNDX:
    fn->fnt = std::make_shared<MSONcommon::GlobalIdTableStartFNDX>();
    break;
  case MSONcommon::FileNodeTypeID::HashedChunkDescriptor2FND:
    fn->fnt = std::make_shared<MSONcommon::HashedChunkDescriptor2FND>(
        fn->stpFormat, fn->cbFormat);
    break;
  case MSONcommon::FileNodeTypeID::ObjectDataEncryptionKeyV2FNDX:
    fn->fnt = std::make_shared<MSONcommon::ObjectDataEncryptionKeyV2FNDX>(
        fn->stpFormat, fn->cbFormat);
    break;
  case MSONcommon::FileNodeTypeID::ObjectDeclaration2LargeRefCountFND:
    fn->fnt = std::make_shared<MSONcommon::ObjectDeclaration2LargeRefCountFND>(
        fn->stpFormat, fn->cbFormat);
    break;
  case MSONcommon::FileNodeTypeID::ObjectDeclaration2RefCountFND:
    fn->fnt = std::make_shared<MSONcommon::ObjectDeclaration2RefCountFND>(
        fn->stpFormat, fn->cbFormat);
    break;
  case MSONcommon::FileNodeTypeID::ObjectDeclarationFileData3LargeRefCountFND:
    fn->fnt = std::make_shared<
        MSONcommon::ObjectDeclarationFileData3LargeRefCountFND>();
    break;
  case MSONcommon::FileNodeTypeID::ObjectDeclarationFileData3RefCountFND:
    fn->fnt =
        std::make_shared<MSONcommon::ObjectDeclarationFileData3RefCountFND>();
    break;
  case MSONcommon::FileNodeTypeID::ObjectDeclarationWithRefCount2FNDX:
    fn->fnt = std::make_shared<MSONcommon::ObjectDeclarationWithRefCount2FNDX>(
        fn->stpFormat, fn->cbFormat);
    break;
  case MSONcommon::FileNodeTypeID::ObjectDeclarationWithRefCountFNDX:
    fn->fnt = std::make_shared<MSONcommon::ObjectDeclarationWithRefCountFNDX>(
        fn->stpFormat, fn->cbFormat);
    break;
  case MSONcommon::FileNodeTypeID::ObjectGroupEndFND:
    fn->fnt = std::make_shared<MSONcommon::ObjectGroupEndFND>();
    break;
  case MSONcommon::FileNodeTypeID::ObjectGroupListReferenceFND:
    fn->fnt = std::make_shared<MSONcommon::ObjectGroupListReferenceFND>(
        fn->stpFormat, fn->cbFormat);
    break;
  case MSONcommon::FileNodeTypeID::ObjectGroupStartFND:
    fn->fnt = std::make_shared<MSONcommon::ObjectGroupStartFND>();
    break;
  case MSONcommon::FileNodeTypeID::ObjectInfoDependencyOverridesFND:
    fn->fnt = std::make_shared<MSONcommon::ObjectInfoDependencyOverridesFND>(
        fn->stpFormat, fn->cbFormat);
    break;
  case MSONcommon::FileNodeTypeID::ObjectRevisionWithRefCount2FNDX:
    fn->fnt = std::make_shared<MSONcommon::ObjectRevisionWithRefCount2FNDX>(
        fn->stpFormat, fn->cbFormat);
    break;
  case MSONcommon::FileNodeTypeID::ObjectRevisionWithRefCountFNDX:
    fn->fnt = std::make_shared<MSONcommon::ObjectRevisionWithRefCountFNDX>(
        fn->stpFormat, fn->cbFormat);
    break;
  case MSONcommon::FileNodeTypeID::ObjectSpaceManifestListReferenceFND:
    fn->fnt = std::make_shared<MSONcommon::ObjectSpaceManifestListReferenceFND>(
        fn->stpFormat, fn->cbFormat);
    break;
  case MSONcommon::FileNodeTypeID::ObjectSpaceManifestListStartFND:
    fn->fnt = std::make_shared<MSONcommon::ObjectSpaceManifestListStartFND>();
    break;
  case MSONcommon::FileNodeTypeID::ObjectSpaceManifestRootFND:
    fn->fnt = std::make_shared<MSONcommon::ObjectSpaceManifestRootFND>();
    break;
  case MSONcommon::FileNodeTypeID::ReadOnlyObjectDeclaration2LargeRefCountFND:
    fn->fnt = std::make_shared<
        MSONcommon::ReadOnlyObjectDeclaration2LargeRefCountFND>(fn->stpFormat,
                                                                fn->cbFormat);
    break;
  case MSONcommon::FileNodeTypeID::ReadOnlyObjectDeclaration2RefCountFND:
    fn->fnt =
        std::make_shared<MSONcommon::ReadOnlyObjectDeclaration2RefCountFND>(
            fn->stpFormat, fn->cbFormat);
    break;
  case MSONcommon::FileNodeTypeID::RevisionManifestEndFND:
    fn->fnt = std::make_shared<MSONcommon::RevisionManifestEndFND>();
    break;
  case MSONcommon::FileNodeTypeID::RevisionManifestListReferenceFND:
    fn->fnt = std::make_shared<MSONcommon::RevisionManifestListReferenceFND>(
        fn->stpFormat, fn->cbFormat);
    break;
  case MSONcommon::FileNodeTypeID::RevisionManifestListStartFND:
    fn->fnt = std::make_shared<MSONcommon::RevisionManifestListStartFND>();
    break;
  case MSONcommon::FileNodeTypeID::RevisionManifestStart4FND:
    fn->fnt = std::make_shared<MSONcommon::RevisionManifestStart4FND>();
    break;
  case MSONcommon::FileNodeTypeID::RevisionManifestStart6FND:
    fn->fnt = std::make_shared<MSONcommon::RevisionManifestStart6FND>();
    break;
  case MSONcommon::FileNodeTypeID::RevisionManifestStart7FND:
    fn->fnt = std::make_shared<MSONcommon::RevisionManifestStart7FND>();
    break;
  case MSONcommon::FileNodeTypeID::RevisionRoleAndContextDeclarationFND:
    fn->fnt =
        std::make_shared<MSONcommon::RevisionRoleAndContextDeclarationFND>();
    break;
  case MSONcommon::FileNodeTypeID::RevisionRoleDeclarationFND:
    fn->fnt = std::make_shared<MSONcommon::RevisionRoleDeclarationFND>();
    break;
  case MSONcommon::FileNodeTypeID::RootObjectReference2FNDX:
    fn->fnt = std::make_shared<MSONcommon::RootObjectReference2FNDX>();
    break;
  case MSONcommon::FileNodeTypeID::RootObjectReference3FND:
    fn->fnt = std::make_shared<MSONcommon::RootObjectReference3FND>();
    break;

  default:
    fn->fnt = nullptr;
    break;
  }

  if (fn->fnt != nullptr) {
    ds >> *fn->fnt;
  }

  return fnc;
}

quint64
RevisionStoreFile::stpFromChunk(std::weak_ptr<RevisionStoreChunkContainer> chunk) {
  if (chunk.expired()) {
    return UINT64_MAX;
  } else {
    auto lchunk = chunk.lock();

    // if chunk is a FileNode, we must first sum up to the parent
    // FileNodeListFragment
    if (lchunk->getType() == RevisionStoreChunkType::FileNode) {
      quint64 stp = 0;
      auto fileNodeListFragmentChunk = std::static_pointer_cast<libmson::FileNode>( lchunk->getContent() )->getParent();

      quint64 subtotal = stpTillIterator(m_chunks, fileNodeListFragmentChunk);

      // now summing up within the FileNodeListFragment
      stp += FileNodeListFragment::headerSize;

      subtotal += stpTillIterator(
          std::static_pointer_cast<libmson::FileNodeListFragment>(
              fileNodeListFragmentChunk.lock()->getContent())
              ->getFileNodes(),
          lchunk);

      if (subtotal != UINT64_MAX) {
        return stp + subtotal;
      } else {
        return UINT64_MAX;
      }

    } else {
      return stpTillIterator(m_chunks, chunk);
    }
  }
}

quint64 RevisionStoreFile::stpTillIterator(
    const std::list<std::shared_ptr<RevisionStoreChunkContainer>> &list,
    const std::weak_ptr<RevisionStoreChunkContainer> &chunk) {
  if (chunk.expired()) {
    return UINT64_MAX;
  } else {
    auto lchunk = chunk.lock();

    auto it = std::find(list.begin(), list.end(), lchunk);

    auto addCb = [](quint64 a, std::shared_ptr<RevisionStoreChunkContainer> b) {
      return std::move(a) + b->cb();
    };

    return std::accumulate(list.begin(), it, 0, addCb);
  }
}

MSONcommon::FileChunkReference64x32 RevisionStoreFile::getFcr64x32FromChunk(
    std::weak_ptr<RevisionStoreChunkContainer> chunk) {
  if (chunk.expired()) {
    return MSONcommon::FileChunkReference64x32(
        MSONcommon::FCR_INITTYPE::FCRNIL);
  } else {
    auto lchunk = chunk.lock();
    quint64 stp = stpFromChunk(lchunk);
    return MSONcommon::FileChunkReference64x32(stp, lchunk->cb());
  }
}

MSONcommon::FileChunkReference64
RevisionStoreFile::getFcr64FromChunk(std::weak_ptr<RevisionStoreChunkContainer> chunk) {
  if (chunk.expired()) {
    return MSONcommon::FileChunkReference64(MSONcommon::FCR_INITTYPE::FCRNIL);
  } else {
    auto lchunk = chunk.lock();
    quint64 stp = stpFromChunk(lchunk);
    return MSONcommon::FileChunkReference64(stp, lchunk->cb());
  }
}

void RevisionStoreFile::insertChunkSorted(
    std::shared_ptr<RevisionStoreChunkContainer> chunk) {
  if (chunk->getType() == RevisionStoreChunkType::RevistionStoreFileHeader) {
    qWarning("Did not add second RevistionStoreFileHeader to chunk list.");
    return;
  }

  if (m_chunks.size() < 2) {
    m_chunks.push_back(chunk);
    return;
  }

  const quint64 chunkInitialStp = chunk->getInitialStp();

  for (auto it = m_chunks.rbegin(); it != m_chunks.rend(); ++it) {
    if (it->get()->getInitialStp() < chunkInitialStp) {
      --it;
      m_chunks.insert(it.base(), chunk);
      return;
    }
  }
}

} // namespace libmson
