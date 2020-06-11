#include "MSONHeader.h"

QUuid MSONHeader::getGuidFile() const
{
  return guidFile;
}

void MSONHeader::setGuidFile(const QUuid &value)
{
  guidFile = value;
}

QUuid MSONHeader::getGuidFileType() const
{
  return guidFileType;
}

void MSONHeader::setGuidFileType(const QUuid &value)
{
  guidFileType = value;
}

QUuid MSONHeader::getGuidLegacyFileVersion() const
{
  return guidLegacyFileVersion;
}

void MSONHeader::setGuidLegacyFileVersion(const QUuid &value)
{
  guidLegacyFileVersion = value;
}

QUuid MSONHeader::getGuidFileFormat() const
{
  return guidFileFormat;
}

void MSONHeader::setGuidFileFormat(const QUuid &value)
{
  guidFileFormat = value;
}

long MSONHeader::getFfvLastCode() const
{
  return ffvLastCode;
}

void MSONHeader::setFfvLastCode(long value)
{
  ffvLastCode = value;
}

long MSONHeader::getFfvNewestCode() const
{
  return ffvNewestCode;
}

void MSONHeader::setFfvNewestCode(long value)
{
  ffvNewestCode = value;
}

long MSONHeader::getFfvOldestCode() const
{
  return ffvOldestCode;
}

void MSONHeader::setFfvOldestCode(long value)
{
  ffvOldestCode = value;
}

long MSONHeader::getFfvOldestReader() const
{
  return ffvOldestReader;
}

void MSONHeader::setFfvOldestReader(long value)
{
  ffvOldestReader = value;
}

FileChunkReference MSONHeader::getFcrLegacyFreeChunkList() const
{
  return fcrLegacyFreeChunkList;
}

void MSONHeader::setFcrLegacyFreeChunkList(const FileChunkReference &value)
{
  fcrLegacyFreeChunkList = value;
}

FileChunkReference MSONHeader::getFcrLegacyTransactionLog() const
{
  return fcrLegacyTransactionLog;
}

void MSONHeader::setFcrLegacyTransactionLog(const FileChunkReference &value)
{
  fcrLegacyTransactionLog = value;
}

long MSONHeader::getCTransactionsInLog() const
{
  return cTransactionsInLog;
}

void MSONHeader::setCTransactionsInLog(long value)
{
  cTransactionsInLog = value;
}

long MSONHeader::getCbLegacyExpectedFileLength() const
{
  return cbLegacyExpectedFileLength;
}

void MSONHeader::setCbLegacyExpectedFileLength(long value)
{
  cbLegacyExpectedFileLength = value;
}

long MSONHeader::getRgbPlaceholder() const
{
  return rgbPlaceholder;
}

void MSONHeader::setRgbPlaceholder(long value)
{
  rgbPlaceholder = value;
}

FileChunkReference MSONHeader::getFcrLegacyFileNodeListRoot() const
{
  return fcrLegacyFileNodeListRoot;
}

void MSONHeader::setFcrLegacyFileNodeListRoot(const FileChunkReference &value)
{
  fcrLegacyFileNodeListRoot = value;
}

long MSONHeader::getCbLegacyFreeSpaceInFreeChunkList() const
{
  return cbLegacyFreeSpaceInFreeChunkList;
}

void MSONHeader::setCbLegacyFreeSpaceInFreeChunkList(long value)
{
  cbLegacyFreeSpaceInFreeChunkList = value;
}

short MSONHeader::getFNeedsDefrag() const
{
  return fNeedsDefrag;
}

void MSONHeader::setFNeedsDefrag(short value)
{
  fNeedsDefrag = value;
}

short MSONHeader::getFRepairedFile() const
{
  return fRepairedFile;
}

void MSONHeader::setFRepairedFile(short value)
{
  fRepairedFile = value;
}

short MSONHeader::getFNeedsGarbageCollect() const
{
  return fNeedsGarbageCollect;
}

void MSONHeader::setFNeedsGarbageCollect(short value)
{
  fNeedsGarbageCollect = value;
}

unsigned short MSONHeader::getFHasNoEmbeddedFileObjects() const
{
  return fHasNoEmbeddedFileObjects;
}

void MSONHeader::setFHasNoEmbeddedFileObjects(unsigned short value)
{
  fHasNoEmbeddedFileObjects = value;
}

