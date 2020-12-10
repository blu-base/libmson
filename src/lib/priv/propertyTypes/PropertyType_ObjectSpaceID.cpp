#include "PropertyType_ObjectSpaceID.h"

namespace libmson {
namespace priv {


PropertyType_ObjectSpaceID::PropertyType_ObjectSpaceID() {}

PropertyIDType PropertyType_ObjectSpaceID::getType() const
{
  return PropertyIDType::ObjectSpaceID;
}

void PropertyType_ObjectSpaceID::deserialize(QDataStream& ds) {}

void PropertyType_ObjectSpaceID::serialize(QDataStream& ds) const {}

} // namespace priv
} // namespace libmson
