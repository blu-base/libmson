#include "MSONHeader.h"
#include "FileChunkReference.h"

MSONHeader::MSONHeader()
  :
    //guidFileType {QUuid::fromString(QString(v_guidFileType_One))},
    guidFile {QUuid().createUuid()},
    guidLegacyFileVersion {QUuid()},
    guidFileFormat {QUuid(v_guidFileFormat)},
    ffvLastWriterVersion {0x0000002A},
    ffvOldestWriterVersion {0x0000002A},
    ffvNewestWriterVersion {0x0000002A},
    ffvOldestReader {0x0000002A},
    fcrLegacyFreeChunkList {FileChunkReference32(I_FileChunkReference::INITTYPE::INIT_FCRZERO)},
    fcrLegacyTransactionLog {FileChunkReference32(I_FileChunkReference::INITTYPE::INIT_FCRNIL)},
    cTransactionsInLog {1},
    cbLegacyExpectedFileLength {0},
    rgbPlaceholder {0},
    fcrLegacyFileNodeListRoot {FileChunkReference32(I_FileChunkReference::INITTYPE::INIT_FCRNIL)},
    cbLegacyFreeSpaceInFreeChunkList{0},
    fNeedsDefrag {0},
    fRepairedFile {0},
    fNeedsGarbageCollect {0},
    fHasNoEmbeddedFileObjects {0},
    guidAncestor{QUuid()},
    crcName {0}, // TODO init crcName properly
    cbExpectedFileLength {0},
    cbFreeSpaceInFreeChunkList {0},
    guidFileVersion {QUuid().createUuid()},          // TODO check actual initialization
    guidDenyReadFileVersion {QUuid().createUuid()},  // TODO check actual initialization
    grfDebugLogFlags {0},
    fcrDebugLog {FileChunkReference64x32(I_FileChunkReference::INITTYPE::INIT_FCRZERO)},
    fcrAllocVerificationFreeChunkList {FileChunkReference64x32(I_FileChunkReference::INITTYPE::INIT_FCRZERO)},
    bnCreated {0},
    bnLastWroteToThisFile{0},
    bnOldestWritten {0},
    bnNewestWritten {0},
    reservedHeaderTail {QByteArray(736,'\0')}
{
}


QUuid MSONHeader::getGuidFileType() const
{
  return guidFileType;
}

void MSONHeader::setGuidFileType(const QUuid &value)
{
  guidFileType = value;
}


/**
 * @brief MSONHeader::isGuidFileTypeValid
 * @return
 *
 * GuidFile is only valid if it contains
 * {7B5C52E4-D88C-4DA7-AEB1-5378D02996D3} for .one file format, or
 * {43FF2FA1-EFD9-4C76-9EE2-10EA5722765F} for .onetoc2 file format
 */
bool MSONHeader::isGuidFileTypeValid() const
{
  QString str = guidFile.toString();

  return str == v_guidFileType_One ||
      str == v_guidFileType_OneToc2;
}

bool MSONHeader::isGuidFileTypeIgnored() const
{
  return false;
}




QUuid MSONHeader::getGuidFile() const
{
  return guidFile;
}

void MSONHeader::setGuidFile(const QUuid &value)
{
  guidFile = value;
}

bool MSONHeader::isGuidFileValid() const
{
  return guidFile.toString() != v_guidZero;
}

bool MSONHeader::isGuidFileIgnored() const
{
  return false;
}




QUuid MSONHeader::getGuidLegacyFileVersion() const
{
  return guidLegacyFileVersion;
}

void MSONHeader::setGuidLegacyFileVersion(const QUuid &value)
{
  guidLegacyFileVersion = value;
}

/**
 * @brief MSONHeader::isGuidLegacyFileVersionValid
 * @return
 *
 * guidLegacyFileVersion must be {00000000-0000-0000-0000-000000000000}"
 */
bool MSONHeader::isGuidLegacyFileVersionValid() const
{
  return guidLegacyFileVersion.toString() == v_guidZero;
}

bool MSONHeader::isGuidLegacyFileVersionIgnored() const
{
  return true;
}



QUuid MSONHeader::getGuidFileFormat() const
{
  return guidFileFormat;
}

void MSONHeader::setGuidFileFormat(const QUuid &value)
{
  guidFileFormat = value;
}

