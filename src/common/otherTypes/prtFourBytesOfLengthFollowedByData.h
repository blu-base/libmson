#ifndef PRTFOURBYTESOFLENGTHFOLLOWEDBYDATA_H
#define PRTFOURBYTESOFLENGTHFOLLOWEDBYDATA_H

#include <QtCore/qglobal.h>

#include <QByteArray>
#include <QDataStream>
#include <QDebug>

#include "../IRevisionStoreFileObject.h"

namespace MSONcommon {

class prtFourBytesOfLengthFollowedByData : public IRevisionStoreFileObject {
private:
  quint32 m_cb;
  QByteArray m_Data;

public:
  prtFourBytesOfLengthFollowedByData() = default;
  virtual ~prtFourBytesOfLengthFollowedByData() = default;

  friend QDebug operator<<(QDebug dbg,
                           const prtFourBytesOfLengthFollowedByData &obj);

  quint32 cb() const;
  void setCb(const quint32 &cb);

  QByteArray Data() const;
  void setData(const QByteArray &Data);

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

 virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  void toDebugString(QDebug dbg) const;
};

} // namespace MSONcommon

#endif // PRTFOURBYTESOFLENGTHFOLLOWEDBYDATA_H
