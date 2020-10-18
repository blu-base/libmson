

#include "RevisionStoreFileHeader.h"
#include <memory>

#include "commonTypes/FileChunkReference32.h"
#include "commonTypes/FileChunkReference64x32.h"
#include "commonTypes/IFileChunkReference.h"

#include "helper/CrcAlgorithms.h"

#include <QDataStream>
#include <QDebug>

#include "helper/Helper.h"


/// \todo RevisionStoreFileHeader make input values const
namespace MSONcommon {

static const QUuid v_guidFileType_One("{7b5c52e4-d88c-4da7-aeb1-5378d02996d3}");
static const QUuid
    v_guidFileType_OneToc2("{43ff2fa1-efd9-4c76-9ee2-10ea5722765f}");
static const QUuid v_guidFileFormat("{109add3f-911b-49f5-a5d0-1791edc8aed8}");
static const QUuid v_guidZero("{00000000-0000-0000-0000-000000000000}");

static constexpr const quint32 def_reservedHeaderTailLength = 728;

RevisionStoreFileHeader::RevisionStoreFileHeader()
    : // guidFileType {QUuid::fromString(QString(v_guidFileType_One))},
      guidFile{QUuid::createUuid()}, guidLegacyFileVersion{QUuid()},
      guidFileFormat{QUuid(v_guidFileFormat)}, ffvLastWriterVersion{0x0000002A},
      ffvOldestWriterVersion{0x0000002A}, ffvNewestWriterVersion{0x0000002A},
      ffvOldestReader{0x0000002A},
      fcrLegacyFreeChunkList{FileChunkReference32()},
      fcrLegacyTransactionLog{FileChunkReference32(FCR_INITTYPE::FCRNIL)},
      cTransactionsInLog{1}, cbLegacyExpectedFileLength{0x400}, rgbPlaceholder{0},
      fcrLegacyFileNodeListRoot{FileChunkReference32(FCR_INITTYPE::FCRNIL)},
      cbLegacyFreeSpaceInFreeChunkList{0}, fNeedsDefrag{0}, fRepairedFile{0},
      fNeedsGarbageCollect{0}, fHasNoEmbeddedFileObjects{0},
      guidAncestor{QUuid()}, crcName{0}, /// \todo init crcName properly
      fcrHashedChunkList{FileChunkReference64x32()},
      fcrTransactionLog{FileChunkReference64x32()},
      fcrFileNodeListRoot{FileChunkReference64x32()},
      fcrFreeChunkList{FileChunkReference64x32()}, cbExpectedFileLength{0},
      cbFreeSpaceInFreeChunkList{0},
      guidFileVersion{QUuid()}, /// \todo check actual initialization
      nFileVersionGeneration{},
      guidDenyReadFileVersion{QUuid()}, /// \todo  check actual initialization
      grfDebugLogFlags{0}, fcrDebugLog{FileChunkReference64x32()},
      fcrAllocVerificationFreeChunkList{FileChunkReference64x32()},
      bnCreated{0}, bnLastWroteToThisFile{0}, bnOldestWritten{0},
      bnNewestWritten{0}, reservedHeaderTailLength{
                            def_reservedHeaderTailLength} {}

quint64 RevisionStoreFileHeader::getSizeInFile() { return sizeInFile; }

void RevisionStoreFileHeader::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("Header");

  xmlWriter.writeStartElement("guidFileType");
  xmlWriter.writeCharacters(guidFileType.toString());
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("guidFile");
  xmlWriter.writeCharacters(guidFile.toString());
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("guidLegacyFileVersion");
  xmlWriter.writeCharacters(guidLegacyFileVersion.toString());
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("guidFileFormat");
  xmlWriter.writeCharacters(guidFileFormat.toString());
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("ffvLastWriterVersion");
  xmlWriter.writeCharacters(QString::number(ffvLastWriterVersion));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("ffvOldestWriterVersion");
  xmlWriter.writeCharacters(QString::number(ffvOldestWriterVersion));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("ffvNewestWriterVersion");
  xmlWriter.writeCharacters(QString::number(ffvNewestWriterVersion));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("ffvOldestReader");
  xmlWriter.writeCharacters(QString::number(ffvOldestReader));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fcrLegacyFreeChunkList");
  xmlWriter << fcrLegacyFreeChunkList;
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fcrLegacyTransactionLog");
  xmlWriter << fcrLegacyTransactionLog;
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("cTransactionsInLog");
  xmlWriter.writeCharacters(QString::number(cTransactionsInLog));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("cbLegacyExpectedFileLength");
  xmlWriter.writeCharacters(QString::number(cbLegacyExpectedFileLength));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("rgbPlaceholder");
  xmlWriter.writeCharacters(QString::number(rgbPlaceholder));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fcrLegacyFileNodeListRoot");
  xmlWriter << fcrLegacyFileNodeListRoot;
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("cbLegacyFreeSpaceInFreeChunkList");
  xmlWriter.writeCharacters(QString::number(cbLegacyFreeSpaceInFreeChunkList));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fNeedsDefrag");
  xmlWriter.writeCharacters(QString::number(fNeedsDefrag));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fRepairedFile");
  xmlWriter.writeCharacters(QString::number(fRepairedFile));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fNeedsGarbageCollect");
  xmlWriter.writeCharacters(QString::number(fNeedsGarbageCollect));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fHasNoEmbeddedFileObjects");
  xmlWriter.writeCharacters(QString::number(fHasNoEmbeddedFileObjects));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("guidAncestor");
  xmlWriter.writeCharacters(guidAncestor.toString());
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("crcName");
  xmlWriter.writeCharacters(qStringHex(crcName, 8));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fcrHashedChunkList");
  xmlWriter << fcrHashedChunkList;
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fcrTransactionLog");
  xmlWriter << fcrTransactionLog;
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fcrFileNodeListRoot");
  xmlWriter << fcrFileNodeListRoot;
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fcrFreeChunkList");
  xmlWriter << fcrFreeChunkList;
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("cbExpectedFileLength");
  xmlWriter.writeCharacters(qStringHex(cbExpectedFileLength, 16));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("cbFreeSpaceInFreeChunkList");
  xmlWriter.writeCharacters(qStringHex(cbFreeSpaceInFreeChunkList, 16));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("guidFileVersion");
  xmlWriter.writeCharacters(guidFileVersion.toString());
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("nFileVersionGeneration");
  xmlWriter.writeCharacters(QString::number(nFileVersionGeneration));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("guidDenyReadFileVersion");
  xmlWriter.writeCharacters(guidDenyReadFileVersion.toString());
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("grfDebugLogFlags");
  xmlWriter.writeCharacters(QString::number(grfDebugLogFlags));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fcrDebugLog");
  xmlWriter << fcrDebugLog;
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fcrAllocVerificationFreeChunkList");
  xmlWriter << fcrAllocVerificationFreeChunkList;
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("bnCreated");
  xmlWriter.writeCharacters(qStringHex(bnCreated, 8));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("bnLastWroteToThisFile");
  xmlWriter.writeCharacters(qStringHex(bnLastWroteToThisFile, 8));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("bnOldestWritten");
  xmlWriter.writeCharacters(qStringHex(bnOldestWritten, 8));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("bnNewestWritten");
  xmlWriter.writeCharacters(qStringHex(bnNewestWritten, 8));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("reservedHeaderTailLength");
  xmlWriter.writeCharacters(qStringHex(reservedHeaderTailLength, 4));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement(); // Header
}