QUuid MSONHeader::getGuidAncestor() const
{
  return guidAncestor;
}

void MSONHeader::setGuidAncestor(const QUuid &value)
{
  guidAncestor = value;
}

long MSONHeader::getCrcName() const
{
  return crcName;
}

void MSONHeader::setCrcName(long value)
{
  crcName = value;
}

FileChunkReference MSONHeader::getFcrHashedChunkList() const
{
  return fcrHashedChunkList;
}

void MSONHeader::setFcrHashedChunkList(const FileChunkReference &value)
{
  fcrHashedChunkList = value;
}

FileChunkReference MSONHeader::getFcrTransactionLog() const
{
  return fcrTransactionLog;
}

void MSONHeader::setFcrTransactionLog(const FileChunkReference &value)
{
  fcrTransactionLog = value;
}

FileChunkReference MSONHeader::getFcrFileNodeListRoot() const
{
  return fcrFileNodeListRoot;
}

void MSONHeader::setFcrFileNodeListRoot(const FileChunkReference &value)
{
  fcrFileNodeListRoot = value;
}

FileChunkReference MSONHeader::getFcrFreeChunkList() const
{
  return fcrFreeChunkList;
}

void MSONHeader::setFcrFreeChunkList(const FileChunkReference &value)
{
  fcrFreeChunkList = value;
}

long MSONHeader::getCbExpectedFileLength() const
{
  return cbExpectedFileLength;
}

void MSONHeader::setCbExpectedFileLength(long value)
{
  cbExpectedFileLength = value;
}

long MSONHeader::getCbFreeSpaceInFreeChunkList() const
{
  return cbFreeSpaceInFreeChunkList;
}

void MSONHeader::setCbFreeSpaceInFreeChunkList(long value)
{
  cbFreeSpaceInFreeChunkList = value;
}

QUuid MSONHeader::getGuidFileVersion() const
{
  return guidFileVersion;
}

void MSONHeader::setGuidFileVersion(const QUuid &value)
{
  guidFileVersion = value;
}

long MSONHeader::getNFileVersionGeneration() const
{
  return nFileVersionGeneration;
}

void MSONHeader::setNFileVersionGeneration(long value)
{
  nFileVersionGeneration = value;
}

QUuid MSONHeader::getGuidDenyReadFileVersion() const
{
  return guidDenyReadFileVersion;
}

void MSONHeader::setGuidDenyReadFileVersion(const QUuid &value)
{
  guidDenyReadFileVersion = value;
}

long MSONHeader::getGrfDebugLogFlags() const
{
  return grfDebugLogFlags;
}

void MSONHeader::setGrfDebugLogFlags(long value)
{
  grfDebugLogFlags = value;
}

FileChunkReference MSONHeader::getFcrDebugLog() const
{
  return fcrDebugLog;
}

void MSONHeader::setFcrDebugLog(const FileChunkReference &value)
{
  fcrDebugLog = value;
}

FileChunkReference MSONHeader::getFcrAllocVerificationFreeChunkList() const
{
  return fcrAllocVerificationFreeChunkList;
}

void MSONHeader::setFcrAllocVerificationFreeChunkList(const FileChunkReference &value)
{
  fcrAllocVerificationFreeChunkList = value;
}

long MSONHeader::getBnCreated() const
{
  return bnCreated;
}

void MSONHeader::setBnCreated(long value)
{
  bnCreated = value;
}

long MSONHeader::getBnLastWroteToThisFile() const
{
  return bnLastWroteToThisFile;
}

void MSONHeader::setBnLastWroteToThisFile(long value)
{
  bnLastWroteToThisFile = value;
}

long MSONHeader::getBnOldestWritten() const
{
  return bnOldestWritten;
}

void MSONHeader::setBnOldestWritten(long value)
{
  bnOldestWritten = value;
}

long MSONHeader::getBnNewestWritten() const
{
  return bnNewestWritten;
}

void MSONHeader::setBnNewestWritten(long value)
{
  bnNewestWritten = value;
}

QByteArray MSONHeader::getReserved() const
{
  return reserved;
}

void MSONHeader::setReserved(const QByteArray &value)
{
  reserved = value;
}

MSONHeader::MSONHeader()
{

}
