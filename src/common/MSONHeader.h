#ifndef MSONHEADER_H
#define MSONHEADER_H

#include <memory>

#include <QByteArray>
#include <QString>
#include <QUuid>
#include <QXmlStreamWriter>
#include <QtCore/qglobal.h>

#include "commonTypes/FileChunkReference32.h"
#include "commonTypes/FileChunkReference64x32.h"
#include "commonTypes/IFileChunkReference.h"

#include "IRevisionStoreFileObject.h"

namespace MSONcommon {

/**
 * @class MSONHeader
 *
 * @brief serialzies and deserializes an MSON file stream
 *
 * MSON Header class which (de)serialzies an input stream
 */
class MSONHeader : public IRevisionStoreFileObject {
private:
  QUuid guidFileType;
  QUuid guidFile;
  QUuid guidLegacyFileVersion;
  QUuid guidFileFormat;
  quint32 ffvLastWriterVersion;   // ffvLastCodeThatWroteToThisFile  // long?
  quint32 ffvOldestWriterVersion; // ffvNewestCodeThatHasWrittenToThisFile
  quint32 ffvNewestWriterVersion; // ffvOldestCodeThatHasWrittenToThisFile
  quint32 ffvOldestReader;        // ffvOldestCodeThatMayReadThisFile
  FileChunkReference32 fcrLegacyFreeChunkList;
  FileChunkReference32 fcrLegacyTransactionLog;
  quint32 cTransactionsInLog;
  quint32 cbLegacyExpectedFileLength;
  quint64 rgbPlaceholder;
  FileChunkReference32 fcrLegacyFileNodeListRoot;
  quint32 cbLegacyFreeSpaceInFreeChunkList;
  quint8 fNeedsDefrag;
  quint8 fRepairedFile;
  quint8 fNeedsGarbageCollect;
  quint8 fHasNoEmbeddedFileObjects;
  QUuid guidAncestor;
  quint32 crcName;
  FileChunkReference64x32 fcrHashedChunkList;
  FileChunkReference64x32 fcrTransactionLog;
  FileChunkReference64x32 fcrFileNodeListRoot;
  FileChunkReference64x32 fcrFreeChunkList;
  quint64 cbExpectedFileLength;
  quint64 cbFreeSpaceInFreeChunkList;
  QUuid guidFileVersion;
  quint64 nFileVersionGeneration;
  QUuid guidDenyReadFileVersion;
  quint32 grfDebugLogFlags;
  FileChunkReference64x32 fcrDebugLog;
  FileChunkReference64x32 fcrAllocVerificationFreeChunkList;
  quint32 bnCreated;
  quint32 bnLastWroteToThisFile;
  quint32 bnOldestWritten;
  quint32 bnNewestWritten;
  quint32 reservedHeaderTailLength;

public:
  MSONHeader();

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;

public:
  QUuid getGuidFileType() const;
  void setGuidFileType(const QUuid &value);
  bool isGuidFileTypeValid() const;
  static bool isGuidFileTypeIgnored();

  QUuid getGuidFile() const;
  void setGuidFile(const QUuid &value);
  bool isGuidFileValid() const;
  static bool isGuidFileIgnored();

  QUuid getGuidLegacyFileVersion() const;
  void setGuidLegacyFileVersion(const QUuid &value);
  bool isGuidLegacyFileVersionValid() const;
  static bool isGuidLegacyFileVersionIgnored();

  QUuid getGuidFileFormat() const;
  void setGuidFileFormat(const QUuid &value);
  bool isGuidFileFormatValid() const;
  static bool isGuidFileFormatIgnored();

  quint32 getFfvLastWriterVersion() const;
  void setFfvLastWriterVersion(quint32 value);
  bool isFfvLastWriterVersionValid() const;
  static bool isFfvLastWriterVersionIgnored();

  quint32 getFfvNewestWriterVersion() const;
  void setFfvNewestWriterVersion(quint32 value);
  bool isFfvNewestWriterVersionValid() const;
  static bool isFfvNewestWriterVersionIgnored();

