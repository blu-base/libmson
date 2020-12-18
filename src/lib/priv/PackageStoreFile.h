#ifndef PACKAGESTOREFILE_H
#define PACKAGESTOREFILE_H

#include <QString>
#include <QtCore/qglobal.h>

#include "packageTypes/DataElementPackage.h"
#include "packageTypes/PackagingStructure.h"

namespace libmson {
namespace packStore {

class PackageStoreFile {
public:
  PackageStoreFile();


  friend class PackageStoreFileParser;

  PackagingStructure_SPtr_t getHeader() const;
  void setHeader(const PackagingStructure_SPtr_t& header);

  QString getFileName() const;
  void setFileName(const QString& fileName);

  bool getIsEncrypted() const;
  void setIsEncrypted(bool isEncrypted);

  std::vector<std::shared_ptr<DataElement>> getElements() const;
  void setElements(const std::vector<std::shared_ptr<DataElement>>& packages);

private:
  /// File name such as "Notebook.one". Does not include any path information.
  QString m_fileName;

  bool m_isEncrypted = false;

  PackagingStructure_SPtr_t m_header;

  std::vector<DataElement_SPtr_t> m_elements;
};


} // namespace packStore
} // namespace libmson

#endif // PACKAGESTOREFILE_H
