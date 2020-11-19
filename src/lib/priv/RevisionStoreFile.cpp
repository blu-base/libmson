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

//#include "helper/CrcAlgorithms.h"


namespace libmson {
namespace priv {

QString RevisionStoreFile::getFileName() const { return m_fileName; }

void RevisionStoreFile::setFileName(const QString& fileName)
{
  m_fileName = fileName;
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

} // namespace priv
} // namespace libmson
