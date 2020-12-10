#include "PropertyType_PropertySet.h"

namespace libmson {
namespace priv {

PropertyType_PropertySet::PropertyType_PropertySet() {}

PropertySet PropertyType_PropertySet::data() const { return m_data; }

void PropertyType_PropertySet::setData(const PropertySet& data)
{
  m_data = data;
}

quint64 PropertyType_PropertySet::getSizeInFile() const
{
  return m_data.getSizeInFile();
}

PropertyIDType PropertyType_PropertySet::getType() const
{
  return PropertyIDType::PropertySet;
}

void PropertyType_PropertySet::deserialize(QDataStream& ds) { ds >> m_data; }

void PropertyType_PropertySet::serialize(QDataStream& ds) const
{
  ds << m_data;
}

} // namespace priv
} // namespace libmson
