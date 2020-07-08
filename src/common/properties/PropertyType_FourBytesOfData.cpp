#include "PropertyType_FourBytesOfData.h"

#include <QDataStream>
#include <QDebug>

QByteArray PropertyType_FourBytesOfData::data() const { return m_data; }

void PropertyType_FourBytesOfData::setData(const QByteArray &data) {
  m_data = data;
}

PropertyType_FourBytesOfData::PropertyType_FourBytesOfData() {}

void PropertyType_FourBytesOfData::deserialize(QDataStream &ds) {

  char *raw;
  uint len = 4;
  ds.readBytes(raw, len);
  m_data = QByteArray(raw, len);
}

void PropertyType_FourBytesOfData::serialize(QDataStream &ds) const {
  ds << m_data;
}

void PropertyType_FourBytesOfData::toDebugString(QDebug dbg) const {}
