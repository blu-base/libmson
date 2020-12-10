#include "FileTime.h"

#include <QDate>
#include <QTime>

namespace libmson {

FileTime::FileTime() : m_time() {}

FileTime::FileTime(const QDateTime& time) : m_time(time.date(), time.time()) {}

FileTime::FileTime(const quint32 fileTimeLow, const quint32 fileTimeHigh)
{
  const quint64 FileTimeMsecs =
      ((static_cast<quint64>(fileTimeHigh) << 32) + fileTimeLow) / 10000;

  m_time = origin().addMSecs(FileTimeMsecs);
}

QDateTime FileTime::getTime() const { return m_time; }

void FileTime::setTime(const QDateTime& time) { m_time = time; }

void FileTime::deserialize(QDataStream& ds)
{
  quint32 fileTimeLow;
  quint32 fileTimeHigh;
  ds >> fileTimeLow;
  ds >> fileTimeHigh;

  const quint64 FileTimeMsecs =
      ((static_cast<quint64>(fileTimeHigh) << 32) + fileTimeLow) / 10000;

  m_time = origin().addMSecs(FileTimeMsecs);
}

void FileTime::serialize(QDataStream& ds) const
{

  const quint64 fileTime = 10000 * origin().msecsTo(m_time);

  const quint32 fileTimeLow(static_cast<quint32>(fileTime & 0xFFFFFFFF));
  const quint32 fileTimeHigh(fileTime >> 32);

  ds << fileTimeLow << fileTimeHigh;
}

// void FileTime::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
//   xmlWriter.writeStartElement("FileTime");
//   xmlWriter.writeCharacters(getTime().toString("dd/MM/yyyy hh:mm:ss AP"));
//   xmlWriter.writeEndElement();
// }

} // namespace libmson
