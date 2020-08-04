#include "PropertyType_ArrayNumber.h"

#include <QDataStream>
#include <QDebug>

std::vector<CompactID> PropertyType_ArrayNumber::data() const {
  return m_data;
}

void PropertyType_ArrayNumber::setData(
    const std::vector<CompactID> &data) {}

quint32 PropertyType_ArrayNumber::cCIDs() const { return m_cCIDs; }

void PropertyType_ArrayNumber::setCCIDs(const quint32 &cCIDs) {
  m_cCIDs = cCIDs;
}

PropertyType_ArrayNumber::PropertyType_ArrayNumber() : m_cCIDs{} {}

void PropertyType_ArrayNumber::deserialize(QDataStream &ds) {
  ds >> m_cCIDs;

  CompactID temp;
  for (size_t i{0}; i < m_cCIDs; i++) {
    ds >> temp;
    m_data.push_back(temp);
  }
}

void PropertyType_ArrayNumber::serialize(QDataStream &ds) const {
  ds << m_cCIDs;

  for (size_t i{0}; i < m_cCIDs; i++) {
    ds << m_data.at(i);
  }
}

void PropertyType_ArrayNumber::toDebugString(QDebug dbg) const {}
