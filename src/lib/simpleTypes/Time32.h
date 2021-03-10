#ifndef TIME32_H
#define TIME32_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDateTime>


#include "../interfaces/IStreamable.h"

namespace libmson {

/** @class Time32
 *  @brief
 *
 *  represents the simple type Time32 according to MS-ONE section 2.3.1
 *
 *  Uses QDateTime member for convenience.
 */
class Time32 : public IStreamable {
private:
  QDateTime m_time;

public:
  Time32();
  Time32(const QDateTime& time);

  QDateTime getTime() const;
  void setTime(const QDateTime& time);

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;

  /// UTC offset for 01-01-1980 12:00am
  static const quint64 utcoffset = 315576000;
};

} // namespace libmson

#endif // TIME32_H