void RevisionStoreFileHeader::serialize(QDataStream &ds) const {
  // if byte order is big endian, change to little endian
  if (ds.byteOrder() == QDataStream::BigEndian) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  ds << guidFileType;
  ds << guidFile;
  ds << guidLegacyFileVersion;
  ds << guidFileFormat;
  ds << ffvLastWriterVersion;
  ds << ffvOldestWriterVersion;
  ds << ffvNewestWriterVersion;
  ds << ffvOldestReader;
  ds << fcrLegacyFreeChunkList;
  ds << fcrLegacyTransactionLog;
  ds << cTransactionsInLog;
  ds << cbLegacyExpectedFileLength;
  ds << rgbPlaceholder;
  ds << fcrLegacyFileNodeListRoot;
  ds << cbLegacyFreeSpaceInFreeChunkList;
  ds << fNeedsDefrag;
  ds << fRepairedFile;
  ds << fNeedsGarbageCollect;
  ds << fHasNoEmbeddedFileObjects;
  ds << guidAncestor;

  /// \todo get the fileName from somewhere to compute final crcName. Might be done as post process
  ///
  /// QString fileName;
  /// ds <<  MSONcommon::Crc32::computeCrcName(fileName);
  ///
  /// \todo Maybe crcName should be computed elsewhere to keep it between saves
  ds << crcName;
  ds << fcrHashedChunkList;
  ds << fcrTransactionLog;
  ds << fcrFileNodeListRoot;
  ds << fcrFreeChunkList;
  ds << cbExpectedFileLength;
  ds << cbFreeSpaceInFreeChunkList;
  ds << guidFileVersion;
  ds << nFileVersionGeneration;
  ds << guidDenyReadFileVersion;
  ds << grfDebugLogFlags;
  ds << fcrDebugLog;
  ds << fcrAllocVerificationFreeChunkList;
  ds << bnCreated;
  ds << bnLastWroteToThisFile;
  ds << bnOldestWritten;
  ds << bnNewestWritten;
  ds << QByteArray(reservedHeaderTailLength, '\00');
}

void RevisionStoreFileHeader::deserialize(QDataStream &ds) {
  // if byte order is big endian, change to little endian
  if (ds.byteOrder() == QDataStream::BigEndian) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  if (ds.device()->bytesAvailable() < 0x400) {
    qFatal("File size insufficient to be OneNote file.");
  }

  ds >> guidFileType;
  ds >> guidFile;
  ds >> guidLegacyFileVersion;
  ds >> guidFileFormat;
  ds >> ffvLastWriterVersion;
  ds >> ffvOldestWriterVersion;
  ds >> ffvNewestWriterVersion;
  ds >> ffvOldestReader;
  ds >> fcrLegacyFreeChunkList;
  ds >> fcrLegacyTransactionLog;
  ds >> cTransactionsInLog;
  ds >> cbLegacyExpectedFileLength;
  ds >> rgbPlaceholder;
  ds >> fcrLegacyFileNodeListRoot;
  ds >> cbLegacyFreeSpaceInFreeChunkList;
  ds >> fNeedsDefrag;
  ds >> fRepairedFile;
  ds >> fNeedsGarbageCollect;
  ds >> fHasNoEmbeddedFileObjects;
  ds >> guidAncestor;
  ds >> crcName;
  ds >> fcrHashedChunkList;
  ds >> fcrTransactionLog;
  ds >> fcrFileNodeListRoot;
  ds >> fcrFreeChunkList;
  ds >> cbExpectedFileLength;
  ds >> cbFreeSpaceInFreeChunkList;
  ds >> guidFileVersion;
  ds >> nFileVersionGeneration;
  ds >> guidDenyReadFileVersion;
  ds >> grfDebugLogFlags;
  ds >> fcrDebugLog;
  ds >> fcrAllocVerificationFreeChunkList;
  ds >> bnCreated;
  ds >> bnLastWroteToThisFile;
  ds >> bnOldestWritten;
  ds >> bnNewestWritten;
  ds.skipRawData(reservedHeaderTailLength);
}

