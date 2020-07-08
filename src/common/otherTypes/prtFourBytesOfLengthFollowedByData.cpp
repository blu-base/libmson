#include "prtFourBytesOfLengthFollowedByData.h"

quint32 prtFourBytesOfLengthFollowedByData::cb() const
{
    return m_cb;
}

void prtFourBytesOfLengthFollowedByData::setCb(const quint32& cb)
{
    m_cb = cb;
}

QByteArray prtFourBytesOfLengthFollowedByData::Data() const
{
    return m_Data;
}

void prtFourBytesOfLengthFollowedByData::setData(const QByteArray& Data)
{
    m_Data = Data;
}

void prtFourBytesOfLengthFollowedByData::deserialize(QDataStream& ds)
{
    ds >> m_cb;

    char* temp ;
    ds.readBytes(temp, m_cb);

    m_Data = QByteArray(temp,m_cb);
}

void prtFourBytesOfLengthFollowedByData::serialize(QDataStream& ds) const
{
    ds << m_cb;
    ds << m_Data;
}

void prtFourBytesOfLengthFollowedByData::toDebugString(QDebug dbg) const
{
    dbg << "prtFourBytesOfLengthFollowedByData: size: " << m_cb << '\n';
}

prtFourBytesOfLengthFollowedByData::prtFourBytesOfLengthFollowedByData()
{

}


QDataStream &operator<<(QDataStream &ds, const prtFourBytesOfLengthFollowedByData &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, prtFourBytesOfLengthFollowedByData &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const prtFourBytesOfLengthFollowedByData &obj) {
  obj.toDebugString(dbg);
  return dbg;
}
