#ifndef REVISIONSTOREFILEHEADER_H
#define REVISIONSTOREFILEHEADER_H

#include <QUuid>
#include <QtCore/qglobal.h>
#include <priv/commonTypes/FileChunkReference32.h>
#include <priv/commonTypes/FileChunkReference64x32.h>

#include <memory>

#include "Chunkable.h"


namespace libmson {
namespace priv {

typedef std::shared_ptr<class TransactionLogFragment>
    TransactionLogFragment_SPtr_t;
typedef std::weak_ptr<class TransactionLogFragment>
    TransactionLogFragment_WPtr_t;

typedef std::shared_ptr<class FreeChunkListFragment>
    FreeChunkListFragment_SPtr_t;
typedef std::weak_ptr<class FreeChunkListFragment> FreeChunkListFragment_WPtr_t;

typedef std::shared_ptr<class FileNodeListFragment> FileNodeListFragment_SPtr_t;
typedef std::weak_ptr<class FileNodeListFragment> FileNodeListFragment_WPtr_t;


class RevisionStoreFileHeader : public Chunkable {


  friend class RevisionStoreFileParser;


public:
  RevisionStoreFileHeader(
      const quint64 initialStp = 0, const quint64 initialCb = 0, const quint64 cbExpectedFileLength = 0x400);

