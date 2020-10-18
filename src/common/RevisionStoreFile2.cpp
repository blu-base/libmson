#include "RevisionStoreFile2.h"

#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QUuid>

#include "chunks/Chunkable.h"
#include "chunks/FreeChunk.h"
#include "chunks/FreeChunkListFragment.h"
#include "chunks/RevisionStoreFileHeader.h"

#include "helper/CrcAlgorithms.h"

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

  auto headerChunk = std::make_shared<RevisionStoreChunk>(
      std::make_shared<RevisionStoreFileHeader>(), 0u);

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
  }

  MSONcommon::FileChunkReference64x32 fcrFreeChunkList;
  m_ds >> fcrFreeChunkList;
  if (!fcrFreeChunkList.is_fcrNil() && !fcrFreeChunkList.is_fcrZero()) {

    auto freeChunkListFragment = std::make_shared<RevisionStoreChunk>(
        std::make_shared<FreeChunkListFragment>(fcrFreeChunkList.cb()),
        fcrFreeChunkList.stp());

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
      m_chunks.begin()->get()->getChunk());

  quint64 totalFileSize = 0;

  auto addCb = [](quint64 a, std::shared_ptr<RevisionStoreChunk> b) {
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

bool RevisionStoreFile::writeChunk(std::shared_ptr<RevisionStoreChunk> chunk) {
  switch (chunk->getType()) {

  case RevisionStoreChunkType::RevistionStoreFileHeader:
    qWarning("Trying to write another header mid-stream");
    break;
  case RevisionStoreChunkType::FileNodeListFragmentHeader:
    break;
  case RevisionStoreChunkType::FileNode:
    break;
  case RevisionStoreChunkType::FileNodeListFragmentFooter:
    break;
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
    std::shared_ptr<RevisionStoreChunk> chunk) {

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
    std::shared_ptr<RevisionStoreChunk> chunk) {

  if (chunk->getType() != RevisionStoreChunkType::FreeChunk) {
    qWarning("Tried writing chunk with wrong method (FreeChunk)");
    return false;
  }

  auto fc =
      std::static_pointer_cast<FreeChunk>(chunk->getChunk());

  m_ds.device()->write(QByteArray(fc->cb(),'\0'));
  return true;
}




quint64
RevisionStoreFile::stpFromChunk(std::weak_ptr<RevisionStoreChunk> chunk) {
  if (chunk.expired()) {
    return UINT64_MAX;
  } else {
    auto lchunk = chunk.lock();

    auto it = std::find(m_chunks.begin(), m_chunks.end(), lchunk);

    auto addCb = [](quint64 a, std::shared_ptr<RevisionStoreChunk> b) {
      return std::move(a) + b->cb();
    };

    return std::accumulate(m_chunks.begin(), it, 0, addCb);
  }
}

MSONcommon::FileChunkReference64x32 RevisionStoreFile::getFcr64x32FromChunk(
    std::weak_ptr<RevisionStoreChunk> chunk) {
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
RevisionStoreFile::getFcr64FromChunk(std::weak_ptr<RevisionStoreChunk> chunk) {
  if (chunk.expired()) {
    return MSONcommon::FileChunkReference64(MSONcommon::FCR_INITTYPE::FCRNIL);
  } else {
    auto lchunk = chunk.lock();
    quint64 stp = stpFromChunk(lchunk);
    return MSONcommon::FileChunkReference64(stp, lchunk->cb());
  }
}

void RevisionStoreFile::insertChunkSorted(
    std::shared_ptr<RevisionStoreChunk> chunk) {
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
