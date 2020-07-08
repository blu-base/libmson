#include "PropertyType_ArrayOfPropertyValues.h"

#include <QDataStream>
#include <QDebug>

prtArrayOfPropertyValues PropertyType_ArrayOfPropertyValues::data() const {
  return m_data;
}

void PropertyType_ArrayOfPropertyValues::setData(
    const prtArrayOfPropertyValues &data) {
  m_data = data;
}

PropertyType_ArrayOfPropertyValues::PropertyType_ArrayOfPropertyValues() {}

/// \todo implement
void PropertyType_ArrayOfPropertyValues::deserialize(QDataStream &ds) {}

void PropertyType_ArrayOfPropertyValues::serialize(QDataStream &ds) const {
  ds << m_data;
}

void PropertyType_ArrayOfPropertyValues::toDebugString(QDebug dbg) const {}
