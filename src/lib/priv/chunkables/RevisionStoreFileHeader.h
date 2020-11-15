#ifndef REVISIONSTOREFILEHEADER_H
#define REVISIONSTOREFILEHEADER_H

#include <QUuid>
#include <QtCore/qglobal.h>

#include <memory>

#include "Chunkable.h"

#include "../commonTypes/FileChunkReference32.h"
#include "../commonTypes/FileChunkReference64x32.h"

#include "Chunkable.h"

#include "FileNodeListFragment.h"
#include "FreeChunkListFragment.h"
#include "TransactionLogFragment.h"

namespace libmson {
namespace priv {

class RevisionStoreFileHeader : public Chunkable {

  friend class RevisionStoreFileWriter;
  friend class RevisionStoreFileParser;


public:
  RevisionStoreFileHeader(
      const quint64 initialStp = 0, const quint64 initialCb = 0);

  RevisionStoreFileHeader(
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
      const quint64 nFileVersionGeneration,
      const QUuid& guidDenyReadFileVersion, const quint32 grfDebugLogFlags,
      const quint32 bnCreated, const quint32 bnLastWroteToThisFile,
      const quint32 bnOldestWritten, const quint32 bnNewestWritten);

  RevisionStoreFileHeader(
      const QUuid& guidFileType, const QUuid& guidFile,
      const quint32 ffvLastWriterVersion, const quint32 ffvOldestWriterVersion,
      const quint32 ffvNewestWriterVersion, const quint32 ffvOldestReader,
      const quint32 cTransactionsInLog, const quint64 rgbPlaceholder,
      const quint8 fNeedsDefrag, const quint8 fRepairedFile,
      const quint8 fNeedsGarbageCollect, const quint8 fHasNoEmbeddedFileObjects,
      const QUuid& guidAncestor, const quint32 crcName,
      const quint64 cbExpectedFileLength,
      const quint64 cbFreeSpaceInFreeChunkList, const QUuid& guidFileVersion,
      const quint64 nFileVersionGeneration,
      const QUuid& guidDenyReadFileVersion, const quint32 grfDebugLogFlags,
      const quint32 bnCreated, const quint32 bnLastWroteToThisFile,
      const quint32 bnOldestWritten, const quint32 bnNewestWritten);

  static const constexpr quint64 sizeInFile = 0x400;

private:
  // Chunkable interface
  virtual quint64 cb() const override { return sizeInFile; }
  virtual RevisionStoreChunkType getType() const override
  {
    return RevisionStoreChunkType::RevisionStoreFileHeader;
  };

private:
  QUuid guidFileType;
  QUuid guidFile;
  QUuid guidLegacyFileVersion;
  QUuid guidFileFormat;
  quint32 ffvLastWriterVersion;   // ffvLastCodeThatWroteToThisFile  // long?
  quint32 ffvOldestWriterVersion; // ffvNewestCodeThatHasWrittenToThisFile
  quint32 ffvNewestWriterVersion; // ffvOldestCodeThatHasWrittenToThisFile
  quint32 ffvOldestReader;        // ffvOldestCodeThatMayReadThisFile
  quint32 cTransactionsInLog;
  quint64 rgbPlaceholder;
  quint8 fNeedsDefrag;
  quint8 fRepairedFile;
  quint8 fNeedsGarbageCollect;
  quint8 fHasNoEmbeddedFileObjects;
  QUuid guidAncestor;
  quint32 crcName;
  FileNodeListFragment_WPtr_t fcrHashedChunkList;
  TransactionLogFragment_WPtr_t fcrTransactionLog;
  FileNodeListFragment_WPtr_t fcrFileNodeListRoot;
  FreeChunkListFragment_WPtr_t fcrFreeChunkList;
  quint64 cbExpectedFileLength;
  quint64 cbFreeSpaceInFreeChunkList;
  QUuid guidFileVersion;
  quint64 nFileVersionGeneration;
  QUuid guidDenyReadFileVersion;
  quint32 grfDebugLogFlags;
  quint32 bnCreated;
  quint32 bnLastWroteToThisFile;
  quint32 bnOldestWritten;
  quint32 bnNewestWritten;


