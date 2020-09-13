#ifndef TIME32_H
#define TIME32_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QXmlStreamWriter>

#include "../IRevisionStoreFileObject.h"

namespace MSONcommon {

class Time32 : public IRevisionStoreFileObject {
private:
  QDateTime m_time;

public:
  Time32();
  Time32(const QDateTime time);

  QDateTime getTime() const;
  void setTime(const QDateTime time);

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;

  static const quint64 utcoffset = 315576000;
};

} // namespace MSONcommon

#endif // TIME32_H