void RevisionStoreFileHeader::toDebugString(QDebug &dbg) const {

  QDebugStateSaver saver(dbg);
  dbg.setAutoInsertSpaces(false);
  dbg.noquote();

  dbg << "=========================================================\n"
      << " MSON Header:\n"
      << " ------------\n";

  dbg << " guidFileType:                      " << guidFileType
      << (isGuidFileTypeValid() ? "" : " INVALID")
      << (isGuidFileTypeIgnored() ? " ignored" : "") << "\n";
  dbg << " guidFile:                          " << guidFile
      << (isGuidFileValid() ? "" : " INVALID")
      << (isGuidFileIgnored() ? " ignored" : "") << "\n";
  dbg << " guidLegacyFileVersion:             " << guidLegacyFileVersion
      << (isFNeedsGarbageCollectValid() ? "" : " INVALID")
      << (isFNeedsGarbageCollectIgnored() ? " ignored" : "") << "\n";
  dbg << " guidFileFormat:                    " << guidFileFormat
      << (isGuidFileFormatValid() ? "" : " INVALID")
      << (isGuidFileFormatIgnored() ? " ignored" : "") << "\n";
  dbg << " ffvLastWriterVersion:              " << ffvLastWriterVersion
      << (isFfvLastWriterVersionValid() ? "" : " INVALID")
      << (isFfvLastWriterVersionIgnored() ? " ignored" : "") << "\n";
  dbg << " ffvOldestWriterVersion:            " << ffvOldestWriterVersion
      << (isFfvOldestWriterVersionValid() ? "" : " INVALID")
      << (isFfvOldestWriterVersionIgnored() ? " ignored" : "") << "\n";
  dbg << " ffvNewestWriterVersion:            " << ffvNewestWriterVersion
      << (isFfvNewestWriterVersionValid() ? "" : " INVALID")
      << (isFfvNewestWriterVersionIgnored() ? " ignored" : "") << "\n";
  dbg << " ffvOldestReader:                   " << ffvOldestReader
      << (isFfvOldestReaderValid() ? "" : " INVALID")
      << (isFfvOldestReaderIgnored() ? " ignored" : "") << "\n";
  dbg << " fcrLegacyFreeChunkList:            " << fcrLegacyFreeChunkList
      << (isFcrLegacyFreeChunkListValid() ? "" : " INVALID")
      << (isFcrLegacyFreeChunkListIgnored() ? " ignored" : "") << "\n";
  dbg << " fcrLegacyTransactionLog:           " << fcrLegacyTransactionLog
      << (isFcrLegacyTransactionLogValid() ? "" : " INVALID")
      << (isFcrLegacyTransactionLogIgnored() ? " ignored" : "") << "\n";
  dbg << " cTransactionsInLog:                " << cTransactionsInLog
      << (isCTransactionsInLogValid() ? "" : " INVALID")
      << (isCTransactionsInLogIgnored() ? " ignored" : "") << "\n";
  dbg << " cbLegacyExpectedFileLength:        " << cbLegacyExpectedFileLength
      << (isCbLegacyExpectedFileLengthValid() ? "" : " INVALID")
      << (isCbLegacyExpectedFileLengthIgnored() ? " ignored" : "") << "\n";
  dbg << " rgbPlaceholder:                    " << rgbPlaceholder
      << (isRgbPlaceholderValid() ? "" : " INVALID")
      << (isRgbPlaceholderIgnored() ? " ignored" : "") << "\n";
  dbg << " fcrLegacyFileNodeListRoot:         " << fcrLegacyFileNodeListRoot
      << (isFcrLegacyFileNodeListRootValid() ? "" : " INVALID")
      << (isFcrLegacyFileNodeListRootIgnored() ? " ignored" : "") << "\n";
  dbg << " cbLegacyFreeSpaceInFreeChunkList:  "
      << cbLegacyFreeSpaceInFreeChunkList
      << (isCbLegacyFreeSpaceInFreeChunkListValid() ? "" : " INVALID")
      << (isCbLegacyFreeSpaceInFreeChunkListIgnored() ? " ignored" : "")
      << "\n";
  dbg << " fNeedsDefrag:                      " << fNeedsDefrag
      << (isFNeedsDefragValid() ? "" : " INVALID")
      << (isFNeedsDefragIgnored() ? " ignored" : "") << "\n";
  dbg << " fRepairedFile:                     " << fRepairedFile
      << (isFRepairedFileValid() ? "" : " INVALID")
      << (isFRepairedFileIgnored() ? " ignored" : "") << "\n";
  dbg << " fNeedsGarbageCollect:              " << fNeedsGarbageCollect
      << (isFNeedsGarbageCollectValid() ? "" : " INVALID")
      << (isFNeedsGarbageCollectIgnored() ? " ignored" : "") << "\n";
  dbg << " fHasNoEmbeddedFileObjects:         " << fHasNoEmbeddedFileObjects
      << (isFHasNoEmbeddedFileObjectsValid() ? "" : " INVALID")
      << (isFHasNoEmbeddedFileObjectsIgnored() ? " ignored" : "") << "\n";
  dbg << " guidAncestor:                      " << guidAncestor
      << (isGuidAncestorValid() ? "" : " INVALID")
      << (isGuidAncestorIgnored() ? " ignored" : "") << "\n";
  dbg << " crcName:                           " << crcName
      << (isCrcNameValid() ? "" : " INVALID")
      << (isCrcNameIgnored() ? " ignored" : "") << "\n";
  dbg << " fcrHashedChunkList:                " << fcrHashedChunkList
      << (isFcrHashedChunkListValid() ? "" : " INVALID")
      << (isFcrHashedChunkListIgnored() ? " ignored" : "") << "\n";
  dbg << " fcrTransactionLog:                 " << fcrTransactionLog
      << (isFcrTransactionLogValid() ? "" : " INVALID")
      << (isFcrTransactionLogIgnored() ? " ignored" : "")
      << (fcrTransactionLog.is_fcrNil() ? " FCRNIL" : "")
      << (fcrTransactionLog.is_fcrZero() ? " FCRZERO" : "") << "\n";
  dbg << " fcrFileNodeListRoot:               " << fcrFileNodeListRoot
      << (isFcrFileNodeListRootValid() ? "" : " INVALID")
      << (isFcrFileNodeListRootIgnored() ? " ignored" : "") << "\n";
  dbg << " fcrFreeChunkList:                  " << fcrFreeChunkList
      << (isFcrFreeChunkListValid() ? "" : " INVALID")
      << (isFcrFreeChunkListIgnored() ? " ignored" : "") << "\n";
  dbg << " cbExpectedFileLength:              "
      << qStringHex(cbExpectedFileLength, sizeof(cbExpectedFileLength) * 2)
      << (isCbExpectedFileLengthValid() ? "" : " INVALID")
      << (isCbExpectedFileLengthIgnored() ? " ignored" : "") << "\n";
  dbg << " cbFreeSpaceInFreeChunkList:        " << cbFreeSpaceInFreeChunkList
      << (isCbFreeSpaceInFreeChunkListValid() ? "" : " INVALID")
      << (isCbFreeSpaceInFreeChunkListIgnored() ? " ignored" : "") << "\n";
  dbg << " guidFileVersion:                   " << guidFileVersion
      << (isGuidFileVersionValid() ? "" : " INVALID")
      << (isGuidFileVersionIgnored() ? " ignored" : "") << "\n";
  dbg << " nFileVersionGeneration:            " << nFileVersionGeneration
      << (isNFileVersionGenerationValid() ? "" : " INVALID")
      << (isNFileVersionGenerationIgnored() ? " ignored" : "") << "\n";
  dbg << " guidDenyReadFileVersion:           " << guidDenyReadFileVersion
      << (isGuidDenyReadFileVersionValid() ? "" : " INVALID")
      << (isGuidDenyReadFileVersionIgnored() ? " ignored" : "") << "\n";
  dbg << " grfDebugLogFlags:                  " << grfDebugLogFlags
      << (isGrfDebugLogFlagsValid() ? "" : " INVALID")
      << (isGrfDebugLogFlagsIgnored() ? " ignored" : "") << "\n";
  dbg << " fcrDebugLog:                       " << fcrDebugLog
      << (isFcrDebugLogValid() ? "" : " INVALID")
      << (isFcrDebugLogIgnored() ? " ignored" : "") << "\n";
  dbg << " fcrAllocVerificationFreeChunkList: "
      << fcrAllocVerificationFreeChunkList
      << (isFcrAllocVerificationFreeChunkListValid() ? "" : " INVALID")
      << (isFcrAllocVerificationFreeChunkListIgnored() ? " ignored" : "")
      << "\n";
  dbg << " bnCreated:                         "
      << qStringHex(bnCreated, sizeof(bnCreated) * 2)
      << (isBnCreatedValid() ? "" : " INVALID")
      << (isBnCreatedIgnored() ? " ignored" : "") << "\n";
  dbg << " bnLastWroteToThisFile:             "
      << qStringHex(bnLastWroteToThisFile, sizeof(bnLastWroteToThisFile) * 2)
      << (isBnLastWroteToThisFileValid() ? "" : " INVALID")
      << (isBnLastWroteToThisFileIgnored() ? " ignored" : "") << "\n";
  dbg << " bnOldestWritten:                   "
      << qStringHex(bnOldestWritten, sizeof(bnOldestWritten) * 2)
      << (isBnOldestWrittenValid() ? "" : " INVALID")
      << (isBnOldestWrittenIgnored() ? " ignored" : "") << "\n";
  dbg << " bnNewestWritten:                   "
      << qStringHex(bnNewestWritten, sizeof(bnNewestWritten) * 2)
      << (isBnNewestWrittenValid() ? "" : " INVALID")
      << (isBnNewestWrittenIgnored() ? " ignored" : "") << "\n";
  dbg << " reservedHeaderTailLength:          " << reservedHeaderTailLength
      << (isReservedHeaderTailValid() ? "" : " INVALID")
      << (isReservedHeaderTailIgnored() ? " ignored" : "") << "\n";
  dbg << "++++++++++++++++++RevisionStoreFileHeader+++++++++++++++++++++++\n\n";
}