  static const QUuid v_guidFileType_One;
  static const QUuid v_guidFileType_OneToc2;
  static const QUuid v_guidFileFormat;
  static const QUuid v_guidLegacyFileVersion;


  static const quint32 def_reservedHeaderTailLength = 728;

public:
  QUuid getGuidFileType() const;
  void setGuidFileType(const QUuid& value);

  QUuid getGuidFile() const;
  void setGuidFile(const QUuid& value);

  QUuid getGuidLegacyFileVersion() const;
  void setGuidLegacyFileVersion(const QUuid& value);

  QUuid getGuidFileFormat() const { return QUuid(guidFileFormat); };

  quint32 getFfvLastWriterVersion() const;
  void setFfvLastWriterVersion(const quint32 value);

  quint32 getFfvNewestWriterVersion() const;
  void setFfvNewestWriterVersion(const quint32 value);

  quint32 getFfvOldestWriterVersion() const;
  void setFfvOldestWriterVersion(const quint32 value);

  quint32 getFfvOldestReader() const;
  void setFfvOldestReader(const quint32 value);

  quint32 getCTransactionsInLog() const;
  void setCTransactionsInLog(const quint32 value);

  quint64 getRgbPlaceholder() const;
  void setRgbPlaceholder(const quint64 value);

  quint8 getFNeedsDefrag() const;
  void setFNeedsDefrag(quint8 value);

  quint8 getFRepairedFile() const;
  void setFRepairedFile(const quint8 value);

  quint8 getFNeedsGarbageCollect() const;
  void setFNeedsGarbageCollect(const quint8 value);

  quint8 getFHasNoEmbeddedFileObjects() const;
  void setFHasNoEmbeddedFileObjects(const quint8 value);

  QUuid getGuidAncestor() const;
  void setGuidAncestor(const QUuid& value);

  quint32 getCrcName() const;
  void setCrcName(const quint32 value);

  FileNodeListFragment_WPtr_t getFcrHashedChunkList();
  void setFcrHashedChunkList(FileNodeListFragment_WPtr_t value);

  TransactionLogFragment_WPtr_t getFcrTransactionLog();
  void setFcrTransactionLog(TransactionLogFragment_WPtr_t value);

  FileNodeListFragment_WPtr_t getFcrFileNodeListRoot();
  void setFcrFileNodeListRoot(FileNodeListFragment_WPtr_t value);

  FreeChunkListFragment_WPtr_t getFcrFreeChunkList();
  void setFcrFreeChunkList(FreeChunkListFragment_WPtr_t value);

  quint64 getCbExpectedFileLength() const;
  void setCbExpectedFileLength(const quint64 value);

  quint64 getCbFreeSpaceInFreeChunkList() const;
  void setCbFreeSpaceInFreeChunkList(const quint64 value);

  QUuid getGuidFileVersion() const;
  void setGuidFileVersion(const QUuid& value);

  quint64 getNFileVersionGeneration() const;
  void setNFileVersionGeneration(const quint64 value);

  QUuid getGuidDenyReadFileVersion() const;
  void setGuidDenyReadFileVersion(const QUuid& value);

  quint32 getGrfDebugLogFlags() const;
  void setGrfDebugLogFlags(const quint32 value);

  quint32 getBnCreated() const;
  void setBnCreated(const quint32 value);

  quint32 getBnLastWroteToThisFile() const;
  void setBnLastWroteToThisFile(const quint32 value);

  quint32 getBnOldestWritten() const;
  void setBnOldestWritten(const quint32 value);

  quint32 getBnNewestWritten() const;
  void setBnNewestWritten(const quint32 value);
};


typedef std::shared_ptr<RevisionStoreFileHeader> RevisionStoreFileHeader_SPtr_t;
typedef std::weak_ptr<RevisionStoreFileHeader> RevisionStoreFileHeader_WPtr_t;

} // namespace priv
} // namespace libmson

#endif // REVISIONSTOREFILEHEADER_H
