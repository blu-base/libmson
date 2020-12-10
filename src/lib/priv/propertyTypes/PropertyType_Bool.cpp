#include "PropertyType_Bool.h"

namespace libmson {
namespace priv {

PropertyType_Bool::PropertyType_Bool() {}


PropertyIDType PropertyType_Bool::getType() const
{
  return PropertyIDType::Bool;
}
void PropertyType_Bool::deserialize(QDataStream& ds) {}

void PropertyType_Bool::serialize(QDataStream& ds) const {}


} // namespace priv
} // namespace libmson