QUuid RevisionStoreFileHeader::getGuidFileType() const { return guidFileType; }

void RevisionStoreFileHeader::setGuidFileType(const QUuid &value) { guidFileType = value; }

/**
 * @brief RevisionStoreFileHeader::isGuidFileTypeValid
 * @return
 *
 * GuidFile is only valid if it contains
 * {7B5C52E4-D88C-4DA7-AEB1-5378D02996D3} for .one file format, or
 * {43FF2FA1-EFD9-4C76-9EE2-10EA5722765F} for .onetoc2 file format
 */
bool RevisionStoreFileHeader::isGuidFileTypeValid() const {
  return guidFileType == v_guidFileType_One ||
         guidFileType == v_guidFileType_OneToc2;
}

bool RevisionStoreFileHeader::isGuidFileTypeIgnored() { return false; }

QUuid RevisionStoreFileHeader::getGuidFile() const { return guidFile; }

void RevisionStoreFileHeader::setGuidFile(const QUuid &value) { guidFile = value; }

bool RevisionStoreFileHeader::isGuidFileValid() const { return guidFile != v_guidZero; }

bool RevisionStoreFileHeader::isGuidFileIgnored() { return false; }

QUuid RevisionStoreFileHeader::getGuidLegacyFileVersion() const {
  return guidLegacyFileVersion;
}

void RevisionStoreFileHeader::setGuidLegacyFileVersion(const QUuid &value) {
  guidLegacyFileVersion = value;
}

/**
 * @brief RevisionStoreFileHeader::isGuidLegacyFileVersionValid
 * @return
 *
 * guidLegacyFileVersion must be {00000000-0000-0000-0000-000000000000}"
 */
