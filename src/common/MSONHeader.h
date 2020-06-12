#ifndef MSONHEADER_H
#define MSONHEADER_H



#include <QtCore/qglobal.h>
#include <QUuid>
#include <QByteArray>
#include <QString>

#include "FileChunkReference.h"



/**
* @class MSONHeader
*
* @brief serialzies and deserializes an MSON file stream
*
* MSON Header class which (de)serialzies an input stream
*/
class MSONHeader
{
private:

    QUuid guidFileType;
    QUuid guidFile;
    QUuid guidLegacyFileVersion;
    QUuid guidFileFormat;
    uint32_t  ffvLastWriterVersion; // ffvLastCodeThatWroteToThisFile  // long?
    uint32_t  ffvOldestWriterVersion; // ffvNewestCodeThatHasWrittenToThisFile
    uint32_t  ffvNewestWriterVersion; // ffvOldestCodeThatHasWrittenToThisFile
    uint32_t  ffvOldestReader; // ffvOldestCodeThatMayReadThisFile
    FileChunkReference32 fcrLegacyFreeChunkList;
    FileChunkReference32 fcrLegacyTransactionLog;
    uint32_t  cTransactionsInLog;
    uint32_t  cbLegacyExpectedFileLength;
    uint64_t  rgbPlaceholder;
    FileChunkReference32 fcrLegacyFileNodeListRoot;
    uint32_t  cbLegacyFreeSpaceInFreeChunkList;
    uint8_t fNeedsDefrag;
    uint8_t fRepairedFile;
    uint8_t fNeedsGarbageCollect;
    uint8_t fHasNoEmbeddedFileObjects;
    QUuid guidAncestor;
    uint32_t  crcName;
    FileChunkReference64x32 fcrHashedChunkList;
    FileChunkReference64x32 fcrTransactionLog;
    FileChunkReference64x32 fcrFileNodeListRoot;
    FileChunkReference64x32 fcrFreeChunkList;
    uint64_t  cbExpectedFileLength;
    uint64_t  cbFreeSpaceInFreeChunkList;
    QUuid guidFileVersion;
    uint64_t  nFileVersionGeneration;
    QUuid guidDenyReadFileVersion;
    uint32_t  grfDebugLogFlags;
    FileChunkReference64x32 fcrDebugLog;
    FileChunkReference64x32 fcrAllocVerificationFreeChunkList;
    uint32_t  bnCreated;
    uint32_t  bnLastWroteToThisFile;
    uint32_t  bnOldestWritten;
    uint32_t  bnNewestWritten;
    QByteArray reservedHeaderTail;



    static constexpr const char* v_guidFileType_One = "{7B5C52E4-D88C-4DA7-AEB1-5378D02996D3}";
    static constexpr const char* v_guidFileType_OneToc2 = "{43FF2FA1-EFD9-4C76-9EE2-10EA5722765F}";
    static constexpr const char* v_guidFileFormat = "{109ADD3F-911B-49F5-A5D0-1791EDC8AED8}";
    static constexpr const char* v_guidZero = "{00000000-0000-0000-0000-000000000000}";

    static constexpr double def_balance = 0.0;

public:
  MSONHeader();



  QUuid getGuidFileType() const;
  void setGuidFileType(const QUuid &value);
  bool isGuidFileTypeValid() const;
  bool isGuidFileTypeIgnored() const;

  QUuid getGuidFile() const;
  void setGuidFile(const QUuid &value);
  bool isGuidFileValid() const;
  bool isGuidFileIgnored() const;

  QUuid getGuidLegacyFileVersion() const;
  void setGuidLegacyFileVersion(const QUuid &value);
  bool isGuidLegacyFileVersionValid() const;
  bool isGuidLegacyFileVersionIgnored() const;


  QUuid getGuidFileFormat() const;
  void setGuidFileFormat(const QUuid &value);
  bool isGuidFileFormatValid() const;
  bool isGuidFileFormatIgnored() const;

  uint32_t  getFfvLastWriterVersion() const;
  void setFfvLastWriterVersion(uint32_t  value);
  bool isFfvLastWriterVersionValid() const;
  bool isFfvLastWriterVersionIgnored() const;

