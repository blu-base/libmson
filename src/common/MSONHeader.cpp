#include "MSONHeader.h"
#include "FileChunkReference.h"

#include <QDebug>
#include <QDataStream>


static const QUuid v_guidFileType_One("{7b5c52e4-d88c-4da7-aeb1-5378d02996d3}");
static const QUuid v_guidFileType_OneToc2 ("{43ff2fa1-efd9-4c76-9ee2-10ea5722765f}");
static const QUuid v_guidFileFormat ("{109add3f-911b-49f5-a5d0-1791edc8aed8}");
static const QUuid v_guidZero ("{00000000-0000-0000-0000-000000000000}");

MSONHeader::MSONHeader()
  :
    //guidFileType {QUuid::fromString(QString(v_guidFileType_One))},
    guidFile {QUuid()},
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
    guidFileVersion {QUuid()},          // TODO check actual initialization
    guidDenyReadFileVersion {QUuid()},  // TODO check actual initialization
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

MSONHeader::MSONHeader(QDataStream& ds)
{
  qDebug() << "Parsing header from DataStream, " << ds.version();

  // if byte order is big endian, change to little endian
  if ( ! ds.byteOrder() ) {
    qDebug() << "MSONHeader: " << "Byte order changed to LittleEndian";
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  ds >> guidFileType;
  qDebug() << "guidFileType: " << guidFileType.toString()
           << ", valid: " << (this->isGuidFileTypeValid() ? "true" : "false")
           << ", ignored: " << (this->isGuidFileTypeIgnored() ? "true" : "false");

  ds >> guidFile;
  qDebug() << "guidFile: " << guidFile.toString()
           << ", valid: " << (this->isGuidFileValid() ? "true" : "false")
           << ", ignored: " << (this->isGuidFileIgnored() ? "true" : "false");


  ds >> guidLegacyFileVersion;
  qDebug() << "guidLegacyFileVersion: " << guidLegacyFileVersion.toString()
           << ", valid: " << (this->isGuidLegacyFileVersionValid() ? "true" : "false")
           << ", ignored: " << (this->isGuidLegacyFileVersionIgnored() ? "true" : "false");

  ds >> guidFileFormat;
  qDebug() << "guidFileFormat: " << guidFileFormat.toString()
           << ", valid: " << (this->isGuidFileFormatValid() ? "true" : "false")
           << ", ignored: " << (this->isGuidFileFormatIgnored() ? "true" : "false");

  ds >> ffvLastWriterVersion;
  qDebug() << "ffvLastWriterVersion: " << ffvLastWriterVersion
           << ", valid: " << (this->isFfvLastWriterVersionValid() ? "true" : "false")
           << ", ignored: " << (this->isFfvLastWriterVersionIgnored() ? "true" : "false");

  ds >> ffvOldestWriterVersion;
  qDebug() << "ffvOldestWriterVersion: " << ffvOldestWriterVersion
           << ", valid: " << (this->isFfvOldestWriterVersionValid() ? "true" : "false")
           << ", ignored: " << (this->isFfvOldestWriterVersionIgnored() ? "true" : "false");

  ds >> ffvNewestWriterVersion;
  qDebug() << "ffvNewestWriterVersion: " << ffvNewestWriterVersion
           << ", valid: " << (this->isFfvNewestWriterVersionValid() ? "true" : "false")
           << ", ignored: " << (this->isFfvNewestWriterVersionIgnored() ? "true" : "false");

  ds >> ffvOldestReader;
  qDebug() << "ffvOldestReader: " << ffvOldestReader
           << ", valid: " << (this->isFfvOldestReaderValid() ? "true" : "false")
           << ", ignored: " << (this->isFfvOldestReaderIgnored() ? "true" : "false");


  ds >> fcrLegacyFreeChunkList;
  qDebug() << "fcrLegacyFreeChunkList: " << fcrLegacyFreeChunkList
           << ", valid: " << (this->isFcrLegacyFreeChunkListValid() ? "true" : "false")
           << ", ignored: " << (this->isFcrLegacyFreeChunkListIgnored() ? "true" : "false");

  ds >> fcrLegacyTransactionLog;
  qDebug() << "fcrLegacyTransactionLog: " << fcrLegacyTransactionLog
           << ", valid: " << (this->isFcrLegacyTransactionLogValid() ? "true" : "false")
           << ", ignored: " << (this->isFcrLegacyTransactionLogIgnored() ? "true" : "false");

  ds >> cTransactionsInLog;
  qDebug() << "cTransactionsInLog: " << cTransactionsInLog
           << ", valid: " << (this->isCTransactionsInLogValid() ? "true" : "false")
           << ", ignored: " << (this->isCTransactionsInLogIgnored() ? "true" : "false");

  ds >> cbLegacyExpectedFileLength;
  qDebug() << "cbLegacyExpectedFileLength: " << cbLegacyExpectedFileLength
           << ", valid: " << (this->isCbLegacyExpectedFileLengthValid() ? "true" : "false")
           << ", ignored: " << (this->isCbLegacyExpectedFileLengthIgnored() ? "true" : "false");

  ds >> rgbPlaceholder;
  qDebug() << "rgbPlaceholder: " << rgbPlaceholder
           << ", valid: " << (this->isRgbPlaceholderValid() ? "true" : "false")
           << ", ignored: " << (this->isRgbPlaceholderIgnored() ? "true" : "false");

  ds >> fcrLegacyFileNodeListRoot;
  qDebug() << "fcrLegacyFileNodeListRoot: " << fcrLegacyFileNodeListRoot
           << ", valid: " << (this->isFcrLegacyFileNodeListRootValid() ? "true" : "false")
           << ", ignored: " << (this->isFcrLegacyFileNodeListRootIgnored() ? "true" : "false");

  ds >> cbLegacyFreeSpaceInFreeChunkList;
  qDebug() << "cbLegacyFreeSpaceInFreeChunkList: " << cbLegacyFreeSpaceInFreeChunkList
           << ", valid: " << (this->isCbLegacyFreeSpaceInFreeChunkListValid() ? "true" : "false")
           << ", ignored: " << (this->isCbLegacyFreeSpaceInFreeChunkListIgnored() ? "true" : "false");



}

MSONHeader MSONHeader::deserialize(QDataStream& ds)
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
  return guidFileType == v_guidFileType_One ||  guidFileType == v_guidFileType_OneToc2;
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
  return guidFile != v_guidZero;
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
  return guidLegacyFileVersion == v_guidZero;
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
  return guidFileFormat == v_guidFileFormat;
}