bool RevisionStoreFileHeader::isGuidLegacyFileVersionValid() const {
  return guidLegacyFileVersion == v_guidZero;
}

bool RevisionStoreFileHeader::isGuidLegacyFileVersionIgnored() { return true; }

QUuid RevisionStoreFileHeader::getGuidFileFormat() const { return guidFileFormat; }

void RevisionStoreFileHeader::setGuidFileFormat(const QUuid &value) {
  guidFileFormat = value;
}

/**
 * @brief RevisionStoreFileHeader::isGuidFileFormatValid
 * @return
 *
 * guidFileFormat must be {109ADD3F-911B-49F5-A5D0-1791EDC8AED8}
 */
bool RevisionStoreFileHeader::isGuidFileFormatValid() const {
  return guidFileFormat == v_guidFileFormat;
}

bool RevisionStoreFileHeader::isGuidFileFormatIgnored() { return false; }

quint32 RevisionStoreFileHeader::getFfvLastWriterVersion() const {
  return ffvLastWriterVersion;
}

void RevisionStoreFileHeader::setFfvLastWriterVersion(quint32 value) {
  ffvLastWriterVersion = value;
}

/**
 * @brief RevisionStoreFileHeader::isFfvLastWriterVersionValid
 * @return
 *
 * must be 0x0000002A to indicate .one file format, or
 * must be 0x0000001B to indicate .onetoc2 file format
 */
bool RevisionStoreFileHeader::isFfvLastWriterVersionValid() const {
  return ffvLastWriterVersion == 0x0000002A ||
         ffvLastWriterVersion == 0x0000001B;
}

bool RevisionStoreFileHeader::isFfvLastWriterVersionIgnored() { return false; }

quint32 RevisionStoreFileHeader::getFfvNewestWriterVersion() const {
  return ffvNewestWriterVersion;
}

void RevisionStoreFileHeader::setFfvNewestWriterVersion(quint32 value) {
  ffvNewestWriterVersion = value;
}
/**
 * @brief RevisionStoreFileHeader::isFfvNewestWriterVersionValid
 * @return
 *
 * must be 0x0000002A to indicate .one file format, or
 * must be 0x0000001B to indicate .onetoc2 file format
 */
bool RevisionStoreFileHeader::isFfvNewestWriterVersionValid() const {
  return ffvLastWriterVersion == 0x0000002A ||
         ffvLastWriterVersion == 0x0000001B;
}

bool RevisionStoreFileHeader::isFfvNewestWriterVersionIgnored() { return false; }

quint32 RevisionStoreFileHeader::getFfvOldestWriterVersion() const {
  return ffvOldestWriterVersion;
}

void RevisionStoreFileHeader::setFfvOldestWriterVersion(quint32 value) {
  ffvOldestWriterVersion = value;
}

/**
 * @brief RevisionStoreFileHeader::isFfvOldestWriterVersionValid
 * @return
 * must be 0x0000002A to indicate .one file format, or
 * must be 0x0000001B to indicate .onetoc2 file format
 */
bool RevisionStoreFileHeader::isFfvOldestWriterVersionValid() const {
  return ffvLastWriterVersion == 0x0000002A ||
         ffvLastWriterVersion == 0x0000001B;
}

bool RevisionStoreFileHeader::isFfvOldestWriterVersionIgnored() { return false; }

quint32 RevisionStoreFileHeader::getFfvOldestReader() const { return ffvOldestReader; }

void RevisionStoreFileHeader::setFfvOldestReader(quint32 value) { ffvOldestReader = value; }

/**
 * @brief RevisionStoreFileHeader::isFfvOldestReaderValid
 * @return
 * must be 0x0000002A to indicate .one file format, or
 * must be 0x0000001B to indicate .onetoc2 file format
 */
bool RevisionStoreFileHeader::isFfvOldestReaderValid() const {
  return ffvLastWriterVersion == 0x0000002A ||
         ffvLastWriterVersion == 0x0000001B;
}

bool RevisionStoreFileHeader::isFfvOldestReaderIgnored() { return false; }

FileChunkReference32 RevisionStoreFileHeader::getFcrLegacyFreeChunkList() const {
  return fcrLegacyFreeChunkList;
}

void RevisionStoreFileHeader::setFcrLegacyFreeChunkList(const FileChunkReference32 &value) {
  fcrLegacyFreeChunkList = value;
}

/**
 * @brief RevisionStoreFileHeader::isFcrLegacyFreeChunkListValid
 * @return
 *
 * must be fcrZero
 */
bool RevisionStoreFileHeader::isFcrLegacyFreeChunkListValid() const {
  return fcrLegacyFreeChunkList.is_fcrZero();
}

bool RevisionStoreFileHeader::isFcrLegacyFreeChunkListIgnored() const { return false; }

FileChunkReference32 RevisionStoreFileHeader::getFcrLegacyTransactionLog() const {
  return fcrLegacyTransactionLog;
}

void RevisionStoreFileHeader::setFcrLegacyTransactionLog(const FileChunkReference32 &value) {
  fcrLegacyTransactionLog = value;
}

/**
 * @brief RevisionStoreFileHeader::isFcrLegacyTransactionLogValid
 * @return
 *
 * must be fcrNil
 */
bool RevisionStoreFileHeader::isFcrLegacyTransactionLogValid() const {
  return fcrLegacyTransactionLog.is_fcrNil();
}

bool RevisionStoreFileHeader::isFcrLegacyTransactionLogIgnored() const { return false; }

quint32 RevisionStoreFileHeader::getCTransactionsInLog() const { return cTransactionsInLog; }

/**
 * @brief RevisionStoreFileHeader::setCTransactionsInLog
 * @param value
 *
 * \todo setting this value forces a new UUID for guidFileVersion as well
 */
void RevisionStoreFileHeader::setCTransactionsInLog(quint32 value) {
  cTransactionsInLog = value;
}

