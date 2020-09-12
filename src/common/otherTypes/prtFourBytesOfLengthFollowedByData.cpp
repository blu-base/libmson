#include "prtFourBytesOfLengthFollowedByData.h"

namespace MSONcommon {

quint32 prtFourBytesOfLengthFollowedByData::cb() const { return m_cb; }

void prtFourBytesOfLengthFollowedByData::setCb(const quint32 &cb) { m_cb = cb; }

QByteArray prtFourBytesOfLengthFollowedByData::Data() const { return m_Data; }

void prtFourBytesOfLengthFollowedByData::setData(const QByteArray &Data) {
  m_Data = Data;
}

void prtFourBytesOfLengthFollowedByData::deserialize(QDataStream &ds) {
  ds >> m_cb;

  m_Data = ds.device()->read(m_cb);
}

void prtFourBytesOfLengthFollowedByData::serialize(QDataStream &ds) const {
  ds << m_cb;
  ds << m_Data;
}

void prtFourBytesOfLengthFollowedByData::toDebugString(QDebug dbg) const {
  dbg << "prtFourBytesOfLengthFollowedByData: size: " << m_cb << '\n';
}

prtFourBytesOfLengthFollowedByData::prtFourBytesOfLengthFollowedByData() {}

QDebug operator<<(QDebug dbg, const prtFourBytesOfLengthFollowedByData &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

} // namespace MSONcommon
