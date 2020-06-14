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
    quint32  ffvLastWriterVersion; // ffvLastCodeThatWroteToThisFile  // long?
    quint32  ffvOldestWriterVersion; // ffvNewestCodeThatHasWrittenToThisFile
    quint32  ffvNewestWriterVersion; // ffvOldestCodeThatHasWrittenToThisFile
    quint32  ffvOldestReader; // ffvOldestCodeThatMayReadThisFile
    FileChunkReference32 fcrLegacyFreeChunkList;
    FileChunkReference32 fcrLegacyTransactionLog;
    quint32  cTransactionsInLog;
    quint32  cbLegacyExpectedFileLength;
    quint64  rgbPlaceholder;
    FileChunkReference32 fcrLegacyFileNodeListRoot;
    quint32  cbLegacyFreeSpaceInFreeChunkList;
    quint8 fNeedsDefrag;
    quint8 fRepairedFile;
    quint8 fNeedsGarbageCollect;
    quint8 fHasNoEmbeddedFileObjects;
    QUuid guidAncestor;
    quint32  crcName;
    FileChunkReference64x32 fcrHashedChunkList;
    FileChunkReference64x32 fcrTransactionLog;
    FileChunkReference64x32 fcrFileNodeListRoot;
    FileChunkReference64x32 fcrFreeChunkList;
    quint64  cbExpectedFileLength;
    quint64  cbFreeSpaceInFreeChunkList;
    QUuid guidFileVersion;
    quint64  nFileVersionGeneration;
    QUuid guidDenyReadFileVersion;
    quint32  grfDebugLogFlags;
    FileChunkReference64x32 fcrDebugLog;
    FileChunkReference64x32 fcrAllocVerificationFreeChunkList;
    quint32  bnCreated;
    quint32  bnLastWroteToThisFile;
    quint32  bnOldestWritten;
    quint32  bnNewestWritten;
    QByteArray reservedHeaderTail;