  uint32_t  getFfvNewestWriterVersion() const;
  void setFfvNewestWriterVersion(uint32_t  value);
  bool isFfvNewestWriterVersionValid() const;
  bool isFfvNewestWriterVersionIgnored() const;

  uint32_t  getFfvOldestWriterVersion() const;
  void setFfvOldestWriterVersion(uint32_t  value);
  bool isFfvOldestWriterVersionValid() const;
  bool isFfvOldestWriterVersionIgnored() const;

  uint32_t  getFfvOldestReader() const;
  void setFfvOldestReader(uint32_t  value);
  bool isFfvOldestReaderValid() const;
  bool isFfvOldestReaderIgnored() const;

  FileChunkReference32 getFcrLegacyFreeChunkList() const;
  void setFcrLegacyFreeChunkList(const FileChunkReference32 &value);
  bool isFcrLegacyFreeChunkListValid() const;
  bool isFcrLegacyFreeChunkListIgnored() const;

  FileChunkReference32 getFcrLegacyTransactionLog() const;
  void setFcrLegacyTransactionLog(const FileChunkReference32 &value);
  bool isFcrLegacyTransactionLogValid() const;
  bool isFcrLegacyTransactionLogIgnored() const;

  uint32_t  getCTransactionsInLog() const;
  void setCTransactionsInLog(uint32_t  value);
  void changeTransactionsInLog(uint32_t  value);
  bool isCTransactionsInLogValid() const;
  bool isCTransactionsInLogIgnored() const;

  uint32_t  getCbLegacyExpectedFileLength() const;
  void setCbLegacyExpectedFileLength(uint32_t  value);
  bool isCbLegacyExpectedFileLengthValid() const;
  bool isCbLegacyExpectedFileLengthIgnored() const;

  uint64_t  getRgbPlaceholder() const;
  void setRgbPlaceholder(uint64_t  value);
  bool isRgbPlaceholderValid() const;
  bool isRgbPlaceholderIgnored() const;

  FileChunkReference32 getFcrLegacyFileNodeListRoot() const;
  void setFcrLegacyFileNodeListRoot(const FileChunkReference32 &value);
  bool isFcrLegacyFileNodeListRootValid() const;
  bool isFcrLegacyFileNodeListRootIgnored() const;

  uint32_t  getCbLegacyFreeSpaceInFreeChunkList() const;
  void setCbLegacyFreeSpaceInFreeChunkList(uint32_t  value);
  bool isCbLegacyFreeSpaceInFreeChunkListValid() const;
  bool isCbLegacyFreeSpaceInFreeChunkListIgnored() const;

  uint8_t getFNeedsDefrag() const;
  void setFNeedsDefrag(uint8_t value);
  bool isFNeedsDefragValid() const;
  bool isFNeedsDefragIgnored() const;

  uint8_t getFRepairedFile() const;
  void setFRepairedFile(uint8_t value);
  bool isFRepairedFileValid() const;
  bool isFRepairedFileIgnored() const;

  uint8_t getFNeedsGarbageCollect() const;
  void setFNeedsGarbageCollect(uint8_t value);
  bool isFNeedsGarbageCollectValid() const;
  bool isFNeedsGarbageCollectIgnored() const;

  uint8_t getFHasNoEmbeddedFileObjects() const;
  void setFHasNoEmbeddedFileObjects(uint8_t value);
  bool isFHasNoEmbeddedFileObjectsValid() const;
  bool isFHasNoEmbeddedFileObjectsIgnored() const;

  QUuid getGuidAncestor() const;
  void setGuidAncestor(const QUuid &value);
  bool isGuidAncestorValid() const;
  bool isGuidAncestorIgnored() const;
  bool guidAncestorLocationInCD() const;
  bool guidAncestorLocationInPD() const;
  bool guidAncestorLocationNotPresent() const;

  uint32_t  getCrcName() const;
  void setCrcName(uint32_t  value);
  bool isCrcNameValid() const;
  bool isCrcNameIgnored() const;

