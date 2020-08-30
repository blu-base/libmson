#ifndef PRTFOURBYTESOFLENGTHFOLLOWEDBYDATA_H
#define PRTFOURBYTESOFLENGTHFOLLOWEDBYDATA_H

#include <QtCore/qglobal.h>

#include <QByteArray>
#include <QDataStream>
#include <QDebug>

class prtFourBytesOfLengthFollowedByData {
private:
  quint32 m_cb;
  QByteArray m_Data;

public:
  prtFourBytesOfLengthFollowedByData();

  friend QDataStream &operator<<(QDataStream &ds,
                                 const prtFourBytesOfLengthFollowedByData &obj);
  friend QDataStream &operator>>(QDataStream &ds,
                                 prtFourBytesOfLengthFollowedByData &obj);

  friend QDebug operator<<(QDebug dbg,
                           const prtFourBytesOfLengthFollowedByData &obj);

  quint32 cb() const;
  void setCb(const quint32 &cb);

  QByteArray Data() const;
  void setData(const QByteArray &Data);

private:
  void deserialize(QDataStream &ds);
  void serialize(QDataStream &ds) const;
  void toDebugString(QDebug dbg) const;
};

#endif // PRTFOURBYTESOFLENGTHFOLLOWEDBYDATA_H