  quint32 getFfvOldestWriterVersion() const;
  void setFfvOldestWriterVersion(quint32 value);
  bool isFfvOldestWriterVersionValid() const;
  static bool isFfvOldestWriterVersionIgnored();

  quint32 getFfvOldestReader() const;
  void setFfvOldestReader(quint32 value);
  bool isFfvOldestReaderValid() const;
  static bool isFfvOldestReaderIgnored();

  FileChunkReference32 getFcrLegacyFreeChunkList() const;
  void setFcrLegacyFreeChunkList(const FileChunkReference32 &value);
  bool isFcrLegacyFreeChunkListValid() const;
  bool isFcrLegacyFreeChunkListIgnored() const;

  FileChunkReference32 getFcrLegacyTransactionLog() const;
  void setFcrLegacyTransactionLog(const FileChunkReference32 &value);
  bool isFcrLegacyTransactionLogValid() const;
  bool isFcrLegacyTransactionLogIgnored() const;

  quint32 getCTransactionsInLog() const;
  void setCTransactionsInLog(quint32 value);
  void changeTransactionsInLog(quint32 value);
  bool isCTransactionsInLogValid() const;
  bool isCTransactionsInLogIgnored() const;

  quint32 getCbLegacyExpectedFileLength() const;
  void setCbLegacyExpectedFileLength(quint32 value);
  bool isCbLegacyExpectedFileLengthValid() const;
  bool isCbLegacyExpectedFileLengthIgnored() const;

  quint64 getRgbPlaceholder() const;
  void setRgbPlaceholder(quint64 value);
  bool isRgbPlaceholderValid() const;
  bool isRgbPlaceholderIgnored() const;

  FileChunkReference32 getFcrLegacyFileNodeListRoot() const;
  void setFcrLegacyFileNodeListRoot(const FileChunkReference32 &value);
  bool isFcrLegacyFileNodeListRootValid() const;
  bool isFcrLegacyFileNodeListRootIgnored() const;

  quint32 getCbLegacyFreeSpaceInFreeChunkList() const;
  void setCbLegacyFreeSpaceInFreeChunkList(quint32 value);
  bool isCbLegacyFreeSpaceInFreeChunkListValid() const;
  bool isCbLegacyFreeSpaceInFreeChunkListIgnored() const;

  quint8 getFNeedsDefrag() const;
  void setFNeedsDefrag(quint8 value);
  bool isFNeedsDefragValid() const;
  bool isFNeedsDefragIgnored() const;

  quint8 getFRepairedFile() const;
  void setFRepairedFile(quint8 value);
  bool isFRepairedFileValid() const;
  bool isFRepairedFileIgnored() const;

  quint8 getFNeedsGarbageCollect() const;
  void setFNeedsGarbageCollect(quint8 value);
  bool isFNeedsGarbageCollectValid() const;
  bool isFNeedsGarbageCollectIgnored() const;

  quint8 getFHasNoEmbeddedFileObjects() const;
  void setFHasNoEmbeddedFileObjects(quint8 value);
  bool isFHasNoEmbeddedFileObjectsValid() const;
  bool isFHasNoEmbeddedFileObjectsIgnored() const;

  QUuid getGuidAncestor() const;
  void setGuidAncestor(const QUuid &value);
  bool isGuidAncestorValid() const;
  bool isGuidAncestorIgnored() const;
  bool guidAncestorLocationInCD() const;
  bool guidAncestorLocationInPD() const;
  bool guidAncestorLocationNotPresent() const;

  quint32 getCrcName() const;
  void setCrcName(quint32 value);
  bool isCrcNameValid() const;
  bool isCrcNameIgnored() const;

  FileChunkReference64x32 &getFcrHashedChunkList();
  void setFcrHashedChunkList(const FileChunkReference64x32 &value);
  bool isFcrHashedChunkListValid() const;
  bool isFcrHashedChunkListIgnored() const;
  bool fcrHashedChunkList_exits() const;