void RevisionStoreFileHeader::changeTransactionsInLog(quint32 value) {
  cTransactionsInLog = value;
  nextGuidFileVersion();
}

/**
 * @brief RevisionStoreFileHeader::isCTransactionsInLogValid
 * @return
 *
 * must not be zero
 */
bool RevisionStoreFileHeader::isCTransactionsInLogValid() const {
  return cTransactionsInLog != 0;
}

bool RevisionStoreFileHeader::isCTransactionsInLogIgnored() const { return false; }

quint32 RevisionStoreFileHeader::getCbLegacyExpectedFileLength() const {
  return cbLegacyExpectedFileLength;
}

void RevisionStoreFileHeader::setCbLegacyExpectedFileLength(quint32 value) {
  cbLegacyExpectedFileLength = value;
}

/**
 * @brief RevisionStoreFileHeader::isCbLegacyExpectedFileLengthValid
 * @return
 *
 * must be zero
 */

bool RevisionStoreFileHeader::isCbLegacyExpectedFileLengthValid() const {
  return cbLegacyExpectedFileLength == 0;
}

bool RevisionStoreFileHeader::isCbLegacyExpectedFileLengthIgnored() const { return true; }

quint64 RevisionStoreFileHeader::getRgbPlaceholder() const { return rgbPlaceholder; }

void RevisionStoreFileHeader::setRgbPlaceholder(quint64 value) { rgbPlaceholder = value; }

/**
 * @brief RevisionStoreFileHeader::isRgbPlaceholderValid
 * @return
 *
 * must be zero
 */
bool RevisionStoreFileHeader::isRgbPlaceholderValid() const { return rgbPlaceholder == 0; }

bool RevisionStoreFileHeader::isRgbPlaceholderIgnored() const { return true; }

FileChunkReference32 RevisionStoreFileHeader::getFcrLegacyFileNodeListRoot() const {
  return fcrLegacyFileNodeListRoot;
}

void RevisionStoreFileHeader::setFcrLegacyFileNodeListRoot(
    const FileChunkReference32 &value) {
  fcrLegacyFileNodeListRoot = value;
}

bool RevisionStoreFileHeader::isFcrLegacyFileNodeListRootValid() const {
  return fcrLegacyFileNodeListRoot.is_fcrNil();
}

bool RevisionStoreFileHeader::isFcrLegacyFileNodeListRootIgnored() const { return false; }

quint32 RevisionStoreFileHeader::getCbLegacyFreeSpaceInFreeChunkList() const {
  return cbLegacyFreeSpaceInFreeChunkList;
}

void RevisionStoreFileHeader::setCbLegacyFreeSpaceInFreeChunkList(quint32 value) {
  cbLegacyFreeSpaceInFreeChunkList = value;
}

bool RevisionStoreFileHeader::isCbLegacyFreeSpaceInFreeChunkListValid() const {
  return cbLegacyExpectedFileLength == 0;
}

bool RevisionStoreFileHeader::isCbLegacyFreeSpaceInFreeChunkListIgnored() const {
  return true;
}

uchar RevisionStoreFileHeader::getFNeedsDefrag() const { return fNeedsDefrag; }

void RevisionStoreFileHeader::setFNeedsDefrag(quint8 value) { fNeedsDefrag = value; }

/**
 * @brief RevisionStoreFileHeader::isFNeedsDefragValid
 *
 * not specified
 * @return
 */
bool RevisionStoreFileHeader::isFNeedsDefragValid() const { return true; }

bool RevisionStoreFileHeader::isFNeedsDefragIgnored() const { return true; }

quint8 RevisionStoreFileHeader::getFRepairedFile() const { return fRepairedFile; }

void RevisionStoreFileHeader::setFRepairedFile(quint8 value) { fRepairedFile = value; }

/**
 * @brief RevisionStoreFileHeader::isFRepairedFileValid
 *
 * not specified
 * @return
 */
bool RevisionStoreFileHeader::isFRepairedFileValid() const { return true; }

bool RevisionStoreFileHeader::isFRepairedFileIgnored() const { return true; }

quint8 RevisionStoreFileHeader::getFNeedsGarbageCollect() const {
  return fNeedsGarbageCollect;
}

void RevisionStoreFileHeader::setFNeedsGarbageCollect(quint8 value) {
  fNeedsGarbageCollect = value;
}

/**
 * @brief RevisionStoreFileHeader::isFNeedsGarbageCollectValid
 *
 * not specified
 * @return
 */
bool RevisionStoreFileHeader::isFNeedsGarbageCollectValid() const { return true; }

bool RevisionStoreFileHeader::isFNeedsGarbageCollectIgnored() const { return true; }

quint8 RevisionStoreFileHeader::getFHasNoEmbeddedFileObjects() const {
  return fHasNoEmbeddedFileObjects;
}

void RevisionStoreFileHeader::setFHasNoEmbeddedFileObjects(quint8 value) {
  fHasNoEmbeddedFileObjects = value;
}

bool RevisionStoreFileHeader::isFHasNoEmbeddedFileObjectsValid() const {
  return fHasNoEmbeddedFileObjects == 0;
}

bool RevisionStoreFileHeader::isFHasNoEmbeddedFileObjectsIgnored() const { return true; }

QUuid RevisionStoreFileHeader::getGuidAncestor() const { return guidAncestor; }

void RevisionStoreFileHeader::setGuidAncestor(const QUuid &value) { guidAncestor = value; }

/**
  \todo Check if Header.guidFile exists
 * @brief RevisionStoreFileHeader::isGuidAncestorValid
 *
 * guidAncestor should mark the Header.guidFile location of the table of
 contents file
 *
 * @return
 */
bool RevisionStoreFileHeader::isGuidAncestorValid() const { return true; }

bool RevisionStoreFileHeader::isGuidAncestorIgnored() const { return false; }

