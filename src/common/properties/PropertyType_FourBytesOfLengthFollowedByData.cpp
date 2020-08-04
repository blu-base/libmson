#include "PropertyType_FourBytesOfLengthFollowedByData.h"

#include <QDataStream>
#include <QDebug>

QByteArray
PropertyType_FourBytesOfLengthFollowedByData::data() const {
  return m_data;
}

void PropertyType_FourBytesOfLengthFollowedByData::setData(
    const QByteArray &data) {
  m_data = data;
}

quint32 PropertyType_FourBytesOfLengthFollowedByData::cb() const
{
    return m_cb;
}

void PropertyType_FourBytesOfLengthFollowedByData::setCb(const quint32& cb)
{
    m_cb = cb;
}

PropertyType_FourBytesOfLengthFollowedByData::
PropertyType_FourBytesOfLengthFollowedByData() {}

void PropertyType_FourBytesOfLengthFollowedByData::deserialize(
        QDataStream &ds) {

  ds >> m_cb;

  char * raw = nullptr;
  ds.readRawData(raw, m_cb);
  m_data.fromRawData(raw,m_cb);
}

void PropertyType_FourBytesOfLengthFollowedByData::serialize(
    QDataStream &ds) const {
    ds << m_cb;
  ds << m_data;
}

void PropertyType_FourBytesOfLengthFollowedByData::toDebugString(
    QDebug dbg) const {}
