#ifndef FILETIME_H
#define FILETIME_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QXmlStreamWriter>

#include "../IRevisionStoreFileObject.h"

namespace MSONcommon {
/// Representing MS-DTYP section 2.3.3
class FileTime : public IRevisionStoreFileObject {
private:
  QDateTime m_time;

public:
  FileTime();
  FileTime(const QDateTime time);

  friend QDebug operator<<(QDebug dbg, const FileTime &obj);

  QDateTime getTime() const;
  void setTime(const QDateTime time);

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  void toDebugString(QDebug dbg) const;

  /// \todo figure out a way to make this a const value
  static QDateTime origin() {
    return QDateTime(QDate(1601, 1, 1), QTime(0, 0, 0, 0), Qt::UTC);
  }
};

} // namespace MSONcommon

#endif // FILETIME_H
