#include "FileDataStoreObject.h"

#include <QDataStream>
#include <QDebug>

#include "../helper/Helper.h"

FileDataStoreObject::FileDataStoreObject()
    : m_cbLength(), m_unused(), m_reserved() {}

QDataStream &operator<<(QDataStream &ds, const FileDataStoreObject &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, FileDataStoreObject &obj) {

  ds.setByteOrder(QDataStream::LittleEndian);

  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const FileDataStoreObject &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

QUuid FileDataStoreObject::guidHeader() const { return m_guidHeader; }

void FileDataStoreObject::setGuidHeader(const QUuid &guidHeader) {
  m_guidHeader = guidHeader;
}

quint64 FileDataStoreObject::cbLength() const { return m_cbLength; }

void FileDataStoreObject::setCbLength(const quint64 &cbLength) {
  m_cbLength = cbLength;
}

QByteArray FileDataStoreObject::FileData() const { return m_FileData; }

void FileDataStoreObject::setFileData(const QByteArray &FileData) {
  m_FileData = FileData;
}

QUuid FileDataStoreObject::guidFooter() const { return m_guidFooter; }

void FileDataStoreObject::setGuidFooter(const QUuid &guidFooter) {
  m_guidFooter = guidFooter;
}

void FileDataStoreObject::deserialize(QDataStream &ds) {

  ds >> m_guidHeader;
  ds >> m_cbLength;
  ds >> m_unused;
  ds >> m_reserved;

  /// \todo reading a large File to memory might be manipulated here
  char *raw;

  uint len = roundUpMultiple(m_cbLength, 8);
  m_padding = len - m_cbLength;
  ds.readBytes(raw, len);

  m_FileData = QByteArray(raw);

  ds >> m_guidFooter;
}

void FileDataStoreObject::serialize(QDataStream &ds) const {

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

void FileDataStoreObject::toDebugString(QDebug dbg) const {
  dbg << "FileDataStoreObject: size: " << qStringHex(m_cbLength, 16) << '\n'
      << "guidHeader: " << m_guidHeader << '\n'
      << "guidFooter: " << m_guidFooter << '\n';
}
