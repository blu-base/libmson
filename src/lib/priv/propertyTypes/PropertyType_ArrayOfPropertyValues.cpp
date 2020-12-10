#include "PropertyType_ArrayOfPropertyValues.h"

namespace libmson {
namespace priv {

PropertyType_ArrayOfPropertyValues::PropertyType_ArrayOfPropertyValues()
    : m_cProperties(0)
{
}

quint32 PropertyType_ArrayOfPropertyValues::cProperties() const
{
  return m_cProperties;
}

void PropertyType_ArrayOfPropertyValues::setCProperties(
    const quint32& cProperties)
{
  m_cProperties = cProperties;
}

PropertyID PropertyType_ArrayOfPropertyValues::prid() const { return m_prid; }

void PropertyType_ArrayOfPropertyValues::setPrid(const PropertyID& prid)
{
  m_prid = prid;
}

std::vector<PropertySet> PropertyType_ArrayOfPropertyValues::data() const
{
  return m_data;
}

void PropertyType_ArrayOfPropertyValues::setData(
    const std::vector<PropertySet>& data)
{
  m_data = data;
}

quint64 PropertyType_ArrayOfPropertyValues::getSizeInFile() const
{
  return sizeInFileBase + std::accumulate(
                              m_data.begin(), m_data.end(), 0,
                              [&](quint64 a, const PropertySet& entry) {
                                return a + entry.getSizeInFile();
                              });
}

PropertyIDType PropertyType_ArrayOfPropertyValues::getType() const
{
  return PropertyIDType::ArrayOfPropertyValues;
}

void PropertyType_ArrayOfPropertyValues::deserialize(QDataStream& ds)
{
  ds >> m_cProperties;

  if (m_cProperties != 0) {
    ds >> m_prid;

    for (quint32 i{0}; i < m_cProperties; i++) {
      PropertySet ps;
      ds >> ps;
      m_data.push_back(ps);
    }
  }
}

void PropertyType_ArrayOfPropertyValues::serialize(QDataStream& ds) const
{
  ds << m_cProperties;

  if (m_cProperties != 0) {
    ds << m_prid;

    for (quint32 i{0}; i < m_cProperties; i++) {
      ds << m_data.at(i);
    }
  }
}

} // namespace priv
} // namespace libmson
