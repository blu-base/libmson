#ifndef PACKAGESTOREFILE_H
#define PACKAGESTOREFILE_H

#include <QString>
#include <QtCore/qglobal.h>

//#include "packageTypes/DataElementPackage.h"
#include "packageTypes/PackagingHeader.h"
#include "packageTypes/PackagingStart.h"

//#include "packageTypes/StorageIndex.h"
//#include "packageTypes/StorageManifest.h"

namespace libmson {
namespace packStore {


class PackageStoreFile {
public:
  PackageStoreFile();


  friend class PackageStoreFileParser;

  PackagingHeader getHeader() const;
  void setHeader(const PackagingHeader& header);

  QString getFileName() const;
  void setFileName(const QString& fileName);

  bool getIsEncrypted() const;
  void setIsEncrypted(bool isEncrypted);

//  std::vector<std::shared_ptr<DataElement>> getElements() const;
//  void setElements(const std::vector<std::shared_ptr<DataElement>>& packages);

  fsshttpb::PackagingStart_WPtr_t getPackagingStart() const;
  void setPackagingStart(const fsshttpb::PackagingStart_SPtr_t& packagingStart);

private:
  /// File name such as "Notebook.one". Does not include any path information.
  QString m_fileName;

  bool m_isEncrypted = false;

  PackagingHeader m_header;

  fsshttpb::PackagingStart_SPtr_t m_packagingStart;

//  std::vector<DataElement_SPtr_t> m_elements;

//  StorageIndex_WPtr_t m_storageIndex;
//  StorageManifest_WPtr_t m_storageManifest;
};


typedef std::shared_ptr<PackageStoreFile> PackageStoreFile_SPtr_t;
typedef std::weak_ptr<PackageStoreFile> PackageStoreFile_WPtr_t;


} // namespace packStore
} // namespace libmson

#endif // PACKAGESTOREFILE_H
