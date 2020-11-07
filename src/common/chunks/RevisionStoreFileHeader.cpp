#include "RevisionStoreFileHeader.h"

namespace libmson {

const QUuid RevisionStoreFileHeader::v_guidFileType_One(
    "{7b5c52e4-d88c-4da7-aeb1-5378d02996d3}");
const QUuid RevisionStoreFileHeader::v_guidFileType_OneToc2(
    "{43ff2fa1-efd9-4c76-9ee2-10ea5722765f}");

const QUuid RevisionStoreFileHeader::v_guidFileFormat (
    "{109ADD3F-911B-49F5-A5D0-1791EDC8AED8}");

const QUuid RevisionStoreFileHeader::v_guidLegacyFileVersion (
    "{00000000-0000-0000-0000-000000000000}");



RevisionStoreFileHeader::RevisionStoreFileHeader()
    : guidFileType(v_guidFileType_One),
      guidFile(QUuid::createUuid()), ffvLastWriterVersion{0x0000002A},
      ffvOldestWriterVersion{0x0000002A}, ffvNewestWriterVersion{0x0000002A},
      ffvOldestReader{0x0000002A}, cTransactionsInLog{1}, rgbPlaceholder{0},
      fNeedsDefrag{0}, fRepairedFile{0}, fNeedsGarbageCollect{0},
      fHasNoEmbeddedFileObjects{0}, guidAncestor{QUuid()}, crcName{0},
      fcrHashedChunkList{std::weak_ptr<RevisionStoreChunkContainer>()},
      fcrTransactionLog{std::weak_ptr<RevisionStoreChunkContainer>()},
      fcrFileNodeListRoot{std::weak_ptr<RevisionStoreChunkContainer>()},
      fcrFreeChunkList{std::weak_ptr<RevisionStoreChunkContainer>()},
      cbExpectedFileLength{0x400}, cbFreeSpaceInFreeChunkList{0},
      guidFileVersion{QUuid()}, nFileVersionGeneration{},
      guidDenyReadFileVersion{QUuid()}, grfDebugLogFlags{0}, bnCreated{0},
      bnLastWroteToThisFile{0}, bnOldestWritten{0}, bnNewestWritten{0} {}

RevisionStoreFileHeader::RevisionStoreFileHeader(
    const QUuid &guidFileType, const QUuid &guidFile,
    const quint32 ffvLastWriterVersion, const quint32 ffvOldestWriterVersion,
    const quint32 ffvNewestWriterVersion, const quint32 ffvOldestReader,
    const quint32 cTransactionsInLog, const quint64 rgbPlaceholder,
    const quint8 fNeedsDefrag, const quint8 fRepairedFile,
    const quint8 fNeedsGarbageCollect, const quint8 fHasNoEmbeddedFileObjects,
    const QUuid &guidAncestor, const quint32 crcName,
    std::weak_ptr<RevisionStoreChunkContainer> fcrHashedChunkList,
    std::weak_ptr<RevisionStoreChunkContainer> fcrTransactionLog,
    std::weak_ptr<RevisionStoreChunkContainer> fcrFileNodeListRoot,
    std::weak_ptr<RevisionStoreChunkContainer> fcrFreeChunkList,
    const quint64 cbExpectedFileLength,
    const quint64 cbFreeSpaceInFreeChunkList, const QUuid &guidFileVersion,
    const quint64 nFileVersionGeneration, const QUuid &guidDenyReadFileVersion,
    const quint32 grfDebugLogFlags, const quint32 bnCreated,
    const quint32 bnLastWroteToThisFile, const quint32 bnOldestWritten,
    const quint32 bnNewestWritten)
    : guidFileType(guidFileType), guidFile(guidFile),
      ffvLastWriterVersion(ffvLastWriterVersion),
      ffvOldestWriterVersion(ffvOldestWriterVersion),
      ffvNewestWriterVersion(ffvNewestWriterVersion),
      ffvOldestReader(ffvOldestReader), cTransactionsInLog(cTransactionsInLog),
      rgbPlaceholder(rgbPlaceholder), fNeedsDefrag(fNeedsDefrag),
      fRepairedFile(fRepairedFile), fNeedsGarbageCollect(fNeedsGarbageCollect),
      fHasNoEmbeddedFileObjects(fHasNoEmbeddedFileObjects),
      guidAncestor(guidAncestor), crcName(crcName),
      fcrHashedChunkList(fcrHashedChunkList),
      fcrTransactionLog(fcrTransactionLog),
      fcrFileNodeListRoot(fcrFileNodeListRoot),
      fcrFreeChunkList(fcrFreeChunkList),
      cbExpectedFileLength(cbExpectedFileLength),
      cbFreeSpaceInFreeChunkList(cbFreeSpaceInFreeChunkList),
      guidFileVersion(guidFileVersion),
      nFileVersionGeneration(nFileVersionGeneration),
      guidDenyReadFileVersion(guidDenyReadFileVersion),
      grfDebugLogFlags(grfDebugLogFlags), bnCreated(bnCreated),
      bnLastWroteToThisFile(bnLastWroteToThisFile),
      bnOldestWritten(bnOldestWritten), bnNewestWritten(bnNewestWritten) {}

RevisionStoreFileHeader::RevisionStoreFileHeader(
    const QUuid &guidFileType, const QUuid &guidFile,
    const quint32 ffvLastWriterVersion, const quint32 ffvOldestWriterVersion,
    const quint32 ffvNewestWriterVersion, const quint32 ffvOldestReader,
    const quint32 cTransactionsInLog, const quint64 rgbPlaceholder,
    const quint8 fNeedsDefrag, const quint8 fRepairedFile,
    const quint8 fNeedsGarbageCollect, const quint8 fHasNoEmbeddedFileObjects,
    const QUuid &guidAncestor, const quint32 crcName,
    const quint64 cbExpectedFileLength,
    const quint64 cbFreeSpaceInFreeChunkList, const QUuid &guidFileVersion,
    const quint64 nFileVersionGeneration, const QUuid &guidDenyReadFileVersion,
    const quint32 grfDebugLogFlags, const quint32 bnCreated,
    const quint32 bnLastWroteToThisFile, const quint32 bnOldestWritten,
    const quint32 bnNewestWritten)
    : guidFileType(guidFileType), guidFile(guidFile),
      ffvLastWriterVersion(ffvLastWriterVersion),
      ffvOldestWriterVersion(ffvOldestWriterVersion),
      ffvNewestWriterVersion(ffvNewestWriterVersion),
      ffvOldestReader(ffvOldestReader), cTransactionsInLog(cTransactionsInLog),
      rgbPlaceholder(rgbPlaceholder), fNeedsDefrag(fNeedsDefrag),
      fRepairedFile(fRepairedFile), fNeedsGarbageCollect(fNeedsGarbageCollect),
      fHasNoEmbeddedFileObjects(fHasNoEmbeddedFileObjects),
      guidAncestor(guidAncestor), crcName(crcName),
      fcrHashedChunkList(std::weak_ptr<RevisionStoreChunkContainer>()),
      fcrTransactionLog(std::weak_ptr<RevisionStoreChunkContainer>()),
      fcrFileNodeListRoot(std::weak_ptr<RevisionStoreChunkContainer>()),
      fcrFreeChunkList(std::weak_ptr<RevisionStoreChunkContainer>()),
      cbExpectedFileLength(cbExpectedFileLength),
      cbFreeSpaceInFreeChunkList(cbFreeSpaceInFreeChunkList),
      guidFileVersion(guidFileVersion),
      nFileVersionGeneration(nFileVersionGeneration),
      guidDenyReadFileVersion(guidDenyReadFileVersion),
      grfDebugLogFlags(grfDebugLogFlags), bnCreated(bnCreated),
      bnLastWroteToThisFile(bnLastWroteToThisFile),
      bnOldestWritten(bnOldestWritten), bnNewestWritten(bnNewestWritten) {}

QUuid RevisionStoreFileHeader::getGuidFileType() const { return guidFileType; }

void RevisionStoreFileHeader::setGuidFileType(const QUuid &value) {
  guidFileType = value;
}

QUuid RevisionStoreFileHeader::getGuidFile() const { return guidFile; }

void RevisionStoreFileHeader::setGuidFile(const QUuid &value) {
  guidFile = value;
}

quint32 RevisionStoreFileHeader::getFfvLastWriterVersion() const {
  return ffvLastWriterVersion;
}

void RevisionStoreFileHeader::setFfvLastWriterVersion(quint32 value) {
  ffvLastWriterVersion = value;
}

quint32 RevisionStoreFileHeader::getFfvNewestWriterVersion() const {
  return ffvNewestWriterVersion;
}

void RevisionStoreFileHeader::setFfvNewestWriterVersion(quint32 value) {
  ffvNewestWriterVersion = value;
}

quint32 RevisionStoreFileHeader::getFfvOldestWriterVersion() const {
  return ffvOldestWriterVersion;
}

void RevisionStoreFileHeader::setFfvOldestWriterVersion(quint32 value) {
  ffvOldestWriterVersion = value;
}

quint32 RevisionStoreFileHeader::getFfvOldestReader() const {
  return ffvOldestReader;
}

void RevisionStoreFileHeader::setFfvOldestReader(quint32 value) {
  ffvOldestReader = value;
}

quint32 RevisionStoreFileHeader::getCTransactionsInLog() const {
  return cTransactionsInLog;
}

/**
 * @brief RevisionStoreFileHeader::setCTransactionsInLog
 * @param value
 *
 * \todo setting this value forces a new UUID for guidFileVersion as well
 */
void RevisionStoreFileHeader::setCTransactionsInLog(const quint32 value) {
  cTransactionsInLog = value;
}

quint64 RevisionStoreFileHeader::getRgbPlaceholder() const {
  return rgbPlaceholder;
}

void RevisionStoreFileHeader::setRgbPlaceholder(const quint64 value) {
  rgbPlaceholder = value;
}

quint8 RevisionStoreFileHeader::getFNeedsDefrag() const { return fNeedsDefrag; }

void RevisionStoreFileHeader::setFNeedsDefrag(const quint8 value) {
  fNeedsDefrag = value;
}

quint8 RevisionStoreFileHeader::getFRepairedFile() const {
  return fRepairedFile;
}

void RevisionStoreFileHeader::setFRepairedFile(const quint8 value) {
  fRepairedFile = value;
}

quint8 RevisionStoreFileHeader::getFNeedsGarbageCollect() const {
  return fNeedsGarbageCollect;
}

void RevisionStoreFileHeader::setFNeedsGarbageCollect(const quint8 value) {
  fNeedsGarbageCollect = value;
}

quint8 RevisionStoreFileHeader::getFHasNoEmbeddedFileObjects() const {
  return fHasNoEmbeddedFileObjects;
}

void RevisionStoreFileHeader::setFHasNoEmbeddedFileObjects(const quint8 value) {
  fHasNoEmbeddedFileObjects = value;
}

QUuid RevisionStoreFileHeader::getGuidAncestor() const { return guidAncestor; }

void RevisionStoreFileHeader::setGuidAncestor(const QUuid &value) {
  guidAncestor = value;
}

quint32 RevisionStoreFileHeader::getCrcName() const { return crcName; }

void RevisionStoreFileHeader::setCrcName(const quint32 value) {
  crcName = value;
}

std::weak_ptr<RevisionStoreChunkContainer>
RevisionStoreFileHeader::getFcrHashedChunkList() {
  return fcrHashedChunkList;
}

void RevisionStoreFileHeader::setFcrHashedChunkList(
    std::weak_ptr<RevisionStoreChunkContainer> value) {
  fcrHashedChunkList = value;
}

std::weak_ptr<RevisionStoreChunkContainer>
RevisionStoreFileHeader::getFcrTransactionLog() {
  return fcrTransactionLog;
}

void RevisionStoreFileHeader::setFcrTransactionLog(
    std::weak_ptr<RevisionStoreChunkContainer> value) {

  fcrTransactionLog = value;
}

std::weak_ptr<RevisionStoreChunkContainer>
RevisionStoreFileHeader::getFcrFileNodeListRoot() {
  return fcrFileNodeListRoot;
}

void RevisionStoreFileHeader::setFcrFileNodeListRoot(
    std::weak_ptr<RevisionStoreChunkContainer> value) {

  fcrFileNodeListRoot = value;
}

std::weak_ptr<RevisionStoreChunkContainer>
RevisionStoreFileHeader::getFcrFreeChunkList() {
  return fcrFreeChunkList;
}

void RevisionStoreFileHeader::setFcrFreeChunkList(
    std::weak_ptr<RevisionStoreChunkContainer> value) {
  fcrFreeChunkList = value;
}

quint64 RevisionStoreFileHeader::getCbExpectedFileLength() const {
  return cbExpectedFileLength;
}

void RevisionStoreFileHeader::setCbExpectedFileLength(const quint64 value) {
  cbExpectedFileLength = value;
}

quint64 RevisionStoreFileHeader::getCbFreeSpaceInFreeChunkList() const {
  return cbFreeSpaceInFreeChunkList;
}

void RevisionStoreFileHeader::setCbFreeSpaceInFreeChunkList(
    const quint64 value) {
  cbFreeSpaceInFreeChunkList = value;
}

QUuid RevisionStoreFileHeader::getGuidFileVersion() const {
  return guidFileVersion;
}

void RevisionStoreFileHeader::setGuidFileVersion(const QUuid &value) {
  guidFileVersion = value;
}

quint64 RevisionStoreFileHeader::getNFileVersionGeneration() const {
  return nFileVersionGeneration;
}

/**
 * @brief RevisionStoreFileHeader::setNFileVersionGeneration
 * @param value
 *
 * must be incremented with change of setGuidFileVersion
 */
void RevisionStoreFileHeader::setNFileVersionGeneration(const quint64 value) {
  nFileVersionGeneration = value;
}

QUuid RevisionStoreFileHeader::getGuidDenyReadFileVersion() const {
  return guidDenyReadFileVersion;
}

/**
 * @brief RevisionStoreFileHeader::setGuidDenyReadFileVersion
 * @param value
 *
 * \todo setting guidDenyReadFileVersion also requires a new file version
 */
void RevisionStoreFileHeader::setGuidDenyReadFileVersion(const QUuid &value) {
  guidDenyReadFileVersion = value;
}

quint32 RevisionStoreFileHeader::getGrfDebugLogFlags() const {
  return grfDebugLogFlags;
}

void RevisionStoreFileHeader::setGrfDebugLogFlags(const quint32 value) {
  grfDebugLogFlags = value;
}

quint32 RevisionStoreFileHeader::getBnCreated() const { return bnCreated; }

void RevisionStoreFileHeader::setBnCreated(const quint32 value) {
  bnCreated = value;
}

quint32 RevisionStoreFileHeader::getBnLastWroteToThisFile() const {
  return bnLastWroteToThisFile;
}

void RevisionStoreFileHeader::setBnLastWroteToThisFile(const quint32 value) {
  bnLastWroteToThisFile = value;
}

quint32 RevisionStoreFileHeader::getBnOldestWritten() const {
  return bnOldestWritten;
}

void RevisionStoreFileHeader::setBnOldestWritten(const quint32 value) {
  bnOldestWritten = value;
}

quint32 RevisionStoreFileHeader::getBnNewestWritten() const {
  return bnNewestWritten;
}

void RevisionStoreFileHeader::setBnNewestWritten(const quint32 value) {
  bnNewestWritten = value;
}

} // namespace libmson