/**
 * @brief MSONHeader::isGuidFileFormatValid
 * @return
 *
 * guidFileFormat must be {109ADD3F-911B-49F5-A5D0-1791EDC8AED8}
 */
bool MSONHeader::isGuidFileFormatValid() const
{
  return guidFileFormat.toString() == v_guidFileFormat;
}

bool MSONHeader::isGuidFileFormatIgnored() const
{
  return false;
}



uint32_t  MSONHeader::getFfvLastWriterVersion() const
{
  return ffvLastWriterVersion;
}

void MSONHeader::setFfvLastWriterVersion(uint32_t  value)
{
  ffvLastWriterVersion = value;
}

/**
 * @brief MSONHeader::isFfvLastWriterVersionValid
 * @return
 *
 * must be 0x0000002A to indicate .one file format, or
 * must be 0x0000001B to indicate .onetoc2 file format
 */
bool MSONHeader::isFfvLastWriterVersionValid() const
{
  return ffvLastWriterVersion == 0x0000002A ||
      ffvLastWriterVersion == 0x0000001B;
}

bool MSONHeader::isFfvLastWriterVersionIgnored() const
{
  return false;
}



uint32_t  MSONHeader::getFfvNewestWriterVersion() const
{
  return ffvNewestWriterVersion;
}

void MSONHeader::setFfvNewestWriterVersion(uint32_t  value)
{
  ffvNewestWriterVersion = value;
}
/**
 * @brief MSONHeader::isFfvNewestWriterVersionValid
 * @return
 *
 * must be 0x0000002A to indicate .one file format, or
 * must be 0x0000001B to indicate .onetoc2 file format
 */
bool MSONHeader::isFfvNewestWriterVersionValid() const
{
  return ffvLastWriterVersion == 0x0000002A ||
      ffvLastWriterVersion == 0x0000001B;
}

bool MSONHeader::isFfvNewestWriterVersionIgnored() const
{
  return false;
}



uint32_t  MSONHeader::getFfvOldestWriterVersion() const
{
  return ffvOldestWriterVersion;
}

void MSONHeader::setFfvOldestWriterVersion(uint32_t  value)
{
  ffvOldestWriterVersion = value;
}

/**
 * @brief MSONHeader::isFfvOldestWriterVersionValid
 * @return
 * must be 0x0000002A to indicate .one file format, or
 * must be 0x0000001B to indicate .onetoc2 file format
 */
bool MSONHeader::isFfvOldestWriterVersionValid() const
{
  return ffvLastWriterVersion == 0x0000002A ||
      ffvLastWriterVersion == 0x0000001B;
}


bool MSONHeader::isFfvOldestWriterVersionIgnored() const
{
  return false;
}



uint32_t  MSONHeader::getFfvOldestReader() const
{
  return ffvOldestReader;
}

void MSONHeader::setFfvOldestReader(uint32_t  value)
{
  ffvOldestReader = value;
}

/**
 * @brief MSONHeader::isFfvOldestReaderValid
 * @return
 * must be 0x0000002A to indicate .one file format, or
 * must be 0x0000001B to indicate .onetoc2 file format
 */
bool MSONHeader::isFfvOldestReaderValid() const
{
  return ffvLastWriterVersion == 0x0000002A ||
      ffvLastWriterVersion == 0x0000001B;
}

bool MSONHeader::isFfvOldestReaderIgnored() const
{
  return false;
}



FileChunkReference32 MSONHeader::getFcrLegacyFreeChunkList() const
{
  return fcrLegacyFreeChunkList;
}

void MSONHeader::setFcrLegacyFreeChunkList(const FileChunkReference32 &value)
{
  fcrLegacyFreeChunkList = value;
}

/**
 * @brief MSONHeader::isFcrLegacyFreeChunkListValid
 * @return
 *
 * must be fcrZero
 */
bool MSONHeader::isFcrLegacyFreeChunkListValid() const
{
  return fcrLegacyFreeChunkList.is_fcrZero();
}

bool MSONHeader::isFcrLegacyFreeChunkListIgnored() const
{
  return false;
}



FileChunkReference32 MSONHeader::getFcrLegacyTransactionLog() const
{
  return fcrLegacyTransactionLog;
}

void MSONHeader::setFcrLegacyTransactionLog(const FileChunkReference32 &value)
{
  fcrLegacyTransactionLog = value;
}

/**
 * @brief MSONHeader::isFcrLegacyTransactionLogValid
 * @return
 *
 * must be fcrNil
 */
