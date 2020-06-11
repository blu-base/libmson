#ifndef MSONHEADER_H
#define MSONHEADER_H



#include <QtCore/qglobal.h>
#include <QUuid>
#include <QByteArray>

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
    long ffvLastCode; // ffvLastCodeThatWroteToThisFile  // long?
    long ffvNewestCode; // ffvOldestCodeThatHasWrittenToThisFile
    long ffvOldestCode; // ffvNewestCodeThatHasWrittenToThisFile
    long ffvOldestReader; // ffvOldestCodeThatMayReadThisFile
    FileChunkReference fcrLegacyFreeChunkList;
    FileChunkReference fcrLegacyTransactionLog;
    long cTransactionsInLog;
    long cbLegacyExpectedFileLength;
    long rgbPlaceholder;
    FileChunkReference fcrLegacyFileNodeListRoot;
    long cbLegacyFreeSpaceInFreeChunkList;
    short fNeedsDefrag; // must be ignored
    short fRepairedFile; // must be ignored
    short fNeedsGarbageCollect; // must be ignored
    unsigned short fHasNoEmbeddedFileObjects; // must be ignored
    QUuid guidAncestor;
    long crcName;
    FileChunkReference fcrHashedChunkList;
    FileChunkReference fcrTransactionLog;
    FileChunkReference fcrFileNodeListRoot;
    FileChunkReference fcrFreeChunkList;
    long cbExpectedFileLength;
    long cbFreeSpaceInFreeChunkList;
    QUuid guidFileVersion;
    long nFileVersionGeneration;
    QUuid guidDenyReadFileVersion;
    long grfDebugLogFlags;
    FileChunkReference fcrDebugLog;
    FileChunkReference fcrAllocVerificationFreeChunkList;
    long bnCreated;
    long bnLastWroteToThisFile;
    long bnOldestWritten;
    long bnNewestWritten;
    QByteArray reserved;
public:
  MSONHeader();





  QUuid getGuidFile() const;
  void setGuidFile(const QUuid &value);
  QUuid getGuidFileType() const;
  void setGuidFileType(const QUuid &value);
  QUuid getGuidLegacyFileVersion() const;
  void setGuidLegacyFileVersion(const QUuid &value);
  QUuid getGuidFileFormat() const;
  void setGuidFileFormat(const QUuid &value);
  long getFfvLastCode() const;
  void setFfvLastCode(long value);
  long getFfvNewestCode() const;
  void setFfvNewestCode(long value);
  long getFfvOldestCode() const;
  void setFfvOldestCode(long value);
  long getFfvOldestReader() const;
  void setFfvOldestReader(long value);
  FileChunkReference getFcrLegacyFreeChunkList() const;
  void setFcrLegacyFreeChunkList(const FileChunkReference &value);
  FileChunkReference getFcrLegacyTransactionLog() const;
  void setFcrLegacyTransactionLog(const FileChunkReference &value);
  long getCTransactionsInLog() const;
  void setCTransactionsInLog(long value);
  long getCbLegacyExpectedFileLength() const;
  void setCbLegacyExpectedFileLength(long value);
  long getRgbPlaceholder() const;
  void setRgbPlaceholder(long value);
  FileChunkReference getFcrLegacyFileNodeListRoot() const;
  void setFcrLegacyFileNodeListRoot(const FileChunkReference &value);
  long getCbLegacyFreeSpaceInFreeChunkList() const;
  void setCbLegacyFreeSpaceInFreeChunkList(long value);
  short getFNeedsDefrag() const;
  void setFNeedsDefrag(short value);
  short getFRepairedFile() const;
  void setFRepairedFile(short value);
  short getFNeedsGarbageCollect() const;
  void setFNeedsGarbageCollect(short value);
  unsigned short getFHasNoEmbeddedFileObjects() const;
  void setFHasNoEmbeddedFileObjects(unsigned short value);
  QUuid getGuidAncestor() const;
  void setGuidAncestor(const QUuid &value);
  long getCrcName() const;
  void setCrcName(long value);
  FileChunkReference getFcrHashedChunkList() const;
  void setFcrHashedChunkList(const FileChunkReference &value);
  FileChunkReference getFcrTransactionLog() const;
  void setFcrTransactionLog(const FileChunkReference &value);
  FileChunkReference getFcrFileNodeListRoot() const;
  void setFcrFileNodeListRoot(const FileChunkReference &value);
  FileChunkReference getFcrFreeChunkList() const;
  void setFcrFreeChunkList(const FileChunkReference &value);
  long getCbExpectedFileLength() const;
  void setCbExpectedFileLength(long value);
  long getCbFreeSpaceInFreeChunkList() const;
  void setCbFreeSpaceInFreeChunkList(long value);
  QUuid getGuidFileVersion() const;
  void setGuidFileVersion(const QUuid &value);
  long getNFileVersionGeneration() const;
  void setNFileVersionGeneration(long value);
  QUuid getGuidDenyReadFileVersion() const;
  void setGuidDenyReadFileVersion(const QUuid &value);
  long getGrfDebugLogFlags() const;
  void setGrfDebugLogFlags(long value);
  FileChunkReference getFcrDebugLog() const;
  void setFcrDebugLog(const FileChunkReference &value);
  FileChunkReference getFcrAllocVerificationFreeChunkList() const;
  void setFcrAllocVerificationFreeChunkList(const FileChunkReference &value);
  long getBnCreated() const;
  void setBnCreated(long value);
  long getBnLastWroteToThisFile() const;
  void setBnLastWroteToThisFile(long value);
  long getBnOldestWritten() const;
  void setBnOldestWritten(long value);
  long getBnNewestWritten() const;
  void setBnNewestWritten(long value);
  QByteArray getReserved() const;
  void setReserved(const QByteArray &value);
};




#endif // MSONHEADER_H
