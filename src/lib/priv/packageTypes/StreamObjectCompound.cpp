#include "StreamObjectCompound.h"
namespace libmson {
namespace packStore {
namespace streamObj {

StreamObjectCompound::StreamObjectCompound() {}

// std::vector<StreamObjectCompound_SPtr_t>
// StreamObjectCompound::getObjects() const
//{
//  return m_objects;
//}

// std::vector<StreamObjectCompound_SPtr_t>
// StreamObjectCompound::getObjects(const std::type_info& ti) const
//{
//  std::vector<StreamObjectCompound_SPtr_t> vec{};

//  std::copy_if(
//      m_objects.begin(), m_objects.end(), std::back_inserter(vec),
//      [&](auto entry) { return typeid(*entry) == ti; });

//  return vec;
//}

} // namespace streamObj
} // namespace packStore
} // namespace libmson
