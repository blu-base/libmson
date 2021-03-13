#include "PackagingHeader.h"

#include <QDebug>

namespace libmson {
namespace packStore {

const QUuid PackagingHeader::guidFileType("{7B5C52E4-D88C-4DA7-AEB1-5378D02996D3}");
const QUuid PackagingHeader::guidFileFormat( "{638DE92F-A6D4-4bc1-9A36-B3FC2511A5B7}");

PackagingHeader::PackagingHeader()
    : m_guidFileType(guidFileType), m_guidFile(QUuid::createUuid()),
      m_guidLegacyFileVersion(m_guidFile), m_guidFileFormat(guidFileFormat),
      m_reserved(0)
{
}

PackagingHeader::PackagingHeader(QUuid guidFile)
    : m_guidFileType(guidFileType), m_guidFile(guidFile),
      m_guidLegacyFileVersion(m_guidFile), m_guidFileFormat(guidFileFormat),
      m_reserved(0)
{
}

PackagingHeader::PackagingHeader(
    QUuid fileType, QUuid guidFile, QUuid guidLegacyFileVersion,
    QUuid fileFormat, quint32 reserved)
    : m_guidFileType(fileType), m_guidFile(guidFile),
      m_guidLegacyFileVersion(guidLegacyFileVersion),
      m_guidFileFormat(fileFormat), m_reserved(reserved)
{
}

QUuid PackagingHeader::getGuidFileType() const { return m_guidFileType; }

void PackagingHeader::setGuidFileType(QUuid fileType)
{
  m_guidFileType = fileType;
}

QUuid PackagingHeader::getGuidFile() const { return m_guidFile; }

void PackagingHeader::setGuidFile(QUuid guidFile) { m_guidFile = guidFile; }

QUuid PackagingHeader::getGuidLegacyFileVersion() const
{
  return m_guidLegacyFileVersion;
}

void PackagingHeader::setGuidLegacyFileVersion(QUuid guidLegacyFileVersion)
{
  m_guidLegacyFileVersion = guidLegacyFileVersion;
}

QUuid PackagingHeader::getGuidFileFormat() const { return m_guidFileFormat; }

void PackagingHeader::setGuidFileFormat(QUuid fileFormat)
{
  m_guidFileFormat = fileFormat;
}

quint32 PackagingHeader::getReserved() const { return m_reserved; }

void PackagingHeader::setReserved(quint32 reserved) { m_reserved = reserved; }

void PackagingHeader::deserialize(QDataStream& ds)
{
  ds >> m_guidFileType;
  if (m_guidFileType != guidFileType) {
    qCritical() << "The file type GUID" << m_guidFileType.toString()
                << "does not match the expected GUID:"
                << guidFileType.toString();
  }

  ds >> m_guidFile;

  ds >> m_guidLegacyFileVersion;

  ds >> m_guidFileFormat;
  if (m_guidFileFormat != guidFileFormat) {
    qCritical() << "The file format GUID" << m_guidFileFormat.toString()
                << "does not match the expected GUID:"
                << guidFileFormat.toString();
  }

  ds >> m_reserved;
}

void PackagingHeader::serialize(QDataStream& ds) const
{
  ds << guidFileType;
  ds << m_guidFile;
  ds << m_guidFile;
  ds << guidFileFormat;
}

} // namespace fsshttpb
} // namespace libmson
