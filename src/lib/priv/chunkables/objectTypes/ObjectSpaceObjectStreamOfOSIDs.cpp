#include "ObjectSpaceObjectStreamOfOSIDs.h"

namespace libmson {
namespace priv {

ObjectSpaceObjectStreamOfOSIDs::ObjectSpaceObjectStreamOfOSIDs()
    : IObjectSpaceObjectStream()
{
}

ObjectSpaceObjectStreamOfOSIDs::ObjectSpaceObjectStreamOfOSIDs(
    const ObjectSpaceObjectStreamHeader::OsidStreamPresence& osidStreamPresence,
    const ObjectSpaceObjectStreamHeader::ExtendedStreamPresence&
        extendedStreamPresence)
    : IObjectSpaceObjectStream(osidStreamPresence, extendedStreamPresence)
{
}

ObjectSpaceObjectStreamOfOSIDs::~ObjectSpaceObjectStreamOfOSIDs() {}

} // namespace priv
} // namespace libmson