bool MSONHeader::isFcrLegacyTransactionLogValid() const
{
  return fcrLegacyTransactionLog.is_fcrNil();
}

bool MSONHeader::isFcrLegacyTransactionLogIgnored() const
{
  return false;
}



uint32_t  MSONHeader::getCTransactionsInLog() const
{
  return cTransactionsInLog;
}


/**
 * @brief MSONHeader::setCTransactionsInLog
 * @param value
 *
 * \todo setting this value forces a new UUID for guidFileVersion as well
 */
void MSONHeader::setCTransactionsInLog(uint32_t  value)
{
  cTransactionsInLog = value;
}

void MSONHeader::changeTransactionsInLog(uint32_t  value)
{
  cTransactionsInLog = value;
  nextGuidFileVersion();
}

/**
 * @brief MSONHeader::isCTransactionsInLogValid
 * @return
 *
 * must not be zero
 */
bool MSONHeader::isCTransactionsInLogValid() const
{
  return cTransactionsInLog != 0;
}

bool MSONHeader::isCTransactionsInLogIgnored() const
{
  return false;
}



uint32_t  MSONHeader::getCbLegacyExpectedFileLength() const
{
  return cbLegacyExpectedFileLength;
}

void MSONHeader::setCbLegacyExpectedFileLength(uint32_t  value)
{
  cbLegacyExpectedFileLength = value;
}

/**
 * @brief MSONHeader::isCbLegacyExpectedFileLengthValid
 * @return
 *
 * must be zero
 */

bool MSONHeader::isCbLegacyExpectedFileLengthValid() const
{
  return cbLegacyExpectedFileLength == 0;
}

bool MSONHeader::isCbLegacyExpectedFileLengthIgnored() const
{
  return true;
}



uint64_t  MSONHeader::getRgbPlaceholder() const
{
  return rgbPlaceholder;
}

void MSONHeader::setRgbPlaceholder(uint64_t  value)
{
  rgbPlaceholder = value;
}

/**
 * @brief MSONHeader::isRgbPlaceholderValid
 * @return
 *
 * must be zero
 */
bool MSONHeader::isRgbPlaceholderValid() const
{
  return rgbPlaceholder == 0;
}

bool MSONHeader::isRgbPlaceholderIgnored() const
{
  return true;
}



FileChunkReference32 MSONHeader::getFcrLegacyFileNodeListRoot() const
{
  return fcrLegacyFileNodeListRoot;
}

void MSONHeader::setFcrLegacyFileNodeListRoot(const FileChunkReference32 &value)
{
  fcrLegacyFileNodeListRoot = value;
}

bool MSONHeader::isFcrLegacyFileNodeListRootValid() const
{
  return fcrLegacyFileNodeListRoot.is_fcrNil();
}

bool MSONHeader::isFcrLegacyFileNodeListRootIgnored() const
{
  return false;
}



uint32_t  MSONHeader::getCbLegacyFreeSpaceInFreeChunkList() const
{
  return cbLegacyFreeSpaceInFreeChunkList;
}

void MSONHeader::setCbLegacyFreeSpaceInFreeChunkList(uint32_t  value)
{
  cbLegacyFreeSpaceInFreeChunkList = value;
}

bool MSONHeader::isCbLegacyFreeSpaceInFreeChunkListValid() const
{
  return cbLegacyExpectedFileLength == 0;
}

bool MSONHeader::isCbLegacyFreeSpaceInFreeChunkListIgnored() const
{
  return true;
}



uchar MSONHeader::getFNeedsDefrag() const
{
  return fNeedsDefrag;
}

void MSONHeader::setFNeedsDefrag(uint8_t value)
{
  fNeedsDefrag = value;
}

/**
 * @brief MSONHeader::isFNeedsDefragValid
 *
 * not specified
 * @return
 */
bool MSONHeader::isFNeedsDefragValid() const
{
  return true;
}

bool MSONHeader::isFNeedsDefragIgnored() const
{
  return true;
}




uint8_t MSONHeader::getFRepairedFile() const
{
  return fRepairedFile;
}

void MSONHeader::setFRepairedFile(uint8_t value)
{
  fRepairedFile = value;
}

/**
 * @brief MSONHeader::isFRepairedFileValid
 *
 * not specified
 * @return
 */
bool MSONHeader::isFRepairedFileValid() const
{
  return true;
}