public:
  MSONHeader();

  MSONHeader(QDataStream& ds);


  MSONHeader deserialize(QDataStream& ds);
  void serialize(QDataStream& out) const;



  QUuid getGuidFileType() const;
  void setGuidFileType(const QUuid &value);
  bool isGuidFileTypeValid() const;
  bool isGuidFileTypeIgnored() const;
  QByteArray serializeGuidFileType() const;
  bool deserializeGuidFileType(QDataStream& in);


  QUuid getGuidFile() const;
  void setGuidFile(const QUuid &value);
  bool isGuidFileValid() const;
  bool isGuidFileIgnored() const;
  QByteArray serializeGuidFile() const;
  bool deserializeGuidFile(QDataStream& in);


  QUuid getGuidLegacyFileVersion() const;
  void setGuidLegacyFileVersion(const QUuid &value);
  bool isGuidLegacyFileVersionValid() const;
  bool isGuidLegacyFileVersionIgnored() const;
  QByteArray serializeGuidLegacyFileVersion() const;
  bool deserializeGuidLegacyFileVersion(QDataStream& in);



  QUuid getGuidFileFormat() const;
  void setGuidFileFormat(const QUuid &value);
  bool isGuidFileFormatValid() const;
  bool isGuidFileFormatIgnored() const;
  QByteArray serializeGuidFileFormat() const;
  bool deserializeGuidFileFormat(QDataStream& in);


  quint32  getFfvLastWriterVersion() const;
  void setFfvLastWriterVersion(quint32  value);
  bool isFfvLastWriterVersionValid() const;
  bool isFfvLastWriterVersionIgnored() const;
  QByteArray serializeFfvLastWriterVersion() const;
  bool deserializeFfvLastWriterVersion(QDataStream& in);

  quint32  getFfvNewestWriterVersion() const;
  void setFfvNewestWriterVersion(quint32  value);
  bool isFfvNewestWriterVersionValid() const;
  bool isFfvNewestWriterVersionIgnored() const;
  QByteArray serializeFfvNewestWriterVersion() const;
  bool deserializeFfvNewestWriterVersion(QDataStream& in);

  quint32  getFfvOldestWriterVersion() const;
  void setFfvOldestWriterVersion(quint32  value);
  bool isFfvOldestWriterVersionValid() const;
  bool isFfvOldestWriterVersionIgnored() const;
  QByteArray serializeFfvOldestWriterVersion() const;
  bool deserializeFfvOldestWriterVersion(QDataStream& in);

  quint32  getFfvOldestReader() const;
  void setFfvOldestReader(quint32  value);
  bool isFfvOldestReaderValid() const;
  bool isFfvOldestReaderIgnored() const;
  QByteArray serializeFfvOldestReader() const;
  bool deserializeFfvOldestReader(QDataStream& in);

  FileChunkReference32 getFcrLegacyFreeChunkList() const;
  void setFcrLegacyFreeChunkList(const FileChunkReference32 &value);
  bool isFcrLegacyFreeChunkListValid() const;
  bool isFcrLegacyFreeChunkListIgnored() const;
  QByteArray serializeFcrLegacyFreeChunkList() const;
  bool deserializeFcrLegacyFreeChunkList(QDataStream& in);

  FileChunkReference32 getFcrLegacyTransactionLog() const;
  void setFcrLegacyTransactionLog(const FileChunkReference32 &value);
  bool isFcrLegacyTransactionLogValid() const;
  bool isFcrLegacyTransactionLogIgnored() const;
  QByteArray serializeFcrLegacyTransactionLog() const;
  bool deserializeFcrLegacyTransactionLog(QDataStream& in);

  quint32  getCTransactionsInLog() const;
  void setCTransactionsInLog(quint32  value);
  void changeTransactionsInLog(quint32  value);
  bool isCTransactionsInLogValid() const;
  bool isCTransactionsInLogIgnored() const;
  QByteArray serializeCTransactionsInLog() const;
  bool deserializeCTransactionsInLog(QDataStream& in);

  quint32  getCbLegacyExpectedFileLength() const;
  void setCbLegacyExpectedFileLength(quint32  value);
  bool isCbLegacyExpectedFileLengthValid() const;
  bool isCbLegacyExpectedFileLengthIgnored() const;
  QByteArray serializeCbLegacyExpectedFileLength() const;
  bool deserializeCbLegacyExpectedFileLength(QDataStream& in);

  quint64  getRgbPlaceholder() const;
  void setRgbPlaceholder(quint64  value);
  bool isRgbPlaceholderValid() const;
  bool isRgbPlaceholderIgnored() const;
  QByteArray serializeRgbPlaceholder() const;
  bool deserializeRgbPlaceholder(QDataStream& in);

  FileChunkReference32 getFcrLegacyFileNodeListRoot() const;
  void setFcrLegacyFileNodeListRoot(const FileChunkReference32 &value);
  bool isFcrLegacyFileNodeListRootValid() const;
  bool isFcrLegacyFileNodeListRootIgnored() const;
  QByteArray serializeFcrLegacyFileNodeListRoot() const;
  bool deserializeFcrLegacyFileNodeListRoot(QDataStream& in);

  quint32  getCbLegacyFreeSpaceInFreeChunkList() const;
  void setCbLegacyFreeSpaceInFreeChunkList(quint32  value);
  bool isCbLegacyFreeSpaceInFreeChunkListValid() const;
  bool isCbLegacyFreeSpaceInFreeChunkListIgnored() const;
  QByteArray serializeCbLegacyFreeSpaceInFreeChunkList() const;
  bool deserializeCbLegacyFreeSpaceInFreeChunkList(QDataStream& in);

  quint8 getFNeedsDefrag() const;
  void setFNeedsDefrag(quint8 value);
  bool isFNeedsDefragValid() const;
  bool isFNeedsDefragIgnored() const;
  QByteArray serializeFNeedsDefrag() const;
  bool deserializeFNeedsDefrag(QDataStream& in);

  quint8 getFRepairedFile() const;
  void setFRepairedFile(quint8 value);
  bool isFRepairedFileValid() const;
  bool isFRepairedFileIgnored() const;
  QByteArray serializeFRepairedFile() const;
  bool deserializeFRepairedFile(QDataStream& in);

  quint8 getFNeedsGarbageCollect() const;
  void setFNeedsGarbageCollect(quint8 value);
  bool isFNeedsGarbageCollectValid() const;
  bool isFNeedsGarbageCollectIgnored() const;
  QByteArray serializeFNeedsGarbageCollect() const;
  bool deserializeFNeedsGarbageCollect(QDataStream& in);

  quint8 getFHasNoEmbeddedFileObjects() const;
  void setFHasNoEmbeddedFileObjects(quint8 value);
  bool isFHasNoEmbeddedFileObjectsValid() const;
  bool isFHasNoEmbeddedFileObjectsIgnored() const;
  QByteArray serializeFHasNoEmbeddedFileObjects() const;
  bool deserializeFHasNoEmbeddedFileObjects(QDataStream& in);

  QUuid getGuidAncestor() const;
  void setGuidAncestor(const QUuid &value);
  bool isGuidAncestorValid() const;
  bool isGuidAncestorIgnored() const;
  QByteArray serializeGuidAncestor() const;
  bool deserializeGuidAncestor(QDataStream& in);
  bool guidAncestorLocationInCD() const;
  bool guidAncestorLocationInPD() const;
  bool guidAncestorLocationNotPresent() const;

  quint32  getCrcName() const;
  void setCrcName(quint32  value);
  bool isCrcNameValid() const;
  bool isCrcNameIgnored() const;
  QByteArray serializeCrcName() const;
  bool deserializeCrcName(QDataStream& in);

  FileChunkReference64x32 getFcrHashedChunkList() const;
  void setFcrHashedChunkList(const FileChunkReference64x32 &value);
  bool isFcrHashedChunkListValid() const;
  bool isFcrHashedChunkListIgnored() const;
  QByteArray serializeFcrHashedChunkList() const;
  bool deserializeFcrHashedChunkList(QDataStream& in);
  bool fcrHashedChunkList_exits() const;

  FileChunkReference64x32 getFcrTransactionLog() const;
  void setFcrTransactionLog(const FileChunkReference64x32 &value);
  bool isFcrTransactionLogValid() const;
  bool isFcrTransactionLogIgnored() const;
  QByteArray serializeFcrTransactionLog() const;
  bool deserializeFcrTransactionLog(QDataStream& in);

  FileChunkReference64x32 getFcrFileNodeListRoot() const;
  void setFcrFileNodeListRoot(const FileChunkReference64x32 &value);
  bool isFcrFileNodeListRootValid() const;
  bool isFcrFileNodeListRootIgnored() const;
  QByteArray serializeFcrFileNodeListRoot() const;
  bool deserializeFcrFileNodeListRoot(QDataStream& in);

  FileChunkReference64x32 getFcrFreeChunkList() const;
  void setFcrFreeChunkList(const FileChunkReference64x32 &value);
  bool isFcrFreeChunkListValid() const;
  bool isFcrFreeChunkListIgnored() const;
  QByteArray serializeFcrFreeChunkList() const;
  bool deserializeFcrFreeChunkList(QDataStream& in);
  bool fcrFreeChunkList_exits() const;

  quint64  getCbExpectedFileLength() const;
  void setCbExpectedFileLength(quint64  value);
  bool isCbExpectedFileLengthValid() const;
  bool isCbExpectedFileLengthIgnored() const;
  QByteArray serializeCbExpectedFileLength() const;
  bool deserializeCbExpectedFileLength(QDataStream& in);

  quint64  getCbFreeSpaceInFreeChunkList() const;
  void setCbFreeSpaceInFreeChunkList(quint64  value);
  bool isCbFreeSpaceInFreeChunkListValid() const;
  bool isCbFreeSpaceInFreeChunkListIgnored() const;
  QByteArray serializeCbFreeSpaceInFreeChunkList() const;
  bool deserializeCbFreeSpaceInFreeChunkList(QDataStream& in);

  QUuid getGuidFileVersion() const;
  void setGuidFileVersion(const QUuid &value);
  void nextGuidFileVersion();
  bool isGuidFileVersionValid() const;
  bool isGuidFileVersionIgnored() const;
  QByteArray serializeGuidFileVersion() const;
  bool deserializeGuidFileVersion(QDataStream& in);

  quint64  getNFileVersionGeneration() const;
  void setNFileVersionGeneration(quint64  value);
  bool isNFileVersionGenerationValid() const;
  bool isNFileVersionGenerationIgnored() const;
  QByteArray serializeNFileVersionGeneration() const;
  bool deserializeNFileVersionGeneration(QDataStream& in);

  QUuid getGuidDenyReadFileVersion() const;
  void setGuidDenyReadFileVersion(const QUuid &value);
  void changeGuidDenyReadFileVersion();
  bool isGuidDenyReadFileVersionValid() const;
  bool isGuidDenyReadFileVersionIgnored() const;
  QByteArray serializeGuidDenyReadFileVersion() const;
  bool deserializeGuidDenyReadFileVersion(QDataStream& in);

  quint32  getGrfDebugLogFlags() const;
  void setGrfDebugLogFlags(quint32  value);
  bool isGrfDebugLogFlagsValid() const;
  bool isGrfDebugLogFlagsIgnored() const;
  QByteArray serializeGrfDebugLogFlags() const;
  bool deserializeGrfDebugLogFlags(QDataStream& in);

  FileChunkReference64x32 getFcrDebugLog() const;
  void setFcrDebugLog(const FileChunkReference64x32 &value);
  bool isFcrDebugLogValid() const;
  bool isFcrDebugLogIgnored() const;
  QByteArray serializeFcrDebugLog() const;
  bool deserializeFcrDebugLog(QDataStream& in);

  FileChunkReference64x32 getFcrAllocVerificationFreeChunkList() const;
  void setFcrAllocVerificationFreeChunkList(const FileChunkReference64x32 &value);
  bool isFcrAllocVerificationFreeChunkListValid() const;
  bool isFcrAllocVerificationFreeChunkListIgnored() const;
  QByteArray serializeFcrAllocVerificationFreeChunkList() const;
  bool deserializeFcrAllocVerificationFreeChunkList(QDataStream& in);

  quint32  getBnCreated() const;
  void setBnCreated(quint32  value);
  bool isBnCreatedValid() const;
  bool isBnCreatedIgnored() const;
  QByteArray serializeBnCreated() const;
  bool deserializeBnCreated(QDataStream& in);

  quint32  getBnLastWroteToThisFile() const;
  void setBnLastWroteToThisFile(quint32  value);
  bool isBnLastWroteToThisFileValid() const;
  bool isBnLastWroteToThisFileIgnored() const;
  QByteArray serializeBnLastWroteToThisFile() const;
  bool deserializeBnLastWroteToThisFile(QDataStream& in);

  quint32  getBnOldestWritten() const;
  void setBnOldestWritten(quint32  value);
  bool isBnOldestWrittenValid() const;
  bool isBnOldestWrittenIgnored() const;
  QByteArray serializeBnOldestWritten() const;
  bool deserializeBnOldestWritten(QDataStream& in);

  quint32  getBnNewestWritten() const;
  void setBnNewestWritten(quint32  value);
  bool isBnNewestWrittenValid() const;
  bool isBnNewestWrittenIgnored() const;
  QByteArray serializeBnNewestWritten() const;
  bool deserializeBnNewestWritten(QDataStream& in);

  QByteArray getReservedHeaderTail() const;
  void setReservedHeaderTail(const QByteArray &value);
  bool isReservedHeaderTailValid() const;
  bool isReservedHeaderTailIgnored() const;
  QByteArray serializeReservedHeaderTail() const;
  bool deserializeReservedHeaderTail(QDataStream& in);

};




#endif // MSONHEADER_H
