#include "RevisionStoreFileHeader.h"

namespace libmson {
namespace priv {

const QUuid RevisionStoreFileHeader::guidFileType_One(
    "{7b5c52e4-d88c-4da7-aeb1-5378d02996d3}");
const QUuid RevisionStoreFileHeader::guidFileType_OneToc2(
    "{43ff2fa1-efd9-4c76-9ee2-10ea5722765f}");

const QUuid RevisionStoreFileHeader::guidFileFormat(
    "{109ADD3F-911B-49F5-A5D0-1791EDC8AED8}");

const QUuid RevisionStoreFileHeader::guidLegacyFileVersion(
    "{00000000-0000-0000-0000-000000000000}");


RevisionStoreFileHeader::RevisionStoreFileHeader(
    const quint64 initialStp, const quint64 initialCb)
    : Chunkable(initialStp, initialCb), m_guidFileType(guidFileType_One),
      m_guidFile(QUuid::createUuid()), m_ffvLastWriterVersion{0x0000002A},
      m_ffvOldestWriterVersion{0x0000002A},
      m_ffvNewestWriterVersion{0x0000002A}, m_ffvOldestReader{0x0000002A},
      m_cTransactionsInLog{1}, m_rgbPlaceholder{0}, m_fNeedsDefrag{0},
      m_fRepairedFile{0}, m_fNeedsGarbageCollect{0},
      m_fHasNoEmbeddedFileObjects{0}, m_guidAncestor{QUuid()}, m_crcName{0},
      m_fcrHashedChunkList{FileNodeListFragment_WPtr_t()},
      m_fcrTransactionLog{TransactionLogFragment_WPtr_t()},
      m_fcrFileNodeListRoot{FileNodeListFragment_WPtr_t()},
      m_fcrFreeChunkList{FreeChunkListFragment_WPtr_t()},
      m_cbExpectedFileLength{0x400}, m_cbFreeSpaceInFreeChunkList{0},
      m_guidFileVersion{QUuid()}, m_nFileVersionGeneration{},
      m_guidDenyReadFileVersion{QUuid()}, m_grfDebugLogFlags{0}, m_bnCreated{0},
      m_bnLastWroteToThisFile{0}, m_bnOldestWritten{0}, m_bnNewestWritten{0}
{
}

RevisionStoreFileHeader::RevisionStoreFileHeader(
    const QUuid& guidFileType, const QUuid& guidFile,
    const quint32 ffvLastWriterVersion, const quint32 ffvOldestWriterVersion,
    const quint32 ffvNewestWriterVersion, const quint32 ffvOldestReader,
    const quint32 cTransactionsInLog, const quint64 rgbPlaceholder,
    const quint8 fNeedsDefrag, const quint8 fRepairedFile,
    const quint8 fNeedsGarbageCollect, const quint8 fHasNoEmbeddedFileObjects,
    const QUuid& guidAncestor, const quint32 crcName,
    FileNodeListFragment_WPtr_t fcrHashedChunkList,
    TransactionLogFragment_WPtr_t fcrTransactionLog,
    FileNodeListFragment_WPtr_t fcrFileNodeListRoot,
    FreeChunkListFragment_WPtr_t fcrFreeChunkList,
    const quint64 cbExpectedFileLength,
    const quint64 cbFreeSpaceInFreeChunkList, const QUuid& guidFileVersion,
    const quint64 nFileVersionGeneration, const QUuid& guidDenyReadFileVersion,
    const quint32 grfDebugLogFlags, const quint32 bnCreated,
    const quint32 bnLastWroteToThisFile, const quint32 bnOldestWritten,
    const quint32 bnNewestWritten)
    : m_guidFileType(guidFileType), m_guidFile(guidFile),
      m_ffvLastWriterVersion(ffvLastWriterVersion),
      m_ffvOldestWriterVersion(ffvOldestWriterVersion),
      m_ffvNewestWriterVersion(ffvNewestWriterVersion),
      m_ffvOldestReader(ffvOldestReader),
      m_cTransactionsInLog(cTransactionsInLog),
      m_rgbPlaceholder(rgbPlaceholder), m_fNeedsDefrag(fNeedsDefrag),
      m_fRepairedFile(fRepairedFile),
      m_fNeedsGarbageCollect(fNeedsGarbageCollect),
      m_fHasNoEmbeddedFileObjects(fHasNoEmbeddedFileObjects),
      m_guidAncestor(guidAncestor), m_crcName(crcName),
      m_fcrHashedChunkList(fcrHashedChunkList),
      m_fcrTransactionLog(fcrTransactionLog),
      m_fcrFileNodeListRoot(fcrFileNodeListRoot),
      m_fcrFreeChunkList(fcrFreeChunkList),
      m_cbExpectedFileLength(cbExpectedFileLength),
      m_cbFreeSpaceInFreeChunkList(cbFreeSpaceInFreeChunkList),
      m_guidFileVersion(guidFileVersion),
      m_nFileVersionGeneration(nFileVersionGeneration),
      m_guidDenyReadFileVersion(guidDenyReadFileVersion),
      m_grfDebugLogFlags(grfDebugLogFlags), m_bnCreated(bnCreated),
      m_bnLastWroteToThisFile(bnLastWroteToThisFile),
      m_bnOldestWritten(bnOldestWritten), m_bnNewestWritten(bnNewestWritten)
{
}

RevisionStoreFileHeader::RevisionStoreFileHeader(
    const QUuid& guidFileType, const QUuid& guidFile,
    const quint32 ffvLastWriterVersion, const quint32 ffvOldestWriterVersion,
    const quint32 ffvNewestWriterVersion, const quint32 ffvOldestReader,
    const quint32 cTransactionsInLog, const quint64 rgbPlaceholder,
    const quint8 fNeedsDefrag, const quint8 fRepairedFile,
    const quint8 fNeedsGarbageCollect, const quint8 fHasNoEmbeddedFileObjects,
    const QUuid& guidAncestor, const quint32 crcName,
    const quint64 cbExpectedFileLength,
    const quint64 cbFreeSpaceInFreeChunkList, const QUuid& guidFileVersion,
    const quint64 nFileVersionGeneration, const QUuid& guidDenyReadFileVersion,
    const quint32 grfDebugLogFlags, const quint32 bnCreated,
    const quint32 bnLastWroteToThisFile, const quint32 bnOldestWritten,
    const quint32 bnNewestWritten)
    : m_guidFileType(guidFileType), m_guidFile(guidFile),
      m_ffvLastWriterVersion(ffvLastWriterVersion),
      m_ffvOldestWriterVersion(ffvOldestWriterVersion),
      m_ffvNewestWriterVersion(ffvNewestWriterVersion),
      m_ffvOldestReader(ffvOldestReader),
      m_cTransactionsInLog(cTransactionsInLog),
      m_rgbPlaceholder(rgbPlaceholder), m_fNeedsDefrag(fNeedsDefrag),
      m_fRepairedFile(fRepairedFile),
      m_fNeedsGarbageCollect(fNeedsGarbageCollect),
      m_fHasNoEmbeddedFileObjects(fHasNoEmbeddedFileObjects),
      m_guidAncestor(guidAncestor), m_crcName(crcName),
      m_fcrHashedChunkList(FileNodeListFragment_WPtr_t()),
      m_fcrTransactionLog(TransactionLogFragment_WPtr_t()),
      m_fcrFileNodeListRoot(FileNodeListFragment_WPtr_t()),
      m_fcrFreeChunkList(FreeChunkListFragment_WPtr_t()),
      m_cbExpectedFileLength(cbExpectedFileLength),
      m_cbFreeSpaceInFreeChunkList(cbFreeSpaceInFreeChunkList),
      m_guidFileVersion(guidFileVersion),
      m_nFileVersionGeneration(nFileVersionGeneration),
      m_guidDenyReadFileVersion(guidDenyReadFileVersion),
      m_grfDebugLogFlags(grfDebugLogFlags), m_bnCreated(bnCreated),
      m_bnLastWroteToThisFile(bnLastWroteToThisFile),
      m_bnOldestWritten(bnOldestWritten), m_bnNewestWritten(bnNewestWritten)
{
}

QUuid RevisionStoreFileHeader::getGuidFileType() const
{
  return m_guidFileType;
}

void RevisionStoreFileHeader::setGuidFileType(const QUuid& value)
{
  m_isChanged    = true;
  m_guidFileType = value;
}

QUuid RevisionStoreFileHeader::getGuidFile() const { return m_guidFile; }

void RevisionStoreFileHeader::setGuidFile(const QUuid& value)
{
  m_isChanged = true;
  m_guidFile  = value;
}

quint32 RevisionStoreFileHeader::getFfvLastWriterVersion() const
{
  return m_ffvLastWriterVersion;
}

void RevisionStoreFileHeader::setFfvLastWriterVersion(quint32 value)
{
  m_isChanged            = true;
  m_ffvLastWriterVersion = value;
}

quint32 RevisionStoreFileHeader::getFfvNewestWriterVersion() const
{
  return m_ffvNewestWriterVersion;
}

void RevisionStoreFileHeader::setFfvNewestWriterVersion(quint32 value)
{
  m_isChanged              = true;
  m_ffvNewestWriterVersion = value;
}

quint32 RevisionStoreFileHeader::getFfvOldestWriterVersion() const
{
  return m_ffvOldestWriterVersion;
}

void RevisionStoreFileHeader::setFfvOldestWriterVersion(quint32 value)
{
  m_isChanged              = true;
  m_ffvOldestWriterVersion = value;
}

quint32 RevisionStoreFileHeader::getFfvOldestReader() const
{
  return m_ffvOldestReader;
}

void RevisionStoreFileHeader::setFfvOldestReader(quint32 value)
{
  m_isChanged       = true;
  m_ffvOldestReader = value;
}

quint32 RevisionStoreFileHeader::getCTransactionsInLog() const
{
  return m_cTransactionsInLog;
}

/**
 * @brief RevisionStoreFileHeader::setCTransactionsInLog
 * @param value
 *
 * \todo setting this value forces a new UUID for guidFileVersion as well
 */
void RevisionStoreFileHeader::setCTransactionsInLog(const quint32 value)
{
  m_isChanged          = true;
  m_cTransactionsInLog = value;
}

quint64 RevisionStoreFileHeader::getRgbPlaceholder() const
{
  return m_rgbPlaceholder;
}

void RevisionStoreFileHeader::setRgbPlaceholder(const quint64 value)
{
  m_isChanged      = true;
  m_rgbPlaceholder = value;
}

quint8 RevisionStoreFileHeader::getFNeedsDefrag() const
{
  return m_fNeedsDefrag;
}

void RevisionStoreFileHeader::setFNeedsDefrag(const quint8 value)
{
  m_isChanged    = true;
  m_fNeedsDefrag = value;
}

quint8 RevisionStoreFileHeader::getFRepairedFile() const
{
  return m_fRepairedFile;
}

void RevisionStoreFileHeader::setFRepairedFile(const quint8 value)
{
  m_isChanged     = true;
  m_fRepairedFile = value;
}

quint8 RevisionStoreFileHeader::getFNeedsGarbageCollect() const
{
  return m_fNeedsGarbageCollect;
}

void RevisionStoreFileHeader::setFNeedsGarbageCollect(const quint8 value)
{
  m_isChanged            = true;
  m_fNeedsGarbageCollect = value;
}

quint8 RevisionStoreFileHeader::getFHasNoEmbeddedFileObjects() const
{
  return m_fHasNoEmbeddedFileObjects;
}

void RevisionStoreFileHeader::setFHasNoEmbeddedFileObjects(const quint8 value)
{
  m_isChanged                 = true;
  m_fHasNoEmbeddedFileObjects = value;
}

QUuid RevisionStoreFileHeader::getGuidAncestor() const
{
  return m_guidAncestor;
}

void RevisionStoreFileHeader::setGuidAncestor(const QUuid& value)
{
  m_isChanged    = true;
  m_guidAncestor = value;
}

quint32 RevisionStoreFileHeader::getCrcName() const { return m_crcName; }

void RevisionStoreFileHeader::setCrcName(const quint32 value)
{
  m_isChanged = true;
  m_crcName   = value;
}

FileNodeListFragment_WPtr_t RevisionStoreFileHeader::getFcrHashedChunkList()
{
  return m_fcrHashedChunkList;
}

void RevisionStoreFileHeader::setFcrHashedChunkList(
    FileNodeListFragment_WPtr_t value)
{
  m_isChanged          = true;
  m_fcrHashedChunkList = value;
}

TransactionLogFragment_WPtr_t RevisionStoreFileHeader::getFcrTransactionLog()
{
  return m_fcrTransactionLog;
}

void RevisionStoreFileHeader::setFcrTransactionLog(
    TransactionLogFragment_WPtr_t value)
{
  m_isChanged         = true;
  m_fcrTransactionLog = value;
}

FileNodeListFragment_WPtr_t RevisionStoreFileHeader::getFcrFileNodeListRoot()
{
  return m_fcrFileNodeListRoot;
}

void RevisionStoreFileHeader::setFcrFileNodeListRoot(
    FileNodeListFragment_WPtr_t value)
{
  m_isChanged           = true;
  m_fcrFileNodeListRoot = value;
}

FreeChunkListFragment_WPtr_t RevisionStoreFileHeader::getFcrFreeChunkList()
{
  return m_fcrFreeChunkList;
}

void RevisionStoreFileHeader::setFcrFreeChunkList(
    FreeChunkListFragment_WPtr_t value)
{
  m_isChanged        = true;
  m_fcrFreeChunkList = value;
}

quint64 RevisionStoreFileHeader::getCbExpectedFileLength() const
{
  return m_cbExpectedFileLength;
}

void RevisionStoreFileHeader::setCbExpectedFileLength(const quint64 value)
{
  m_isChanged            = true;
  m_cbExpectedFileLength = value;
}

quint64 RevisionStoreFileHeader::getCbFreeSpaceInFreeChunkList() const
{
  return m_cbFreeSpaceInFreeChunkList;
}

void RevisionStoreFileHeader::setCbFreeSpaceInFreeChunkList(const quint64 value)
{
  m_isChanged                  = true;
  m_cbFreeSpaceInFreeChunkList = value;
}

QUuid RevisionStoreFileHeader::getGuidFileVersion() const
{
  return m_guidFileVersion;
}

void RevisionStoreFileHeader::setGuidFileVersion(const QUuid& value)
{
  m_isChanged       = true;
  m_guidFileVersion = value;
}

quint64 RevisionStoreFileHeader::getNFileVersionGeneration() const
{
  return m_nFileVersionGeneration;
}

/**
 * @brief RevisionStoreFileHeader::setNFileVersionGeneration
 * @param value
 *
 * must be incremented with change of setGuidFileVersion
 */
void RevisionStoreFileHeader::setNFileVersionGeneration(const quint64 value)
{
  m_isChanged              = true;
  m_nFileVersionGeneration = value;
}

QUuid RevisionStoreFileHeader::getGuidDenyReadFileVersion() const
{
  return m_guidDenyReadFileVersion;
}

/**
 * @brief RevisionStoreFileHeader::setGuidDenyReadFileVersion
 * @param value
 *
 * \todo setting guidDenyReadFileVersion also requires a new file version
 */
void RevisionStoreFileHeader::setGuidDenyReadFileVersion(const QUuid& value)
{
  m_isChanged               = true;
  m_guidDenyReadFileVersion = value;
}

quint32 RevisionStoreFileHeader::getGrfDebugLogFlags() const
{
  return m_grfDebugLogFlags;
}

void RevisionStoreFileHeader::setGrfDebugLogFlags(const quint32 value)
{
  m_isChanged        = true;
  m_grfDebugLogFlags = value;
}

quint32 RevisionStoreFileHeader::getBnCreated() const { return m_bnCreated; }

void RevisionStoreFileHeader::setBnCreated(const quint32 value)
{
  m_isChanged = true;
  m_bnCreated = value;
}

quint32 RevisionStoreFileHeader::getBnLastWroteToThisFile() const
{
  return m_bnLastWroteToThisFile;
}

void RevisionStoreFileHeader::setBnLastWroteToThisFile(const quint32 value)
{
  m_isChanged             = true;
  m_bnLastWroteToThisFile = value;
}

quint32 RevisionStoreFileHeader::getBnOldestWritten() const
{
  return m_bnOldestWritten;
}

void RevisionStoreFileHeader::setBnOldestWritten(const quint32 value)
{
  m_isChanged       = true;
  m_bnOldestWritten = value;
}

quint32 RevisionStoreFileHeader::getBnNewestWritten() const
{
  return m_bnNewestWritten;
}

void RevisionStoreFileHeader::setBnNewestWritten(const quint32 value)
{
  m_isChanged       = true;
  m_bnNewestWritten = value;
}

} // namespace priv
} // namespace libmson