bool MSONHeader::isFRepairedFileIgnored() const
{
  return true;
}

uint8_t MSONHeader::getFNeedsGarbageCollect() const
{
  return fNeedsGarbageCollect;
}

void MSONHeader::setFNeedsGarbageCollect(uint8_t value)
{
  fNeedsGarbageCollect = value;
}

/**
 * @brief MSONHeader::isFNeedsGarbageCollectValid
 *
 * not specified
 * @return
 */
bool MSONHeader::isFNeedsGarbageCollectValid() const
{
  return true;
}

bool MSONHeader::isFNeedsGarbageCollectIgnored() const
{
  return true;
}




uint8_t MSONHeader::getFHasNoEmbeddedFileObjects() const
{
  return fHasNoEmbeddedFileObjects;
}

void MSONHeader::setFHasNoEmbeddedFileObjects(uint8_t value)
{
  fHasNoEmbeddedFileObjects = value;
}

bool MSONHeader::isFHasNoEmbeddedFileObjectsValid() const
{
  return fHasNoEmbeddedFileObjects == 0;
}

bool MSONHeader::isFHasNoEmbeddedFileObjectsIgnored() const
{
  return true;
}



QUuid MSONHeader::getGuidAncestor() const
{
  return guidAncestor;
}


void MSONHeader::setGuidAncestor(const QUuid &value)
{
  guidAncestor = value;
}

/**
  \todo Check if Header.guidFile exists
 * @brief MSONHeader::isGuidAncestorValid
 *
 * guidAncestor should mark the Header.guidFile location of the table of contents file
 *
 * @return
 */
bool MSONHeader::isGuidAncestorValid() const
{
  return true;
}

bool MSONHeader::isGuidAncestorIgnored() const
{
  return false;
}

/**
 * @brief MSONHeader::guidAncestorLocationInCWD
 * \todo
 * Deduct if Header.guidFile is in current directory, or whether it is in the parent directory.
 * If GUID is zero, no table of contents file present
 * @return
 */
bool MSONHeader::guidAncestorLocationInCD() const
{
  return false;
}
bool MSONHeader::guidAncestorLocationInPD() const
{
  return false;
}

bool MSONHeader::guidAncestorLocationNotPresent() const
{
  return guidAncestor.toString() == v_guidZero;
}




uint32_t  MSONHeader::getCrcName() const
{
  return crcName;
}

void MSONHeader::setCrcName(uint32_t  value)
{
  crcName = value;
}

bool MSONHeader::isCrcNameValid() const
{
  return true;
}

bool MSONHeader::isCrcNameIgnored() const
{
  return false;
}



FileChunkReference64x32 MSONHeader::getFcrHashedChunkList() const
{
  return fcrHashedChunkList;
}

void MSONHeader::setFcrHashedChunkList(const FileChunkReference64x32 &value)
{
  fcrHashedChunkList = value;
}

bool MSONHeader::isFcrHashedChunkListValid() const
{
  return true;
}

bool MSONHeader::isFcrHashedChunkListIgnored() const
{
  return false;
}

/**
 * @brief MSONHeader::fcrHashedChunkList_exits
 * @return
 *
 * if fcrHashedChunkList is fcrNil or fcrZero, then HashedChunkLink does not exist.
 */
bool MSONHeader::fcrHashedChunkList_exits() const
{


  return !( fcrHashedChunkList.is_fcrNil() || fcrHashedChunkList.is_fcrZero());
}




FileChunkReference64x32 MSONHeader::getFcrTransactionLog() const
{
  return fcrTransactionLog;
}

void MSONHeader::setFcrTransactionLog(const FileChunkReference64x32 &value)
{
  fcrTransactionLog = value;
}

/**
 * @brief MSONHeader::isFcrTransactionLogValid
 * @return
 *
 * must not be fcrNil and fcrZero
 */
bool MSONHeader::isFcrTransactionLogValid() const
{
  return !fcrTransactionLog.is_fcrNil() && !fcrTransactionLog.is_fcrZero();

}

bool MSONHeader::isFcrTransactionLogIgnored() const
{
  return false;
}



FileChunkReference64x32 MSONHeader::getFcrFileNodeListRoot() const
{
  return fcrFileNodeListRoot;
}

void MSONHeader::setFcrFileNodeListRoot(const FileChunkReference64x32 &value)
{
  fcrFileNodeListRoot = value;
}

