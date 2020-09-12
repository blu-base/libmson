#include <QDataStream>
#include <QDebug>

#include "FileNodeList.h"
#include "FileNodeListHeader.h"
#include "helper/Helper.h"
namespace MSONcommon {
/**
 * @brief FileNodeListHeader::FileNodeListHeader
 */
FileNodeListHeader::FileNodeListHeader()
    : m_fileNodeListID{0x10}, m_nFragmentSequence{0} {}

bool FileNodeListHeader::isValid() {
  return isFileNodeListIDValid() && isNFragmentSequenceValid();
}

void FileNodeListHeader::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("FileNodeListHeader");

  xmlWriter.writeStartElement("fileNodeListID");
  xmlWriter.writeCharacters(QString::number(m_fileNodeListID));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("nFragmentSequence");
  xmlWriter.writeCharacters(QString::number(m_nFragmentSequence));
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
}


QDebug operator<<(QDebug dbg, const FileNodeListHeader &obj) {
  QDebugStateSaver saver(dbg);
  dbg.setAutoInsertSpaces(false);
  dbg.noquote();

  dbg << " FileNodeListHeader\n";
  dbg << " FileNodeListID:    "
      << QString("0x%1").arg(obj.m_fileNodeListID, 8, 16, QLatin1Char('0'))
      << (obj.isFileNodeListIDValid() ? "" : " INVALID") << "\n";
  dbg << " nFragmentSequence: " << obj.m_nFragmentSequence
      << (obj.isNFragmentSequenceValid() ? "" : " INVALID") << "\n";

  return dbg;
};

quint32 FileNodeListHeader::getNFragmentSequence() const {
  return m_nFragmentSequence;
}

void FileNodeListHeader::setNFragmentSequence(const quint32 &value) {
  m_nFragmentSequence = value;
}

/**
 * @brief FileNodeListHeader::isFileNodeListIDValid
 * @return whether the filenodelistid is individual in FileNodeList
 *
 * \todo implement validity check of FileNodeListHeader
 */
bool FileNodeListHeader::isNFragmentSequenceValid() const { return true; }

quint64 FileNodeListHeader::getUintMagic() { return uintMagic; }

quint32 FileNodeListHeader::getFileNodeListID() const {
  return m_fileNodeListID;
}

void FileNodeListHeader::setFileNodeListID(const quint32 &value) {
  m_fileNodeListID = value;
}

/**
 * @brief FileNodeListHeader::isFileNodeListIDValid
 * @return whether the filenodelistid is larger than 0x10 and indivudual in
 * filenodelist
 *
 * \todo implement validity check of FileNodeListHeader "The pair of
 * FileNodeListID and nFragmentSequence fields MUST be unique relative to other
 * FileNodeListFragment structures in the file."
 */
bool FileNodeListHeader::isFileNodeListIDValid() const {
  return m_fileNodeListID >= 0x10;
}
} // namespace MSONcommon


void MSONcommon::FileNodeListHeader::deserialize(QDataStream& ds)
{
  // if byte order is big endian, change to little endian
  if (!ds.byteOrder()) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  // skipping uintMagic
  ds.skipRawData(8);
  ds >> m_fileNodeListID;
  ds >> m_nFragmentSequence;
}

void MSONcommon::FileNodeListHeader::serialize(QDataStream& ds) const
{
  // if byte order is big endian, change to little endian
  if (!ds.byteOrder()) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  ds << uintMagic;
  ds << m_fileNodeListID;
  ds << m_nFragmentSequence;
}
