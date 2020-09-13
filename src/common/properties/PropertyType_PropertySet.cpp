#include "PropertyType_PropertySet.h"

#include <QDataStream>
#include <QDebug>

namespace MSONcommon {

PropertySet PropertyType_PropertySet::data() const { return m_data; }

void PropertyType_PropertySet::setData(const PropertySet &data) {
  m_data = data;
}

void PropertyType_PropertySet::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter << m_data;
}

PropertyType_PropertySet::PropertyType_PropertySet() {}

void PropertyType_PropertySet::deserialize(QDataStream &ds) { ds >> m_data; }

void PropertyType_PropertySet::serialize(QDataStream &ds) const {
  ds << m_data;
}

void PropertyType_PropertySet::toDebugString(QDebug &dbg) const {}

} // namespace MSONcommon
