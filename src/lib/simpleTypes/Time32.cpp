#include "Time32.h"

#include <QDate>
#include <QTime>

namespace libmson {

Time32::Time32() : m_time() {}

Time32::Time32(const QDateTime& time) : m_time(time.date(), time.time()) {}

QDateTime Time32::getTime() const { return m_time; }

void Time32::setTime(const QDateTime& time)
{
  m_time = time;
  m_time.setOffsetFromUtc(utcoffset);
}

void Time32::deserialize(QDataStream& ds)
{
  quint32 time32;
  ds >> time32;

  m_time = QDateTime::fromTime_t(time32 + utcoffset);
}

void Time32::serialize(QDataStream& ds) const
{
  ds << static_cast<quint32>(m_time.toSecsSinceEpoch() - utcoffset);
}

// void Time32::writeLowLevelXml(QXmlStreamWriter& xmlWriter) const
// {
// xmlWriter.writeStartElement("Time32");
// xmlWriter.writeCharacters(getTime().toString("dd/MM/yyyy hh:mm:ss AP"));
// xmlWriter.writeEndElement();
// }

} // namespace libmson
