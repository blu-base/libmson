#include "PropertySet.h"
#include <QDebug>
quint32 PropertySet::cProperties() const { return m_cProperties; }

void PropertySet::setCProperties(const quint32 &cProperties) {
  m_cProperties = cProperties;
}

std::vector<PropertyID> PropertySet::rgPrids() const { return m_rgPrids; }

void PropertySet::setRgPrids(const std::vector<PropertyID> &rgPrids) {
  m_rgPrids = rgPrids;
}

QByteArray PropertySet::rgData() const { return m_rgData; }

void PropertySet::setRgData(const QByteArray &rgData) { m_rgData = rgData; }

/// \todo implement propertyset
void PropertySet::deserialize(QDataStream &ds) {}

void PropertySet::serialize(QDataStream &ds) const {}

void PropertySet::toDebugString(QDebug dbg) const {}

PropertySet::PropertySet() : m_cProperties{} {}

QDataStream &operator<<(QDataStream &ds, const PropertySet &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, PropertySet &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const PropertySet &obj) {
  obj.toDebugString(dbg);
  return dbg;
}
