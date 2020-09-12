#ifndef PRTFOURBYTESOFLENGTHFOLLOWEDBYDATA_H
#define PRTFOURBYTESOFLENGTHFOLLOWEDBYDATA_H

#include <QtCore/qglobal.h>

#include <QByteArray>
#include <QDataStream>
#include <QDebug>

#include "../IDeserializable.h"
#include "../ISerializable.h"

namespace MSONcommon {

class prtFourBytesOfLengthFollowedByData : public ISerializable, public IDeserializable {
private:
  quint32 m_cb;
  QByteArray m_Data;

public:
  prtFourBytesOfLengthFollowedByData();

  friend QDebug operator<<(QDebug dbg,
                           const prtFourBytesOfLengthFollowedByData &obj);

  quint32 cb() const;
  void setCb(const quint32 &cb);

  QByteArray Data() const;
  void setData(const QByteArray &Data);

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  void toDebugString(QDebug dbg) const;
};

} // namespace MSONcommon

#endif // PRTFOURBYTESOFLENGTHFOLLOWEDBYDATA_H
