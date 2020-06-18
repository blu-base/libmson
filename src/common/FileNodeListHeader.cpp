#include <QDataStream>
#include <QDebug>

#include "FileNodeList.h"
#include "FileNodeListHeader.h"

/**
 * @brief FileNodeListHeader::FileNodeListHeader
 */
FileNodeListHeader::FileNodeListHeader()
    : m_fileNodeListID{0x10}, m_nFragmentSequence{0}, m_parent{nullptr} {}

FileNodeListHeader::FileNodeListHeader(const FileNodeListHeader &fnl)
    : m_fileNodeListID{fnl.m_fileNodeListID},
      m_nFragmentSequence{fnl.m_nFragmentSequence}, m_parent{fnl.m_parent} {}

FileNodeListHeader::FileNodeListHeader(FileNodeListHeader &&fnl)
    : m_fileNodeListID{fnl.m_fileNodeListID},
      m_nFragmentSequence{fnl.m_nFragmentSequence}, m_parent{nullptr} {
  delete m_parent;
  m_parent = fnl.m_parent;
  fnl.m_parent = nullptr;
}

FileNodeListHeader::FileNodeListHeader(FileNodeList *parent)
    : m_fileNodeListID{0x10}, m_nFragmentSequence{0}, m_parent{parent} {}

bool FileNodeListHeader::isValid() {
  return isFileNodeListIDValid() && isNFragmentSequenceValid();
}

/**
 * @brief FileNodeListHeader::getNFragmentSequence
 * @return
 */

QDataStream &operator<<(QDataStream &ds, const FileNodeListHeader &obj) {
  // if byte order is big endian, change to little endian
  if (!ds.byteOrder()) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  ds << obj.uintMagic;
  ds << obj.m_fileNodeListID;
  ds << obj.m_nFragmentSequence;

  return ds;
};

QDataStream &operator>>(QDataStream &ds, FileNodeListHeader &obj) {

  // if byte order is big endian, change to little endian
  if (!ds.byteOrder()) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  ds.skipRawData(sizeof(obj.uintMagic));
  ds >> obj.m_fileNodeListID;
  ds >> obj.m_nFragmentSequence;

  return ds;
};

QDebug operator<<(QDebug dbg, const FileNodeListHeader &obj) {
  QDebugStateSaver saver(dbg);
  dbg.setAutoInsertSpaces(false);
  dbg.noquote();

  dbg << " FileNodeListHeader =====================================\n";
  dbg << " FileNodeListID:    "
      << QString("0x%1").arg(obj.m_fileNodeListID, 8, 16, QLatin1Char('0'))
      << (obj.isFileNodeListIDValid() ? "" : " INVALID") << "\n";
  dbg << " nFragmentSequence: " << obj.m_nFragmentSequence
      << (obj.isNFragmentSequenceValid() ? "" : " INVALID") << "\n";

  return dbg;
};

FileNodeListHeader &
FileNodeListHeader::operator=(const FileNodeListHeader &rhs) {
  if (this == &rhs) {
    return *this;
  }
  delete[] m_parent;
  m_parent = rhs.m_parent;

  m_fileNodeListID = rhs.m_fileNodeListID;
  m_nFragmentSequence = rhs.m_nFragmentSequence;

  return *this;
}

FileNodeListHeader &FileNodeListHeader::operator=(FileNodeListHeader &&rhs) {
  if (this == &rhs) {
    return *this;
  }

  delete m_parent;
  m_parent = rhs.m_parent;
  rhs.m_parent = nullptr;

  m_fileNodeListID = rhs.m_fileNodeListID;
  m_nFragmentSequence = rhs.m_nFragmentSequence;

  return *this;
}

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
