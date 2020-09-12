#ifndef FILETIME_H
#define FILETIME_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QXmlStreamWriter>

#include "../IDeserializable.h"
#include "../ISerializable.h"

namespace MSONcommon {
/// Representing MS-DTYP section 2.3.3
class FileTime : public ISerializable, public IDeserializable {
private:
  QDateTime m_time;

public:
  FileTime();
  FileTime(const QDateTime time);

  friend QDebug operator<<(QDebug dbg, const FileTime &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

  QDateTime getTime() const;
  void setTime(const QDateTime time);

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;
  void toDebugString(QDebug dbg) const;

  /// \todo figure out a way to make this a const value
  static QDateTime origin() {
    return QDateTime(QDate(1601, 1, 1), QTime(0, 0, 0, 0), Qt::UTC);
  }
};

} // namespace MSONcommon

#endif // FILETIME_H
