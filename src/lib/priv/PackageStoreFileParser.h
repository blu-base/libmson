#ifndef PACKAGESTOREFILEPARSER_H
#define PACKAGESTOREFILEPARSER_H

#include <memory>

#include <QtCore/qglobal.h>

#include "packageTypes/DataElementPackage.h"
#include "packageTypes/PackagingStructure.h"
#include "packageTypes/StreamObjectHeader.h"
#include "packageTypes/StreamObjectHeaderEnd.h"

#include "packageTypes/CellManifest.h"
#include "packageTypes/DataElementFragment.h"
#include "packageTypes/ObjectDataBLOB.h"
#include "packageTypes/ObjectGroup.h"
#include "packageTypes/RevisionManifest.h"
#include "packageTypes/StorageIndex.h"
#include "packageTypes/StorageManifest.h"

#include "commonTypes/CellId.h"
#include "commonTypes/CompactExtGuid.h"
#include "packageTypes/DataElement.h"

namespace libmson {
namespace packStore {

class PackageStoreFile;

class PackageStoreFileParser {
private:
  QDataStream& m_ds;
  std::shared_ptr<PackageStoreFile> m_file;

public:
  PackageStoreFileParser(QDataStream& inputStream, const QString& fileName);


  std::shared_ptr<PackageStoreFile> parse();

private:
  PackagingStructure_SPtr_t parsePackagingStructure(QDataStream& ds);

  StreamObjectHeader_SPtr_t parseStreamObjectHeader(QDataStream& ds);

  StreamObjectHeaderEnd_SPtr_t parseStreamObjectHeaderEnd(
      const StreamObjectHeader_SPtr_t& header, QDataStream& ds);

  DataElementPackage_SPtr_t parseDataElementPackage(QDataStream& ds);

  //  std::vector<DataElementPackage_SPtr_t> parseDataElementTree(QDataStream&
  //  ds);


  /*--------------------------------------------------------------------------*/
  /* data element types */
  /*--------------------------------------------------------------------------*/
  DataElement_SPtr_t parseDataElement(QDataStream& ds);
  /*--------------------------------------------------------------------------*/
  StorageIndex_SPtr_t parseStorageIndex(QDataStream& ds);
  StorageManifest_SPtr_t parseStorageManifest(QDataStream& ds);
  CellManifest_SPtr_t parseCellManifest(QDataStream& ds);
  RevisionManifest_SPtr_t parseRevisionManifest(QDataStream& ds);
  ObjectGroup_SPtr_t parseObjectGroup(QDataStream& ds);
  ObjectDataBLOB_SPtr_t parseObjectDataBLOB(QDataStream& ds);
  DataElementFragment_SPtr_t parseDataElementFragment(QDataStream& ds);


  static const QUuid storageManifestSchemeGuid_One;
  static const QUuid storageManifestSchemeGuid_OneToc2;
  static const CompactExtGuid storageManifestRootEGuid;
  static const CellId storageManifestRootCellId;
  static const CompactExtGuid storageManifestDataRootEGuid;
  static const CompactExtGuid storageManifestDataRootCellIdParticle;
};

} // namespace packStore
} // namespace libmson

#endif // PACKAGESTOREFILEPARSER_H
