#ifndef FILETIME_H
#define FILETIME_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDateTime>

#include "../interfaces/IStreamable.h"

namespace libmson {
/// Representing MS-DTYP section 2.3.3
//
/** @class FileTime
 * @brief 64bit structure of FILETIME according to [MS-DTYP] section 2.3.3.
 * Count of 100ns (nanosecond) increments since 01-01-1601 UTC
 *
 * For convenience uses the QDateTime class of Qt. Since the accuracy of
 * QDateTime is is microseconds this class currently cuts of information...
 * \todo create a similar class to QDateTime with nanosecond accuracy or store
 * raw data instead, and only convert on method call
 *
 *
 */
class FileTime : public IStreamable {
private:
  QDateTime m_time;

public:
  FileTime();
  FileTime(const QDateTime& time);

  // let caller deal with endian
  FileTime(const quint32 fileTimeLow, const quint32 fileTimeHigh);

  QDateTime getTime() const;
  void setTime(const QDateTime& time);

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;

  /// \todo figure out a way to make this a const value
  static QDateTime origin()
  {
    return QDateTime(QDate(1601, 1, 1), QTime(0, 0, 0, 0), Qt::UTC);
  }
};

} // namespace libmson

#endif // FILETIME_H
