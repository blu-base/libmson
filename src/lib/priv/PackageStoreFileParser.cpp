#include "PackageStoreFileParser.h"

#include <QDebug>

#include "PackageStoreFile.h"


namespace libmson {
namespace packStore {
PackageStoreFileParser::PackageStoreFileParser(
    QDataStream& inputStream, const QString& fileName)
    : m_ds(inputStream), m_file(std::make_shared<PackageStoreFile>())
{
  m_file->m_fileName = fileName;
}

std::shared_ptr<PackageStoreFile> PackageStoreFileParser::parse()
{
  auto header = parsePackagingStructure(m_ds);

  m_file->m_packages = parseDataElementTree(m_ds);
  //  parseStreamObjectHeaderEnd(header->getPackagingStart(), m_ds);


  return m_file;
}

PackagingStructure_SPtr_t
PackageStoreFileParser::parsePackagingStructure(QDataStream& ds)
{
  // if byte order is big endian, change to little endian
  if (ds.byteOrder() == QDataStream::BigEndian) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  auto header = std::make_shared<PackagingStructure>();

  m_file->m_header = header;

  ds >> header->m_guidFileType;
  if (header->m_guidFileType != PackagingStructure::guidFileType) {
    qFatal("guidFileType of the PackagingStructure is invalid.");
  }

  ds >> header->m_guidFile;
  ds >> header->m_guidLegacyFileVersion;
  if (header->m_guidFile != header->m_guidLegacyFileVersion) {
    qDebug("Irregular PackagingStructure: guidFile and "
           "guidLegacyFileVersion are different.");
  }

  ds >> header->m_guidFileFormat;
  if (header->m_guidFileFormat != PackagingStructure::guidFileFormat) {
    qFatal("guidFileFormat of the PackagingStructure is invalid.");
  }

  uint32_t reserved;
  ds >> reserved;

  if (reserved != 0) {
    qDebug("There is a non-zero reserved block in the PackagingStructure");
  }

  auto packageStart = std::make_shared<StreamObjectHeader>();
  ds >> *packageStart;
  header->m_packagingStart = packageStart;

  ds >> header->m_storageIndex;
  ds >> header->m_guidCellSchemaId;

  if (header->m_guidCellSchemaId != PackagingStructure::guidCellSchemaId_One &&
      header->m_guidCellSchemaId !=
          PackagingStructure::guidCellSchemaId_OneToc2) {
    qFatal("m_guidCellSchemaId of the Packaging Structure is neither .one nor "
           ".onetoc");
  }

  return header;
}

StreamObjectHeader_SPtr_t
PackageStoreFileParser::parseStreamObjectHeader(QDataStream& ds)
{
  auto header = std::make_shared<StreamObjectHeader>();
  ds >> *header;
  return header;
}

StreamObjectHeaderEnd_SPtr_t PackageStoreFileParser::parseStreamObjectHeaderEnd(
    const StreamObjectHeader_SPtr_t& header, QDataStream& ds)
{
  auto footer = std::make_shared<StreamObjectHeaderEnd>(header);
  header->setEnd(footer);
  ds >> *footer;

  return footer;
}

DataElementPackage_SPtr_t
PackageStoreFileParser::parseDataElementPackage(QDataStream& ds)
{
  quint64 pos  = ds.device()->pos();
  auto package = std::make_shared<DataElementPackage>();

  auto packageStart = std::make_shared<StreamObjectHeader>();
  ds >> *packageStart;
  package->m_header = packageStart;

  // reserved byte;
  ds.skipRawData(1);


  //  ds.skipRawData(packageStart->getLength());


  //  if (packStore::compoundType.at(packageStart->getType()) == 1) {
  //    parseStreamObjectHeaderEnd(packageStart, ds);
  //  }

  return package;
}

std::vector<DataElementPackage_SPtr_t>
PackageStoreFileParser::parseDataElementTree(QDataStream& ds)
{
  std::vector<DataElementPackage_SPtr_t> vec;


  char peek[1];

  qint64 peeking = ds.device()->peek(peek, 1);


  while ((static_cast<uint8_t>(peek[0]) & 0x1) != 1) {

    auto composite   = std::make_shared<DataElementPackage>();
    composite->m_stp = ds.device()->pos();

    uint8_t streamObjectHeaderType = static_cast<uint8_t>(peek[0]) & 0x3;
    if (!(streamObjectHeaderType == 0) && !(streamObjectHeaderType == 2)) {
      qDebug() << "Potentially incorrectly formated StreamObjectHeader ahead";
    }
    auto packageStart = std::make_shared<StreamObjectHeader>();
    ds >> *packageStart;
    composite->m_header = packageStart;

    composite->m_data = ds.device()->read(composite->m_header->getLength());
    vec.push_back(composite);
    if (packStore::compoundType.at(packageStart->getType()) == 1) {
      composite->m_children = parseDataElementTree(ds);

      if (ds.device()->peek(peek, 1) == 0) {
        qDebug() << "Ran out of bytes";
        break;
      }
      parseStreamObjectHeaderEnd(composite->m_header, ds);
    }
    peeking = ds.device()->peek(peek, 1);

    if (peeking == 0) {
      qDebug() << "Ran out of bytes";
      break;
    }
  }


  return vec;
}


} // namespace packStore
} // namespace libmson
