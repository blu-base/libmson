#include "PackageStoreFile.h"

namespace libmson {
namespace packStore {

PackageStoreFile::PackageStoreFile() {}

PackagingHeader PackageStoreFile::getHeader() const
{
  return m_header;
}

void PackageStoreFile::setHeader(const PackagingHeader& header)
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

fsshttpb::PackagingStart_WPtr_t PackageStoreFile::getPackagingStart() const
{
  return m_packagingStart;
}

void PackageStoreFile::setPackagingStart(const fsshttpb::PackagingStart_SPtr_t& packagingStart)
{
  m_packagingStart = packagingStart;
}

//std::vector<std::shared_ptr<DataElement>> PackageStoreFile::getElements() const
//{
//  return m_elements;
//}

//void PackageStoreFile::setElements(
//    const std::vector<std::shared_ptr<DataElement>>& elements)
//{
//  m_elements = elements;
//}

} // namespace packStore
} // namespace libmson
