#include "FileDataStoreObject.h"

#include "../utils/Helper.h"


namespace libmson {
namespace priv {

FileDataStoreObject::FileDataStoreObject(
    const quint64 initialStp, const quint64 initialCb)
    : Chunkable(initialStp, initialCb), m_cbLength(), m_unused(), m_reserved()
{
}

quint64 FileDataStoreObject::getCbLength() const { return m_cbLength; }

void FileDataStoreObject::setCbLength(const quint64& cbLength)
{
  m_isChanged = true;
  m_cbLength  = cbLength;
}

QByteArray FileDataStoreObject::getFileData() const { return m_FileData; }

void FileDataStoreObject::setFileData(const QByteArray& FileData)
{
  m_isChanged = true;
  m_FileData  = FileData;
}

const quint64 FileDataStoreObject::sizeInFileBase =
    guidSizeInFile + sizeof(m_cbLength) + sizeof(m_unused) +
    sizeof(m_reserved) + guidSizeInFile;


const QUuid
    FileDataStoreObject ::guidFooter("{71FBA722-0F79-4A0B-BB13-899256426B24}");
const QUuid
    FileDataStoreObject ::guidHeader("{BDE316E7-2665-4511-A4C4-8D4D0B7A9EAC}");

// void FileDataStoreObject::writeLowLevelXml(QXmlStreamWriter& xmlWriter) const
//{
//  xmlWriter.writeStartElement("FileDataStoreObject");
//  xmlWriter.writeAttribute("cb", QString::number(m_cbLength));

//  xmlWriter.writeStartElement("guidHeader");
//  xmlWriter.writeCharacters(m_guidHeader.toString());
//  xmlWriter.writeEndElement();

//  xmlWriter.writeStartElement("guidFooter");
//  xmlWriter.writeCharacters(m_guidFooter.toString());
//  xmlWriter.writeEndElement();

//  xmlWriter.writeStartElement("FileData");
//  xmlWriter.writeCharacters(m_FileData.toHex());
//  xmlWriter.writeEndElement();

//  xmlWriter.writeEndElement();
//}

void FileDataStoreObject::deserialize(QDataStream& ds)
{

  quint64 originalPos = ds.device()->pos();


  QUuid test;

  ds >> test;
  if (test != guidHeader) {
    qWarning("FileDataStoreObject header is invalid.");
  }

  ds >> m_cbLength;
  ds >> m_unused;
  ds >> m_reserved;

  /// \todo reading a large File to memory might be manipulated here
  //  m_FileData = QByteArray(m_cbLength, 0x0);
  //      .resize(m_cbLength);

  m_FileData = ds.device()->read(m_cbLength);

  quint64 footerStart =
      ceilToMultiple(originalPos + guidSizeInFile + 20 + m_cbLength, 8);
  ds.device()->seek(footerStart);


  ds >> test;

  if (test != guidFooter) {
    qWarning("FileDataStoreObject footer is invalid.");
  }
}

void FileDataStoreObject::serialize(QDataStream& ds) const
{
  quint64 originalPos = ds.device()->pos();

  ds << guidHeader;
  ds << m_cbLength;
  ds << m_unused;
  ds << m_reserved;

  /// \todo reading a large File to memory might be manipulated here


  ds.writeRawData(m_FileData.data(), m_cbLength);

  quint64 padStart = ds.device()->pos();
  quint64 padEnd =
      ceilToMultiple(originalPos + guidSizeInFile + 20 + m_cbLength, 8);

  quint8 remPad = padEnd - padStart;

  const quint8 zeros8{};
  while (remPad > 0) {
    ds << zeros8;
    --remPad;
  }

  ds << guidFooter;
}

// void FileDataStoreObject::toDebugString(QDebug& dbg) const
//{
//  dbg << "FileDataStoreObject: size: " << qStringHex(m_cbLength, 16) << '\n'
//      << "guidHeader: " << m_guidHeader << '\n'
//      << "guidFooter: " << m_guidFooter << '\n';
//}

quint64 libmson::priv::FileDataStoreObject::cb() const
{
  quint64 fileDataSizeInFile =
      ceilToMultiple(guidSizeInFile + 20 + m_cbLength, 8);

  return fileDataSizeInFile + guidSizeInFile;
}

priv::RevisionStoreChunkType libmson::priv::FileDataStoreObject::getType() const
{
  return RevisionStoreChunkType::FileDataStoreObject;
}

} // namespace priv
} // namespace libmson
