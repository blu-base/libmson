#ifndef PACKAGINGSTRUCTURE_H
#define PACKAGINGSTRUCTURE_H

#include <memory>

#include <QUuid>
#include <QtCore/qglobal.h>

#include "../commonTypes/CompactExtGuid.h"
#include "StreamObjectHeader.h"

namespace libmson {
namespace packStore {


class PackagingStructure {
public:
  PackagingStructure();


  static const QUuid guidFileType;
  static const QUuid guidFileFormat;
  static const QUuid guidCellSchemaId_One;
  static const QUuid guidCellSchemaId_OneToc2;


  QUuid getGuidFileType() const;
  void setGuidFileType(const QUuid& guidFileType);

  QUuid getGuidFile() const;
  void setGuidFile(const QUuid& guidFile);

  QUuid getGuidLegacyFileVersion() const;
  void setGuidLegacyFileVersion(const QUuid& guidLegacyFileVersion);

  QUuid getGuidFileFormat() const;
  void setGuidFileFormat(const QUuid& guidFileFormat);

  CompactExtGuid getStorageIndex() const;
  void setStorageIndex(const CompactExtGuid& storageIndex);

  QUuid getGuidCellSchemaId() const;
  void setGuidCellSchemaId(const QUuid& guidCellSchemaId);


  StreamObjectHeader_SPtr_t getPackagingStart() const;
  void setPackagingStart(const StreamObjectHeader_SPtr_t& packagingStart);


  friend class PackageStoreFileParser;

private:
  QUuid m_guidFileType;
  QUuid m_guidFile;
  QUuid m_guidLegacyFileVersion; /** should have the same value as m_guidFile */
  QUuid m_guidFileFormat;

  StreamObjectHeader_SPtr_t m_packagingStart;

  CompactExtGuid m_storageIndex;
  QUuid m_guidCellSchemaId;
};

typedef std::shared_ptr<PackagingStructure> PackagingStructure_SPtr_t;
typedef std::weak_ptr<PackagingStructure> PackagingStructure_WPtr_t;

} // namespace packStore
} // namespace libmson

#endif // PACKAGINGSTRUCTURE_H
