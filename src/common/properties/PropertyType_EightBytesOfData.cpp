#include "PropertyType_EightBytesOfData.h"

#include <QDataStream>
#include <QDebug>

QByteArray PropertyType_EightBytesOfData::data() const { return m_data; }

void PropertyType_EightBytesOfData::setData(const QByteArray &data) {
  m_data = data;
}

PropertyType_EightBytesOfData::PropertyType_EightBytesOfData() {}

void PropertyType_EightBytesOfData::deserialize(QDataStream &ds) {

  char *raw;
  uint len = 8;
  ds.readBytes(raw, len);
  m_data = QByteArray(raw, len);
}

void PropertyType_EightBytesOfData::serialize(QDataStream &ds) const {
  ds << m_data;
}

void PropertyType_EightBytesOfData::toDebugString(QDebug dbg) const {}
