#include "PropertyType_PropertySet.h"

#include <QDataStream>
#include <QDebug>

PropertySet PropertyType_PropertySet::data() const { return m_data; }

void PropertyType_PropertySet::setData(const PropertySet &data) {
  m_data = data;
}

PropertyType_PropertySet::PropertyType_PropertySet() {}

void PropertyType_PropertySet::deserialize(QDataStream &ds) { ds >> m_data; }

void PropertyType_PropertySet::serialize(QDataStream &ds) const {
  ds << m_data;
}

void PropertyType_PropertySet::toDebugString(QDebug dbg) const {}
