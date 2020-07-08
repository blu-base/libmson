#include "PropertyType_TwoBytesOfData.h"

#include <QDataStream>
#include <QDebug>

QByteArray PropertyType_TwoBytesOfData::data() const { return m_data; }

void PropertyType_TwoBytesOfData::setData(const QByteArray &data) {
  m_data = data;
}

PropertyType_TwoBytesOfData::PropertyType_TwoBytesOfData() {}

void PropertyType_TwoBytesOfData::deserialize(QDataStream &ds) {

  char *raw;
  uint len = 2;
  ds.readBytes(raw, len);
  m_data = QByteArray(raw, len);
}

void PropertyType_TwoBytesOfData::serialize(QDataStream &ds) const {
  ds << m_data;
}

void PropertyType_TwoBytesOfData::toDebugString(QDebug dbg) const {}
