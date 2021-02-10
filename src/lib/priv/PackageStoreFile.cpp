#include "PackageStoreFile.h"

namespace libmson {
namespace packStore {

PackageStoreFile::PackageStoreFile() {}

PackagingStructure_SPtr_t PackageStoreFile::getHeader() const
{
  return m_header;
}

void PackageStoreFile::setHeader(const PackagingStructure_SPtr_t& header)
{
  m_header = header;
}

QString PackageStoreFile::getFileName() const { return m_fileName; }

void PackageStoreFile::setFileName(const QString& fileName)
{
  m_fileName = fileName;
}

bool PackageStoreFile::getIsEncrypted() const { return m_isEncrypted; }

void PackageStoreFile::setIsEncrypted(bool isEncrypted)
{
  m_isEncrypted = isEncrypted;
}

std::vector<std::shared_ptr<DataElement>> PackageStoreFile::getElements() const
{
  return m_elements;
}

void PackageStoreFile::setElements(
    const std::vector<std::shared_ptr<DataElement>>& elements)
{
  m_elements = elements;
}

} // namespace packStore
} // namespace libmson