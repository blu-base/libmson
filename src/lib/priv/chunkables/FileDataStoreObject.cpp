#include "FileDataStoreObject.h"

#include <QDataStream>
#include <QDebug>

#include "../utils/Helper.h"


namespace libmson {
namespace priv {

FileDataStoreObject::FileDataStoreObject(
    const quint64 initialStp, const quint64 initialCb)
    : Chunkable(initialStp, initialCb), m_cbLength(), m_unused(), m_reserved(),
      m_padding()
{
}

QUuid FileDataStoreObject::getGuidHeader() const { return m_guidHeader; }

void FileDataStoreObject::setGuidHeader(const QUuid& guidHeader)
{
  m_guidHeader = guidHeader;
}

quint64 FileDataStoreObject::getCbLength() const { return m_cbLength; }

void FileDataStoreObject::setCbLength(const quint64& cbLength)
{
  m_cbLength = cbLength;
}

QByteArray FileDataStoreObject::getFileData() const { return m_FileData; }

void FileDataStoreObject::setFileData(const QByteArray& FileData)
{
  m_FileData = FileData;
}

QUuid FileDataStoreObject::getGuidFooter() const { return m_guidFooter; }

void FileDataStoreObject::setGuidFooter(const QUuid& guidFooter)
{
  m_guidFooter = guidFooter;
}

const quint64 FileDataStoreObject::sizeInFileBase =
    guidSizeInFile + sizeof(m_cbLength) + sizeof(m_unused) +
    sizeof(m_reserved) + guidSizeInFile;

quint64 FileDataStoreObject::getSizeInFile() const
{
  quint64 fileDataSizeInFile = ceilToMultiple(m_cbLength, 8);

  return sizeInFileBase + fileDataSizeInFile;
}

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

  ds >> m_guidHeader;
  ds >> m_cbLength;
  ds >> m_unused;
  ds >> m_reserved;

  /// \todo reading a large File to memory might be manipulated here
  uint len = ceilToMultiple(m_cbLength, 8);

  m_FileData = ds.device()->read(len);

  ds >> m_guidFooter;
}

void FileDataStoreObject::serialize(QDataStream& ds) const
{

  ds << m_guidHeader;
  ds << m_cbLength;
  ds << m_unused;
  ds << m_reserved;

  /// \todo reading a large File to memory might be manipulated here

  ds << m_FileData;

  QByteArray padding;
  ds << padding.append('\0', m_padding);

  ds << m_guidFooter;
}

// void FileDataStoreObject::toDebugString(QDebug& dbg) const
//{
//  dbg << "FileDataStoreObject: size: " << qStringHex(m_cbLength, 16) << '\n'
//      << "guidHeader: " << m_guidHeader << '\n'
//      << "guidFooter: " << m_guidFooter << '\n';
//}

quint64 libmson::priv::FileDataStoreObject::cb() const
{
  return getSizeInFile();
}

priv::RevisionStoreChunkType libmson::priv::FileDataStoreObject::getType() const
{
  return RevisionStoreChunkType::FileDataStoreObject;
}

} // namespace priv
} // namespace libmson
