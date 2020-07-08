#include "PropertyType_FourBytesOfLengthFollowedByData.h"

#include <QDataStream>
#include <QDebug>

prtArrayOfPropertyValues
PropertyType_FourBytesOfLengthFollowedByData::data() const {
  return m_data;
}

void PropertyType_FourBytesOfLengthFollowedByData::setData(
    const prtArrayOfPropertyValues &data) {
  m_data = data;
}

PropertyType_FourBytesOfLengthFollowedByData::
    PropertyType_FourBytesOfLengthFollowedByData() {}

void PropertyType_FourBytesOfLengthFollowedByData::deserialize(
    QDataStream &ds) {

  ds >> m_data;
}

void PropertyType_FourBytesOfLengthFollowedByData::serialize(
    QDataStream &ds) const {
  ds << m_data;
}

void PropertyType_FourBytesOfLengthFollowedByData::toDebugString(
    QDebug dbg) const {}
