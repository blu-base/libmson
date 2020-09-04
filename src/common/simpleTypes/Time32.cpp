#include "Time32.h"

#include <QDate>
#include <QTime>

Time32::Time32() : m_time() {}

Time32::Time32(const QDateTime time) : m_time(time.date(), time.time()) {}

QDateTime Time32::getTime() const { return m_time; }

void Time32::setTime(const QDateTime time) {
  m_time = time;
  m_time.setOffsetFromUtc(utcoffset);
}

QDataStream &operator<<(QDataStream &ds, const Time32 &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, Time32 &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const Time32 &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

void Time32::deserialize(QDataStream &ds) {
  quint32 time32;
  ds >> time32;

  m_time = QDateTime::fromTime_t(time32 + utcoffset);
}

void Time32::serialize(QDataStream &ds) const {
  ds << static_cast<quint32>(m_time.toSecsSinceEpoch() - utcoffset);
}

void Time32::toDebugString(QDebug dbg) const { dbg << "Time32:\n" << m_time; }
