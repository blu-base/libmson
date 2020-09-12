#ifndef TIME32_H
#define TIME32_H


#include <QtCore/qglobal.h>

#include <QDateTime>
#include <QDataStream>
#include <QDebug>
#include <QXmlStreamWriter>

#include "../IDeserializable.h"
#include "../ISerializable.h"

namespace MSONcommon {

class Time32: public ISerializable, public IDeserializable {
private:
  QDateTime m_time;

public:
  Time32();
  Time32(const QDateTime time);

  friend QDebug operator<<(QDebug dbg, const Time32 &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

  QDateTime getTime() const;
  void setTime(const QDateTime time);

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  void toDebugString(QDebug dbg) const;

  static const quint64 utcoffset = 315576000;
};

} // namespace MSONcommon

#endif // TIME32_H
