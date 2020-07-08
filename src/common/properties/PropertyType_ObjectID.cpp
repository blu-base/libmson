#include "PropertyType_ObjectID.h"

#include <QDataStream>
#include <QDebug>

CompactID PropertyType_ObjectID::data() const { return m_data; }

void PropertyType_ObjectID::setData(const CompactID &data) { m_data = data; }

PropertyType_ObjectID::PropertyType_ObjectID() {}

void PropertyType_ObjectID::deserialize(QDataStream &ds) { ds >> m_data; }

void PropertyType_ObjectID::serialize(QDataStream &ds) const { ds << m_data; }

void PropertyType_ObjectID::toDebugString(QDebug dbg) const {}
