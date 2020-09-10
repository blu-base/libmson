#ifndef TIME32_H
#define TIME32_H


#include <QtCore/qglobal.h>

#include <QDateTime>
#include <QDataStream>
#include <QDebug>
#include <QXmlStreamWriter>

namespace MSONcommon {

class Time32 {
private:
  QDateTime m_time;

public:
  Time32();
  Time32(const QDateTime time);

  friend QDataStream &operator<<(QDataStream &ds, const Time32 &obj);
  friend QDataStream &operator>>(QDataStream &ds, Time32 &obj);

  friend QDebug operator<<(QDebug dbg, const Time32 &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

  QDateTime getTime() const;
  void setTime(const QDateTime time);

private:
  void deserialize(QDataStream &ds);
  void serialize(QDataStream &ds) const;
  void toDebugString(QDebug dbg) const;

  static const quint64 utcoffset = 315576000;
};

} // namespace MSONcommon

#endif // TIME32_H
