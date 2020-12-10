#include "PropertyType_NoData.h"

namespace libmson {
namespace priv {

PropertyType_NoData::PropertyType_NoData() {}

PropertyIDType PropertyType_NoData::getType() const
{
  return PropertyIDType::NoData;
}
void PropertyType_NoData::deserialize(QDataStream& ds) {}

void PropertyType_NoData::serialize(QDataStream& ds) const {}

} // namespace priv
} // namespace libmson