/**
 * @brief RevisionStoreFileHeader::guidAncestorLocationInCWD
 * \todo
 * Deduct if Header.guidFile is in current directory, or whether it is in the
 * parent directory. If GUID is zero, no table of contents file present
 * @return
 */
bool RevisionStoreFileHeader::guidAncestorLocationInCD() const { return false; }
bool RevisionStoreFileHeader::guidAncestorLocationInPD() const { return false; }

bool RevisionStoreFileHeader::guidAncestorLocationNotPresent() const {
  return guidAncestor == v_guidZero;
}

quint32 RevisionStoreFileHeader::getCrcName() const { return crcName; }

void RevisionStoreFileHeader::setCrcName(quint32 value) { crcName = value; }

bool RevisionStoreFileHeader::isCrcNameValid() const { return true; }

bool RevisionStoreFileHeader::isCrcNameIgnored() const { return false; }

FileChunkReference64x32 &RevisionStoreFileHeader::getFcrHashedChunkList() {
  return fcrHashedChunkList;
}

void RevisionStoreFileHeader::setFcrHashedChunkList(const FileChunkReference64x32 &value) {
  fcrHashedChunkList = value;
}

bool RevisionStoreFileHeader::isFcrHashedChunkListValid() const { return true; }

bool RevisionStoreFileHeader::isFcrHashedChunkListIgnored() const { return false; }

/**
 * @brief RevisionStoreFileHeader::fcrHashedChunkList_exits
 * @return
 *
 * if fcrHashedChunkList is fcrNil or fcrZero, then HashedChunkLink does not
 * exist.
 */
bool RevisionStoreFileHeader::fcrHashedChunkList_exits() const {
  return !(fcrHashedChunkList.is_fcrNil() || fcrHashedChunkList.is_fcrZero());
}

FileChunkReference64x32 &RevisionStoreFileHeader::getFcrTransactionLog() {
  return fcrTransactionLog;
}

void RevisionStoreFileHeader::setFcrTransactionLog(const FileChunkReference64x32 &value) {

  fcrTransactionLog = value;
}

/**
 * @brief RevisionStoreFileHeader::isFcrTransactionLogValid
 * @return
 *
 * must not be fcrNil and fcrZero
 */
bool RevisionStoreFileHeader::isFcrTransactionLogValid() const {
  return !fcrTransactionLog.is_fcrNil() && !fcrTransactionLog.is_fcrZero();
}

bool RevisionStoreFileHeader::isFcrTransactionLogIgnored() const { return false; }

FileChunkReference64x32 &RevisionStoreFileHeader::getFcrFileNodeListRoot() {
  return fcrFileNodeListRoot;
}

void RevisionStoreFileHeader::setFcrFileNodeListRoot(const FileChunkReference64x32 &value) {

  fcrFileNodeListRoot = value;
}

/**
 * @brief RevisionStoreFileHeader::isFcrFileNodeListRootValid
 * @return
 *
 * must not be fcrNil and fcrZero
 */
bool RevisionStoreFileHeader::isFcrFileNodeListRootValid() const {
  return !fcrFileNodeListRoot.is_fcrNil() && !fcrFileNodeListRoot.is_fcrZero();
}

bool RevisionStoreFileHeader::isFcrFileNodeListRootIgnored() const { return false; }

FileChunkReference64x32 &RevisionStoreFileHeader::getFcrFreeChunkList() {
  return fcrFreeChunkList;
}

void RevisionStoreFileHeader::setFcrFreeChunkList(const FileChunkReference64x32 &value) {
  fcrFreeChunkList = value;
}

/**
 * @brief RevisionStoreFileHeader::isFcrFreeChunkListValid
 * @return
 *
 * unspecified validity
 */
bool RevisionStoreFileHeader::isFcrFreeChunkListValid() const { return true; }

bool RevisionStoreFileHeader::isFcrFreeChunkListIgnored() const { return false; }

/**
 * @brief RevisionStoreFileHeader::fcrFreeChunkList_exits
 * @return
 *
 * If fcrFreeChunkList is zero, then FreeChunkList does not exist
 */
bool RevisionStoreFileHeader::fcrFreeChunkList_exits() const {
  return !(fcrFreeChunkList.is_fcrNil() || fcrFreeChunkList.is_fcrZero());
}

quint64 RevisionStoreFileHeader::getCbExpectedFileLength() const {
  return cbExpectedFileLength;
}

void RevisionStoreFileHeader::setCbExpectedFileLength(quint64 value) {
  cbExpectedFileLength = value;
}

bool RevisionStoreFileHeader::isCbExpectedFileLengthValid() const { return true; }

bool RevisionStoreFileHeader::isCbExpectedFileLengthIgnored() const { return false; }

quint64 RevisionStoreFileHeader::getCbFreeSpaceInFreeChunkList() const {
  return cbFreeSpaceInFreeChunkList;
}

void RevisionStoreFileHeader::setCbFreeSpaceInFreeChunkList(quint64 value) {
  cbFreeSpaceInFreeChunkList = value;
}

/**
 * @brief RevisionStoreFileHeader::isCbFreeSpaceInFreeChunkListValid
 * @return
 *
 * \todo unspecified validity
 *
 * OneNote 2010 sometimes writes invalid value here
 */
bool RevisionStoreFileHeader::isCbFreeSpaceInFreeChunkListValid() const { return true; }

bool RevisionStoreFileHeader::isCbFreeSpaceInFreeChunkListIgnored() const { return false; }

QUuid RevisionStoreFileHeader::getGuidFileVersion() const { return guidFileVersion; }

void RevisionStoreFileHeader::setGuidFileVersion(const QUuid &value) {
  guidFileVersion = value;
}

/**
 * @brief RevisionStoreFileHeader::nextGuidFileVersion
 *
 * advances guidFileVersion, and increments nFileVersionGeneration
 */