  FileChunkReference64x32 &getFcrTransactionLog();
  void setFcrTransactionLog(const FileChunkReference64x32 &value);
  bool isFcrTransactionLogValid() const;
  bool isFcrTransactionLogIgnored() const;

  FileChunkReference64x32 &getFcrFileNodeListRoot();
  void setFcrFileNodeListRoot(const FileChunkReference64x32 &value);
  bool isFcrFileNodeListRootValid() const;
  bool isFcrFileNodeListRootIgnored() const;

  FileChunkReference64x32 &getFcrFreeChunkList();
  void setFcrFreeChunkList(const FileChunkReference64x32 &value);
  bool isFcrFreeChunkListValid() const;
  bool isFcrFreeChunkListIgnored() const;
  bool fcrFreeChunkList_exits() const;

  quint64 getCbExpectedFileLength() const;
  void setCbExpectedFileLength(quint64 value);
  bool isCbExpectedFileLengthValid() const;
  bool isCbExpectedFileLengthIgnored() const;

  quint64 getCbFreeSpaceInFreeChunkList() const;
  void setCbFreeSpaceInFreeChunkList(quint64 value);
  bool isCbFreeSpaceInFreeChunkListValid() const;
  bool isCbFreeSpaceInFreeChunkListIgnored() const;

  QUuid getGuidFileVersion() const;
  void setGuidFileVersion(const QUuid &value);
  void nextGuidFileVersion();
  bool isGuidFileVersionValid() const;
  bool isGuidFileVersionIgnored() const;

  quint64 getNFileVersionGeneration() const;
  void setNFileVersionGeneration(quint64 value);
  bool isNFileVersionGenerationValid() const;
  bool isNFileVersionGenerationIgnored() const;

  QUuid getGuidDenyReadFileVersion() const;
  void setGuidDenyReadFileVersion(const QUuid &value);
  void changeGuidDenyReadFileVersion();
  bool isGuidDenyReadFileVersionValid() const;
  bool isGuidDenyReadFileVersionIgnored() const;

  quint32 getGrfDebugLogFlags() const;
  void setGrfDebugLogFlags(quint32 value);
  bool isGrfDebugLogFlagsValid() const;
  bool isGrfDebugLogFlagsIgnored() const;

  FileChunkReference64x32 &getFcrDebugLog();
  void setFcrDebugLog(const FileChunkReference64x32 &value);
  bool isFcrDebugLogValid() const;
  bool isFcrDebugLogIgnored() const;

  FileChunkReference64x32 getFcrAllocVerificationFreeChunkList() const;
  void
  setFcrAllocVerificationFreeChunkList(const FileChunkReference64x32 &value);
  bool isFcrAllocVerificationFreeChunkListValid() const;
  bool isFcrAllocVerificationFreeChunkListIgnored() const;

  quint32 getBnCreated() const;
  void setBnCreated(quint32 value);
  bool isBnCreatedValid() const;
  bool isBnCreatedIgnored() const;

  quint32 getBnLastWroteToThisFile() const;
  void setBnLastWroteToThisFile(quint32 value);
  bool isBnLastWroteToThisFileValid() const;
  bool isBnLastWroteToThisFileIgnored() const;

  quint32 getBnOldestWritten() const;
  void setBnOldestWritten(quint32 value);
  bool isBnOldestWrittenValid() const;
  bool isBnOldestWrittenIgnored() const;

  quint32 getBnNewestWritten() const;
  void setBnNewestWritten(quint32 value);
  bool isBnNewestWrittenValid() const;
  bool isBnNewestWrittenIgnored() const;

  quint32 getReservedHeaderTailLength() const;
  void setReservedHeaderTailLength(const quint32 &value);
  bool isReservedHeaderTailValid() const;
  bool isReservedHeaderTailIgnored() const;
};

#endif // MSONHEADER_H
}
