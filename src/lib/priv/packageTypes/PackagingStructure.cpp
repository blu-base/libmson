#include "PackagingStructure.h"

namespace libmson {
namespace packStore {


PackagingStructure::PackagingStructure()
    : m_guidFileType(guidFileType), m_guidFile(QUuid::createUuid()),
      m_guidLegacyFileVersion(m_guidFile), m_guidFileFormat(guidFileFormat),
      m_storageIndex(), m_guidCellSchemaId(guidCellSchemaId_One)
{
}

QUuid PackagingStructure::getGuidFileType() const { return m_guidFileType; }

void PackagingStructure::setGuidFileType(const QUuid& guidFileType)
{
  m_guidFileType = guidFileType;
}

QUuid PackagingStructure::getGuidFile() const { return m_guidFile; }

void PackagingStructure::setGuidFile(const QUuid& guidFile)
{
  m_guidFile = guidFile;
}

QUuid PackagingStructure::getGuidLegacyFileVersion() const
{
  return m_guidLegacyFileVersion;
}

void PackagingStructure::setGuidLegacyFileVersion(
    const QUuid& guidLegacyFileVersion)
{
  m_guidLegacyFileVersion = guidLegacyFileVersion;
}

QUuid PackagingStructure::getGuidFileFormat() const { return m_guidFileFormat; }

void PackagingStructure::setGuidFileFormat(const QUuid& guidFileFormat)
{
  m_guidFileFormat = guidFileFormat;
}

CompactExtGuid PackagingStructure::getStorageIndex() const
{
  return m_storageIndex;
}

void PackagingStructure::setStorageIndex(const CompactExtGuid& storageIndex)
{
  m_storageIndex = storageIndex;
}

QUuid PackagingStructure::getGuidCellSchemaId() const
{
  return m_guidCellSchemaId;
}

void PackagingStructure::setGuidCellSchemaId(const QUuid& guidCellSchemaId)
{
  m_guidCellSchemaId = guidCellSchemaId;
}

StreamObjectHeader_SPtr_t PackagingStructure::getPackagingStart() const
{
  return m_packagingStart;
}

void PackagingStructure::setPackagingStart(
    const StreamObjectHeader_SPtr_t& packagingStart)
{
  m_packagingStart = packagingStart;
}


const QUuid
    PackagingStructure::guidFileType("{7B5C52E4-D88C-4DA7-AEB1-5378D02996D3}");

const QUuid PackagingStructure::guidFileFormat(
    "{638DE92F-A6D4-4bc1-9A36-B3FC2511A5B7}");

const QUuid PackagingStructure::guidCellSchemaId_One(
    "{1F937CB4-B26F-445F-B9F8-17E20160E461}");
const QUuid PackagingStructure::guidCellSchemaId_OneToc2(
    "{E4DBFD38-E5C7-408B-A8A1-0E7B421E1F5F}");

} // namespace packStore
} // namespace libmson
