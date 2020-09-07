#include "FileTime.h"

#include <QDate>
#include <QTime>

FileTime::FileTime() : m_time() {}

FileTime::FileTime(const QDateTime time) : m_time(time.date(), time.time()) {}

QDateTime FileTime::getTime() const { return m_time; }

void FileTime::setTime(const QDateTime time) { m_time = time; }

QDataStream &operator<<(QDataStream &ds, const FileTime &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, FileTime &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const FileTime &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

void FileTime::deserialize(QDataStream &ds) {
  quint32 fileTimeLow;
  quint32 fileTimeHigh;
  ds >> fileTimeLow;
  ds >> fileTimeHigh;

  const quint64 FileTimeMsecs =
      ((static_cast<quint64>(fileTimeHigh) << 32) + fileTimeLow) / 10000;

  m_time = origin() .addMSecs(FileTimeMsecs);
}

void FileTime::serialize(QDataStream &ds) const {

  const quint64 fileTime = 10000 * origin().msecsTo(m_time);

  const quint32 fileTimeLow(static_cast<quint32>(fileTime & 0xFFFFFFFF));
  const quint32 fileTimeHigh(fileTime >> 32);

  ds << fileTimeLow << fileTimeHigh;
}

void FileTime::toDebugString(QDebug dbg) const {
  dbg << "FileTime:\n" << m_time;
}
