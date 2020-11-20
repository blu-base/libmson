#include "RevisionStoreFile.h"

#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QUuid>

//#include "chunkables/Chunkable.h"
//#include "chunkables/FileNode.h"
//#include "chunkables/FileNodeListFragment.h"
//#include "chunkables/FreeChunk.h"
//#include "chunkables/FreeChunkListFragment.h"
//#include "chunkables/RevisionStoreFileHeader.h"

#include "utils/CrcAlgorithms.h"


namespace libmson {
namespace priv {

QString RevisionStoreFile::getFileName() const { return m_fileName; }

void RevisionStoreFile::setFileName(const QString& fileName)
{
  m_header->setIsChanged();
  m_fileName = fileName;
  m_header->setCrcName(Crc32::computeCrcName(m_fileName));
}

RevisionStoreFileHeader_SPtr_t RevisionStoreFile::getHeader() const
{
  return m_header;
}

void RevisionStoreFile::setHeader(const RevisionStoreFileHeader_SPtr_t& header)
{
  m_header->setIsChanged();
  m_header = header;
}

std::vector<TransactionLogFragment_WPtr_t>
RevisionStoreFile::getTransactionLogs() const
{
  return m_transactionLogs;
}

void RevisionStoreFile::setTransactionLogs(
    const std::vector<TransactionLogFragment_WPtr_t>& transactionLogs)
{
  m_transactionLogs = transactionLogs;
}

FileNode_WPtr_t RevisionStoreFile::getFileDataStoreListReference() const
{
  return m_fileDataStoreListReference;
}

void RevisionStoreFile::setFileDataStoreListReference(
    const FileNode_WPtr_t& fileDataStoreListReference)
{
  m_fileDataStoreListReference = fileDataStoreListReference;
}

void RevisionStoreFile::setChunks(const std::list<Chunkable_SPtr_t>& chunks)
{
  m_chunks = chunks;
}

} // namespace priv
} // namespace libmson
