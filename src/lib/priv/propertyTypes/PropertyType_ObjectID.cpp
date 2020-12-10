#include "PropertyType_ObjectID.h"

namespace libmson {
namespace priv {

PropertyType_ObjectID::PropertyType_ObjectID() {}

CompactID PropertyType_ObjectID::data() const { return m_data; }

void PropertyType_ObjectID::setData(const CompactID& data) { m_data = data; }


PropertyIDType PropertyType_ObjectID::getType() const
{
  return PropertyIDType::ObjectID;
}

void PropertyType_ObjectID::deserialize(QDataStream& ds) { ds >> m_data; }

void PropertyType_ObjectID::serialize(QDataStream& ds) const { ds << m_data; }

} // namespace priv
} // namespace libmson