/**
 * @brief MSONHeader::isFcrFileNodeListRootValid
 * @return
 *
 * must not be fcrNil and fcrZero
 */
bool MSONHeader::isFcrFileNodeListRootValid() const
{
  return !fcrFileNodeListRoot.is_fcrNil() && !fcrFileNodeListRoot.is_fcrZero();
}

bool MSONHeader::isFcrFileNodeListRootIgnored() const
{
  return false;
}



FileChunkReference64x32 MSONHeader::getFcrFreeChunkList() const
{
  return fcrFreeChunkList;
}

void MSONHeader::setFcrFreeChunkList(const FileChunkReference64x32 &value)
{
  fcrFreeChunkList = value;
}

/**
 * @brief MSONHeader::isFcrFreeChunkListValid
 * @return
 *
 * unspecified validity
 */
bool MSONHeader::isFcrFreeChunkListValid() const
{
  return true;
}

bool MSONHeader::isFcrFreeChunkListIgnored() const
{
  return false;
}

/**
 * @brief MSONHeader::fcrFreeChunkList_exits
 * @return
 *
 * If fcrFreeChunkList is zero, then FreeChunkList does not exist
 */
bool MSONHeader::fcrFreeChunkList_exits() const
{
  return !(fcrFreeChunkList.is_fcrNil() || fcrFreeChunkList.is_fcrZero());
}



uint64_t  MSONHeader::getCbExpectedFileLength() const
{
  return cbExpectedFileLength;
}

void MSONHeader::setCbExpectedFileLength(uint64_t  value)
{
  cbExpectedFileLength = value;
}

bool MSONHeader::isCbExpectedFileLengthValid() const
{
  return true;
}

bool MSONHeader::isCbExpectedFileLengthIgnored() const
{
  return false;
}



uint64_t  MSONHeader::getCbFreeSpaceInFreeChunkList() const
{
  return cbFreeSpaceInFreeChunkList;
}

void MSONHeader::setCbFreeSpaceInFreeChunkList(uint64_t  value)
{
  cbFreeSpaceInFreeChunkList = value;
}

/**
 * @brief MSONHeader::isCbFreeSpaceInFreeChunkListValid
 * @return
 *
 * \todo unspecified validity
 *
 * OneNote 2010 sometimes writes invalid value here
 */
bool MSONHeader::isCbFreeSpaceInFreeChunkListValid() const
{
  return true;
}

bool MSONHeader::isCbFreeSpaceInFreeChunkListIgnored() const
{
  return false;
}



QUuid MSONHeader::getGuidFileVersion() const
{
  return guidFileVersion;
}

void MSONHeader::setGuidFileVersion(const QUuid &value)
{
  guidFileVersion = value;
}

/**
 * @brief MSONHeader::nextGuidFileVersion
 *
 * advances guidFileVersion, and increments nFileVersionGeneration
 */
void MSONHeader::nextGuidFileVersion()
{
  guidFileVersion = QUuid::createUuid();

  nFileVersionGeneration++;

}

bool MSONHeader::isGuidFileVersionValid() const
{
  return guidFileVersion != v_guidZero;
}

bool MSONHeader::isGuidFileVersionIgnored() const
{
  return false;
}



uint64_t  MSONHeader::getNFileVersionGeneration() const
{
  return nFileVersionGeneration;
}

/**
 * @brief MSONHeader::setNFileVersionGeneration
 * @param value
 *
 * must be incremented with change of setGuidFileVersion
 */
void MSONHeader::setNFileVersionGeneration(uint64_t  value)
{
  nFileVersionGeneration = value;
}

/**
 * @brief MSONHeader::isNFileVersionGenerationValid
 * @return
 *
 * unspecified validity
 */
bool MSONHeader::isNFileVersionGenerationValid() const
{
  return true;
}

bool MSONHeader::isNFileVersionGenerationIgnored() const
{
  return false;
}

QUuid MSONHeader::getGuidDenyReadFileVersion() const
{
  return guidDenyReadFileVersion;
}


/**
 * @brief MSONHeader::setGuidDenyReadFileVersion
 * @param value
 *
 * \todo setting guidDenyReadFileVersion also requires a new file version
 */
void MSONHeader::setGuidDenyReadFileVersion(const QUuid &value)
{
  guidDenyReadFileVersion = value;
}