void RevisionStoreFileHeader::nextGuidFileVersion() {
  guidFileVersion = QUuid::createUuid();

  nFileVersionGeneration++;
}

bool RevisionStoreFileHeader::isGuidFileVersionValid() const {
  return guidFileVersion != v_guidZero;
}

bool RevisionStoreFileHeader::isGuidFileVersionIgnored() const { return false; }

quint64 RevisionStoreFileHeader::getNFileVersionGeneration() const {
  return nFileVersionGeneration;
}

/**
 * @brief RevisionStoreFileHeader::setNFileVersionGeneration
 * @param value
 *
 * must be incremented with change of setGuidFileVersion
 */
void RevisionStoreFileHeader::setNFileVersionGeneration(quint64 value) {
  nFileVersionGeneration = value;
}

/**
 * @brief RevisionStoreFileHeader::isNFileVersionGenerationValid
 * @return
 *
 * unspecified validity
 */
bool RevisionStoreFileHeader::isNFileVersionGenerationValid() const { return true; }

bool RevisionStoreFileHeader::isNFileVersionGenerationIgnored() const { return false; }

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

void RevisionStoreFileHeader::changeGuidDenyReadFileVersion() {
  guidDenyReadFileVersion = QUuid::createUuid();
}

bool RevisionStoreFileHeader::isGuidDenyReadFileVersionValid() const {
  return guidDenyReadFileVersion != v_guidZero;
}

bool RevisionStoreFileHeader::isGuidDenyReadFileVersionIgnored() const { return false; }

quint32 RevisionStoreFileHeader::getGrfDebugLogFlags() const { return grfDebugLogFlags; }

void RevisionStoreFileHeader::setGrfDebugLogFlags(quint32 value) {
  grfDebugLogFlags = value;
}

bool RevisionStoreFileHeader::isGrfDebugLogFlagsValid() const {
  return grfDebugLogFlags == 0;
}

bool RevisionStoreFileHeader::isGrfDebugLogFlagsIgnored() const { return true; }

FileChunkReference64x32 &RevisionStoreFileHeader::getFcrDebugLog() { return fcrDebugLog; }

void RevisionStoreFileHeader::setFcrDebugLog(const FileChunkReference64x32 &value) {
  fcrDebugLog = value;
}

bool RevisionStoreFileHeader::isFcrDebugLogValid() const { return fcrDebugLog.is_fcrZero(); }

bool RevisionStoreFileHeader::isFcrDebugLogIgnored() const { return true; }

FileChunkReference64x32
RevisionStoreFileHeader::getFcrAllocVerificationFreeChunkList() const {
  return fcrAllocVerificationFreeChunkList;
}

void RevisionStoreFileHeader::setFcrAllocVerificationFreeChunkList(
    const FileChunkReference64x32 &value) {
  fcrAllocVerificationFreeChunkList = value;
}

bool RevisionStoreFileHeader::isFcrAllocVerificationFreeChunkListValid() const {
  return fcrAllocVerificationFreeChunkList.is_fcrZero();
}

bool RevisionStoreFileHeader::isFcrAllocVerificationFreeChunkListIgnored() const {
  return true;
}

quint32 RevisionStoreFileHeader::getBnCreated() const { return bnCreated; }

void RevisionStoreFileHeader::setBnCreated(quint32 value) { bnCreated = value; }

/**
 * @brief RevisionStoreFileHeader::isBnCreatedValid
 * @return
 *
 * unspecified validity
 */
bool RevisionStoreFileHeader::isBnCreatedValid() const { return true; }

bool RevisionStoreFileHeader::isBnCreatedIgnored() const { return true; }

quint32 RevisionStoreFileHeader::getBnLastWroteToThisFile() const {
  return bnLastWroteToThisFile;
}

void RevisionStoreFileHeader::setBnLastWroteToThisFile(quint32 value) {
  bnLastWroteToThisFile = value;
}

/**
 * @brief RevisionStoreFileHeader::isBnLastWroteToThisFileValid
 * @return
 *
 * unspecified validity
 */
bool RevisionStoreFileHeader::isBnLastWroteToThisFileValid() const { return true; }

bool RevisionStoreFileHeader::isBnLastWroteToThisFileIgnored() const { return true; }

quint32 RevisionStoreFileHeader::getBnOldestWritten() const { return bnOldestWritten; }

void RevisionStoreFileHeader::setBnOldestWritten(quint32 value) { bnOldestWritten = value; }

/**
 * @brief RevisionStoreFileHeader::isBnOldestWrittenValid
 * @return
 *
 * unspecified validity
 */
bool RevisionStoreFileHeader::isBnOldestWrittenValid() const { return true; }

bool RevisionStoreFileHeader::isBnOldestWrittenIgnored() const { return true; }

quint32 RevisionStoreFileHeader::getBnNewestWritten() const { return bnNewestWritten; }

void RevisionStoreFileHeader::setBnNewestWritten(quint32 value) { bnNewestWritten = value; }

/**
 * @brief RevisionStoreFileHeader::isBnNewestWrittenValid
 * @return
 *
 * unspecified validity
 */
bool RevisionStoreFileHeader::isBnNewestWrittenValid() const { return true; }

bool RevisionStoreFileHeader::isBnNewestWrittenIgnored() const { return true; }

quint32 RevisionStoreFileHeader::getReservedHeaderTailLength() const {
  return reservedHeaderTailLength;
}

void RevisionStoreFileHeader::setReservedHeaderTailLength(const quint32 &value) {
  reservedHeaderTailLength = value;
}

/**
 * @brief RevisionStoreFileHeader::isReservedHeaderTailValid
 * @return true if reservedHeaderTail is all '\0'
 *
 * Is actually not checked
 */
bool RevisionStoreFileHeader::isReservedHeaderTailValid() const { return true; }

bool RevisionStoreFileHeader::isReservedHeaderTailIgnored() const { return true; }

} // namespace MSONcommon
