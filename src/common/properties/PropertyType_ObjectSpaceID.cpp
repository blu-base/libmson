#include "PropertyType_ObjectSpaceID.h"

#include <QDataStream>
#include <QDebug>

QByteArray PropertyType_ObjectSpaceID::data() const { return m_data; }

void PropertyType_ObjectSpaceID::setData(const QByteArray &data) {
  m_data = data;
}

PropertyType_ObjectSpaceID::PropertyType_ObjectSpaceID() {}

void PropertyType_ObjectSpaceID::deserialize(QDataStream &ds) {

  char *raw;
  uint len = 1;
  ds.readBytes(raw, len);
  m_data = QByteArray(raw, len);
}

void PropertyType_ObjectSpaceID::serialize(QDataStream &ds) const {
  ds << m_data;
}

void PropertyType_ObjectSpaceID::toDebugString(QDebug dbg) const {}