  RevisionStoreFileHeader(
    const QUuid& guidFileType, const QUuid& guidFile,
    const quint32 ffvLastWriterVersion, const quint32 ffvOldestWriterVersion,
    const quint32 ffvNewestWriterVersion, const quint32 ffvOldestReader,
    const FileChunkReference32& fcrLegacyFreeChunkList,
    const FileChunkReference32& fcrLegacyTransactionLog,
    const quint32 cTransactionsInLog, const quint32 cbLegacyExpectedFileLength,
    const quint64 rgbPlaceholder,
    const FileChunkReference32& fcrLegacyFileNodeListRoot,
    const quint32 cbLegacyFreeSpaceInFreeChunkList, const quint8 fNeedsDefrag,
    const quint8 fRepairedFile, const quint8 fNeedsGarbageCollect,
    const quint8 fHasNoEmbeddedFileObjects, const QUuid& guidAncestor,
    const quint32 crcName, FileNodeListFragment_SPtr_t fcrHashedChunkList,
    TransactionLogFragment_SPtr_t fcrTransactionLog,
    FileNodeListFragment_SPtr_t fcrFileNodeListRoot,
    FreeChunkListFragment_SPtr_t fcrFreeChunkList,
    const quint64 cbExpectedFileLength,
    const quint64 cbFreeSpaceInFreeChunkList, const QUuid& guidFileVersion,
    const quint64 nFileVersionGeneration, const QUuid& guidDenyReadFileVersion,
    const quint32 grfDebugLogFlags, const FileChunkReference64x32& fcrDebugLog,
    const FileChunkReference64x32& fcrAllocVerificationFreeChunkList,
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

  static const constexpr quint64 sizeInFile = 0x400u;

  static const QUuid guidFileType_One;
  static const QUuid guidFileType_OneToc2;
  static const QUuid guidFileFormat;
  static const QUuid guidLegacyFileVersion;


  static const quint32 def_reservedHeaderTailLength = 728u;

private:
  // Chunkable interface
  virtual quint64 cb() const override { return sizeInFile; }
  virtual RevisionStoreChunkType getType() const override
  {
    return RevisionStoreChunkType::RevisionStoreFileHeader;
  };

private:
  QUuid m_guidFileType;
  QUuid m_guidFile;
  QUuid m_guidLegacyFileVersion;
  QUuid m_guidFileFormat;
  quint32 m_ffvLastWriterVersion;   // ffvLastCodeThatWroteToThisFile  // long?
  quint32 m_ffvOldestWriterVersion; // ffvNewestCodeThatHasWrittenToThisFile
  quint32 m_ffvNewestWriterVersion; // ffvOldestCodeThatHasWrittenToThisFile
  quint32 m_ffvOldestReader;        // ffvOldestCodeThatMayReadThisFile
  FileChunkReference32 m_fcrLegacyFreeChunkList;
  FileChunkReference32 m_fcrLegacyTransactionLog;
  quint32 m_cTransactionsInLog;
  quint32 m_cbLegacyExpectedFileLength;
  quint64 m_rgbPlaceholder;
  FileChunkReference32 m_fcrLegacyFileNodeListRoot;
  quint32 m_cbLegacyFreeSpaceInFreeChunkList;
  quint8 m_fNeedsDefrag;
  quint8 m_fRepairedFile;
  quint8 m_fNeedsGarbageCollect;
  quint8 m_fHasNoEmbeddedFileObjects;
  QUuid m_guidAncestor;
  quint32 m_crcName;
  FileNodeListFragment_WPtr_t m_fcrHashedChunkList;
  TransactionLogFragment_WPtr_t m_fcrTransactionLog;
  FileNodeListFragment_WPtr_t m_fcrFileNodeListRoot;
  FreeChunkListFragment_WPtr_t m_fcrFreeChunkList;
  quint64 m_cbExpectedFileLength;
  quint64 m_cbFreeSpaceInFreeChunkList;
  QUuid m_guidFileVersion;
  quint64 m_nFileVersionGeneration;
  QUuid m_guidDenyReadFileVersion;
  quint32 m_grfDebugLogFlags;
  FileChunkReference64x32 m_fcrDebugLog;
  FileChunkReference64x32 m_fcrAllocVerificationFreeChunkList;
  quint32 m_bnCreated;
  quint32 m_bnLastWroteToThisFile;
  quint32 m_bnOldestWritten;
  quint32 m_bnNewestWritten;


public:
  QUuid getGuidFileType() const;
  void setGuidFileType(const QUuid& value);

  QUuid getGuidFile() const;
  void setGuidFile(const QUuid& value);

  QUuid getGuidLegacyFileVersion() const { return guidLegacyFileVersion; };

  QUuid getGuidFileFormat() const { return guidFileFormat; };

  quint32 getFfvLastWriterVersion() const;
  void setFfvLastWriterVersion(const quint32 value);

  quint32 getFfvNewestWriterVersion() const;
  void setFfvNewestWriterVersion(const quint32 value);

  quint32 getFfvOldestWriterVersion() const;
  void setFfvOldestWriterVersion(const quint32 value);

  quint32 getFfvOldestReader() const;
  void setFfvOldestReader(const quint32 value);

  FileChunkReference32 getFcrLegacyFreeChunkList() const;

  FileChunkReference32 getFcrLegacyTransactionLog() const;

  quint32 getCTransactionsInLog() const;
  void setCTransactionsInLog(const quint32 value);

  quint32 getCbLegacyExpectedFileLength() const;

  quint64 getRgbPlaceholder() const;
  void setRgbPlaceholder(const quint64 value);

  FileChunkReference32 getFcrLegacyFileNodeListRoot() const;
  void setFcrLegacyFileNodeListRoot(
      const FileChunkReference32& fcrLegacyFileNodeListRoot);

  quint32 getCbLegacyFreeSpaceInFreeChunkList() const;
  void setCbLegacyFreeSpaceInFreeChunkList(
      const quint32& cbLegacyFreeSpaceInFreeChunkList);

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
  void setFcrHashedChunkList(FileNodeListFragment_SPtr_t value);

  TransactionLogFragment_WPtr_t getFcrTransactionLog();
  void setFcrTransactionLog(TransactionLogFragment_SPtr_t value);

  FileNodeListFragment_WPtr_t getFcrFileNodeListRoot();
  void setFcrFileNodeListRoot(FileNodeListFragment_SPtr_t value);

  FreeChunkListFragment_WPtr_t getFcrFreeChunkList();
  void setFcrFreeChunkList(FreeChunkListFragment_SPtr_t value);

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

  FileChunkReference64x32 getFcrDebugLog() const;

  FileChunkReference64x32 getFcrAllocVerificationFreeChunkList() const;

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