void MSONHeader::changeGuidDenyReadFileVersion()
{
  guidDenyReadFileVersion = QUuid::createUuid();
}



bool MSONHeader::isGuidDenyReadFileVersionValid() const
{
  return guidDenyReadFileVersion.toString() != v_guidZero;
}

bool MSONHeader::isGuidDenyReadFileVersionIgnored() const
{
  return false;
}



uint32_t  MSONHeader::getGrfDebugLogFlags() const
{
  return grfDebugLogFlags;
}

void MSONHeader::setGrfDebugLogFlags(uint32_t  value)
{
  grfDebugLogFlags = value;
}

bool MSONHeader::isGrfDebugLogFlagsValid() const
{
  return grfDebugLogFlags == 0;
}

bool MSONHeader::isGrfDebugLogFlagsIgnored() const
{
  return true;
}



FileChunkReference64x32 MSONHeader::getFcrDebugLog() const
{
  return fcrDebugLog;
}

void MSONHeader::setFcrDebugLog(const FileChunkReference64x32 &value)
{
  fcrDebugLog = value;
}

bool MSONHeader::isFcrDebugLogValid() const
{
  return fcrDebugLog.is_fcrZero();
}

bool MSONHeader::isFcrDebugLogIgnored() const
{
  return true;
}



FileChunkReference64x32 MSONHeader::getFcrAllocVerificationFreeChunkList() const
{
  return fcrAllocVerificationFreeChunkList;
}

void MSONHeader::setFcrAllocVerificationFreeChunkList(const FileChunkReference64x32 &value)
{
  fcrAllocVerificationFreeChunkList = value;
}

bool MSONHeader::isFcrAllocVerificationFreeChunkListValid() const
{
  return fcrAllocVerificationFreeChunkList.is_fcrZero();
}

bool MSONHeader::isFcrAllocVerificationFreeChunkListIgnored() const
{
  return true;
}



uint32_t  MSONHeader::getBnCreated() const
{
  return bnCreated;
}

void MSONHeader::setBnCreated(uint32_t  value)
{
  bnCreated = value;
}


/**
 * @brief MSONHeader::isBnCreatedValid
 * @return
 *
 * unspecified validity
 */
bool MSONHeader::isBnCreatedValid() const
{
  return true;
}

bool MSONHeader::isBnCreatedIgnored() const
{
  return true;
}



uint32_t  MSONHeader::getBnLastWroteToThisFile() const
{
  return bnLastWroteToThisFile;
}

void MSONHeader::setBnLastWroteToThisFile(uint32_t  value)
{
  bnLastWroteToThisFile = value;
}

/**
 * @brief MSONHeader::isBnLastWroteToThisFileValid
 * @return
 *
 * unspecified validity
 */
bool MSONHeader::isBnLastWroteToThisFileValid() const
{
  return true;
}

bool MSONHeader::isBnLastWroteToThisFileIgnored() const
{
  return true;
}



uint32_t  MSONHeader::getBnOldestWritten() const
{
  return bnOldestWritten;
}

void MSONHeader::setBnOldestWritten(uint32_t  value)
{
  bnOldestWritten = value;
}

/**
 * @brief MSONHeader::isBnOldestWrittenValid
 * @return
 *
 * unspecified validity
 */
bool MSONHeader::isBnOldestWrittenValid() const
{
  return true;
}

bool MSONHeader::isBnOldestWrittenIgnored() const
{
  return true;
}



uint32_t  MSONHeader::getBnNewestWritten() const
{
  return bnNewestWritten;
}

void MSONHeader::setBnNewestWritten(uint32_t  value)
{
  bnNewestWritten = value;
}

/**
 * @brief MSONHeader::isBnNewestWrittenValid
 * @return
 *
 * unspecified validity
 */
bool MSONHeader::isBnNewestWrittenValid() const
{
  return true;
}

bool MSONHeader::isBnNewestWrittenIgnored() const
{
  return true;
}

QByteArray MSONHeader::getReservedHeaderTail() const
{
  return reservedHeaderTail;
}

void MSONHeader::setReservedHeaderTail(const QByteArray &value)
{
  reservedHeaderTail = value;
}

bool MSONHeader::isReservedHeaderTailValid() const
{
  return reservedHeaderTail == QByteArray(reservedHeaderTail.size(), '\0');
}

bool MSONHeader::isReservedHeaderTailIgnored() const
{
  return true;
}


