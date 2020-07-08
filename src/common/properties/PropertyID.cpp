#include "PropertyID.h"

#include "../commonTypes/Enums.h"

#include <QDataStream>
#include <QDebug>

PropertyIDs PropertyID::id() const { return m_id; }

void PropertyID::setId(const PropertyIDs &id) { m_id = id; }

PropertyIDType PropertyID::type() const { return m_type; }

void PropertyID::setType(const PropertyIDType &type) { m_type = type; }

int PropertyID::boolValue() const {
  if (m_type == PropertyIDType::Bool) {
    return m_boolValue;
  } else {
    return -1;
  }
}

void PropertyID::setBoolValue(bool boolValue) {
  if (m_type == PropertyIDType::Bool) {
    m_boolValue = boolValue;
  } else {
    m_boolValue = false;
  }
}

PropertyID::PropertyID()
    : m_id(PropertyIDs::None), m_type(PropertyIDType::None),
      m_boolValue(false) {}

PropertyID::PropertyID(const PropertyIDs &id, const PropertyIDType &type)
    : m_id(id), m_type(type), m_boolValue(false) {}

void PropertyID::deserialize(QDataStream &ds) {
  quint32 temp;

  ds >> temp;

  m_id = static_cast<PropertyIDs>((temp << 6) >> 6);
  m_type = static_cast<PropertyIDType>((temp << 1) >> 27);
  m_boolValue = temp << 31;

  if (m_type != PropertyIDType::Bool) {
    m_boolValue = false;
  }
}

void PropertyID::serialize(QDataStream &ds) const {
  quint32 temp{};

  temp += m_boolValue << 31;
  temp += static_cast<quint32>(m_type) << 26;
  temp += static_cast<quint32>(m_id);

  ds << temp;
}

void PropertyID::toDebugString(QDebug dbg) const {}
