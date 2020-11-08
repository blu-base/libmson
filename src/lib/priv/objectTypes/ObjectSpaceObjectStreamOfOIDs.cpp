#include "ObjectSpaceObjectStreamOfOIDs.h"

#include "ObjectSpaceObjectStreamHeader.h"

namespace libmson{
namespace priv{

ObjectSpaceObjectStreamOfOIDs::ObjectSpaceObjectStreamOfOIDs()
    : IObjectSpaceObjectStream() {}

ObjectSpaceObjectStreamOfOIDs::ObjectSpaceObjectStreamOfOIDs(
    const ObjectSpaceObjectStreamHeader::OsidStreamPresence &osidStreamPresence,
    const ObjectSpaceObjectStreamHeader::ExtendedStreamPresence
        &extendedStreamPresence)
    : IObjectSpaceObjectStream(osidStreamPresence, extendedStreamPresence) {}

ObjectSpaceObjectStreamOfOIDs::~ObjectSpaceObjectStreamOfOIDs() {}

} //namespace priv
} // namespace libmson