  FileChunkReference64x32 getFcrHashedChunkList() const;
  void setFcrHashedChunkList(const FileChunkReference64x32 &value);
  bool isFcrHashedChunkListValid() const;
  bool isFcrHashedChunkListIgnored() const;
  bool fcrHashedChunkList_exits() const;

  FileChunkReference64x32 getFcrTransactionLog() const;
  void setFcrTransactionLog(const FileChunkReference64x32 &value);
  bool isFcrTransactionLogValid() const;
  bool isFcrTransactionLogIgnored() const;

  FileChunkReference64x32 getFcrFileNodeListRoot() const;
  void setFcrFileNodeListRoot(const FileChunkReference64x32 &value);
  bool isFcrFileNodeListRootValid() const;
  bool isFcrFileNodeListRootIgnored() const;

  FileChunkReference64x32 getFcrFreeChunkList() const;
  void setFcrFreeChunkList(const FileChunkReference64x32 &value);
  bool isFcrFreeChunkListValid() const;
  bool isFcrFreeChunkListIgnored() const;
  bool fcrFreeChunkList_exits() const;

  uint64_t  getCbExpectedFileLength() const;
  void setCbExpectedFileLength(uint64_t  value);
  bool isCbExpectedFileLengthValid() const;
  bool isCbExpectedFileLengthIgnored() const;

  uint64_t  getCbFreeSpaceInFreeChunkList() const;
  void setCbFreeSpaceInFreeChunkList(uint64_t  value);
  bool isCbFreeSpaceInFreeChunkListValid() const;
  bool isCbFreeSpaceInFreeChunkListIgnored() const;

  QUuid getGuidFileVersion() const;
  void setGuidFileVersion(const QUuid &value);
  void nextGuidFileVersion();
  bool isGuidFileVersionValid() const;
  bool isGuidFileVersionIgnored() const;

  uint64_t  getNFileVersionGeneration() const;
  void setNFileVersionGeneration(uint64_t  value);
  bool isNFileVersionGenerationValid() const;
  bool isNFileVersionGenerationIgnored() const;

  QUuid getGuidDenyReadFileVersion() const;
  void setGuidDenyReadFileVersion(const QUuid &value);
  void changeGuidDenyReadFileVersion();
  bool isGuidDenyReadFileVersionValid() const;
  bool isGuidDenyReadFileVersionIgnored() const;

  uint32_t  getGrfDebugLogFlags() const;
  void setGrfDebugLogFlags(uint32_t  value);
  bool isGrfDebugLogFlagsValid() const;
  bool isGrfDebugLogFlagsIgnored() const;

  FileChunkReference64x32 getFcrDebugLog() const;
  void setFcrDebugLog(const FileChunkReference64x32 &value);
  bool isFcrDebugLogValid() const;
  bool isFcrDebugLogIgnored() const;

  FileChunkReference64x32 getFcrAllocVerificationFreeChunkList() const;
  void setFcrAllocVerificationFreeChunkList(const FileChunkReference64x32 &value);
  bool isFcrAllocVerificationFreeChunkListValid() const;
  bool isFcrAllocVerificationFreeChunkListIgnored() const;

  uint32_t  getBnCreated() const;
  void setBnCreated(uint32_t  value);
  bool isBnCreatedValid() const;
  bool isBnCreatedIgnored() const;

  uint32_t  getBnLastWroteToThisFile() const;
  void setBnLastWroteToThisFile(uint32_t  value);
  bool isBnLastWroteToThisFileValid() const;
  bool isBnLastWroteToThisFileIgnored() const;

  uint32_t  getBnOldestWritten() const;
  void setBnOldestWritten(uint32_t  value);
  bool isBnOldestWrittenValid() const;
  bool isBnOldestWrittenIgnored() const;

  uint32_t  getBnNewestWritten() const;
  void setBnNewestWritten(uint32_t  value);
  bool isBnNewestWrittenValid() const;
  bool isBnNewestWrittenIgnored() const;

  QByteArray getReservedHeaderTail() const;
  void setReservedHeaderTail(const QByteArray &value);
  bool isReservedHeaderTailValid() const;
  bool isReservedHeaderTailIgnored() const;

};




#endif // MSONHEADER_H