bool MSONHeader::isGuidFileFormatIgnored() const
{
  return false;
}



quint32  MSONHeader::getFfvLastWriterVersion() const
{
  return ffvLastWriterVersion;
}

void MSONHeader::setFfvLastWriterVersion(quint32  value)
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



quint32  MSONHeader::getFfvNewestWriterVersion() const
{
  return ffvNewestWriterVersion;
}

void MSONHeader::setFfvNewestWriterVersion(quint32  value)
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



quint32  MSONHeader::getFfvOldestWriterVersion() const
{
  return ffvOldestWriterVersion;
}

void MSONHeader::setFfvOldestWriterVersion(quint32  value)
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



quint32  MSONHeader::getFfvOldestReader() const
{
  return ffvOldestReader;
}

void MSONHeader::setFfvOldestReader(quint32  value)
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



quint32  MSONHeader::getCTransactionsInLog() const
{
  return cTransactionsInLog;
}


/**
 * @brief MSONHeader::setCTransactionsInLog
 * @param value
 *
 * \todo setting this value forces a new UUID for guidFileVersion as well
 */
void MSONHeader::setCTransactionsInLog(quint32  value)
{
  cTransactionsInLog = value;
}

void MSONHeader::changeTransactionsInLog(quint32  value)
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



quint32  MSONHeader::getCbLegacyExpectedFileLength() const
{
  return cbLegacyExpectedFileLength;
}

void MSONHeader::setCbLegacyExpectedFileLength(quint32  value)
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



quint64  MSONHeader::getRgbPlaceholder() const
{
  return rgbPlaceholder;
}

void MSONHeader::setRgbPlaceholder(quint64  value)
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



quint32  MSONHeader::getCbLegacyFreeSpaceInFreeChunkList() const
{
  return cbLegacyFreeSpaceInFreeChunkList;
}

void MSONHeader::setCbLegacyFreeSpaceInFreeChunkList(quint32  value)
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

void MSONHeader::setFNeedsDefrag(quint8 value)
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




quint8 MSONHeader::getFRepairedFile() const
{
  return fRepairedFile;
}

void MSONHeader::setFRepairedFile(quint8 value)
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

quint8 MSONHeader::getFNeedsGarbageCollect() const
{
  return fNeedsGarbageCollect;
}

void MSONHeader::setFNeedsGarbageCollect(quint8 value)
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




quint8 MSONHeader::getFHasNoEmbeddedFileObjects() const
{
  return fHasNoEmbeddedFileObjects;
}

void MSONHeader::setFHasNoEmbeddedFileObjects(quint8 value)
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
  return guidAncestor == v_guidZero;
}




quint32  MSONHeader::getCrcName() const
{
  return crcName;
}

void MSONHeader::setCrcName(quint32  value)
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



quint64  MSONHeader::getCbExpectedFileLength() const
{
  return cbExpectedFileLength;
}

void MSONHeader::setCbExpectedFileLength(quint64  value)
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



quint64  MSONHeader::getCbFreeSpaceInFreeChunkList() const
{
  return cbFreeSpaceInFreeChunkList;
}

void MSONHeader::setCbFreeSpaceInFreeChunkList(quint64  value)
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



quint64  MSONHeader::getNFileVersionGeneration() const
{
  return nFileVersionGeneration;
}

/**
 * @brief MSONHeader::setNFileVersionGeneration
 * @param value
 *
 * must be incremented with change of setGuidFileVersion
 */
void MSONHeader::setNFileVersionGeneration(quint64  value)
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
  return guidDenyReadFileVersion != v_guidZero;
}

bool MSONHeader::isGuidDenyReadFileVersionIgnored() const
{
  return false;
}



quint32  MSONHeader::getGrfDebugLogFlags() const
{
  return grfDebugLogFlags;
}

void MSONHeader::setGrfDebugLogFlags(quint32  value)
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



quint32  MSONHeader::getBnCreated() const
{
  return bnCreated;
}

void MSONHeader::setBnCreated(quint32  value)
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



quint32  MSONHeader::getBnLastWroteToThisFile() const
{
  return bnLastWroteToThisFile;
}

void MSONHeader::setBnLastWroteToThisFile(quint32  value)
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



quint32  MSONHeader::getBnOldestWritten() const
{
  return bnOldestWritten;
}

void MSONHeader::setBnOldestWritten(quint32  value)
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



quint32  MSONHeader::getBnNewestWritten() const
{
  return bnNewestWritten;
}

void MSONHeader::setBnNewestWritten(quint32  value)
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


